/*!
 * \file
 * \brief Helpers for loops.
 * \since
 * v.3.0.0
 */

#pragma once

#include <cpp_util_3/ensure.hpp>

#include <type_traits>
#include <stdexcept>

namespace cpp_util_3 {

namespace loops_details {

template< typename COUNT_TYPE >
typename std::enable_if< std::is_unsigned< COUNT_TYPE >::value >::type
ensure_non_negative( COUNT_TYPE )
	{
		/* There is no need to do additional checks */
	}

template< typename COUNT_TYPE >
typename std::enable_if< std::is_signed< COUNT_TYPE >::value >::type
ensure_non_negative( COUNT_TYPE n )
	{
		ensure< std::invalid_argument >( n >= 0,
				[]{ return "N must be a non negative integer"; } );
	}

} /* namespace loops_details */

//FIXME: there should be comments for arguments of that function.
/*!
 * \brief Helper for doing some action for N times.
 *
 * Usage example:
 * \code
	cpp_util_3::n_times( 3, []{ cout << "===" << endl; } );
 * \endcode
 *
 * \tparam COUNT_TYPE type of loop counter.
 * \tparam LAMBDA lambda or functional object to be body of the loop.
 */
template< typename COUNT_TYPE, typename LAMBDA >
void
n_times( COUNT_TYPE n, LAMBDA && body )
	{
		loops_details::ensure_non_negative( n );
		for( ; n; --n )
			body();
	}

} /* namespace cpp_util_3 */

