#pragma once
#include <fstream>
#include <iostream>
#include "CuboidObstacle.hh"
#include "Drone.hh"
#include "GnuplotLink.hh"

#include <chrono>
#include <thread>

#define DEG_TO_RAD(degree) (degree * M_PI / 180.0)
#define RAD_TO_DEG(radians) (radians * 180.0 / M_PI)

/**
 * @brief Klasa modeluje pojecie sceny, tj. miejsca gdzie zostana utworzone obiekty
 *
 */
class Scene {
   private:
    std::list<std::shared_ptr<SceneObject>> scene_objects;
    std::vector<std::shared_ptr<Drone>> drones;
    std::shared_ptr<Drone> active_drone;

    PzG::GnuplotLink link;  // lacze do gnuplota pozwalajace na rysowanie bryl

    void DisplayRotors();
    void GnuplotConfiguration();

   public:
    Scene() = delete;
    Scene(PzG::GnuplotLink& gnuplot_link, const std::vector<std::shared_ptr<Drone>> drones_on_scene,
          const std::list<std::shared_ptr<SceneObject>> objects_on_scene);
    ~Scene() {}
    void Init();
    /* -------------------------------------------------------------------------- */
    void DisplayDrone();
    void Move(double distance, double tilt_angle);
    void Rotate(double rotation_angle);

    void AnimateMove(double distance, double tilt_angle, double rotors_speed = 5, unsigned int refresh_rate = 10);
    void AnimateRotation(double rotation_angle, double rotors_speed = 5, unsigned int refresh_rate = 10);

    void AddDroneToList(std::shared_ptr<Drone> drone);
    void AddObstacleToList(std::shared_ptr<SceneObject> obstacle);
    
    //FIXME dron nadal sie rysuje!
    void DeleteDrone(unsigned int drone_numb);

    /* -------------------------------------------------------------------------- */

    void WriteVertexToFile();
    /* -------------------------------------------------------------------------- */
    bool DetectCollision();
    void SwitchActiveDrone(unsigned int drone_numb);
};
