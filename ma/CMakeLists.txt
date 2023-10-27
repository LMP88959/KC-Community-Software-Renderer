# crickets...

add_library(ma STATIC ma.c bstrap.c)
add_library(kc::MA ALIAS ma)

target_include_directories(ma PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})