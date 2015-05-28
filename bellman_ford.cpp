#include <cstdio>
#include <algorithm>
#define INF (1 << 29)
#define all(a) (a).begin(), (a).end()
using namespace std;
typedef pair<int, int> pii; //weight, index

int main() {
    if(fopen("jobhunt.in", "r")) {
        freopen("jobhunt.in", "r", stdin);
        freopen("jobhunt.out", "w", stdout);
    }

    int d, p, n, f, start;
    scanf("%d %d %d %d %d", &d, &p, &n, &f, &start);

    vector<vector<pii>> edges(n);
    for(int i = 0; i < p; i++) {
        int u, v;
        scanf("%d %d", &u, &v);
        edges[--u].push_back({-d, --v});
    }

    for(int i = 0; i < f; i++) {
        int u, v, t;
        scanf("%d %d %d", &u, &v, &t);
        edges[--u].push_back({t - d, --v});
    }

    vector<int> dist(n, INF);
    dist[--start] = 0;

    bool flag = false;
    for(int i = 0; i < n; i++) {
        flag = false;
        for(int curr = 0; curr < n; curr++) {
            for(auto it : edges[curr]) {
                int ndist = it.first + dist[curr];
                int next  = it.second;
                if(ndist < dist[next]) {
                    dist[next] = ndist;
                    flag = true;
                }
            }
        }
    }

    int mindist = *min_element(all(dist));
    printf("%d\n", flag ? -1 : d - mindist);

    return 0;
}
