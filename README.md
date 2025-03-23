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
Step 1: Clone the Repository
bash
Copy
Edit
git clone https://github.com/yourusername/maximal-clique-enumeration.git
cd maximal-clique-enumeration
Step 2: Compile the Code
bash
Copy
Edit
g++ -std=c++17 -O2 -o maximal_clique demo4.cpp
-std=c++17: Uses C++17 standard.

-O2: Optimization flag for better performance.

▶️ Run the Program
bash
Copy
Edit
./maximal_clique <graph_file>
Example:
bash
Copy
Edit
./maximal_clique datasets/graph1.txt
<graph_file>: Path to the input file containing the edge list.

📄 Input File Format
Comment lines start with #.

Header line (optional) can specify nodes and edges:

bash
Copy
Edit
 Nodes: 100 Edges: 500
Each subsequent line represents an edge:

Copy
Edit
1 2
2 3
3 4
🏃 Sample Output
yaml
Copy
Edit
Elapsed time: 0.85 seconds
Total Cliques = 342
Max Clique size = 5

Distribution of clique sizes:
Size 2: 78 cliques
Size 3: 150 cliques
Size 4: 90 cliques
Size 5: 24 cliques
🛠️ Automating with Makefile (Optional)
If you create a Makefile, you can simplify compilation and execution:

makefile
Copy
Edit
all:
    g++ -std=c++17 -O2 -o maximal_clique demo4.cpp

run:
    ./maximal_clique datasets/graph1.txt
Run with Makefile:
bash
Copy
Edit
make
make run

📊 Performance Metrics
The program tracks:

Total maximal cliques found

Maximum clique size

Runtime in seconds

Clique size distribution
