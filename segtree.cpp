/*
 * Segment tree: supports point updates and range queries in O(lg N) time.
 *
 * This problem is "marathon" from USACO Dec. 14 Gold. It requires us
 * to keep track of multiple segtrees.
 */
#include <cstdio>
#include <algorithm>
#define MAXN (1 << 17)
#define INF (1 << 30)
using namespace std;

struct node {
	int maxval;
	int sum;
	node()      : maxval(-INF) , sum(0) {}
	node(int a) : maxval(a)    , sum(a) {}

	node operator+(const node& rhs) {
		node ret;
		ret.maxval = max(maxval, rhs.maxval);
		ret.sum    = maxval + rhs.sum;
		return ret;
	}
} ZERO;

#define lchild (2*curr)
#define rchild (2*curr + 1)
#define mid ((lo + hi) / 2)

void build(node segtree[], int arr[]) {
	for(int i=0; i<MAXN; i++)
		segtree[MAXN + i] = node(arr[i]);
	for(int curr = MAXN - 1; curr > 0; curr--)
		segtree[curr] = segtree[lchild] + segtree[rchild];
}

void update(node segtree[], int index, int value) {
	int curr = MAXN + index;
	segtree[curr] = value;
	curr /= 2;
	for(; curr > 0; curr /= 2)
		segtree[curr] = segtree[lchild] + segtree[rchild];
}

node aks(node segtree[], int left, int right, int curr = 1, int lo = 0, int hi = MAXN - 1) {
	if (left >  hi || lo >  right) return ZERO;
	if (left <= lo && hi <= right) return segtree[curr];
	return aks(segtree, left, right, lchild, lo, mid)
		 + aks(segtree, left, right, rchild, mid+1, hi);
}

void printtree(node segtree[]) {
	for(int i = 1; i < 2 * MAXN; i++) {
		printf("%d\t", segtree[i].maxval);
		if ((i & (i + 1) )== 0) putchar('\n');
	}
}

int n, q;
int xs[MAXN], ys[MAXN];
int dists[MAXN], saved[MAXN];
node SEGdists[2*MAXN], SEGsaved[2*MAXN]; //segment trees

//distance between i'th and j'th chkpt
int getdist(int i, int j) {
	if(i < 0 || j >= n) return 0;
	return abs(xs[i] - xs[j])
	     + abs(ys[i] - ys[j]);
}

//how much can you save by skipping i'th chkpt?
int getsave(int i) {
	if(i == 0 || i == n-1) return 0;
	else return getdist(i-1, i  )
	          + getdist(i  , i+1)
              - getdist(i-1, i+1);
}

int main() {
    if(fopen("marathon.in", "r")) {
        freopen("marathon.in", "r", stdin);
        freopen("marathon.out", "w", stdout);
    }

	scanf("%d %d", &n, &q);
	for(int i=0; i<n; i++)
		scanf("%d %d", &xs[i], &ys[i]);

	for(int i=1; i<n; i++) {
		dists[i] = getdist(i-1, i);
		saved[i] = getsave(i);
	}

	build(SEGdists, dists);
	build(SEGsaved, saved);

	while(q--) {
		char buf[2];
		scanf("%s", buf);
		if(buf[0] == 'Q') { //query
			int i, j;
			scanf("%d %d", &i, &j);
			i--; j--;

			int dist = aks(SEGdists, i+1, j  ).sum;
			int save = aks(SEGsaved, i+1, j-1).maxval;
			printf("%d\n", dist - save);
		} else { //update
			int i, x, y;
			scanf("%d %d %d", &i, &x, &y);
			i--;
			xs[i] = x, ys[i] = y;

			update(SEGdists, i,   getdist(i-1, i  ));
			update(SEGdists, i+1, getdist(i  , i+1));

			update(SEGsaved, i-1, getsave(i-1));
			update(SEGsaved, i  , getsave(i  ));
			update(SEGsaved, i+1, getsave(i+1));
		}
	}
	return 0;
}
