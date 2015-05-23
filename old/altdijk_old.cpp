#include <cstdio>
#include <vector>
#include <queue>
#include <algorithm>
#include <cstring>
#define repi(a, i) for(typeof((a).begin()) i = (a).begin(), _##i = (a).end(); i != _##i; i++) 
#define MAXN 100100
using namespace std;
typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, int> node; //weight, curr
typedef priority_queue<node, vector<node>, greater<node> > PQ;

vector<pii> edges[MAXN];
int from[MAXN], vis[MAXN]; 
ll dists[MAXN];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	while(m--) {
		int u, v, w;
		scanf("%d %d %d", &u, &v, &w);
		edges[u].push_back(pii(w, v));
		edges[v].push_back(pii(w, u));
	}

	memset(dists, 127, sizeof (dists));
	dists[1] = 0;
	PQ pq;
	pq.push(node(0, 1));
	while(!pq.empty()) {
		ll dist = pq.top().first;
		int curr = pq.top().second;
		pq.pop();

		if (vis[curr] != 0) continue;
		vis[curr] = 1;

		//printf("visiting node %d\n", curr);

		if (curr == n) break;

		repi(edges[curr], it) {
			ll ndist = it->first + dist;
			int next = it->second;
			if(ndist < dists[next]) {
				dists[next] = ndist;
				from[next] = curr;
				pq.push(node(ndist, next));
			}
		}
	}


	//for(int i=1; i<=5; i++)
		//printf("from[%d] = %d\n", i, from[i]);

	if (from[n] == 0) //we didn't visit it
		puts("-1");
	else {
		vector<int> order;
		for(int curr = n; curr != 0; curr = from[curr])
			order.push_back(curr);
		reverse(order.begin(), order.end());
		repi(order, it)
			printf("%d%c", *it, (*it == n) ? '\n' : ' ');
	}

	return 0;
}
