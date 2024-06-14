
#ifndef LAB2_MUTABLESEQUENCE_H
#define LAB2_MUTABLESEQUENCE_H

#include "Sequence.h"

template <class T>
class MutableSequence: public Sequence<T>{
public:

    //destructor
    virtual ~MutableSequence() = default;

    //methods
    virtual void append(const T& item) = 0;
    virtual void prepend(const T& item) = 0;
    virtual void insertAt(const T& item, int index) = 0;
    virtual void set(int index,const T& item) = 0;
    virtual bool operator==(const MutableSequence<T>& other) = 0;

};


#endif //LAB2_MUTABLESEQUENCE_H
