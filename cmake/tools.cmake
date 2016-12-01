# tools

set(VIKR_TOOLS_ALLOCATOR_DIR ${VIKR_TOOLS_DIR}/allocator/)
set(VIKR_TOOLS_ALLOCATOR_DETAIL_DIR ${VIKR_TOOLS_ALLOCATOR_DIR}/detail/)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_TOOLS_ALLOCATOR_DETAIL_DIR}/pool_allocator.inl
  ${VIKR_TOOLS_ALLOCATOR_DETAIL_DIR}/stack_allocator.inl
  ${VIKR_TOOLS_ALLOCATOR_DETAIL_DIR}/doublebuffered_allocator.inl)


set(VIKR_GLOB
  ${VIKR_GLOB}
  ${VIKR_TOOLS_ALLOCATOR_DIR}/pool_allocator.hpp
  ${VIKR_TOOLS_ALLOCATOR_DIR}/stack_allocator.hpp
  ${VIKR_TOOLS_ALLOCATOR_DIR}/doublebuffered_allocator.hpp)