/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年02月15日 星期一 09时29分42秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, f[maxn], k;
struct node { set<int> r, c; } ;
vector<node> ans;
set<int> ccc;

inline void Insert(node &t, int x, int op)
{
	if ( x < 1 || x > m ) return ;
	if ( op == 0 ) t.r.insert(x);
	else t.c.insert(x);
}

inline void Solve(vector<pii> a, vector<pii> b, int n)
{
	REP(i, 0, 12) 
	{
		node t = {ccc, ccc};
		REP(j, 1, n) 
			if ( (f[j] >> i) & 1 ) Insert(t, a.front().first + j + j - 2, 0);
			else Insert(t, a.front().second + j + j - 2, 1);
		REP(j, 1, n) 
			if ( (f[j] >> i) & 1 ) Insert(t, b.front().first + j + j - 2, 0);
			else Insert(t, b.front().second + j + j - 2, 1);
		ans.push_back(t);
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	REP(i, 0, (1 << 13))
	{
		int num = 0; REP(j, 1, 13) if ( (i >> j - 1) & 1 ) ++ num;	
		if ( num == 6 ) f[++ k] = i;
	}

	scanf("%d", &m); n = m;
	if ( m % 2 == 0 ) ++ n;
	vector<pii> a, b; a.push_back(pii(1, 0)); b.push_back(pii(1, 1)); Solve(a, b, (n + 1) / 2);
	a.clear(); b.clear(); a.push_back(pii(2, 1)); b.push_back(pii(2, 2)); Solve(a, b, (n + 1) / 2);
	int num = 0;
	for ( auto it : ans ) 
	{
		if ( !it.r.size() || !it.c.size() ) continue ;
		++ num;
	}
	printf("%d\n", num);
	for ( auto it : ans ) 
	{
		if ( !it.r.size() || !it.c.size() ) continue ;
		printf("%d %d ", it.r.size(), it.c.size());
		for ( auto i : it.r ) printf("%d ", i);
		for ( auto i : it.c ) printf("%d ", i);
		puts("");
	}
    return 0;
}
