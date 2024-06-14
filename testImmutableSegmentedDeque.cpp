#include "TestImmutableSegmentedDeque.h"

void ImmutableSegmentedDequeTest::test(){
    testConstructors();
    testGet();
    testSet();
    testGetFirst();
    testGetLast();
    testGetLength();
    testAppend();
    testPrepend();
    testInsertAt();
    testPopHead();
    testPopTail();
    testRemoveAt();
    testGetBuffSize();
    testOperatorAccess();
    testOperatorEqual();
    testConcat();
    testGetSubSequence();
}

void ImmutableSegmentedDequeTest::testConstructors(){
    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;

    ImmutableSegmentedDeque<int> immut_deque1(buffSize);//default
    assert(immut_deque1.getBuffSize() == buffSize);
    assert(immut_deque1.getLength() == 0);

    ImmutableSegmentedDeque<int> immut_deque2(elems, length, buffSize);//immut_deque from array
    assert(immut_deque2.getBuffSize() == buffSize);
    assert(immut_deque2.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(immut_deque2.get(i) == elems[i]);
    }

    DynamicArray<int> array(elems, length);
    ImmutableSegmentedDeque<int> immut_deque3(array, buffSize);//immut_deque from DynamicArray
    assert(immut_deque3.getBuffSize() == buffSize);
    assert(immut_deque3.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(immut_deque3.get(i) == elems[i]);
    }

    LinkedList<int> list(elems, length);
    ImmutableSegmentedDeque<int> immut_deque4(list, buffSize);//immut_deque from LinkedList
    assert(immut_deque4.getBuffSize() == buffSize);
    assert(immut_deque4.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(immut_deque4.get(i) == elems[i]);
    }

    MutableArraySequence<int> sequence(elems, length);
    ImmutableSegmentedDeque<int> immut_deque5(sequence, buffSize);//immut_deque from Sequence
    assert(immut_deque5.getBuffSize() == buffSize);
    assert(immut_deque5.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(immut_deque5.get(i) == elems[i]);
    }

    ImmutableSegmentedDeque<int> immut_deque(elems, length, buffSize);
    ImmutableSegmentedDeque<int> immut_deque6(immut_deque, buffSize);//immut_deque copy
    assert(immut_deque6.getBuffSize() == immut_deque.getBuffSize());
    assert(immut_deque6.getLength() == immut_deque.getLength());
    for (int i = 0; i < length; i++) {
        assert(immut_deque6.get(i) == elems[i]);
    }

}

void ImmutableSegmentedDequeTest::testGet(){

    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;

    ImmutableSegmentedDeque<int> immut_deque(elems, length, buffSize);
    for (int i = 0; i < length; ++i) {
        assert(immut_deque.get(i) == elems[i]);
    }

    try {
        immut_deque.get(-1);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
    try {
        immut_deque.get(length);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
}

void ImmutableSegmentedDequeTest::testSet(){
    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;
    int index = 4;
    int value = 100;
    ImmutableSegmentedDeque<int> immut_deque(elems, length, buffSize);
    ImmutableSegmentedDeque<int>* result = immut_deque.set(index, value);
    assert(immut_deque.getLength() == result->getLength());
    assert(immut_deque.getBuffSize() == result->getBuffSize());
    for (int i = 0; i < index; i++) {
        assert(result->get(i) == elems[i]);
    }
    assert(result->get(index) == value);
    for (int i = index+1; i < result->getLength(); ++i) {
        assert(result->get(i) == elems[i]);
    }
    delete result;

    try {
        immut_deque.set(-1, value);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
    try {
        immut_deque.set(length, value);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
}

void ImmutableSegmentedDequeTest::testGetFirst(){

    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;
    int value = 100;
   
    ImmutableSegmentedDeque<int> immut_deque(elems, length, buffSize);
    assert(immut_deque.getFirst() == elems[0]);

    ImmutableSegmentedDeque<int>* immut_deque1 = immut_deque.prepend(value);
    assert(immut_deque1->getFirst() == value);
    delete immut_deque1;

    ImmutableSegmentedDeque<int> immut_deque2(buffSize);
    try {
        immut_deque2.getFirst();
        assert(false);
    } catch(IndexOutOfRange &ex) {}
}

void ImmutableSegmentedDequeTest::testGetLast(){
    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;
    int value = 100;
    
    ImmutableSegmentedDeque<int> immut_deque(elems, length, buffSize);
    assert(immut_deque.getLast() == elems[length - 1]);

    ImmutableSegmentedDeque<int>* immut_deque1 = immut_deque.append(value);
    assert(immut_deque1->getLast() == value);
    delete immut_deque1;

    ImmutableSegmentedDeque<int> immut_deque2(buffSize);
    try {
        immut_deque2.getLast();
        assert(false);
    } catch(IndexOutOfRange &ex) {}
};

void ImmutableSegmentedDequeTest::testGetLength(){
    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;
    
    ImmutableSegmentedDeque<int> immut_deque(elems, length, buffSize);
    assert(immut_deque.getLength() == length);

    SegmentedDeque<int> deque1(buffSize);
    assert(immut_deque.getLength() == 0);
}

void ImmutableSegmentedDequeTest::testAppend(){
    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;
    int value = 100;

    ImmutableSegmentedDeque<int> immut_deque1(elems, length, buffSize);

    ImmutableSegmentedDeque<int>* immut_deque2 = immut_deque1.append(value);
    assert(immut_deque2->getLength() == length + 1);
    assert(immut_deque2->getLast() == value);
    delete immut_deque2;

    ImmutableSegmentedDeque<int> immut_deque3;
    assert(immut_deque3.getLength() == 0);
    ImmutableSegmentedDeque<int>* immut_deque4 = immut_deque3.append(value);
    assert(immut_deque4->getLength() == 1);
    assert(immut_deque4->getLast() == value);
    delete immut_deque4;
}

void ImmutableSegmentedDequeTest::testPrepend(){
    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;
    int value = 100;

    ImmutableSegmentedDeque<int> immut_deque1(elems, length, buffSize);
    ImmutableSegmentedDeque<int>* immut_deque2 = immut_deque1.prepend(value);

    assert(immut_deque2->getLength() == length + 1);
    assert(immut_deque2->getFirst() == value);
    delete immut_deque2;

    ImmutableSegmentedDeque<int> immut_deque3;
    assert(immut_deque3.getLength() == 0);
    ImmutableSegmentedDeque<int>* immut_deque4 = immut_deque3.prepend(value);
    assert(immut_deque4->getLength() == 1);
    assert(immut_deque4->getFirst() == value);
    delete immut_deque4;
}

void ImmutableSegmentedDequeTest::testInsertAt(){

    
    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;
    int value = 100;


    int index = buffSize; //begnnig of segment
    ImmutableSegmentedDeque<int> immut_deque1(elems, length, buffSize);
    ImmutableSegmentedDeque<int>* immut_deque2 = immut_deque1.insertAt(index, value);
    assert(immut_deque2->getLength() == length + 1);
    assert(immut_deque1.getLength() == length);

    for (int i = 0; i < index; i++){
        assert(immut_deque2->get(i) == elems[i]);
    }
    assert(immut_deque2->get(index) == value);
    for (int i = index + 1; i < immut_deque2->getLength(); i++){
        assert(immut_deque2->get(i) == elems[i - 1]);
    }
    delete immut_deque2;

    index = buffSize - 1;//end of segment
    ImmutableSegmentedDeque<int> immut_deque3(elems, length, buffSize);
    ImmutableSegmentedDeque<int>* immut_deque4 = immut_deque3.insertAt(index, value);
    assert(immut_deque4->getLength() == length + 1);
    assert(immut_deque3.getLength() == length);

    for (int i = 0; i < index; i++){
        assert(immut_deque4->get(i) == elems[i]);
    }
    assert(immut_deque4->get(index) == value);
    for (int i = index + 1; i < immut_deque4->getLength(); i++){
        assert(immut_deque4->get(i) == elems[i - 1]);
    }
    delete immut_deque4;



    index = 0; // first index of deque
    ImmutableSegmentedDeque<int> immut_deque5(elems, length, buffSize);
    ImmutableSegmentedDeque<int>* immut_deque6 = immut_deque5.insertAt(index, value);
    assert(immut_deque6->getLength() == length + 1);
    assert(immut_deque5.getLength() == length);

    assert(immut_deque6->get(index) == value);
    for (int i = index + 1; i < immut_deque6->getLength(); i++){
        assert(immut_deque6->get(i) == elems[i - 1]);
    }
    delete immut_deque6;


    index = length; //last index of deque
    ImmutableSegmentedDeque<int> immut_deque7(elems, length, buffSize);
    ImmutableSegmentedDeque<int>* immut_deque8 = immut_deque7.insertAt(index, value);
    assert(immut_deque8->getLength() == length + 1);
    assert(immut_deque7.getLength() == length);

    for (int i = 0; i < index; i++){
        assert(immut_deque8->get(i) == elems[i]);
    }
    assert(immut_deque8->get(index) == value);
    delete immut_deque8;


    index = buffSize / 2; //middle of segment
    ImmutableSegmentedDeque<int> immut_deque9(elems, length, buffSize);
    ImmutableSegmentedDeque<int>* immut_deque10 = immut_deque9.insertAt(index, value);
    assert(immut_deque10->getLength() == length + 1);
    assert(immut_deque9.getLength() == length);

    for (int i = 0; i < index; i++){
        assert(immut_deque10->get(i) == elems[i]);
    }
    assert(immut_deque10->get(index) == value);
    for (int i = index + 1; i < immut_deque10->getLength(); i++){
        assert(immut_deque10->get(i) == elems[i - 1]);
    }
    delete immut_deque10;


    index = 0;
    ImmutableSegmentedDeque<int> immut_deque; //empty deque
    ImmutableSegmentedDeque<int>* immut_deque0 = immut_deque.insertAt(index, value);
    assert(immut_deque.getLength() == 0);
    assert(immut_deque0->getLength() == 1);

    assert(immut_deque0->get(0) == value);
    delete immut_deque0;

   
    ImmutableSegmentedDeque<int> deque(elems, length, buffSize);
    try {
        deque.insertAt(-1, value);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
    try {
        deque.insertAt(deque.getLength() + 1, value);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
}

void ImmutableSegmentedDequeTest::testPopHead(){

    int elems[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}; 
    int length = 15;
    int buffSize = 7;
    int value = 100;

    ImmutableSegmentedDeque<int> immut_deque1(elems, length, buffSize);
    ImmutableSegmentedDeque<int>* immut_deque2 = immut_deque1.popHead(); //removes edge

    assert(immut_deque2->getLength() == length - 1);
    assert(immut_deque1.getLength() == length);

    for (int i = 0; i < immut_deque2->getLength(); i++) {
        assert(immut_deque2->get(i) == elems[i]);
    }
    delete immut_deque2;


    int elems1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length1 = 10;
    int buffSize1 = 5;

    ImmutableSegmentedDeque<int> immut_deque3(elems1, length1, buffSize1);
    ImmutableSegmentedDeque<int>* immut_deque4 = immut_deque3.popHead(); // 2 el in segment

    assert(immut_deque4->getLength() == length - 1);
    assert(immut_deque3.getLength() == length);

    for (int i = 0; i < immut_deque4->getLength(); ++i) {
        assert(immut_deque4->get(i) == elems[i]);
    }
    delete immut_deque4;

    ImmutableSegmentedDeque<int> immut_deque0;
    try {
        
        immut_deque0.popHead();
        assert(false);
    } catch (IndexOutOfRange &ex) {}
}

void ImmutableSegmentedDequeTest::testPopTail(){
    int elems[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int length = 15;
    int buffSize = 7;

    ImmutableSegmentedDeque<int> immut_deque1(elems, length, buffSize);
    ImmutableSegmentedDeque<int>* immut_deque2 = immut_deque1.popTail();

    assert(immut_deque2->getLength() == length - 1);
    assert(immut_deque1.getLength() == length);

    for (int i = 0; i < immut_deque2->getLength(); ++i) {
        assert(immut_deque2->get(i) == elems[i + 1]);
    }
    delete immut_deque2;

    ImmutableSegmentedDeque<int> immut_deque0;
    try {
        
        immut_deque0.popHead();
        assert(false);
    } catch (IndexOutOfRange &ex) {}
}

void ImmutableSegmentedDequeTest::testRemoveAt(){
    int elems[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int length = 15;
    int buffSize = 7;

    int index = length - 1; // last element
    ImmutableSegmentedDeque<int> immut_deque1(elems, length, buffSize);
    ImmutableSegmentedDeque<int>* immut_deque2 = immut_deque1.removeAt(index);

    assert(immut_deque2->getLength() == length - 1);
    assert(immut_deque1.getLength() == length);

    for (int i = 0; i < immut_deque2->getLength(); i++) {
        assert(immut_deque2->get(i) == elems[i]);
    }
    delete immut_deque2;

    int elems1[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length1 = 11;
    int buffSize1 = 5;

    index = length1 / 2; // middle of deque
    ImmutableSegmentedDeque<int> immut_deque3(elems1, length1, buffSize1);
    ImmutableSegmentedDeque<int>* immut_deque4 = immut_deque3.removeAt(index);

    assert(immut_deque4->getLength() == length - 1);
    assert(immut_deque3.getLength() == length);


    for (int i = 0; i < index; i++){
        assert(immut_deque4->get(i) == elems[i]);   
    }

    for (int i = index; i < immut_deque4->getLength(); i++){
        assert(immut_deque4->get(i) == elems[i + 1]);   
    }
    delete immut_deque4;


    ImmutableSegmentedDeque<int> immut_deque0(elems1, length1, buffSize1);
    try {
        immut_deque0.removeAt(-1);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
    try {
        immut_deque0.removeAt(immut_deque0.getLength());
        assert(false);
    } catch (IndexOutOfRange &ex) {}

}

void ImmutableSegmentedDequeTest::testConcat(){
    int elems1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length1 = 10;
    int buffSize1 = 5;

    int elems2[7] = {10, 11, 12, 13, 14, 15, 16}; 
    int length2 = 7;
    int buffSize2 = 6;

    ImmutableSegmentedDeque<int> immut_deque1(elems1, length1, buffSize1);//full deque
    ImmutableSegmentedDeque<int> immut_deque2(elems2, length2, buffSize2);//full deque
    ImmutableSegmentedDeque<int>* result1 = immut_deque1.concat(immut_deque2);
    assert(result1->getLength() == (length1 + length2));

    for (int i = 0; i < length1; i++){
        assert(result1->get(i) == elems1[i]);
    }
    for (int i = length1; i < length2; i++){
        assert(result1->get(i) == elems2[i - length1]);
    }
    delete result1;


    ImmutableSegmentedDeque<int> immut_deque3(elems1, length1, buffSize1);// full deque
    ImmutableSegmentedDeque<int> immut_deque4;//empty deque
    ImmutableSegmentedDeque<int>* result2 = immut_deque3.concat(immut_deque4);
    assert(result2->getLength() == length1);

    for (int i = 0; i < length1; i++){
        assert(result2->get(i) == elems1[i]);
    }
    delete result2;


    ImmutableSegmentedDeque<int> immut_deque5;//empty deque
    ImmutableSegmentedDeque<int> immut_deque6(elems2, length2, buffSize2);// full deque
    ImmutableSegmentedDeque<int>* result3 = immut_deque5.concat(immut_deque6);
    assert(result3->getLength() == length2);

    for (int i = 0; i < length2; i++){
        assert(result3->get(i) == elems2[i]);
    }
    delete result3;

    ImmutableSegmentedDeque<int> immut_deque7;
    ImmutableSegmentedDeque<int> immut_deque8;
    ImmutableSegmentedDeque<int>* result4 = immut_deque7.concat(immut_deque8);
    assert(result4->getLength() == 0);
    delete result4;
}

void ImmutableSegmentedDequeTest::testGetSubSequence(){

    int elems[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int buffSize = 6;

    int startIndex = 3; // start < end
    int endIndex = 6;
    ImmutableSegmentedDeque<int> immut_deque1(elems, length, buffSize);
    Sequence<int>* result1 = immut_deque1.getSubSequence(startIndex, endIndex);
    assert(result1->getLength() == (endIndex - startIndex + 1));
    for (int i = 0; i < result1->getLength(); i++) {
        assert(result1->get(i) == elems[i + startIndex]);
    }
    delete result1;


    int startIndex = 4;
    int endIndex = 4; // start == end
    ImmutableSegmentedDeque<int> immut_deque2(elems, length, buffSize);
    Sequence<int>* result2 = immut_deque2.getSubSequence(startIndex, endIndex);
    assert(result2->getLength() == 1);
    assert(result2->getFirst() == elems[startIndex]);
    delete result2;

    ImmutableSegmentedDeque<int> immut_deque0(elems, length, buffSize);
    try {
        startIndex = - 1; // start < 0
        endIndex = 5;
        immut_deque0.getSubSequence(startIndex, endIndex);
        assert(false);
    } catch (IndexOutOfRange &ex) {}

    try {
        startIndex = 0;
        endIndex = length; // end == length
        immut_deque0.getSubSequence(startIndex, endIndex);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
    try {
        startIndex = 4;
        endIndex = 3; // start > end
        immut_deque0.getSubSequence(startIndex, endIndex);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
}

void ImmutableSegmentedDequeTest::testGetBuffSize(){
    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = 10;
    int buffSize = 5;
    SegmentedDeque<int> immut_deque(elems, length, buffSize);
    assert(immut_deque.getBuffSize() == buffSize);

    SegmentedDeque<int> immut_deque1;
    assert(immut_deque1.getBuffSize() == 4);
};

void ImmutableSegmentedDequeTest::testOperatorAccess(){
    int elems[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int length = 15;
    int buffSize = 7;

    ImmutableSegmentedDeque<int> immut_deque1(elems, length, buffSize);
    for (int i = 0; i < length; i++) {
        assert(immut_deque1[i] == elems[i]);
    }

    ImmutableSegmentedDeque<int> immut_deque0(elems, length, buffSize);
    try {
        immut_deque0[-1];
        assert(false);
    } catch (IndexOutOfRange &ex) {}
    try {
        immut_deque0[length];
        assert(false);
    } catch (IndexOutOfRange &ex) {}
}

void ImmutableSegmentedDequeTest::testOperatorEqual(){
   
    int elems[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int elems1[15] = {0, 2, 3, 4556, 56, 7, 9, 0, -1, -200, 12, 13, 14};
    int length = 15;
    int buffSize = 7;

    ImmutableSegmentedDeque<int> immut_deque1(elems, length, buffSize);
    ImmutableSegmentedDeque<int> immut_deque2(elems, length, buffSize);
    ImmutableSegmentedDeque<int> immut_deque3(elems + 1, length - 1, buffSize);
    ImmutableSegmentedDeque<int> immut_deque4(elems1, length, buffSize);
    ImmutableSegmentedDeque<int> immut_deque5(elems, length, buffSize + 1);
    ImmutableSegmentedDeque<int> immut_deque6;

    assert(immut_deque1 == immut_deque2);
    assert((immut_deque1 == immut_deque3) == false);
    assert((immut_deque1 == immut_deque4) == false);
    assert((immut_deque1 == immut_deque5) == false);
    assert((immut_deque1 == immut_deque6) == false);

}

