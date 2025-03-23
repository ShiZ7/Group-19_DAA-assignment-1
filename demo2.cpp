#include <bits/stdc++.h>
#include <chrono>

using namespace std;
using namespace std::chrono;

/*
Pseudocode reference:

procedure CLIQUE;
    procedure UPDATE(i, C);
        begin
            if i = n + 1 then
                print out a new clique C
            else
                if C ∩ N(i) ≠ ∅ then UPDATE(i + 1, C)

                // (maximality test + lexicographical test)
                if both "maximality test" and "lexico. test" succeed then
                    SAVE := C - N(i)
                    C := (C ∩ N(i)) ∪ {i}
                    UPDATE(i + 1, C)
                    C := (C - {i}) ∪ SAVE
        end
    begin
        sort the vertices by degree
        initialize S[i] := 0, T[i] := 0 for each vertex i
        C := {first vertex of the graph}
        UPDATE(2, C)
    end
*/

// ----------------------------------------------------------------------------
// Global data structures
// ----------------------------------------------------------------------------
static unordered_map<int, vector<int>> graphAdj;
static unordered_map<int, unordered_set<int>> neighborsSet;

static int totalVertices;
static int ma = 0;                      
static long long totalMaximalCliques = 0; 
static unordered_map<int, long long> cliqueSizeCount;

static vector<int> maximalitySupport; 
static vector<int> adjacencyTemporary;

// ----------------------------------------------------------------------------
// UPDATE(i, currentClique): main recursion
// Implements lines from the pseudocode inside commented references.
// ----------------------------------------------------------------------------
void UPDATE(int i, vector<int> currentClique)
{
    // (Pseudo line: if i = n + 1 then print out new clique C)
    if (i == totalVertices + 1) {
        if (!currentClique.empty()) {
            int sz = (int)currentClique.size();
            cliqueSizeCount[sz]++;
            ma = max(ma, sz);
            totalMaximalCliques++;
        }
        return;
    }

    // (Pseudo line: if C ∩ N(i) ≠ ∅ then UPDATE(i + 1, C))
    {
        unordered_set<int> cliqueSet(currentClique.begin(), currentClique.end());
        bool intersectNotEmpty = false;
        for (int nbr : graphAdj[i]) {
            if (cliqueSet.find(nbr) != cliqueSet.end()) {
                intersectNotEmpty = true;
                break;
            }
        }
        if (intersectNotEmpty) {
            UPDATE(i + 1, currentClique);
        }
    }

    // (Pseudo lines: "if both 'maximality test' and 'lexico test' succeed then
    // SAVE := C - N(i); C := (C ∩ N(i)) ∪ {i}; UPDATE(i+1, C); revert...")

    unordered_set<int> neighborsOfI(neighborsSet[i].begin(), neighborsSet[i].end());

    // SAVE = C - N(i)
    vector<int> SAVE;
    SAVE.reserve(currentClique.size());
    for (int c : currentClique) {
        if (neighborsOfI.find(c) == neighborsOfI.end()) {
            SAVE.push_back(c);
        }
    }

    // C_intersectN = C ∩ N(i)
    vector<int> cIntersectN;
    cIntersectN.reserve(currentClique.size());
    for (int c : currentClique) {
        if (neighborsOfI.find(c) != neighborsOfI.end()) {
            cIntersectN.push_back(c);
        }
    }

    // newClique = (C ∩ N(i)) ∪ {i}
    vector<int> newClique = cIntersectN;
    newClique.push_back(i);

    for (size_t idx = 0; idx < adjacencyTemporary.size(); idx++) {
        adjacencyTemporary[idx] = 0;
        maximalitySupport[idx] = 0;
    }

    unordered_set<int> oldCliqueSet(currentClique.begin(), currentClique.end());

    for (int vertex : cIntersectN) {
        for (int adj : graphAdj[vertex]) {
            if (adj == i) continue;
            if (oldCliqueSet.find(adj) == oldCliqueSet.end()) {
                adjacencyTemporary[adj]++;
            }
        }
    }

    // differenceSet = currentClique - neighbors(i)
    vector<int> differenceSet;
    differenceSet.reserve(currentClique.size());
    for (int c : currentClique) {
        if (neighborsOfI.find(c) == neighborsOfI.end()) {
            differenceSet.push_back(c);
        }
    }

    for (int df : differenceSet) {
        for (int adj : graphAdj[df]) {
            if (oldCliqueSet.find(adj) == oldCliqueSet.end()) {
                maximalitySupport[adj]++;
            }
        }
    }

    bool isMaximal = true;
    int intersectionSize = (int)cIntersectN.size();

    // (maximality test / lexico test portion)
    for (int adj : graphAdj[i]) {
        if (adj >= i) continue;
        if (oldCliqueSet.find(adj) != oldCliqueSet.end()) continue;
        if (adjacencyTemporary[adj] == intersectionSize) {
            isMaximal = false;
            break;
        }
    }

    if (isMaximal) {
        vector<int> sortedDiff = differenceSet;
        sort(sortedDiff.begin(), sortedDiff.end());
        int setSize = (int)sortedDiff.size();

        // Additional lexico + maximal checks from your advanced code:
        for (int pos = 0; pos < (int)sortedDiff.size(); pos++) {
            int cur = sortedDiff[pos];
            for (int adj : graphAdj[cur]) {
                if (adj >= i) continue;
                if (oldCliqueSet.find(adj) != oldCliqueSet.end()) continue;
                if (adjacencyTemporary[adj] == intersectionSize) {
                    if (adj >= cur) {
                        maximalitySupport[adj]--;
                    } else {
                        bool isFirstCandidate = true;
                        for (int p2 = 0; p2 < pos; p2++) {
                            if (sortedDiff[p2] > adj) {
                                isFirstCandidate = false;
                                break;
                            }
                        }
                        if (isFirstCandidate) {
                            if ((maximalitySupport[adj] + pos == setSize) &&
                                (pos == 0 || adj >= sortedDiff[pos-1])) {
                                isMaximal = false;
                            }
                        }
                    }
                }
            }
        }

        if (!cIntersectN.empty()) {
            for (int vx : cIntersectN) {
                for (int adj : graphAdj[vx]) {
                    if (adj >= i) continue;
                    if (oldCliqueSet.find(adj) != oldCliqueSet.end()) continue;
                    if (adjacencyTemporary[adj] == intersectionSize && maximalitySupport[adj] == 0) {
                        if (sortedDiff.empty() || sortedDiff.back() < adj) {
                            isMaximal = false;
                        }
                    }
                }
            }
        } else {
            if (!sortedDiff.empty() && sortedDiff.back() < i - 1) {
                isMaximal = false;
            }
        }
    }

    {
        for (int vx : cIntersectN) {
            for (int adj : graphAdj[vx]) {
                if (adj == i) continue;
                adjacencyTemporary[adj] = 0;
            }
        }
        for (int df : differenceSet) {
            for (int adj : graphAdj[df]) {
                maximalitySupport[adj] = 0;
            }
        }
    }

    if (isMaximal) {
        sort(newClique.begin(), newClique.end());
        newClique.erase(unique(newClique.begin(), newClique.end()), newClique.end());
        UPDATE(i + 1, newClique);
        // "C := (C - {i}) ∪ SAVE" is automatically undone since 'currentClique' is unchanged
    }
}

int main(int argc, char** argv)
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    if (argc < 2) {
        cerr << "Usage: " << argv[0] << " <graph_file>" << endl;
        return 1;
    }

    ifstream fin(argv[1]);
    if (!fin) {
        cerr << "Cannot open file " << argv[1] << endl;
        return 1;
    }

    int n = -1, e = -1;
    bool foundHeader = false;
    vector<pair<int,int>> edgesTemp;
    unordered_set<int> uniqueNodes;

    while (true) {
        string line;
        if (!getline(fin, line)) break;
        if (line.empty()) continue;
        if (line[0] == '#') {
            size_t posN = line.find("Nodes:");
            size_t posE = line.find("Edges:");
            if (posN != string::npos && posE != string::npos) {
                int parseN=-1, parseE=-1;
                string s = line.substr(1);
                while (!s.empty() && isspace(s[0])) s.erase(s.begin());
                stringstream ss(s);
                vector<string> tokens;
                string w;
                while (ss >> w) tokens.push_back(w);
                for (size_t i=0; i<tokens.size(); i++){
                    if (tokens[i].find("Nodes:") != string::npos && (i+1)<tokens.size()){
                        parseN = stoi(tokens[i+1]);
                    }
                    if (tokens[i].find("Edges:") != string::npos && (i+1)<tokens.size()){
                        parseE = stoi(tokens[i+1]);
                    }
                }
                if (parseN>0 && parseE>=0){
                    n= parseN; e= parseE;
                    foundHeader=true;
                }
            }
            continue;
        }
        stringstream ss(line);
        int u,v;
        ss >> u >> v;
        if (!ss) continue;
        edgesTemp.push_back({u,v});
        uniqueNodes.insert(u);
        uniqueNodes.insert(v);
    }
    fin.close();

    int initial_n = n;
    if (!foundHeader){
        n = (int)uniqueNodes.size();
        e = (int)edgesTemp.size();
        cerr << "[Fallback] deduce n="<<n<<", e="<<e<<endl;
    }

    for (auto &ed : edgesTemp){
        int u = ed.first, v = ed.second;
        graphAdj[u].push_back(v);
        graphAdj[v].push_back(u);
        neighborsSet[u].insert(v);
        neighborsSet[v].insert(u);
    }
    cerr<<"Graph read: n="<<uniqueNodes.size()<<" e="<<e<<" (expected "<<e<<")\n";

    vector<pair<int,int>> vertexDegreeList;
    for (int vx: uniqueNodes){
        int deg = (int)neighborsSet[vx].size();
        vertexDegreeList.push_back({vx, deg});
    }
    sort(vertexDegreeList.begin(), vertexDegreeList.end(),
        [](auto &a, auto &b){ return a.second< b.second; });

    vector<int> sortedVertices;
    for (auto &p: vertexDegreeList){
        sortedVertices.push_back(p.first);
    }
    totalVertices = (int)sortedVertices.size();

    int maxLabel = 0;
    for (int vx: sortedVertices){
        auto &adjv = graphAdj[vx];
        sort(adjv.begin(), adjv.end());
        adjv.erase(unique(adjv.begin(), adjv.end()), adjv.end());
        if (vx > maxLabel) maxLabel = vx;
    }

    maximalitySupport.resize(maxLabel+2, 0);
    adjacencyTemporary.resize(maxLabel+2, 0);

    int singleNodeCliques = 0;
    if (initial_n>0){
        singleNodeCliques = initial_n - (int)uniqueNodes.size();
    }

    auto startTime = high_resolution_clock::now();

    // (Pseudo line: "C := {first vertex of the graph}" => we do 'UPDATE(2, {1})' for your approach)
    UPDATE(2, {1});

    auto endTime = high_resolution_clock::now();
    double secs = duration_cast<duration<double>>(endTime - startTime).count();

    cout<<"\nElapsed time: "<<secs<<" seconds\n";
    cout<<"Total Cliques = "<<(totalMaximalCliques + singleNodeCliques)<<"\n";
    cout<<"Max Clique size = "<<ma<<"\n";

    vector<int> sizeKeys;
    for (auto &kv: cliqueSizeCount){
        sizeKeys.push_back(kv.first);
    }
    sort(sizeKeys.begin(), sizeKeys.end());

    cout<<"\nDistribution of clique sizes:\n";
    for (int s : sizeKeys){
        cout<<"Size "<<s<<": "<<cliqueSizeCount[s]<<" cliques\n";
    }

    return 0;
}
