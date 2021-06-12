cmake_minimum_required(VERSION 3.20)

project(RWL VERSION 0.1.0)

if(WIN32)
  message(AUTHOR_WARNING "RWL won't work on Windows yet!!")
endif()

find_library(xcbLib xcb NAMES xcb1 XCB REQUIRED)

set(SRC "${CMAKE_CURRENT_SOURCE_DIR}/src/")
set(INCLUDE "${CMAKE_CURRENT_SOURCE_DIR}/include/")
set(RWL "${INCLUDE}rwl/")

set(CLASSES
  "Pen"
  "core"
  "Color"
  "Window/WinComm"
  "Window/Window"
)

set(CPP_FILES
)

set(HPP_FILES
  "rwl"
)

set(PCH_FILES
  "Log"
  "Vec2"
)

set(RECT
  "Rect"
  "RectComm"
  "RectPtrComm"
  "RectRefComm"
)

set(DRAWABLES
  "Drawable"
  "DrawableComm"
)

# Add Rect/ to every file specified in RECT and save it in DRAWABLE
foreach(file ${RECT})
  set(${DRAWABLES} ${DRAWABLES};Rect/${file})
endforeach()

# Add Drawable/ to every file specified in DRAWABLE and save it in HPP_FILES
foreach(file ${DRAWABLES})
  set(HPP_FILES ${HPP_FILES};Drawables/${file})
endforeach()

set(ALL_FILES)

# For every file in CLASSES, add the path to it and an extension and save it in ALL_FILES
foreach(file ${CLASSES})
  set(ALL_FILES ${ALL_FILES};${RWL}${file}.hpp ${SRC}${file}.cpp)
endforeach()

# For every file in CPP_FILES, add the path to it and .cpp extension and save it to ALL_FILES
foreach(file ${CPP_FILES})
  set(ALL_FILES ${ALL_FILES};${SRC}${file}.cpp)
endforeach()

# For every file in HPP_FILES, add the path and .hpp extension to it and save it to ALL_FILES
foreach(file ${HPP_FILES})
  set(ALL_FILES ${ALL_FILES};${RWL}${file}.hpp)
endforeach()

# For every file in PCH_FILES add the path and .hpp extension to it and save it in PCH_FILES and ALL_FILES
foreach(file ${PCH_FILES})
  set(PCH_EVAL ${PCH_EVAL};${RWL}${file}.hpp)
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
"${INCLUDE}"
)

target_precompile_headers(rwl PRIVATE
  <cmath>
  <memory>
  <cstdlib>
  <iostream>
  <xcb/xcb.h>
  <functional>
  <type_traits>
  ${PCH_EVAL}
)

target_compile_features(rwl PUBLIC cxx_std_20)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU" OR CMAKE_CXX_COMPILE_ID STREQUAL "Clang")
  target_compile_options(rwl PRIVATE -pipe -Wall -Werror)
elseif(CMAKE_CXX_COMPILER_ID STREQUAL "MSVC")
  target_compile_options(rwl PRIVATE /W4 /WX)
endif()