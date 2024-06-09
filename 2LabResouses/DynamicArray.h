
#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <iostream>
#include <cmath>
#include "Exceptions.h"

template<class T> void copyArray(T*,const T*, int);

template <class T>
class DynamicArray {
private:
    T *array;
    int arr_size;
    int capacity;

public:
    //constructors
    DynamicArray(T* items, const int count): arr_size(0), capacity(0),  array(nullptr) {
        if (count > 0) {
            arr_size = count;
            array = new T[count];
            for(int i = 0 ; i < arr_size; ++i) {
                array[i] = items[i];
            }
        }
    };

    explicit DynamicArray(const int size) : arr_size(0), capacity(0), array(nullptr) {//rename arg
        if (size > 0) {
            arr_size= size;
            array = new T[size];
        }
    };

    explicit DynamicArray(const DynamicArray<T> &other): arr_size(other.arr_size), capacity(other.capacity), array(nullptr){
       if (other.arr_size > 0 && other.array!=nullptr) {
           array = new T[other.arr_size];
           for (int i = 0; i < other.arr_size; ++i) {
               array[i] = other.array[i];
           }
       }
    };

    DynamicArray(): array(nullptr), arr_size(0), capacity(0){};

    //explicit DynamicArray(const Sequence<T>& other): arr_size(other.getLength()), array(new T[other.getLength()]) {
    //    for (int i = 0; i < arr_size; ++i) {
    //        set(i, other.get(i));
    //    }
    //}

    //destructor
    ~DynamicArray() {
        delete[] array;
    }

    //methods
    T& get(const int index) {
        if (index >= arr_size || index < 0) {
            throw IndexOutOfRange();
        }
        return (array[index]);
    }

    int getSize() const {
        return arr_size;
    }

    void set(const int index, const T& value) {
        if (index >= arr_size || index < 0) throw IndexOutOfRange();
        array[index] = value;
    }

    //void resize(const int new_size) {
    //    if (new_size < 0) throw IndexOutOfRange();
    //    if (new_size==arr_size) return;
    //    if (new_size == 0) {
    //        delete[] array;
    //        arr_size = 0;
    //        capacity = 0;
    //        array = nullptr;
    //        return;
    //    }

    //    // using more memory than we need to make resize more efficient
    //    if (new_size > capacity) {
    //        if (capacity == 0) capacity = 1;
    //        while (capacity <= new_size + 1) capacity *= 2;
    //        T *new_array = new T[capacity];
    //        if (array != nullptr) {
    //            copyArray<T>(new_array, array, arr_size);
    //            delete[] array;
    //        }
    //        array = new_array;
    //    }
    //    else if (new_size < capacity / 3) {
    //        while (capacity / 3 > new_size + 1) capacity /= 2;
    //        T *new_array = new T[capacity];
    //        if (array != nullptr) {
    //            copyArray<T>(new_array, array, new_size);
    //            delete[] array;
    //        }
    //        array = new_array;
    //    }
    //    arr_size = new_size;
    //}

    //изменена на стандартную для работы дека
    void resize(int new_size) {
        if (new_size < 0) throw IndexOutOfRange();
        if (new_size == arr_size) return;
        T* temp_arr = new T[new_size];
        int min_size = new_size < size ? new_size : size;
        for (int i = 0; i < min_size; ++i) {
            temp_arr[i] = array[i];
        }
        delete[] array;
        array = temp_arr;
        size = new_size;
        if (size == 0) {
            delete[] array;
            array = nullptr;
        }
    }

    void print(){
        for (int i = 0; i < arr_size;i++){
            if (i != arr_size - 1) std::cout << this->get(i) << " ";
            else std::cout << this->get(i);
        }
    }

    const T& operator[](int index) const{
        if (index < 0 || index > arr_size) throw IndexOutOfRange();
        return array[index];
    }

    T& operator[](int index){
        if (index < 0 || index > arr_size) throw IndexOutOfRange();
        return array[index];
    }

    bool operator==(const DynamicArray<T>& other) {
        if (this->array == other.array) return true;
        if (this->getSize() == other.getSize()){
            for (int i = 0; i < this->getSize(); ++i) {
                if ((*this)[i] != (other)[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }



    //фунции для дека (нет тестов)

    void append(const T& item) {
        resize(size + 1);
        array[size - 1] = item;
    }

    void prepend(const T& item) {
        T* temp_arr = new T[size + 1];
        for (int i = 1; i < (size + 1); i++) {
            temp_arr[i] = array[i - 1];
        }
        temp_arr[0] = item;

        delete[] array;
        array = temp_arr;
        size += 1;
    }

    void insertAt(int index, const T& item) {
        if (index < 0 || index > size) throw IndexOutOfRange;
        T* temp_arr = new T[size + 1];
        for (int i = 0; i < index; ++i) {
            temp_arr[i] = array[i];
        }
        temp_arr[index] = item;
        for (int i = index; i < size + 1; ++i) {
            temp_arr[i] = array[i - 1];
        }
        delete[] array;
        array = temp_arr;
        size += 1;
    }


};

template <typename T>
void copyArray(T *new_arr,const T* old_arr,int new_size) {
    for(int i = 0; i < new_size; ++i) {
        new_arr[i] = old_arr[i];
    }
};

#endif //DYNAMICARRAY_H
