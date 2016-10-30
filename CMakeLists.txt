#
# Vikr Build script for compilation.
# Copyright (c) Mario Garcia, Under the MIT License.
#
cmake_minimum_required(VERSION 2.8)

project("VikrSoftware")

# Checking Operating system version.
if (WIN32)
  message("Windows")
elseif(LINUX)
  message("Linux")
else()
  message(ERROR_FATAL "Operating system not compatible with Vikr!")
  return()
endif()

# Name version
set(VIKR_VERSION "0.01")


# concat the name!
set(VIKR_NAME "Vikr")


# Set the directories for the compiler
include_directories(SYSTEM vikr-source/)

# Vikr Rendering engine directories
set(VIKR_SOURCE_DIR   vikr-source/)
set(VIKR_GLAD_DIR     ${VIKR_SOURCE_DIR}/glad/)
set(VIKR_PLATFORM_DIR ${VIKR_SOURCE}/platform/)
set(VIKR_RENDERER_DIR ${VIKR_SOURCE_DIR}/renderer/)
set(VIKR_SHADER_DIR   ${VIKR_SOURCE_DIR}/shader/)
set(VIKR_UTIL_DIR     ${VIKR_SOURCE_DIR}/util/)

# Setting up the glob.
set(VIKR_GLOB)


set(VIKR_NAME ${VIKR_NAME} "_" ${VIKR_VERSION})
# This will have to be changed up a bit though...
# A Rendering engine is usually broken up into pieces, is this ok though?
add_library(${VIKR_NAME} SHARED
  ${VIKR_GLOB})

