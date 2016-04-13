# What Is It?

cpp\_util is a header-only C++11 library. It is a collection of some small
tools which were created to simplify application developement. Some of them are
rather old and even ancient, created even before C++98 was standartized. Some
are relative new and require C++ compilers with good support of C++11 standard.

# How To Use

Just clone Hg repository somewhere and add path to `dev` folder to your
INCLUDE path. For example:

~~~~~
::bash
cd ~/projects
hg clone https://bitbucket.com/sobjectizerteam/cpp_util-3.0
export CPLUS_INCLUDE_PATH=$(CPLUS_INCLUDE_PATH):~/projects/cpp_util-3.0/dev
~~~~~

or

~~~~~
cd c:\projects
hg clone https://bitbucket.com/sobjectizerteam/cpp_util-3.0
set INCLUDE=%INCLUDE%;c:\projects\cpp_util-3.0\dev
~~~~~

## Recipe For MxxRu::externals

Inclusion of cpp\_util via MxxRu::externals can be done wil recipes like
these:

~~~~~
::ruby
MxxRu::arch_externals :cpp_util_3 do |e|
  e.url 'https://bitbucket.org/sobjectizerteam/cpp_util-3.0/get/v.3.0.0-rc2.tar.gz'

  e.map_dir 'dev/cpp_util_3' => 'dev'
end
~~~~~

Or

~~~~~
::ruby
MxxRu::hg_externals :cpp_util_3 do |e|
  e.url 'https://bitbucket.org/sobjectizerteam/cpp_util-3.0'
  e.tag 'v.3.0.0-rc2'

  e.map_dir 'dev/cpp_util_3' => 'dev'
end
~~~~~

## Building Samples And Test

[Mxx_ru](https://sourceforge.net/projects/mxxru/) build tool is necessary
for building samples and tests. To install Mxx\_ru you need Ruby and RubyGems
installed in your system (in most cases RubyGems is installed with
Ruby automatically). Then:

~~~~~
::bash
gem install Mxx_ru
~~~~~

To build all tests and samples it is necessary to run `ruby build.rb` from
`dev` folder:

~~~~~
::bash
cd ~/projects
hg clone https://bitbucket.com/sobjectizerteam/cpp_util-3.0
cd cpp_util-3.0/dev
ruby build.rb
~~~~~

To build some specific sample or test it is necessary to run corresponding
project file from `dev` folder:

~~~~~
::bash
cd ~/projects
hg clone https://bitbucket.com/sobjectizerteam/cpp_util-3.0
cd cpp_util-3.0/dev
ruby sample/lexcast/util/prj.rb
~~~~~

*Note.* Mxx\_ru tries to detect type of your compiler automatically. In most
cases it just works. But sometimes it is necessary to specify your compiler
manually via `MXX_RU_CPP_TOOLSET` environment variable. For example if you have
GCC and clang in your Linux and want to use clang, then `MXX_RU_CPP_TOOLSET`
must be set as:

~~~~~
::bash
export MXX_RU_CPP_TOOLSET=clang_linux
~~~~~

# License

cpp\_util is distributed under 3-clauses BSD license.

# What's Inside?

## cpp_util_3/at_scope_exit.hpp

Helper function `at_scope_exit`. Something like `scope_exit` from D language
or `defer` from Go:

~~~~~
::c++
#include <cpp_util_3/at_scope_exit.hpp>
...
void dump_content_to_file( const char * file_name, const content & cnt )
{
	std::FILE * file = std::fopen( file_name, "w" );
	if( file )
	{
		auto file_closer = cpp_util_3::at_scope_exit( [file] {
			std::fclose( file );
		} );
		...
	}
}

~~~~~

## cpp_util_3/detect_compiler.hpp

Definition for macros like `CPP_UTIL_3_EXPORT`, `CPP_UTIL_3_IMPORT`,
`CPP_UTIL_3_WINDOWS`, `CPP_UTIL_3_WIN64` and so on.

Macros `CPP_UTIL_3_EXPORT` and `CPP_UTIL_3_IMPORT` hide compiler-specific
keywords for exporting/importing functions from dynamic-link libraries:

~~~~~
::c++
// Somewhere in DLL-related header file...
#include <cpp_util_3/detect_compiler.hpp>

#if defined(MY_DLL)
	// Header included during compilation of the DLL.
	// Symbols must be exported.
	#define MY_DLL_DECLSPEC CPP_UTIL_3_EXPORT
#else
	// Header included during compilation of a DLL client.
	// Symbols must be imported.
	#define MY_DLL_DECLSPEC CPP_UTIL_3_IMPORT
#endif

...
class MY_DLL_DECLSPEC some_exported_class { ... };

MY_DLL_DECLSPEC void some_exported_function();
~~~~~


**Under Contruction**
