/*
 * Demo of cpp_util_3/h/detect_compiler.hpp capabilities.
 */

#include <iostream>

#include <cpp_util_3/detect_compiler.hpp>

#define MACRO_CONTENT_IMPL_(M) #M
#define MACRO_CONTENT(M) MACRO_CONTENT_IMPL_(M)

int
main()
{
	std::cout << "CPP_UTIL_2_EXPORT: " << MACRO_CONTENT(CPP_UTIL_2_EXPORT) << std::endl;
	std::cout << "CPP_UTIL_2_IMPORT: " << MACRO_CONTENT(CPP_UTIL_2_IMPORT) << std::endl;

#if defined(CPP_UTIL_2_WINDOWS)
	std::cout << "CPP_UTIL_2_WINDOWS" << std::endl;

#if defined(CPP_UTIL_2_WIN64)
	std::cout << "CPP_UTIL_2_WIN64" << std::endl;
#endif

#if defined(CPP_UTIL_2_WIN32)
	std::cout << "CPP_UTIL_2_WIN32" << std::endl;
#endif

#endif /* ifdef CPP_UTIL_2_WINDOWS */
}

