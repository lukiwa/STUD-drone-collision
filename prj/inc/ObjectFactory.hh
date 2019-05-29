#include "SceneObject.hh"


/**
 * @brief Singleton fabryki obiektow, umozliwa tworzenie  
 *        odpowiednio zainicializowanych obiektow sceny
 */
class ObjectFactory {
   private:
    ObjectFactory() = default;
    ObjectFactory(const ObjectFactory&) = delete;
    ObjectFactory& operator=(const ObjectFactory&) = delete;

   public:
    ~ObjectFactory() = default;
    /**
     * @brief Dostep do singletonu fabryki obiektow
     *
     *
     * @return ObjectFactory* wskaznik na instancje fabryki obiektow
     */
    static ObjectFactory* Get() {
        static ObjectFactory instance;
        return &instance;
    }

    void Display() { std::cout << "chodzi" << std::endl; }
};
