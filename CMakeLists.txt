cmake_minimum_required(VERSION 2.8.3)

project(qore-magic-module)

set (VERSION_MAJOR 0)
set (VERSION_MINOR 0)
set (VERSION_PATCH 2)

# where to look first for cmake modules, before ${CMAKE_ROOT}/Modules/ is checked
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake )


FIND_PACKAGE (Qore REQUIRED)

find_package(LibMagic REQUIRED)


include_directories( ${CMAKE_SOURCE_DIR}/src )
include_directories( ${LIBMAGIC_INCLUDE_DIR} )

set(CPP_SRC
    src/qoremagic.cpp
    src/magic-module.cpp
)

set(QPP_SRC
    src/magic.qpp
   )

qore_wrap_qpp(QPP_SOURCES ${QPP_SRC})

SET (module_name "magic")

add_library(${module_name} SHARED ${CPP_SRC} ${QPP_SOURCES})
qore_binary_module(${module_name} "${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}" ${LIBMAGIC_LIBRARY})

qore_dist("${VERSION_MAJOR}.${VERSION_MINOR}.${VERSION_PATCH}")

qore_config_info()



