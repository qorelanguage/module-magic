cmake_minimum_required(VERSION 2.8.3)

project(qore-magic-module)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 0)
set (VERSION_PATCH 2)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )

FIND_PACKAGE (Qore 0.9 REQUIRED)

find_package(LibMagic REQUIRED)

# Check for C++11.
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
if(COMPILER_SUPPORTS_CXX11)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
else()
    message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

include_directories( ${CMAKE_SOURCE_DIR}/src )
include_directories( ${LIBMAGIC_INCLUDE_DIR} )

set(CPP_SRC
    src/qoremagic.cpp
    src/magic-module.cpp
)

set(QPP_SRC
    src/magic.qpp
   )

qore_wrap_qpp_value(QPP_SOURCES ${QPP_SRC})

SET (module_name "magic")

set(QORE_DOX_TMPL_SRC
  docs/mainpage.dox.tmpl
)

set(_XTRA_LIBS "")
if(CMAKE_SYSTEM_NAME STREQUAL "Windows")
   set(_XTRA_LIBS "${_XTRA_LIBS};shlwapi;regex")
endif()

add_library(${module_name} MODULE ${CPP_SRC} ${QPP_SOURCES})

set(MODULE_DOX_INPUT ${CMAKE_SOURCE_DIR}/src/main.cpp)
string(REPLACE ";" " " MODULE_DOX_INPUT "${MODULE_DOX_INPUT}")

qore_binary_module(${module_name} "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}" ${LIBMAGIC_LIBRARY} ${_XTRA_LIBS})

qore_dist("${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

qore_config_info()
