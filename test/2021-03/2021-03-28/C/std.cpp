/***************************************************************
	File name: std.cpp
	Author: ljfcnyali
	Create time: 2021年03月28日 星期日 14时32分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define x first
#define y second
typedef long long LL;

const int maxn = 4e4 + 10;
const int INF = 9e18;

int n, m = 47;
pii a[maxn];

pii operator + (pii a, pii b) { return pii(a.x + b.x, a.y + b.y); } 

inline pii Solve(vector<pii> f, int m, vector<int> a, vector<int> b)
{
	if ( !f.size() ) 
	{
		int ret = 0, num = 1;
		REP(i, 0, m) 
		{
			if ( a[i] == b[i] ) num *= 2;
			ret += min(a[i], b[i]) * (1ll << i);
		}
		return pii(ret, num);
	}
	if ( m == -1 ) return pii(0, 1);	
	pii ans = pii(INF, 0), ret = pii(0, 0);
	vector<pii> g; vector<int> c = a, d = b;
	for ( auto it : f ) 
	{
		int x = (it.x >> m) & 1;
		if ( x == ((it.y >> m) & 1) ) { g.push_back(it); continue ; }
		REP(j, 0, m) ret.x += (it.x & (1ll << j)) * (x == 1 ? 1 : -1);
		REP(j, 0, m) if ( (it.y >> j) & 1 ) c[j] += x == 1 ? -1 : 1; else d[j] += x == 1 ? -1 : 1; 
	}
	ret.x += c[m] * (1ll << m); ret = ret + Solve(g, m - 1, c, d);
	if ( ret.x < ans.x ) ans = ret;
	else if ( ret.x == ans.x ) ans.y += ret.y; 

	g.clear(); c = a; d = b; ret = pii(0, 0);
	for ( auto it : f ) 
	{
		int x = (it.x >> m) & 1;
		if ( x != ((it.y >> m) & 1) ) { g.push_back(it); continue ; }
		REP(j, 0, m) ret.x += (it.x & (1ll << j)) * (x == 1 ? 1 : -1);
		REP(j, 0, m) if ( (it.y >> j) & 1 ) c[j] += x == 1 ? -1 : 1; else d[j] += x == 1 ? -1 : 1; 
	}
	ret.x += d[m] * (1ll << m); ret = ret + Solve(g, m - 1, c, d);
	if ( ret.x < ans.x ) ans = ret;
	else if ( ret.x == ans.x ) ans.y += ret.y; 

	return ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) scanf("%lld", &a[i].x);
	REP(i, 1, n) scanf("%lld", &a[i].y);
	vector<pii> t; vector<int> p(m + 1), q(m + 1); 
	REP(i, 1, n) t.push_back(a[i]);
	pii ans = Solve(t, m, p, q);
	printf("%lld %lld\n", ans.x, ans.y);
    return 0;
}
