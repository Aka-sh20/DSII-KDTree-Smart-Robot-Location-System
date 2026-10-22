#ifndef KDTREE_H
#define KDTREE_H

#include <iostream>
#include <string>
#include <vector>

using namespace std;

// Store information about an object
struct Object {
    string name;
    int x;
    int y;

    Object(string objectName, int objectX, int objectY);
};

// Each node stores one object
struct Node {
    Object object;
    Node* left;
    Node* right;

    Node(const Object& value);
};

class KDTree {
private:
    Node* root;
    int count;

    // Functions used inside the KD-Tree
    Node* insertNode(Node* current, const Object& object, int depth);

    const Node* searchNode(const Node* current,
                           int x, int y, int depth) const;

    const Node* searchName(const Node* current,
                           const string& name) const;

    void nearestNode(const Node* current, int x, int y,
                     int depth, const Node*& best,
                     long long& bestDistance) const;

    void collectObjects(const Node* current,
                        vector<Object>& objects) const;

    void printTree(const Node* current, const string& prefix,
                   bool lastChild, char side, int depth) const;

    void clear(Node* current);

public:
    KDTree();
    ~KDTree();

    // Prevent copying the tree by mistake
    KDTree(const KDTree&) = delete;
    KDTree& operator=(const KDTree&) = delete;

    bool addObject(const string& name, int x, int y);

    const Object* searchObject(int x, int y) const;
    const Object* searchObjectByName(const string& name) const;

    const Object* findNearest(int x, int y) const;

    bool removeObject(int x, int y);
    bool removeObjectByName(const string& name);

    void displayObjects() const;
    void displayTree() const;

    int getCount() const;
};

#endif