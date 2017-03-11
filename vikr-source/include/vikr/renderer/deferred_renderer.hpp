//
// Copyright (c) Mario Garcia, Under the MIT License.
// 
#ifndef __VIKR_DEFERRED_RENDERER_HPP
#define __VIKR_DEFERRED_RENDERER_HPP


#include <vikr/renderer/renderer.hpp>
#include <vikr/graphics/command_buffer.hpp>
#include <vikr/graphics/framebuffer.hpp>
#include <vikr/graphics/render_pass.hpp>
#include <vikr/renderer/render_queue.hpp>
#include <vikr/shader/texture_config.hpp>
#include <vikr/shader/shader.hpp>
#include <vikr/shader/cubemap.hpp>
#include <vikr/shader/font_printer.hpp>
#include <vikr/mesh/mesh.hpp>
#include <vikr/renderer/gbuffer.hpp>
#include <vikr/renderer/screen_quad.hpp>
#include <vikr/renderer/skybox.hpp>
#include <glm/glm.hpp>
#include <string>
#include <memory>
#include <unordered_map>


namespace vikr {


/// Default Deferred Renderer implementation. This renderer should demonstrate
/// the simplicity and quickness it takes for developing a small renderer
/// in a quick amount of time, most notably a deferred one in this case.
/// This allows for more time handling shader programming as opposed to 
/// programming a low level renderer.
class DeferredRenderer : public IRenderer {
public:
  /// Default constructor override.
  DeferredRenderer();
  
  /// Set the camera for this renderer engine.
  vvoid SetCamera(ICamera *cam) override { camera = cam; }

  /// Get the camera from this renderer engine. This helps with
  /// RenderPasses that require camera input, such as view, projection,
  /// and position. Of course, you can always store that information on
  /// a uniform buffer.
  ICamera *GetCamera() override { return camera; }

  /// Initialize the renderer with the render device plugin.
  /// This enables our renderer object to use the specified 
  /// RHI to use in this device. It is essential that the RenderDevice
  /// must not be deleted in any way, as the Renderer relies heavily
  /// on it's use.
  vint32 Init(RenderDevice *device, ResourceManager *mgr) override;

  /// Render the given scene. a Scene input is required in order
  /// to properly draw something on the screen. One may also be able
  /// to supply our renderer with basic SceneNodes and commands instead
  /// of an entire Scene.
  vvoid Render() override;

  /// Pushback a RenderCommand. This will push back our command
  /// in the render queue for the next frame render.
  vvoid PushBack(RenderCommand *command) override;

  /// Pushback a SceneNode. Will Most commonly be used for 
  /// Basic object rendering. We will be supplying a Scene input
  /// parameter in the future, but for now, SceneNode suffices.
  /// Additionally, any light commands in the SceneNode will be 
  /// pushed back to the deferred queue.
  vvoid PushBack(SceneNode *obj) override;

  /// Pushback a RenderCommand into the deferred queue. This 
  /// allows the user to manually push back a rendering command
  /// without it being automated by the SceneNode. 
  vvoid PushBackDeferred(RenderCommand *command) override;

  /// Sort the RenderQueue inside this Renderer. Sorting is 
  /// done automatically when calling Render(), but if need be,
  /// the programmer may also be able to sort the queue ahead of
  /// time.
  vvoid Sort() override { m_renderQueue.Sort(); }

  /// Set a color for this renderer to use when clearing
  /// the screen after displaying a frame. Any texels not 
  /// drawn in on the display will be colored in this format.
  vvoid SetClearColor(glm::vec4 cc) { clear_color = cc; }

  /// Get the color used for clearing the screen with.
  glm::vec4 GetClearColor() { return clear_color; }

  /// Check if this Renderer is in the middle of rendering.
  /// This is essentially, especially for multithreaded applications,
  /// and maybe multiprocess applications.
  vbool IsRendering() { return rendering; }

  /// Present the Frame that has been rendered, onto the 
  /// screen for view. This needs to be called after Render()
  /// in order to see the frame onscreen.
  vvoid Present() override;

  /// Get the current RenderDevice used to initialize, 
  /// as well as render, this Renderer engine.
  RenderDevice *GetDevice() { return m_renderDevice; }

  /// Clean up all resources. This won't cleanup the 
  /// RenderDevice or ResourceManager, as it is up to the 
  /// programmer to clean those up after themselves.
  vint32 CleanupResources();


private:
  /// Camera currently used for rendering.
  /// Essential, as it is the only way to 
  /// see any transformations on screen, heh. 
  ICamera *camera;

  /// Checks if the renderer is in the middle of rendering.
  /// Usefully for multithreaded applications as it should be
  /// treated as a read-only variable
  vbool rendering = false;

  /// The RenderQueue that is used to store RenderCommands.
  /// Contains RenderCommands, as well as deferred RenderCommands,
  /// for use when rendering onto a frame.
  RenderQueue m_renderQueue;
  
  /// Object oriented  Gbuffer pass.
  GBuffer m_gbuffer;

  /// Le Screen quad. This is where we draw our 
  /// geometry on, as well as the lighting. Since geometry will
  /// be projected onto a texture map, light can be used to shade
  /// geometry pixels that are actually seen by the view, and not
  /// on objects that can not be seen, thus causing light shading
  /// overrlaps.
  ScreenQuad m_screenquad;

  /**
    light shader.
  */
  ShaderProgram *lightShader                              = nullptr;

  /// the Commandbufferlist.
  CommandbufferList *m_commandBufferList;
  CommandbufferList *m_deferredBufferList;

  std::vector<DirectionalLight *> m_directionalLights;

  FontPrinter printer;

  Skybox skybox;

  /**
    Render device used by this Renderer.
  */
  RenderDevice *m_renderDevice                            = nullptr;

  glm::vec4 clear_color;
};
} // vikr
#endif // __VIKR_DEFERRED_RENDERER_HPP