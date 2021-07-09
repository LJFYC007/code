/***************************************************************
	File name: stacktwo.cpp
	Author: ljfcnyali
	Create time: 2021年06月23日 星期三 10时50分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e6 + 10;
const int Mod = 998244353;

int n, a[maxn], f[maxn], ans, sum, fac[maxn], inv[maxn];
deque<pii> Q; 

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; } 
inline int C(int n, int m) { return n < m ? 0 : fac[n] * inv[m] % Mod * inv[n - m] % Mod; } 

inline void Insert(int l, int r)
{
	Q.push_front(pii(l, r));
	sum = sum * f[r - l + 1] % Mod;
}

signed main()
{
    freopen("stacktwo.in", "r", stdin);
    freopen("stacktwo.out", "w", stdout);
	n = maxn - 10; fac[0] = inv[0] = 1; REP(i, 1, n) fac[i] = fac[i - 1] * i % Mod;
	inv[n] = power(fac[n], Mod - 2); for ( int i = n - 1; i >= 1; -- i ) inv[i] = inv[i + 1] * (i + 1) % Mod;
	scanf("%lld", &n); 
	REP(i, 1, n) scanf("%lld", &a[i]);
	f[0] = 1; REP(i, 1, n) f[i] = (C(i + i, i) - C(i + i, i - 1)) % Mod;
	Q.push_front(pii(1, n)); sum = f[n];
	REP(i, 1, n)
	{
		pii now = Q.front(); Q.pop_front(); sum = sum * power(f[now.second - now.first + 1], Mod - 2) % Mod;
		while ( now.first > now.second ) 
		{
			now = Q.front(); Q.pop_front(); 
			sum = sum * power(f[now.second - now.first + 1], Mod - 2) % Mod;
		}

		int ret = 0, len = now.second - now.first + 1;
		int x = max(now.first, a[i] + 1) - now.first + 1;
		if ( x <= len / 2 ) 
		{
			ret = f[len];
			REP(i, 1, x - 1) ret = (ret - f[i - 1] * f[len - i]) % Mod;
		}
		else REP(i, x, len) ret = (ret + f[i - 1] * f[len - i]) % Mod;

		ans = (ans + ret * sum) % Mod;

		if ( a[i] < now.first || a[i] > now.second ) break ; 
		if ( a[i] == now.first ) Insert(a[i] + 1, now.second);
		else if ( a[i] == now.second ) Insert(now.first, a[i] - 1);
		else
		{
			Insert(a[i] + 1, now.second);
			Insert(now.first, a[i] - 1);
		}
		if ( i == n ) ++ ans;
	}
	printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
