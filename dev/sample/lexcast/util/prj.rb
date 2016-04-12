require 'mxx_ru/cpp'

MxxRu::Cpp::exe_target {
	target 'sample_lexcast_util'

	required_prj 'cpp_util_3/prj.rb'

	cpp_source 'main.cpp'
}
