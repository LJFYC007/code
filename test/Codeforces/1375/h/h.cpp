/***************************************************************
	File name: h.cpp
	Author: ljfcnyali
	Create time: 2020年07月10日 星期五 15时55分56秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010;
const int maxm = 1e5 + 10;
const int INF = 0x3f3f3f3f;

int n, N, q, block, a[maxn], cnt, num, id[maxn], ans[maxm], belong[maxn];
struct node 
{ 
    int l, r, id; 
    node(int a = 0, int b = 0, int c = 0) { l = a; r = b; id = c; } 
    bool operator < (const node &a) const { return l < a.l || (l == a.l && r < a.r); }
} ;
vector<int> t[maxn], B[maxn];
vector<pii> A[1000 * maxn];
pii Q[maxm];

inline int Get(int x, int pos) { return lower_bound(B[x].begin(), B[x].end(), pos) - B[x].begin(); }

inline void Build(int x, set<node> Set)
{
    B[x].clear(); 
    for ( auto it : Set ) if ( B[x].empty() || B[x].back() != it.l ) 
    {
        B[x].push_back(it.l);
        A[x * N + Get(x, it.l)].clear();
    }
    for ( auto it : Set ) A[x * N + Get(x, it.l)].push_back(pii(it.r, it.id));
}

inline int Find(int x, int l, int r)
{
    auto L = lower_bound(B[x].begin(), B[x].end(), l);
    if ( L == B[x].end() ) return 0;
    auto R = upper_bound(A[x * N + Get(x, *L)].begin(), A[x * N + Get(x, *L)].end(), pii(r, INF));
    if ( R == A[x * N + Get(x, *L)].begin() ) return 0;
    -- R;
    if ( l <= *L && (*R).first <= r ) return (*R).second;
    return 0;

}

inline set<node> Solve(int x, int l, int r)
{
    set<node> ans; ans.clear();
    if ( l > r ) return ans;
    if ( l == r ) { ans.insert(node(id[l], id[l], id[l])); return ans; }
    int Mid = l + r >> 1;
    set<node> L = Solve(x, l, Mid), R = Solve(x, Mid + 1, r);
    for ( auto it : L ) if ( it.l == it.r ) ans.insert(it);
    for ( auto it : R ) if ( it.l == it.r ) ans.insert(it);
    Build(1, L); Build(2, R);
    for ( int i = 0; i < t[x].size(); ++ i ) for ( int j = i + 1; j < t[x].size(); ++ j ) 
    {
        if ( a[t[x][i]] < l || a[t[x][j]] < l || r < a[t[x][i]] || r < a[t[x][j]] ) continue ;
        int posl = Find(1, t[x][i], t[x][j]), posr = Find(2, t[x][i], t[x][j]);
        if ( !posl || !posr ) ans.insert(node(t[x][i], t[x][j], posl + posr));
        else { printf("%d %d\n", posl, posr); ++ num; -- cnt; ans.insert(node(t[x][i], t[x][j], num)); }
    }
    return ans;
}

set<node> Set[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &q); block = sqrt(q);
    if ( n == 1 ) 
    {
        puts("1");
        REP(i, 1, q) printf("1 "); puts("");
        return 0;
    }
    N = block;
    REP(i, 1, n) belong[i] = (i - 1) / block + 1;
    REP(i, 1, n) 
    { 
        scanf("%d", &a[i]); id[a[i]] = i; 
        t[belong[a[i]]].push_back(i);
    }
    REP(i, 1, q) scanf("%d%d", &Q[i].first, &Q[i].second);

    cnt = 2 * n * block + 2848; 
    printf("%d\n", cnt);
    cnt -= n; num = n;

    for ( int l = 1, r = min(n, block); l <= n; l += block, r = min(n, r + block) ) 
        Set[belong[l]] = Solve(belong[l], l, r);
    REP(i, 1, belong[n]) Build(i, Set[i]);
    REP(i, 1, q)
    {
        int last = 0, l = Q[i].first, r = Q[i].second;
        REP(j, 1, belong[n])
        {
            int pos = Find(j, l, r);
            if ( !pos ) continue ;
            if ( last ) { printf("%d %d\n", last, pos); ++ num; -- cnt; last = num; }
            else last = pos;
        }
        ans[i] = last;
    }

    while ( cnt ) { if ( a[1] < a[2] ) puts("1 2"); else puts("2 1"); -- cnt; } 
    REP(i, 1, q) printf("%d ", ans[i]); puts("");
    return 0;
}
