#include "UserInterface.hh"

using namespace std;

/**
 * @brief Inicializacja dzialania interfejsu uzytkownika
 *
 */
void UserInterface::Init(void) {
    Scene scene = SceneInit();
    scene.DisplayDrone();
    UIManager(scene);
}
/**
 * @brief Zarzadza wykonywaniem operacji na prostokacie przez uzytkownika
 *
 * @param link referencja do lacza do gnuplota
 * @param rectangle referncja do zainicializowanego prostokata
 */
void UserInterface::UIManager(Scene& scene) {
    DisplayMenu();
    int choice;
    do {
        choice = GetChoice();
        switch (choice) {
            case Rotate:
                RealiseRotation(scene);
                break;

            case Move:
                RealiseMove(scene);
                break;

            case MenuDisplay:
                DisplayMenu();
                break;
            case SwtichDrone:
                RealiseDroneSwitch(scene);
                break;
            case End:
                cout << endl << "Koniec dzialania programu" << endl << endl;
                break;

            case Unrecognised:
                cout << "Nierozpoznana opcja!" << endl;
                break;
        }
    } while (choice != End);
}

/**
 * @brief Wczytuje wybrana opcje od uzytkownika
 *
 * @return UserInterface::Choice wartosc wyliczeniowa wybranej opcji
 */
UserInterface::Choice UserInterface::GetChoice(void) const {
    char choice;
    cout << endl << "Twoj wybor? (w-menu) > ";
    cin >> choice;
    switch (choice) {
        case 'o':
            return Rotate;
            break;

        case 'j':
            return Move;
            break;

        case 'w':
            return MenuDisplay;
            break;
        case 'k':
            return End;
            break;
        case 's':
            return SwtichDrone;
            break;
        default:
            cin.ignore(100, '\n');
            return Unrecognised;
            break;
    }
}
/* -------------------------------------------------------------------------- */

/**
 * @brief Inicializuje scene, tj. prostopadloscian w ukladzie wspolrzednych
 *
 * @return Scene scena z prostopadloscianem
 */
Scene UserInterface::SceneInit(void) {
    PzG::GnuplotLink link;

    std::vector<std::shared_ptr<Drone>> drones_on_scene;
    std::list<std::shared_ptr<SceneObject>> objects_on_scene;

    auto drone1 = make_shared<Drone>(10, 10, 5, 5, Insert(25, 25, 25));
    drone1->AddMembersFilenames(link, 1);
    drones_on_scene.push_back(drone1);
    objects_on_scene.push_front(drone1);

    auto drone2 = make_shared<Drone>(10, 10, 5, 5, Insert(100, 75, 15));
    drone2->AddMembersFilenames(link, 2);
    drones_on_scene.push_back(drone2);
    objects_on_scene.push_front(drone2);

    auto drone3 = make_shared<Drone>(10, 10, 5, 5, Insert(80, 25, 25));
    drone3->AddMembersFilenames(link, 3);
    drones_on_scene.push_back(drone3);
    objects_on_scene.push_front(drone3);

    /* --------------------------- DODAWANIE PRZESZKOD -------------------------- */

    auto obst1 = make_shared<CuboidObstacle>();
    obst1->Init(Insert(50, 50, 50), 10, 50);
    obst1->AddFilename(link);
    objects_on_scene.push_back(obst1);

    /* -------------------------------------------------------------------------- */
    auto obst2 = make_shared<CuboidObstacle>();
    obst2->Init(Insert(20, 80, 30), 0, 60);
    obst2->AddFilename(link);
    objects_on_scene.push_back(obst2);
    /* -------------------------------------------------------------------------- */
    auto obst3 = make_shared<CuboidObstacle>();
    obst3->Init(Insert(75, 75, 25), 15, 50);
    obst3->AddFilename(link);
    objects_on_scene.push_back(obst3);

    auto obst4 = make_shared<CuboidObstacle>();
    obst4->Init(Insert(25, 50, 80), 50, 5);
    obst4->AddFilename(link);
    objects_on_scene.push_back(obst4);

    Scene scene(link, drones_on_scene, objects_on_scene);
    return scene;
}

/**
 * @brief Realizuje zadanie rotacji drona na scenie
 *
 * @param scene scena zawierajaca drona
 */
void UserInterface::RealiseRotation(Scene& scene) {
    double rotation_angle;
    GetRotationInfo(rotation_angle);
    scene.AnimateRotation(rotation_angle);
}

/**
 * @brief Pobiera od uzytkownika parametru obrotu
 *
 * @param out_angle kat obrotu
 */
void UserInterface::GetRotationInfo(double& out_angle) {
    std::cout << "Podaj kat rotacji w stopniach: ";
    std::cin >> out_angle;
}

/**
 * @brief Pobiera od uzytkownika parametry ruchu
 *
 * @param out_tilt_angle kat wznoszenia/opadania
 * @param out_distance dystans na jaki ma poleciec dron
 */
void UserInterface::GetMoveInfo(double& out_tilt_angle, double& out_distance) {
    cout << "Podaj dlugosc drogi przelotu i kat wznoszenia (+)/ opadania (-)." << endl;
    cout << "Dlugosc drogi: ";
    cin >> out_distance;

    cout << "Kat wznoszenia[stopnie]: ";
    cin >> out_tilt_angle;
}

/**
 * @brief Realizuje ruch drona na scenie
 *
 * @param scene scena zawierajaca drona
 */
void UserInterface::RealiseMove(Scene& scene) {
    double tilt_angle, distance;
    GetMoveInfo(tilt_angle, distance);
    scene.AnimateMove(distance, tilt_angle);
}
/**
 * @brief Realizuje zmiane aktywnego drona na scenie
 *
 * @param scene scene na ktorej znajduja sie drony
 */
void UserInterface::RealiseDroneSwitch(Scene& scene) {
    unsigned int drone_numb;
    GetDroneNumb(drone_numb);
    scene.SwitchActiveDrone(drone_numb);
}

/**
 * @brief Pobiera od uzytkownika numer drona do zmiany
 *
 * @param int numer drona na ktory ma zostac zmieniony numer drona
 */
void UserInterface::GetDroneNumb(unsigned int& out_drone_numb) {
    std::cout << "Podaj numer drona: ";
    std::cin >> out_drone_numb;
}

/**
 * @brief Wyswietla menu
 *
 */
void UserInterface::DisplayMenu(void) const {
    cout << endl;
    cout << "o - obrot drona" << endl;
    cout << "j - lot na wprost" << endl;
    cout << "w - wyswietl ponownie menu" << endl;
    cout << "s - zmiana aktywnego drona" << endl;
    cout << "k - koniec dzialania programu" << endl;
}
