/**
 * @file multiplier754_AT4_tb.cc
 * @author Luigi Capogrosso
 * @date 17 Jan 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#include "multiplier754_AT4_tb.hh"

//==============================================================================
void multiplier754_AT4_tb::invalidate_direct_mem_ptr(uint64 start_range,
                                                     uint64 end_range)
{

}
//==============================================================================
tlm::tlm_sync_enum
//==============================================================================
multiplier754_AT4_tb::nb_transport_bw(tlm::tlm_generic_payload &trans,
                                      tlm::tlm_phase &phase,
                                      sc_time &t)
{
    // There must be a pending response.
    if (!response_pending)
    {
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return tlm::TLM_COMPLETED;
    }

    // The phase should be BEGIN_RESP.
    if (phase != tlm::BEGIN_RESP)
    {
        trans.set_response_status(tlm::TLM_GENERIC_ERROR_RESPONSE);
        return tlm::TLM_COMPLETED;
    }

    available_response.notify();
    phase = tlm::END_RESP;

    return tlm::TLM_COMPLETED;
}
//==============================================================================
void multiplier754_AT4_tb::run()
{
    sc_time local_time = SC_ZERO_TIME;

    // First transaction (initialization).
    iostruct multiplier_packet;
    tlm::tlm_generic_payload payload;

    for (int i = 1; i <= 10000000; i++)
    {
        multiplier_packet.in_op1 = rand();
        multiplier_packet.in_op2 = rand();

        // Start write transaction.
        tlm::tlm_phase phase = tlm::BEGIN_REQ;
        tlm::tlm_generic_payload payload;
        payload.set_address(0);
        payload.set_data_ptr((unsigned char *)&multiplier_packet);
        payload.set_write();

        tlm::tlm_sync_enum result =
            initiator_socket->nb_transport_fw(payload, phase, local_time);

        if (result == tlm::TLM_COMPLETED)
        {
            /* If the target immediately completes the transaction something
             * wrong happened. We should inspect the response status and
             * take appropriate actions. In this case we just stop the
             * simulation.
             */
            sc_stop();
        }

        // Phase must be END_REQ.
        if (phase != tlm::END_REQ)
        {
            sc_stop();
        }

        response_pending = true;
        wait(available_response);
        response_pending = false;

        // Start read transaction.
        phase = tlm::BEGIN_REQ;
        payload.set_address(0);
        payload.set_data_ptr((unsigned char *)&multiplier_packet);
        payload.set_read();

        result = initiator_socket->nb_transport_fw(payload, phase, local_time);

        if (result == tlm::TLM_COMPLETED)
        {
            /* If the target immediately completes the transaction something
             * wrong happened. We should inspect the response status and
             * take appropriate actions. In this case we just stop the
             * simulation.
             */
            sc_stop();
        }

        // Phase must be END_REQ.
        if (phase != tlm::END_REQ)
        {
            sc_stop();
        }

        response_pending = true;
        wait(available_response);
        response_pending = false;

        if (payload.get_response_status() == tlm::TLM_OK_RESPONSE)
        {
        }
    }
    sc_stop();
}
//==============================================================================
multiplier754_AT4_tb::multiplier754_AT4_tb(sc_module_name name)
    : sc_module(name)
    , response_pending(false)
{
    initiator_socket(*this);
    SC_THREAD(run);
}
//==============================================================================
