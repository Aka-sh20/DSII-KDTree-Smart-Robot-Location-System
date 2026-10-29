# KARLS — Research Poster and Abstract

**Full title:** Design and Implementation of KARLS: A C++ KD-Tree-Based Robotic Location and Spatial Intelligence System with Applications in AI, Quantum Computing, and Blockchain

**KARLS** = KD-Tree Assisted Robotic Location System  
**Student:** Akashkumar Dilipbhai Patel  
**Faculty advisor:** Dr. Visvasuresh (Victor) Govindaswamy  
**Institution:** Concordia University Chicago  
**Course:** Data Structures and Algorithms II (DS II)

## About this poster
This is the research-poster component of the existing KARLS C++ project. The program uses a two-dimensional KD-Tree to store warehouse object locations as (X,Y) points. A simulated robot can update its position, search stored objects and identify the nearest object using Euclidean distance and KD-Tree nearest-neighbor search. It **does not** move a physical robot or calculate collision-free navigation paths.

The poster presents the project motivation, KD-Tree structure and 2D spatial representation, a menu-driven C++ simulation, UML/design, object-location examples, and research opportunities involving AI/ML, quantum computing, blockchain and autonomous robotics. These emerging technologies are **proposed future work**, not implemented features.

## Files in this folder

| Path | Description |
|---|---|
| `Poster/KARLS_Final_Research_Poster.pptx` | Final submitted PowerPoint poster |
| `Abstract/KARLS_Revised_Abstract_Akashkumar_Patel.docx` | Editable revised abstract, with keywords and future work |
| `Diagrams/KARLS_Spatial_Map_and_KDTree_2320x3000.png` | High-resolution coordinate map and KD-Tree figure |
| `PROJECT_LINKS.md` | Links to main repository, videos, and LinkedIn; fill in after publishing |

## Example spatial demonstration

- Robot: (4, 6)
- Workstation: (2, 6)
- Shelf A: (6, 8)
- Shelf B: (5, 4)
- Boxes: (7, 5)
- Charging Station: (1, 3)
- Nearest stored object: **Workstation**, at **2.00 units** from the robot.

## KD-Tree and C++ program
The full source code (`KDTree.h`, `KDTree.cpp`, `main.cpp`), UML, sample runs, research report, and other existing coursework files should remain in the **main KARLS repository**. This ZIP is an **add-on folder**, not a replacement for the existing repository.

## Poster presentation and social sharing
Fill in the links in `PROJECT_LINKS.md`, then copy them into this README and make sure the video description and LinkedIn poster post link back to the public GitHub repository.

## Important verification before publishing
Review the poster for any remaining template wording (for example, **Contacts**) and ensure the UML matches the final menu's name-based operations. The revised Word abstract here was prepared from the latest approved *draft wording*, not independently confirmed as professor-approved.
