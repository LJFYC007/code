/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年01月20日 星期一 09时11分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int N = 3e4;
const int Mod = 1e9 + 7;

int f[maxn], n, d, ans, g[maxn];
vector<int> t;

inline void DFS(int x)
{
    if ( x > N ) return ; ans = (ans + f[x]) % Mod;
    // printf("%lld %lld\n", x, f[x]);
    for ( auto i : t ) 
    {
        if ( !x && !i ) continue ;
        DFS(x * 10 + i);
    }
}

signed main()
{
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
    scanf("%lld%lld", &n, &d);
    REP(i, 0, d - 1) { int x; scanf("%lld", &x); if ( x ) t.push_back(i); }
    f[0] = 1;
    REP(i, 1, n)
    {
        int l, r; scanf("%lld%lld", &l, &r);
        REP(j, 0, N) g[j] = 0;
        for ( int j = N; j >= 0; -- j ) REP(k, l, r) g[j + k] = (g[j + k] + f[j]) % Mod;
        REP(j, 0, N) f[j] = g[j];
    }
    DFS(0);
    printf("%lld\n", ans);
    return 0;
}
