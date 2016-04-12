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
	\since v.2.0.2
	\file
	\brief Функция для конвертации значений из одного типа в
		другой с использованием промежуточного текстового представления.
*/

#pragma once

#include <sstream>

namespace	cpp_util_2
{

/*!
	\since v.2.0.2
	\brief Функция для конвертации значений из одного типа в
		другой с использованием промежуточного текстового представления.

	В ряде случаев возникает задача преобразования некоторого значения
	в его текстовое представление. Например, при порождении исключений:
\code
// Способ 1. Использование sprintf.
const std::string &
my_string_vector_t::operator[]( unsigned int index ) const
{
	if( index >= size() )
	{
		// Преобразуем index в строку, чтобы можно
		// было сформировать подробное описание ошибки.
		char tmp[ 32 ];
		sprintf( tmp, "%u", index );
		throw std::out_of_range(
			std::string( "index is too big" ) + tmp );
	}
	...
}
// Способ 2. Использование std::ostringstream.
const std::string &
my_string_vector_t::operator[]( unsigned int index ) const
{
	if( index >= size() )
	{
		// Преобразуем index в строку, чтобы можно
		// было сформировать подробное описание ошибки.
		std::ostringstream tmp;
		tmp << index;
		throw std::out_of_range(
			std::string( "index is too big" ) + tmp.str() );
	}
	...
}
\endcode

	Оба этих способа усложняют код не нужными подробностями
	преобразования одного значения в строковое представление.
	И, хотя способ с sprintf более эффективен, он более сложен в
	сопровождении, т.к. формат sprintf жестко связан с типом
	параметра index. Если со временем index поменяет тип (на unsigned long
	для очень больших массивов или на std::string для ассоциативных
	массивов), то придется помнить про особенность форматной
	строки sprintf. В случае с std::ostringstream такой проблемы нет.

	Функция lexcast() упрощает подобные преобразования, сохраняя
	все достоинства и недостатки способа с применением std::ostringstream.
	В приведенном примере функция lexcast() может быть использована
	следующим образом:
\code
// Способ 3. Использование cpp_util_2::lexcast.
const std::string &
my_string_vector_t::operator[]( unsigned int index ) const
{
	if( index >= size() )
		throw std::out_of_range(
			std::string( "index is too big" ) +
			cpp_util_2::lexcast< std::string >( index ) );
	...
}
\endcode
	или, что еще проще:
\code
// Способ 4. Использование cpp_util_2::slexcast.
const std::string &
my_string_vector_t::operator[]( unsigned int index ) const
{
	if( index >= size() )
		throw std::out_of_range(
			std::string( "index is too big" ) +
			cpp_util_2::slexcast( index ) );
	...
}
\endcode

	То, что для преобразования значений используется промежуточное
	текстовое представление позволяет не только преобразовывать
	числовые значения в строку, но и преобразовывать строку в
	числовое значение.

	\par Порождение исключений.
	Сама функция lexcast() исключений не порождает и не контролирует
	успешность выполнения преобразований. Но lexcast не перехватывает
	никаких исключений, которые могут быть порождены операторами
	сдвига.

	\par Требование к типу \c From.
	Для типа \c From должен быть определен оператор сдвига
	в std::ostream.

	\par Требование к типу \c To.
	Для типа \с To должен быть определен оператор сдвига из
	std::istream.

	\return Значение, полученное преобразованием \a f в текстовое
	представление, а затем считанное из текстового представления.
	Результат не определен, если текстовое представление \a f
	не может быть корректно приведено к типу \c To.

	\sa cpp_util_2::slexcast()
*/
template< class To, class From >
To
lexcast(
	//! Что преобразуется.
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
	\since v.2.1.0
	\brief Функция для конвертации значений из одного типа в
		другой с использованием промежуточного текстового представления
		и специального способа преобразования значения.

	Данный вариант lexcast использует объект-преобразователь, который
	осуществляет преобразование значения в std::stringstream.

	\par Требования к типу Putter
	Тип Putter должен иметь метод operator() следующего формата:
\code
void
operator( std::ostream & to, const From & what ) const;
\endcode
*/
template< class To, class From, class Putter >
To
lexcast(
	//! Что преобразуется.
	const From & f,
	//! Как преобразуется.
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
	объекта-putter можно указать объект cpp_util_2::lexcasts::def_putter:
\code
// Извлекаем число из строкового шестнадцатиричного представления.
int i = cpp_util_2::lexcast< int >( "ffab",
	cpp_util_2::lexcasts::def_putter(),
	cpp_util_2::lexcasts::hex_getter() );
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

	С помощью cpp_util_2::lexcast() можно попытаться преобразовать
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
	std::string str_a( cpp_util_2::lexcast< std::string >( a ) );
}
\endcode

	Но проблема в том, что в str_a будет содержаться только "m_a:",
	т.к. оператор >> для std::string извлекает значения из промежуточного
	std::stringstream в cpp_util_2::lexcast() только до первого пробела.

	Функция slexcast() решает эту проблему и позволяет поместить
	в str_a все содержимое промежуточного std::stringstream. В приведенном
	примере функцию slexcast()  можно использовать так:
\code
void f()
{
	A a;
	std::string str_a( cpp_util_2::slexcast( a ) );
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

} /* namespace cpp_util_2 */

