/***************************************************************
	File name: AGC003F.cpp
	Author: ljfcnyali
	Create time: 2021年02月18日 星期四 08时42分23秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1010;
const int Mod = 1e9 + 7;

int n, m, k, a[maxn][maxn], x, y, z;
char s[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 

struct Matrix { int n, m, f[2][2]; } f;
Matrix operator *(Matrix a, Matrix b)
{
	Matrix c; c.n = a.n; c.m = b.m;
	REP(i, 0, 1) REP(j, 0, 1)
	{
		c.f[i][j] = 0;
		REP(k, 0, 1) c.f[i][j] = (c.f[i][j] + a.f[i][k] * b.f[k][j]) % Mod;
	}
	return c;
}

inline Matrix power(Matrix a, int b)
{
	Matrix r = a; -- b;
	while ( b ) { if ( b & 1 ) r = r * a; a = a * a; b >>= 1; } 
	return r;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld%lld", &n, &m, &k);
	REP(i, 1, n) 
	{
		scanf("%s", s + 1);
		REP(j, 1, m) a[i][j] = s[j] == '#' ? 1 : 0;
	}
	REP(i, 1, n) REP(j, 1, m) if ( a[i][j] == 1 ) ++ x;
	int num1 = 0, num2 = 0;
	REP(i, 1, n) num1 += a[i][1] == 1 && a[i][m] == 1;
	REP(i, 1, m) num2 += a[1][i] == 1 && a[n][i] == 1;
	if ( !num1 && !num2 ) { printf("%lld\n", power(x, k - 1)); return 0; } 
	if ( k <= 1 || (num1 && num2) ) { printf("1\n"); return 0; }
	z = num1 + num2;
	if ( num1 ) { REP(i, 1, n) REP(j, 1, m - 1) if ( a[i][j] && a[i][j + 1] ) ++ y; }
	else { REP(i, 1, n - 1) REP(j, 1, m) if ( a[i][j] && a[i + 1][j] ) ++ y; }
	f.n = f.m = 2;
	f.f[0][0] = x; f.f[0][1] = y; f.f[1][0] = 0; f.f[1][1] = z;
	f = power(f, k - 1);
	int ans = (f.f[0][0] - f.f[0][1]) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
