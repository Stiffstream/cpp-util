/*
 * Testing for at_scope_exit.
 */

#include <cpp_util_3/at_scope_exit.hpp>

#include <test/helpers.hpp>

#include <sstream>

using namespace cpp_util_3;

void
simple_test()
	{
		std::string v{ "Hello!" };

		{
			auto sentinel = at_scope_exit( [&] { v = "Bye!"; } );

			v += " How are you?";
			CHECK_CONDITION( "Hello! How are you?" == v );
		}

		CHECK_CONDITION( "Bye!" == v );
	}

UNIT_TEST_MAIN(
	simple_test();
)

