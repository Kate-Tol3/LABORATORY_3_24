#include "testSegmentedDeque.h"

void SegmentedDequeTest::test(){
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
    testOperatorAssign();
};

void SegmentedDequeTest::testConstructors(){

    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = 10;
    int buffSize = 5;

    SegmentedDeque<int> deque1(buffSize); // default
    assert(deque1.getBuffSize() == buffSize);
    assert(deque1.getLength() == 0);

    SegmentedDeque<int> deque2(elems, length, buffSize); // deque from array
    assert(deque2.getBuffSize() == buffSize);
    assert(deque2.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(deque2.get(i) == elems[i]);
    }
    
    LinkedList<int> list(elems, length);
    SegmentedDeque<int> deque3(list, buffSize); // deque from LinkedList
    assert(deque3.getBuffSize() == buffSize);
    assert(deque3.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(deque3.get(i) == list.get(i));
    }

    DynamicArray<int> array(elems, length);
    SegmentedDeque<int> deque4(array, buffSize); // deque from DynamicArray
    assert(deque4.getBuffSize() == buffSize);
    assert(deque4.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(deque4.get(i) == array.get(i));
    }

    MutableArraySequence<int> array_seq(elems, length);
    SegmentedDeque<int> deque5(array_seq, buffSize); // deque from MutableArraySequence
    assert(deque5.getBuffSize() == buffSize);
    assert(deque5.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(deque5.get(i) == array_seq.get(i));
    }

    ImmutableArraySequence<int> imm_array_seq(elems, length);
    SegmentedDeque<int> deque6(imm_array_seq, buffSize); // deque from ImmutableArraySequence
    assert(deque6.getBuffSize() == buffSize);
    assert(deque6.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(deque6.get(i) == imm_array_seq.get(i));
    }

    MutableListSequence<int> list_seq(elems, length);
    SegmentedDeque<int> deque7(list_seq, buffSize); // deque from MutableListSequence
    assert(deque7.getBuffSize() == buffSize);
    assert(deque7.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(deque7.get(i) == list_seq.get(i));
    }

    ImmutableArraySequence<int> imm_list_seq(elems, length);
    SegmentedDeque<int> deque8(imm_list_seq, buffSize); // deque from ImmutableListSequence
    assert(deque8.getBuffSize() == buffSize);
    assert(deque8.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(deque8.get(i) == imm_list_seq.get(i));
    }

    SegmentedDeque<int> array_deque(elems, length);
    SegmentedDeque<int> deque9(array_deque, buffSize); // copy
    assert(deque9.getBuffSize() == buffSize);
    assert(deque9.getLength() == length);
    for (int i = 0; i < length; i++) {
        assert(deque9.get(i) == array_deque.get(i));
    }
};

void SegmentedDequeTest::testGet(){
    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = 10;
    int buffSize = 5;
    SegmentedDeque<int> deque(elems, length, buffSize);
    int value = 100;
    deque.append(value);
    assert(deque.get(length) == value);

    try {
        deque.get(-1);
        assert(false);
    }
    catch(IndexOutOfRange& ex){}

};

void SegmentedDequeTest::testSet(){
    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int new_elems[11] = {0, 1, 2, 3, 4, 5, 100, 7, 8, 9};
    int length = 10;
    int buffSize = 5;
    SegmentedDeque<int> deque(elems, length, buffSize);
    int index = 6;
    int value = 100;
    deque.set(index, value);
    
    assert(deque.getLength() == length);
    for (int i = 0; i < length; i++){
        std::cout << deque[i];
        assert(deque[i] == new_elems[i]);
    }
        
    try { //empty deque
        deque.set(-1, value);
        assert(false && "Must catch IndexOutOfRange");
    }
    catch(IndexOutOfRange& ex){}

};

void SegmentedDequeTest::testGetFirst(){
    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = 10;
    int buffSize = 5;
    SegmentedDeque<int> deque(elems, length, buffSize);
    assert(deque.getFirst() == elems[0]);

    try {
        SegmentedDeque<int> deque1(buffSize);
        deque1.getFirst();
        assert(false);
    } catch(IndexOutOfRange& ex){}
};

void SegmentedDequeTest::testGetLast(){
    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = 10;
    int buffSize = 5;
    SegmentedDeque<int> deque(elems, length, buffSize);
    assert(deque.getLast() == elems[0]);

    try {
        SegmentedDeque<int> deque1(buffSize);
        deque1.getLast();
        assert(false);
    } catch(IndexOutOfRange& ex){}
};

void SegmentedDequeTest::testGetLength(){
    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = 10;
    int buffSize = 5;
    SegmentedDeque<int> deque(elems, length, buffSize);
    assert(deque.getLength() == length);

    SegmentedDeque<int> deque1(buffSize);
    assert(deque1.getLength() == 0);
};

void SegmentedDequeTest::testAppend(){
    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = 10;
    int buffSize = 5;
    SegmentedDeque<int> deque(elems, length, buffSize);
    int value = 100;
    deque.append(value);
    assert(deque.getLength() == length+1);
    for (int i = 0; i < length; i++){
        assert(deque[i] == elems[i]);
    }
    assert(deque.getLast() == value);

    SegmentedDeque<int> deque1(buffSize);//empty deque
    deque1.append(value);
    assert(deque1.getLength() == 1);
    assert(deque1.getLast() == value);
};

void SegmentedDequeTest::testPrepend(){
    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = 10;
    int buffSize = 5;
    SegmentedDeque<int> deque(elems, length, buffSize);
    int value = 100;
    deque.prepend(value);
    assert(deque.getLength() == length+1);
    for (int i = 1; i < length + 1; i++){
        assert(deque[i] == elems[i]);
    }
    assert(deque.getFirst() == value);

    SegmentedDeque<int> deque1(buffSize);//empty deque
    deque1.prepend(value);
    assert(deque1.getLength() == 1);
    assert(deque1.getFirst() == value);
};

void SegmentedDequeTest::testInsertAt(){
    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = 10;
    int buffSize = 5;

    SegmentedDeque<int> deque(elems, length, buffSize);
    int value = 100;
    int index = buffSize;
    deque.insertAt(index, value);
    assert(deque.getLength() == length+1);
    for (int i = 1; i < index; i++){
        assert(deque[i] == elems[i]);
    }
    assert(deque.get(index) == value);

    for (int i = index + 1; i < length + 1; i++){
        assert(deque[i] == elems[i - 1]);
    }


    SegmentedDeque<int> deque1(elems, length, buffSize);
    index = buffSize - 1;
    deque1.insertAt(index, value);
    assert(deque1.getLength() == length+1);
    for (int i = 1; i < index; i++){
        assert(deque1[i] == elems[i]);
    }
    assert(deque1.get(index) == value);

    for (int i = index + 1; i < length + 1; i++){
        assert(deque1[i] == elems[i - 1]);
    }

    SegmentedDeque<int> deque2(elems, length, buffSize);
    index = 0;
    deque2.insertAt(index, value);
    assert(deque2.getLength() == length+1);
    for (int i = 1; i < index; i++){
        assert(deque2[i] == elems[i]);
    }
    assert(deque2.get(index) == value);

    for (int i = index + 1; i < length + 1; i++){
        assert(deque2[i] == elems[i - 1]);
    }

    SegmentedDeque<int> deque3(elems, length, buffSize);
    index = length;
    deque3.insertAt(index, value);
    assert(deque3.getLength() == length+1);
    for (int i = 1; i < index; i++){
        assert(deque3[i] == elems[i]);
    }
    assert(deque3.get(index) == value);

    for (int i = index + 1; i < length + 1; i++){
        assert(deque3[i] == elems[i - 1]);
    }

    SegmentedDeque<int> deque4(elems, length, buffSize);
    index = int(buffSize/2);
    deque4.insertAt(index, value);
    assert(deque4.getLength() == length+1);
    for (int i = 1; i < index; i++){
        assert(deque4[i] == elems[i]);
    }
    assert(deque4.get(index) == value);

    for (int i = index + 1; i < length + 1; i++){
        assert(deque4[i] == elems[i - 1]);
    }

    SegmentedDeque<int> deque5(buffSize);//empty deque
    deque5.insertAt(0, value);
    assert(deque5.getLength() == 1);
    assert(deque5.getFirst() == value);
    assert(deque5.getLast() == value);

    SegmentedDeque<int> deque6(elems, length, buffSize);//invalid index
    try {
        deque6.insertAt(-1, value);
        assert(false);
    } catch (IndexOutOfRange& ex) {}

};

void SegmentedDequeTest::testPopHead(){
    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = 10;
    int buffSize = 5;
    SegmentedDeque<int> deque1(elems, length, buffSize);
    deque1.popHead();
    assert(deque1.getLength() == length - 1);
    for (int i = 0; i < deque1.getLength(); ++i) {
        assert(deque1[i] == elems[i]);
    }

    int elems1[8] = {0, 1, 2, 3, 4, 5, 6, 7};
    int length1 = 8;
    SegmentedDeque<int> deque2(elems1, length1, buffSize);
    deque2.popHead();
    assert(deque2.getLength() == length1 - 1);
    for (int i = 0; i < deque2.getLength(); ++i) {
        assert(deque2[i] == elems[i]);
    }

    SegmentedDeque<int> deque3(buffSize);
    try {
        deque3.popHead();
        assert(false);
    } catch (IndexOutOfRange& ex) {}

};

void SegmentedDequeTest::testPopTail(){
    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = 10;
    int buffSize = 5;
    SegmentedDeque<int> deque1(elems, length, buffSize);
    deque1.popTail();
    assert(deque1.getLength() == length - 1);
    for (int i = 0; i < deque1.getLength(); ++i) {
        assert(deque1[i] == elems[i + 1]);
    }

    SegmentedDeque<int> deque2(elems + 1, length - 1, buffSize);
    deque2.prepend(elems[0]);
    deque2.popTail();
    assert(deque2.getLength() == length - 1);
    for (int i = 0; i < deque2.getLength(); i++) {
        deque2[i] = elems[i + 1];
    }

    SegmentedDeque<int> deque3(buffSize);
    try {
        deque3.popTail();
        assert(false);
    } catch (IndexOutOfRange& ex) {}
};

void SegmentedDequeTest::testRemoveAt(){
    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = 10;
    int buffSize = 5;
    length--;
    SegmentedDeque<int> deque(elems + 1, length, buffSize);
    deque.prepend(elems[0]);
    deque.removeAt(length);
    assert(deque.getLength() == length);
    for (int i = 0; i < deque.getLength(); ++i) {
        assert(deque[i] == elems[i]);
    }

    SegmentedDeque<int> deque1(elems + 1, length, buffSize);
    deque1.prepend(elems[0]);

    deque1.removeAt(0);
    assert(deque1.getLength() == length);
    for (int i = 0; i < deque1.getLength(); ++i) {
        assert(deque1[i] == elems[i + 1]);
    }

    SegmentedDeque<int> deque2(elems + 1, length, buffSize);
    deque2.prepend(elems[0]);
    int index = 3;

    deque2.removeAt(index);
    assert(deque2.getLength() == length);
    for (int i = 0; i < index; i++) {
        assert(deque2[i] == elems[i]);
    }
    for (int i = index; i < deque2.getLength(); i++) {
        assert(deque2[i] == elems[i + 1]);
    }

    SegmentedDeque<int> deque3(elems + 1, length, buffSize);
    deque3.prepend(elems[0]);

    try {
        deque3.removeAt(-1);
        assert(false);
    } catch (IndexOutOfRange& ex) {}
    try {
        deque3.removeAt(deque3.getLength());
        assert(false);
    } catch (IndexOutOfRange& ex) {}
};

void SegmentedDequeTest::testGetBuffSize(){
    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = 10;
    int buffSize = 5;
    SegmentedDeque<int> deque(elems, length, buffSize);
    assert(deque.getBuffSize() == buffSize);

    SegmentedDeque<int> deque1;
    assert(deque1.getBuffSize() == 4);
};

void SegmentedDequeTest::testOperatorAccess(){
    int elems[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length = 10;
    int buffSize = 5;

    SegmentedDeque<int> deque(elems, length, buffSize);
    assert(elems[0] == deque[0]);

    int value = 100;
    int index = 8;
    deque[index] = value;
    assert(deque[index] == value);

    SegmentedDeque<int> deque1(elems, length, buffSize);
    deque1.prepend(elems[0]);
    try {
        deque1[-1];
        assert(false);
    } catch (IndexOutOfRange& ex) {}
    try {
        deque1[length];
        assert(false);
    } catch (IndexOutOfRange& ex) {}
};

void SegmentedDequeTest::testOperatorAssign(){
    int elems1[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    int length1 = 10;
    int buffSize1 = 5;

    int elems2[6] = {0, 1, 2, 3, 4, 5};
    int length2 = 5;
    int buffSize2 = 3;

    SegmentedDeque<int> deque1(elems1, length1, buffSize1);
    SegmentedDeque<int> deque2(elems2, length2, buffSize2);

    deque1 = deque2;
    assert(deque1.getLength() == deque2.getLength());
    assert(deque1.getBuffSize() == deque2.getBuffSize());
    for (int i = 0; i < length2; ++i) {
        assert(deque2[i] == deque1[i]);
    }
};  