#include <iostream>
#include <vector>
#include <unordered_set>
#include <unordered_map>
#include <algorithm>
#include <utility>
#include <fstream>
#include <sstream>
#include <string>
#include <chrono>

using namespace std;
using namespace chrono;
using AdjList = unordered_map<int, unordered_set<int> >;

// Function to remap vertex IDs to 0-based indexing
vector<pair<int, int> > remapEdgesToZeroBased(const vector<pair<int, int> >& edges, unordered_map<int, int>& vertexMap) {
    unordered_set<int> uniqueVertices;
    for (const auto& edge : edges) {
        uniqueVertices.insert(edge.first);
        uniqueVertices.insert(edge.second);
    }

    int newID = 0;
    for (int v : uniqueVertices) {
        vertexMap[v] = newID++;
    }

    vector<pair<int, int> > newEdges;
    for (const auto& edge : edges) {
        newEdges.push_back(make_pair(vertexMap[edge.first], vertexMap[edge.second]));
    }
    return newEdges;
}

// Compute degeneracy ordering
pair<vector<int>, AdjList> computeDegeneracyOrdering(const vector<pair<int, int> >& edges) {
    AdjList adj;
    unordered_set<int> allVertices;

    for (const auto& edge : edges) {
        int u = edge.first, v = edge.second;
        adj[u].insert(v);
        adj[v].insert(u);
        allVertices.insert(u);
        allVertices.insert(v);
    }

    vector<int> ordering;
    unordered_set<int> remainingVertices = allVertices;
    unordered_map<int, int> degrees;
    for (int v : remainingVertices) {
        degrees[v] = adj[v].size();
    }

    while (!remainingVertices.empty()) {
        int minDeg = INT_MAX, minVertex = -1;
        for (int v : remainingVertices) {
            if (degrees[v] < minDeg) {
                minDeg = degrees[v];
                minVertex = v;
            }
        }

        ordering.push_back(minVertex);
        remainingVertices.erase(minVertex);
        for (int u : adj[minVertex]) {
            if (remainingVertices.count(u)) degrees[u]--;
        }
    }

    return make_pair(ordering, adj);
}

// Optimized Bron-Kerbosch with pivoting (avoiding unnecessary copying)
void bronKerboschPivot(
    unordered_set<int>& P, unordered_set<int>& R, unordered_set<int>& X,
    const AdjList& adj, vector<unordered_set<int> >& cliques) {

    if (P.empty() && X.empty()) {
        cliques.push_back(R);
        return;
    }

    int pivot = -1, maxIntersection = -1;
    for (int u : P) {
        int intersectionSize = 0;
        if (adj.find(u) != adj.end()) {
            for (int v : P) {
                if (adj.at(u).count(v)) intersectionSize++;
            }
        }
        if (intersectionSize > maxIntersection) {
            maxIntersection = intersectionSize;
            pivot = u;
        }
    }

    vector<int> P_minus_neighbors;
    if (pivot != -1) {
        for (int v : P) {
            if (adj.find(pivot) == adj.end() || adj.at(pivot).count(v) == 0) {
                P_minus_neighbors.push_back(v);
            }
        }
    }

    for (int v : P_minus_neighbors) {
        unordered_set<int> new_R = R;
        new_R.insert(v);

        unordered_set<int> new_P, new_X;
        if (adj.find(v) != adj.end()) {
            for (int u : P) if (adj.at(v).count(u)) new_P.insert(u);
            for (int u : X) if (adj.at(v).count(u)) new_X.insert(u);
        }

        bronKerboschPivot(new_P, new_R, new_X, adj, cliques);
        
        P.erase(v);
        X.insert(v);
    }
}

// Find maximal cliques using degeneracy ordering
vector<unordered_set<int> > bronKerboschDegeneracy(const vector<pair<int, int> >& edges) {
    const auto& [ordering, adj] = computeDegeneracyOrdering(edges);
    vector<unordered_set<int> > cliques;

    for (size_t i = 0; i < ordering.size(); ++i) {
        int vi = ordering[i];
        unordered_set<int> P, X;
        if (adj.find(vi) != adj.end()) {
            for (size_t j = i + 1; j < ordering.size(); ++j) {
                if (adj.at(vi).count(ordering[j])) P.insert(ordering[j]);
            }
            for (size_t j = 0; j < i; ++j) {
                if (adj.at(vi).count(ordering[j])) X.insert(ordering[j]);
            }
        }
        unordered_set<int> R;
        R.insert(vi);
        bronKerboschPivot(P, R, X, adj, cliques);
    }

    return cliques;
}

// Write clique size distribution to CSV
void writeCliquesToCSV(const vector<unordered_set<int> >& cliques, const string& filename) {
    unordered_map<int, int> cliqueSizeCount;
    for (const auto& clique : cliques) {
        cliqueSizeCount[clique.size()]++;
    }

    ofstream outputFile(filename);
    if (!outputFile.is_open()) {
        cerr << "Error: Could not open output file!" << endl;
        return;
    }

    outputFile << "Clique Size,Count\n";
    for (const auto& [size, count] : cliqueSizeCount) {
        outputFile << size << "," << count << "\n";
    }

    outputFile.close();
    cout << "Clique sizes and counts written to " << filename << endl;
}

// Print statistics
void printStatistics(const vector<unordered_set<int> >& cliques) {
    int maxCliqueSize = 0;
    unordered_map<int, int> cliqueSizeCount;

    for (const auto& clique : cliques) {
        int size = clique.size();
        maxCliqueSize = max(maxCliqueSize, size);
        cliqueSizeCount[size]++;
    }

    cout << "\nTotal Maximal Cliques: " << cliques.size() << endl;
    cout << "Largest Maximal Clique Size: " << maxCliqueSize << endl;
}

int main() {
    ifstream inputFile("as-skitter.txt");
    if (!inputFile.is_open()) {
        cerr << "Error: Could not open the file 'as-skitter.txt'" << endl;
        return 1;
    }

    string header;
    getline(inputFile, header);

    vector<pair<int, int> > edges;
    string line;
    while (getline(inputFile, line)) {
        if (line.empty() || line[0] == '#') continue;
        stringstream ss(line);
        int u, v;
        if (ss >> u >> v) edges.push_back(make_pair(u, v));
    }
    inputFile.close();

    cout << "Loaded " << edges.size() << " edges from the file." << endl;

    auto start = high_resolution_clock::now();

    unordered_map<int, int> vertexMap;
    auto zeroBasedEdges = remapEdgesToZeroBased(edges, vertexMap);

    auto cliques = bronKerboschDegeneracy(zeroBasedEdges);

    auto end = high_resolution_clock::now();
    double executionTime = duration<double>(end - start).count();

    printStatistics(cliques);
    writeCliquesToCSV(cliques, "grok-as-skitter.csv");

    cout << "Execution Time: " << executionTime << " seconds" << endl;
    return 0;
}
