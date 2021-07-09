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

const int maxn = 2010;
const int Mod = 1e9 + 7;
const int inv2 = (Mod + 1) / 2;

int n, k, f[maxn][maxn], a[maxn][maxn], val[maxn], Next[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void Get(int n)
{
    REP(i, 1, n)
    {
        if ( !a[i][i] ) continue ;
        REP(j, 1, n) 
        {
            if ( j == i || !a[j][i] ) continue ;
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
        REP(j, 1, i) Next[(j + k - 1) % i + 1] = j;
        REP(j, 1, i) val[j] = 0;
        REP(j, 1, i)
        {
            if ( val[j] ) continue ;
            int nex = Next[j], num = f[i][j], p = inv2;
            do
            {
                num = (num + p * f[i][nex]) % Mod;
                p = p * inv2 % Mod;
                nex = Next[nex];
            } while ( nex != j ) ;
            val[j] = num * power(1 - p, Mod - 2) % Mod;
            nex = j;
            while ( Next[nex] != j ) 
            {
                val[Next[nex]] = (val[nex] - f[i][nex]) * 2 % Mod;
                nex = Next[nex];
            }
        }
        REP(j, 2, i)
        {
            int nex = (j + (k % (i - 1)) - 1) % i + 1;
            if ( nex >= j ) -- nex;
            f[i - 1][nex] = val[j] * inv2 % Mod;
        }
    }
    printf("%lld\n", (f[1][1] + Mod) % Mod);
    // cerr << 281842771 % Mod << endl;
    return 0;
}
