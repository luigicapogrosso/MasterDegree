/**
 * @file multiplier754_LT_tb.hh
 * @author Luigi Capogrosso
 * @date 17 Jan 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#ifndef __MULTIPLIER754_LT_TB_HH
#define __MULTIPLIER754_LT_TB_HH

#include <tlm.h>
#include <systemc.h>
#include <tlm_utils/tlm_quantumkeeper.h>

#include "LT.hh"

//==============================================================================
class multiplier754_LT_tb
    : public sc_module
    , public virtual tlm::tlm_bw_transport_if<>
{
public:
    tlm::tlm_initiator_socket<> initiator_socket;

    multiplier754_LT_tb(sc_module_name name);

private:
    SC_HAS_PROCESS(multiplier754_LT_tb);

    virtual void invalidate_direct_mem_ptr(uint64 start_range,
                                           uint64 end_range);

    virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &trans,
                                               tlm::tlm_phase &phase,
                                               sc_time &t);

    tlm_utils::tlm_quantumkeeper m_qk;

    void run();
};
//==============================================================================
#endif
