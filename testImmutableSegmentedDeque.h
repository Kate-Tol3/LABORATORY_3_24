#pragma once
#include <cassert>
#include <stdexcept>
#include "ImmutableSegmentedDeque.h"
#include "MutableArraySequence.h"
#include "LinkedList.h"
#include "DynamicArray.h"
#include "Sequence.h"

class ImmutableSegmentedDequeTest {
public:
    void test();
    void testConstructors();
    void testGet();
    void testSet();
    void testGetFirst();
    void testGetLast();
    void testGetLength();
    void testAppend();
    void testPrepend();
    void testInsertAt();
    void testPopHead();
    void testPopTail();
    void testRemoveAt();
    void testGetBuffSize();
    void testOperatorEqual();
    void testConcat();
    void testGetSubSequence();
    void testOperatorAccess();
    void testOperatorAssign(); 
};
