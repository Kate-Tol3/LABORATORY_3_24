#include <stdexcept>
#include "Sequence.h"
#include "Exeptions.h"
#include "Exeptions+.h"
#include "MutableSequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"


template <typename T>
class SegmentedDeque {
private:
    int size = 0; //длина всего дека (количество элементов)
    int buff_size = 0; //длина сегмента
    DynamicArray<T*>* arr_ptr = nullptr; // массив указателей 
    int offset_tail = 0; // смещение в самом правом сегменте
    int offset_head = 0; // смещение в самом левом сегменте


private:
    void assertSizeCorrect() {
        if (size == 0) throw EmptyExeption;
    }
    void assertIndexCorrect(const int index) {
        if (index < 0 || index >= size) throw IndexOutOfRange;
    }

    //private methods

    void increaseFromHead() { // добавляем сегмент справа
        arr_ptr->append(new T[buff_size]);
    }

    void increaseFromTail() { // добавляем сегмент слева
        arr_ptr->prepend(new T[buff_size]);
    }

    void decreaseFromHead() { //удаляем сегмент справа
        arr_ptr->resize(arr_ptr->getSize() - 1);
    }

    void decreaseFromTail() { // удаляем сегмент  слева
        new_size = arr_ptr->getSize() - 1;

        DynamicArray<T*>* temp_arr = new DynamicArray<T*>(new_size);
        for (int i = 0; i < new_size; i++) {
            temp_arr->set(i, (*arr_ptr)[i + 1]);
        }
        delete arr_ptr;
        arr_ptr = temp_arr;
    }

    T& getElement(int index) const {
        assertIndexCorrect(index);
        int segment_ind = index / buff_size;
        index %= buff_size;
        if (offset_tail == 0) return (*arr_ptr)[segment_ind][index];
        if (offset_tail < index + 1) return (*arr_ptr)[segment_ind + 1][index - offset_tail];
        return (*arr_ptr)[segment_ind][(buff_size - offset_tail + index) % buff_size];
    }
    
    void deleteSegDeque() {
        if (size == 0) return;
        for (int i = 0; i < arr_ptr->getSize(); i++) {
            delete[](*arr_ptr)[i];
        }
        delete arr_ptr;
    }

public:

    //constructors

    SegmentedDeque(int buff_size = 4) : buff_size(buff_size) {};

    SegmentedDeque(const T& arr, int size, int buff_size = 4) : size(0), buff_size(buff_size) {
        if (size > 0):
            for (int i = 0; i < size; i++) {
                append(arr[i]);
            }
    };
    
    SegmentedDeque(const LinkedList<T>& other, int buff_size = 4) : buff_size(buff_size) {
        for (int i = 0; i < other.getLength(); ++i) {
            append(other.get(i));
        }
    }

    SegmentedDeque(const DynamicArray<T>& other, int buff_size = 4) : buff_size(buff_size) {
        for (int i = 0; i < other.getSize(); ++i) {
            append(other.get(i));
        }
    }

    SegmentedDeque(const SegmentedDeque<T>& other, int buff_size = 4) : buff_size(buff_size) {
        for (int i = 0; i < other.getLength(); ++i) {
            append(other.get(i));
        }
    }

    SegmentedDeque(const Sequence<T>& other, int buff_size = 4) : buff_size(buff_size) {
        for (int i = 0; i < other.getLength(); ++i) {
            append(other.get(i));
        }
    }

    //SegmentedDeque(T* array, int size, int bufSize = 4) : bufSize(bufSize) {
    //    for (int i = 0; i < size; ++i) {
    //        append(array[i]);
    //    }
    //}

    //destructor
    ~SegmentedDeque() {
        deleteSegDeque();
    }

    //overriden operators

    T& operator[](int index) { // для последовательного обращения по индексу
        return getElement(index);
    }

    const T& operator[](int index) const { // соответвует остальнам константным операторам [] (для наследования)
        return getElement(index);
    }

    SegmentedDeque<T>& operator=(const SegmentedDeque<T>& other) {
        deleteSegDeque();
        size = 0;
        offset_tail = 0;
        offset_head = 0;
        buff_size = other.buff_size;

        for (int i = 0; i < other.getLength(); i++) {
            append(other.get(i));
        }
        return *this;
    }


    //methods

    int getLength() const {
        return size;
    }

    const T& getFirst() const {
        assertSizeCorrect();
        return (*this)[0];
    }

    const T& getLast() const {
        assertSizeCorrect();
        return (*this)[size - 1];
    }


    const T& get(int index) const {
        assertIndexCorrect(index);
        return (*this)[index];
    }


    void set(int index, const T& item) {
        (*this)[index] = item;
    }

    void append(const T& item) {
        if (size == 0) arr_ptr = new DynamicArray<T*>(0);
        if (offset_head == 0) { // добавляем сегмент в конец
            increaseFromHead();
            (*arr_ptr)[arr_ptr->getSize() - 1][offset_head] = item;
            offset_head = 1;
        }
        else { // не добавляем сегмент
            (*arr_ptr)[arr_ptr->getSize() - 1][offset_head] = item;
            offset_head = (offset_head + 1) % buff_size;
        }
        size++;
        size++;
    }

    void prepend(const T& item) {
        if (size == 0) arr_ptr = new DynamicArray<T*>(0);
        if (offset_tail == 0) { // добавляем сегмент в начало
            increaseFromTail();
            (*arr_ptr)[0][buff_size - 1] = item; // заполняем элементы с конца сегмента
            offset_tail++;
        }
        else { // не добавляем сегмент
            (*arr_ptr)[0][buff_size - offset_tail - 1] = item;// заполняем элементы с конца сегмента
            offset_tail = (offset_tail + 1) % buff_size;
        }
        size++;
    }

    void insertAt(int index, const T& item) {
        assertIndexCorrect(index);
        if (size == 0) arr_ptr = new DynamicArray<T*>(0);
        if (index == size) {
            append(item);
            return;
        }
        prepend(0); // добавляем элемент вначале (item)
        for (int i = 0; i < index; i++) {
            (*this)[i] = (*this)[i + 1];
        }
        (*this)[index] = item;
    }

    void popHead() {
        assertSizeCorrect();
        if (offset_head == 1) { // удаляем последний сегмент
            decreaseFromHead();
            offset_head = 0;
        }
        else { // не удаляем последний сегмент
            if (offset_head == 0) {
                offset_head = buff_size;
            }
            --offset_head;
        }
        --size;
    }

    void popTail() {
        assertSizeCorrect();
        if (offset_tail == 1) { // удаляем первый сегмент
            decreaseFromTail();
            offset_tail = 0;
        }
        else { // не удаляем сегмент
            if (offset_tail == 0) {
                offset_tail = buff_size;
            }
            --offset_tail;
        }
        --size;
    }

    void removeAt(int index) {
        assertIndexCorrect(index);
        for (int i = index; i < (size - 1); i++) {
            (*this)[i] = (*this)[i + 1];
        }
        popHead();
    }

    int getBuffSize() const {
        return buff_size;
    }






























        int size()
        if tail > head
            return n - head + tail
        else
            return tail - head
            function pushBack(x : T) :
            if (head == (tail + 1) % n)
                T newDeque[n * 2]
                for i = 0 to n - 2
                    newDeque[i] = d[head]
                    head = (head + 1) % n
                    d = newDeque
                    head = 0
                    tail = n - 1
                    n *= 2
                    d[tail] = x
                    tail = (tail + 1) % n
                    T popBack() :
                    if (empty())
                        return error "underflow"
                        if (size() < n / 4)
                            T newDeque[n / 2]
                            int dequeSize = size()
                            for i = 0 to dequeSize - 1
                                newDeque[i] = d[head]
                                head = (head + 1) % n
                                d = newDeque
                                head = 0
                                tail = dequeSize
                                n /= 2
                                tail = (tail - 1 + n) % n
                                return d[tail]
                                function pushFront(x : T) :
                                if (head == (tail + 1) % n)
                                    T newDeque[n * 2]
                                    for i = 0 to n - 2
                                        newDeque[i] = d[head]
                                        head = (head + 1) % n
                                        d = newDeque
                                        head = 0
                                        tail = n - 1
                                        n *= 2
                                        head = (head - 1 + n) % n
                                        d[head] = x
                                        T popFront() :
                                        if (empty())
                                            return error "underflow"
                                            if (size() < n / 4)
                                                T newDeque[n / 2]
                                                int dequeSize = size()
                                                for i = 0 to dequeSize - 1
                                                    newDeque[i] = d[head]
                                                    head = (head + 1) % n
                                                    d = newDeque
                                                    head = 0
                                                    tail = dequeSize
                                                    n /= 2
                                                    T ret = d[head]
                                                    head = (head + 1) % n
                                                    return ret


};