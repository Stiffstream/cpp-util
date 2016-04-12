/*

Yauheni A. Akhotnikau (C) 1997-2013
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
	\file cpp_util_2/h/detect_compiler.hpp
	\brief Зависящие от компилятора макросы.

	Макросы, имена которых для всех компиляторов остаются
	одинаковыми, но раскрываются по разному.

	Основное назначение этих макросов -- унификация и скрытие
	от программиста различных особенностей и/или не стандартизированных
	расширений C++.
*/

#pragma once

/*!
	\def CPP_UTIL_2_EXPORT
	\brief Указание экспортируемости.

	Указывает, что класс/функция должна быть экспортируемой.
*/

/*!
	\def CPP_UTIL_2_IMPORT
	\brief Указание импортируемости.

	Указывает, что класс/функция должна быть импортируемой.
*/

/*!
	\def CPP_UTIL_2_EXTERNC_NAME(name)
	\brief Сформировать extern "C" имя.
	\deprecated Ранее использовалась для управления именами
	экспортируемых из DLL функций.
*/

/*!
	\def CPP_UTIL_2_EXTERNC_DECL(prefix, name, args)
	\brief Декларировать extern "C" функцию.
	\deprecated Ранее использовалась для управления именами
	экспортируемых из DLL функций.
*/

/*!
	\def CPP_UTIL_2_EXPORT_FUNC_SPEC(ret_type)
	\brief Декларация экспорта функции.

	В различных компиляторах ключевые слова для экспорта функции
	нужно указывать либо до, либо после указания типа возвращаемого
	значения.

	\par Visual C++:
	\verbatim
	__declspec(dllexport) void fn() {...}
	\endverbatim

	\par Watcom C++ & Borland C++:
	\verbatim
	void _export fn() {...}
	\endverbatim

	Макрос CPP_UTIL_2_EXPORT_FUNC_SPEC подставляет соответсвующее
	ключевое слово для экспорта функции либо перед, либо после
	типа возвращаемого значения.

	\par Пример использования:
	\verbatim
	CPP_UTIL_2_EXPORT_FUNC_SPEC(void) fn() {...}
	\endverbatim
*/

/*!
	\def CPP_UTIL_2_IMPORT_FUNC_SPEC(ret_type)
	\brief Декларация импорта функции.

	В различных компиляторах ключевые слова для импорта функции
	нужно указывать либо до, либо после указания типа возвращаемого
	значения, либо не указывать вовсе.

	\par Visual C++:
	\verbatim
	__declspec(dllimport) void fn() {...}
	\endverbatim

	\par Watcom C++ & Borland C++:
	\verbatim
	void _import fn() {...}
	\endverbatim

	Макрос CPP_UTIL_2_IMPORT_FUNC_SPEC подставляет соответсвующее
	ключевое слово для экспорта функции либо перед, либо после
	типа возвращаемого значения.

	\par Пример использования:
	\verbatim
	CPP_UTIL_2_IMPORT_FUNC_SPEC(void) fn() {...}
	\endverbatim
*/

/*!
	\def	CPP_UTIL_2_EXPORT_TYPE(type_qualifier)
	\brief Экспорт класса или структуры.

	Аналог CPP_UTIL_2_EXPORT_FUNC_SPEC для типов.

	\deprecated Использование этого макроса делает тип не
	видимым в визуальных средах программирования (Visual C++,
	Visual SlikEdit).
*/

/*!
	\def	CPP_UTIL_2_IMPORT_TYPE(type_qualifier)
	\brief Импорт класса или структуры.

	Аналог CPP_UTIL_2_IMPORT_FUNC_SPEC для типов.

	\deprecated Использование этого макроса делает тип не
	видимым в визуальных средах программирования (Visual C++,
	Visual SlikEdit).
*/

/*!
	\def CPP_UTIL_2_WIN32
	\brief Индикация платформы Win32.

	Символ CPP_UTIL_2_WIN32 определен, если осуществляется
	компиляция для платформы Win32.
*/

/*!
	\def CPP_UTIL_2_WIN64
	\brief Индикация платформы Win64.

	Символ CPP_UTIL_2_WIN64 определен, если осуществляется
	компиляция для платформы Win64.
*/

/*!
 * \def CPP_UTIL_2_WINDOWS
 * \brief Индикация платформы Windows.
 *
 * Является определенным, если определен CPP_UTIL_2_WIN32 или
 * CPP_UTIL_2_WIN64
 */

/*!
	\def CPP_UTIL_2_WIN32_DLL_ENTRY_POINT
	\brief Имя точки входа в DLL.

	Необязательная стартовая функция Win32-DLL в различных
	компиляторах имеет различные имена.

	\par Visual C++
	DllMain

	\par Borland C++
	DllEntryPoint

	\par Watcom C++
	LibMain

	Макрос \c CPP_UTIL_2_WIN32_DLL_ENTRY_POINT раскрывается
	в соответствии с особенностями конкретного компилятора.
*/

/*
	Delete compilers differences
*/
#if defined( _MSC_VER )
/*
** Visual C++
*/
#define CPP_UTIL_2_EXPORT __declspec(dllexport)
#define CPP_UTIL_2_IMPORT __declspec(dllimport)
#define CPP_UTIL_2_EXTERNC_NAME(name) _##name
#define CPP_UTIL_2_EXTERNC_DECL(prefix, name, args)\
extern "C" \
prefix CPP_UTIL_2_EXTERNC_NAME(name) args

#define CPP_UTIL_2_EXPORT_FUNC_SPEC(ret_type)\
CPP_UTIL_2_EXPORT ret_type

#define CPP_UTIL_2_IMPORT_FUNC_SPEC(ret_type)\
CPP_UTIL_2_IMPORT ret_type

#define CPP_UTIL_2_EXPORT_TYPE(type_qualifier)\
type_qualifier	CPP_UTIL_2_EXPORT

#define CPP_UTIL_2_IMPORT_TYPE(type_qualifier)\
type_qualifier	CPP_UTIL_2_IMPORT

#if defined( _WIN64 )
 # define CPP_UTIL_2_WIN64
#endif

#if defined( _WIN32 )

#define CPP_UTIL_2_WIN32

#define CPP_UTIL_2_WIN32_DLL_ENTRY_POINT DllMain

#endif /* defined _WIN32 */

#endif /* _MSC_VER */

#if defined( __MINGW32__ ) || defined( __WINGW64__ )
/*
** MinGW C++
*/
#define CPP_UTIL_2_EXPORT __declspec(dllexport)
#define CPP_UTIL_2_IMPORT __declspec(dllimport)

#define CPP_UTIL_2_EXPORT_FUNC_SPEC(ret_type)\
CPP_UTIL_2_EXPORT ret_type

#define CPP_UTIL_2_IMPORT_FUNC_SPEC(ret_type)\
CPP_UTIL_2_IMPORT ret_type

#define CPP_UTIL_2_EXPORT_TYPE(type_qualifier)\
type_qualifier	CPP_UTIL_2_EXPORT

#define CPP_UTIL_2_IMPORT_TYPE(type_qualifier)\
type_qualifier	CPP_UTIL_2_IMPORT

#if defined( __WIN64__ )

#define CPP_UTIL_2_WIN64

#endif

#if defined( __WIN32__ )

#define CPP_UTIL_2_WIN32

#define CPP_UTIL_2_WIN32_DLL_ENTRY_POINT DllMain

#endif /* defined __WIN32__ */

#endif /* __MINGW32__ */


#if defined( __WATCOMC__ )
/*
** WATCOM C++
*/
#define CPP_UTIL_2_EXPORT _export
#define CPP_UTIL_2_IMPORT
#define CPP_UTIL_2_EXTERNC_NAME(name) _##name
#define CPP_UTIL_2_EXTERNC_DECL(prefix, name, args)\
extern "C" \
prefix CPP_UTIL_2_EXTERNC_NAME(name) args

#define CPP_UTIL_2_EXPORT_FUNC_SPEC(ret_type)\
ret_type CPP_UTIL_2_EXPORT

#define CPP_UTIL_2_IMPORT_FUNC_SPEC(ret_type)\
ret_type CPP_UTIL_2_IMPORT

#define CPP_UTIL_2_EXPORT_TYPE(type_qualifier)\
type_qualifier	CPP_UTIL_2_EXPORT

#define CPP_UTIL_2_IMPORT_TYPE(type_qualifier)\
type_qualifier	CPP_UTIL_2_IMPORT

#if defined( __NT__)

#define CPP_UTIL_2_WIN32

#define CPP_UTIL_2_WIN32_DLL_ENTRY_POINT LibMain

#endif /* __NT__ */

#endif /* __WATCOMC__ */


#if defined( __BORLANDC__ )
/*
** Borland C++
*/
#define CPP_UTIL_2_EXPORT _export
#define CPP_UTIL_2_IMPORT 
#define CPP_UTIL_2_EXTERNC_NAME(name) name
#define CPP_UTIL_2_EXTERNC_DECL(prefix, name, args)\
extern "C" \
prefix CPP_UTIL_2_EXTERNC_NAME(name) args

#define CPP_UTIL_2_EXPORT_FUNC_SPEC(ret_type)\
ret_type CPP_UTIL_2_EXPORT

#define CPP_UTIL_2_IMPORT_FUNC_SPEC(ret_type)\
ret_type CPP_UTIL_2_IMPORT

#define CPP_UTIL_2_EXPORT_TYPE(type_qualifier)\
type_qualifier	CPP_UTIL_2_EXPORT

#define CPP_UTIL_2_IMPORT_TYPE(type_qualifier)\
type_qualifier	CPP_UTIL_2_IMPORT

#if defined( __WIN32__ )

#define CPP_UTIL_2_WIN32

#define CPP_UTIL_2_WIN32_DLL_ENTRY_POINT DllEntryPoint

#endif /* __WIN32__ */

#endif /* __BORLANDC__ */


#if defined( __TANDEM )
/*
** Tandem C++
*/
#define CPP_UTIL_2_EXPORT /*export$*/
#define CPP_UTIL_2_IMPORT /*import$*/

#define CPP_UTIL_2_EXPORT_FUNC_SPEC(ret_type)\
CPP_UTIL_2_EXPORT ret_type

#define CPP_UTIL_2_IMPORT_FUNC_SPEC(ret_type)\
CPP_UTIL_2_IMPORT ret_type

#define CPP_UTIL_2_EXPORT_TYPE(type_qualifier)\
type_qualifier	CPP_UTIL_2_EXPORT

#define CPP_UTIL_2_IMPORT_TYPE(type_qualifier)\
type_qualifier	CPP_UTIL_2_IMPORT

#define CPP_UTIL_2_TANDEM

#endif /* __TANDEM */


#if !defined( CPP_UTIL_2_EXPORT )
#define CPP_UTIL_2_EXPORT
#endif

#if !defined( CPP_UTIL_2_IMPORT )
#define CPP_UTIL_2_IMPORT
#endif

#if !defined( CPP_UTIL_2_EXTERNC_NAME )
#define CPP_UTIL_2_EXTERNC_NAME(name) name
#endif

#if !defined( CPP_UTIL_2_EXTERNC_DECL )
#define CPP_UTIL_2_EXTERNC_DECL(prefix, name, args)\
extern "C" \
prefix name args
#endif

#if !defined( CPP_UTIL_2_EXPORT_FUNC_SPEC )
#define CPP_UTIL_2_EXPORT_FUNC_SPEC(ret_type)\
ret_type
#endif

#if !defined( CPP_UTIL_2_IMPORT_FUNC_SPEC )
#define CPP_UTIL_2_IMPORT_FUNC_SPEC(ret_type)\
ret_type
#endif

#if !defined( CPP_UTIL_2_EXPORT_TYPE )
#define CPP_UTIL_2_EXPORT_TYPE(type_qualifier)\
type_qualifier
#endif

#if !defined( CPP_UTIL_2_IMPORT_TYPE )
#define CPP_UTIL_2_IMPORT_TYPE(type_qualifier)\
type_qualifier
#endif

#if defined( CPP_UTIL_2_WIN32 ) || defined( CPP_UTIL_2_WIN64 )
#define CPP_UTIL_2_WINDOWS
#endif
