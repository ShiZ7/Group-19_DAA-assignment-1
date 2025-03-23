#include <bits/stdc++.h>
#include <chrono>  // for timing
using namespace std;



// The adjacency for each node v: graph[v] = list of neighbors of v
static unordered_map<int, vector<int>> graphAdj;

// Also store each node’s neighbors in an unordered_set for quick checks:
static unordered_map<int, unordered_set<int>> neighborsSet;

// To avoid printing one line extra at start
static bool extra = false;

// To check max size
static int ma = 0;

// To count number of cliques
static int countclique = 0;

// To store the distribution of clique sizes
static unordered_map<int, int> cliqueSizeCount;

void EXPAND(vector<int>& SUBG, unordered_set<int>& CAND,int& clqsz);


void CLIQUES(const vector<int>& nodes)
{
    // Build SUBG and CAND
    vector<int> SUBG = nodes;
    unordered_set<int> CAND(nodes.begin(), nodes.end());  // Use unordered_set for faster lookups

    // Start recursion with empty path
    int clqsz=0;
    EXPAND(SUBG, CAND, clqsz);
}

/******************************************************************************
 * EXPAND(SUBG, CAND, pathString):
 *   If SUBG empty => "pathString + clique," => done with that line -> print
 *
 *   Else pick pivot u that maximizes |CAND ∩ neighbors(u)|.
 *   EXT_u = CAND - neighbors(u).
 *   For each q in EXT_u:
 *     localPath = pathString + (q + ", ")
 *     Recurse with (SUBG_q, CAND_q, localPath)
 *     After recursion, localPath + "back," => that is the final version
 *     print localPath on a new line
 *****************************************************************************/
void EXPAND(vector<int>& SUBG, unordered_set<int>& CAND, int& clqsz)
{
    // 1) If SUBG empty => we've found a maximal clique
    if (SUBG.empty()) {
        ma = max(ma, clqsz);
        cliqueSizeCount[clqsz]++;

        countclique++;
        return;
    }

    // 2) Choose pivot u in SUBG to maximize |CAND ∩ neighbors(u)|
    int bestU = -1;
    int bestCount = -1;
    for (int v : SUBG) {
        int overlap = 0;
        for (int w : graphAdj[v]) {
            if (CAND.count(w)) {
                overlap++;
            }
        }
        if (overlap > bestCount) {
            bestCount = overlap;
            bestU = v;
        }
    }

    // 3) EXT_u = CAND - neighbors(bestU)
    unordered_set<int> pivotN(neighborsSet[bestU].begin(), neighborsSet[bestU].end());
    vector<int> EXT_u;
    EXT_u.reserve(CAND.size());
    for (int c : CAND) {
        if (!pivotN.count(c)) {
            EXT_u.push_back(c);
        }
    }

   
    for (int q : EXT_u) {
        // Build local path for the child
        int addedsize = clqsz + 1;

        // 5) Modify SUBG and CAND for the next recursion step
        unordered_set<int> newCAND;
        vector<int> newSUBG;
        //FINI = SUBG - CAND
        //as it is Not required here we have not generated to save time complexity

        // Update SUBG and CAND based on q
        for (int s : SUBG) {
            if (neighborsSet[q].count(s)) {
                newSUBG.push_back(s);
            }
        }
        for (int c : CAND) {
            if (neighborsSet[q].count(c)) {
                newCAND.insert(c);
            }
        }

        // Recurse
        EXPAND(newSUBG, newCAND, addedsize);
        CAND.erase(q);
    }
}

/******************************************************************************
 * main() - read the file, parse # Nodes: / # Edges:, build adjacency,
 * then call CLIQUES(nodes).
 *****************************************************************************/
int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <graph_file>\n";
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Cannot open file " << argv[1] << endl;
        return 1;
    }

    int n = -1, e = -1;
    bool foundHeader = false;
    vector<pair<int, int>> edgesTemp;
    unordered_set<int> uniqueNodes;

    while (true) {
        string line;
        if (!getline(fin, line)) break;
        if (line.empty()) continue;
        if (line[0] == '#') {
            size_t posN = line.find("Nodes:");
            size_t posE = line.find("Edges:");
            if (posN != string::npos && posE != string::npos) {
                int parseN = -1, parseE = -1;
                string s = line.substr(1);
                while (!s.empty() && isspace(s[0])) s.erase(s.begin());
                stringstream ss(s);
                vector<string> tokens;
                string w;
                while (ss >> w) tokens.push_back(w);
                for (size_t i = 0; i < tokens.size(); i++) {
                    if (tokens[i].find("Nodes:") != string::npos && (i + 1) < tokens.size()) {
                        parseN = stoi(tokens[i + 1]);
                    }
                    if (tokens[i].find("Edges:") != string::npos && (i + 1) < tokens.size()) {
                        parseE = stoi(tokens[i + 1]);
                    }
                }
                if (parseN > 0 && parseE >= 0) {
                    n = parseN;
                    e = parseE;
                    foundHeader = true;
                }
            }
            continue;
        }

        stringstream ss(line);
        int u = -1, v = -1;
        ss >> u >> v;
        if (!ss) continue;
        edgesTemp.push_back({u, v});
        uniqueNodes.insert(u);
        uniqueNodes.insert(v);
    }
    fin.close();

    if (!foundHeader) {
        int mx = -1;
        for (auto& p : edgesTemp) {
            mx = max(mx, p.first);
            mx = max(mx, p.second);
        }
        n = uniqueNodes.size();
        e = edgesTemp.size();
        cerr << "[Fallback] deduce n=" << n << ", e=" << e << endl;
    }

    // Build adjacency
    for (auto& pp : edgesTemp) {
        int u = pp.first, v = pp.second;
        graphAdj[u].push_back(v);
        graphAdj[v].push_back(u);
        neighborsSet[u].insert(v);
        neighborsSet[v].insert(u);
    }

    cerr << "Graph read: n=" << uniqueNodes.size() << " e=" << e << " (expected " << e << ")" << endl;

    vector<int> nodes(uniqueNodes.begin(), uniqueNodes.end());

    // Counting single-node cliques (nodes with no neighbors)
    int singleNodeCliques = uniqueNodes.size() - n;

    // Start timing
    auto start = chrono::high_resolution_clock::now();

    CLIQUES(nodes);

    // End timing
    auto end = chrono::high_resolution_clock::now();
    chrono::duration<double> diff = end - start;
    double seconds = diff.count();

    cout << "\nElapsed time: " << seconds << " seconds\n";
    cout << "Total Cliques = " << countclique + singleNodeCliques << endl;
    cout << "Max Clique size = " << ma << endl;

    vector<int> sortedSizes;
    for (const auto& entry : cliqueSizeCount) {
        sortedSizes.push_back(entry.first);
    }

    sort(sortedSizes.begin(), sortedSizes.end());

    cout << "\nDistribution of clique sizes:\n";
    for (int size : sortedSizes) {
        cout << "Size " << size << ": " << cliqueSizeCount[size] << " cliques\n";
    }

    return 0;
}
