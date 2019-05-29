#include "SceneObject.hh"

void SceneObject::AddFilename(PzG::GnuplotLink& link) {
    std::string scene_object_filename =
        "dat/scene_obj/scene_obj" + std::to_string(GetCounter()) + ".dat";
    /* -------------------------------------------------------------------------- */

    this->filename = scene_object_filename;
    link.AddFilename(scene_object_filename.c_str());
}
/**
 * @brief Wyswietla ilosci stworzonych obiektow(uzywajac klasy Counter)
 *
 */
void SceneObject::DisplayObjectsNumb() {
    std::cout << std::endl;
    std::cout << "Laczna ilosc stworzonych obiektow sceny: ";
    std::cout << GetCreated();
    std::cout << std::endl;

    std::cout << "Ilosc istniejacych obiektow sceny ";
    std::cout << GetCounter();
    std::cout << std::endl;
}