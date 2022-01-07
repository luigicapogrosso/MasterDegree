/**
 * @file main_multiplier754_UT.cc
 * @author Luigi Capogrosso
 * @date 17 Jan 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#include "multiplier754_UT.hh"
#include "multiplier754_UT_tb.hh"

//==============================================================================
class multiplier_top
    : public sc_module
{
private:
    multiplier754_UT m_target;
    multiplier754_UT_tb m_initiator;

public:
    multiplier_top(sc_module_name name)
        : sc_module(name)
        , m_target("target")
        , m_initiator("initiator")
    {
        m_initiator.initiator_socket(m_target.target_socket);
    }
};
//==============================================================================
int main(int argc, char *argv[])
{
    multiplier_top top("top");
    sc_start();

    return 0;
}
//==============================================================================
