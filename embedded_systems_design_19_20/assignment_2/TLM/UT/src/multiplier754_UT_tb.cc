/**
 * @file multiplier754_UT_tb.cc
 * @author Luigi Capogrosso
 * @date 17 Jan 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#include "multiplier754_UT_tb.hh"
//==============================================================================
void multiplier754_UT_tb::invalidate_direct_mem_ptr(uint64 start_range,
                                                    uint64 end_range)
{

}
//==============================================================================
tlm::tlm_sync_enum
//==============================================================================
multiplier754_UT_tb::nb_transport_bw(tlm::tlm_generic_payload &trans,
                                     tlm::tlm_phase &phase, 
                                     sc_time &t)
{
    return tlm::TLM_COMPLETED;
}
//==============================================================================
void multiplier754_UT_tb::run()
{
    sc_time local_time;

    // First transaction.
    iostruct multiplier_packet;
    tlm::tlm_generic_payload payload;

    for (int i = 1; i <= 10000000; i++)
    {
        multiplier_packet.in_op1 = rand();
        multiplier_packet.in_op2 = rand();

        payload.set_data_ptr((unsigned char *)&multiplier_packet);
        payload.set_address(0);
        payload.set_write();

        initiator_socket->b_transport(payload, local_time);

        // Start read transaction.
        if (payload.get_response_status() == tlm::TLM_OK_RESPONSE)
        {
        }
    }

    sc_stop();
}
//==============================================================================
multiplier754_UT_tb::multiplier754_UT_tb(sc_module_name name)
    : sc_module(name)
{
    initiator_socket(*this);

    SC_THREAD(run);
}
