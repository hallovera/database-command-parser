#include <iostream>
#include <sstream>
#include <string>

using namespace std;

#include "globals.h"
#include "Shape.h"
#include "ShapeNode.h"
#include "GroupNode.h"
#include "ShapeList.h"
#include "GroupList.h"

// This is a pointer to the groups list
// The list itself must be allocated
GroupList* gList;

// Determines if given group name exists
GroupNode* findGroup(string name);
// Find if given string is within a array of length "arrayLength"
int findInArray(const string *array, int arrayLength, string str);
// Determines reason stringstream "lineStream" failed, and prints it to cout
void checkSStreamFailReason(stringstream &lineStream);
// Finds position of Shape with name "name" within shapesArray
ShapeNode* findPos(string name);
// Processes a name argument in "lineStream", catches/outputs related errors, and outputs name to "name" if no errors
bool processName(stringstream &lineStream, string &name, string op, const string* reserved, const int reservedLength, bool isGroup);
// Processes a type argument in "lineStream", catches/outputs related errors, and outputs type to "type" if no errors
bool processType(stringstream &lineStream, string &type);
// Processes a location argument in "lineStream", catches/outputs related errors, and outputs location to "loc" if no errors
bool processLoc(stringstream &lineStream, int &loc);
// Processes a size argument in "lineStream", catches/outputs related errors, and outputs size to "size" if no errors
bool processSize(stringstream &lineStream, int &size);

int main() {
    // Create the groups list
    gList = new GroupList();
    
    // Create the pool group and add it to the group list
    GroupNode* poolGroup = new GroupNode(keyWordsList[NUM_KEYWORDS-1]);
    gList->insert(poolGroup);
    
    string line;
    string command;
    
    cout << "> ";         // Prompt for input
    getline(cin, line);    // Get a line from standard input

    while ( !cin.eof () ) {
        // Put the line in a linestream for parsing
        // Making a new sstream for each line so flags etc. are cleared
        stringstream lineStream (line);

        command = "";
        
        // Read from string stream into the command
        // The only way this can fail is if the eof is encountered
        lineStream >> command;
        
        // Check for the command and act accordingly

        // Reserved word constants
        const string reserved[] = {"shape", "group", "draw", "move", "delete", "ellipse", "triangle", "rectangle", "pool"}; 
        
        // Number of reserved words
        const int reservedLength = sizeof(reserved) / sizeof(string);

        string toDeleteFrom = "";

        string name;
        string groupName;
        string type;
        int xloc, yloc;
        int xsize, ysize;

        bool failed = false;
        int numOfArgs = 0;

        ShapeNode* tempShapeNode = nullptr;
        GroupNode* tempGroupNode = nullptr;

        if (command == "shape") {
            failed = false;
            numOfArgs = 6;

            for (int current = 0; current < numOfArgs; current++) {
                switch (current) {
                    case 0:
                        failed = processName(lineStream, name, command, reserved, reservedLength, false);
                        break;
                    case 1:
                        failed = processType(lineStream, type);
                        break;
                    case 2:
                        failed = processLoc(lineStream, xloc);
                        break;
                    case 3:
                        failed = processLoc(lineStream, yloc);
                        break;
                    case 4:
                        failed = processSize(lineStream, xsize);
                        break;
                    case 5:
                        failed = processSize(lineStream, ysize);
                        break;
                    default:
                        break;
                }
                if (failed) break;
            }

            if (!failed) {
                tempShapeNode = new ShapeNode();
                tempShapeNode->setShape(new Shape(name, type, xloc, yloc, xsize, ysize));
                gList->getHead()->getShapeList()->insert(tempShapeNode);
                cout << name << ": " << type << " " << xloc << " " << yloc << " " << xsize << " " << ysize << endl;
            }
        } else if (command == "group") {
            failed = false;
            numOfArgs = 1;

            for (int current = 0; current < numOfArgs; current++) {
                switch (current) {
                    case 0:
                        failed = processName(lineStream, name, command, reserved, reservedLength, true);
                        break;
                    default:
                        break;
                }
                if (failed) break;
            }

            if (!failed) {
                tempGroupNode = new GroupNode(name);
                gList->insert(tempGroupNode);

                cout << name << ": group" << endl;
            }
        } else if (command == "draw") {
            failed = false;
            numOfArgs = 0;

            if (!failed) {
                cout << "drawing:" << endl;
                gList->print();
            }
        } else if (command == "move") {
            failed = false;
            numOfArgs = 2;

            for (int current = 0; current < numOfArgs; current++) {
                switch (current) {
                    case 0:
                        failed = processName(lineStream, name, command, reserved, reservedLength, false);
                        break;
                    case 1:
                        failed = processName(lineStream, groupName, command, reserved, reservedLength, true);
                        break;
                    default:
                        break;
                }
                if (failed) break;
            }

            if (!failed) {
                tempShapeNode = nullptr;
                for (GroupNode* currentG = gList->getHead(); currentG != nullptr; currentG = currentG->getNext()) {
                    tempShapeNode = currentG->getShapeList()->remove(name);
                    if (tempShapeNode != nullptr) {
                        findGroup(groupName)->getShapeList()->insert(tempShapeNode);
                        break;
                    }
                }
                cout << "moved " << name << " to " << groupName << endl;
            }
        } else if (command == "delete") {
            failed = false;
            numOfArgs = 1;

            for (int current = 0; current < numOfArgs; current++) {
                switch (current) {
                    case 0:
                        failed = processName(lineStream, name, command, reserved, reservedLength, false);
                        break;
                    default:
                        break;
                }
                if (failed) break;
            }

            if (!failed) {
                for (GroupNode* currentG = gList->getHead(); currentG != nullptr; currentG = currentG->getNext()) {
                    //------------ DELETE A GROUP --------------------
                    if (currentG->getName() == name) {
                        if (currentG->getShapeList()->getHead() == nullptr) {
                            for (GroupNode* prevG = gList->getHead(); prevG != nullptr; prevG = prevG->getNext()) {
                                if (prevG->getNext() == currentG) {
                                    prevG->setNext(currentG->getNext());
                                    break;
                                }
                            }
                            delete currentG;
                            currentG = nullptr;
                            break;
                        }

                        // Not a fan of the 1==1. Check if it could break
                        for (ShapeNode* currentS = gList->getHead()->getShapeList()->getHead(); 1 == 1; currentS = currentS->getNext()) {
                            // ------- IF POOL IS EMPTY, OR IF CURRENT SHAPENODE IS AT END OF POOL -----
                            if (gList->getHead()->getShapeList()->getHead() == nullptr || currentS->getNext() == nullptr) {
                                if (gList->getHead()->getShapeList()->getHead() == nullptr) {
                                    gList->getHead()->getShapeList()->setHead(currentG->getShapeList()->getHead());
                                } else if (currentS->getNext() == nullptr) {
                                    currentS->setNext(currentG->getShapeList()->getHead());
                                }
                                currentG->getShapeList()->setHead(nullptr);

                                for (GroupNode* prevG = gList->getHead(); prevG != nullptr; prevG = prevG->getNext()) {
                                    if (prevG->getNext() == currentG) {
                                        prevG->setNext(currentG->getNext());
                                        break;
                                    }
                                }

                                delete currentG;
                                currentG = nullptr;
                                break;
                            }
                        }
                        if (currentG == nullptr) break;
                    }
                    // ------------- END DELETE A GROUP -----------------

                    // ------------- DELETE A SHAPENODE -----------------                
                    
                    tempShapeNode = currentG->getShapeList()->remove(name);
                    if (tempShapeNode != nullptr) {
                        delete tempShapeNode;
                        tempShapeNode = nullptr;
                        break;
                    }
                    // ------------- END DELETE A SHAPENODE -------------
                }
                cout << name << ": deleted" << endl;
            }
        }

        // Once the command has been processed, prompt for the
        // next command
        cout << "> ";          // Prompt for input
        getline(cin, line);
        
    }  // End input loop until EOF.
    
    return 0;
}

GroupNode* findGroup(string name) {
    GroupNode* current = gList->getHead();

    while (current != nullptr) {
        if (current->getName() == name) {
            return current;
        }
        current = current->getNext();
    }
    return nullptr;
}

int findInArray(const string *array, int arrayLength, string str) {
    for (int i = 0; i < arrayLength; i++) {
        if (array[i] == str) {
            return i;
        }
    }
    return -1;
}

void checkSStreamFailReason(stringstream &lineStream) {
    if (!lineStream.eof()) {
        cout << "error: invalid argument" << endl;
    } else {
        cout << "error: too few arguments" << endl;
    }
}

ShapeNode* findPos(string name) {
    GroupNode* current = gList->getHead();

    while (current != nullptr) {
        if (current->getShapeList()->find(name) != nullptr) {
            return current->getShapeList()->find(name);
        }
        current = current->getNext(); 
    }
    return nullptr;
}

bool processName(stringstream &lineStream, string &name, string op, const string* reserved, const int reservedLength, bool isGroup) {
    lineStream >> name;
    
    if ((op == "shape" || op == "group") && (findInArray(reserved, reservedLength, name) != -1)) {
        cout << "error: invalid name" << endl;
        return true;
    } else if ((op == "shape" || op == "group") && (findPos(name) != nullptr || findGroup(name) != nullptr)) {
        cout << "error: name " << name << " exists" << endl;
        return true;
    // Other commands (non-"create") use "name" to find an item
    } else if (op == "delete") {
        if (name == "pool") {
            cout << "error: invalid name" << endl;
            return true;
        } else if (findGroup(name) == nullptr && findPos(name) == nullptr) {
            cout << "error: shape " << name << " not found" << endl;
            return true;
        }
    } else if (op == "move") {
        if (isGroup && findGroup(name) == nullptr) {
            cout << "error: group " << name << " not found" << endl;
            return true;
        } else if (!isGroup && findPos(name) == nullptr) {
            cout << "error: shape " << name << " not found" << endl;
            return true;
        }
    }
    return false;
}

bool processType(stringstream &lineStream, string &type) {
    lineStream >> type;
    return false;
}

bool processLoc(stringstream &lineStream, int &loc) {
    lineStream >> loc;
    return false;
}

bool processSize(stringstream &lineStream, int &size) {
    lineStream >> size;
    return false;
}