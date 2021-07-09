/***************************************************************
	File name: G.cpp
	Author: ljfcnyali
	Create time: 2021年03月04日 星期四 20时53分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, a[maxn], p[maxn];
bool vis[maxn];
vector<int> circle[maxn];
vector<pii> ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) { scanf("%d", &a[i]); p[a[i]] = i; } 
	REP(i, 1, n) if ( !vis[i] ) 
	{
		++ m; int x = a[i]; circle[m].push_back(i); vis[i] = true;
		while ( x != i ) { circle[m].push_back(x); vis[x] = true; x = a[x]; } 
	}
	for ( int i = 1; i < m; i += 2 ) 
	{
		int x = i, y = i + 1;
		auto a = circle[x], b = circle[y];
		ans.push_back(pii(a.back(), b.back()));
		for ( int j = 0; j + 1 < a.size(); ++ j ) ans.push_back(pii(a[j], b.back()));
		for ( int j = 0; j + 1 < b.size(); ++ j ) ans.push_back(pii(a.back(), b[j])); 
		ans.push_back(pii(a.back(), b.back()));
	}
	if ( m & 1 ) 
	{
		auto a = circle[m];
		if ( a.size() == 1 )
		{
		}
		else if ( a.size() == 2 ) 
		{
			int x = a[0], y = circle[1].back(), z = a[1];
			ans.push_back(pii(x, y));
			ans.push_back(pii(y, z));
			ans.push_back(pii(x, y));
		}
		else
		{
			int x = a[0], y = a[a.size() - 2], z = a.back();
			ans.push_back(pii(x, z));			
			for ( int i = 1; i + 2 < a.size(); ++ i ) ans.push_back(pii(a[i], a.back()));
			ans.push_back(pii(x, y));
			ans.push_back(pii(y, z));
			ans.push_back(pii(x, z));
		}
	}

	printf("%d\n", (int)ans.size()); for ( auto it : ans ) printf("%d %d\n", it.first, it.second);
    return 0;
}
