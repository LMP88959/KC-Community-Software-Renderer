include_guard(DIRECTORY)

macro(target_register_submodule _target _name)
  target_compile_definitions(${_target} PRIVATE MA_SUBMODULE_NAME_=${_name})
  set(KC_MODULE_LIST "${KC_MODULE_LIST} X(${_name}_load_submodule)" PARENT_SCOPE)
endmacro()