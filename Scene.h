#pragma once

#include "Core/Base.h"
#include <glm/glm.hpp>

struct Transform {
  glm::vec3 position;
  glm::vec3 rotation;
  glm::vec3 scale;
};

struct Model {
  // USED TO CHECK IF THE ASSET IS ALREADY LOADED IN MEMORY.
  ambr::U64 UUID;

  // OpenGL ID buffer IDs
  ambr::U32 vertexArrayObject;
  ambr::U32 vertices;
  ambr::U32 indices;
  ambr::U32 textureCoords;
  ambr::U32 normals;

  // Include vertex data, with textures and normals etc...
};

class Entity {
 public:
  std::string name;
  Transform transform;
  ambr::U32 modelID;
};

class Scene {
 public:
  std::string name;
 private:
  std::vector<Entity> m_Entities;
};

class ModelManager {
 public:
  static ModelManager& Get() {
    static ModelManager s_Instance;
    return s_Instance;
  }

  const Model& GetModel(ambr::U32 modelID) const;
  void FreeUnusedModels(Scene scene);
  ambr::U32 ImportModel(const std::string& path);

 private:
  std::vector<Model> m_Model;
};