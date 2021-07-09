/***************************************************************
	File name: AGC020E.cpp
	Author: ljfcnyali
	Create time: 2021年06月26日 星期六 16时26分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 110;
const int Mod = 998244353;

int n, f[maxn]; char s[maxn];
map<vector<int>, int> Map1, Map2;

inline int Get(vector<int> a);

inline int Solve(vector<int> a)
{
	int ret = 0, n = a.size(); 
	if ( n == 1 ) return a[0] + 1;
	if ( Map1.count(a) ) return Map1[a];
	REP(k, 1, n - 1) if ( n % k == 0 ) 
	{
		vector<int> b(k); REP(i, 0, k - 1) b[i] = 1;
		for ( int i = 0, j = k - 1; i <= n - 1; i += k, j += k )
			REP(o, i, j) if ( a[o] == 0 ) b[o % k] = 0;
		ret = (ret + Get(b)) % Mod;
	}
	Map1[a] = ret; return ret;
}

inline int Get(vector<int> a)
{
	if ( Map2.count(a) ) return Map2[a];
	int n = a.size(); vector<int> f(n + 1); f[0] = 1; 
	REP(i, 1, n) REP(j, 0, i - 1) 
	{
		vector<int> b; REP(o, j + 1, i) b.push_back(a[o - 1]);
		f[i] = (f[i] + f[j] * Solve(b)) % Mod;
	}
	Map2[a] = f[n]; return f[n];
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%s", s + 1); n = str(s + 1);
	vector<int> a; REP(i, 1, n) a.push_back(s[i] == '1');
	printf("%lld\n", (Get(a) + Mod) % Mod);
    return 0;
}
