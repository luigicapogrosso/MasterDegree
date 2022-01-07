/**
 * @file multiplier754_AT4_tb.hh
 * @author Luigi Capogrosso
 * @date 17 Jan 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#ifndef __MULTIPLIER754_AT4_TB_HH
#define __MULTIPLIER754_AT4_TB_HH

#include <tlm.h>
#include <systemc.h>
#include "AT4.hh"

//==============================================================================
class multiplier754_AT4_tb
    : public sc_module
    , public virtual tlm::tlm_bw_transport_if<>
{
public:
    tlm::tlm_initiator_socket<> initiator_socket;

    multiplier754_AT4_tb(sc_module_name name);

private:
    SC_HAS_PROCESS(multiplier754_AT4_tb);

    virtual void invalidate_direct_mem_ptr(uint64 start_range,
                                           uint64 end_range);

    virtual tlm::tlm_sync_enum nb_transport_bw(tlm::tlm_generic_payload &trans,
                                               tlm::tlm_phase &phase,
                                               sc_time &t);

    void run();

    bool response_pending;
    sc_event available_response;
};
//===============================================================
#endif
