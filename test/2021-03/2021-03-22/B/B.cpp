/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年03月22日 星期一 22时04分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, a[2][maxn], ans, b[2][maxn], Stack[maxn], tot;
vector<pii> p;
bool ok[maxn], use[maxn];

inline void Solve(int op)
{ 
	tot = 0;
	REP(i, 1, n)
	{
		while ( tot && a[op][Stack[tot]] > a[op][i] ) -- tot;
		if ( tot && a[op][Stack[tot]] == a[op][i] ) 
		{ 
			if ( Stack[tot] != i - 1 ) { p.push_back(pii(Stack[tot], i - 1)); -- ans; } 
			-- tot; 
		} 
		Stack[++ tot] = i; 
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) REP(o, 0, 1) scanf("%d", &a[o][i]);
	REP(o, 0, 1) REP(i, 1, n - 1) if ( a[o][i] != a[o][i + 1] ) { b[o][i] = min(a[o][i], a[o][i + 1]); ++ ans; } else b[o][i] = -1;		
	REP(i, 1, n - 1) if ( b[0][i] != -1 && b[1][i] != -1 ) { ok[i] = true; -- ans; } 
	Solve(0); Solve(1);
	sort(p.begin(), p.end(), [](pii a, pii b) { return a.first < b.first; });
	multiset<pii> Set; int now = 0;
	REP(i, 1, n - 1) if ( ok[i] ) 
	{
		while ( now < p.size() && p[now].first <= i ) 
		{
			Set.insert(pii(p[now].second, now));
			++ now;
		}
		auto it = Set.begin(); 
		while ( it != Set.end() && it -> first < i ) it = Set.erase(it);
		if ( it != Set.end() ) { Set.erase(it); ++ ans; }
	}
	printf("%d\n", ans);
    return 0;
}
