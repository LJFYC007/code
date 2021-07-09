/***************************************************************
	File name: P4999.cpp
	Author: ljfcnyali
	Create time: 2019年10月21日 星期一 21时04分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 210;
const int Mod = 1e9 + 7;

int T, tmp[maxn], tot, f[maxn][maxn];

inline int DFS(int x, int sum, int opt)
{
    if ( !x ) return sum;
    if ( !opt && f[x][sum] ) return f[x][sum];
    int Max = opt ? tmp[x] : 9, ret = 0;
    REP(i, 0, Max) ret = (ret + DFS(x - 1, sum + i, opt & (i == Max))) % Mod;
    if ( !opt ) f[x][sum] = ret;
    return ret;
}

inline int Solve(int x)
{
    tot = 0;
    while ( x ) { tmp[++ tot] = x % 10; x /= 10; }
    return DFS(tot, 0, 1);
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld", &T);
    while ( T -- ) 
    {
        int l, r; scanf("%lld%lld", &l, &r);
        printf("%lld\n", (Solve(r) - Solve(l - 1) + Mod) % Mod);
    }
    return 0;
}
