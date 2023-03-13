#pragma once

#include "Base.h"

#ifndef NO_CEREAL
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>
#endif

namespace tbd {

struct Transform {
  Vector3<float> position;
  Vector3<float> rotation;
  Vector3<float> scale;

#ifndef NO_CEREAL
  template <class Archive>
  void serialize( Archive & ar )
  {
    ar( position, rotation, scale );
  }
#endif
};

struct Model {
  // USED TO CHECK IF THE ASSET IS ALREADY LOADED IN MEMORY.
  U64 md5;

  // OpenGL ID buffer IDs
  U32 vao;
  U32 vbo;
  U32 ebo;

  // Include vertex data, with textures and normals etc...
  std::vector<Vector3<float>> vertices;
  std::vector<Vector3<U32>> indices;
  std::vector<Vector3<float>> textureCoords;
  std::vector<Vector3<float>> normals;

  // Texture file
  std::vector<U8> texture;

#ifndef NO_CEREAL
  template <class Archive>
  void serialize( Archive & ar )
  {
    ar( md5, vao, vbo, ebo, vertices, indices, textureCoords, normals, texture );
  }
#endif
};

class Entity {
 public:
  Entity();
  Entity(const std::string &name, const Transform &transform, const std::shared_ptr<Model> &model);

  std::string name;
  Transform transform;
  std::shared_ptr<Model> model;

#ifndef NO_CEREAL
  template <class Archive>
  void serialize( Archive & ar )
  {
    ar( name, transform, model );
  }
#endif
};

class Scene {
 public:
  std::string name;

  void addEntity(const Entity &entity);
  const Entity& getEntity(const U8 &index);
  const std::vector<Entity>& getEntities();

#ifndef NO_CEREAL
  template <class Archive>
  void serialize( Archive & ar )
  {
    ar( name, m_Entities );
  }
#endif

 private:
  std::vector<Entity> m_Entities;

};

class ModelManager {
 public:
  static ModelManager &Get() {
    static ModelManager s_Instance;
    return s_Instance;
  }

  std::shared_ptr<Model> ImportModel(const std::string &path);
  std::shared_ptr<Model> ImportModel(const std::vector<Vector3<float>> &vertices,
                                    const std::vector<Vector3<U32>> &indices,
                                    const std::vector<Vector3<float>> &textureCoords,
                                    const std::vector<Vector3<float>> &normals,
                                    const std::vector<U8> texture);
  void FreeUnusedModels(Scene scene);

  [[nodiscard]] std::shared_ptr<Model> GetModel(U32 modelID) const;

 private:
  std::vector<Model> m_Model;
};

class SceneManager {
public:
    static SceneManager &Get() {
      static SceneManager s_Instance;
      return s_Instance;
    }

    std::stringstream exportScene(const Scene &scene);
    std::shared_ptr<Scene> importScene(std::istream &input);

    void exportToFile(const std::string &sceneName, const std::stringstream &ss);
    std::stringstream importFromFile(const std::string &fileName);

    [[nodiscard]] std::shared_ptr<Model> GetScene(U32 sceneID) const;

private:
  std::vector<Scene> m_Scene;


};

};
