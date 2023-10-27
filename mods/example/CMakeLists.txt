# filler submodule
add_library(kcmod_example STATIC example.c)
add_library(kc-mod::EXAMPLE ALIAS kcmod_example)

target_register_submodule(kcmod_example EXAMPLE)
target_link_libraries(kcmod_example PRIVATE kc::MA)