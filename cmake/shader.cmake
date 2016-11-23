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
  ${VIKR_SHADER_GLSL_DIR}/gl_material.hpp
  ${VIKR_SHADER_GLSL_DIR}/gl_material.cpp
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
  ${VIKR_SHADER_DIR}/shader_config.hpp
  ${VIKR_SHADER_DIR}/shader.hpp
  ${VIKR_SHADER_DIR}/shader.cpp
  ${VIKR_SHADER_DIR}/shader_compiler.hpp
  ${VIKR_SHADER_DIR}/shader_linker.hpp
  ${VIKR_SHADER_DIR}/material.hpp
  ${VIKR_SHADER_DIR}/material.cpp
  ${VIKR_SHADER_DIR}/texture.hpp
  ${VIKR_SHADER_DIR}/texture.cpp
  ${VIKR_SHADER_DIR}/texture1d.hpp
  ${VIKR_SHADER_DIR}/texture2d.hpp
  ${VIKR_SHADER_DIR}/texture3d.hpp
  ${VIKR_SHADER_DIR}/cubemap.hpp)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_STB_DIR}/stb_image.h
  ${VIKR_STB_DIR}/stb_image.cpp)