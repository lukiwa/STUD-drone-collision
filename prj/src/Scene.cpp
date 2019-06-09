#include "Scene.hh"

Scene::Scene(PzG::GnuplotLink& gnuplot_link, const std::vector<std::shared_ptr<Drone>> drones_on_scene,
             const std::list<std::shared_ptr<SceneObject>> objects_on_scene)
    : scene_objects(objects_on_scene), drones(drones_on_scene), link(gnuplot_link) {
    active_drone = drones_on_scene.front();
    GnuplotConfiguration();
}

/**
 * @brief Konfiguracja gnuplota do rysowania bryl na scenie
 *
 */
void Scene::GnuplotConfiguration() {
    link.SetDrawingMode(PzG::DM_3D);
    link.Init();
    link.SetRangeX(0, 100);
    link.SetRangeY(0, 100);
    link.SetRangeZ(0, 90);
}

/**
 * @brief Wpisuje wspolrzedne obiektow na scenie do pliku
 *
 */
void Scene::WriteVertexToFile() {
    /*
    for (const std::shared_ptr<Drone>& w_drone : drones) {
        w_drone->WriteWertexToFile();
    }
    */
    for (const std::shared_ptr<SceneObject>& w_obst : this->scene_objects) {
        w_obst->WriteWertexToFile();
    }
}

/**
 * @brief Umozliwia rotacje drona BEZ ANIMACJI
 *
 * @param rotation_angle kat obrotu w stopniach
 */
void Scene::Rotate(double rotation_angle) {
    active_drone->Rotate(DEG_TO_RAD(rotation_angle));
    WriteVertexToFile();
    link.Draw();
}

/**
 * @brief Umozliwia ruch drona BEZ ANIMACJI
 *
 * @param distance dystans w poziomie na jaki ma poleciec dron
 * @param tilt_angle kat wznoszenia/opadania
 */
void Scene::Move(double distance, double tilt_angle) {
    assert(distance > 0);
    active_drone->Move(distance, DEG_TO_RAD(tilt_angle));
    WriteVertexToFile();
    link.Draw();
}
/**
 * @brief Umozliwia animacje ruchu drona
 *
 * @param distance dystans w poziomie
 * @param tilt_angle kat wznoszenia/opadania
 * @param rotors_speed predkosc rotorow, domyslnie 5 stopnia co 10ms
 * @param refresh_rate opoznienie zapisywania
 *        NOTE: Im mniejsza wartosc tym czesciej zapisywane sa wierzcholki - ruch jest szybszy
 *              Im wieksza wartosc tym rzadziej, ruch wolniejszy ale moga znikac krawedzie!
 */
void Scene::AnimateMove(double distance, double tilt_angle, double rotors_speed, unsigned int refresh_rate) {
    assert(distance >= 0);
    if (tilt_angle == 0) {
        // ruch tylko w pionie
        for (int i = 0; i < distance; ++i) {
            active_drone->Move(1, 0);
            DisplayDrone();
            if (DetectCollision()) break;

            std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate));

            active_drone->RotateAllRotors(DEG_TO_RAD(rotors_speed));
            DisplayRotors();
        }
    } else if (tilt_angle == 90) {
        for (int i = 0; i < tilt_angle; ++i) {
            active_drone->Move(1, DEG_TO_RAD(90));
            DisplayDrone();
            if (DetectCollision()) break;

            std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate));

            active_drone->RotateAllRotors(DEG_TO_RAD(rotors_speed));
            DisplayRotors();
        }
    } else if (tilt_angle == -90) {
        for (int i = tilt_angle; i < 0; ++i) {
            active_drone->Move(1, DEG_TO_RAD(-90));
            DisplayDrone();
            if (DetectCollision()) break;

            std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate));

            active_drone->RotateAllRotors(DEG_TO_RAD(rotors_speed));
            DisplayRotors();
        }
    }

    else if (tilt_angle > 0) {
        // ruch w poziomie
        for (int i = 0; i < distance; ++i) {
            active_drone->Move(1, 0);
            DisplayDrone();
            if (DetectCollision()) break;

            std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate));

            active_drone->RotateAllRotors(DEG_TO_RAD(rotors_speed));
            DisplayRotors();
        }  // ruch ww pionie
        for (int i = 0; i < tilt_angle; ++i) {
            active_drone->Move(1, DEG_TO_RAD(90));
            DisplayDrone();
            if (DetectCollision()) break;

            std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate));

            active_drone->RotateAllRotors(DEG_TO_RAD(rotors_speed));
            DisplayRotors();
        }
        /* -------------------------------------------------------------------------- */
    } else if (tilt_angle < 0) {
        for (int i = 0; i < distance; ++i) {
            active_drone->Move(1, 0);
            DisplayDrone();
            if (DetectCollision()) break;

            std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate));

            active_drone->RotateAllRotors(DEG_TO_RAD(rotors_speed));
            DisplayRotors();
        }
        for (int i = tilt_angle; i < 0; ++i) {
            active_drone->Move(1, DEG_TO_RAD(-90));
            DisplayDrone();
            if (DetectCollision()) break;

            std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate));

            active_drone->RotateAllRotors(DEG_TO_RAD(rotors_speed));
            DisplayRotors();
        }
    }
}

/**
 * @brief Animowana rotacja drona
 *
 * @param rotation_angle kat rotacji w stopniach
 * @param rotors_speed predkosc rotorow - domyslnie 5 stopnia co 10ms
 * @param refresh_rate opoznienie zapisywania
 *        NOTE: Im mniejsza wartosc tym czesciej zapisywane sa wierzcholki - ruch jest szybszy
 *              Im wieksza wartosc tym rzadziej, ruch wolniejszy ale moga znikac krawedzie!
 */
void Scene::AnimateRotation(double rotation_angle, double rotors_speed, unsigned int refresh_rate) {
    if (rotation_angle > 0) {
        for (int i = 0; i < rotation_angle; ++i) {
            active_drone->Rotate(DEG_TO_RAD(1));
            DisplayDrone();

            std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate));

            active_drone->RotateAllRotors(DEG_TO_RAD(-rotors_speed));
            DisplayRotors();
        }
    } else if (rotation_angle < 0) {
        for (int i = 0; i > rotation_angle; --i) {
            active_drone->Rotate(DEG_TO_RAD(-1));
            DisplayDrone();

            std::this_thread::sleep_for(std::chrono::milliseconds(refresh_rate));

            active_drone->RotateAllRotors(DEG_TO_RAD(rotors_speed));
            DisplayRotors();
        }
    }
}

bool Scene::DetectCollision() {
    for (const std::shared_ptr<SceneObject>& w_obj : this->scene_objects) {
        if (w_obj == active_drone) continue;
        if (w_obj->IsCollisionDetected(active_drone)) {
            std::cerr << "KOLIZJA" << std::endl;
            return true;
        }
    }
    return false;
}

/**
 * @brief Wyswietla drona na scenie
 *
 */
void Scene::DisplayDrone() {
    WriteVertexToFile();
    link.Draw();
}

/** NOTE  zapisuje wspolrzedne calej sceny!
 * @brief Wyswietla rotory drona na scenie
 *
 */
void Scene::DisplayRotors() {
    WriteVertexToFile();
    link.Draw();
}

/**
 * @brief Przelacza aktualnie uzywangeo drona
 *
 * @param drone_numb numer drona ktory ma byc teraz sterowany
 */
void Scene::SwitchActiveDrone(unsigned int drone_numb) {
    assert(drone_numb <= drones.size());
    active_drone = this->drones[drone_numb];
}

/**
 * @brief Dodaje drona do listy obketow sceny i wektora dronow
 *
 * @param drone dron ktory ma byc dodany
 */
void Scene::AddDroneToList(std::shared_ptr<Drone> drone) {
    scene_objects.push_back(drone);
    drones.push_back(drone);
    WriteVertexToFile();
    link.Draw();
}

/**
 * @brief Dodaje przeszkode do listy obketow
 *
 * @param obstacle przeszkoda ktora ma zostac dodana
 */
void Scene::AddObstacleToList(std::shared_ptr<SceneObject> obstacle) {
    scene_objects.push_back(obstacle);
    WriteVertexToFile();
    link.Draw();
}

/**
 * @brief Usuwa wybranego drona z listy
 * 
 * @param drone_numb 
 */
void Scene::DeleteDrone(unsigned int drone_numb) {
    auto postion = drones.begin() + drone_numb;

    if (drones.size() >= 2) {
        if (*(drones.begin() + drone_numb) != active_drone) {
            drones.erase(postion);
        } else {
            std::cerr << "Nie mozna usunac aktywnego drona!" << std::endl;
        }
    } else {
        std::cerr << "Zbyt malo dronow do usuniecia!" << std::endl;
    }
}