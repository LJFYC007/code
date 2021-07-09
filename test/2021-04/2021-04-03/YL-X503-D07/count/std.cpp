/***************************************************************
    File name: count.cpp
    Author: ljfcnyali
    Create time: 2021年04月03日 星期六 09时04分51秒
***************************************************************/
#include<bits/stdc++.h>
 
using namespace std;
 
#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 33;
const int Mod = 10007;
 
int n, k, c, ans, fac[maxn], inv[maxn], ttt[maxn], C[1600][1600];
int f[4][17][maxn][maxn][maxn * 2];
pii a[maxn];
bool use1[maxn], use2[maxn];
 
inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int sgn(int x) { return x & 1 ? -1 : 1; } 
inline void add(int &x, int y) { x += y; }
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("count.in", "r", stdin);
    freopen("count.out", "w", stdout);
#endif
    scanf("%d%d%d", &n, &k, &c); fac[0] = inv[0] = ttt[0] = 1; 
    REP(i, 1, n) { fac[i] = fac[i - 1] * i % Mod; ttt[i] = ttt[i - 1] * 2 % Mod; }
    inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
    REP(i, 1, k) { int x, y; scanf("%d%d", &x, &y); a[i] = pii(x, y); } 
    REP(i, 0, n * n) { C[i][0] = 1; REP(j, 1, i) C[i][j] = (C[i - 1][j - 1] + C[i - 1][j]) % Mod; }
		
	REP(o, 0, 3) f[o][0][0][0][0] = 1;
    REP(S, 0, (1 << k) - 1)
    {
        mem(use1); mem(use2); int val = 0;
        REP(i, 1, k) if ( (S >> i - 1) & 1 ) { use1[a[i].first] = use2[a[i].second] = true; ++ val; } 
 
		REP(o, 0, 3) REP(i, 1, (n + 1) / 2) REP(x, 0, i + i) REP(y, 0, i + i) REP(z, 0, i * 4) f[o][i][x][y][z] = 0;
        REP(o, 0, 3) REP(i, 1, n / 2) REP(x, 0, i + i - 2) REP(y, 0, i + i - 2) REP(z, 0, i * 4 - 4) if ( f[o][i - 1][x][y][z] ) 
        {
			f[o][i - 1][x][y][z] %= Mod; const int tttt = f[o][i - 1][x][y][z]; 
            REP(X, 0, !use1[i]) REP(Y, 0, !use1[n - i + 1]) REP(s, 0, !use2[i]) REP(t, 0, !use2[n - i + 1]) 
            {
                int cnt = 0;
                if ( (o == 1 || o == 3) && !X && !s ) ++ cnt;
                if ( (o == 1 || o == 3) && !Y && !t ) ++ cnt;
                if ( (o == 2 || o == 3) && !X && !t ) ++ cnt;
                if ( (o == 2 || o == 3) && !Y && !s ) ++ cnt;
                add(f[o][i][x + X + Y][y + s + t][z + cnt], tttt);
            }
        }
        if ( n & 1 )
        {
            REP(o, 0, 3) REP(x, 0, n) REP(y, 0, n) REP(z, 0, n + n) if ( f[o][n / 2][x][y][z] ) 
            {
                REP(s, 0, 1) REP(t, 0, 1) 
                {
                    if ( use1[n / 2 + 1] && s == 1 ) continue ;
                    if ( use2[n / 2 + 1] && t == 1 ) continue ; 
                    int cnt = 0; if ( o >= 1 && !s && !t ) ++ cnt;
                    add(f[o][n / 2 + 1][x + s][y + t][z + cnt], f[o][n / 2][x][y][z]);
                }
            }
        }

        bool flag1 = false, flag2 = false;
        REP(i, 1, k) if ( (S >> i - 1) & 1 ) 
        {
            if ( a[i].first == a[i].second ) flag1 = true;
            if ( a[i].first + a[i].second == n + 1 ) flag2 = true;
        }
 
        int m = (n + 1) / 2;
        REP(o, 0, 3) REP(x, 0, n) REP(y, 0, n) REP(z, 0, n + n)
        {
			f[o][m][x][y][z] %= Mod;	
            if ( o == 1 && flag1 ) continue ; 
            if ( o == 2 && flag2 ) continue ; 
            if ( o == 3 && (flag1 || flag2) ) continue ; 
            int num = n * n - n * (x + y) + x * y - z - val;
            if ( num >= 0 )  ans = (ans + sgn(val + x + y) * ((o == 1 || o == 2) ? -1 : 1) * C[num][c - val] * f[o][m][x][y][z]) % Mod;
        }
    }
     
    printf("%d\n", (ans + Mod) % Mod);
    return 0;
}
