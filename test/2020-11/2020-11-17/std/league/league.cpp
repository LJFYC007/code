#include <bits/stdc++.h>

using std::pair;
using std::vector;
using std::string;

typedef long long ll;
typedef pair<int, int> pii;

#define fst first
#define snd second
#define pb(a) push_back(a)
#define mp(a, b) std::make_pair(a, b)
#define debug(...) fprintf(stderr, __VA_ARGS__)

template <typename T> bool chkmax(T& a, T b) { return a < b ? a = b, 1 : 0; }
template <typename T> bool chkmin(T& a, T b) { return a > b ? a = b, 1 : 0; }

const int oo = 0x3f3f3f3f;

string procStatus() {
    std::ifstream t("/proc/self/status");
    return string(std::istreambuf_iterator<char>(t), std::istreambuf_iterator<char>());
}

template <typename T> T read(T& x) {
    int f = 1; x = 0;
    char ch = getchar();
    for(;!isdigit(ch); ch = getchar()) if(ch == '-') f = -1;
    for(; isdigit(ch); ch = getchar()) x = x * 10 + ch - 48;
    return x *= f;
}

const int N = 300000;

struct diameter { int x, y, d; };

int sz[N + 5];
int fa[N + 5][21], dep[N + 5];
int st[N + 5], to[(N << 1) + 5], nxt[(N << 1) + 5], e = 1;

inline void addedge(int u, int v) { to[++ e] = v; nxt[e] = st[u]; st[u] = e; }

int get_up(int x, int d) {
    for(int i = 0; d > 0; ++i, d >>= 1)
        if(d & 1) x = fa[x][i];
    return x;
}

int get_lca(int x, int y) {
    if(dep[x] < dep[y]) std::swap(x, y);
    for(int i = 0, d = dep[x] - dep[y]; d > 0; ++i, d >>= 1) 
        if(d & 1) x = fa[x][i];
    if(x == y) return x;
    for(int i = 20; i >= 0; --i) 
        if(fa[x][i] != fa[y][i]) x = fa[x][i], y = fa[y][i];
    return fa[x][0];
}

inline int get_dis(int x, int y, int lca = 0) {
    if(lca) return dep[x] + dep[y] - 2*dep[lca];
    return dep[x] + dep[y] - 2*dep[get_lca(x, y)];
}

inline int get_mid(int x, int y) {
    int r = get_lca(x, y), dis = get_dis(x, y) >> 1;
    return (dep[x] - dep[r] >= dis) ? get_up(x, dis) : get_up(y, dis);
}

inline void merge(diameter& a, diameter b) {
    int len = a.d, x = a.x, y = a.y;
    if(chkmax(len, b.d)) a.x = b.x, a.y = b.y;
    if(chkmax(len, get_dis(x, b.x))) a.x = x, a.y = b.x;
    if(chkmax(len, get_dis(x, b.y))) a.x = x, a.y = b.y;
    if(chkmax(len, get_dis(y, b.x))) a.x = y, a.y = b.x;
    if(chkmax(len, get_dis(y, b.y))) a.x = y, a.y = b.y;
    a.d = len;
}

diameter sub[N + 5];
void dfs(int u, int f = 0) {

    fa[u][0] = f;
    dep[u] = dep[f] + 1;
    sub[u] = (diameter) { u, u, 0 };
    for(int i = 1; i < 21; ++i) fa[u][i] = fa[fa[u][i-1]][i-1];

    sz[u] = 1;
    for(int i = st[u]; i; i = nxt[i]) {
        int v = to[i];
        if(v == f) continue;
        dfs(v, u); sz[u] ++;
        merge(sub[u], sub[v]);
    }
}

int ans = oo;
int length[N + 5];
int sx, sy, tx0, tx1, ty0, ty1;
pair<diameter, int> *pre[N + 5];

void dfs1(int u, diameter lst, int f = 0) {

    if(f > 0) {
        int len = std::max(std::max(lst.d, (lst.d + 1) / 2 + (sub[u].d + 1) / 2 + 1), sub[u].d);

        if(chkmin(ans, length[u-1] = len)) {
            sx = u, sy = f;
            tx0 = lst.x, tx1 = lst.y;
            ty0 = sub[u].x, ty1 = sub[u].y;
        }
    }

    int c = 0;
    pre[u] = new pair<diameter, int> [sz[u] + 5];

    pre[u][c ++] = mp(lst, -1);
    for(int i = st[u]; i; i = nxt[i]) {
        int v = to[i];
        if(v == f) continue;

        diameter x = pre[u][c-1].fst;
        merge(x, sub[v]); pre[u][c ++] = mp(x, v);
    }

    diameter suf = lst, temp;
    merge(suf, (diameter) { u, u, 0 });

    for(int i = c - 1; i > 0; --i) {
        int v = pre[u][i].snd;

        merge(temp = suf, pre[u][i-1].fst);
        dfs1(v, temp, u); merge(suf, sub[v]);
    }
}

int n;
int main() {
    freopen("league.in", "r", stdin);
    freopen("league.out", "w", stdout);

    read(n);
    for(int i = 1; i < n; ++i) {
        static int u, v;
        read(u), read(v);
        addedge(u, v); addedge(v, u);
    }

    dfs(1);
    dfs1(1, (diameter) { 1, 1, 0 });

    vector<int> plan;
    for(int i = 1; i < n; ++i) if(length[i] == ans) plan.pb(i);

    printf("%d\n", ans);
    printf("%lu ", plan.size()); for(auto v : plan) printf("%d ", v);
    printf("\n%d %d %d %d\n", sx, sy, get_mid(tx0, tx1), get_mid(ty0, ty1));

    return 0;
}
