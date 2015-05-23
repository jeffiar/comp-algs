/* 
 * BIT or fenwick tree is a data structure supporting an O(lg N)
 * finding prefix sums (aks) and setting values (set).
 *
 * This problem is "mdeian" from USACO Nov 11 Gold.
 */
#include <cstdio>
#define MAXN (2 << 17)
using namespace std;

int arr[MAXN], tree[2 * MAXN];

// find arr[0] + arr[1] + ... + arr[curr]
int aks(int curr) {
    int psum = 0;
    for (int i = curr + MAXN; i > 0; i -= (i & -i))
        psum += tree[i];
    return psum;
}

// set arr[curr] = val
void set(int curr, int val) {
    for (int i = curr + MAXN; i < 2*MAXN; i += (i & -i))
        tree[i] += val;
}

int main() {
    if(fopen("median.in", "r")) {
        freopen("median.in", "r", stdin);
        freopen("median.out", "w", stdout);
    }

    int n, x;
    scanf("%d%d", &n, &x);
    for (int i = 0; i < n; ++i) {
        scanf("%d", &arr[i]);
        arr[i] = (arr[i] >= x ? 1 : -1);
    }

    int sum = 0;
    long long total = 0;
    set(0, 1);

    for (int i = 0; i < n; ++i) {
        sum += arr[i];
        total += aks(sum);
        set(sum, 1);
    }

    printf("%lld\n", total);
    return 0;
}
