/*!
	\since
	v.2.0.2

	\file
	\brief Функция для конвертации значений из одного типа в
		другой с использованием промежуточного текстового представления.
*/

#pragma once

#include <sstream>

namespace	cpp_util_3
{

/*!
	\since
	v.2.0.2

	\brief A very simple alternative of boost::lexical_cast.

	Usage example:
\code
const std::string &
my_string_vector_t::operator[]( unsigned int index ) const
{
	if( index >= size() )
		throw std::out_of_range(
			std::string( "index is too big: " ) +
			cpp_util_3::lexcast< std::string >( index ) );
	...
}
\endcode
	Or more simple way:
\code
const std::string &
my_string_vector_t::operator[]( unsigned int index ) const
{
	if( index >= size() )
		throw std::out_of_range(
			std::string( "index is too big: " ) +
			cpp_util_3::slexcast( index ) );
	...
}
\endcode

	\note Allows to convert numbers to strings. And other way: strings
	to numbers.

	\par Exceptions
	Function lexcast() do not throw any exception by itselt.
	It also do not control the success of value transformations.
	But these transformation can raise some exceptions: lexcast() do
	not catch them.

	\par Requirements for type From.
	There should be operator<<() for std::ostream.

	\par Requirements for type To.
	There should be operator>>() for std::istream.
	Type \c To must be DefaultConstructible.

	\sa cpp_util_3::slexcast()
*/
template< class To, class From >
To
lexcast(
	//! Value to transform.
	const From & f )
{
	std::stringstream	ss;
	ss << f;
	To t;
	ss.seekg( 0 );
	ss >> t;

	return t;
}

/*!
	\since
	v.2.1.0

	The same as lexcast() but uses \a putter for storing \a f
	into temporary ostream.

	Type \a Putter must have operator() with the following format:
\code
void
operator( std::ostream & to, const From & what ) const;
\endcode
*/
template< class To, class From, class Putter >
To
lexcast(
	//! What to transform.
	const From & f,
	//! How to transform.
	const Putter & putter )
{
	std::stringstream	ss;
	putter( ss, f );
	To t;
	ss.seekg( 0 );
	ss >> t;

	return t;
}

/*!
	\since v.2.1.0
	\brief Функция для конвертации значений из одного типа в
		другой с использованием промежуточного текстового представления
		и специальноых способов преобразования значения.

	Данный вариант lexcast использует объект-преобразователь, который
	осуществляет преобразование значения в std::ostream и
	объект-преобразователь, который считывает значение из
	std::istream.

	Если требуется только специальный объект-getter, то в качестве
	объекта-putter можно указать объект cpp_util_3::lexcasts::def_putter:
\code
// Извлекаем число из строкового шестнадцатиричного представления.
int i = cpp_util_3::lexcast< int >( "ffab",
	cpp_util_3::lexcasts::def_putter(),
	cpp_util_3::lexcasts::hex_getter() );
\endcode

	\par Требования к типу Putter
	Тип Putter должен иметь метод operator() следующего формата:
\code
void
operator( std::ostream & to, const From & what ) const;
\endcode

	\par Требования к типу Getter
	Тип Getter должен иметь метод operator() следующего формата:
\code
void
operator( std::istream & to, To & what ) const;
\endcode
*/
template< class To, class From, class Putter, class Getter >
To
lexcast(
	//! Что преобразуется.
	const From & f,
	//! Как преобразуется в std::ostream.
	const Putter & putter,
	//! Как преобразуется из std::istream.
	const Getter & getter )
{
	std::stringstream	ss;
	putter( ss, f );
	To t;
	ss.seekg( 0 );
	getter( ss, t );

	return t;
}

/*!
	\since v.2.1.0

	Вариант функции lexcast() для преобразования в строку.

	С помощью cpp_util_3::lexcast() можно попытаться преобразовать
	любой объект в строку, если у этого объекта определен оператор
	сдвига в std::ostream. Например:
\code
class	A
{
	int	m_a;
	float	m_b;
	public :
		std::ostream &
		dump_to( std::ostream & to ) const
		{
			return ( to << "m_a: " << a << ", m_b: " << m_b );
		}
};
inline std::ostream &
operator<<( std::ostream & to, const A & a )
{
	return a.dump_to( to );
}

void f()
{
	A a;
	std::string str_a( cpp_util_3::lexcast< std::string >( a ) );
}
\endcode

	Но проблема в том, что в str_a будет содержаться только "m_a:",
	т.к. оператор >> для std::string извлекает значения из промежуточного
	std::stringstream в cpp_util_3::lexcast() только до первого пробела.

	Функция slexcast() решает эту проблему и позволяет поместить
	в str_a все содержимое промежуточного std::stringstream. В приведенном
	примере функцию slexcast()  можно использовать так:
\code
void f()
{
	A a;
	std::string str_a( cpp_util_3::slexcast( a ) );
}
\endcode
*/
template< class From >
std::string
slexcast(
	//! Что преобразуется.
	const From & f )
{
	std::stringstream	ss;
	ss << f;

	return ss.str();
}

/*!
	\since v.2.1.0

	Вариант функции slexcast() с использованием объекта-преобразователя
	значения в строку.

	\par Требования к типу Putter
	Тип Putter должен иметь метод operator() следующего формата:
\code
void
operator( std::ostream & to, const From & what ) const;
\endcode
*/
template< class From, class Putter >
std::string
slexcast(
	//! Что преобразуется.
	const From & f,
	//! Как преобразуется.
	const Putter & putter )
{
	std::stringstream	ss;
	putter( ss, f );

	return ss.str();
}

} /* namespace cpp_util_3 */

