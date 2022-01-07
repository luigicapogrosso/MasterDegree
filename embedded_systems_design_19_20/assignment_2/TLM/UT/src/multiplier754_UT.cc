/**
 * @file multiplier754_UT.cc
 * @author Luigi Capogrosso
 * @date 17 Jan 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#include "multiplier754_UT.hh"

//==============================================================================
multiplier754_UT::multiplier754_UT(sc_module_name name_)
    : sc_module(name_)
    , target_socket("target_socket")
    , pending_transaction(NULL)
{
    target_socket(*this);
}
//==============================================================================
void multiplier754_UT::b_transport(tlm::tlm_generic_payload &trans, sc_time &t)
{
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
}
//==============================================================================
bool multiplier754_UT::get_direct_mem_ptr(tlm::tlm_generic_payload &trans,
                                       tlm::tlm_dmi &dmi_data)
{
    return false;
}
//==============================================================================
tlm::tlm_sync_enum
//==============================================================================
multiplier754_UT::nb_transport_fw(tlm::tlm_generic_payload &trans,
                               tlm::tlm_phase &phase,
                               sc_time &t)
{
    return tlm::TLM_COMPLETED;
}
//==============================================================================
unsigned int multiplier754_UT::transport_dbg(tlm::tlm_generic_payload &trans)
{
    return 0;
}
//==============================================================================
void multiplier754_UT::multiplier_function()
{
    ieee754 tmp_op1, tmp_op2, mul;

    tmp_op1.uint = ioDataStruct.in_op1;
    tmp_op2.uint = ioDataStruct.in_op2;
    mul.fp = tmp_op1.fp * tmp_op2.fp;

    tmp_res = mul.uint;
}
//==============================================================================
// Initialization.
void multiplier754_UT::end_of_elaboration()
{

}
//==============================================================================
void multiplier754_UT::reset()
{

}
//==============================================================================
