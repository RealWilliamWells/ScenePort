#include "Scene.h"

namespace tbd {

std::shared_ptr<Model> ModelManager::ImportModel(const std::string &path) {
  return std::shared_ptr<Model>();
}

std::shared_ptr<Model> ModelManager::ImportModel(const std::vector<Vector3<float>> &vertices,
                                                const std::vector<Vector3<U32>> &indices,
                                                const std::vector<Vector3<float>> &textureCoords,
                                                const std::vector<Vector3<float>> &normals) {
  Model model = {.vertices=vertices, .indices=indices, .textureCoords=textureCoords, .normals=normals};
  m_Model.push_back(model);
  return std::make_shared<Model>(model);
}

void ModelManager::FreeUnusedModels(Scene scene) {

}

std::shared_ptr<Model> ModelManager::GetModel(U32 modelID) const {
  return std::shared_ptr<Model>();
}

Entity::Entity() {}

Entity::Entity(const std::string &name, const Transform &transform, const std::shared_ptr<Model> &model) :
  name(name),
  transform(transform),
  model(model) {}

void Scene::addEntity(const Entity &entity) {
  m_Entities.push_back(entity);
}

const Entity& Scene::getEntity(const U8 &index) {
  return m_Entities.at(index);
}

std::shared_ptr<Scene> SceneManager::importScene(std::istream &input) {
  Scene scene;
  cereal::BinaryInputArchive inputArchive(input);
  inputArchive(scene);

  m_Scene.push_back(scene);
  return std::make_shared<Scene>(scene);
}

std::stringstream SceneManager::exportScene(const Scene &scene) {
  std::stringstream ss;
  cereal::BinaryOutputArchive outArchive( ss );
  outArchive( scene );

  return ss;
}

};


