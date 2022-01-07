/**
 * @file multiplier754_LT_tb.cc
 * @author Luigi Capogrosso
 * @date 17 Jan 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#include "multiplier754_LT_tb.hh"
//==============================================================================
void multiplier754_LT_tb::invalidate_direct_mem_ptr(uint64 start_range,
                                                     uint64 end_range)
{

}
//==============================================================================
tlm::tlm_sync_enum
//==============================================================================
multiplier754_LT_tb::nb_transport_bw(tlm::tlm_generic_payload &trans,
                                     tlm::tlm_phase &phase,
                                     sc_time &t)
{
    return tlm::TLM_COMPLETED;
}
//==============================================================================
void multiplier754_LT_tb::run()
{
    sc_time local_time = m_qk.get_local_time();

    // First transaction (initialization).
    iostruct multiplier_packet;
    tlm::tlm_generic_payload payload;

    for (int i = 1; i <= 10000000; i++)
    {
        multiplier_packet.in_op1 = rand();
        multiplier_packet.in_op2 = rand();

        payload.set_data_ptr((unsigned char *)&multiplier_packet);
        payload.set_address(0);
        payload.set_write();

        local_time = m_qk.get_local_time();

        // Start write transaction.
        initiator_socket->b_transport(payload, local_time);

        // Start read transaction.
        if (payload.get_response_status() == tlm::TLM_OK_RESPONSE)
        {
        }

        m_qk.set(local_time);
        if (m_qk.need_sync())
        {
            m_qk.sync();
        }
    }
    sc_stop();
}
//==============================================================================
multiplier754_LT_tb::multiplier754_LT_tb(sc_module_name name)
    : sc_module(name)
{

    initiator_socket(*this);

    SC_THREAD(run);

    m_qk.set_global_quantum(sc_time(500, SC_NS));
    m_qk.reset();
}
//==============================================================================
