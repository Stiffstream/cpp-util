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
	\file cpp_util_2/h/nocopy.hpp
	\brief ����� cpp_util_2::nocopy_t
*/

#pragma once

namespace cpp_util_2
{

//
// nocopy_t
//

//! ������� �����, ����������� ����������� ��������.
/*!
	�����, ������� ���������� ����� �������� ����������� �
	�������� �����������. ��������� ����� ����������� ��
	nocopy_t ������ ��� �� ����� �������� ����������� �
	�������� �����������.

	������ �������������:

	\code
	class	my_smart_ptr_t : private cpp_util_2::nocopy_t
	{
		private :
			// ��-�� ����� ��������� ������� my_smart_ptr_t
			// �� ����� ������������.
			void *	m_ptr;
		public :
			my_smart_ptr_t();
			~my_smart_ptr_t();
			...
	};
	\endcode

	��������� ��������� ������������ ������ �������������
	my_smart_ptr_t * � cpp_util_2::nocopy_t.
*/
class	nocopy_t
{
	protected :
		nocopy_t() {}
		~nocopy_t() {}

	private :
		nocopy_t( const nocopy_t & );
		nocopy_t &
		operator=( const nocopy_t & );
};

} /*cpp_util_2 */

