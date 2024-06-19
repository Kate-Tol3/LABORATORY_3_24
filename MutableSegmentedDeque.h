#pragma once

#include <stdexcept>
#include "Sequence.h"
#include "MutableSequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "SegmentedDeque.h"

template <typename T>
class MutableSegmentedDeque : public MutableSequence<T> {
private:
    SegmentedDeque<T>* deque;

private:
    void assertSizeCorrect() const {
        if (deque->getLength() == 0) throw EmptyExeption();
    }

public:

    //constructors

    MutableSegmentedDeque(int buff_size = 4) : deque(new SegmentedDeque<T>(buff_size)) {}
    MutableSegmentedDeque(const Sequence<T>& other, int buff_size = 4) : deque(new SegmentedDeque<T>(other, buff_size)) {}
    MutableSegmentedDeque(T* array, int size, int buff_size = 4) : deque(new SegmentedDeque<T>(array, size, buff_size)) {}
    MutableSegmentedDeque(const LinkedList<T>& other, int buff_size = 4) : deque(new SegmentedDeque<T>(other, buff_size)) {}
    MutableSegmentedDeque(const DynamicArray<T>& other, int buff_size = 4) : deque(new SegmentedDeque<T>(other, buff_size)) {}
    MutableSegmentedDeque(const MutableSegmentedDeque<T>& other, int buff_size = 4) : deque(new SegmentedDeque<T>(*other.deque, buff_size)) {}

    //destructor

    ~MutableSegmentedDeque() override {
        delete deque;
    }
    
    //overriden operators

    T& operator[](int index) { //для последовательного разыменования
        return (*deque)[index];
    }

    const T& operator[](int index) const override { //const [] наследуется
        return (*deque)[index];
    }

    MutableSegmentedDeque<T>& operator=(const MutableSegmentedDeque<T>& other) {
        (*deque) = (*other.deque);
    }

    bool operator==(const MutableSequence<T>& other) override{// не проверяет размер буфера
        if (this == &other) return true;
        if (this->getLength() == other.getLength()){
            for (int i = 0; i < this->getLength(); ++i) {
                if ((*this)[i] != (other)[i]) {
                    return false;
                }
            }
            return true;
        }
        return false;
    }

    //methods

    int getLength() const override {
        return deque->getLength();
    }

    const T& get(int index) const override {
        return (*this)[index];
    }

    const T& getFirst() const override {
        assertSizeCorrect();
        return deque->getFirst();
    }

    const T& getLast() const override {
        assertSizeCorrect();
        return deque->getLast();
    }

    void set(int index, const T& item) override {
        deque->set(index, item);
    }

    void append(const T& item) override {
        deque->append(item);
    }

    void prepend(const T& item) override {
        deque->prepend(item);
    }

    void insertAt( const T& item, int index) override {
        deque->insertAt(index, item);
    }

    void popHead() {
        deque->popHead();
    }

    void popTail() {
        deque->popTail();
    }

    void removeAt(int index) {
        deque->removeAt(index);
    }

    int getBuffSize() const {
        return deque->getBuffSize();
    }

    void print() const{
        deque->print();
    }

    MutableSegmentedDeque<T>* concat(const Sequence<T>& other) override {
        MutableSegmentedDeque<T>* new_deque = new MutableSegmentedDeque<T>(*this);
        for (int i = 0; i < other.getLength(); i++) {
            new_deque->append(other.get(i));
        }
        return new_deque;
    }

    MutableSegmentedDeque<T>* getSubSequence(int startIndex, int endIndex) override {
        if (startIndex > endIndex || startIndex < 0 || endIndex >= getLength()) throw IndexOutOfRange();
        MutableSegmentedDeque<T>* new_deque = new MutableSegmentedDeque<T>;
        for (int i = startIndex; i <= endIndex; i++) {
            new_deque->append(this->get(i));
        }
        return new_deque;
    }

    
};

