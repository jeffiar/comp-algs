#include <cstdio>
#include <vector>
#include <cmath>
#include <algorithm>
#define MAXN 100000
#define RANGE_SUM 0
#define RANGE_MIN 1
#define RANGE_MAX 2
using namespace std;

void build_segtree(vector<int>& segtree, vector<int>& arr, int type);
void update(vector<int>& segtree, int pos, int val, int type);
int range_sum(vector<int>& segtree, int start, int end);
int range_min(vector<int>& segtree, int start, int end);
int range_max(vector<int>& segtree, int start, int end);

int main() {
	

	return 0;
}

void build_h(int type, vector<int>& arr, vector<int>& segtree, int node, int lo, int hi) {
	if (lo == hi)
		segtree[node] = arr[lo];
	else {
		int mid = (lo + hi) / 2;
		build_h(type, arr, segtree, 2*node    , lo     , mid);
		build_h(type, arr, segtree, 2*node + 1, mid + 1, hi );

		int left = segtree[2*node], right = segtree[2*node + 1];
		if (type == RANGE_SUM)
			segtree[node] = left + right;
		else if (type == RANGE_MIN)
			segtree[node] = min(left, right);
		else if (type == RANGE_MAX)
			segtree[node] = max(left, right);
	}
}

void build_segtree(vector<int>& segtree, vector<int>& arr, int type) {
	int length = (int)(pow(2.0, 1 + floor((log((double)arr.size()) / log(2.0)) + 1)));
	segtree.resize(length, 0);
	
	int sentinel = (type == RANGE_MIN) ? (1 << 30) : 0;
	while(arr.size() != length/2)
		arr.push_back(sentinel);

	build_h(type, arr, segtree, 1, 0, arr.size() - 1);
}

int query(int type, vector<int>& segtree, int node, int lo, int hi, int start, int end) {
	if (hi < start  || end <  lo) return -1;
	if (start <= lo && hi <= end) return segtree[node];

	int mid = (lo + hi) / 2;
	int left  = query(type, segtree, 2*node    , lo     , mid, start, end);
	int right = query(type, segtree, 2*node + 1, mid + 1, hi , start, end);

	if (left == -1) return right;
	if (right == -1) return left;

	if (type == RANGE_SUM)
		return left + right;
	else if (type == RANGE_MIN)
		return min(left, right);
	else if (type == RANGE_MAX)
		return max(left, right);
}

void update(vector<int>& segtree, int pos, int val, int type) {
	int node = (segtree.size() / 2) + pos;
	segtree[node] = val;
	node /= 2;
	//printf("updating %dth value to %d\n", pos, val);
	while(node > 0) {
		int left = segtree[2*node], right = segtree[2*node + 1];
		if (type == RANGE_SUM)
			segtree[node] = left + right;
		else if (type == RANGE_MIN)
			segtree[node] = min(left, right);
		else if (type == RANGE_MAX)
			segtree[node] = max(left, right);
		node /= 2;
	}
}

int range_sum(vector<int>& segtree, int start, int end) 
{ return query(RANGE_SUM, segtree, 1, 0, segtree.size()/2 - 1, start, end); }

int range_min(vector<int>& segtree, int start, int end) 
{ return query(RANGE_MIN, segtree, 1, 0, segtree.size()/2 - 1, start, end); }

int range_max(vector<int>& segtree, int start, int end) 
{ return query(RANGE_MAX, segtree, 1, 0, segtree.size()/2 - 1, start, end); }

void printsegtree(vector<int>& segtree) {
	for(int i=0; i<segtree.size(); i++) {
		printf("%d\t", segtree[i]);
		if ((i & (i + 1) )== 0) putchar('\n');
	}

}
