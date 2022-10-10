cmake_minimum_required(VERSION 3.1)

include("${CMAKE_CURRENT_LIST_DIR}/OpenALTargets.cmake")

set(OPENAL_FOUND ON)
set(OPENAL_INCLUDE_DIR $<TARGET_PROPERTY:OpenAL::OpenAL,INTERFACE_INCLUDE_DIRECTORIES>)
set(OPENAL_LIBRARY $<LINK_ONLY:OpenAL::OpenAL>)
set(OPENAL_DEFINITIONS $<TARGET_PROPERTY:OpenAL::OpenAL,INTERFACE_COMPILE_DEFINITIONS>)
set(OPENAL_VERSION_STRING 1.22.2)
