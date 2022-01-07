/**
 * @file multiplier754_AT4.hh
 * @author Luigi Capogrosso
 * @date 17 Jan 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#ifndef __MULTIPLIER754_AT4_HH__
#define __MULTIPLIER754_AT4_HH__

#include <tlm.h>
#include <systemc.h>

#include "AT4.hh"

//==============================================================================
class multiplier754_AT4
    : public sc_module
    , public virtual tlm::tlm_fw_transport_if<>
{
public:
    tlm::tlm_target_socket<> target_socket;

    virtual void b_transport(tlm::tlm_generic_payload &trans, sc_time &t);

    virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload &trans,
                                    tlm::tlm_dmi &dmi_data);

    virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload &trans,
                                               tlm::tlm_phase &phase,
                                               sc_time &t);

    virtual unsigned int transport_dbg(tlm::tlm_generic_payload &trans);

    iostruct ioDataStruct;
    tlm::tlm_generic_payload *pending_transaction;

    sc_event io_event;
    void IOPROCESS();

    void multiplier_function();

    void end_of_elaboration();

    void reset();

    SC_HAS_PROCESS(multiplier754_AT4);

    multiplier754_AT4(sc_module_name name_);
};
//==============================================================================
#endif
