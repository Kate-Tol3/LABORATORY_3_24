#pragma once

#include <stdexcept>
#include "Sequence.h"
#include "ImmutableSequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "Exceptions.h"
#include "Exceptions+.h"
#include "SegmentedDeque.h"

template <typename T>
class ImmutableSegmentedDeque : public ImmutableSequence<T> {
private:
    SegmentedDeque<T>* deque;

private:
    void assertSizeCorrect() const {
        if (deque->getLength() == 0) throw EmptyExeption();
    }
    void assertIndexCorrect(int index) const{
        if (index < 0 || index >= deque->getLength()) throw IndexOutOfRange();
    }

public:

    //constructors
    ImmutableSegmentedDeque(int buff_size = 4) : deque(new SegmentedDeque<T>(buff_size)) {}
    ImmutableSegmentedDeque(const Sequence<T>& other, int buff_size = 4) : deque(new SegmentedDeque<T>(other, buff_size)) {}
    ImmutableSegmentedDeque(T* array, int size, int buff_size = 4) : deque(new SegmentedDeque<T>(array, size, buff_size)) {}
    ImmutableSegmentedDeque(const LinkedList<T>& other, int buff_size = 4) : deque(new SegmentedDeque<T>(other, buff_size)) {}
    ImmutableSegmentedDeque(const DynamicArray<T>& other, int buff_size = 4) : deque(new SegmentedDeque<T>(other, buff_size)) {}
    ImmutableSegmentedDeque(const ImmutableSegmentedDeque<T>& other, int buff_size = 4) : deque(new SegmentedDeque<T>(*other.deque, buff_size)) {}

    //destructor

    ~ImmutableSegmentedDeque() override {
        delete deque;
    }

    //overriden operator

    const T& operator[](int index) const override{
        return (*deque)[index];
    }

    bool operator==(const ImmutableSequence<T>& other) override{ // не проверяет размер буфера
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
        return deque->getFirst();
    }

    const T& getLast() const override {
        return deque->getLast();
    }

    int getBuffSize() const {
        return deque->getBuffSize();
    }

    void print() const{
        deque->print();
    }

    ImmutableSegmentedDeque<T>* set(int index, const T& item) override {
        assertIndexCorrect(index);
        ImmutableSegmentedDeque<T>* new_deque = new ImmutableSegmentedDeque<T>(*this);
        new_deque->deque->set(index, item);
        return new_deque;
    }

    ImmutableSegmentedDeque<T>* append(const T& item) override {
        ImmutableSegmentedDeque<T>* new_deque = new ImmutableSegmentedDeque<T>(*this);
        new_deque->deque->append(item);
        return new_deque;
    }

    ImmutableSegmentedDeque<T>* prepend(const T& item) override {
        ImmutableSegmentedDeque<T>* new_deque = new ImmutableSegmentedDeque<T>(*this);
        new_deque->deque->prepend(item);
        return new_deque;
    }

    ImmutableSegmentedDeque<T>* insertAt(const T& item, int index) override {
        assertIndexCorrect(index);
        ImmutableSegmentedDeque<T>* new_deque = new ImmutableSegmentedDeque<T>(*this);
        new_deque->deque->insertAt(index, item);
        return new_deque;
    }

    ImmutableSegmentedDeque<T>* popHead() const {
        assertSizeCorrect();
        ImmutableSegmentedDeque<T>* new_deque = new ImmutableSegmentedDeque<T>(*this);
        new_deque->deque->popHead();
        return new_deque;
    }

    ImmutableSegmentedDeque<T>* popTail() const {
        assertSizeCorrect();
        ImmutableSegmentedDeque<T>* new_deque = new ImmutableSegmentedDeque<T>(*this);
        new_deque->deque->popTail();
        return new_deque;
    }

    ImmutableSegmentedDeque<T>* removeAt(int index) const {
        assertIndexCorrect(index);
        ImmutableSegmentedDeque<T>* new_deque = new ImmutableSegmentedDeque<T>(*this);
        new_deque->deque->removeAt(index);
        return new_deque;
    }

    ImmutableSegmentedDeque<T>* concat(const Sequence<T>& other) override {
        ImmutableSegmentedDeque<T>* new_deque = new ImmutableSegmentedDeque<T>(*this);
        for (int i = 0; i < other.getLength(); i++) {
            new_deque->deque->append(other.get(i));
        }
        return new_deque;
    }

    ImmutableSegmentedDeque<T> *getSubSequence(int startIndex, int endIndex) override{
        if (startIndex > endIndex || startIndex < 0 || endIndex >= getLength()) throw IndexOutOfRange();
        ImmutableSegmentedDeque<T>* new_deque = new ImmutableSegmentedDeque<T>(getBuffSize());
        for (int i = startIndex; i <= endIndex; i++) {
            new_deque->deque->append(get(i));
        }
        return new_deque;
    }
};

