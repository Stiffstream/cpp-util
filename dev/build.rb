require 'mxx_ru/cpp'

MxxRu::Cpp::composite_target( Mxx_ru::BUILD_ROOT ) {

	global_include_path '.'

	toolset.force_cpp11

	# If there is local options file then use it.
	if FileTest.exist?( 'local-build.rb' )
		required_prj 'local-build.rb'
	else
		default_runtime_mode( MxxRu::Cpp::RUNTIME_RELEASE )
		MxxRu::enable_show_brief
		global_obj_placement MxxRu::Cpp::RuntimeSubdirObjPlacement.new( 'target' )
	end

	required_prj 'test/lexcast/prj.ut.rb'

	required_prj 'test/hex_dumps/prj.ut.rb'

	required_prj 'test/string_piece/prj.ut.rb'

	required_prj 'test/at_scope_exit/prj.ut.rb'

	required_prj 'test/rollback_on_exception/prj.ut.rb'

	required_prj 'test/ensure/prj.ut.rb'

	required_prj 'sample/lexcast/util/prj.rb'
	required_prj 'sample/lexcast/throw/prj.rb'

	required_prj 'sample/detect_compiler/prj.rb'
}
