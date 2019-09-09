#pragma once
#include "DroneCorpus.hh"
#include "RegularHex.hh"

/**
 * @brief Modeluje pojecie rotoru drona
 *
 */
class DroneRotor : public RegularHex {
   private:
    std::string filename;
    Vector3D mounting_point;  // poczatkowy punkt zamocowania rotora w dronie

   protected:
   public:
    /**
     * @brief Dodaje nazwe pliku do zapisu rotora
     *
     * @param filename nazwa pliku
     */
    inline void AddFilename(std::string filename) { this->filename = filename; }

    /**
     * @brief Zapisuje wierzcholki rotora do podanego wczesniej pliku
     *
     */
    bool WriteVertexToFile() {
        if (filename == "default") {
            std::cerr << "Nie dodano nazwy rotora!" << std::endl;
            return false;
        }
        std::ofstream file_stream;

        file_stream.open(filename);
        if (!file_stream.is_open()) {
            std::cerr << ":(  Operacja otwarcia do zapisu \"" << filename << "\"" << std::endl
                      << ":(  nie powiodla sie." << std::endl;
            return false;
        } else {
            WriteVertexAs4(file_stream);
            file_stream.close();
            return true;
        }
    }

    DroneRotor() : RegularHex() { filename = "default"; }
    ~DroneRotor() {}
    /**
     * @brief Rotacja rotora wokol osi OZ w stosunku do punktu mocowania
     *
     * @param mounting_point punkt mocowania, srodek dolnej podstawy
     * @param rotation_angle kat obrotu
     */
    void Rotate(const Vector3D& mounting_point, double rotation_angle) {
        Vector3D points_to_fix[2];
        points_to_fix[0] = mounting_point;
        RotateZAxis(rotation_angle);
        points_to_fix[1] =
            vertex_coords[3];  // dolny srodkowy punkt ma byc przeusniety do punktu mocowania
        Vector3D fix_vector = points_to_fix[1].CalculateNewVector(points_to_fix[0]);
        MoveByVector(fix_vector);
    }

    
};
