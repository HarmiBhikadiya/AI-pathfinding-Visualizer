🚀 Weighted Pathfinding Visualizer


Real-Time Pathfinding Visualizer using C++, OpenGL, BFS, and Dijkstra on Weighted Grids.



📌 Overview

This project is an interactive **pathfinding visualizer** built using **C++** and **OpenGL (GLUT)**.

It demonstrates how graph traversal and shortest-path algorithms work in real time on a weighted grid environment.


Features:
• Select start and end nodes
• Create obstacles
• Visualize BFS and Dijkstra algorithms
• Observe node exploration step-by-step
• Highlight the final shortest path



✨ Features

• 🎮 Interactive grid-based UI  
• 🟢 Start node selection  
• 🔴 End node selection  
• ⚫ Obstacle generation  
• 🔵 Real-time visited-node animation  
• 🟡 Final shortest-path highlighting  
• ⚡ Adjustable animation speed  
• 📊 Weighted graph implementation  
• 🧠 BFS and Dijkstra visualization  
• 🎨 OpenGL-based rendering  



🛠 Tech Stack

TechnologyPurposeC++Core Programming LanguageOpenGLGraphics RenderingSTLData StructuresOOPModular Class Design






🧠 Algorithms Implemented

🔹 Breadth First Search (BFS)

o Uses `queue`
o Explores nodes level-by-level
o Suitable for unweighted traversal

🔹 Dijkstra’s Algorithm

o Uses `priority_queue`
o Computes shortest weighted path
o Handles varying traversal costs efficiently



🎮 Controls
	
KeyAction1Select Dijkstra Algorithm2Select BFS AlgorithmARun AlgorithmCClear Grid+/-Increase / Decrease SpeedMouse ClickSet Start, End, and Obstacles

🎨 Node Colour Representation

ColourMeaning🟢 GreenStart Node      🔴 RedEnd Node ⚫ BlackObstacle      🔵 BlueVisited Node   🟡 YellowFinal Path⚪ WhiteUnvisited Node


🖼 Screenshots

Grid Initialization



BFS Visualization



Dijkstra Visualization




⚙️ How to Run

      Windows (MinGW)

bash
g++ src/main.cpp -o app -lfreeglut -lopengl32 -lglu32
./app


      Linux

```bash
g++ src/main.cpp -o app -lglut -lGL -lGLU
./app
```



📚 Concepts Used

o Graph Traversal
o Weighted Shortest Path
o Event-Driven Programming
o Real-Time Rendering
o Animation Loop
o Coordinate Mapping
o Path Reconstruction
o Object-Oriented Programming



📂 Project Structure


AI-pathfinding-visualizer/
│
├── src/
│   └── main.cpp
│
├── screenshots/
│   ├── bfs.png
│   ├── dijkstra.png
│   └── grid.png
│
├── README.md
└── .gitignore


---

💡 Future Improvements

o A* Algorithm Support
o Drag-to-draw Obstacles
o Right-click Eraser
o GUI Controls
o Diagonal Movement
o Performance Statistics



🌟 Learning Outcomes

This project strengthened my understanding of:

o Data Structures & Algorithms
o Graph Theory
o OpenGL Rendering
o Event-Driven Programming
o Animation Systems
o Object-Oriented Design
o Git & GitHub Workflow



📬 Feedback

Suggestions and improvements are always welcome! 🚀

