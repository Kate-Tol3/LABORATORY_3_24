#include "testMutableSegmentedDeque.h"    
    
void MutableSegmentedDequeTest::test(){
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
    void testConcat();
};

void MutableSegmentedDequeTest::testConstructors(){
    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;

    MutableSegmentedDeque<int> mut_deque1(buffSize);//default
    assert(mut_deque1.getBuffSize() == buffSize);
    assert(mut_deque1.getLength() == 0);

    MutableSegmentedDeque<int> mut_deque2(elems, length, buffSize);//mut_deque from array
    assert(mut_deque2.getBuffSize() == buffSize);
    assert(mut_deque2.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(mut_deque2.get(i) == elems[i]);
    }

    DynamicArray<int> array(elems, length);
    MutableSegmentedDeque<int> mut_deque3(array, buffSize);//mut_deque from DynamicArray
    assert(mut_deque3.getBuffSize() == buffSize);
    assert(mut_deque3.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(mut_deque3.get(i) == elems[i]);
    }

    LinkedList<int> list(elems, length);
    MutableSegmentedDeque<int> mut_deque4(list, buffSize);//mut_deque from LinkedList
    assert(mut_deque4.getBuffSize() == buffSize);
    assert(mut_deque4.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(mut_deque4.get(i) == elems[i]);
    }

    MutableArraySequence<int> sequence(elems, length);
    MutableSegmentedDeque<int> mut_deque5(sequence, buffSize);//mut_deque from Sequence
    assert(mut_deque5.getBuffSize() == buffSize);
    assert(mut_deque5.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(mut_deque5.get(i) == elems[i]);
    }

    MutableSegmentedDeque<int> mut_deque(elems, length, buffSize);
    MutableSegmentedDeque<int> mut_deque0(mut_deque, buffSize);//mut_deque copy
    assert(mut_deque.getBuffSize() == mut_deque0.getBuffSize());
    assert(mut_deque.getLength() == mut_deque0.getLength());
    for (int i = 0; i < length; i++) {
        assert(mut_deque0.get(i) == elems[i]);
    }

}

void MutableSegmentedDequeTest::testGet(){

    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;

    MutableSegmentedDeque<int> mut_deque(elems, length, buffSize);
    for (int i = 0; i < length; i++) {
        assert(mut_deque.get(i) == elems[i]);
    }

    try {
        mut_deque.get(-1);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
    try {
        mut_deque.get(length);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
}

void MutableSegmentedDequeTest::testSet(){
    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;
    int index = 4;
    int value = 100;
    MutableSegmentedDeque<int> mut_deque(elems, length, buffSize);
    mut_deque.set(index, value);
    assert(mut_deque.getLength() == length);
    assert(mut_deque.getBuffSize() == buffSize);
    for (int i = 0; i < index; i++) {
        assert(mut_deque.get(i) == elems[i]);
    }
    assert(mut_deque.get(index) == value);
    for (int i = index+1; i < mut_deque.getLength(); ++i) {
        assert(mut_deque.get(i) == elems[i]);
    }

    try {
        mut_deque.set(-1, value);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
    try {
        mut_deque.set(length, value);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
}

void MutableSegmentedDequeTest::testGetFirst(){

    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;
    int value = 100;
   
    MutableSegmentedDeque<int> mut_deque(elems, length, buffSize);
    assert(mut_deque.getFirst() == elems[0]);

    mut_deque.prepend(value);
    assert(mut_deque.getFirst() == value);

    MutableSegmentedDeque<int> mut_deque1(buffSize);
    try {
        mut_deque1.getFirst();
        assert(false);
    } catch(IndexOutOfRange &ex) {}
}

void MutableSegmentedDequeTest::testGetLast(){
    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;
    int value = 100;
    
    MutableSegmentedDeque<int> mut_deque(elems, length, buffSize);
    assert(mut_deque.getLast() == elems[length - 1]);
    mut_deque.append(value);
    assert(mut_deque.getLast() == value);

    MutableSegmentedDeque<int> mut_deque1(buffSize);
    try {
        mut_deque1.getLast();
        assert(false);
    } catch(IndexOutOfRange &ex) {}
};

void MutableSegmentedDequeTest::testGetLength(){
    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;
    
    MutableSegmentedDeque<int> mut_deque(elems, length, buffSize);
    assert(mut_deque.getLength() == length);

    MutableSegmentedDeque<int> mut_deque1(buffSize);
    assert(mut_deque1.getLength() == 0);
}

void MutableSegmentedDequeTest::testAppend(){
    int elems[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}; 
    int length = 15;
    int buffSize = 7;
    int value = 100;

    MutableSegmentedDeque<int> mut_deque1(elems, length, buffSize);

    mut_deque1.append(value);
    assert(mut_deque1.getLength() == length + 1);
    assert(mut_deque1.getLast() == value);

    MutableSegmentedDeque<int> mut_deque2;
    assert(mut_deque2.getLength() == 0);
    mut_deque2.append(value);
    assert(mut_deque2.getLength() == 1);
    assert(mut_deque2.getLast() == value);
}

void MutableSegmentedDequeTest::testPrepend(){
    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;
    int value = 100;

    MutableSegmentedDeque<int> mut_deque1(elems, length, buffSize);
    mut_deque1.prepend(value);
    assert(mut_deque1.getLength() == length + 1);
    assert(mut_deque1.getFirst() == value);

    MutableSegmentedDeque<int> mut_deque2;
    assert(mut_deque2.getLength() == 0);
    mut_deque2.prepend(value);
    assert(mut_deque2.getLength() == 1);
    assert(mut_deque2.getFirst() == value);
}

void MutableSegmentedDequeTest::testInsertAt(){
    int elems[12] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11}; 
    int length = 12;
    int buffSize = 5;
    int value = 100;


    int index = buffSize; //begnnig of segment
    MutableSegmentedDeque<int> mut_deque1(elems, length, buffSize);
    assert(mut_deque1.getLength() == length);
    mut_deque1.insertAt(index, value);
    assert(mut_deque1.getLength() == length + 1);
    
    for (int i = 0; i < index; i++){
        assert(mut_deque1.get(i) == elems[i]);
    }
    assert(mut_deque1.get(index) == value);
    for (int i = index + 1; i < mut_deque1.getLength(); i++){
        assert(mut_deque1.get(i) == elems[i - 1]);
    }


    index = buffSize - 1;//end of segment
    MutableSegmentedDeque<int> mut_deque2(elems, length, buffSize);
    assert(mut_deque2.getLength() == length);
    mut_deque2.insertAt(index, value);
    assert(mut_deque2.getLength() == length + 1);
    
    for (int i = 0; i < index; i++){
        assert(mut_deque2.get(i) == elems[i]);
    }
    assert(mut_deque2.get(index) == value);
    for (int i = index + 1; i < mut_deque2.getLength(); i++){
        assert(mut_deque2.get(i) == elems[i - 1]);
    }


    index = 0; // first index of deque
    MutableSegmentedDeque<int> mut_deque3(elems, length, buffSize);
    assert(mut_deque3.getLength() == length);
    mut_deque3.insertAt(index, value);
    assert(mut_deque3.getLength() == length + 1);
    
    assert(mut_deque3.get(index) == value);
    for (int i = index + 1; i < mut_deque3.getLength(); i++){
        assert(mut_deque3.get(i) == elems[i - 1]);
    }


    index = length; //last index of deque
    MutableSegmentedDeque<int> mut_deque4(elems, length, buffSize);
    assert(mut_deque4.getLength() == length);
    mut_deque4.insertAt(index, value);
    assert(mut_deque4.getLength() == length + 1);

    for (int i = 0; i < index; i++){
        assert(mut_deque4.get(i) == elems[i]);
    }
    assert(mut_deque4.get(index) == value);


    index = buffSize / 2; //middle of segment
    MutableSegmentedDeque<int> mut_deque5(elems, length, buffSize);
    assert(mut_deque5.getLength() == length);
    mut_deque5.insertAt(index, value);
    assert(mut_deque5.getLength() == length + 1);

    for (int i = 0; i < index; i++){
        assert(mut_deque5.get(i) == elems[i]);
    }
    assert(mut_deque5.get(index) == value);
    for (int i = index + 1; i < mut_deque5.getLength(); i++){
        assert(mut_deque5.get(i) == elems[i - 1]);
    }

    index = 0;
    MutableSegmentedDeque<int> mut_deque; //empty deque
    assert(mut_deque.getLength() == 0);
    mut_deque.insertAt(index, value);
    assert(mut_deque.getLength() == 1);

    assert(mut_deque.get(0) == value);

   
    MutableSegmentedDeque<int> mut_deque0(elems, length, buffSize);
    try {
        mut_deque0.insertAt(-1, value);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
    try {
        mut_deque0.insertAt(mut_deque0.getLength() + 1, value);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
}

void MutableSegmentedDequeTest::testPopHead(){

    int elems[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14}; 
    int length = 15;
    int buffSize = 7;
    
    MutableSegmentedDeque<int> mut_deque1(elems, length, buffSize);
    assert(mut_deque1.getLength() == length);
    mut_deque1.popHead(); //removes edge
    assert(mut_deque1.getLength() == length - 1);
    
    for (int i = 0; i < mut_deque1.getLength(); i++) {
        assert(mut_deque1.get(i) == elems[i]);
    }


    int elems1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length1 = 10;
    int buffSize1 = 5;

    MutableSegmentedDeque<int> mut_deque2(elems1, length1, buffSize1);
    assert(mut_deque2.getLength() == length);
    mut_deque2.popHead(); // 2 el in segment
    assert(mut_deque2.getLength() == length - 1);

    for (int i = 0; i < mut_deque2.getLength(); ++i) {
        assert(mut_deque2.get(i) == elems[i]);
    }

    MutableSegmentedDeque<int> mut_deque0;
    try {
        mut_deque0.popHead();
        assert(false);
    } catch (IndexOutOfRange &ex) {}
}

void MutableSegmentedDequeTest::testPopTail(){
    int elems[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int length = 15;
    int buffSize = 7;

    MutableSegmentedDeque<int> mut_deque1(elems, length, buffSize);
    assert(mut_deque1.getLength() == length);
    mut_deque1.popTail();
    assert(mut_deque1.getLength() == length - 1);

    for (int i = 0; i < mut_deque1.getLength(); ++i) {
        assert(mut_deque1.get(i) == elems[i + 1]);
    }

    MutableSegmentedDeque<int> mut_deque0;
    try {
        mut_deque0.popHead();
        assert(false);
    } catch (IndexOutOfRange &ex) {}
}

void MutableSegmentedDequeTest::testRemoveAt(){
    int elems[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int length = 15;
    int buffSize = 7;

    int index = length - 1; // last element
    MutableSegmentedDeque<int> mut_deque1(elems, length, buffSize);
    assert(mut_deque1.getLength() == length);
    mut_deque1.removeAt(index);
    assert(mut_deque1.getLength() == length - 1);

    for (int i = 0; i < mut_deque1.getLength(); i++) {
        assert(mut_deque1.get(i) == elems[i]);
    }

    int elems1[11] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int length1 = 11;
    int buffSize1 = 5;

    index = length1 / 2; // middle of deque
    MutableSegmentedDeque<int> mut_deque2(elems1, length1, buffSize1);
    assert(mut_deque2.getLength() == length);
    mut_deque2.removeAt(index);
    assert(mut_deque2.getLength() == length - 1);
    
    for (int i = 0; i < index; i++){
        assert(mut_deque2.get(i) == elems[i]);   
    }

    for (int i = index; i < mut_deque2.getLength(); i++){
        assert(mut_deque2.get(i) == elems[i + 1]);   
    }


    MutableSegmentedDeque<int> mut_deque0(elems1, length1, buffSize1);
    try {
        mut_deque0.removeAt(-1);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
    try {
        mut_deque0.removeAt(mut_deque0.getLength());
        assert(false);
    } catch (IndexOutOfRange &ex) {}

}

void MutableSegmentedDequeTest::testConcat(){
    int elems1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length1 = 10;
    int buffSize1 = 5;

    int elems2[7] = {10, 11, 12, 13, 14, 15, 16}; 
    int length2 = 7;
    int buffSize2 = 6;

    MutableSegmentedDeque<int> mut_deque1(elems1, length1, buffSize1);//full deque
    MutableSegmentedDeque<int> mut_deque2(elems2, length2, buffSize2);//full deque
    MutableSegmentedDeque<int>* result1 = mut_deque1.concat(mut_deque2);
    assert(result1->getLength() == (length1 + length2));

    for (int i = 0; i < length1; i++){
        assert(result1->get(i) == elems1[i]);
    }
    for (int i = length1; i < length2; i++){
        assert(result1->get(i) == elems2[i - length1]);
    }
    delete result1;


    MutableSegmentedDeque<int> mut_deque3(elems1, length1, buffSize1);// full deque
    MutableSegmentedDeque<int> mut_deque4;//empty deque
    MutableSegmentedDeque<int>* result2 = mut_deque3.concat(mut_deque4);
    assert(result2->getLength() == length1);

    for (int i = 0; i < length1; i++){
        assert(result2->get(i) == elems1[i]);
    }
    delete result2;


    MutableSegmentedDeque<int> mut_deque5;//empty deque
    MutableSegmentedDeque<int> mut_deque6(elems2, length2, buffSize2);// full deque
    MutableSegmentedDeque<int>* result3 = mut_deque5.concat(mut_deque6);
    assert(result3->getLength() == length2);

    for (int i = 0; i < length2; i++){
        assert(result3->get(i) == elems2[i]);
    }
    delete result3;

    MutableSegmentedDeque<int> mut_deque7;
    MutableSegmentedDeque<int> mut_deque8;
    MutableSegmentedDeque<int>* result4 = mut_deque7.concat(mut_deque8);
    assert(result4->getLength() == 0);
    delete result4;
}

void MutableSegmentedDequeTest::testGetSubSequence(){

    int elems[14] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13};
    int length = 14;
    int buffSize = 6;

    int startIndex = 3; // start < end
    int endIndex = 6;
    MutableSegmentedDeque<int> mut_deque1(elems, length, buffSize);
    Sequence<int>* result1 = mut_deque1.getSubSequence(startIndex, endIndex);
    assert(result1->getLength() == (endIndex - startIndex + 1));
    for (int i = 0; i < result1->getLength(); i++) {
        assert(result1->get(i) == elems[i + startIndex]);
    }
    delete result1;


    startIndex = 4;
    endIndex = 4; // start == end
    MutableSegmentedDeque<int> mut_deque2(elems, length, buffSize);
    Sequence<int>* result2 = mut_deque2.getSubSequence(startIndex, endIndex);
    assert(result2->getLength() == 1);
    assert(result2->getFirst() == elems[startIndex]);
    delete result2;

    MutableSegmentedDeque<int> mut_deque0(elems, length, buffSize);
    try {
        startIndex = - 1; // start < 0
        endIndex = 5;
        mut_deque0.getSubSequence(startIndex, endIndex);
        assert(false);
    } catch (IndexOutOfRange &ex) {}

    try {
        startIndex = 0;
        endIndex = length; // end == length
        mut_deque0.getSubSequence(startIndex, endIndex);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
    try {
        startIndex = 4;
        endIndex = 3; // start > end
        mut_deque0.getSubSequence(startIndex, endIndex);
        assert(false);
    } catch (IndexOutOfRange &ex) {}
}

void MutableSegmentedDequeTest::testGetBuffSize(){
    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = 10;
    int buffSize = 5;
    SegmentedDeque<int> mut_deque(elems, length, buffSize);
    assert(mut_deque.getBuffSize() == buffSize);

    SegmentedDeque<int> mut_deque1;
    assert(mut_deque1.getBuffSize() == 4);
};

void MutableSegmentedDequeTest::testOperatorAccess(){
    int elems[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int length = 15;
    int buffSize = 7;

    MutableSegmentedDeque<int> mut_deque1(elems, length, buffSize);
    for (int i = 0; i < length; i++) {
        assert(mut_deque1[i] == elems[i]);
    }

    MutableSegmentedDeque<int> mut_deque0(elems, length, buffSize);
    try {
        mut_deque0[-1];
        assert(false);
    } catch (IndexOutOfRange &ex) {}
    try {
        mut_deque0[length];
        assert(false);
    } catch (IndexOutOfRange &ex) {}
}

void MutableSegmentedDequeTest::testOperatorEqual(){
   
    int elems[15] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14};
    int elems1[15] = {0, 2, 3, 4556, 56, 7, 9, 0, -1, -200, 12, 13, 14};
    int length = 15;
    int buffSize = 7;

    MutableSegmentedDeque<int> mut_deque1(elems, length, buffSize);
    MutableSegmentedDeque<int> mut_deque2(elems, length, buffSize);
    MutableSegmentedDeque<int> mut_deque3(elems + 1, length - 1, buffSize);
    MutableSegmentedDeque<int> mut_deque4(elems1, length, buffSize);
    MutableSegmentedDeque<int> mut_deque5(elems, length, buffSize + 1);
    MutableSegmentedDeque<int> mut_deque6;

    assert(mut_deque1 == mut_deque2);
    assert((mut_deque1 == mut_deque3) == false);
    assert((mut_deque1 == mut_deque4) == false);
    assert((mut_deque1 == mut_deque5) == false);
    assert((mut_deque1 == mut_deque6) == false);

}

