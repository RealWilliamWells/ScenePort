//
// Created by william on 13/03/23.
//

#include "gtest/gtest.h"

#include "ExampleData.h"
#include "Scene.h"

#include <fstream>
#include <cereal/types/vector.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/archives/binary.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

namespace tbd {
    std::vector<U8> loadExampleTexture() {
      // Load texture file
      const std::string textureFile = "res/example/gfx/jesus.jpg";
      int width;
      int height;
      int nrChannels;
      stbi_set_flip_vertically_on_load(true);
      U8* textureDataPointer = stbi_load(textureFile.c_str(), &width, &height, &nrChannels, 0);

      U32 textureSize = width*height*nrChannels;

      std::vector<U8> textureData;
      textureData.reserve(textureSize);

      for (int i = 0; i < textureSize; i++) {
        textureData.push_back(textureDataPointer[i]); // add each element of the data to the vector
      }

      stbi_image_free(textureDataPointer);

      return textureData;
    }

    TEST (ModelManagerTest, ImportModelFromGivenValues) {
      ModelManager modelManager;

      std::shared_ptr<Model> model = modelManager.ImportModel(vertices, {}, textureCoords, {}, {});

      EXPECT_EQ(model->vertices.at(3).x, vertices.at(3).x);
    }

    TEST (SceneManagerTest, ExportAndLoadScene) {
      std::vector<U8> texture = loadExampleTexture();

      ModelManager modelManager;

      std::shared_ptr<Model> model = modelManager.ImportModel(vertices, {}, textureCoords, {}, texture);

      Entity entity("test", {.0f, .0f, .0f}, model);

      Scene scene;
      scene.name = "test";

      scene.addEntity(entity);

      // Export and import scene in binary
      SceneManager sceneManager;

      std::stringstream ss = sceneManager.exportScene(scene);
      sceneManager.exportToFile(scene.name, ss);

      std::shared_ptr<Scene> importedScene = sceneManager.importScene(ss);

      EXPECT_EQ(scene.getEntity(0).model->vertices.at(3).x,
                importedScene->getEntity(0).model->vertices.at(3).x);
    }

  TEST (SceneManagerTest, ImportSceneFromFile) {
    Scene scene;

    // Export and import scene in binary
    SceneManager sceneManager;

    std::stringstream input = sceneManager.importFromFile("res/example/scenes/test.oscene");

    std::shared_ptr<Scene> importedScene = sceneManager.importScene(input);

    EXPECT_EQ(0.5f, importedScene->getEntity(0).model->vertices.at(3).x);
  }

};