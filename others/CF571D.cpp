/***************************************************************
	File name: CF571D.cpp
	Author: ljfcnyali
	Create time: 2021年04月28日 星期三 19时45分05秒
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

int n, m, a[maxn], tag[maxn], belong[maxn], ans[maxn], f[maxn], size[maxn];
vector<int> p[maxn];
struct node { int op, x, y; } q[maxn];
vector<pii> Q[maxn];

inline int find(int x) { return x == f[x] ? x : find(f[x]); } 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld%lld", &n, &m); REP(i, 1, n) { size[i] = 1; f[i] = i; } 
	REP(i, 1, m) 
	{
		char c[1]; scanf("%s", c);
		if ( c[0] == 'U' ) { q[i].op = 1; scanf("%lld%lld", &q[i].x, &q[i].y); } 
		if ( c[0] == 'M' ) 
		{ 
			q[i].op = 2; scanf("%lld%lld", &q[i].x, &q[i].y); 
			int x = find(q[i].x), y = find(q[i].y);
			if ( size[x] > size[y] ) swap(x, y);
			f[x] = y; a[x] = i; size[y] += size[x];
		} 
		if ( c[0] == 'A' ) { q[i].op = 3; scanf("%lld", &q[i].x); } 
		if ( c[0] == 'Z' ) { q[i].op = 4; scanf("%lld", &q[i].x); tag[find(q[i].x)] = i; }
		if ( c[0] == 'Q' ) 
		{ 
			q[i].op = 5; scanf("%lld", &q[i].x); 
			Q[i].push_back(pii(q[i].x, i)); 
			int x = q[i].x, val = tag[x];
			while ( f[x] != x ) 
			{
				if ( a[x] <= tag[f[x]] ) val = tag[f[x]];
				x = f[x];
			}
			Q[val].push_back(pii(q[i].x, -i));
		} 
	}
	REP(i, 1, n) { p[i].push_back(i); belong[i] = i; a[i] = tag[i] = 0; } 
	REP(i, 1, m)
	{
		if ( q[i].op == 1 ) 
		{
			int x = belong[q[i].x], y = belong[q[i].y];
			if ( p[x].size() > p[y].size() ) for ( auto it : p[y] ) { p[x].push_back(it); belong[it] = x; a[it] += tag[y] - tag[x]; } 
			else for ( auto it : p[x] ) { p[y].push_back(it); belong[it] = y; a[it] += tag[x] - tag[y]; }
		}
		if ( q[i].op == 3 ) 
		{
			int x = belong[q[i].x];
			tag[x] += p[x].size();
		}
		for ( auto it : Q[i] ) 
		{
			int x = it.second, val = a[it.first] + tag[belong[it.first]];
			if ( x > 0 ) ans[x] += val; else ans[-x] -= val;
		}
	}
	REP(i, 1, m) if ( q[i].op == 5 ) printf("%lld\n", ans[i]);
    return 0;
}
