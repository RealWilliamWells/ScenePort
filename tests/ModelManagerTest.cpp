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

namespace tbd {

    TEST (ModelManagerTest, ImportModelFromGivenValues) {
      ModelManager modelManager;

      std::shared_ptr<Model> model = modelManager.ImportModel(vertices, {}, textureCoords, {});

      EXPECT_EQ(model->vertices.at(3).x, vertices.at(3).x);
    }

    TEST (ModelManagerTest, ExportAndLoadScene) {
      ModelManager modelManager;

      std::shared_ptr<Model> model = modelManager.ImportModel(vertices, {}, textureCoords, {});

      Entity entity("test", {.0f, .0f, .0f}, model);

      Scene scene;

      scene.addEntity(entity);

      // Export and import scene in binary
      SceneManager sceneManager;

      std::stringstream ss = sceneManager.exportScene(scene);

      std::shared_ptr<Scene> importedScene = sceneManager.importScene(ss);

      EXPECT_EQ(scene.getEntity(0).model->vertices.at(3).x,
                importedScene->getEntity(0).model->vertices.at(3).x);
    }

};