# Vikr Renderer
Smallscale Renderer using OpenGL 4.3 and Vulkan API graphics. 
Experimental Graphics Renderer Engine. This is a research and experimental
engine...

# Redesign
This engine is going to be completely redesigned, The currently implementation is creating much more 
code smell that expected, and the further it is becoming complicated, the more it begins to pile on
into a huge mess. This engine **IS UNDERGOING A MAJOR REDESIGN.**


# Implementation
Vikr is still in development, however, this renderer plugin is designed for use in both
academia, game engines, and for research. It is still at its low implementation, and there
is a ton of work to do on it before it can be released as a stable engine. 
  
Currently all resources and implementations within the engine source code is subject to change,
so keep in mind that this engine is barely newborn (Vulkan isn't even implemented yet,
OpenGL is 90% finished, and alot of the code needs to be abstracted to allow Vulkan and OpenGL plugins (along with soon to follow DirectX12 and Metal)). I only ask for patience until the engine is fully implemented, cleaned up,
and optimized. Contribution is always welcome!
  
The Design goal of this renderer is to allow the user to handle memory management, while the Engine merely uses the data
given to manipulate the objects it must render. **VERY STRONG** emphasis in avoiding dynamic allocation as much as possible.

  
# Credits and Honorable Mentions
Credits out to Joey De Vries and his tutorials on OpenGL, which has taught me,
through simple to understand, steps on learning graphics programming! check
out his tutorial website: http://learnopengl.com/#!Introduction
  
You should also check out his work in progress engine here as well, as he is implementing
much more advanced work than me! : https://github.com/JoeyDeVries/Cell
  
Notable mention to Koray Hagen and his delectable knowledge on Computer Graphics rendering,
helping me by pointing the way to certain rendering techniques with tangent space normal
mapping and Skew-Symmetric Matrices.