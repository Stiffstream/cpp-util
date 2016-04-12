/*
 * Testing for rollback_on_exception.
 */

#include <cpp_util_3/rollback_on_exception.hpp>

#include <test/helpers.hpp>

#include <sstream>

using namespace cpp_util_3;

void
change_or_throw( std::string & what, bool must_throw )
	{
		if( must_throw )
			throw std::runtime_error( "change_or_throw: " + what );
		else
			what = "no_exception";
	}

void
void_f_test()
	{
		{
			std::string v{ "Hello!" };
			do_with_rollback_on_exception(
				[&]{ change_or_throw( v, false ); },
				[&]{ v = "thrown"; } );
			CHECK_CONDITION( "no_exception" == v );
		}

		{
			std::string v{ "Hello!" };
			CHECK_THROW(std::runtime_error,
				do_with_rollback_on_exception(
					[&]{ change_or_throw( v, true ); },
					[&]{ v = "thrown"; } );
			);

			CHECK_CONDITION( "thrown" == v );
		}
	}

std::string
return_or_throw( std::string & what, bool must_throw )
	{
		if( must_throw )
			throw std::runtime_error( "return_or_throw: " + what );
		else
			return what + "no_exception";
	}

void
nonvoid_f_test()
	{
		{
			std::string v{ "Hello!" };
			std::string r = do_with_rollback_on_exception(
				[&]{ return return_or_throw( v, false ); },
				[&]{ v = "thrown"; } );

			CHECK_CONDITION( "Hello!no_exception" == r );
		}

		{
			std::string v{ "Hello!" };
			CHECK_THROW(std::runtime_error,
				std::string r = do_with_rollback_on_exception(
					[&]{ return return_or_throw( v, true ); },
					[&]{ v = "thrown"; } );
			);

			CHECK_CONDITION( "thrown" == v );
		}
	}


UNIT_TEST_MAIN(
	void_f_test();
	nonvoid_f_test();
)

