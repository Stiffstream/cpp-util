/*

Yauheni A. Akhotnikau (C) 1997-2003
e-mail: eao197@yahoo.com

Permission is granted to anyone to use this software for any purpose on any
computer system, and to redistribute it freely, subject to the following
restrictions:

1. This software is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.

2. The origin of this software must not be misrepresented, either by
   explicit claim or by omission.

3. Altered versions must be plainly marked as such, and must not be
   misrepresented as being the original software.

*/

/*!
	\since v.2.0.3
	\file
	\brief Вспомогательные объекты для преобразования и извлечения
		значений.
*/

#pragma once

#include <cpp_util_3/lexcast.hpp>

namespace	cpp_util_3
{

namespace	lexcasts
{

namespace impl
{
	//! Вспомогательная функция для сдвига значений в std::ostream.
	template< class T >
	inline void
	ostream_lshift( std::ostream & o, const T & v )
	{
		o << v;
	}

	//! \name Специальные случаи ostream_lshift для типа char.
	//! \{
	template<>
	inline void
	ostream_lshift( std::ostream & to, const char & v )
	{
		ostream_lshift( to, static_cast< unsigned short >(
			static_cast< unsigned char >( v ) ) );
	}

	template<>
	inline void
	ostream_lshift( std::ostream & to, const signed char & v )
	{
		ostream_lshift( to, static_cast< unsigned short >(
			static_cast< unsigned char >( v ) ) );
	}

	template<>
	inline void
	ostream_lshift( std::ostream & to, const unsigned char & v )
	{
		ostream_lshift( to, static_cast< unsigned short >( v ) );
	}
	//! \}

	//! Вспомогательная функция для сдвига значений из std::istream.
	template< class T >
	inline void
	istream_rshift( std::istream & o, T & v )
	{
		o >> v;
	}

	//! \name Специальные случаи istream_rshift для типа char.
	//! \{
	template<>
	inline void
	istream_rshift( std::istream & from, char & v )
	{
		unsigned short s;
		istream_rshift( from, s );
		v = static_cast< char >( s );
	}

	template<>
	inline void
	istream_rshift( std::istream & from, signed char & v )
	{
		unsigned short s;
		istream_rshift( from, s );
		v = static_cast< signed char >( s );
	}

	template<>
	inline void
	istream_rshift( std::istream & from, unsigned char & v )
	{
		unsigned short s;
		istream_rshift( from, s );
		v = static_cast< unsigned char >( s );
	}

	template<>
	inline void
	istream_rshift( std::istream & from, short & v )
	{
		unsigned short s;
		istream_rshift( from, s );
		v = static_cast< short >( s );
	}

	template<>
	inline void
	istream_rshift( std::istream & from, int & v )
	{
		unsigned int s;
		istream_rshift( from, s );
		v = static_cast< int >( s );
	}

	template<>
	inline void
	istream_rshift( std::istream & from, long & v )
	{
		unsigned long s;
		istream_rshift( from, s );
		v = static_cast< long >( s );
	}
	//! \}
}

//
// def_putter
//

//! Преобразователь значения, который использует стандартный
//! оператор сдвига, определенный для данного типа.
struct	def_putter
{
	template< class T >
	void
	operator()( std::ostream & o, const T & v ) const
	{
		o << v;
	}
};

//
// hex
//

//! Преобразование целочисленного значения в шестнадцатиричное
//! представление.
/*!
	\since v.2.0.3

	Для того, чтобы получить в строке шестнадцатиричное представление
	числа можно воспользоваться классом hex_t в качестве
	объекта-значения для cpp_util_3::lexcast():
\code
unsigned int ui = 2378;
std::string str_hex_ui(
	cpp_util_3::slexcast( ui, cpp_util_3::lexcasts::hex() ) );
\endcode

*/
struct hex
{
	template< class T >
	void
	operator()( std::ostream & to, const T & v ) const
	{
		std::ios::fmtflags old = to.setf(
			std::ios::hex,
			std::ios::basefield );
		impl::ostream_lshift( to, v );
		to.setf( old );
	}
};

//
// prefixed_hex
//

//! Преобразование целочисленного значения в шестнадцатиричное
//! представление с добавлением указанного префикса.
class prefixed_hex
{
	private :
		//! Префикс значения.
		std::string	m_prefix;

	public :
		//! Основной конструктор.
		prefixed_hex( const std::string & prefix )
		:	m_prefix( prefix )
		{}
		//! Конструктор копирования.
		prefixed_hex( const prefixed_hex & o )
		:	m_prefix( o.m_prefix )
		{}

		//! Оператор копирования.
		prefixed_hex &
		operator=( const prefixed_hex & o )
		{
			m_prefix = o.m_prefix;
			return *this;
		}

		template< class T >
		void
		operator()( std::ostream & to, const T & v ) const
		{
			to << m_prefix;
			std::ios::fmtflags old = to.setf(
				std::ios::hex,
				std::ios::basefield );
			impl::ostream_lshift( to, v );
			to.setf( old );
		}
};

//
// hex_0x
//

//! Преобразование целочисленного значения в шестнадцатиричное
//! представление с добавлением стандартного для C/C++ префикса 0x.
/*!
	\since v.2.1.0

	Для того, чтобы получить в строке шестнадцатиричное представление
	числа, которое начинается со стандартного C/C++ префикса 0x,
	можно воспользоваться классом hex_0x в качестве
	объекта-значения для cpp_util_3::lexcast():
\code
unsigned int ui = 2378;
std::string str_hex_ui( cpp_util_3::slexcast( ui,
	cpp_util_3::lexcasts::hex_0x() ) );
\endcode
*/
class	hex_0x
:	public prefixed_hex
{
	public :
		hex_0x()
		:	prefixed_hex( "0x" )
		{}
};

//
// hex_bslashx
//

//! Преобразование целочисленного значения в шестнадцатиричное
//! представление с добавлением стандартного для C/C++ префикса \\x.
/*!
	\since v.2.1.0

	Для того, чтобы получить в строке шестнадцатиричное представление
	числа, которое начинается со стандартного C/C++ префикса \\x,
	можно воспользоваться классом hex_bslashx_t в качестве
	объекта-значения для cpp_util_3::lexcast():
\code
unsigned int ui = 2378;
std::string str_hex_ui( cpp_util_3::slexcast( ui,
	cpp_util_3::lexcasts::hex_bslashx() ) );
\endcode

*/
class	hex_bslashx
:	public prefixed_hex
{
	public :
		hex_bslashx()
		:	prefixed_hex( "\\x" )
		{}
};

//
// hex_getter
//

//! Преобразование шестнадцатиричное представления числа в число.
/*!
	\since v.2.0.3

	Для того, чтобы извлечь из строкого шестнадцатиричное представление
	числа значение можно воспользоваться классом hex_getter в качестве
	объекта-извлекателя для cpp_util_3::lexcast():
\code
unsigned int ui = cpp_util_3::lexcast< unsigned int >(
	std::string( "ff5d" ),
	cpp_util_3::lexcasts::def_putter(),
	cpp_util_3::lexcasts::hex_getter() );
\endcode

*/
struct hex_getter
{
	template< class T >
	void
	operator()( std::istream & to, T & v ) const
	{
		std::ios::fmtflags old = to.setf(
			std::ios::hex,
			std::ios::basefield );
		impl::istream_rshift( to, v );
		to.setf( old );
	}
};

//
// all_t
//

//! Вспомогательная структура для преобразования значений
//! на которые указывают итераторы.
/*!
	\since v.2.0.3
	\sa	cpp_util_3::lexcasts::all().
*/
template< class It >
struct	all_t
{
	//! Итератор на начало.
	It m_b;
	//! Итератор на конец.
	It m_e;
	//! Разделитель между значениями.
	const std::string & m_sep;

	//! Инициализирующий конструктор.
	all_t( It b, It e, const std::string & sep )
	:	m_b( b )
	,	m_e( e )
	,	m_sep( sep )
	{}
	//! Конструктор копирования.
	all_t( const all_t & o )
	:	m_b( o.m_b )
	,	m_e( o.m_e )
	,	m_sep( o.m_sep )
	{}
};

//! Преобразование значений.
/*!
	\note После последнего элемента разделитель не печатается.
*/
template< class It >
std::ostream &
operator<<( std::ostream & to, const all_t< It > & what )
{
	It b( what.m_b ), e( what.m_e );
	while( b != e )
	{
		to << *b;
		if( (++b) != e )
			to << what.m_sep;
	}
	return to;
}

//
// all
//

//! Выполнение преобразования всех значений между указанными
//! итераторами.
/*!
	\since v.2.0.3

	С помощью этой функции можно осуществлять преобразование,
	например, всех значений контейнера или массива (вспомогательный
	string_getter используется для того, чтобы прочитать из
	промежуточного буфера все значения вместе с пробелами):
\code
// Печать всех значений из массива.
unsigned int ui[ 64 ] = { ... };
std::cout << cpp_util_3::slexcast(
	cpp_util_3::lexcasts::all( ui, ui + ( sizeof(ui) / sizeof(ui[0]) ) ) );

// Печать всех значений вектора строк, разделяя каждое значение
// переводом строки.
std::set< std::string >	ss;
...
std::cout << cpp_util_3::slexcast(
	cpp_util_3::lexcasts::all( ss.begin(), ss.end(), "\n" ) );
\endcode

	\note После последнего элемента разделитель не печатается.
*/
template< class It >
all_t< It >
all( It b, It e, const std::string & sep = " " )
{
	return all_t< It >( b, e, sep );
}

//
// all_cont_t
//

//! Вспомогательная структура для преобразования значений
//! на которые указывают итераторы.
/*!
	\since v.2.0.3
	\sa	cpp_util_3::lexcasts::all().
*/
template< class Cont >
struct	all_cont_t
{
	//! Контейнер.
	const Cont &	m_c;
	//! Разделитель между значениями.
	const std::string & m_sep;

	//! Инициализирующий конструктор.
	all_cont_t( const Cont & c, const std::string & sep )
	:	m_c( c )
	,	m_sep( sep )
	{}
	//! Конструктор копирования.
	all_cont_t( const all_cont_t & o )
	:	m_c( o.m_c )
	,	m_sep( o.m_sep )
	{}
};

//! Преобразование значений.
/*!
	\note После последнего элемента разделитель не печатается.
*/
template< class Cont >
std::ostream &
operator<<( std::ostream & to, const all_cont_t< Cont > & what )
{
	typename Cont::const_iterator
		b( what.m_c.begin() ),
		e( what.m_c.end() );
	while( b != e )
	{
		to << *b;
		if( (++b) != e )
			to << what.m_sep;
	}
	return to;
}

//! Выполнение преобразования всех значений указанного контейнера.
/*!
	\since v.2.0.3

	С помощью этой функции можно осуществлять преобразование,
	например, всех значений контейнера, который обладает
	методами begin(), end(), возвращающими итераторы (вспомогательный
	string_getter используется для того, чтобы прочитать из
	промежуточного буфера все значения вместе с пробелами):
\code
// Печать всех значений вектора строк, разделяя каждое значение
// переводом строки.
std::set< std::string >	ss;
...
std::cout << cpp_util_3::slexcast(
	cpp_util_3::lexcasts::all( ss, "\n" ) );
\endcode

	\attention В типе \a Cont должен быть определен тип \b const_iterator.

	\note После последнего элемента разделитель не печатается.
*/
template< class Cont >
all_cont_t< Cont >
all( const Cont & c, const std::string & sep = " " )
{
	return all_cont_t< Cont >( c, sep );
}

//
// all_using_t
//

//! Вспомогательная структура для преобразования значений
//! на которые указывают итераторы.
/*!
	\since v.2.0.3
	\sa	cpp_util_3::lexcasts::all().
*/
template< class It, class Putter >
struct	all_using_t
{
	//! Итератор на начало.
	It m_b;
	//! Итератор на конец.
	It m_e;
	//! Разделитель между значениями.
	const std::string & m_sep;
	//! Преобразователь значений.
	Putter	m_putter;

	//! Инициализирующий конструктор.
	all_using_t( It b, It e, const std::string & sep, Putter putter )
	:	m_b( b )
	,	m_e( e )
	,	m_sep( sep )
	,	m_putter( putter )
	{}
	//! Конструктор копирования.
	all_using_t( const all_using_t & o )
	:	m_b( o.m_b )
	,	m_e( o.m_e )
	,	m_sep( o.m_sep )
	,	m_putter( o.m_putter )
	{}
};

//! Преобразование значений.
/*!
	\note После последнего элемента разделитель не печатается.
*/
template< class It, class Putter >
std::ostream &
operator<<( std::ostream & to,
	const all_using_t< It, Putter > & what )
{
	It b( what.m_b ), e( what.m_e );
	while( b != e )
	{
		what.m_putter( to, *b );
		if( (++b) != e )
			to << what.m_sep;
	}
	return to;
}

//
// all_using
//

//! Выполнение преобразования всех значений между указанными
//! итераторами с использованием указанного преобразователя.
/*!
	\since v.2.0.3

	С помощью этой функции можно осуществлять преобразование,
	например, всех значений контейнера или массива (вспомогательный
	string_getter используется для того, чтобы прочитать из
	промежуточного буфера все значения вместе с пробелами):
\code
// Печать всех значений из массива.
unsigned int ui[ 64 ] = { ... };
std::cout << cpp_util_3::slexcast(
	cpp_util_3::lexcasts::all( ui, ui + ( sizeof(ui) / sizeof(ui[0]) ),
		" ", cpp_util_3::lexcasts::hex_0x() ) );
\endcode

	\note После последнего элемента разделитель не печатается.
*/
template< class It, class Putter >
all_using_t< It, Putter >
all( It b, It e, const std::string & sep, Putter putter )
{
	return all_using_t< It, Putter >( b, e, sep, putter );
}

//! Выполнение преобразования всех значений указанного контейнера
//! с использованием указанного преобразователя.
/*!
	\since v.2.0.3

	С помощью этой функции можно осуществлять преобразование,
	например, всех значений контейнера, который обладает
	методами begin(), end(), возвращающими итераторы:
\code
// Печать шестнадцатиричного представления каждого символа строки.
std::string hello( "Hello!" );
std::cout << cpp_util_3::slexcast(
	cpp_util_3::lexcasts::all( hello, "",
		cpp_util_3::lexcasts::hex_bslashx() ) );
\endcode

	\note После последнего элемента разделитель не печатается.
*/
#if defined( _MSC_VER ) && ( _MSC_VER < 1300 )

template< class Cont, class Putter >
all_using_t< Cont::const_iterator, Putter >
all( const Cont &c, const std::string & sep, Putter putter )
{
	return all_using_t< Cont::const_iterator, Putter >(
		c.begin(), c.end(), sep, putter );
}

#else

template< class Cont, class Putter >
all_using_t< typename Cont::const_iterator, Putter >
all( const Cont &c, const std::string & sep, Putter putter )
{
	return all_using_t< typename Cont::const_iterator, Putter >(
		c.begin(), c.end(), sep, putter );
}
#endif

} /* namespace lexcasts */

} /* namespace cpp_util_3 */

