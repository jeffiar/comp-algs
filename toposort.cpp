#include <cstdio>
#include <vector>
#define MAXN 100100
#define MAXM 100
using namespace std;

int n, m;
vector<int> edges[MAXN];
int indeg[MAXN];
bool visited[MAXN];

void recurse(int curr) {
    visited[curr] = true;

    //these lines are executed in topological order
    //do shit with curr

    for(auto next : edges[curr]) {
        indeg[next]--;
        if (indeg[next] == 0)
            recurse(next);
    }
}

int main() {
    scanf("%d %d", &n, &m);
    for(int i = 0; i < m; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        edges[a].push_back(b);
        indeg[b]++;
    }
    
    for(int i = 1; i <= n; i++) {
        if (visited[i]) continue;
        if (indeg[i] == 0)
            recurse(i);
    }
}
