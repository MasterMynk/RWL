cmake_minimum_required(VERSION 3.20)

project(RWL VERSION 0.1.0)

if(WIN32)
  message(AUTHOR_WARNING "RWL won't work on Windows yet!!")
endif()

set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(RWL "${SRC}rwl/")

set(CPP_FILES
  "core"
  "Color"
  "Window"
)
  
set(HPP_FILES
  "rwl"
  "Log"
  "Vec2"
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
  <cmath>
  <stdio.h>
  <iostream>
  <xcb/xcb.h>
  <functional>
)

target_compile_features(rwl PUBLIC cxx_std_20)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILE_ID STREQUAL "Clang")
  target_compile_options(rwl PRIVATE -pipe -Wall -Werror)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(rwl PRIVATE /W4 /WX)
endif()