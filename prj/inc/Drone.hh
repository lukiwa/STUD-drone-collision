#pragma once

#include "Cuboid.hh"
#include "DroneRotor.hh"
#include "RegularHex.hh"
#include "SceneObject.hh"

#define ROTOR_NUMB 4

/**
 * @brief Klasa modeluje pojecie drona skladajacego sie z korpusu i ROTOR_NUMB
 *        illsci wirnikow
 *
 */
class Drone : public SceneObject {
   private:
    /* -------------------------------------------------------------------------- */

    // int rotor_numb = ROTOR_NUMB;  // ilosc rotorow drona
    double corpus_height, corpus_edge_length, rotor_height, rotor_edge_length;  // wymiary drona
    Vector3D corpus_middle_coords;  // wspolrzedne srodka korpusu
    Vector3D drone_middle_coords;   // wspolrzedne srodka drona
    double Zrotation;               // kat o jaki aktualnie obrocony jest dron
    DroneCorpus corpus;
    DroneRotor rotor[ROTOR_NUMB];

    unsigned int drone_numb;

    /* --------------------------------- METODY --------------------------------- */
    void AddRotationAngle(double rotation_angle);

   protected:
   public:
    Drone() = default;
    Drone(double height, double edge_length, double rotor_edge_length, double rotor_height,
          const Vector3D& corpus_middle_coords, PzG::GnuplotLink link, unsigned int drone_numb);
    ~Drone() = default;

    void AddMembersFilenames(PzG::GnuplotLink& link, unsigned int drone_numb);
    bool WriteWertexToFile() override;
    bool IsCollisionDetected(std::shared_ptr<Drone> drone) const override;

    void Zero();

    /* ------------------------------ METODY RUCHU ------------------------------ */
    void RotateCorpus(double rotation_angle);
    void RotateAllRotors(double rotation_angle);
    void Rotate(double rotation_angle);
    void Move(double distance, double tilt_angle);

    /* --------------------------------- GETTERS -------------------------------- */
    const Vector3D& GetDroneMiddle() const;
    double GetDroneHeight() const;
    double GetEdgeLength() const;
    unsigned int GetDroneNumb() const { return drone_numb; }
};
