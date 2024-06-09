#pragma once

#include <stdexcept>
#include "Sequence.h"
#include "ImmutableSequence.h"
#include "DynamicArray.h"
#include "LinkedList.h"
#include "SegmentedDeque.h"

template <typename T>
class ImmutableSegmentedDeque : public ImmutableSequence<T> {
private:
    SegmentedDeque<T>* deque;

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

    const T& operator[](int index) const override {
        return (*deque)[index];
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

    ImmutableSegmentedDeque<T>* set(int index, const T& item) const override {
        if (index < 0 || index >= getLength()) throw std::out_of_range("Entered index is out of range.\n");
        ImmutableSegmentedDeque<T>* result = new ImmutableSegmentedDeque<T>(*this);
        result->deque->set(index, item);
        return result;
    }

    ImmutableSegmentedDeque<T>* append(const T& item) const override {
        ImmutableSegmentedDeque<T>* result = new ImmutableSegmentedDeque<T>(*this);
        result->deque->append(item);
        return result;
    }

    ImmutableSegmentedDeque<T>* prepend(const T& item) const override {
        ImmutableSegmentedDeque<T>* result = new ImmutableSegmentedDeque<T>(*this);
        result->deque->prepend(item);
        return result;
    }

    ImmutableSegmentedDeque<T>* insertAt(int index, const T& item) const override {
        if (index < 0 || index > getLength()) throw std::out_of_range("Entered index is out of range.\n");
        ImmutableSegmentedDeque<T>* result = new ImmutableSegmentedDeque<T>(*this);
        result->deque->insertAt(index, item);
        return result;
    }

    ImmutableSegmentedDeque<T>* popHead() const {
        if (getLength() == 0) throw std::out_of_range("You tried to delete element from the empty deque.\n");
        ImmutableSegmentedDeque<T>* result = new ImmutableSegmentedDeque<T>(*this);
        result->deque->popHead();
        return result;
    }

    ImmutableSegmentedDeque<T>* popTail() const {
        if (getLength() == 0) throw std::out_of_range("You tried to delete element from the empty deque.\n");
        ImmutableSegmentedDeque<T>* result = new ImmutableSegmentedDeque<T>(*this);
        result->deque->popTail();
        return result;
    }

    ImmutableSegmentedDeque<T>* removeAt(int index) const {
        if (index < 0 || index >= getLength()) throw std::out_of_range("Entered index is out of range");
        ImmutableSegmentedDeque<T>* result = new ImmutableSegmentedDeque<T>(*this);
        return result;
    }

    ImmutableSegmentedDeque<T>* concat(const Sequence<T>& other) const override {
        ImmutableSegmentedDeque<T>* result = new ImmutableSegmentedDeque<T>(*this);
        for (int i = 0; i < other.getLength(); ++i) {
            result->deque->append(other.get(i));
        }
        return result;
    }

    ImmutableSegmentedDeque<T>* getSubsequence(int startIndex, int endIndex) const override {
        if (startIndex > endIndex || startIndex < 0 || endIndex >= getLength()) throw std::out_of_range("Entered indices are out of range.\n");
        ImmutableSegmentedDeque<T>* result = new ImmutableSegmentedDeque<T>(getBufSize());
        for (int i = startIndex; i <= endIndex; ++i) {
            result->deque->append(get(i));
        }
        return result;
    }

    int getBufSize() const {
        return deque->getBufSize();
    }
};

