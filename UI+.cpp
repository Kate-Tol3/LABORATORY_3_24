#include "UI+.h"

std::string selectElementType() {
    std::cout << "Enter the type of elements in sequence from list:\n"
        << "* int *\n"
        << "* double *\n"
        << "* string *\n"
        << "* complex *\n\n";
    std::string elType;
    std::cin >> elType;
    while (elType != "int" && elType != "double" && elType != "string" && elType != "complex" && elType != "person") {
        std::cout << "Invalid type. Try again.\n";
        std::cin >> elType;
    }
    return elType;
}

std::string selectSequenceType() {
    std::cout << "Enter the type of sequence from list:\n"
        << "* deque *\n"
        << "* array *\n\n";
    std::string seqType;
    std::cin >> seqType;
    while (seqType != "deque" && seqType != "array") {
        std::cout << "Invalid type. Try again.\n";
        std::cin >> seqType;
    }
    return seqType;
}

void showUI() {

    std::cout << "This is the program to work with the deque and sequence. Let's start!\n\n\n";
    std::string seqType;
    std::string elType;
    std::string func;
    while (true){
        seqType = selectSequenceType();
        elType = selectElementType();
        if (seqType == "deque" && elType == "int") {
            DequeUI<int> ui;
            func = ui.start();
        } 
        else if (seqType == "deque" && elType == "double") {
            DequeUI<double> ui;
            func = ui.start();
        } 
        else if (seqType == "deque" && elType == "string") {
            DequeUI<std::string> ui;
            func = ui.start();
        } 
        else if (seqType == "deque" && elType == "complex") {
            DequeUI<Complex> ui;
            func = ui.start();
        } 
        
        else if (seqType == "array" && elType == "int") {
            SequenceUI<int> ui;
            func = ui.start();
        } 
        else if (seqType == "array" && elType == "double") {
            SequenceUI<double> ui;
            func = ui.start();
        } 
        else if (seqType == "array" && elType == "string") {
            SequenceUI<std::string> ui;
            func = ui.start();
        } 
        else if (seqType == "array" && elType == "complex") {
            SequenceUI<Complex> ui;
            func = ui.start();
        }
        while (func != "start" && func != "end") {
            std::cout << "Incorrect input. Try again.\n";
            std::cin >> func;
        }
        if (func == "end") break;  
    }
    std::cout << "\nThe end of program\n";
}


