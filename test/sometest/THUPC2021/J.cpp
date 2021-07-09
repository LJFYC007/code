/***************************************************************
	File name: J.cpp
	Author: ljfcnyali
	Create time: 2020年12月12日 星期六 13时39分40秒
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
const int Mod = 998244353;

int n, k, ans, f[510][16], a[20];

inline int calc(int pos)
{
    int x = 0; REP(i, pos - k + 1, pos) x = x * 2 + a[i];
    return x;
}

inline void Solve()
{
    REP(i, k - 1, (1 << k) - 1) if ( !a[calc(i)] ) return ;
    // REP(i, 0, (1 << k) - 1) cout << a[i]; 
    mem(f); int pos = (1 << k) - 1;
    f[pos][calc(pos)] = 1;
    REP(i, pos, n - 2) REP(j, 0, (1 << k) - 1)
    {
        if ( !f[i][j] ) continue ;
        int x;
        x = (j << 1) & ((1 << k) - 1);
        if ( a[x] ) f[i + 1][x] = (f[i + 1][x] + f[i][j]) % Mod;
        x = (j << 1 | 1) & ((1 << k) - 1);
        if ( a[x] ) f[i + 1][x] = (f[i + 1][x] + f[i][j]) % Mod;
    }
    int sum = 0;
    REP(i, 0, (1 << k) - 1) sum = (sum + f[n - 1][i]) % Mod;
    ans = (ans + sum) % Mod;
    // cout << " " << sum << endl;
}

inline void DFS(int x)
{
    if ( x == (1 << k) ) { Solve(); return ; }
    a[x] = 0; DFS(x + 1);
    a[x] = 1; DFS(x + 1);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    DFS(0);
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
