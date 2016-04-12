/*
 * Testing for ensure.
 */

#include <cpp_util_2/h/ensure.hpp>

#include <test/h/helpers.hpp>

using namespace cpp_util_2;

void
simple_test()
	{
		std::string v{ "Hello!" };
		CHECK_THROW(std::invalid_argument,
			ensure< std::invalid_argument >( "Bye!" == v,
				[]{ return "expected 'Bye!'"; } );
		);
	}

UNIT_TEST_MAIN(
	simple_test();
)

