/*
 * Tests for string_dumper.
 */

#include <cpp_util_3/hex_dumps/string_dumper.hpp>

#include <test/helpers.hpp>

#include <sstream>

using namespace cpp_util_3::hex_dumps;

void
test_empty_string()
	{
		std::ostringstream to;

		to << string_dumper( std::string() );

		CHECK_CONDITION( std::string() == to.str() );

		to << string_dumper( std::string( "" ) );

		CHECK_CONDITION( std::string() == to.str() );
	}

void
test_hello_world()
	{
		std::ostringstream to;

		to << "'" << string_dumper( "hello, world" ) << "'";

		CHECK_CONDITION(
				"'68 65 6c 6c 6f 2c 20 77 6f 72 6c 64'" == to.str() );
	}

void
test_hello_world_no_spaces()
	{
		std::ostringstream to;

		to << "'" << string_dumper_without_spaces( "hello, world" ) << "'";

		CHECK_CONDITION(
				"'68656c6c6f2c20776f726c64'" == to.str() );
	}

void
test_escaped_symbols()
	{
		std::ostringstream to;

		to << "'" << string_dumper( "\x01\x02\x03\x0A\x10\x1F" ) << "'";

		CHECK_CONDITION(
				"'01 02 03 0a 10 1f'" == to.str() );
	}

void
test_hex_escaped_empty_string()
	{
		std::ostringstream to;

		to << hex_escaped_string_dumper( std::string() );

		CHECK_CONDITION( std::string() == to.str() );

		to << hex_escaped_string_dumper( std::string( "" ) );

		CHECK_CONDITION( std::string() == to.str() );

		to << hex_escaped_string_dumper( "" );

		CHECK_CONDITION( std::string() == to.str() );
	}

void
test_hex_escaped_symbols()
	{
		std::ostringstream to;

		to << '\'' << hex_escaped_string_dumper( "\x01\x02\x03\x0A\x10\x1F" )
				<< '\'';

		CHECK_CONDITION( "'\\x01\\x02\\x03\\x0a\\x10\\x1f'" == to.str() );
	}

void
test_hex_escaped_mixed_symbols()
	{
		std::ostringstream to;

		to << '\'' << hex_escaped_string_dumper( "\x02/03/0024/\x03" )
				<< '\'';

		CHECK_CONDITION( "'\\x02/03/0024/\\x03'" == to.str() );
	}

UNIT_TEST_MAIN(
	test_empty_string();
	test_hello_world();
	test_hello_world_no_spaces();
	test_escaped_symbols();
	test_hex_escaped_empty_string();
	test_hex_escaped_symbols();
	test_hex_escaped_mixed_symbols();
)

