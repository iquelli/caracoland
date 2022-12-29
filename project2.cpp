#include <iostream>
#include <vector>
#include <cstring>
#include <string>
#include <algorithm>
using namespace std;

struct Arc {
    int start, finish, weight;
};

struct Path {
    int parent;
    int rank;
};

int vertices;
int arcs;
vector<Path> paths;
vector<Arc> pairs;

int calculateWork();
bool comparator(Arc &arc1, Arc &arc2);
int find(int &vertex);
void unite(int &startParent, int &finishParent);

int main() {
    scanf("%d", &vertices);
    scanf("%d", &arcs);

    pairs.resize(arcs);  // initializes the vector of pairs

    for(int i = 0; i < arcs; i++) {
        int vertex1;
        int vertex2;
        int amount;

        scanf("%d %d %d", &vertex1, &vertex2, &amount);

        if(vertex1 < vertex2) {
            pairs[i].start = vertex1;
            pairs[i].finish = vertex2;
        }
        else {
            pairs[i].start = vertex2;
            pairs[i].finish = vertex1;
        }

        pairs[i].weight = amount;
    }

    printf("%d\n", calculateWork());

    return 0;
}

bool comparator(Arc &arc1, Arc &arc2) {
    return arc1.weight > arc2.weight;
}

int calculateWork() {
    int max_work = 0;
    paths.resize(vertices+1); // because there is no vertex 0

    // make set
    for(int i = 0 ;i < vertices+1; i++) {
		paths[i].parent=-1;
		paths[i].rank = 0;
	}

    sort(pairs.begin(), pairs.end(), comparator);

    int j = 0; // check if minimum number of arcs has been already found
    for(int i = 0; i< arcs; i++) {
        int startParent = find(pairs[i].start);
        int finishParent = find(pairs[i].finish);

        if(startParent != finishParent) {

            max_work += pairs[i].weight;
            unite(startParent, finishParent);

            j++;
            if(j == vertices -1)  // to not check more than necessary cases
                break;
        }
    }

    return max_work;
}

int find(int &vertex) {
    if(paths[vertex].parent == -1)
        return vertex;

    paths[vertex].parent = find(paths[vertex].parent);
    return paths[vertex].parent;
}

void unite(int &startParent, int &finishParent) {

    if(paths[startParent].rank > paths[finishParent].rank)
        paths[finishParent].parent = startParent;

    else if(paths[startParent].rank < paths[finishParent].rank)
        paths[startParent].parent = finishParent;

    else {
        paths[finishParent].parent = startParent;
        paths[startParent].rank++;
    } 
}
