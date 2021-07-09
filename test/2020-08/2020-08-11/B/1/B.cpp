/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2020年08月11日 星期二 08时42分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define lson root << 1
#define rson root << 1 | 1
#define x first
#define y second
typedef long long LL;

const int maxn = 5e5 + 10;
const int Mod = 1e9 + 7;

int n, q, a[maxn], ans[maxn];
char s[maxn];
struct Matrix { int a[11][11]; } e, f[11], g[11], fac[maxn], inv[maxn];
Matrix operator * (Matrix a, Matrix b)
{
    Matrix c; 
    REP(i, 0, 10) REP(j, 0, 10) c.a[i][j] = 0;
    REP(i, 0, 10) REP(k, 0, 10) if ( a.a[i][k] ) REP(j, 0, 10) c.a[i][j] = (c.a[i][j] + (LL)a.a[i][k] * b.a[k][j]) % Mod;
    return c;
};

inline int power(LL a, int b) { LL r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline Matrix Solve(Matrix a)
{
    int n = 10, f[30][30]; mem(f);
    REP(i, 0, n) REP(j, 0, n) f[i][j] = a.a[i][j];
    REP(i, 0, n) f[i][n + 1 + i] = 1;
    REP(i, 0, n)
    {
        int Max = i;
        REP(j, i + 1, n) if ( f[j][i] > f[Max][i] ) Max = j;
        REP(j, 0, 2 * n + 1) swap(f[i][j], f[Max][j]);
        f[i][i] = power(f[i][i], Mod - 2);
        REP(j, 0, 2 * n + 1) if ( j != i ) f[i][j] = f[i][j] * f[i][i] % Mod;
        REP(j, 0, n) if ( j != i ) REP(k, i + 1, n * 2 + 1) f[j][k] = (f[j][k] - f[j][i] * f[i][k]) % Mod;
    }
    REP(i, 0, n) REP(j, n + 1, n + n + 1) a.a[i][j - n] = f[i][j];
    return a;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("B.in", "r", stdin);
    freopen("B.out", "w", stdout);
#endif
    REP(i, 0, 10) e.a[i][i] = 1;
    scanf("%s", s + 1); n = str(s + 1); 
    REP(i, 1, n) a[i] = s[i] - 'a' + 1;
    REP(j, 1, 10)
    {
        f[j].a[0][0] = 2; f[j].a[0][j] = 1;
        REP(i, 1, 10) 
            if ( j != i ) f[j].a[i][i] = 1;
            else f[j].a[i][0] = -1;
        g[j] = Solve(f[j]);
    }
    fac[0] = inv[0] = e; 
    REP(i, 1, n)
    {
        fac[i] = fac[i - 1] * f[a[i]];
        inv[i] = g[a[i]] * inv[i - 1];
    }
    scanf("%d", &q);
    while ( q -- ) 
    {
        int l, r; scanf("%d%d", &l, &r);
        Matrix x = inv[l - 1] * fac[r];
        printf("%d\n", (x.a[0][0] - 1 + Mod) % Mod);
    }
    return 0;
}
