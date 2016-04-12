#if defined( _MSC_VER )
	#if !defined( _CRT_SECURE_NO_WARNINGS )
		#define _CRT_SECURE_NO_WARNINGS
	#endif
#endif

#include <string>

#include <test/h/helpers.hpp>

#define CPP_UTIL_STRING_PIECE_STORE_DATA_TYPE
#include <cpp_util_2/h/string_piece.hpp>

void check_type(
	const cpp_util_2::string_piece_t & p,
	int expected_type )
	{
		CHECK_CONDITION( p.type() == expected_type );
	}

UNIT_TEST_MAIN(
	const char * s1 = "abc";
	const std::string s2 = "abc";

	check_type( "abc", cpp_util_2::string_piece_t::null_terminated );
	check_type( s1, cpp_util_2::string_piece_t::null_terminated );
	check_type( s2, cpp_util_2::string_piece_t::std_basic_string );

	cpp_util_2::string_piece_t sp1( "abc" );
	cpp_util_2::string_piece_t sp2( s1 );
	cpp_util_2::string_piece_t sp3( s2 );

	check_type( sp1, cpp_util_2::string_piece_t::null_terminated );
	check_type( sp2, cpp_util_2::string_piece_t::null_terminated );
	check_type( sp3, cpp_util_2::string_piece_t::std_basic_string );

	const unsigned char * us1 =
			reinterpret_cast< const unsigned char * >( "abc" );
	cpp_util_2::string_piece_t spu2( us1 );
	check_type( spu2, cpp_util_2::string_piece_t::null_terminated );

	cpp_util_2::string_piece_t sp4;
	check_type( sp4, cpp_util_2::string_piece_t::no_type );

	sp4.set( "abc" );
	check_type( sp4, cpp_util_2::string_piece_t::null_terminated );
	sp4.set( s1 );
	check_type( sp4, cpp_util_2::string_piece_t::null_terminated );
	sp4.set( s2 );
	check_type( sp4, cpp_util_2::string_piece_t::std_basic_string );
	sp4.set( s1, std::strlen( s1 ) );
	check_type( sp4, cpp_util_2::string_piece_t::array_fragment );
	sp4.clear();
	check_type( sp4, cpp_util_2::string_piece_t::no_type );
	sp4.set( us1 );
	check_type( sp4, cpp_util_2::string_piece_t::null_terminated );

	char a1[ 32 ];
	std::strcpy( a1, "test" );
	cpp_util_2::string_piece_t sp5( a1 );
	check_type( sp5, cpp_util_2::string_piece_t::null_terminated );
	CHECK_CONDITION( 4 == sp5.size() );
	std::strcpy( a1, "test-1" );
	sp5.set( a1 );
	check_type( sp5, cpp_util_2::string_piece_t::null_terminated );
	CHECK_CONDITION( 6 == sp5.size() );

	cpp_util_2::string_piece_t sp7(
			cpp_util_2::string_literal( "Just Another Test" ) );
	check_type( sp7, cpp_util_2::string_piece_t::array_fragment );
	CHECK_CONDITION( 17 == sp7.size() );
)

