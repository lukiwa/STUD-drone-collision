#pragma once

#include <vector>
#include "Vector.hh"

/**
 * @brief Klasa modeluje pojecie obiektu geometrycznego
 *        Zawiera informacje o ilosci wymiarow obiektu, ilosci
 *        wierzcholkow oraz ich wspolrzednych
 *
 */
template <unsigned int DIMENSIONS_NUMB>
class GeometricObject {
   private:
   protected:
    GeometricObject() {}
    unsigned int vertex_numb;
    std::vector<Vector<DIMENSIONS_NUMB>> vertex_coords;
    std::vector<Vector<DIMENSIONS_NUMB>> org_vertex_coords;

   public:
    ~GeometricObject() {}
    /* -------------------------------------------------------------------------- */

    /**
     * @brief Umozliwia dostep do danego wierzcholka prostopadloscianu
     *
     * @param v_numb numer wierzcholka do ktorego chcemy sie dostac
     * @return Vector3D wektor wspolrzednych wierzcholka
     */
    inline Vector<DIMENSIONS_NUMB> operator[](unsigned int v_numb) const {
        assert(v_numb < vertex_numb);
        return vertex_coords[v_numb];
    }
    /**
     * @brief Umozliwia dostep i zmodyfikowanie danego weierzcholka
     *
     */
    inline Vector<DIMENSIONS_NUMB> &operator[](unsigned int v_numb) {
        assert(v_numb < vertex_numb);
        return vertex_coords[v_numb];
    }
    /* -------------------------------------------------------------------------- */
};
