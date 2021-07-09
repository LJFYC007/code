/***************************************************************
	File name: dierti.cpp
	Author: ljfcnyali
	Create time: 2020年11月27日 星期五 08时42分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 1e9 + 7;

int n, Begin[maxn], Next[maxn], To[maxn], e, Root, fa[maxn], sum, K, ans = 1;
int size[maxn], p[maxn];
bool vis[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline bool Check(int x) 
{ 
    if ( vis[x] ) return false;
    int son = 0;
    for ( int i = Begin[x]; i; i = Next[i] ) if ( size[To[i]] ) ++ son;
    if ( son >= 2 ) vis[x] = true;
    return son == 1;
}

inline void Solve(int x)
{
    if ( x < K ) { p[x] = true; return ; }
    if ( size[x] ) 
    {
        if ( Check(x) ) { sum += size[x]; p[x] = true; }
        return ;
    }
    Solve(fa[x]);
}

inline void Get(int x, int y)
{
    if ( !y ) return ;
    if ( p[y] ) ++ sum;
    Get(fa[x], fa[y]);
}

inline void Maintain(int x)
{
    if ( x == 0 ) return ;
    ++ size[x]; Maintain(fa[x]);
}

signed main()
{
    freopen("dierti.in", "r", stdin);
    freopen("dierti.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld", &fa[i]); if ( fa[i] ) add(fa[i], i); else Root = i; }
    REP(i, 1, n)
    {
        K = i; 
        if ( Check(i) ) { sum += size[i]; p[i] = true; }
        else if ( !size[i] ) Solve(fa[i]);
        ++ sum; Get(i, fa[i]); Maintain(i);
        // cout << sum << endl;
        ans = ans * sum % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
