require 'rubygems'

gem 'Mxx_ru', '>= 1.3.0'

require 'mxx_ru/cpp'

MxxRu::Cpp::exe_target {

  target 'unit.test.terminate_if_throws'

  cpp_source 'main.cpp'
}
