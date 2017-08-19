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
	std::cout << "CPP_UTIL_3_EXPORT: " << MACRO_CONTENT(CPP_UTIL_3_EXPORT) << std::endl;
	std::cout << "CPP_UTIL_3_IMPORT: " << MACRO_CONTENT(CPP_UTIL_3_IMPORT) << std::endl;

#if defined(CPP_UTIL_3_WINDOWS)
	std::cout << "CPP_UTIL_3_WINDOWS" << std::endl;

#if defined(CPP_UTIL_3_WIN64)
	std::cout << "CPP_UTIL_3_WIN64" << std::endl;
#endif

#if defined(CPP_UTIL_3_WIN32)
	std::cout << "CPP_UTIL_3_WIN32" << std::endl;
#endif

#endif /* ifdef CPP_UTIL_3_WINDOWS */

#if defined(CPP_UTIL_3_UNIX)
	std::cout << "CPP_UTIL_3_UNIX" << std::endl;
#endif /* ifdef CPP_UTIL_3_UNIX */
}

