/**
 * @file multiplier754_LT.cc
 * @author Luigi Capogrosso
 * @date 17 Jan 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#include "multiplier754_LT.hh"

//==============================================================================
multiplier754_LT::multiplier754_LT(sc_module_name name_)
    : sc_module(name_)
    , target_socket("target_socket")
    , pending_transaction(NULL)
{
    target_socket(*this);
}
//==============================================================================
void multiplier754_LT::b_transport(tlm::tlm_generic_payload &trans, sc_time &t)
{
    timing_annotation = SC_ZERO_TIME;

    ioDataStruct = *((iostruct *)trans.get_data_ptr());

    if (trans.is_write())
    {
        multiplier_function();
        trans.set_response_status(tlm::TLM_OK_RESPONSE);
        ioDataStruct.res = tmp_res;
        *((iostruct *)trans.get_data_ptr()) = ioDataStruct;
    }
    else if (trans.is_read())
    {
        ioDataStruct.res = tmp_res;
        *((iostruct *)trans.get_data_ptr()) = ioDataStruct;
    }

    t += timing_annotation;
}
//==============================================================================
bool multiplier754_LT::get_direct_mem_ptr(tlm::tlm_generic_payload &trans,
                                          tlm::tlm_dmi &dmi_data)
{
    return false;
}
//==============================================================================
tlm::tlm_sync_enum
//==============================================================================
multiplier754_LT::nb_transport_fw(tlm::tlm_generic_payload &trans,
                                  tlm::tlm_phase &phase, sc_time &t)
{
    return tlm::TLM_COMPLETED;
}
//==============================================================================
unsigned int multiplier754_LT::transport_dbg(tlm::tlm_generic_payload &trans)
{
    return 0;
}
//==============================================================================
void multiplier754_LT::multiplier_function()
{
    ieee754 tmp_op1, tmp_op2, mul;

    tmp_op1.uint = ioDataStruct.in_op1;
    tmp_op2.uint = ioDataStruct.in_op2;
    mul.fp = tmp_op1.fp * tmp_op2.fp;

    tmp_res = mul.uint;
    timing_annotation += sc_time(100, SC_NS);
}
//==============================================================================
// Initialization.
//==============================================================================
void multiplier754_LT::end_of_elaboration()
{

}
//==============================================================================
void multiplier754_LT::reset()
{

}
//==============================================================================
