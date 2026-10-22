#include "KDTree.h"

using namespace std;

// Constructor for Object
Object::Object(string objectName, int objectX, int objectY)
    : name(objectName), x(objectX), y(objectY) {
}

// Constructor for Node
Node::Node(const Object& value)
    : object(value), left(nullptr), right(nullptr) {
}

// Create an empty KD-Tree
KDTree::KDTree() {
    root = nullptr;
    count = 0;
}

// Delete tree nodes when the program ends
KDTree::~KDTree() {
    clear(root);
}

// Remove all nodes from memory
void KDTree::clear(Node* current) {
    if (current == nullptr) {
        return;
    }

    clear(current->left);
    clear(current->right);

    delete current;
}

// Insert an object into the KD-Tree
Node* KDTree::insertNode(Node* current,
                         const Object& object, int depth) {

    if (current == nullptr) {
        return new Node(object);
    }

    // Even levels compare X
    if (depth % 2 == 0) {

        if (object.x < current->object.x) {
            current->left = insertNode(
                current->left, object, depth + 1);
        } else {
            current->right = insertNode(
                current->right, object, depth + 1);
        }
    }

    // Odd levels compare Y
    else {

        if (object.y < current->object.y) {
            current->left = insertNode(
                current->left, object, depth + 1);
        } else {
            current->right = insertNode(
                current->right, object, depth + 1);
        }
    }

    return current;
}

// Search for an object using X and Y coordinates
const Node* KDTree::searchNode(const Node* current,
                              int x, int y, int depth) const {

    if (current == nullptr) {
        return nullptr;
    }

    if (current->object.x == x &&
        current->object.y == y) {
        return current;
    }

    if (depth % 2 == 0) {

        if (x < current->object.x) {
            return searchNode(current->left, x, y, depth + 1);
        } else {
            return searchNode(current->right, x, y, depth + 1);
        }
    } else {

        if (y < current->object.y) {
            return searchNode(current->left, x, y, depth + 1);
        } else {
            return searchNode(current->right, x, y, depth + 1);
        }
    }
}

// Search for an object using its name
const Node* KDTree::searchName(const Node* current,
                               const string& name) const {

    if (current == nullptr) {
        return nullptr;
    }

    // Check the current object
    if (current->object.name == name) {
        return current;
    }

    // Search the left side
    const Node* found = searchName(current->left, name);

    if (found != nullptr) {
        return found;
    }

    // Search the right side
    return searchName(current->right, name);
}

// Add a new object
bool KDTree::addObject(const string& name, int x, int y) {

    // Do not allow an empty name
    if (name.find_first_not_of(" \t") == string::npos) {
        return false;
    }

    // Do not allow duplicate names
    if (searchObjectByName(name) != nullptr) {
        return false;
    }

    // Do not allow duplicate coordinates
    if (searchObject(x, y) != nullptr) {
        return false;
    }

    Object newObject(name, x, y);

    root = insertNode(root, newObject, 0);
    count++;

    return true;
}

// Find an object using coordinates
const Object* KDTree::searchObject(int x, int y) const {

    const Node* found = searchNode(root, x, y, 0);

    if (found == nullptr) {
        return nullptr;
    }

    return &found->object;
}

// Find an object using its name
const Object* KDTree::searchObjectByName(
    const string& name) const {

    const Node* found = searchName(root, name);

    if (found == nullptr) {
        return nullptr;
    }

    return &found->object;
}

// Calculate squared distance
static long long distanceSquared(int x1, int y1,
                                 int x2, int y2) {

    long long dx = (long long)x1 - x2;
    long long dy = (long long)y1 - y2;

    return dx * dx + dy * dy;
}

// Search for the nearest object
void KDTree::nearestNode(const Node* current,
                         int x, int y, int depth,
                         const Node*& best,
                         long long& bestDistance) const {

    if (current == nullptr) {
        return;
    }

    // Calculate distance to the current object
    long long distance = distanceSquared(
        x, y, current->object.x, current->object.y);

    // Update the nearest object if needed
    if (best == nullptr || distance < bestDistance) {
        best = current;
        bestDistance = distance;
    }

    // Compare X or Y depending on the level
    long long difference;

    if (depth % 2 == 0) {
        difference = (long long)x - current->object.x;
    } else {
        difference = (long long)y - current->object.y;
    }

    const Node* first;
    const Node* second;

    // Choose which side to search first
    if (difference < 0) {
        first = current->left;
        second = current->right;
    } else {
        first = current->right;
        second = current->left;
    }

    // Search the closer side
    nearestNode(first, x, y, depth + 1,
                best, bestDistance);

    // Search the other side if it may contain a closer object
    if (difference * difference <= bestDistance) {
        nearestNode(second, x, y, depth + 1,
                    best, bestDistance);
    }
}

// Start searching for the nearest object
const Object* KDTree::findNearest(int x, int y) const {

    const Node* best = nullptr;
    long long bestDistance = 0;

    nearestNode(root, x, y, 0, best, bestDistance);

    if (best == nullptr) {
        return nullptr;
    }

    return &best->object;
}

// Collect all objects from the tree
void KDTree::collectObjects(const Node* current,
                            vector<Object>& objects) const {

    if (current == nullptr) {
        return;
    }

    objects.push_back(current->object);

    collectObjects(current->left, objects);
    collectObjects(current->right, objects);
}

// Remove an object using coordinates
bool KDTree::removeObject(int x, int y) {

    if (searchObject(x, y) == nullptr) {
        return false;
    }

    // Save all objects
    vector<Object> objects;
    collectObjects(root, objects);

    // Clear the old tree
    clear(root);
    root = nullptr;
    count = 0;

    // Add all objects except the removed object
    for (int i = 0; i < (int)objects.size(); i++) {

        if (objects[i].x != x || objects[i].y != y) {
            addObject(objects[i].name,
                      objects[i].x,
                      objects[i].y);
        }
    }

    return true;
}

// Remove an object using its name
bool KDTree::removeObjectByName(const string& name) {

    const Object* object = searchObjectByName(name);

    if (object == nullptr) {
        return false;
    }

    // Save the coordinates before removing the object
    int x = object->x;
    int y = object->y;

    return removeObject(x, y);
}

// Display all objects
void KDTree::displayObjects() const {

    if (root == nullptr) {
        cout << "No objects have been added yet.\n";
        return;
    }

    vector<Object> objects;
    collectObjects(root, objects);

    cout << "\nObjects in the robot's environment ("
         << count << "):\n";

    for (int i = 0; i < (int)objects.size(); i++) {

        cout << i + 1 << ". "
             << objects[i].name
             << " (" << objects[i].x
             << ", " << objects[i].y << ")\n";
    }
}

// Print the branches of the tree
void KDTree::printTree(const Node* current,
                       const string& prefix,
                       bool lastChild, char side,
                       int depth) const {

    if (current == nullptr) {
        return;
    }

    cout << prefix;

    if (lastChild) {
        cout << "`-- ";
    } else {
        cout << "|-- ";
    }

    cout << side << ": "
         << current->object.name
         << " (" << current->object.x
         << ", " << current->object.y
         << ") [Compare ";

    if (depth % 2 == 0) {
        cout << "X";
    } else {
        cout << "Y";
    }

    cout << "]\n";

    string nextPrefix = prefix;

    if (lastChild) {
        nextPrefix += "    ";
    } else {
        nextPrefix += "|   ";
    }

    if (current->left != nullptr) {
        printTree(current->left, nextPrefix,
                  current->right == nullptr,
                  'L', depth + 1);
    }

    if (current->right != nullptr) {
        printTree(current->right, nextPrefix,
                  true, 'R', depth + 1);
    }
}

// Display the complete KD-Tree
void KDTree::displayTree() const {

    if (root == nullptr) {
        cout << "KD-Tree is empty.\n";
        return;
    }

    cout << "\nROOT: "
         << root->object.name
         << " (" << root->object.x
         << ", " << root->object.y
         << ") [Compare X]\n";

    if (root->left != nullptr) {
        printTree(root->left, "",
                  root->right == nullptr,
                  'L', 1);
    }

    if (root->right != nullptr) {
        printTree(root->right, "",
                  true, 'R', 1);
    }
}

// Return the number of objects
int KDTree::getCount() const {
    return count;
}
