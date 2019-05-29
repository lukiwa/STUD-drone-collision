#pragma once
#include "RightPrism.hh"
#include "SceneObject.hh"
#include "vector"

/**
 * @brief Definiuje pojecie przeszkody
 *
 */
class Obstacle : public SceneObject {
   private:
   protected:
   public:
    Obstacle() : SceneObject() {}
    ~Obstacle() {}
};
