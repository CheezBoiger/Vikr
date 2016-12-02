//
// Copyright (c) Mario Garcia, Under the MIT License.
//
#include <resources/model_loader.hpp>

// Assimp Importers.
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#include <scene/scene_node.hpp>
#include <shader/material.hpp>
#include <shader/texture.hpp>
#include <mesh/mesh.hpp>


namespace vikr {


SceneNode *ModelLoader::ImportModel(std::string path, std::string name) {
  return nullptr;
}
} // vikr