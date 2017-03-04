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
class ResourceManager;
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
    ResourceManager *mgr, 
    std::string path, 
    std::string name, 
    vbool dynamic
  );

private:
  static SceneNode *ProcessNode(
    RenderDevice *device,
    ResourceManager *mgr
    , aiNode *node
    , const aiScene *scene
    , std::string dir
    , std::string name
    , vbool dynamic
  );

  static Mesh *ProcessMesh(
    RenderDevice *device,
    ResourceManager *mgr, 
    aiMesh *mesh, 
    const aiScene *scene, 
    vbool dynamic
  );

  static Material *ParseMaterial(
    RenderDevice *device
    , ResourceManager *mgr
    , aiMaterial *material
    , std::string dir
    , std::string name);

  static std::string ProcessPath(aiString *path, std::string dir);
};
} // vikr
#endif // __VIKR_MODEL_LOADER_HPP