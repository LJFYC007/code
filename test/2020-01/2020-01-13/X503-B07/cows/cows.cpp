/***************************************************************
	File name: cows.cpp
	Author: ljfcnyali
	Create time: 2020年01月13日 星期一 08时06分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010;
const int maxm = 40000010;

int n, m, a[60][60], Begin[maxn], Next[maxn], To[maxn], e, vis[60], f[maxm];
vector<int> t;
LL ans;
bool p[60];
char s[60];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS1(int x)
{
    if ( x == m + 1 ) 
    {
        int ret = 0;
        for ( auto i : t ) ret |= 1 << i - 1;
        f[ret] = 1;
        return ;
    }
    vis[x] = 1; 
    bool flag = true;
    for ( auto i : t ) if ( !a[i][x] ) flag = false;
    if ( flag ) { t.push_back(x); DFS1(x + 1); t.pop_back(); }
    vis[x] = 0;
    DFS1(x + 1);
}

inline void DFS2(const int x, const int sum)
{
    if ( x == m ) 
    {
        int ret = 0;
        REP(i, 1, m) if ( vis[i] == sum ) ret |= 1 << i - 1;
        ans += !sum ? f[(1 << m) - 1] : f[ret];
        return ;
    }
    DFS2(x - 1, sum);
    if ( vis[x] != sum ) return ;
    p[x] = true;
    for ( int i = Begin[x]; i; i = Next[i] ) ++ vis[To[i]];
    DFS2(x - 1, sum + 1);
    for ( int i = Begin[x]; i; i = Next[i] ) -- vis[To[i]];
    p[x] = false;
}

signed main()
{
    freopen("cows.in", "r", stdin);
    freopen("cows.out", "w", stdout);
    scanf("%d", &n); 
    m = n >> 1;
    REP(i, 1, n)
    {
        scanf("%s", s + 1);
        REP(j, 1, n) if ( s[j] == '1' ) { if ( i > j ) add(i, j); a[i][j] = 1; }
    }
    DFS1(1);
    REP(i, 1, m) REP(j, 0, (1 << i - 1) - 1) REP(k, 0, (1 << m - i) - 1) 
        f[(j << m - i + 1) | k | (1 << m - i)] += f[(j << m - i + 1) | k];
    DFS2(n, 0);
    printf("%lld\n", ans);
    return 0;
}
