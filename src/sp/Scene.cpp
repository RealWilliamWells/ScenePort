#include "Scene.h"

namespace sp {

std::shared_ptr<Model> ModelManager::ImportModel(const std::string &path) {
  return std::shared_ptr<Model>();
}

std::shared_ptr<Model> ModelManager::ImportModel(const std::vector<Vector3<float>> &vertices,
                                                const std::vector<Vector3<U32>> &indices,
                                                const std::vector<Vector3<float>> &textureCoords,
                                                const std::vector<Vector3<float>> &normals,
                                                const Texture &texture) {
  //Model model = {.vertices=vertices, .indices=indices, .textureCoords=textureCoords, .normals=normals, .texture=texture};
  //m_Model.push_back(model);
  //return std::make_shared<Model>(model);
  return std::shared_ptr<Model>();
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

const std::vector<Entity>& Scene::getEntities() {
  return m_Entities;
}

std::shared_ptr<Scene> SceneManager::importScene(std::istream &input) {
  Scene scene;
  cereal::BinaryInputArchive inputArchive(input);
  inputArchive(scene);

  m_Scene.push_back(scene);
  return std::make_shared<Scene>(scene);
}

std::stringstream SceneManager::importFromFile(const std::string &fileName) {
  std::ifstream is(fileName, std::ios::binary);
  std::stringstream ss;
  ss << is.rdbuf();
  return ss;
}

std::stringstream SceneManager::exportScene(const Scene &scene) {
  std::stringstream ss;
  cereal::BinaryOutputArchive outArchive( ss );
  outArchive( scene );

  return ss;
}

void SceneManager::exportToFile(const std::string &sceneName, const std::stringstream &ss) {
  std::ofstream os(sceneName + ".oscene", std::ios::binary);
  if (os) {
    os << ss.str() << std::endl;
  }
  os.close();
}

};


