# shader

set(VIKR_SHADER_SRC_DIR ${VIKR_SRC_DIR}/shader/)
set(VIKR_SHADER_INCLUDE_DIR ${VIKR_INCLUDE_DIR}/shader/)

set(VIKR_SHADER_GLSL_SRC_DIR ${VIKR_SHADER_SRC_DIR}/glsl/)
set(VIKR_SHADER_GLSL_INCLUDE_DIR ${VIKR_SHADER_INCLUDE_DIR}/glsl/)

set(VIKR_SHADER_SPIRV_SRC_DIR ${VIKR_SHADER_SRC_DIR}/spv/)
set(VIKR_SHADER_SPIRV_INCLUDE_DIR ${VIKR_SHADER_INCLUDE_DIR}/spv/)

set(VIKR_STB_SRC_DIR ${VIKR_SHADER_SRC_DIR}/stb/)
set(VIKR_STB_INCLUDE_DIR ${VIKR_SHADER_INCLUDE_DIR}/stb/)

if(vulkan)
  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_SHADER_SPIRV_SRC_DIR}/spv_linker.cpp
    ${VIKR_SHADER_SPIRV_SRC_DIR}/spv_shader.cpp
    ${VIKR_SHADER_SPIRV_SRC_DIR}/spv_shader_module.cpp
    ${VIKR_SHADER_SPIRV_SRC_DIR}/spv_validator.cpp
    ${VIKR_SHADER_SPIRV_SRC_DIR}/spv_compiler.cpp
    ${VIKR_SHADER_SPIRV_SRC_DIR}/spv_program.cpp
    ${VIKR_SHADER_SPIRV_SRC_DIR}/spv_texture.cpp
  )

  set(VIKR_GLOB
    ${VIKR_GLOB}
    ${VIKR_SHADER_SPIRV_INCLUDE_DIR}/spv_compiler.hpp
    ${VIKR_SHADER_SPIRV_INCLUDE_DIR}/spv_validator.hpp            
    ${VIKR_SHADER_SPIRV_INCLUDE_DIR}/spv_shader_module.hpp
    ${VIKR_SHADER_SPIRV_INCLUDE_DIR}/spv_shader.hpp
    ${VIKR_SHADER_SPIRV_INCLUDE_DIR}/spv_linker.hpp
    ${VIKR_SHADER_SPIRV_INCLUDE_DIR}/spv_program.hpp
    ${VIKR_SHADER_SPIRV_INCLUDE_DIR}/spv_texture.hpp
  )
endif()

# OpenGL always enabled
set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SHADER_GLSL_SRC_DIR}/gl_cubemap.cpp
  ${VIKR_SHADER_GLSL_SRC_DIR}/glsl_preprocessor.cpp
  ${VIKR_SHADER_GLSL_SRC_DIR}/gl_texture.cpp
  ${VIKR_SHADER_GLSL_SRC_DIR}/gl_texture1d.cpp
  ${VIKR_SHADER_GLSL_SRC_DIR}/gl_texture2d.cpp
  ${VIKR_SHADER_GLSL_SRC_DIR}/gl_texture3d.cpp
  ${VIKR_SHADER_GLSL_SRC_DIR}/glsl_compiler.cpp
  ${VIKR_SHADER_GLSL_SRC_DIR}/glsl_linker.cpp
  ${VIKR_SHADER_GLSL_SRC_DIR}/glsl_shader.cpp
  ${VIKR_SHADER_GLSL_SRC_DIR}/glsl_program.cpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SHADER_GLSL_INCLUDE_DIR}/glsl_shader.hpp
  ${VIKR_SHADER_GLSL_INCLUDE_DIR}/glsl_linker.hpp
  ${VIKR_SHADER_GLSL_INCLUDE_DIR}/glsl_compiler.hpp
  ${VIKR_SHADER_GLSL_INCLUDE_DIR}/gl_texture3d.hpp
  ${VIKR_SHADER_GLSL_INCLUDE_DIR}/gl_texture2d.hpp
  ${VIKR_SHADER_GLSL_INCLUDE_DIR}/gl_texture1d.hpp
  ${VIKR_SHADER_GLSL_INCLUDE_DIR}/gl_texture.hpp
  ${VIKR_SHADER_GLSL_INCLUDE_DIR}/glsl_preprocessor.hpp
  ${VIKR_SHADER_GLSL_INCLUDE_DIR}/gl_cubemap.hpp
  ${VIKR_SHADER_GLSL_INCLUDE_DIR}/glsl_program.hpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SHADER_SRC_DIR}/shader.cpp
  ${VIKR_SHADER_SRC_DIR}/material.cpp
  ${VIKR_SHADER_SRC_DIR}/texture.cpp
  ${VIKR_SHADER_SRC_DIR}/font_printer.cpp
  ${VIKR_SHADER_SRC_DIR}/shader_program.cpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_SHADER_INCLUDE_DIR}/cubemap.hpp
  ${VIKR_SHADER_INCLUDE_DIR}/texture_config.hpp
  ${VIKR_SHADER_INCLUDE_DIR}/texture.hpp
  ${VIKR_SHADER_INCLUDE_DIR}/material.hpp
  ${VIKR_SHADER_INCLUDE_DIR}/shader_uniform_params.hpp
  ${VIKR_SHADER_INCLUDE_DIR}/shader_config.hpp
  ${VIKR_SHADER_INCLUDE_DIR}/shader.hpp
  ${VIKR_SHADER_INCLUDE_DIR}/font_printer.hpp
  ${VIKR_SHADER_INCLUDE_DIR}/shader_program.hpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_STB_SRC_DIR}/stb_image.cpp
)

set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_STB_INCLUDE_DIR}/stb_image.h
  ${VIKR_STB_INCLUDE_DIR}/stb_truetype.h
)



