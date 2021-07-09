/***************************************************************
	File name: AGC040E.cpp
	Author: ljfcnyali
	Create time: 2021年07月02日 星期五 16时01分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;
const int INF = 0x3f3f3f3f;

int n, a[maxn];
vector<pii> f[maxn];

inline vector<pii> Merge(vector<pii> a, vector<pii> b)
{
	vector<pii> c; 
	a.push_back(pii(INF, INF)); b.push_back(pii(INF, INF));
	a.push_back(pii(INF, INF)); b.push_back(pii(INF, INF));
	a.push_back(pii(INF, INF)); b.push_back(pii(INF, INF));
	a.push_back(pii(INF, INF)); b.push_back(pii(INF, INF));
	while ( 1 ) 
	{
		if ( a[0].first == INF && b[0].first == INF ) break ; 
		if ( a[1].first < b[0].first ) { a.erase(a.begin()); continue ; } 
		if ( b[1].first < a[0].first ) { b.erase(b.begin()); continue ; } 
		if ( a[0].second > b[0].second || (a[0].second == b[0].second && a[0].first > b[0].first) ) swap(a, b);
		c.push_back(pii(a[0].first, a[0].second));
		a.erase(a.begin()); b.erase(b.begin());	
	}
	return c;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
	f[0].push_back(pii(0, 0)); 
	REP(i, 1, n + 1)
	{
		f[i].push_back(pii(0, INF));
		for ( auto it : f[i - 1] )
		{
			int x = it.first, val = it.second; vector<pii> p;
			if ( x > a[i - 1] ) break ;
			if ( min(x, x + a[i] - a[i - 1]) - 1 >= 0 ) 
				p.push_back(pii(0, val + 2));
			if ( max(x, x + a[i] - a[i - 1]) - 1 >= 0 ) 
				p.push_back(pii(max(0, min(x, x + a[i] - a[i - 1])), val + 1));
			p.push_back(pii(max(0, max(x, x + a[i] - a[i - 1])), val));
			f[i] = Merge(f[i], p);
		}
	}
	printf("%d\n", f[n + 1][0].second);
    return 0;
}
