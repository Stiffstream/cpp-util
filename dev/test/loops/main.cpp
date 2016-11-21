/*
 * Testing for ensure.
 */

#include <cpp_util_3/loops.hpp>

#include <test/helpers.hpp>

using namespace cpp_util_3;

void
simple_n_times_int_arg()
	{
		const int N = 4;
		int i = 0;
		n_times( N, [&]{ ++i; } );

		CHECK_CONDITION( 4 == i );
	}

void
simple_n_times_uint_arg()
	{
		const unsigned int N = 4;
		int i = 0;
		n_times( N, [&]{ ++i; } );

		CHECK_CONDITION( 4 == i );
	}

void
simple_n_times_int_zero()
	{
		const int N = 0;
		int i = 0;
		n_times( N, [&]{ ++i; } );

		CHECK_CONDITION( 0 == i );
	}

void
simple_n_times_uint_zero()
	{
		const unsigned int N = 0;
		int i = 0;
		n_times( N, [&]{ ++i; } );

		CHECK_CONDITION( 0 == i );
	}

void
simple_n_times_negative_int()
	{
		const int N = -1;
		int i = 0;
		n_times( N, [&]{ ++i; } );

		CHECK_CONDITION( 0 == i );
	}

UNIT_TEST_MAIN(
	simple_n_times_int_arg();
	simple_n_times_uint_arg();
	simple_n_times_int_zero();
	simple_n_times_uint_zero();
	simple_n_times_negative_int();
)

