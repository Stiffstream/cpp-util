require 'mxx_ru/cpp'

Mxx_ru::setup_target(
	Mxx_ru::Cpp::Exe_target.new( "sample/lexcast/throw/prj.rb" ) {
		target( "sample_lexcast_throw" )

		required_prj( "cpp_util_2/prj.rb" )

		cpp_source( "main.cpp" )
	}
)
