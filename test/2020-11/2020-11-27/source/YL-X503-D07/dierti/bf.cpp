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

int n, Begin[maxn], Next[maxn], To[maxn], e, Root, f[maxn], fa[maxn], K, sum, ans;

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

inline void DFS(int u)
{
    for ( int i = Begin[u]; i; i = Next[i] ) 
    {
        int v = To[i]; DFS(v);
        f[u] = min(f[u], f[v]);
    }
}

inline int Solve(int x)
{
    int ret = 1, lst = x; x = fa[x];
    while ( x ) 
    {
        if ( x <= K ) ++ ret; 
        else 
        {
            bool flag = false;
            for ( int i = Begin[x]; i; i = Next[i] ) 
            {
                int v = To[i]; if ( v == lst ) continue ;
                if ( f[v] <= K ) flag = true;
            }
            if ( flag ) ++ ret;
        }
        lst = x; x = fa[x];
    }
    return ret;
}

signed main()
{
    freopen("dierti.in", "r", stdin);
    freopen("dierti.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) { scanf("%lld", &fa[i]); if ( fa[i] ) add(fa[i], i); else Root = i; }
    REP(i, 1, n) f[i] = i;
    DFS(Root);
    ans = 1;
    REP(o, 1, n)
    {
        K = o; sum = 0;
        REP(i, 1, o) sum += Solve(i);
        // cout << sum << endl;
        ans = ans * sum % Mod;
    }
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
