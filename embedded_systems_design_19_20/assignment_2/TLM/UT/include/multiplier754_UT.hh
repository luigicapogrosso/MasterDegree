/**
 * @file multiplier754_UT.hh
 * @author Luigi Capogrosso
 * @date 17 Jan 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#ifndef __MULTIPLIER754_UT_HH__
#define __MULTIPLIER754_UT_HH__

#include <tlm.h>
#include <systemc.h>

#include "UT.hh"

//==============================================================================
class multiplier754_UT
    : public sc_module
    , public virtual tlm::tlm_fw_transport_if<>
{
public:
    tlm::tlm_target_socket<> target_socket;

    virtual void b_transport(tlm::tlm_generic_payload& trans, sc_time& t);

    virtual bool get_direct_mem_ptr(tlm::tlm_generic_payload& trans,
                                    tlm::tlm_dmi& dmi_data);

    virtual tlm::tlm_sync_enum nb_transport_fw(tlm::tlm_generic_payload& trans,
                                               tlm::tlm_phase& phase,
                                               sc_time& t);

    virtual unsigned int transport_dbg(tlm::tlm_generic_payload& trans);

    iostruct ioDataStruct;
    tlm::tlm_generic_payload *pending_transaction;
    sc_int<32> tmp_res;

    void multiplier_function();

    void end_of_elaboration();

    void reset();

    SC_HAS_PROCESS(multiplier754_UT);

    multiplier754_UT(sc_module_name name_);
};
//==============================================================================
#endif
