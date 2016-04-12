/*
 * cpp_util_3
 */

/*!
 * \since v.2.3.1
 * \brief Обертка над голыми указателями на char и над std::string.
 */

#pragma once

#include <string>
#include <cstring>

namespace cpp_util_3 {

//
// string_piece_t
//

/*!
 * \since v.2.3.1
 * \brief Обертка над голыми указателями на char и над std::string.
 *
 * Идея нагло сперта из библиотеки PCRE (http://www.pcre.org). Там
 * этот класс используется для реалиазации C++ классов, методы которых
 * должны получать строковые аргументы. Класс string_piece_t позволяет
 * унифицировано работать как с const char *, так и с const std::string &
 * не требуя копирования значения аргумента.
 *
 * \par v.2.5.0
 *
 * При использовании версии 2.4.0 выяснилось, что не во всех случаях
 * длина строкового литерала будет такой, как это ожидается:
 * \code
 * char tmp[ 32 ];
 * std::strcpy( tmp, "test" );
 * f( tmp );
 *
 * void f( const cpp_util_3::string_piece_t name )
 * {
 * 	// Здесь name.size == 32 а не 4!
 * }
 * \endcode
 * Проблема была устранена за счет отказа от шаблонных конструкторов.
 *
 * \par Благодарности
 * <a href="http://www.rsdn.ru/Users/48023.aspx">night beast</a> за
 * обнаруженные ошибки в реализации шаблонных конструкторов.
 */
class string_piece_t
	{
#if defined( CPP_UTIL_STRING_PIECE_STORE_DATA_TYPE )
	public :
		static const int no_type = 0;
		static const int null_terminated = 2;
		static const int std_basic_string = 3;
		static const int array_fragment = 4;
	#define CPP_UTIL_STRING_PIECE_MAKE_DATA(p, l, t) {(p), (l), (t)}
#else
	#define CPP_UTIL_STRING_PIECE_MAKE_DATA(p, l, t) {(p), (l)}
#endif

	private:
		/*!
		 * \since v.2.4.0
		 * \brief Структура внутренностей объекта string_piece.
		 */
		struct data_t
			{
				const char * m_ptr;
				size_t m_length;
#if defined(CPP_UTIL_STRING_PIECE_STORE_DATA_TYPE)
				int m_type;
#endif
			};

		/*!
		 * \since v.2.4.0
		 * \brief Конструирование внутренностей string_piece из
		 * null-terminated строки.
		 */
		inline static data_t
		from_null_terminated( const char * p )
			{
				data_t r = CPP_UTIL_STRING_PIECE_MAKE_DATA(
						p,
						p ? std::strlen( p ) : 0,
						null_terminated );
				return r;
			}
		inline static data_t
		from_null_terminated( const unsigned char * p )
			{
				return from_null_terminated(
						reinterpret_cast< const char * >( p ) );
			}

		/*!
		 * \since v.2.4.0
		 * \brief Конструирование внутренностей string_piece из std::string.
		 */
		inline static data_t
		from_std_basic_string( const std::string & s )
			{
				data_t r = CPP_UTIL_STRING_PIECE_MAKE_DATA(
						s.data(),
						s.length(),
						std_basic_string );
				return r;
			}

		/*!
		 * \since v.2.4.0
		 * \brief Конструирование внутренностей string_piece из фрагмента
		 * вектора char-ов.
		 */
		inline static data_t
		from_array_fragment( const char * p, size_t len )
			{
				data_t r = CPP_UTIL_STRING_PIECE_MAKE_DATA(
						p,
						len,
						array_fragment );
				return r;
			}
		inline static data_t
		from_array_fragment( const unsigned char * p, size_t len )
			{
				return from_array_fragment(
						reinterpret_cast< const char * >( p ), len );
			}

		/*!
		 * \since v.2.4.0
		 * \brief Конструирование пустых внутренностей string_piece.
		 */
		inline static data_t
		empty_data()
			{
				data_t r = CPP_UTIL_STRING_PIECE_MAKE_DATA( 0, 0, no_type );
				return r;
			}

		/*!
		 * \since v.2.4.0
		 * \brief Внутренности объекта string_piece.
		 */
		data_t m_data;

	public:
		//! Конструктор по умолчанию.
		string_piece_t()
			:	m_data( empty_data() )
			{}
		//! Конструктор для случая std::string.
		string_piece_t( const std::string & str )
			:	m_data( from_std_basic_string( str ) )
			{}
		//! Констуктор для случая строкового буфера.
		string_piece_t( const char * ptr, size_t len )
			:	m_data( from_array_fragment( ptr, len ) )
			{}
		//! Констуктор для случая строкового буфера.
		string_piece_t( const unsigned char * ptr, size_t len )
			:	m_data( from_array_fragment( ptr, len ) )
			{}
		//! Конструктор для случая null-terminated строки.
		string_piece_t( const char * p )
			:	m_data( from_null_terminated( p ) )
			{}
		//! Конструктор для случая null-terminated строки.
		string_piece_t( const unsigned char * p )
			:	m_data( from_null_terminated( p ) )
			{}

		const char*
		data() const { return m_data.m_ptr; }

		size_t
		size() const { return m_data.m_length; }

		size_t
		length() const { return m_data.m_length; }

		bool
		empty() const { return m_data.m_length == 0; }

#if defined( CPP_UTIL_STRING_PIECE_STORE_DATA_TYPE )
		int
		type() const { return m_data.m_type; }
#endif

		void
		clear() { m_data = empty_data(); }

		void
		set( const char* buffer, size_t len )
			{
				m_data = from_array_fragment( buffer, len );
			}

		void
		set( const std::string & str )
			{
				m_data = from_std_basic_string( str );
			}

		void
		set( const char * p )
			{
				m_data = from_null_terminated( p );
			}

		void
		set( const unsigned char * p )
			{
				m_data = from_null_terminated( p );
			}

		char
		operator[](int i) const { return m_data.m_ptr[i]; }

		int
		compare( const string_piece_t& x ) const
			{
				int r = memcmp(
						m_data.m_ptr,
						x.m_data.m_ptr,
						m_data.m_length < x.m_data.m_length ?
								m_data.m_length : x.m_data.m_length );
				if( r == 0 )
					{
						if( m_data.m_length < x.m_data.m_length ) r = -1;
						else if( m_data.m_length > x.m_data.m_length ) r = +1;
					}
				return r;
			}

		bool
		operator==( const string_piece_t & x ) const
			{
				return ( ( m_data.m_length == x.m_data.m_length ) &&
						( memcmp(
								m_data.m_ptr,
								x.m_data.m_ptr,
								m_data.m_length ) == 0 ) );
			}
		bool
		operator!=( const string_piece_t & x ) const
			{
				return !(*this == x);
			}
		bool
		operator<( const string_piece_t & x ) const
			{
				return compare( x ) < 0;
			}
		bool
		operator<=( const string_piece_t & x ) const
			{
				return compare( x ) <= 0;
			}
		bool
		operator>( const string_piece_t & x ) const
			{
				return compare( x ) > 0;
			}
		bool
		operator>=( const string_piece_t & x ) const
			{
				return compare( x ) >= 0;
			}

		string_piece_t
		substr( size_t offset, size_t len )
			{
				return string_piece_t( m_data.m_ptr + offset, len );
			}

		std::string
		to_string() const
			{
				return std::string( data(), size() );
			}
	};

/*!
 * \since v.2.5.0
 * \brief Вспомогательная функция для оптимизации конструирования
 * string_piece из строковых литералов.
 *
 * Пример использования:
 *
 * \code
 * void some_function( const cpp_util_3::string_piece_t & a ) {...}
 * ...
 * some_function( cpp_util_3::string_literal( "Hello!" ) );
 * \endcode
 */
template< size_t N >
string_piece_t
string_literal( const char (&c)[ N ] )
	{
		return string_piece_t( c, N-1 );
	}

/*!
 * \since v.2.5.0
 * \brief Вспомогательная функция для оптимизации конструирования
 * string_piece из строковых литералов.
 *
 * Пример использования:
 *
 * \code
 * void some_function( const cpp_util_3::string_piece_t & a ) {...}
 * ...
 * some_function( cpp_util_3::string_literal( "Hello!" ) );
 * \endcode
 */
template< size_t N >
string_piece_t
string_literal( const unsigned char (&c)[ N ] )
	{
		return string_piece_t( c, N-1 );
	}

} /* namespace cpp_util_3 */

