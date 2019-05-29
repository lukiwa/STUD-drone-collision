#pragma once
#include <memory>
#include "Counter.hh"
// #include "Drone.hh"
#include "GnuplotLink.hh"
#include "Vector3D.hh"

class Drone;  // zeby uniknac zaleznosci cyklicznej
/**
 * @brief Modeluje pojecie obiektu sceny tj wszystkich przeszkod i robotow
 *
 */
class SceneObject : public Counter<SceneObject> {
   private:
   protected:
    std::string filename;

   public:
    using Counter<SceneObject>::GetCounter;
    using Counter<SceneObject>::GetCreated;

    SceneObject() { filename = "default"; }
    ~SceneObject() {}  // TODO wirtualny destruktor
    // TODO czy kolizja // TODO konstruktory??

    void AddFilename(PzG::GnuplotLink& link);

    virtual bool IsCollisionDetected(std::shared_ptr<Drone> drone) const = 0;
    virtual bool WriteWertexToFile() = 0;
    static void DisplayObjectsNumb();
};
