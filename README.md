# Vikr Renderer
Vikr is a smallscale renderer using OpenGL 4.3 and Vulkan API graphics. It is an academic graphics
engine solely designed for researching computer graphics and testing shaders for academic use. Its
capability does not stop in just mere research, as it can also be used for startup game engines and
other possibilities involving physics and computer vision. It is still in current development, so use 
this engine for hobbyist use, and not for professional work!

# Implementation
Vikr Rendering implementation involves a large use of abstraction:
  
![alt tag](https://raw.githubusercontent.com/Cheezboiger/vikr/master/samples/dragon_ex.png)
  
Currently all resources and implementations within the engine source code is subject to change,
so keep in mind that this engine is not fully stable. I only ask for patience until the engine is fully implemented, cleaned up,
and optimized. Contribution is always welcome!
  
The Design goal of this renderer is to allow the user to handle memory management, while the Engine merely uses the data
given to manipulate the objects it must render. **VERY STRONG** emphasis in avoiding dynamic allocation as much as possible.

# Current Status

The image below describes the current, stable, implementation of the Vikr Renderer:
  
Keep in mind that the following image was rendered in OpenGL:
![alt tag](https://raw.githubusercontent.com/Cheezboiger/vikr/master/samples/deferred_sample.png)

Current Features:
  - Working Scene Graph with customizable components.
  - Model Loader ready.
  - Deferred Shading and lighting.
  - OpenGL Ready.
  - Blinn-Phong default shading
  - Graphics Layer hardware abstraction with plugin Render Devices (This allows easier plugins for OpenGL, Vulkan, etc...)
  - GLSL Compiler, Preprocessor, and Linker ready.
  - Quaternion-based Motion Camera.
  - Cross compatibility with Windows and Linux.
  
Work in Progress:
  - Vulkan implementation (for a more modern Graphics API)
  - Shadow Mapping
  - SSAO
  - Cubemaps (skyboxes as well).
  - Bumpmaps (Tangent and BiTangent spaces)
  - Parallax Mapping
  - HDR and Bloom

Future Works:
  - Physically Based Rendering (PBR)
  - Animation
  - Audio (For some sounds with your Scene?)
  - Camera Frustum Culling
  - Octree Culling
  - Vikr Editor (for easier editing when using Vikr)
  - Multithreaded Rendering
  - Metal and DirectX 12 implementations
    
# Building This Project
To build this project, you need the following:
  - CMake (the latest version)
  - a C++ Compiler (Visual Studio for Windows, GCC for Linux, Clang for OSX (not tested), or Intel, whichever really)
  - Graphics Card with Vulkan Ready Driver (if you plan on using Vulkan).

This Project comes with a cmake script, ready to setup the project without too much hassle. The real hassle would be the 
shader files, which when compiling and running, the program would not know where to look (I still need to work on the 
filesystem handles for the Renderer). For now, simply copy/paste the shaders from the lib folder into the directory of where the 
executable was compiled and linked, and store them into a folder called "shaders" within the same directory as the executable.
This will be fixed soon, I promise! 

simply create a folder and use the cmake gui to build the project for you. If you are doing the command line (or terminal) way,
just type, within your folder that you plan to build the project in:

```
cmake path/to/vikr/project/
```
  
Even easier, I added the current build folder with a Windows .sln ready file, so the project should work out of the box, except you still need to worry about the shader files...

# Further Note
This is an engine solely for researching and as a hobby, especially if you are interested in how Renderers work. If you are looking for a well designed Graphics Renderer, I suggest looking into Pixar's RenderMan, Autodesk Maya, 3DSMax, AutoCAD, Blender, and/or other professional software. If you are looking for a stable Game Engine for Game development, I would definitely recommend Unity, Unreal Engine (highly recommend), Crytek Engine, Cocos2D, Torque, BansheeEngine, Pomdog and/or other professional/indie game engines. 
  
If you are interested in Graphics Programming, I would suggest you look into Joey De Vries LearnOpenGL tutorials and, if you are ready, into Alex Overvoorde's Vulkan Tutorials. This Graphics engine would not be possible without their tutorials.
  
Vulkan tutorials: https://vulkan-tutorial.com/
OpenGL tutorials: https://learnopengl.com/
  
# Credits and Honorable Mentions
Credits out to Joey De Vries and his tutorials on OpenGL, which has taught me,
through simple to understand, steps on learning graphics programming! check
out his tutorial website: http://learnopengl.com/#!Introduction
  
You should also check out his work in progress engine here as well, as he is implementing
much more advanced work than me! : https://github.com/JoeyDeVries/Cell
  
Notable mention to Koray Hagen and his delectable knowledge on Computer Graphics rendering,
helping me by pointing the way to certain rendering techniques with tangent space normal
mapping and Skew-Symmetric Matrices.