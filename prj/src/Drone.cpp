#include "Drone.hh"

/**
 * @brief Konstruuje nowy dron o zadanych parametrach
 *
 * @param height wysokosc korpusu drona
 * @param edge_length dlugosc boku korpusu
 * @param rotor_edge_length dlugosc boku rotora
 * @param rotor_height wysokosc rotora
 * @param corpus_middle_coords punkt srodkowy korpusu
 * @param link lacze do gnuplota
 * @param drone_numb numer drona
 */

Drone::Drone(double height, double edge_length, double rotor_edge_length, double rotor_height,
             const Vector3D& corpus_middle_coords, PzG::GnuplotLink link, unsigned int drone_numb)
    : corpus_height(height),
      corpus_edge_length(edge_length),
      rotor_height(rotor_height),
      rotor_edge_length(rotor_edge_length),
      corpus_middle_coords(corpus_middle_coords),
      Zrotation(0) {
    /* ----------------------- Inicializacja srodka drona ----------------------- */
    drone_middle_coords = corpus_middle_coords;
    drone_middle_coords[2] = drone_middle_coords[2] + rotor_height / 2;
    /* -------------------------------------------------------------------------- */
    corpus.Init(corpus_middle_coords, corpus_edge_length, corpus_height);
    rotor[0].Init(corpus[1], rotor_edge_length, rotor_height);
    rotor[1].Init(corpus[5], rotor_edge_length, rotor_height);
    rotor[2].Init(corpus[9], rotor_edge_length, rotor_height);
    rotor[3].Init(corpus[13], rotor_edge_length, rotor_height);

    AddMembersFilenames(link, drone_numb);
}

/**
 * @brief Dostep do srodka drona
 *
 * @return const Vector3D& wspolrzedne srodka drona
 */
const Vector3D& Drone::GetDroneMiddle() const { return drone_middle_coords; }

/**
 * @brief Dostep do calkowitej wysokosci drona
 *
 * @return double wyskosc drona
 */
double Drone::GetDroneHeight() const { return corpus_height + rotor_height; }

/**
 * @brief Dostep do calkowitej dlugosci drona(po przekatnej)
 *
 * @return double calkowita dlugosc przekatnej drona
 */
double Drone::GetEdgeLength() const {
    double rotor_diag_length = rotor[0][0].CalculateNewVector(rotor[0][1]).CalculateVectorLength();
    return corpus_edge_length + (2 * rotor_diag_length);
}

/**
 * @brief Rotacja korpusu drona o zadany kat
 *
 * @param rotation_angle kat rotacji
 */
void Drone::RotateCorpus(double rotation_angle) { corpus.Rotate(rotation_angle); }

/**
 * @brief Rotacja wszystkich rotorow drona
 *
 * @param rotation_angle kat rotacji
 */
void Drone::RotateAllRotors(double rotation_angle) {
    rotor[0].Rotate(corpus[1], rotation_angle);
    rotor[1].Rotate(corpus[5], rotation_angle);
    rotor[2].Rotate(corpus[9], rotation_angle);
    rotor[3].Rotate(corpus[13], rotation_angle);
}

/**
 * @brief Umozliwia rotacje drona wokol wlasnej osi o zadany kat
 *
 * @param rotation_angle zadany kat rotacji
 */
void Drone::Rotate(double rotation_angle) {
    corpus.Rotate(rotation_angle);
    RotateAllRotors(rotation_angle);
    AddRotationAngle(rotation_angle);
}

/**
 * @brief Ruch drona o zadana dlugosc przy danym kacie nachylenia
 *
 * @param distance dlugosc drogi
 * @param tilt_angle kat wznoszenia/opadania
 */
void Drone::Move(double distance, double tilt_angle) {
    assert(distance > 0);
    Vector3D move_vector;

    move_vector[0] = distance * std::sin(Zrotation) * std::cos(tilt_angle);
    move_vector[1] = distance * std::cos(Zrotation) * std::cos(tilt_angle);
    move_vector[2] = distance * std::sin(tilt_angle);

    corpus_middle_coords = corpus_middle_coords + move_vector;
    drone_middle_coords = drone_middle_coords + move_vector;

    corpus.MoveByVector(move_vector);
    for (int i = 0; i < ROTOR_NUMB; ++i) {
        rotor[i].MoveByVector(move_vector);
    }
}

/**
 * @brief Dodaje do obecnego kata obrotu nastepny kat
 * NOTE kat rotacji zawsze jest dodatni
 *      np kat -45 zamieniany jest na kat 315
 *      Ulatwia to obsluge sytuacju gdy kat przekroczy 360
 *
 * @param rotation_angle kat obrotu
 */
void Drone::AddRotationAngle(double rotation_angle) {
    if (rotation_angle < 0) {
        rotation_angle += 2 * M_PI;
    }

    Zrotation += rotation_angle;

    if (Zrotation > 2 * M_PI) {
        Zrotation -= 2 * M_PI;
    }
}

/**
 * @brief Zapisuje wspolrzedne drona do odpowiednich plikow
 *
 * @return true jezeli udalo sie zapisac
 * @return false jezeli nie udalo sie zapisac
 */
bool Drone::WriteWertexToFile() {
    if (!corpus.WriteVertexToFile()) {
        return false;
    }
    for (int i = 0; i < ROTOR_NUMB; ++i) {
        if (!rotor[i].WriteVertexToFile()) {
            return false;
        }
    }
    return true;
}

/**
 * @brief Dodaje nazwy plikow do zapsisu dla poszczegolnych skladowych drona
 *       NOTE dodaje tez naazwy plikow do lacza do gnuplota
 *
 * @param link lacze do gnuplota aby dodac tam nazwe pliku
 * @param drone_numb numer drona
 */
void Drone::AddMembersFilenames(PzG::GnuplotLink& link, unsigned int drone_numb) {
    /* -------------------------------------------------------------------------- */
    /*                                 DLA KORPUSU                                */
    /* -------------------------------------------------------------------------- */
    std::string corpus_filename = "dat/drone/corpus/corpus" + std::to_string(drone_numb) + ".dat";
    corpus.AddFilename(corpus_filename);
    link.AddFilename(corpus_filename.c_str());

    /* -------------------------------------------------------------------------- */
    /*                                 DLA ROTOROW                                */
    /* -------------------------------------------------------------------------- */
    std::string rotor_filename;
    for (int i = 0; i < ROTOR_NUMB; ++i) {
        rotor_filename = "dat/drone/rotor/rotor" + std::to_string(drone_numb) + std::to_string(i) + ".dat";
        rotor[i].AddFilename(rotor_filename);
        link.AddFilename(rotor_filename.c_str());
    }
}
/**
 * @brief Detekcja kolizji z innym dronem na scenie
 *
 * @param drone dron z ktroym ma byc wykryta kolizja
 * @return true jezeli wykryto kolizje
 * @return falsew przeciwnym wypadki
 */
bool Drone::IsCollisionDetected(std::shared_ptr<Drone> drone) const {
    double distance_between_middles =
        (this->drone_middle_coords.CalculateNewVector(drone->GetDroneMiddle())).CalculateVectorLength();
    if (distance_between_middles < (this->GetDroneHeight() / 2) + (drone->GetDroneHeight() / 2)) {
        return true;
    }

    if (distance_between_middles < (this->GetEdgeLength() / 2) + (drone->GetEdgeLength() / 2)) {
        return true;
    }
    return false;
}