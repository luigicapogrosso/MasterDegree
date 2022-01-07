/**
 * @file main_multiplier754_AT4.cc
 * @author Luigi Capogrosso
 * @date 17 Jan 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#include "multiplier754_AT4.hh"
#include "multiplier754_AT4_tb.hh"

//==============================================================================
class multiplier_top
    : public sc_module
{
public:
    multiplier_top(sc_module_name name)
        : sc_module(name)
        , m_target("target")
        , m_initiator("initiator")
    {
        m_initiator.initiator_socket(m_target.target_socket);
    }
private:
    multiplier754_AT4 m_target;
    multiplier754_AT4_tb m_initiator;
};
//==============================================================================
int main(int argc, char *argv[])
{
    multiplier_top top("top");
    sc_start();

    return 0;
}
//==============================================================================
