#include "GroupList.h"

GroupList::GroupList() {
    head = nullptr;
}

GroupList::~GroupList() {
    GroupNode* current = head;
    GroupNode* next = head->getNext();

    while (current != nullptr) {
        delete current;
        current = next;
        if (next != nullptr) {
            next = next->getNext();
        }
    }
    head = nullptr;
}

GroupNode* GroupList::getHead() const {
    return head;
}

void GroupList::setHead(GroupNode* ptr) {
    head = ptr;
}

void GroupList::insert(GroupNode* s) {
    GroupNode* current = head;

    if (current == nullptr) {
        head = s;
        return;
    }

    while (current->getNext() != nullptr) {
        current = current->getNext();
    }
    current->setNext(s);
}

GroupNode* GroupList::remove(string name) {
    GroupNode* current = head;
    GroupNode* previous = nullptr;

    while (current != nullptr) {
        if (current->getName() == name) {
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

void GroupList::print() const {
    GroupNode* current = head;
    while (current != nullptr) {
        current->print();
        current = current->getNext();
    }
}