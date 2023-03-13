#include "Scene.h"

namespace tbd {

std::shared_ptr<Model> ModelManager::ImportModel(const std::string &path) {
  return std::shared_ptr<Model>();
}

std::shared_ptr<Model> ModelManager::ImportModel(const std::vector<Vector3<float>> &vertices,
                                                const std::vector<Vector3<U32>> &indices,
                                                const std::vector<Vector3<float>> &textureCoords,
                                                const std::vector<Vector3<float>> &normals) {
  return std::shared_ptr<Model>(
          new Model({.vertices=vertices, .indices=indices, .textureCoords=textureCoords, .normals=normals}));
}

void ModelManager::FreeUnusedModels(Scene scene) {

}

std::shared_ptr<Model> ModelManager::GetModel(U32 modelID) const {
  return std::shared_ptr<Model>();
}

};


