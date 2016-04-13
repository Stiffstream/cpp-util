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
manually via `MXX_RU_CPP_TOOLSET` environment variable:

~~~~~
::bash
export MXX_RU_CPP_TOOLSET=clang_linux
~~~~~

# License

cpp\_util is distributed under 3-clauses BSD license.

# What's Inside?

**Under Contruction**