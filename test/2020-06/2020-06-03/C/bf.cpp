/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2020年06月03日 星期三 10时19分25秒
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
const int inv2 = (Mod + 1) / 2;

int n, k, f[maxn][maxn], a[maxn][maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void Get(int n)
{
    REP(i, 1, n)
    {
        if ( !a[i][i] ) continue ;
        REP(j, 1, n) 
        {
            if ( j == i ) continue ;
            int tmp = a[j][i] * power(a[i][i], Mod - 2) % Mod;
            REP(k, 1, n + 1) a[j][k] = (a[j][k] - a[i][k] * tmp) % Mod;
        }
    }
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("C.in", "r", stdin);
    freopen("C.out", "w", stdout);
#endif
    scanf("%lld%lld", &n, &k);
    f[n][(k - 1) % n + 1] = 1; 
    for ( int i = n; i >= 2; -- i )
    {
        mem(a);
        REP(j, 1, i) 
        { 
            a[j][i + 1] = f[i][j];
            a[j][j] = 1;
            a[(j + k - 1) % i + 1][j] = -inv2;
        }
        Get(i);    
        REP(j, 2, i)
        {
            int nex = (j + k - 1) % i + 1;
            if ( nex >= j ) -- nex;
            f[i - 1][nex] = (a[j][i + 1] * power(a[j][j], Mod - 2) % Mod) * inv2 % Mod;
        }
    }
    printf("%lld\n", (f[1][1] + Mod) % Mod);
    return 0;
}
