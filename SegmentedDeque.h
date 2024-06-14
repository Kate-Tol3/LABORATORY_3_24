#include <stdexcept>

#include "Sequence.h"
#include "Exceptions.h"
#include "Exceptions+.h"
#include "MutableSequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"


template <typename T>
class SegmentedDeque {
private:
    int size = 0; //����� ����� ���� (���������� ���������)
    int buff_size = 0; //����� ��������
    DynamicArray<T*>* arr_ptr = nullptr; // ������ ���������� 
    int offset_tail = 0; // �������� � ����� ������ ��������
    int offset_head = 0; // �������� � ����� ����� ��������

    void assertSizeCorrect() const {
        if (size == 0) throw EmptyExeption();
    }
    void assertIndexCorrect(int index) const{
        if (index < 0 || index >= size) throw IndexOutOfRange();
    }

    //private methods

    void increaseFromHead() { // ��������� ������� ������
        arr_ptr->append(new T[buff_size]);
    }

    void increaseFromTail() { // ��������� ������� �����
        arr_ptr->prepend(new T[buff_size]);
    }

    void decreaseFromHead() { //������� ������� ������
        arr_ptr->resize(arr_ptr->getSize() - 1);
    }

    void decreaseFromTail() { // ������� �������  �����
        int new_size = arr_ptr->getSize() - 1;

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

    SegmentedDeque(const T* arr, int arr_size, int buff_size = 4) : size(0), buff_size(buff_size) {
        if (arr_size > 0) {
            for (int i = 0; i < arr_size; i++) {
                append(arr[i]);
            }
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
        for (int i = 0; i < other.getLength(); i++) {
            append(other.get(i));
        }
    }

    SegmentedDeque(const Sequence<T>& other, int buff_size = 4) : buff_size(buff_size) {
        for (int i = 0; i < other.getLength(); ++i) {
            append(other.get(i));
        }
    }

    //destructor
    ~SegmentedDeque() {
        deleteSegDeque();
    }

    //overriden operators

    T& operator[](int index) { // ��� ����������������� ��������� �� �������
        return getElement(index);
    }

    const T& operator[](int index) const { // ����������� ��������� ����������� ���������� [] (��� ������������)
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

    void print(){
        std::cout << (*this)[0];
        for (int i = 1; i < size; i++) {
            std::cout <<" "<< (*this)[i];
        }
    }

    void append(const T& item) {
        if (size == 0) arr_ptr = new DynamicArray<T*>(0);
        if (offset_head == 0) { // ��������� ������� � �����
            increaseFromHead();
            (*arr_ptr)[arr_ptr->getSize() - 1][offset_head] = item;
            offset_head = 1;
        }
        else { // �� ��������� �������
            (*arr_ptr)[arr_ptr->getSize() - 1][offset_head] = item;
            offset_head = (offset_head + 1) % buff_size;
        }
        size++;
    }

    void prepend(const T& item) {
        if (size == 0) arr_ptr = new DynamicArray<T*>(0);
        if (offset_tail == 0) { // ��������� ������� � ������
            increaseFromTail();
            (*arr_ptr)[0][buff_size - 1] = item; // ��������� �������� � ����� ��������
            offset_tail++;
        }
        else { // �� ��������� �������
            (*arr_ptr)[0][buff_size - offset_tail - 1] = item;// ��������� �������� � ����� ��������
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
        prepend(0); // ��������� ������� ������� (item)
        for (int i = 0; i < index; i++) {
            (*this)[i] = (*this)[i + 1];
        }
        (*this)[index] = item;
    }

    void popHead() {
        assertSizeCorrect();
        if (offset_head == 1){ // если элемент единственный в сегменте
            decreaseFromHead();
            offset_head = 0;
            return;
        }
        if (offset_head == 0) offset_head = buff_size;

        offset_head--;
        size--;
    }

    void popTail() {
        assertSizeCorrect();
        if (offset_tail == 1){ // если элемент единственный в сегменте
            decreaseFromTail();
            offset_tail = 0;
            return;
        }
        if (offset_tail == 0) offset_tail = buff_size;

        offset_tail--;
        size--;
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

};