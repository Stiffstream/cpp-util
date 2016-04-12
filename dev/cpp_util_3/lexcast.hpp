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
	\brief ������� ��� ����������� �������� �� ������ ���� �
		������ � �������������� �������������� ���������� �������������.
*/

#pragma once

#include <sstream>

namespace	cpp_util_2
{

/*!
	\since v.2.0.2
	\brief ������� ��� ����������� �������� �� ������ ���� �
		������ � �������������� �������������� ���������� �������������.

	� ���� ������� ��������� ������ �������������� ���������� ��������
	� ��� ��������� �������������. ��������, ��� ���������� ����������:
\code
// ������ 1. ������������� sprintf.
const std::string &
my_string_vector_t::operator[]( unsigned int index ) const
{
	if( index >= size() )
	{
		// ����������� index � ������, ����� �����
		// ���� ������������ ��������� �������� ������.
		char tmp[ 32 ];
		sprintf( tmp, "%u", index );
		throw std::out_of_range(
			std::string( "index is too big" ) + tmp );
	}
	...
}
// ������ 2. ������������� std::ostringstream.
const std::string &
my_string_vector_t::operator[]( unsigned int index ) const
{
	if( index >= size() )
	{
		// ����������� index � ������, ����� �����
		// ���� ������������ ��������� �������� ������.
		std::ostringstream tmp;
		tmp << index;
		throw std::out_of_range(
			std::string( "index is too big" ) + tmp.str() );
	}
	...
}
\endcode

	��� ���� ������� ��������� ��� �� ������� �������������
	�������������� ������ �������� � ��������� �������������.
	�, ���� ������ � sprintf ����� ����������, �� ����� ������ �
	�������������, �.�. ������ sprintf ������ ������ � �����
	��������� index. ���� �� �������� index �������� ��� (�� unsigned long
	��� ����� ������� �������� ��� �� std::string ��� �������������
	��������), �� �������� ������� ��� ����������� ���������
	������ sprintf. � ������ � std::ostringstream ����� �������� ���.

	������� lexcast() �������� �������� ��������������, ��������
	��� ����������� � ���������� ������� � ����������� std::ostringstream.
	� ����������� ������� ������� lexcast() ����� ���� ������������
	��������� �������:
\code
// ������ 3. ������������� cpp_util_2::lexcast.
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
	���, ��� ��� �����:
\code
// ������ 4. ������������� cpp_util_2::slexcast.
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

	��, ��� ��� �������������� �������� ������������ �������������
	��������� ������������� ��������� �� ������ ���������������
	�������� �������� � ������, �� � ��������������� ������ �
	�������� ��������.

	\par ���������� ����������.
	���� ������� lexcast() ���������� �� ��������� � �� ������������
	���������� ���������� ��������������. �� lexcast �� �������������
	������� ����������, ������� ����� ���� ��������� �����������
	������.

	\par ���������� � ���� \c From.
	��� ���� \c From ������ ���� ��������� �������� ������
	� std::ostream.

	\par ���������� � ���� \c To.
	��� ���� \� To ������ ���� ��������� �������� ������ ��
	std::istream.

	\return ��������, ���������� ��������������� \a f � ���������
	�������������, � ����� ��������� �� ���������� �������������.
	��������� �� ���������, ���� ��������� ������������� \a f
	�� ����� ���� ��������� ��������� � ���� \c To.

	\sa cpp_util_2::slexcast()
*/
template< class To, class From >
To
lexcast(
	//! ��� �������������.
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
	\brief ������� ��� ����������� �������� �� ������ ���� �
		������ � �������������� �������������� ���������� �������������
		� ������������ ������� �������������� ��������.

	������ ������� lexcast ���������� ������-���������������, �������
	������������ �������������� �������� � std::stringstream.

	\par ���������� � ���� Putter
	��� Putter ������ ����� ����� operator() ���������� �������:
\code
void
operator( std::ostream & to, const From & what ) const;
\endcode
*/
template< class To, class From, class Putter >
To
lexcast(
	//! ��� �������������.
	const From & f,
	//! ��� �������������.
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
	\brief ������� ��� ����������� �������� �� ������ ���� �
		������ � �������������� �������������� ���������� �������������
		� ������������ �������� �������������� ��������.

	������ ������� lexcast ���������� ������-���������������, �������
	������������ �������������� �������� � std::ostream �
	������-���������������, ������� ��������� �������� ��
	std::istream.

	���� ��������� ������ ����������� ������-getter, �� � ��������
	�������-putter ����� ������� ������ cpp_util_2::lexcasts::def_putter:
\code
// ��������� ����� �� ���������� ������������������ �������������.
int i = cpp_util_2::lexcast< int >( "ffab",
	cpp_util_2::lexcasts::def_putter(),
	cpp_util_2::lexcasts::hex_getter() );
\endcode

	\par ���������� � ���� Putter
	��� Putter ������ ����� ����� operator() ���������� �������:
\code
void
operator( std::ostream & to, const From & what ) const;
\endcode

	\par ���������� � ���� Getter
	��� Getter ������ ����� ����� operator() ���������� �������:
\code
void
operator( std::istream & to, To & what ) const;
\endcode
*/
template< class To, class From, class Putter, class Getter >
To
lexcast(
	//! ��� �������������.
	const From & f,
	//! ��� ������������� � std::ostream.
	const Putter & putter,
	//! ��� ������������� �� std::istream.
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

	������� ������� lexcast() ��� �������������� � ������.

	� ������� cpp_util_2::lexcast() ����� ���������� �������������
	����� ������ � ������, ���� � ����� ������� ��������� ��������
	������ � std::ostream. ��������:
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

	�� �������� � ���, ��� � str_a ����� ����������� ������ "m_a:",
	�.�. �������� >> ��� std::string ��������� �������� �� ��������������
	std::stringstream � cpp_util_2::lexcast() ������ �� ������� �������.

	������� slexcast() ������ ��� �������� � ��������� ���������
	� str_a ��� ���������� �������������� std::stringstream. � �����������
	������� ������� slexcast()  ����� ������������ ���:
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
	//! ��� �������������.
	const From & f )
{
	std::stringstream	ss;
	ss << f;

	return ss.str();
}

/*!
	\since v.2.1.0

	������� ������� slexcast() � �������������� �������-���������������
	�������� � ������.

	\par ���������� � ���� Putter
	��� Putter ������ ����� ����� operator() ���������� �������:
\code
void
operator( std::ostream & to, const From & what ) const;
\endcode
*/
template< class From, class Putter >
std::string
slexcast(
	//! ��� �������������.
	const From & f,
	//! ��� �������������.
	const Putter & putter )
{
	std::stringstream	ss;
	putter( ss, f );

	return ss.str();
}

} /* namespace cpp_util_2 */

