#include "KDTree.h"
#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>
#include <limits>
#include <cstdlib>

using namespace std;

// Store the robot's location
class Robot {
private:
    int x;
    int y;
    bool locationSet;

public:
    Robot() {
        x = 0;
        y = 0;
        locationSet = false;
    }

    void setLocation(int newX, int newY) {
        x = newX;
        y = newY;
        locationSet = true;
    }

    int getX() const {
        return x;
    }

    int getY() const {
        return y;
    }

    bool hasLocation() const {
        return locationSet;
    }
};

// Read a whole number from the user
int readNumber(const string& message) {

    int number;

    while (true) {
        cout << message;

        if (cin >> number) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return number;
        }

        if (cin.eof()) {
            cout << "\nInput ended. Closing program.\n";
            exit(0);
        }

        cout << "Invalid input. Please enter a whole number.\n";

        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
}

// Calculate straight-line distance
double distanceBetween(int x1, int y1, int x2, int y2) {

    double dx = (double)x1 - x2;
    double dy = (double)y1 - y2;

    return sqrt(dx * dx + dy * dy);
}

// Display the main menu
void showMenu() {

    cout << "\n========================================================\n";
    cout << "  KD-TREE BASED SMART ROBOT OBJECT LOCATION SYSTEM\n";
    cout << "========================================================\n";
    cout << "1. Add Object to Robot's Environment\n";
    cout << "2. Search Object by Name\n";
    cout << "3. Set / Update Robot's Current Location\n";
    cout << "4. Find Nearest Object to Robot\n";
    cout << "5. Measure Distance from Robot to Selected Object\n";
    cout << "6. Display All Objects in Robot's Environment\n";
    cout << "7. Display KD-Tree Structure\n";
    cout << "8. Remove Object by Name\n";
    cout << "9. Exit System\n";
    cout << "========================================================\n";
}

int main() {

    KDTree tree;
    Robot robot;

    // Show distances with two decimal places
    cout << fixed << setprecision(2);

    while (true) {

        showMenu();

        int choice = readNumber("Enter your choice: ");

        // Option 9: Exit
        if (choice == 9) {
            cout << "Thank you for using the robot location system!\n";
            break;
        }

        // Option 1: Add an object
        if (choice == 1) {

            string name;

            cout << "Enter object name: ";
            getline(cin, name);

            if (name.find_first_not_of(" \t") == string::npos) {
                cout << "Object name cannot be empty.\n";
                continue;
            }

            int x = readNumber("Enter object X: ");
            int y = readNumber("Enter object Y: ");

            if (tree.searchObjectByName(name) != nullptr) {
                cout << "An object with this name already exists.\n";
            }
            else if (tree.searchObject(x, y) != nullptr) {
                cout << "An object already exists at this location.\n";
            }
            else if (tree.addObject(name, x, y)) {
                cout << "Object added successfully!\n";
            }
        }

        // Option 2: Search for an object by name
        else if (choice == 2) {

            string name;

            cout << "Enter object name: ";
            getline(cin, name);

            const Object* object = tree.searchObjectByName(name);

            if (object != nullptr) {

                cout << "Object found successfully!\n";
                cout << "Object name: " << object->name << "\n";
                cout << "Object location: ("
                     << object->x << ", "
                     << object->y << ")\n";
            }
            else {
                cout << "Object not found in the robot's environment.\n";
            }
        }

        // Option 3: Set or update robot location
        else if (choice == 3) {

            int x = readNumber("Enter robot X: ");
            int y = readNumber("Enter robot Y: ");

            robot.setLocation(x, y);

            cout << "Robot location saved: ("
                 << robot.getX() << ", "
                 << robot.getY() << ")\n";
        }

        // Option 4: Find the nearest object
        else if (choice == 4) {

            if (!robot.hasLocation()) {
                cout << "Please set the robot location first (Option 3).\n";
                continue;
            }

            const Object* object =
                tree.findNearest(robot.getX(), robot.getY());

            if (object == nullptr) {
                cout << "No objects available. Add an object first.\n";
            }
            else {

                cout << "Robot location: ("
                     << robot.getX() << ", "
                     << robot.getY() << ")\n";

                cout << "Nearest object: "
                     << object->name
                     << " (" << object->x
                     << ", " << object->y << ")\n";

                cout << "Distance: "
                     << distanceBetween(
                            robot.getX(), robot.getY(),
                            object->x, object->y)
                     << " units\n";
            }
        }

        // Option 5: Measure distance using object name
        else if (choice == 5) {

            if (!robot.hasLocation()) {
                cout << "Please set the robot location first (Option 3).\n";
                continue;
            }

            string name;

            cout << "Enter object name: ";
            getline(cin, name);

            const Object* object = tree.searchObjectByName(name);

            if (object == nullptr) {
                cout << "Object not found in the robot's environment.\n";
            }
            else {

                cout << "Robot location: ("
                     << robot.getX() << ", "
                     << robot.getY() << ")\n";

                cout << "Selected object: "
                     << object->name
                     << " (" << object->x
                     << ", " << object->y << ")\n";

                cout << "Distance from robot: "
                     << distanceBetween(
                            robot.getX(), robot.getY(),
                            object->x, object->y)
                     << " units\n";
            }
        }

        // Option 6: Display all objects
        else if (choice == 6) {
            tree.displayObjects();
        }

        // Option 7: Display the KD-Tree structure
        else if (choice == 7) {
            tree.displayTree();
        }

        // Option 8: Remove an object by name
        else if (choice == 8) {

            string name;

            cout << "Enter object name to remove: ";
            getline(cin, name);

            if (tree.removeObjectByName(name)) {
                cout << "Object removed successfully!\n";
            }
            else {
                cout << "Object not found in the robot's environment.\n";
            }
        }

        // Invalid menu option
        else {
            cout << "Invalid menu choice. Choose 1 to 9.\n";
        }
    }

    return 0;
}