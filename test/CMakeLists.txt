# Copyright (c) Mario Garcia. Under the MIT License.
# Vikr test script.
#
cmake_minimum_required(VERSION 2.8 FATAL_ERROR)
project("Vikr-Test")


set(TEST_GLOB)


set(TEST_GLOB
  ${TEST_GLOB}
  main.cpp)



add_executable(VikrRendererTest
  ${TEST_GLOB})