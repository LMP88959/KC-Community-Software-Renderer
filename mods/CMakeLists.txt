include(regmod.cmake)
set(KC_MODULE_LIST "")

# would have each submodule be its own folder
# we would do add_subdirectory(...) for each...
add_subdirectory(example)
# ...

configure_file(modloader.c.in 
  ${CMAKE_CURRENT_SOURCE_DIR}/modloader.c @ONLY)

add_library(mods STATIC modloader.c)
add_library(kc::MODS ALIAS mods)

target_link_libraries(mods PRIVATE kc::MA)

# ...then link them to the target
target_link_libraries(mods INTERFACE
  kc-mod::EXAMPLE
  # ...
)