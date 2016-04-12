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
	\file
	\brief Не привязанные к компилятору макросы.

	Основные макросы, которые могут использоваться в любых
	компиляторах.
*/

#pragma once

/*!
	\def CPP_UTIL_2_ASIZE(array)
	Возвращает размер массива \a array в элементах.
*/
#define CPP_UTIL_2_ASIZE(array) (sizeof(array)/sizeof(array[0]))

/*!
	\def CPP_UTIL_2_SIZEOFATTR( t, a )
	Возвращает размерность атрибута \a attr типа \a type
	в байтах.
*/
#define CPP_UTIL_2_SIZEOFATTR( t, a ) (sizeof(((t *)0)->a))

