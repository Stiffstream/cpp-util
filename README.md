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

Inclusion of cpp\_util via MxxRu::externals can be done with recipes like
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
		auto file_closer = cpp_util_3::at_scope_exit( [file]{ std::fclose( file ); } );
		...
	}
}

~~~~~

## cpp_util_3/detect_compiler.hpp

Definition for macros like `CPP_UTIL_3_EXPORT`, `CPP_UTIL_3_IMPORT`,
`CPP_UTIL_3_UNIX`, `CPP_UTIL_3_WINDOWS`, `CPP_UTIL_3_WIN64` and so on.

Macros `CPP_UTIL_3_EXPORT` and `CPP_UTIL_3_IMPORT` hide compiler-specific
keywords for exporting/importing functions from dynamic-link libraries:

~~~~~
::c++
// Somewhere in DLL-related header file...
#pragma once
...
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

## cpp_util_3/ensure.hpp

Helper function `ensure` for simplification of checking for some condition
and throwing an exception if that condition is not fulfilled:

~~~~~
::c++
#include <cpp_util_3/ensure.hpp>
...
// Do some 3rd-party library call.
auto r = mosquitto_subscribe( m_mosq.get(),
		&mid, topic_name.c_str(), qos_to_use );
// Expect only a subset of error codes.
// If another error code is returned then exception must be thrown.
cpp_util_3::ensure< std::runtime_error >(
		MOSQ_ERR_SUCCESS == r || MOSQ_ERR_NO_CONN == r || MOSQ_ERR_CONN_LOST == r,
		[&]{
			return tfm::format( "mosquitto_subscribe(%s, %d) failed, rc=%d",
				topic_name, qos_to_use, r );
		} );

~~~~~

## cpp_util_3/terminate_if_throws.hpp

Helper function `terminate_if_throws` is intended to be used in cases where
some block of code must be run without any exceptions. If an exception is thrown
from that block then the whole application must be terminated.

~~~~~
::c++
#include <cpp_util_3/terminate_if_throws.hpp>
...
// We want to provide strong exception guarantee for that method.
void some_complex_class::do_some_modification(const params & p) {
  // Checks all necessary conditions first.
  // Some exceptions can be thrown here.
  check_condition_one(p);
  check_condition_two(p);
  ...
  // Preallocate some resources.
  // Exceptions are expected here. But this is not a problem
  // because there is no any actual state changes yet.
  auto r1 = preallocate_resource_one(p);
  auto r2 = preallocate_resource_two(p);
  ...
  // All preparations are done. We don't expect exceptions
  // in the following block of code. But if some exception is thrown
  // then we don't know how to repair from it.
  cpp_util_3::terminate_if_throws( [&] {
    do_state_change_action_one(...);
	do_state_change_action_two(...);
	...
  } );
}
~~~~~

## cpp_util_3/outliving.hpp

Helper class and related stuff for lifetime indication via type:

~~~~~
::c++
class config { ... };

class data_processor {
	// Indicator that reference to config must outlive data_processor object.
	cpp_util_3::outliving_reference_t<const config> cfg_;
public :
	data_processor(
		// Indicator that reference to config must outlive data_processor object.
		cpp_util_3::outliving_reference_t<const config> cfg)
	: cfg_(cfg)
	{...}
	...
};

void f() {
	config cfg = load_config();
	data_processor processor( cpp_util_3::outliving_const(cfg) );
	...
}
~~~~~

## cpp_util_3/lexcast.hpp

Family of functions `lexcast` and `slexcast`. They are very old and now it
is better to use more modern and efficient alternatives (*Boost.LexicalCast*,
*cppformat* or *tinyformat*). Functions `lexcast`/`slexcast` are still in
cpp\_util library mostly by reasons of compatibility.

But there are some lexcast helpers which can be useful even now.

### cpp_util_3/lexcasts/utils.hpp

Several tools like `hex`, `hex_0x` and `all`. For example, it is possible to
show content of a vector by help from cppformat and cpp\_util:

~~~~~
::c++
#include <cppformat/format.h>

#include <cpp_util_3/lexcasts/util.hpp>

#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;
using namespace cpp_util_3;

int main()
	{
		vector< int > v{ 1, 2, 3, 4, 5, 6 };

		fmt::print( "vector is: {}\n", lexcasts::all( v, ", " ) );
		fmt::print( "vector is: {}\n", lexcasts::all( v, ", ", lexcasts::hex_0x() ) );
		fmt::print( "items greater than 3: {}\n",
				lexcasts::all(
					upper_bound( begin(v), end(v), 3),
					end(v),
					", ", lexcasts::hex() ) );
	}
~~~~~

This example will print:

~~~~~
vector is: 1, 2, 3, 4, 5, 6
vector is: 0x1, 0x2, 0x3, 0x4, 0x5, 0x6
items greater than 3: 4, 5, 6
~~~~~

## cpp_util_3/loops.hpp

Helper function(s) for writing loops in declarative style. For example:

~~~~~
::c++
#include <cpp_util_3/loops.hpp>

using namespace cpp_util_3;
...
n_times( 3, []{ std::cout << "===" << std::endl; } );
~~~~~

## cpp_util_3/hex_dumps/string_dumper.hpp

Helper functions for creation of hex dumps of strings or byte buffers
(could be useful for logging):

~~~~~
::c++
#include <cpp_util_3/hex_dumps/string_dumper.hpp>
#include <iostream>

using namespace std;
namespace dumps = cpp_util_3::hex_dumps;

int main()
	{
		// Will print '68 65 6c 6c 6f 2c 20 77 6f 72 6c 64':
		cout << "'" << dumps::string_dumper("hello, world") << "'\n";
		// Will print '68656c6c6f2c20776f726c64'
		cout << "'" << dumps::string_dumper_without_spaces("hello, world") << "'\n";
	}
~~~~~

## cpp_util_3/rollback_on_exception.hpp

Helper function `do_with_rollback_on_exception` which simplifies
writting of exception safe code:

~~~~~
::c++
#include <cpp_util_3/rollback_on_exception.hpp>
...
void some_complex_container::insert_item( const some_data & item )
{
	// Three internal containers must be updated.
	// Any update can lead to exception.
	// Container update must be rolled back on exception.
	first_container_.push_back( item );
	cpp_util_3::do_with_rollback_on_exception(
		[&]{
			second_container_.push_back( item );
			cpp_util_3::do_with_rollback_on_exception(
				[&]{ thrid_container_.push_back( itsm ); },
				// Rollback action.
				[&]{ second_container_.pop_back(); } );
		},
		// Rollback action.
		[&]{ first_container_.pop_back(); } );
}
~~~~~

## cpp_util_3/string_piece.hpp

Helper class `string_piece_t` is old and simple analog of `string_span` from
C++ Core Guidelines or `string_view` from proposals for C++17.

It can be used for functions and methods which except string-like params:

~~~~~
::c++
#include <cpp_util_3/string_piece.hpp>
...
bool is_valid_name( cpp_util_3::string_piece_t name ) {
  ... // Some manipulation of name's contents.
}
...
char name1[ 16 ] = {...};
if( is_valid_name( name1 ) ) { ... }

if( is_valid_name( "some name" ) ) { ... }

std::string name2 = ...;
if( is_valid_name( name2 ) ) { ... }
~~~~~