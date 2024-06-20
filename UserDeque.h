#pragma once
#include "Sequence.h" 
#include "MutableSegmentedDeque.h"

#include "Complex.h"
#include <string>
#include <iostream>
#include <stdexcept>

template <typename T>
class UserDeque {

private:

    MutableSegmentedDeque<T>* deque = new MutableSegmentedDeque<T>;

public:

    ~UserDeque() {
        delete deque;
    }

    UserDeque() = default;

    //methods
    void getArgument(int* i_arg) {
        std::string s_arg;
        std::cin >> s_arg;
        try {
            *i_arg = std::stoi(s_arg);
        }
        catch (IndexOutOfRange &ex) {
            *i_arg = -10000000;
            std::cout << "Invalid input. Try again.";
            // std::cout << "Invalid type. Must be number. Try again.";
        }
    }

    void setValue() {
       int index; 
        std::cout << "\nEnter index where set : ";
        getArgument(&index);
        std::cout << "\nEnter the value to set : " << index << std::endl;
        try {
            std::cin >> (*deque)[index];
        } catch (IndexOutOfRange &ex) {}
        std::cin.ignore();
    }

    void printValue() {
        int index; 
        std::cout << "\nEnter the index of element : ";
        getArgument(&index);
        try {
            std::cout << deque->get(index) << std::endl;
        } catch (IndexOutOfRange &ex) {}
        std::cin.ignore();
    }

    void insertValue() {
        int index; 
        std::cout << "\nEnter index where insert : ";
        getArgument(&index);
        std::cout << "Enter the value to insert : ";
        try {
            T item;
            std::cin >> item;
            deque->insertAt(item, index);
            std::cout << "\nThe element was successfully inserted.\n";
        } catch (IndexOutOfRange &ex) {}
        //std::cin.ignore();
    }

    void appendValue() {
        std::cout << "\nEnter the value to append: ";
        T item;
        std::cin >> item;
        deque->append(item);
        std::cin.ignore();
    }

    void prependValue() {
        std::cout << "\nEnter the value to prepend: ";
        T item;
        std::cin >> item;
        deque->prepend(item);
        std::cin.ignore();
    }

    void getLength(){
        std::cout << deque->getLength();
    }

    void popHead() {
        try {
            deque->popHead();
            std::cout << "\nYou have removed last element.\n";
        } catch (IndexOutOfRange &ex) {}
    }

    void popTail() {
        try {
            deque->popTail();
            std::cout << "\nYou have removed first element.\n";
        } catch (IndexOutOfRange &ex) {}
    }

    void removeAt() {
        int index;
        std::cout << "\nEnter index of element to remove: ";
        std::cin >> index;
        try {
            deque->removeAt(index);
            std::cout << "\nYou removed element with index " << index << ".\n";
        } catch (IndexOutOfRange &ex) {}
        std::cin.ignore();
    }

    void printFirst() {
        try {
            std::cout << deque->getFirst() << "\n";
        } catch(IndexOutOfRange &ex) {}
    }

    void printLast() {
        try {
            std::cout << deque->getLast() << "\n";
        } catch(IndexOutOfRange &ex) {}
    }

    void printDeque() {
        try {
           deque->print();
        } catch(IndexOutOfRange &ex) {}   
    }

    void printSubsequence() {
        int start;
        int end;
        std::cout << "\nEnter start and end indexes of your subsequence: ";
        try {
            std::cout << "\nstart: " << std::endl;
            getArgument(&start);
            std::cout << "\nend: " << std::endl;
            getArgument(&end);
            Sequence<T>* subsequence = deque->getSubSequence(start, end);
            subsequence->print();
            delete subsequence; 
        } catch (IndexOutOfRange &ex) {}
        std::cin.ignore();
    }
};

template <typename T>
class DequeUI {

private:

    void showList() {
        std::cout << "Select action:\n"
        << "1  *** print deque\n"
        << "2  *** print element\n"
        << "3  *** set element\n"
        << "4  *** insert element\n"
        << "5  *** append element\n"
        << "6  *** prepend element\n"
        << "7  *** pop head\n"
        << "8  *** pop tail\n"
        << "9  *** remove at index\n"
        << "10 *** get first\n"
        << "11 *** get last\n"
        << "12 *** get length\n"
        << "13 *** print subsequence\n"
        << "0 *** exit\n\n";
    }

    void DequeMenu() {
        UserDeque<T> userDeque;

        showList();

        std::string action;
        while (true) {
            std::cout << "\nEnter the action: ";
            std::cin >> action;
            //std::cout << "action = " << action;
            if (action == "1") userDeque.printDeque();
            else if (action == "2") userDeque.printValue();
            else if (action == "3") userDeque.setValue();
            else if (action == "4") userDeque.insertValue();
            else if (action == "5") userDeque.appendValue();
            else if (action == "6") userDeque.prependValue();
            else if (action == "7") userDeque.popHead();
            else if (action == "8") userDeque.popTail();
            else if (action == "9") userDeque.removeAt();
            else if (action == "10") userDeque.printFirst();
            else if (action == "11") userDeque.printLast();
            else if (action == "12") userDeque.getLength();
            else if (action == "13") userDeque.printSubsequence();
            else if (action == "0") break;
        }
    }

public:

    std::string menu() {
        std::string action;
        DequeMenu();
        std::cout << "To end the program type --> end.\n" << "To start again type --> start.\n";
        std::cin >> action;
        return action;
    }
};

