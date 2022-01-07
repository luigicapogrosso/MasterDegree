/**
 * @file LT.hh
 * @author Luigi Capogrosso
 * @date 17 Jan 2019
 * @copyright 2019 Luigi Capogrosso
 * @brief <brief>
 */

#ifndef __LT_HH__
#define __LT_HH__

#include <systemc.h>

//==============================================================================
#define ADDRESS_TYPE int
#define DATA_TYPE iostruct
//==============================================================================
struct iostruct
{
    sc_int<32> in_op1;
    sc_int<32> in_op2;
    sc_int<32> res;
};
//==============================================================================
// Convert uint in float bit to bit.
typedef union
{
    unsigned int uint;
    float        fp;
} ieee754;
//==============================================================================
#endif
