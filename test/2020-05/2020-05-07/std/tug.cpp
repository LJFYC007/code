#include <cstdio>
#include <cstring>
#include <iostream>
#include <algorithm>

const int N = 120000;
const int M = 900000;
const int INF = 1e9;

int n;

struct edge {
    int sz, head[N+9], to[N+9], w[N+9], ne[N+9], ba[N+9];
    edge() {
        sz = 1, memset(head, 0, sizeof head);
    }
    inline void addedge(int u, int v, int _w) {
        to[sz] = v, ba[head[u]] = sz, w[sz] = _w, ne[sz] = head[u], head[u] = sz++;
        to[sz] = u, ba[head[v]] = sz, w[sz] = _w, ne[sz] = head[v], head[v] = sz++;
    }
    inline void del(int u, int e) {
        if(head[u] == e) head[u] = ne[e];
        ne[ba[e]] = ne[e], ba[ne[e]] = ba[e];
    }
#define inv(x) ((x-1)^1)+1
    inline void del(int e) {
        int u = to[inv(e)], v = to[e];
        del(u, e), del(v, inv(e));
    }
}g;

int deg[N+9];
int q[N+9], l, r;
int sum;
bool vis[N+9];
int to[N+9][2];
bool used[N+9];
int c[M+9];
bool ok[M+9];
int sumall;

inline int abs(int x) {
    return x < 0 ? -x : x;
}

inline void chkmin(int &x, int y) {
    if(x > y) x = y;
}

int main() {
    freopen("tug.in", "r", stdin);
    freopen("tug.out", "w", stdout);
    
    scanf("%d", &n);
    for(int i = 1; i <= 2*n; ++i) {
        int u, v, w;
        scanf("%d%d%d", &u, &v, &w);
        g.addedge(u, v+n, w);
        deg[u]++, deg[v+n]++;
    }
    for(int i = 1; i <= 2*n; ++i)
        if(deg[i] == 0) {
            puts("-1");
            exit(0);
        }
        else if(deg[i] == 1)
            q[++r] = i;
    while(l < r) {
        int u = q[++l], e = g.head[u], v = g.to[e];
        vis[u] = true;
        if(u <= n) sum += g.w[e];
        else sum -= g.w[e];
        deg[u]--, deg[v]--, g.del(e);
        if(deg[v] == 0) {
            puts("-1");
            exit(0);
        }
        else if(deg[v] == 1)
            q[++r] = v;
    }
    for(int i = 1; i <= 2*n; ++i)
        if(deg[i] == 2) {
            int temp = 2;
            for(int j = g.head[i]; j; j = g.ne[j])
                to[i][--temp] = j;
        }
    for(int i = 1; i <= 2*n; ++i)
        if(!vis[i]) {
            int sum = 0, cur = i, f = 1;
            while(true) {
                vis[cur] = true;
                if(!used[to[cur][0]]) {
                    sum += f*g.w[to[cur][0]];
                    used[to[cur][0]] = used[inv(to[cur][0])] = true;
                    cur = g.to[to[cur][0]];
                }
                else if(!used[to[cur][1]]) {
                    sum += f*g.w[to[cur][1]];
                    used[to[cur][1]] = used[inv(to[cur][1])] = true;
                    cur = g.to[to[cur][1]];
                }
                else break;
                f = -f;
            }
            if(sum < 0) sum = -sum;
            c[sum]++;
            sumall += sum;
            //printf("%d\n", sum);
        }
    ok[0] = true;
    for(int i = 1; i <= sumall; ++i)
        if(c[i]) {
            //printf("%d\n", i);
            for(int j = sumall; j >= 0; --j)
                if(ok[j])
                    for(int k = 1; k <= c[i] && !ok[j+k*i]; ++k)
                        ok[j+k*i] = true;
        }
    sum = abs(sum);
    int min = INF;
    for(int i = 0; i <= sumall; ++i)
        if(ok[i]) chkmin(min, abs(sum+2*i-sumall));
    printf("%d\n", min);
    
    fclose(stdin);fclose(stdout);
    return 0;
}
