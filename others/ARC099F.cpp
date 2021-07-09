/***************************************************************
	File name: ARC099F.cpp
	Author: ljfcnyali
	Create time: 2021年06月17日 星期四 15时32分30秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5e5 + 10;
const int seed1 = 233;
const int seed2 = 107;
const int Mod1 = 998244353;
const int Mod2 = 1e9 + 7;

int n, p1[maxn], p2[maxn], Hash1[maxn], Hash2[maxn], a[maxn], ans;
char s[maxn]; map<int, int> Map1, Map2;

inline int power(int a, int b, int Mod) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }
inline int calc1(int x) { return x < 0 ? power(p1[-x], Mod1 - 2, Mod1) : p1[x]; }
inline int calc2(int x) { return x < 0 ? power(p2[-x], Mod2 - 2, Mod2) : p2[x]; }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	p1[0] = p2[0] = 1; REP(i, 1, maxn - 10) p1[i] = p1[i - 1] * seed1 % Mod1, p2[i] = p2[i - 1] * seed2 % Mod2;
	scanf("%lld", &n); scanf("%s", s + 1);
	int pos = 250000; a[0] = pos;
	REP(i, 1, n)
	{
		Hash1[i] = Hash1[i - 1]; Hash2[i] = Hash2[i - 1];
		if ( s[i] == '<' ) -- pos;
		if ( s[i] == '>' ) ++ pos;
		if ( s[i] == '+' ) 
		{
			Hash1[i] = (Hash1[i] + p1[pos]) % Mod1;
			Hash2[i] = (Hash2[i] + p2[pos]) % Mod2;
		}
		if ( s[i] == '-' ) 
		{
			Hash1[i] = (Hash1[i] + Mod1 - p1[pos]) % Mod1;
			Hash2[i] = (Hash2[i] + Mod2 - p2[pos]) % Mod2;
		}
		a[i] = pos; ++ Map1[Hash1[i]]; ++ Map2[Hash2[i]];
	}
	REP(i, 1, n)
	{
		int val1 = (Hash1[n] * calc1(a[i - 1] - 250000) + Hash1[i - 1]) % Mod1;
		int val2 = (Hash2[n] * calc2(a[i - 1] - 250000) + Hash2[i - 1]) % Mod2;
		ans += min(Map1[val1], Map2[val2]); -- Map1[Hash1[i]]; -- Map2[Hash2[i]];
	}
	printf("%lld\n", ans);
    return 0;
}
