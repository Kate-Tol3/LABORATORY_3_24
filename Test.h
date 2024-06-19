#pragma once

#include "TestDynamicArray.h"
#include "TestLinkedList.h"
#include "TestMutableSequence.h"
#include "TestImmutableSequence.h"
#include "MutableArraySequence.h"
#include "MutableListSequence.h"
#include "ImmutableArraySequence.h"
#include "ImmutableListSequence.h"
#include "testSegmentedDeque.h"
#include "testImmutableSegmentedDeque.h"
#include "testMutableSegmentedDeque.h"

class Test {
public:
    void testDynamicArray();
    void testLinkedList();
    void testMutableArraySequence();
    void testMutableListSequence();
    void testImmutableArraySequence();
    void testImmutableListSequence();
    void testImmutableSegmentedDeque();
    void testSegmentedDeque();
    void testMutableSegmentedDeque();

    void TestAll();

};