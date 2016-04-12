require 'mxx_ru/cpp'

Mxx_ru::setup_target(
	Mxx_ru::Cpp::Exe_target.new( "sample/lexcast/util/prj.rb" ) {
		target( "sample_lexcast_util" )

		required_prj( "cpp_util_2/prj.rb" )

		cpp_source( "main.cpp" )
	}
)
