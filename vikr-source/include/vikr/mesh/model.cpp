//
// Copyright (c) Mario Garcia. Under the MIT License.
//
#include <mesh/model.hpp>
#include <util/vikr_filesystem.hpp>
#include <util/vikr_log.hpp>


namespace vikr {


vvoid Model::LoadModel(std::string path) {
  Assimp::Importer importer;
  const aiScene *scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_FlipUVs);
  if (!scene || scene->mFlags == AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode) {
    VikrLog::DisplayMessage(VIKR_ERROR, "ASSIMP ERROR: " + std::string(importer.GetErrorString()));
    return;
  }
  directory = path.substr(0, path.find_last_of('/'));
  ProcessNode(scene->mRootNode, scene);
}


vvoid Model::ProcessNode(aiNode *node, const aiScene *scene) {
  for (vuint32 i = 0; i < node->mNumMeshes; ++i) {
    aiMesh *ai_mesh = scene->mMeshes[node->mMeshes[i]];
    Mesh *mesh = ProcessMesh(ai_mesh, scene);
    std::vector<Texture *> textures;
    if (ai_mesh->mMaterialIndex >= 0) {
      aiMaterial *material = scene->mMaterials[ai_mesh->mMaterialIndex]; 
      std::vector<Texture *> diffuse = 
                          LoadMaterialTextures(material , aiTextureType_DIFFUSE,
                                                "vikrTex_diffuse");
      textures.insert(textures.end(), diffuse.begin(), diffuse.end());
      std::vector<Texture *> specular = 
                          LoadMaterialTextures(material, aiTextureType_SPECULAR,
                                                "vikrTex_specular");
      textures.insert(textures.end(), specular.begin(), specular.end());
    }
    renderables.push_back(std::make_pair(mesh, std::move(textures)));
  }
  for (vuint32 i = 0; i < node->mNumChildren; ++i) {
    ProcessNode(node->mChildren[i], scene);
  }
}
} // vikr