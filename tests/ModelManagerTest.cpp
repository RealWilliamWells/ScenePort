//
// Created by william on 13/03/23.
//

#include "gtest/gtest.h"

#include "ExampleData.h"
#include "Scene.h"

TEST (ModelManagerTest, ImportModelFromGivenValues) {
  tbd::ModelManager modelManager;

  std::shared_ptr<tbd::Model> model = modelManager.ImportModel(vertices, {}, textureCoords, {});

  EXPECT_EQ(model->vertices.at(3).x, vertices.at(3).x);
}
