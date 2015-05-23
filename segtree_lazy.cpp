/*
 * Segtree with lazy propogation. This data structure supports range updates and
 * range sums both in O(lg N) time. (and it's notoriously hard to code correctly)
 *
 * The code is a solution to HORRIBLE on SPOJ.
 */
#include <cstdio>
#include <algorithm>
#include <cstring>
#define MAXN (1 << 17)
#define INF (1 << 30)
using namespace std;
typedef long long ll;

struct node {
	ll sum;
	ll numleaves;
	node() : sum(0), numleaves(1) {}
	node operator+(const node& rhs) {
		node ret;
		ret.sum = this->sum + rhs.sum;
		ret.numleaves = this->numleaves + rhs.numleaves;
		return ret;
	}
} ZERO;

node segtree[2*MAXN];
ll lazy[2*MAXN];

#define lchild (2*curr)
#define rchild (2*curr + 1)
#define mid ((lo + hi) / 2)

//pass laziness down to children
void down(int curr) { 
	segtree[curr].sum += lazy[curr] * segtree[curr].numleaves;
	if (curr < MAXN) { //curr is not a leaf
		lazy[lchild] += lazy[curr];
		lazy[rchild] += lazy[curr];
	}
	lazy[curr] = 0;
}

// set arr[left] = arr[left+1] = ... = arr[right-1] = arr[right] = val
void update(int left, int right, int val, int curr = 1, int lo = 0, int hi = MAXN - 1) {
	if (lazy[curr] != 0) down(curr);
	if (left > hi || lo > right) return;
	if (left <= lo && hi <= right) {
        lazy[curr] += val; down(curr);
        return;
	}

	update(left, right, val, lchild, lo, mid);
	update(left, right, val, rchild, mid + 1, hi);

	segtree[curr] = segtree[lchild] + segtree[rchild];
}

// find arr[left] + arr[left+1] + ... + arr[right-1] + arr[right]
node aks(int left, int right, int curr = 1, int lo = 0, int hi = MAXN - 1) {
	if (lazy[curr] != 0) down(curr);
	if (left >  hi || lo >  right) return ZERO;
	if (left <= lo && hi <= right) return segtree[curr];

	return aks(left, right, lchild, lo, mid)
		 + aks(left, right, rchild, mid+1, hi);
}

void build() {
	memset(lazy, 0, sizeof(lazy));
	for(int i=0; i<MAXN; i++)
		segtree[MAXN + i] = ZERO;
	for(int curr = MAXN - 1; curr > 0; curr--)
		segtree[curr] = segtree[lchild] + segtree[rchild];
}

void solve() {
	int n, nqueries, type, p, q, val;

    build();
	scanf("%d %d", &n, &nqueries);
	while(nqueries--) {
		scanf("%d %d %d", &type, &p, &q);
		if (p > q) swap(p, q);
		if (type) { //query
			printf("%lld\n", aks(p, q).sum);
        } else { //update
			scanf("%d", &val);
			update(p, q, val);
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while(T--)
		solve();
	return 0;
}
