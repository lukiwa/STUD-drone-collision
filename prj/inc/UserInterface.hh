#pragma once

#include "ObjectFactory.hh"
#include "Scene.hh"
#include "SceneObject.hh"

#define DEG_TO_RAD(degree) (degree * M_PI / 180.0)

/**
 * @brief Klasa modeluje pojecie interfejsu uzytkownika
 *
 */
class UserInterface {
    enum Choice { Rotate, Move, MenuDisplay, SwtichDrone, End, Unrecognised };
    /* -------------------------------------------------------------------------- */
    void UIManager(Scene& scene);
    Choice GetChoice(void) const;

    /* -------------------------------------------------------------------------- */
    Scene SceneInit();

    /* -------------------------------------------------------------------------- */
    void RealiseRotation(Scene& scene);
    void GetRotationInfo(double& out_angle);
    void RealiseMove(Scene& scene);
    void GetMoveInfo(double& out_tilt_angle, double& out_distance);
    void RealiseDroneSwitch(Scene& scene);
    void GetDroneNumb(unsigned int& out_drone_numb);

    /* -------------------------------------------------------------------------- */

    void DisplayMenu(void) const;

   public:
    UserInterface() {}
    ~UserInterface() {}
    void Init(void);
};