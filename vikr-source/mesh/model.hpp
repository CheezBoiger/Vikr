//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#ifndef __VIKR_MODEL_HPP
#define __VIKR_MODEL_HPP


#include <platform/vikr_api.hpp>
#include <platform/vikr_types.hpp>
#include <renderer/group_command.hpp>

// Going to need group command on this one...

// Assimp importers.
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

// Materials and mesh.
#include <mesh/mesh.hpp>
#include <shader/material.hpp>
#include <shader/texture.hpp>

// std headers.
#include <string>

namespace vikr {


/**
  Model is a class intended for importing various different 
  graphical models that are imported from graphics software like
  Maya, 3DSMax, and Blender. IT is abstract, for it must be 
  defined by the renderer api you plan to use.

  @deprecated
*/
class Model {
public:
  virtual ~Model() { }

  GroupCommand *GetGroupCommand() { return &m_command; }

protected:
  vvoid LoadModel(std::string path);
  vvoid ProcessNode(aiNode *node, const aiScene *scene);
  virtual Mesh *ProcessMesh(aiMesh *mesh, const aiScene *scene) = 0;
  virtual std::vector<Texture *> LoadMaterialTextures(aiMaterial *material, aiTextureType type, std::string type_name) = 0;

private:

  GroupCommand m_command;
  std::string directory;
  std::vector<std::pair<Mesh *, std::vector<Texture *> > > renderables;

};
} // vikr
#endif // __VIKR_MODEL_HPP