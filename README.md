There are three algorithms under this project.

##    1.)Maximal Clique Enumeration

This repository implements a maximal clique enumeration algorithm in C++, optimized for both sparse and dense graphs. It leverages pivoting strategies for efficient performance, tracking runtime, clique counts, and size distribution.

🚀 Features
Efficient maximal clique enumeration using pivoting.

Handles large graph datasets with quick lookups.

Outputs clique statistics and distribution.

Built-in timing for performance evaluation.

📥 Prerequisites
Ensure you have the following installed:

C++17 or later

g++ (GNU Compiler Collection)

Make (optional for automation)

⚙️ Build Instructions

git clone https://github.com/ShiZ7/maximal-clique-enumeration.git

cd maximal-clique-enumeration

g++ -std=c++17 -O2 -o maximal_clique demo4.cpp


-O2: Optimization flag for better performance.

▶️ Run the Program
./maximal_clique <graph_file>


📄 Input File Format
Comment lines start with #.


 Nodes: 100 Edges: 500
 
Each subsequent line represents an edge:

Edge list:

Copy
Edit
1 2
2 3
3 4

🏃 Sample Output

Elapsed time: 0.85 seconds
Total Cliques = 342
Max Clique size = 5

Distribution of clique sizes:
Size 2: 78
Size 3: 150
Size 4: 90
Size 5: 24


Run with Makefile:

make
make run

📊 Performance Metrics

The program tracks:

Total maximal cliques found

Maximum clique size

Runtime in seconds

Clique size distribution
