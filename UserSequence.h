#pragma once
#include "Sequence.h" // для функции printSubsequence
#include "MutableArraySequence.h"
#include "Complex.h"
#include <string>
#include <iostream>
#include <stdexcept>

template <typename T>
class UserSequence {

private:

    MutableArraySequence<T>* sequence = new MutableArraySequence<T>;

public:

    ~UserSequence() {
        delete sequence;
    }
    
    UserSequence() = default;

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
    
    void setElement() {
        int index; 
        std::cout << "\nEnter index where set : ";
        getArgument(&index);
        std::cout << "\nEnter the value to set : " << std::endl;
        try {
            std::cin >> (*sequence)[index];
        } catch (IndexOutOfRange &ex) {}
    }

    void printElement() {
        int index; 
        std::cout << "\nEnter the index of element: ";
        getArgument(&index);
        try {
            std::cout << ((*sequence)[index]) << std::endl;
        } catch (IndexOutOfRange &ex) {}
    }

    void insertValue() {
        int index; 
        std::cout << "\nEnter index where insert : ";
        getArgument(&index);
        std::cout << "\nEnter the value to insert : ";
        try {
            T item;
            std::cin >> item;
            sequence->insertAt(item, index);
            std::cout << "\nThe element was successfully inserted.\n";
        } catch (IndexOutOfRange &ex) {}
    }

    void appendValue() {
        std::cout << "\nEnter the value to append: ";
        T item;
        std::cin >> item;
        sequence->append(item);  
    }

    void prependValue() {
        std::cout << "\nEnter the value to prepend: ";
        T item;
        std::cin >> item;
        sequence->prepend(item);
    }

    void getLength(){
        std::cout << sequence->getLength();
    }

    void printFirst() {
        try {
            std::cout << sequence->getFirst();
        } catch(IndexOutOfRange &ex) {}
    }

    void printLast() {
        try {
            std::cout << sequence->getLast();
        } catch(IndexOutOfRange &ex) {}
    }

    void printSequence() {
        try {
           sequence->print();
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
            Sequence<T>* subsequence = sequence->getSubSequence(start, end);
            subsequence->print();
            delete subsequence;  
        } catch (IndexOutOfRange &ex) {}
    }

    void fillSequence(){

        std::cout << "\nEnter size of your sequence: ";
        int length = 0;
        getArgument(&length);
        std::cout << "\nEnter values to fill your sequence:\n";
        T item;
        for (int i = 0; i < length; i ++){
            try{
                std::cin >> item;
                sequence->append(item);
            } catch(std::invalid_argument &ex){
            std::cout << "\nYou have entered invalid value.";
            }
            
        }
        std::cout << "\n";
    
    }
};

template <typename T>
class SequenceUI {

private:

    void showList() {
    std::cout << "Select action:\n"
        << "1  *** print sequence\n"
        << "2  *** print element\n"
        << "3  *** printFirst\n"
        << "4  *** printLast\n"
        << "5  *** insert element\n"
        << "6  *** set element\n"
        << "7  *** append element\n"
        << "8  *** prepend element\n"
        << "9  *** Print subSequence\n"
        << "10 *** get length of sequence\n"
        << "0  *** exit\n\n";
    }

    void SequenceMenu() {
        UserSequence<T> sequence;

        sequence.fillSequence();

        showList();

        std::string action;
        while (true) {
            std:: cout << "\nEnter action number from list: ";;
            std::cin >> action;
            if (action == "1") sequence.printSequence();
            else if (action == "2") sequence.printElement();
            else if (action == "3") sequence.printFirst();
            else if (action == "4") sequence.printLast();
            else if (action == "5") sequence.insertValue();
            else if (action == "6") sequence.setElement();
            else if (action == "7") sequence.appendValue();
            else if (action == "8") sequence.prependValue();
            else if (action == "9") sequence.printSubsequence();
            else if (action == "10") sequence.getLength();
            else if (action == "0") break;
        }
    }

public:

    std::string menu() {
        std::string action;
        SequenceMenu();
        std::cout << "To end the program type --> end.\n" << "If you want to start again --> again.\n";
        std::cin >> action;
        return action;
    }
};