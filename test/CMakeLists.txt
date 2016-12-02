# Copyright (c) Mario Garcia. Under the MIT License.
# Vikr test script.
#
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("Vikr-Test")

# Set the directories for the compiler
include_directories(SYSTEM ../vikr-source/)


set(TEST_GLOB)


set(TEST_GLOB
  ${TEST_GLOB}
  main.cpp)



add_executable(VikrRendererTest
  ${TEST_GLOB})


target_link_libraries(VikrRendererTest ${VIKR_NAME})