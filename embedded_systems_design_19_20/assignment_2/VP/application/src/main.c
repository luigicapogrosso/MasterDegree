//----------------------------------------------------------
//-- TITLE: Example of C main code rom for mos6502
//--
//-- Author: Stefano Centomo
//--
//-- Date:19/04/2018
//----------------------------------------------------------
//---------------------------------------
//---------------------------------------
//
//	M6502
//	SUPPORTED TYPES & DIMENSIONS
//
//  int 		=>	16 bits
//  char		=>	8 bits
//  uint8_t/int8_t	=>	8 bits
//  uint16_t/int16_t	=>	16 bits
//  uint32_t/int32_t	=>	32 bits
//  float/double	=> not supported
//
//---------------------------------------
//---------------------------------------

#include <stdbool.h>
#include "custom_stdlib.h"
#include "routines.h"

static void test_multiplier()
{
	// VARIABLES
	uint16_t op1	= 5;
	uint16_t op2	= 2;
	uint32_t result	= 0;

	// Test the multiplier pheripheral
 	result = mul(op1, op2);
 	//Write the result on IO Module
 	io_write(result);
 	//Read new data from IO Module
	op2	= (uint16_t) io_read();
	//Execute multiplication with new op2
 	result = mul(op1, op2);
 	//Write result on IO Module
 	io_write(result);
}

static void test_multiplier754_v(
	uint32_t op1,
	uint32_t op2,
	uint32_t *result)
{
	// Test the multiplier 754 floating-point pheripheral.
 	*result = mul754_v(op1, op2);
}

static void test_multiplier754_vhd(
	uint32_t op1,
	uint32_t op2,
	uint32_t *result)
{
	// Test the multiplier 754 floating-point pheripheral.
 	*result = mul754_vhd(op1, op2);
}

int main()
{
	// Variables.
	uint32_t in_op1	= 0x40000000; // 2.0
	uint32_t in_op2	= 0x3f000000; // 0.5

	uint32_t out_res1, out_res2;
	uint32_t is_equals;

	test_multiplier754_v(in_op1, in_op2, &out_res1);
	test_multiplier754_vhd(in_op1, in_op2, &out_res2);

	if (out_res1 == out_res2)
	{
		io_write(1);
	}
	else
	{
		io_write(0);
	}

	is_equals = io_read();

	return 0;
}
