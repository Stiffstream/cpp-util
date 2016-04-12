/*
	Пример порождения исключения с использованием
	cpp_util_2::lexcast().
*/

#include <map>
#include <string>
#include <iostream>
#include <stdexcept>

#include <cpp_util_2/h/lexcast.hpp>

// Класс словаря, в котором оператор [] порождает
// исключение, если элемент не найден по ключу.
template< class Key, class Value, class Pred = std::less< Key > >
class	hard_map_t : public std::map< Key, Value, Pred >
{
	typedef std::map< Key, Value, Pred > base_type_t;
	public :
		hard_map_t()
		{}
		hard_map_t( const hard_map_t & o )
		:
			base_type_t( o )
		{}

		hard_map_t &
		operator=( const hard_map_t & o )
		{
			base_type_t::operator=( o );
			return *this;
		}

		Value &
		operator[]( const Key & k )
		{
			typename base_type_t::iterator it = this->find( k );
			if( it == this->end() )
				throw std::invalid_argument(
					std::string( "Key not found: " ) +
					cpp_util_2::lexcast< std::string >( k ) );
			return it->second;
		}
};

// Проверяем работу карты с целыми ключами.
void
check_int()
{
	hard_map_t< int, int > m;
	m.insert( hard_map_t< int, int >::value_type( 0, 0 ) );
	m.insert( hard_map_t< int, int >::value_type( -1, -1 ) );
	m.insert( hard_map_t< int, int >::value_type( 1, 1 ) );

	try
	{
		std::cout << "search key: 0 => " << std::flush
			<< m[ 0 ] << std::endl;
		std::cout << "search key: -1 => " << std::flush
			<< m[ -1 ] << std::endl;
		std::cout << "search key: 2 => " << std::flush
			<< m[ 2 ] << std::endl;
	}
	catch( const std::exception & x )
	{
		std::cout << x.what() << std::endl;
	}
}

// Проверяем работу карты со строковыми ключами.
void
check_string()
{
	hard_map_t< std::string, int > m;
	m.insert( hard_map_t< std::string, int >::value_type( "A", 0 ) );
	m.insert( hard_map_t< std::string, int >::value_type( "B", -1 ) );
	m.insert( hard_map_t< std::string, int >::value_type( "C", 1 ) );

	try
	{
		std::cout << "search key: A => " << std::flush
			<< m[ "A" ] << std::endl;
		std::cout << "search key: B => " << std::flush
			<< m[ "B" ] << std::endl;
		std::cout << "search key: D => " << std::flush
			<< m[ "D" ] << std::endl;
	}
	catch( const std::exception & x )
	{
		std::cout << x.what() << std::endl;
	}
}

int
main()
{
	check_int();
	check_string();

	return 0;
}
