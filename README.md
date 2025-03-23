There are three algorithms under this project.

#    1.)Maximal Clique Enumeration

This repository implements a maximal clique enumeration algorithm in C++, optimized for both sparse and dense graphs. It leverages pivoting strategies for efficient performance, tracking runtime, clique counts, and size distribution.

 ## Features
-Efficient maximal clique enumeration using pivoting.

-Handles large graph datasets with quick lookups.

-Outputs clique statistics and distribution.

-Built-in timing for performance evaluation.

## Prerequisites

-C++17 or later

-g++ (GNU Compiler Collection)


## Build Instructions

-git clone https://shiz7.github.io/Group-19_DAA-assignment-1/

-cd maximal-clique-enumeration

-g++ -std=c++17 -O2 -o maximal_clique demo4.cpp


## Optimization flag for better performance.

▶️ Run the Program
-./maximal_clique <graph_file>


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

## Sample Output

Elapsed time: 0.85 seconds
Total Cliques = 342
Max Clique size = 5

Distribution of clique sizes:
Size 2: 78
Size 3: 150
Size 4: 90
Size 5: 24


## Run with Makefile:

make
make run

## Performance Metrics

The program tracks:
-Total maximal cliques found

-Maximum clique size

-Runtime in seconds

-Clique size distribution


# 2.)Bron-Kerbosch Clique Enumeration


## Features
-Maximal clique enumeration with degeneracy ordering.
-CSV output for clique size distribution.
-Tracks execution time and largest clique size.

## Build & Run 

Step 1: Compile the code
- g++ -std=c++17 -O2 -o bronkerbosch bronkerbosch.cpp

Step 2: Execute the program
- ./bronkerbosch

## Input Format

Edge list in u v format.

Total Maximal Cliques: 452

Largest Maximal Clique Size: 6

Execution Time: 1.27 seconds

## Output
grok-as-skitter.csv contains clique size distribution.

## 📄 Dataset Preparation
You can read the detailed dataset preparation process [here](dataset_preparation.txt).



#  Question3

## Project Overview
This project focuses on implementing and experimenting with maximal clique enumeration algorithms in C++. The objective is to identify all maximal cliques in a given graph dataset and analyze the performance in terms of execution time and clique size distribution.

## File Description
- **demo2.cpp**: The main C++ source file containing the implementation of the maximal clique enumeration algorithm.

## Compilation and Execution

### Prerequisites
- C++ Compiler (e.g., g++)
- Standard Template Library (STL)

### Compilation
To compile the program, use the following command:
```bash
g++ -std=c++17 -O2 -o clique_enum demo2.cpp
```

### Execution
To run the program, provide a graph input file as an argument:
```bash
./clique_enum <graph_file>
```
Example:
```bash
./clique_enum sample_graph.txt
```

## Input File Format
- The input file should contain edges of the graph in the format:
```
u v
```
Where `u` and `v` represent connected vertices. Commented lines starting with `#` are ignored.

## Output Description
- **Total Cliques**: The number of maximal cliques found.
- **Max Clique Size**: The size of the largest clique identified.
- **Clique Size Distribution**: The number of cliques of each size.
- **Elapsed Time**: The time taken to complete the enumeration.

## Performance Analysis
The program measures the performance based on:
- Execution time using `std::chrono`.
- Distribution of clique sizes.

## Graph Datasets
The experiment is designed to run on multiple graph datasets with varying densities and sizes to assess the scalability and efficiency of the implementation.

## Results and Discussion
This section will include:
- Analysis of execution time across different datasets.
- Insights on how clique sizes distribute in sparse vs. dense graphs.

## Conclusion
The project demonstrates how maximal clique enumeration behaves under different graph structures, offering insights into its computational complexity and performance bottlenecks.

## References
- Research papers on maximal clique enumeration.
- Documentation on C++ standard libraries.

## Acknowledgments
Special thanks to the contributors of open-source graph datasets used for testing.





## Group Members:
(Group 19)

Shivansh Shanker Gupta	
2022A7PS0047H (Report , Webpage & Q3)

Sidharth Saxena	
2021B4A72488H (Q1,3)

T.Sai Sathwik
2020B4A71567H (Q1,Q3)

G Sri Vishwahitha	
2022A7PS0041H (Q2)
	
Snigdha Kaipa	(Generating Histograms)
2022A7PS2014H
