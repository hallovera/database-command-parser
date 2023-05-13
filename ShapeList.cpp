#include "ShapeList.h"

ShapeList::ShapeList() {
    head = nullptr;
}

ShapeList::~ShapeList() {
    ShapeNode* current = head;
    ShapeNode* next;
    if (current != nullptr) {
        next = head->getNext();
    }
    
    while (current != nullptr) {
        delete current;
        current = next;
        if (next != nullptr) {
            next = next->getNext();
        }
    }
    head = nullptr;
}

ShapeNode* ShapeList::getHead() const {
    return head;
}

void ShapeList::setHead(ShapeNode* ptr) {
    head = ptr;
}

ShapeNode* ShapeList::find(string name) const {
    ShapeNode* current = head;
    while (current != nullptr) {
        if (current->getShape()->getName() == name) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

// Do WE have to check if s is nullptr??
void ShapeList::insert(ShapeNode* s) {
    ShapeNode* current = head;

    if (current == nullptr) {
        head = s;
        s->setNext(nullptr);
        return;
    }

    // Check if this works for all edge cases
    while (current->getNext() != nullptr) {
        current = current->getNext();
    }
    current->setNext(s);
    s->setNext(nullptr);
}

ShapeNode* ShapeList::remove(string name) {
    ShapeNode* current = head;
    ShapeNode* previous = nullptr;

    while (current != nullptr) {
        if (current->getShape()->getName() == name) {
            if (previous == nullptr) {
                head = current->getNext();
            } else {
                previous->setNext(current->getNext());
            }
            return current;
        }
        previous = current;
        current = current->getNext();
    }  
    return nullptr;
}

void ShapeList::print() const {
    ShapeNode* current = head;

    while (current != nullptr) {
        current->getShape()->draw();
        current = current->getNext();
    }
    
}