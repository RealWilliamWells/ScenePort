#pragma once

#include "Base.h"

#ifndef NO_CEREAL
#include "cereal/types/vector.hpp"
#include "cereal/types/memory.hpp"
#include "cereal/archives/binary.hpp"
#endif

namespace sp {

// Represents a 4x4 matrix. Can be used a transformation matrix.
struct Matrix4 {
  std::vector<float> data;

#ifndef NO_CEREAL
  template<class Archive>
  void serialize(Archive &ar) {
    ar(data);
  }
#endif
};

// Contains the transformation data required to derive the transformation matrix.
struct Transform {
  Vector3<float> position;
  Vector3<float> rotation;
  Vector3<float> scale;

#ifndef NO_CEREAL
  template<class Archive>
  void serialize(Archive &ar) {
    ar(position, rotation, scale);
  }
#endif
};

// Contains the texture data.
struct Texture {
  // OpenGL ID of the texture.
  U32 textureID;

  U32 width;
  U32 height;
  U32 nrChannels;

  // Raw texture data.
  std::vector<U8> data;

#ifndef NO_CEREAL
  template<class Archive>
  void serialize(Archive &ar) {
    ar(width, height, nrChannels, data);
  }
#endif
};

// Contains the data required to load and render a mesh.
// A model can consist of multiple meshes.
// Each mesh contains a transformation matrix, which represents its position relative to Model space.
// Each mesh can only contain a single texture.
struct Mesh {
  std::string name;
  std::vector<Vector3<float>> vertices;
  std::vector<Vector3<U32>> indices;
  std::vector<Vector3<float>> textureCoords;
  std::vector<Vector3<float>> normals;
  Texture texture;
  Matrix4 transformationMatrix;

#ifndef NO_CEREAL
  template<class Archive>
  void serialize(Archive &ar) {
    ar(name, vertices, indices, textureCoords, normals, texture, transformationMatrix);
  }
#endif
};

struct Model {
  std::string name;
  std::vector<Mesh> meshes;

#ifndef NO_CEREAL
  template<class Archive>
  void serialize(Archive &ar) {
    ar(name, meshes);
  }
#endif
};

class Entity {
 public:
  Entity();
  Entity(const std::string &name, const Transform &transform, const std::shared_ptr<Model> &model);

  std::string name;
  std::shared_ptr<Model> model;
  Transform transform;

#ifndef NO_CEREAL
  template<class Archive>
  void serialize(Archive &ar) {
    ar(name, transform, model);
  }
#endif
};

struct Skybox {
  Texture front;
  Texture back;
  Texture left;
  Texture right;
  Texture up;
  Texture down;
};

class Scene {
 public:
  std::string name;

  void addEntity(const Entity &entity);
  const Entity &getEntity(const U8 &index);
  const std::vector<Entity> &getEntities();

#ifndef NO_CEREAL
  template<class Archive>
  void serialize(Archive &ar) {
    ar(name, m_Entities);
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
                                     const Texture &texture);
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
