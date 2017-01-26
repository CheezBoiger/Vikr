//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_MODEL_LOADER_HPP
#define __VIKR_MODEL_LOADER_HPP


#include <vikr/resources/resource_manager.hpp>
#include <string>

struct aiNode;
struct aiScene;
struct aiString;
struct aiMaterial;
struct aiMesh;


namespace vikr {


class SceneNode;
class SceneComponent;
class RenderDevice;


/**
  Loads models for the renderer. this is accomplished using Assimp library.
  If we were to do this ourselves, it would be time consuming. 

  Credits out to Joey De Vries which is his implementation of the MeshLoader.
*/
class ModelLoader {
public:
  /**
    Creates a scene node.
  */
  static SceneNode *ImportModel(
    RenderDevice *device, 
    std::string path, 
    std::string name, 
    vbool dynamic
  );

private:
  static SceneNode *ProcessNode(RenderDevice *device
    , aiNode *node
    , const aiScene *scene
    , std::string dir
    , std::string name
    , vbool dynamic
  );

  static Mesh *ProcessMesh(
    RenderDevice *device, 
    aiMesh *mesh, 
    const aiScene *scene, 
    vbool dynamic
  );

  static Material *ParseMaterial(RenderDevice *device
    , aiMaterial *material
    , std::string dir
    , std::string name);

  static std::string ProcessPath(aiString *path, std::string dir);

  static std::vector<Texture *> loaded_textures;
};
} // vikr
#endif // __VIKR_MODEL_LOADER_HPP