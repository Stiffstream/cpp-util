/*
 * Testing for at_scope_exit.
 */

#include <cpp_util_3/at_scope_exit.hpp>

#include <test/helpers.hpp>

#include <sstream>
#include <functional>

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

void
move_at_exit_object_1()
	{
		int v = 0;
		std::function<void()> f([&]{ v = 1; });

		{
			auto sentinel1 = at_scope_exit(f);
			auto sendinel2{std::move(sentinel1)};
		}
		CHECK_CONDITION( 1 == v );
	}

void
move_at_exit_object_2()
	{
		int v = 0;
		std::function<void()> f([&]{ v = 1; });

		{
			auto sentinel1 = at_scope_exit(std::move(f));
			auto sendinel2{std::move(sentinel1)};
		}
		CHECK_CONDITION( 1 == v );
	}

UNIT_TEST_MAIN(
	simple_test();
	move_at_exit_object_1();
	move_at_exit_object_2();
)

