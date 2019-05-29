#pragma once
#include "Cuboid.hh"

/**
 * @brief Modeluje pojecie korpusu drona
 *
 */
class DroneCorpus : public Cuboid {
   private:
    std::string filename;

   protected:
   public:
    /**
     * @brief Dodaje nazwe pliku do ktorego zostana zapisane wierzcholki korpusu
     *
     * @param filename nazwa pliki
     */
    inline void AddFilename(std::string filename) { this->filename = filename; }
    /**
     * @brief Zapisuje wspolrzedne do pliku     
     *
     * @return true jezeli udalo sie zapisac
     * @return false jezeli nie udalo sie zapisac
     */
    bool WriteVertexToFile() {
        if (filename == "default") {
            std::cerr << "Nie dodano nazwy korpusu!" << std::endl;
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
    DroneCorpus() : Cuboid() { filename = "default"; }
    ~DroneCorpus() {}
};