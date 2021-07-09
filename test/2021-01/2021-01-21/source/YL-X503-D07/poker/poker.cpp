/***************************************************************
	File name: poker.cpp
	Author: ljfcnyali
	Create time: 2021年01月21日 星期四 11时46分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 510;
const int Mod = 998244353;

int n, m, k, a[maxn], tot, N;
struct Matrix { int n, m, a[maxn][maxn]; } F, G, f[maxn * 5];
Matrix operator * (Matrix a, Matrix b)
{
    Matrix c; c.n = a.n; c.m = b.m;
    REP(i, 1, c.n) REP(j, 1, c.m)
    {
        c.a[i][j] = 0;
        REP(k, 1, a.m) c.a[i][j] += a.a[i][k] * b.a[k][j];
        c.a[i][j] %= Mod;
    }
    return c;
}
inline Matrix power(Matrix a, int b) { Matrix r = a; -- b; while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; } return r; } 
inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

signed main()
{
    freopen("poker.in", "r", stdin);
    freopen("poker.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &k);
    REP(i, 1, n) { scanf("%lld", &a[i]); N += a[i]; } 
    F.n = F.m = G.n = n + 1; G.m = 1;   
    REP(i, 2, n + 1) F.a[i][i - 1] = 1; F.a[n + 1][n + 1] = 1;
    REP(i, 1, n) F.a[i][n] = a[n - i + 1] * power(N, Mod - 2) % Mod;
    G.a[1][n] = G.a[1][n + 1] = 1;
    f[0] = G; REP(i, 1, m + m) f[i] = f[i - 1] * F;
      

    return 0;
}
