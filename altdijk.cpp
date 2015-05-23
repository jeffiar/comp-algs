/*
 * An (uglyish) implementation of dijkstra's shortest path alg
 * with backtracing the path. Solution to codeforces 20C...
 */

#include <cstdio>
#include <climits>
#include <algorithm>
#include <queue>
#define all(a) (a).begin(), (a).end()
using namespace std;

typedef long long ll;
typedef pair<ll, int> pii; //dist, node #

int main() {
    if(fopen("altdijk.in", "r")) {
        freopen("altdijk.in", "r", stdin);
        freopen("altdijk.out", "w", stdout);
    }

	int n, m;
	scanf("%d %d", &n, &m);

    //yuck I don't like 1-based indexing
    vector<vector<pii>> edges(n+1);
    vector<ll> dists(n+1, LLONG_MAX);
    vector<int> from(n+1), vis(n+1);

	while(m--) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edges[u].push_back({w, v});
		edges[v].push_back({w, u});
	}

	priority_queue<pii, vector<pii>, greater<pii>>  pq;
    int start = 1;
	pq.push({0, start});
	dists[start] = 0;

	while(!pq.empty()) {
		ll dist = pq.top().first;
		int curr = pq.top().second;
		pq.pop();

		if (vis[curr] != 0) continue;
		vis[curr] = 1;

		//printf("visiting node %d\n", curr);
        
		if (curr == n) break;

        for(auto it : edges[curr]) {
			ll ndist = it.first + dist;
			int next = it.second;
			if(ndist < dists[next]) {
				dists[next] = ndist;
				from[next]  = curr;
				pq.push({ndist, next});
			}
		}
	}

	if (from[n] != 0) { 
        // print out order backwards
		vector<int> order;
		for(int curr = n; curr != 0; curr = from[curr])
			order.push_back(curr);
        reverse(all(order));
        for(int curr : order)
			printf("%d%c", curr, (curr == n) ? '\n' : ' ');
    } else {
        //we didn't visit it
		puts("-1");
	}

	return 0;
}
