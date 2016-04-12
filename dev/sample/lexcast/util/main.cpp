/*
	ѕример работы со средствами из cpp_util_3/lexcast/h/util.hpp.
*/

#include <map>
#include <set>
#include <string>
#include <iostream>
#include <stdexcept>
#include <climits>

#include <cpp_util_3/lexcasts/h/util.hpp>

// ƒемонстраци€ работы cpp_util_3::slexcast.
void
slexcast_demo()
{
	std::string pre( "This is string with spaces." );
	std::string	post( cpp_util_3::slexcast( pre ) );

	std::cout << "*** slexcast_demo:\n\tpre: "
		<< pre << "\n\tpost: " << post << "\n" << std::endl;
}

// ƒемонстраци€ преобразовани€ в шестнадцатиричное представление.
void
hex_putter_demo()
{
	// ≈сли тип char по умолчанию беззнаковый.
	char c1 = 16;
	// ≈сли тип char по умолчанию знаковый.
	char c2 = static_cast< char >( -3 );
	signed char c_negative = -3;
	unsigned char uc = 16;

	short s = 16;
	short s_negative = -3;
	unsigned short us = 16;
	int i = 16;
	int i_negative = -3;
	unsigned int ui = 16;
	long l = 16;
	long l_negative = -3;
	unsigned long ul = 16;

	std::cout << "*** hex_putter_demo:\n\t"
		<< static_cast<int>(c1) << " " << cpp_util_3::slexcast( c1,
			cpp_util_3::lexcasts::hex() ) << ", "
		<< cpp_util_3::slexcast( c1,
			cpp_util_3::lexcasts::hex_0x() ) << ", "
		<< cpp_util_3::slexcast( c1,
			cpp_util_3::lexcasts::hex_bslashx() )
		<< "\n\t"

		<< static_cast<int>(c2) << " " << cpp_util_3::slexcast( c2,
			cpp_util_3::lexcasts::hex() ) << ", "
		<< cpp_util_3::slexcast( c2,
			cpp_util_3::lexcasts::hex_0x() ) << ", "
		<< cpp_util_3::slexcast( c2,
			cpp_util_3::lexcasts::hex_bslashx() )
		<< "\n\t"

		<< static_cast<int>(c_negative) << " " << cpp_util_3::slexcast( c_negative,
			cpp_util_3::lexcasts::hex() ) << ", "
		<< cpp_util_3::slexcast( c_negative,
			cpp_util_3::lexcasts::hex_0x() ) << ", "
		<< cpp_util_3::slexcast( c_negative,
			cpp_util_3::lexcasts::hex_bslashx() )
		<< "\n\t"

		<< static_cast<unsigned int>(uc) << " " << cpp_util_3::slexcast( uc,
			cpp_util_3::lexcasts::hex() ) << ", "
		<< cpp_util_3::slexcast( uc,
			cpp_util_3::lexcasts::hex_0x() ) << ", "
		<< cpp_util_3::slexcast( uc,
			cpp_util_3::lexcasts::hex_bslashx() )
		<< "\n\t"

		<< s << " " << cpp_util_3::slexcast( s,
			cpp_util_3::lexcasts::hex() ) << ", "
		<< cpp_util_3::slexcast( s,
			cpp_util_3::lexcasts::hex_0x() ) << ", "
		<< cpp_util_3::slexcast( s,
			cpp_util_3::lexcasts::hex_bslashx() )
		<< "\n\t"

		<< s_negative << " " << cpp_util_3::slexcast( s_negative,
			cpp_util_3::lexcasts::hex() ) << ", "
		<< cpp_util_3::slexcast( s_negative,
			cpp_util_3::lexcasts::hex_0x() ) << ", "
		<< cpp_util_3::slexcast( s_negative,
			cpp_util_3::lexcasts::hex_bslashx() )
		<< "\n\t"

		<< us << " " << cpp_util_3::slexcast( us,
			cpp_util_3::lexcasts::hex() ) << ", "
		<< cpp_util_3::slexcast( us,
			cpp_util_3::lexcasts::hex_0x() ) << ", "
		<< cpp_util_3::slexcast( us,
			cpp_util_3::lexcasts::hex_bslashx() )
		<< "\n\t"

		<< i << " " << cpp_util_3::slexcast( i,
			cpp_util_3::lexcasts::hex() ) << ", "
		<< cpp_util_3::slexcast( i,
			cpp_util_3::lexcasts::hex_0x() ) << ", "
		<< cpp_util_3::slexcast( i,
			cpp_util_3::lexcasts::hex_bslashx() )
		<< "\n\t"

		<< i_negative << " " << cpp_util_3::slexcast( i_negative,
			cpp_util_3::lexcasts::hex() ) << ", "
		<< cpp_util_3::slexcast( i_negative,
			cpp_util_3::lexcasts::hex_0x() ) << ", "
		<< cpp_util_3::slexcast( i_negative,
			cpp_util_3::lexcasts::hex_bslashx() )
		<< "\n\t"

		<< ui << " " << cpp_util_3::slexcast( ui,
			cpp_util_3::lexcasts::hex() ) << ", "
		<< cpp_util_3::slexcast( ui,
			cpp_util_3::lexcasts::hex_0x() ) << ", "
		<< cpp_util_3::slexcast( ui,
			cpp_util_3::lexcasts::hex_bslashx() )
		<< "\n\t"

		<< l << " " << cpp_util_3::slexcast( l,
			cpp_util_3::lexcasts::hex() ) << ", "
		<< cpp_util_3::slexcast( l,
			cpp_util_3::lexcasts::hex_0x() ) << ", "
		<< cpp_util_3::slexcast( l,
			cpp_util_3::lexcasts::hex_bslashx() )
		<< "\n\t"

		<< l_negative << " " << cpp_util_3::slexcast( l_negative,
			cpp_util_3::lexcasts::hex() ) << ", "
		<< cpp_util_3::slexcast( l_negative,
			cpp_util_3::lexcasts::hex_0x() ) << ", "
		<< cpp_util_3::slexcast( l_negative,
			cpp_util_3::lexcasts::hex_bslashx() )
		<< "\n\t"

		<< ul << " " << cpp_util_3::slexcast( ul,
			cpp_util_3::lexcasts::hex() ) << ", "
		<< cpp_util_3::slexcast( ul,
			cpp_util_3::lexcasts::hex_0x() ) << ", "
		<< cpp_util_3::slexcast( ul,
			cpp_util_3::lexcasts::hex_bslashx() )
		<< "\n\t"

		<< 127 << " " << cpp_util_3::slexcast( 127,
			cpp_util_3::lexcasts::hex() ) << ", "
		<< cpp_util_3::slexcast( 127,
			cpp_util_3::lexcasts::hex_0x() ) << ", "
		<< cpp_util_3::slexcast( 127,
			cpp_util_3::lexcasts::hex_bslashx() )
		<< "\n\t"

		<< -127 << " " << cpp_util_3::slexcast( -127,
			cpp_util_3::lexcasts::hex() ) << ", "
		<< cpp_util_3::slexcast( -127,
			cpp_util_3::lexcasts::hex_0x() ) << ", "
		<< cpp_util_3::slexcast( -127,
			cpp_util_3::lexcasts::hex_bslashx() ) << "\n"
		<< std::endl;
}

// ƒемонстраци€ преобразовани€ из шестнадцатиричного представлени€ в число.
void
hex_getter_demo()
{
	std::cout << "*** hex_getter_demo:" << std::endl;

	std::string hex8( "f3" );

	char c = cpp_util_3::lexcast< char >( hex8,
		cpp_util_3::lexcasts::def_putter(),
		cpp_util_3::lexcasts::hex_getter() );
	signed char sc = cpp_util_3::lexcast< signed char >( hex8,
		cpp_util_3::lexcasts::def_putter(),
		cpp_util_3::lexcasts::hex_getter() );
	unsigned char uc = cpp_util_3::lexcast< unsigned char >( hex8,
		cpp_util_3::lexcasts::def_putter(),
		cpp_util_3::lexcasts::hex_getter() );

	std::cout << "\n\thex8: " << hex8
		<< "\n\tchar: " << static_cast<short>(c)
		<< "\n\tsigned char: " << static_cast<short>(sc)
		<< "\n\tunsigned char: " << static_cast<unsigned short>(uc)
		<< std::endl;

	std::string	hex16( "ff5d" );

	short s = cpp_util_3::lexcast< short >( hex16,
		cpp_util_3::lexcasts::def_putter(),
		cpp_util_3::lexcasts::hex_getter() );
	unsigned short us = cpp_util_3::lexcast< unsigned short >( hex16,
		cpp_util_3::lexcasts::def_putter(),
		cpp_util_3::lexcasts::hex_getter() );
	int i = cpp_util_3::lexcast< int >( hex16,
		cpp_util_3::lexcasts::def_putter(),
		cpp_util_3::lexcasts::hex_getter() );
	unsigned int ui = cpp_util_3::lexcast< unsigned int >( hex16,
		cpp_util_3::lexcasts::def_putter(),
		cpp_util_3::lexcasts::hex_getter() );

	std::cout << "\n\thex16: " << hex16
		<< "\n\tshort: " << s
		<< "\n\tunsigned short: " << us
		<< "\n\tint: " << i
		<< "\n\tunsigned int: " << ui
		<< std::endl;

	std::string	hex32( "ffffff5d" );

	int i32 = cpp_util_3::lexcast< int >( hex32,
		cpp_util_3::lexcasts::def_putter(),
		cpp_util_3::lexcasts::hex_getter() );
	unsigned int ui32 = cpp_util_3::lexcast< unsigned int >( hex32,
		cpp_util_3::lexcasts::def_putter(),
		cpp_util_3::lexcasts::hex_getter() );
	long l = cpp_util_3::lexcast< long >( hex32,
		cpp_util_3::lexcasts::def_putter(),
		cpp_util_3::lexcasts::hex_getter() );
	unsigned long ul = cpp_util_3::lexcast< unsigned int >( hex32,
		cpp_util_3::lexcasts::def_putter(),
		cpp_util_3::lexcasts::hex_getter() );

	std::cout << "\n\thex32: " << hex32
		<< " (int=" << sizeof(int)*CHAR_BIT << "bits, long="
			<< sizeof(long)*CHAR_BIT << "bits)"
		<< "\n\tint: " << i32
		<< "\n\tunsigned int: " << ui32
		<< "\n\tlong: " << l
		<< "\n\tunsigned long: " << ul
		<< std::endl;
}

// ѕреобразование значений контейнера с
// использованием cpp_util_3::slexcast().
void
container_putter_demo()
{
	std::cout << "*** container_putter_demo:" << std::endl;

	// ѕечать всех значений из массива.
	unsigned int ui[ 8 ] = { 18, 17, 16, 15, 14, 13, 12, 10 };
	std::cout << cpp_util_3::slexcast(
			cpp_util_3::lexcasts::all(
				ui, ui + ( sizeof(ui) / sizeof(ui[0]) ) ) )
		<< std::endl;
	// “о же самое, но в шестнадцатиричном виде.
	std::cout << cpp_util_3::slexcast(
			cpp_util_3::lexcasts::all(
				ui, ui + ( sizeof(ui) / sizeof(ui[0]) ), " ",
				cpp_util_3::lexcasts::hex() ) )
		<< std::endl;

	// ѕечать всех значений вектора строк, раздел€€ каждое значение
	// переводом строки.
	std::set< std::string >	ss;
	ss.insert( "AAA" );
	ss.insert( "CCC" );
	ss.insert( "BBB" );
	ss.insert( "EEE" );
	ss.insert( "DDD" );
#if !defined( __BORLANDC__ )
	std::cout << cpp_util_3::slexcast(
			cpp_util_3::lexcasts::all( ss.begin(), ss.end(), "\n" ) )
		<< std::endl;
#endif

	// ≈ще раз, но проще.
	std::cout << cpp_util_3::slexcast(
			cpp_util_3::lexcasts::all( ss, "\n" ) )
		<< std::endl;

	// ќтображаем каждый символ строки в шестнадцатиричном виде.
	std::string hello( "Hello, World" );
	std::cout << "ASCII string: " << hello
		<< "\nHex string: " << cpp_util_3::slexcast(
			cpp_util_3::lexcasts::all( hello.begin(), hello.end(), "",
				cpp_util_3::lexcasts::hex_bslashx() ) )
		// ѕечатаем тоже самое, но проще.
		<< "\nHex string 2: "<< cpp_util_3::slexcast(
			cpp_util_3::lexcasts::all( hello, "",
				cpp_util_3::lexcasts::hex_bslashx() ) )
		<< std::endl;
}

int
main()
{
	slexcast_demo();

	hex_putter_demo();

	hex_getter_demo();

	container_putter_demo();

	return 0;
}
