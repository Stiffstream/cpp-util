/*
 * Test for terminate_if_throws
 */

#include <cpp_util_3/terminate_if_throws.hpp>

#include <iostream>
#include <stdexcept>

int safe_idiv( int a, int b )
{
	if( 0 == b )
		throw std::invalid_argument( "Division to 0" );

	return a / b;
}

void do_div( int a, int b )
{
	std::cout << a << "/" << b << "=" << std::flush;
	const auto r = cpp_util_3::terminate_if_throws( [&] {
			return safe_idiv(a, b);
		} );
	std::cout << r << std::endl;
}

int main()
{
	do_div( 3, 2 );
	do_div( 4, 0 );
	
	return 0;
}

