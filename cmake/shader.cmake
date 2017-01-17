# shader

set(VIKR_SHADER_GLSL_DIR ${VIKR_SHADER_DIR}/glsl/)
set(VIKR_SHADER_SPIRV_DIR ${VIKR_SHADER_DIR}/spv/)


if(vulkan)
  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_SHADER_SPIRV_DIR}/spv_linker.hpp
    ${VIKR_SHADER_SPIRV_DIR}/spv_linker.cpp
    ${VIKR_SHADER_SPIRV_DIR}/spv_shader.hpp
    ${VIKR_SHADER_SPIRV_DIR}/spv_shader.cpp
    ${VIKR_SHADER_SPIRV_DIR}/spv_shader_module.hpp
    ${VIKR_SHADER_SPIRV_DIR}/spv_shader_module.cpp
    ${VIKR_SHADER_SPIRV_DIR}/spv_validator.hpp
    ${VIKR_SHADER_SPIRV_DIR}/spv_validator.cpp
    ${VIKR_SHADER_SPIRV_DIR}/spv_compiler.hpp
    ${VIKR_SHADER_SPIRV_DIR}/spv_compiler.cpp)
endif()

# OpenGL always enabled
set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SHADER_GLSL_DIR}/gl_cubemap.hpp
  ${VIKR_SHADER_GLSL_DIR}/gl_cubemap.cpp
  ${VIKR_SHADER_GLSL_DIR}/glsl_preprocessor.hpp
  ${VIKR_SHADER_GLSL_DIR}/glsl_preprocessor.cpp
  ${VIKR_SHADER_GLSL_DIR}/gl_texture.hpp
  ${VIKR_SHADER_GLSL_DIR}/gl_texture.cpp
  ${VIKR_SHADER_GLSL_DIR}/gl_texture1d.hpp
  ${VIKR_SHADER_GLSL_DIR}/gl_texture1d.cpp
  ${VIKR_SHADER_GLSL_DIR}/gl_texture2d.hpp
  ${VIKR_SHADER_GLSL_DIR}/gl_texture2d.cpp
  ${VIKR_SHADER_GLSL_DIR}/gl_texture3d.hpp
  ${VIKR_SHADER_GLSL_DIR}/gl_texture3d.cpp
  ${VIKR_SHADER_GLSL_DIR}/glsl_compiler.hpp
  ${VIKR_SHADER_GLSL_DIR}/glsl_compiler.cpp
  ${VIKR_SHADER_GLSL_DIR}/glsl_linker.hpp
  ${VIKR_SHADER_GLSL_DIR}/glsl_linker.cpp
  ${VIKR_SHADER_GLSL_DIR}/glsl_shader.hpp
  ${VIKR_SHADER_GLSL_DIR}/glsl_shader.cpp)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SHADER_DIR}/shader_uniform_params.hpp
  ${VIKR_SHADER_DIR}/shader_config.hpp
  ${VIKR_SHADER_DIR}/shader.hpp
  ${VIKR_SHADER_DIR}/shader.cpp
  ${VIKR_SHADER_DIR}/material.hpp
  ${VIKR_SHADER_DIR}/material.cpp
  ${VIKR_SHADER_DIR}/texture_config.hpp
  ${VIKR_SHADER_DIR}/texture.hpp
  ${VIKR_SHADER_DIR}/texture.cpp
  ${VIKR_SHADER_DIR}/cubemap.hpp)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_STB_DIR}/stb_image.h
  ${VIKR_STB_DIR}/stb_image.cpp)