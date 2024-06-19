#include "Test.h"

void Test::testDynamicArray() {
    DynamicArrayTest tda;
    tda.test();
}

void Test::testLinkedList() {
    LinkedListTest tll;
    tll.test();
}

void Test::testMutableArraySequence() {
    MutableSequenceTest<MutableArraySequence> tmas;
    tmas.test();
}

void Test::testMutableListSequence() {
    MutableSequenceTest<MutableListSequence> tmls;
    tmls.test();
}

void Test::testImmutableArraySequence() {
    ImmutableSequenceTest<ImmutableArraySequence> tias;
    tias.test();
}

void Test::testImmutableListSequence() {
    ImmutableSequenceTest<ImmutableListSequence> tils;
    tils.test();
}

void Test::testImmutableSegmentedDeque() {
    ImmutableSegmentedDequeTest tisd;
    tisd.test();
}

void Test::testSegmentedDeque() {
    SegmentedDequeTest tsd;
    tsd.test();
}

void Test::testMutableSegmentedDeque() {
    MutableSegmentedDequeTest tmsd;
    tmsd.test();
}

void Test::TestAll() {

    testDynamicArray();
    testLinkedList();
    testMutableArraySequence();
    testMutableListSequence();
    testImmutableArraySequence();
    testImmutableListSequence();
    testSegmentedDeque();
    testImmutableSegmentedDeque();
    testMutableSegmentedDeque();

}