# shader

set(VIKR_SHADER_GLSL_DIR ${VIKR_SHADER_DIR}/glsl/)
set(VIKR_SHADER_SPIRV_DIR ${VIKR_SHADER_DIR}/spirv/)


if(vulkan)
  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_SHADER_SPIRV_DIR}/spirv_compiler.hpp
    ${VIKR_SHADER_SPIRV_DIR}/spirv_compiler.cpp)
endif()

# OpenGL always enabled
set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SHADER_GLSL_DIR}/glsl_compiler.hpp
  ${VIKR_SHADER_GLSL_DIR}/glsl_compiler.cpp
  ${VIKR_SHADER_GLSL_DIR}/glsl_linker.hpp
  ${VIKR_SHADER_GLSL_DIR}/glsl_linker.cpp
  ${VIKR_SHADER_GLSL_DIR}/glsl_parser.hpp
  ${VIKR_SHADER_GLSL_DIR}/glsl_parser.cpp)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SHADER_DIR}/shader_parser.hpp
  ${VIKR_SHADER_DIR}/shader_parser.cpp
  ${VIKR_SHADER_DIR}/shader.hpp
  ${VIKR_SHADER_DIR}/shader.cpp
  ${VIKR_SHADER_DIR}/shader_compiler.hpp
  ${VIKR_SHADER_DIR}/shader_linker.hpp
  ${VIKR_SHADER_DIR}/imaterial.hpp
  ${VIKR_SHADER_DIR}/material.hpp
  ${VIKR_SHADER_DIR}/material.cpp
  ${VIKR_SHADER_DIR}/itexture.hpp
  ${VIKR_SHADER_DIR}/texture.hpp
  ${VIKR_SHADER_DIR}/texture.cpp)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_STB_DIR}/stb_image.h
  ${VIKR_STB_DIR}/stb_image.cpp)