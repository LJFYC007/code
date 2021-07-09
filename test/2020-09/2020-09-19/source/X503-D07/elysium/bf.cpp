/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2020年09月19日 星期六 09时20分44秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, Begin[maxn], Next[maxn], To[maxn], e, a[maxn], ans;
struct node { int x, d, c; } b[maxn];
bool vis[maxn], use[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void Find(int u, int dep)
{
    if ( dep < 0 ) return ; 
    vis[u] = false;
    for ( int i = Begin[u]; i; i = Next[i] ) Find(To[i], dep - 1);
}

inline void DFS(int x, int sum)
{
    if ( x == m + 1 ) 
    { 
        REP(i, 1, n) vis[i] = true;
        REP(i, 1, m) if ( !use[i] ) Find(b[i].x, b[i].d);
        REP(i, 1, n) if ( vis[i] ) sum += a[i];
        /*
        if ( sum == 668 )
        {
            REP(i, 1, m) if ( !use[i] ) printf("%d ", i); puts("");
        }
        */
        ans = max(ans, sum); return ; 
    }
    DFS(x + 1, sum);  
    use[x] = true; DFS(x + 1, sum - b[x].c); use[x] = false;
}

int main()
{
    freopen("elysium.in", "r", stdin);
    freopen("elysium1.out", "w", stdout);
    scanf("%d%d", &n, &m);
    REP(i, 2, n) { int u; scanf("%d", &u); add(u, i); }
    int sum = 0; REP(i, 1, n) { scanf("%d", &a[i]); sum += a[i]; }
    REP(i, 1, m) scanf("%d%d%d", &b[i].x, &b[i].d, &b[i].c);
    DFS(1, 0);
    printf("%d\n", ans);
    return 0;
}
