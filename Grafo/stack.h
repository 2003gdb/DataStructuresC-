#pragma once

#include <iostream>

using namespace std;

template <typename t>
class NodoStack {
public:
    t dato;
    NodoStack<t> *next;

    NodoStack(t dato): dato(dato), next(nullptr) {}
};

template <typename t>
class Stack {
private:
    NodoStack<t> *top;
    
public:
    Stack(): top(nullptr) {}

    ~Stack() {}

    bool push (t dato) {
        NodoStack<t> *nuevoNodo = new(nothrow) NodoStack<t>(dato);

        if (!nuevoNodo) {
            return false;
        }

        if (!top) {
            top = nuevoNodo;
            return true;
        }

        nuevoNodo->next = top;
        top = nuevoNodo;
        return true;
    } 

    bool pop() {
        if (!top) {
            return false;
        }

        NodoStack<t> *tmp = top;
        top = top->next;
        delete tmp;

        return true;
    }

    bool isEmpty() {
        return top == nullptr;
    }

    t *getTop() {
        if (!top) {
            return nullptr;
        }
        return &top->dato;
    }

    void print() {
        NodoStack<t> *actual = top;

        while (actual) {
            cout << actual->dato << " ";
            actual = actual->next;
        }
        cout << "\n";
        }

};