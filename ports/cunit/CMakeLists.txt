cmake_minimum_required (VERSION 3.8.0)
project (cunit C)

set(HEADERS_DIR  "${PROJECT_SOURCE_DIR}/CUnit/Headers")
set(SOURCES_DIR "${PROJECT_SOURCE_DIR}/CUnit/Sources")

if(MSVC)
  add_compile_options(/W3 /wd4005 /wd4996 -D_CRT_SECURE_NO_WARNINGS)
endif()

configure_file(
  "${HEADERS_DIR}/CUnit.h.in"
  "${PROJECT_BINARY_DIR}/CUnit.h"
  @ONLY
)

file(READ "${PROJECT_BINARY_DIR}/CUnit.h" CUNIT_H)
if (BUILD_SHARED_LIBS)
  string(REPLACE "ifdef CU_DLL" "if 1" CUNIT_H "${CUNIT_H}")
else()
  string(REPLACE "ifdef CU_DLL" "if 0" CUNIT_H "${CUNIT_H}")
endif()
file(WRITE "${PROJECT_BINARY_DIR}/CUnit.h" "${CUNIT_H}")

include_directories("${PROJECT_BINARY_DIR}")
include_directories(${HEADERS_DIR})

add_library(cunit
  "${SOURCES_DIR}/Automated/Automated.c"
  "${SOURCES_DIR}/Basic/Basic.c"
  "${SOURCES_DIR}/Console/Console.c"
  "${SOURCES_DIR}/Framework/CUError.c"
  "${SOURCES_DIR}/Framework/MyMem.c"
  "${SOURCES_DIR}/Framework/TestDB.c"
  "${SOURCES_DIR}/Framework/TestRun.c"
  "${SOURCES_DIR}/Framework/Util.c"
)
target_compile_definitions(cunit PRIVATE -DCU_BUILD_DLL)
target_include_directories(cunit INTERFACE $<INSTALL_INTERFACE:include>)

install(TARGETS cunit EXPORT unofficial-cunit-config)

install(EXPORT unofficial-cunit-config
  NAMESPACE unofficial::cunit::
  DESTINATION share/unofficial-cunit
  FILE unofficial-cunit-config.cmake
)

if(NOT DISABLE_INSTALL_HEADERS)
  install(DIRECTORY "${HEADERS_DIR}/" DESTINATION include/CUnit FILES_MATCHING PATTERN "*.h")
  install(FILES "${PROJECT_BINARY_DIR}/CUnit.h" DESTINATION include/CUnit)
endif()
