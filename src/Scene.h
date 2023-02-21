#pragma once

#include "Base.h"

namespace tbd {

struct Transform {
  Vector3<float> position;
  Vector3<float> rotation;
  Vector3<float> scale;
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

};

class Entity {
 public:
  std::string name;
  Transform transform;
  std::shared_ptr<Model> model;
};

class Scene {
 public:
  std::string name;
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
  void FreeUnusedModels(Scene scene);

  [[nodiscard]] std::shared_ptr<Model> GetModel(U32 modelID) const;

 private:
  std::vector<Model> m_Model;
};

};
