# KD-Tree Based Smart Robot Object Location System

**BLAST 02 — Emerging Technologies Through Data Structures in C++**  
**Topic:** KD-Tree (2D spatial data structure)  
**Emerging area:** AI / Robotics  
**Course:** Data Structures and Algorithms II  
**Instructor:** Dr. Victor Govindaswamy  
**Presenter shown on accompanying theory slides:** Akash Patel

## 1. About this project

For this assignment, I worked with a **KD-Tree**, a binary tree that stores points using coordinates. I used a small warehouse example where a robot needs to find objects such as shelves, boxes, workstations, and a charging station. Each stored object has a **unique name** and an **(X, Y)** location. The robot has its own location, which can be changed through the menu.

The aim is to demonstrate the KD-Tree data structure in C++, not to create an actual moving robot or a complete AI system. The program runs in a terminal and shows what happens when objects are added, searched, displayed, or removed.

## 2. What is a KD-Tree?

A KD-Tree means **K-Dimensional Tree**. In this project, **K = 2**, because an object's position has two coordinates: X and Y. Like other binary trees, a node can have a left child and a right child. The difference is the way we choose a branch:

- At **depth 0** (the root), we compare **X**.
- At **depth 1**, we compare **Y**.
- At **depth 2**, we compare **X** again, and so on.
- When the selected coordinate is **smaller**, the new point goes left. Otherwise, it goes right.
- The program does not allow two objects to share the same coordinates or name.

This is useful for storing spatial data. For example, a robot can ask which stored object is nearest to its current position.

### Simple insertion example

If I insert these objects in this order — Boxes (4, 7), Shelf B (2, 6), Workstation (1, 5), Shelf A (8, 3) — the KD-Tree looks like this:

```text
                    Boxes (4,7) [X]
                    /              \\
       Shelf B (2,6) [Y]         Shelf A (8,3) [Y]
              /
    Workstation (1,5) [X]
```

Boxes is the root because it was entered first. Shelf B goes left because 2 is smaller than 4 on X. Workstation goes left below Shelf B after comparing Y. Shelf A goes right of Boxes.

## 3. How this relates to AI and Robotics

A warehouse robot might need to find the nearest box or check the distance to a charging station. Our C++ program demonstrates the **location-search part** of that problem. The KD-Tree stores object coordinates, and a separate `Robot` class stores the robot's current position. A real robot would also need sensors, collision detection, navigation, and movement controls; those are outside the scope of this project.

Other uses of KD-Trees include working with 3D sensor points, computer graphics, and some nearest-neighbor searches in machine learning.

## 4. Menu and features

| Option | Feature | What the user does |
|---|---|---|
| 1 | Add Object to Robot's Environment | Enter a unique object name, X, and Y |
| 2 | Search Object by Name | Enter a name; the program displays its stored coordinates |
| 3 | Set / Update Robot's Current Location | Enter robot X and Y |
| 4 | Find Nearest Object to Robot | Find the stored point nearest to the robot |
| 5 | Measure Distance from Robot to Selected Object | Enter a name; calculate straight-line distance |
| 6 | Display All Objects in Robot's Environment | Show objects in KD-Tree preorder (root, left, right) |
| 7 | Display KD-Tree Structure | Show root, left/right connections, and comparison axes |
| 8 | Remove Object by Name | Find the named object, delete it, and rebuild the remaining tree |
| 9 | Exit System | Close the program |

**Important difference between two searches:** Options **2, 5, and 8** find an object **by name**. Since a KD-Tree is organized by coordinates, the name-search helper may have to visit multiple nodes. The program also keeps a coordinate-based `searchNode()` function, which uses the actual KD-Tree X/Y comparisons. Option **4** is the main nearest-neighbor demonstration of the KD-Tree.

## 5. Source-code files

- [`Source-Code/KDTree.h`](Source-Code/KDTree.h) — declarations for `Object`, `Node`, and `KDTree`, including functions for insertion, searching, nearest neighbor, and removal.
- [`Source-Code/KDTree.cpp`](Source-Code/KDTree.cpp) — implementations of KD-Tree operations and the tree display.
- [`Source-Code/main.cpp`](Source-Code/main.cpp) — `Robot` class, number input, distance formula, menu, and user interaction.

The code uses `using namespace std;` and simple comments to make it easier to follow.

## 6. Compile and run (Ubuntu / Linux)

A C++ compiler such as `g++` is required. In the terminal, from the repository's main folder, run:

```bash
cd Source-Code
g++ KDTree.cpp main.cpp -o KDTree
./KDTree
```

The three C++ files should stay in the same folder. You can also use `g++ -std=c++11 KDTree.cpp main.cpp -o KDTree` because the code uses C++11 features such as `nullptr`.

## 7. Sample execution

The screenshots in this repository come from my live terminal demonstration. For example, after adding objects including **Shelf B (5, 4)** and setting the robot's position to **(4, 6)**:

**Search for an object by name**

```text
Enter your choice: 2
Enter object name: Shelf B
Object found successfully!
Object name: Shelf B
Object location: (5, 4)
```

**Find the closest object**

```text
Enter your choice: 4
Robot location: (4, 6)
Nearest object: Workstation (2, 6)
Distance: 2.00 units
```

**Calculate distance to a selected object**

```text
Enter your choice: 5
Enter object name: Boxes
Robot location: (4, 6)
Selected object: Boxes (7, 5)
Distance from robot: 3.16 units
```

**Remove an object**

```text
Enter your choice: 8
Enter object name to remove: Workstation
Object removed successfully!
```

See [`Screenshots/`](Screenshots/) for more examples. The theory presentation and screenshots use **different sets of sample coordinates** to explain the same general ideas.

## 8. Distance and nearest-neighbor search

The distance used here is **Euclidean distance**, or straight-line distance:

```text
Distance = sqrt((objectX - robotX)^2 + (objectY - robotY)^2)
```

For example, if the robot is at (4, 6) and Boxes is at (7, 5), the distance is `sqrt(3^2 + (-1)^2) = sqrt(10) = 3.16 units` (rounded).

In the nearest-neighbor function, the program checks a more promising branch first, keeps the closest object found, and checks the opposite branch if it could contain a closer object. This is different from simply picking whichever node lies on the first search path.

## 9. Removing an object and tree traversal

I used a straightforward removal method so I could follow the process step by step: find the object, collect the objects in **preorder**, clear the old tree, and reinsert every remaining object. Rebuilding takes additional time, and the root or printed order can change afterward. Option **6** displays preorder, **not necessarily the order the objects were originally entered**.

This is a learning-focused solution, rather than the more advanced specialized KD-Tree deletion algorithm.

## 10. Complexity and limitations

| Operation | Favorable / balanced situation | Worst case |
|---|---|---|
| Insert by coordinates | O(log n) | O(n) |
| Exact search by coordinates | O(log n) | O(n) |
| Search by name | O(n) | O(n) |
| Nearest neighbor in 2D | Often visits fewer nodes than a full scan | O(n) |
| Display all objects | O(n) | O(n) |
| Delete by rebuilding and reinserting | Can approach O(n log n) | O(n²) |

Here `n` means the number of stored objects. A KD-Tree can become unbalanced depending on insertion order. The program uses **O(n)** memory for nodes; removal also uses a temporary vector of objects. It does not balance the tree automatically, plan a collision-free route, or use live robot sensors.

## 11. Validation and example edge cases

The program checks several cases:

- An empty object name is rejected.
- A repeated object name is rejected.
- A repeated X/Y location is rejected.
- Searching or removing an unknown name reports that the object was not found.
- Nearest-object search asks for the robot position if it has not been set yet.
- Nearest-object search reports when no objects have been added.
- The menu rejects an invalid menu choice, and non-numeric input is handled for numeric prompts.

## 12. UML and project documentation

- [Research report](Documentation/Research/Research_Report.pdf)
- [Theory presentation — Part 1](Documentation/Presentation/KDTree_Theory_Part1.pdf)
- [Original KDTree UML PowerPoint](Documentation/UML/KDTree_UML_Original.pptx)
- [Robot UML PowerPoint](Documentation/UML/Robot_UML.pptx)
- [Current implementation and UML notes](Documentation/UML/Current_Design_Notes.md)

**Version note:** The original report and the original KDTree UML were prepared for an earlier version of the program, before the final name-based menu changes. They are included as uploaded, without rewriting the student's source materials. The README and current design notes describe the uploaded final C++ implementation. Please update the older report and PowerPoint before using them as final academic submissions.

## 13. Screenshots and evidence

- [Add objects and menu](Screenshots/Program_Menu_%26_Add_Objects.png)
- [Search for an object by name](Screenshots/Add_Search_Object.png)
- [Set robot location](Screenshots/Set_Robot_Location.png)
- [Find nearest object](Screenshots/Nearest_Object.png)
- [Measure distance](Screenshots/Distance_Calculation.png)
- [Show all objects](Screenshots/Display_All_Objects.png)
- [Display KD-Tree structure](Screenshots/KDTree_Structure.png)
- [Remove object](Screenshots/Remove_Object.png)

## 14. YouTube and LinkedIn 

- **YouTube — Part 1 (Theory):** [https://youtu.be/10bkCGe_qBs]
- **YouTube — Part 2 (C++ live demonstration):** [https://youtu.be/PgyIM9xZ9gs]
- **LinkedIn — Theory post:** [https://www.linkedin.com/posts/patel-akash-51a395208_kdtree-datastructures-algorithms-share-7519114236837380097-8OZy/?highlightedUpdateUrn=urn%3Ali%3Aactivity%3A7519114238032949249&highlightedUpdateType=SOCIAL_SHARE&origin=SOCIAL_SHARE&utm_source=share&utm_medium=member_desktop&rcm=ACoAADS84aYB4gqMkxKBoN4DtiRjbRRovxbcl-w]
- **LinkedIn — Practical demonstration post:** [https://www.linkedin.com/posts/patel-akash-51a395208_kdtree-datastructures-datastructuresandalgorithms-share-7519115581892087808-eX5w/?highlightedUpdateUrn=urn%3Ali%3Aactivity%3A7519115583276126208&highlightedUpdateType=SOCIAL_SHARE&origin=SOCIAL_SHARE&utm_source=share&utm_medium=member_desktop&rcm=ACoAADS84aYB4gqMkxKBoN4DtiRjbRRovxbcl-w]

## 15. References

1. [GeeksforGeeks — KD Trees in C++](https://www.geeksforgeeks.org/cpp/kd-trees-in-cpp/)
2. [SSOJet — Implement KD-Tree in C++](https://ssojet.com/dev-guides/implement-kd-tree-in-cpp)
3. [LeetCode Discuss — KD-tree Search / Insert / Delete Summary](https://leetcode.com/discuss/post/136595/kd-tree-search-insert-delete-summary-wit-5qzx/)

## 16. What I learned

Working through this project helped me understand how one binary tree can compare different dimensions at different levels. I also learned why searching for an exact location is different from finding the nearest location. The most challenging part for me was following recursive functions during nearest-neighbor search and removal. The tree display and the simple warehouse examples helped me see where each object is stored.

I thank **Dr. Victor Govindaswamy** for the opportunity to connect data structures with a practical AI/Robotics example.
