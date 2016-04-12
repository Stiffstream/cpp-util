/*
 * cpp_util_3
 */

/*!
 * \since v.2.3.0
 * \file
 * \brief Вспомогательные средства для организации unit-тестирования.
 */

#pragma once

#include <cpp_util_3/h/lexcast.hpp>

#include <iostream>
#include <stdexcept>

inline void
check_and_throw(
		bool check_result,
		const std::string & condition,
		const std::string & file,
		int line )
	{
		if( !check_result )
			throw std::runtime_error(
					file + ":" + cpp_util_3::slexcast( line ) + ": '" +
					condition + "' failed!" );
	}

#define CHECK_CONDITION(condition) \
check_and_throw( (condition), #condition, __FILE__, __LINE__ )

#define CHECK_THROW_IMPL_(file, line, exception_class, body)\
do \
	{ \
		bool exception_thrown__ = false; \
		try { \
			body \
		} \
		catch( const exception_class & ) { \
			exception_thrown__ = true; \
		} \
		catch( const std::exception & x ) { \
			std::cerr << file << ":" << line << ": expected " \
					<< #exception_class << " by caught: " \
					<< x.what() << std::endl; \
		} \
		catch( ... ) { \
			std::cerr << file << ":" << line << ": expected " \
					<< #exception_class << " but caught unknown exception" \
					<< std::endl; \
		} \
		if( !exception_thrown__ ) \
			throw std::runtime_error( \
					std::string( file ) + ":" + \
					cpp_util_3::slexcast( line ) + ": " + \
					std::string( "expected: " ) + #exception_class + \
					" but nothing thrown" ); \
	} \
while( false )

#define CHECK_THROW(exception_class, body) \
CHECK_THROW_IMPL_(__FILE__, __LINE__, exception_class, body )

#define UNIT_TEST_MAIN(body) \
int \
main( int, char ** ) \
	{ \
		int result = 0; \
\
		try \
			{ \
				body \
			} \
		catch( const std::exception & x ) \
			{ \
				std::cerr << "*** Exception caught: " \
						<< std::endl << x.what() << std::endl; \
				result = 2; \
			} \
\
		return result; \
	}

