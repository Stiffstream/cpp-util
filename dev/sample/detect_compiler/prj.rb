require 'mxx_ru/cpp'

MxxRu::Cpp::exe_target {
	target( "sample_detect_compiler" )

	required_prj( "cpp_util_2/prj.rb" )

	cpp_source( "main.cpp" )
}

