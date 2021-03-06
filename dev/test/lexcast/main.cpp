#include <string>
#include <iostream>

#include <cpp_util_3/lexcast.hpp>

#include <test/helpers.hpp>

void
to_string()
{
	std::string a;

	a = cpp_util_3::lexcast< std::string >( 123 );
	CHECK_CONDITION( "123" == a );

	a = cpp_util_3::lexcast< std::string >( -123 );
	CHECK_CONDITION( "-123" == a );

	a = cpp_util_3::lexcast< std::string >( 123.123 );
	CHECK_CONDITION( "123.123" == a );

	a = cpp_util_3::lexcast< std::string >( -123.123 );
	CHECK_CONDITION( "-123.123" == a );

	a = cpp_util_3::lexcast< std::string >( "`123'" );
	CHECK_CONDITION( "`123'" == a );
}

void
from_string()
{
	int i;
	i = cpp_util_3::lexcast< int >( "123" );
	CHECK_CONDITION( 123 == i );

	i = cpp_util_3::lexcast< int >( "-123" );
	CHECK_CONDITION( -123 == i );

	unsigned int ui;
	ui = cpp_util_3::lexcast< unsigned int >( "123" );
	CHECK_CONDITION( 123 == ui );
}

UNIT_TEST_MAIN(
	to_string();

	from_string();
)
