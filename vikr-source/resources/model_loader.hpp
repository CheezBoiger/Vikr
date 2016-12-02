//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_MODEL_LOADER_HPP
#define __VIKR_MODEL_LOADER_HPP


#include <resources/resource_manager.hpp>
#include <string>

struct aiNode;
struct aiScene;
struct aiString;
struct aiMaterial;
struct aiMesh;


namespace vikr {


class SceneNode;
class SceneComponent;


/**
  Loads models for the renderer. this is accomplished using Assimp library.
  If we were to do this ourselves, it would be time consuming. 

  Credits out to Joey De Vries which is his implementation of the MeshLoader.
*/
class ModelLoader {
public:

  static SceneNode *ImportModel(std::string path, std::string name);

private:
  static SceneNode *ProcessNode(aiNode *node, const aiScene *scene, std::string dir);
  static Mesh *ProcessMesh(aiMesh *mesh, const aiScene *scene);
  static Material *ParseMaterial(aiMaterial *material, std::string dir);
  static std::string ProcessPath(aiString *path, std::string dir);
};
} // vikr
#endif // __VIKR_MODEL_LOADER_HPP