add_library(fw pkb.c sys.c)
add_library(kc::FW ALIAS fw)

if(UNIX)
  # apt install libx11-dev libxext-dev
  # brew install libx11 xquartz
  find_package(X11 REQUIRED)
elseif(WIN32)
  # Fix WINVER using lowest possible version by default
  string(REGEX MATCH "[0-9]+$" KC_WIN_BUILD ${CMAKE_SYSTEM_VERSION})
endif()

target_sources(fw PRIVATE 
  $<$<BOOL:${WIN32}>:wvid.c> 
  $<$<BOOL:${UNIX}>:xvid.c>
)

target_link_libraries(fw PRIVATE
  $<$<BOOL:${UNIX}>:X11::Xext>
  $<$<BOOL:${WIN32}>:winmm>
)

target_include_directories(fw PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
target_compile_definitions(fw PRIVATE $<$<BOOL:${WIN32}>:KC_OS_WIN_BUILD=${KC_WIN_BUILD}>)