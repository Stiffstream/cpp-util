require 'mxx_ru/cpp'

Mxx_ru::setup_target(
	Mxx_ru::Cpp::Exe_target.new( "test/lexcast/prj.rb" ) {
		target( "test_lexcast" )

		required_prj( "cpp_util_2/prj.rb" )

		cpp_source( "main.cpp" )
	}
)
