/***************************************************************
  File name: A.cpp
Author: ljfcnyali
Create time: 2021年03月07日 星期日 09时06分22秒
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
const int Mod = 1e9 + 7;

int n, a[maxn], sum, ans, f[65], num = 1, fac[maxn], inv[maxn], S;

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : (fac[n] * inv[m] % Mod) * inv[n - m] % Mod; } 

inline int Query(int x)
{
	for ( int i = 62; i >= 0; -- i ) if ( (x >> i) & 1 ) 
	{
		if ( !f[i] ) return 0;
		x ^= f[i];
	}
	return num;
}

inline void Insert(int x)
{
	for ( int i = 62; i >= 0; -- i ) if ( (x >> i) & 1 ) 
	{
		if ( !f[i] ) { f[i] = x; return ; } 
		x ^= f[i];
	}
	num = num * 2 % Mod;
}

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	REP(i, 1, n) { scanf("%lld", &a[i]); sum ^= a[i]; S ^= a[i]; }
	sort(a + 1, a + n + 1);
	if ( sum == 0 ) ans = 1;
	for ( int r = n, l; r >= 1; r = l - 1 ) 
	{
		l = r; while ( l > 1 && a[l - 1] == a[l] ) -- l; 
		REP(i, l, r) sum ^= a[i];
		REP(i, 1, r - l + 1)
		{
			int ret = C(r - l + 1, i);
			int x = a[l] - i % 2; x ^= sum;
			if ( (r - l + 1 - i) & 1 ) x ^= a[l];
			ans = (ans + ret * Query(x)) % Mod;

			x = a[l] - i % 2; 
			if ( x == (S ^ (i & 1 ? a[l] : 0)) ) ans = (ans - ret) % Mod;
			x = a[l] - (i + 1) % 2;
			if ( x == (S ^ (i & 1 ? a[l] : 0)) ) ans = (ans + ret) % Mod;
		}
		REP(i, l, r) Insert(a[i]);
	}
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
