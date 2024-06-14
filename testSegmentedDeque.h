#pragma once
#include "testSegmentedDeque.h"
#include "Exceptions.h"
#include "MutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableArraySequence.h"
#include "ImmutableListSequence.h"
#include "Sequence.h"
#include "DynamicArray.h"
#include "SegmentedDeque.h"
#include <cassert>

class SegmentedDequeTest {
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
    void testOperatorAccess();
    void testOperatorAssign();  
};