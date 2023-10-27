add_library(pl clip.c gfx.c imode.c importer.c math.c pl.c)
add_library(kc::PL ALIAS pl)

target_include_directories(pl PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(pl PRIVATE $<$<BOOL:${MSVC}>:_CRT_SECURE_NO_WARNINGS>)