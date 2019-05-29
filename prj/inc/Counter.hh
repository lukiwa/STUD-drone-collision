#pragma once

/**
 * @brief Szablon sluzacy do zliczania obiektow danej klasy
 *
 * @tparam T typ klasy ktorej obiekty maja byc zliczane
 */
template <class T>
class Counter {
   private:
    static int counter;  // ilosc aktualnie zyjacych obiektow
    static int created;  // calkowita ilosc stworzoncyh obiektow

   public:
    Counter();
    Counter(const Counter<T>&);
    ~Counter();

    /**
     * @brief Get the Counter object
     *
     * @return int ilosc aktualnie stworzonych obiektow
     */
    static int GetCounter() { return counter; }
    /**
     * @brief Get the Created object
     *
     * @return int calkowita ilosc stworzonych obiektow
     */
    static int GetCreated() { return created; }
};

template <class T>
int Counter<T>::counter = 0;

template <class T>
int Counter<T>::created = 0;

template <class T>
Counter<T>::Counter() {
    ++counter;
    ++created;
}

template <class T>
Counter<T>::Counter(const Counter<T>&) {
    ++counter;
    ++created;
}

template <class T>
Counter<T>::~Counter() {
    --counter;
}
