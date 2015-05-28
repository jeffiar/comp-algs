/*
 * My standard implementation of dijkstra's shortest path alg
 */
#include <cstdio>
#include <queue>
#include <algorithm>
#define MAXN 100100
using namespace std;
typedef pair<int, int> pii; //weight, curr
typedef priority_queue<pii, vector<pii>, greater<pii> > PQ;

bool vis[MAXN];

int main() {
    int n, m;
    scanf("%d %d", &n, &m);

    vector<vector<pii>> edges(n);
    while(m--) {
        int u, v, w;
        scanf("%d %d %d", &u, &v, &w);
        edges[u].push_back({w, v});
        edges[v].push_back({w, u});
    }

    PQ pq;
    pq.push({0,0});
    while(!pq.empty()) {
        int dist = pq.top().first;
        int curr = pq.top().second;
        pq.pop();

        if (vis[curr] != false) continue;
        vis[curr] = true;

        /*
         * curr visited in "shortest path" order here
         */

        for(pii it : edges[curr]) {
            int ndist = it.first + dist;
            int next = it.second;
            pq.push({ndist, next});
        }
    }

    return 0;
}
