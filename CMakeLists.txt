cmake_minimum_required(VERSION 3.20)

project(RWL VERSION 0.1.0)

if(WIN32)
  message(AUTHOR_WARNING "RWL won't work on Windows yet!!")
endif()

set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(RWL "${SRC}rwl/")

set(CPP_FILES
  "core"
)

set(HPP_FILES
  "rwl"
)
set(ALL_FILES)

foreach(file ${CPP_FILES})
  set(ALL_FILES ${ALL_FILES};${RWL}${file}/${file}.hpp ${RWL}${file}/${file}.cpp)
endforeach()

foreach(file ${HPP_FILES})
  set(ALL_FILES ${ALL_FILES};${RWL}${file}.hpp)
endforeach()

add_library(rwl
  ${ALL_FILES}
)

if(WIN32)
elseif(APPLE)
else()
target_compile_definitions(rwl PUBLIC
  RWL_PLATFORM=LINUX
)
endif()

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
  target_compile_definitions(rwl PUBLIC
    RWL_DEBUG=1
  )
endif()

target_include_directories(rwl PUBLIC
  "${SRC}"
)

target_precompile_headers(rwl PRIVATE
  <xcb/xcb.h>
  <functional>
)