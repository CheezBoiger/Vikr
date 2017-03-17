//
// Copyright (c) Mario Garcia, Under the MIT license.
// 
#ifndef __VIKR_COMPUTE_PIPELINE_STATE_HPP
#define __VIKR_COMPUTE_PIPELINE_STATE_HPP


#include <vikr/platform/vikr_types.hpp>
#include <vikr/platform/vikr_api.hpp>

#include <vikr/graphics/render_device.hpp>


namespace vikr {


/// Compute pipeline state, for computing of course!
/// Should only contain one Compute shader and nothing else!
class ComputePipelineState : public RenderDeviceObject, public GUID {
  VIKR_DISALLOW_COPY_AND_ASSIGN(ComputePipelineState);
public:
  ComputePipelineState(GraphicsAPIType type)
    : RenderDeviceObject(type) { }
  
private:

};
} // vikr
#endif // __VIKR_COMPUTE_PIPELINE_STATE_HPP