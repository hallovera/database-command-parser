#include "ShapeNode.h"

ShapeNode::ShapeNode() {
    myShape = nullptr;
    next = nullptr;
}

ShapeNode::~ShapeNode() {
    delete myShape;
    myShape = nullptr;
}

Shape* ShapeNode::getShape() const {
    return myShape;
}

void ShapeNode::setShape(Shape* ptr) {
    myShape = ptr;
}

ShapeNode* ShapeNode::getNext() const {
    return next;
}

void ShapeNode::setNext(ShapeNode* ptr) {
    next = ptr;
}

void ShapeNode::print() const {
    myShape->draw();
}


