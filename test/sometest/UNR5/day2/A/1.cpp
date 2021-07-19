/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年07月19日 星期一 08时53分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e5 + 10;

int n, m; vector<pii> ans1, ans2, ans3, ans4, A[2]; pii ans[maxn];
struct node { int l, a[3]; } a[maxn];
multiset<int> l1[maxn], l2[maxn];
map<int, int> Map[maxn]; bool vis[maxn];

inline void Maintain(int x, int y, int op)
{
	vis[x] = true; A[op].push_back(pii(x, y));
	if ( a[x].l == 1 ) l1[a[x].a[1]].erase(l1[a[x].a[1]].find(x));
	else { l2[a[x].a[1]].erase(l2[a[x].a[1]].find(x)); l2[a[x].a[2]].erase(l2[a[x].a[2]].find(x)); }
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	REP(i, 1, n) 
	{ 
		scanf("%d", &a[i].l); REP(j, 1, a[i].l) scanf("%d", &a[i].a[j]); 
		if ( a[i].l == 2 ) 
		{
			int x = a[i].a[1], y = a[i].a[2];
			if ( Map[x].count(y) ) 
			{ 
				vis[i] = vis[Map[x][y]] = true;
				ans1.push_back(pii(i, 0)); ans2.push_back(pii(Map[x][y], 0)); 
				Map[x].erase(y); continue ; 
			}
			if ( Map[y].count(x) ) 
			{ 
				vis[i] = vis[Map[y][x]] = true;
				ans1.push_back(pii(i, 0)); ans2.push_back(pii(Map[y][x], 1)); 
				Map[y].erase(x); continue ; 
			}
			Map[x][y] = i;
		}
	}
	REP(i, 1, n) if ( !vis[i] ) 
	{
		if ( a[i].l == 1 ) l1[a[i].a[1]].insert(i);
		else 
		{
			l2[a[i].a[1]].insert(i);
			l2[a[i].a[2]].insert(i);
		}
	}

	REP(i, 1, n) if ( !vis[i] ) 
	{
		if ( a[i].l == 2 ) continue ; 
		// if ( a[i].l == 1 ) continue ; 
		int now, op = 1; A[0].clear(); A[1].clear(); bool flag = false;
		/*
		if ( !l1[a[i].a[1]].empty() ) 
		{
			now = a[i].a[2];
			Maintain(i, 0, 0); Maintain(*l1[a[i].a[1]].begin(), 0, 1);
		}
		else if ( !l1[a[i].a[2]].empty() ) 
		{
			now = a[i].a[1];
			Maintain(i, 0, 0); Maintain(*l1[a[i].a[2]].begin(), 1, 1);
		}
		else continue ;
		*/
		now = a[i].a[1]; Maintain(i, 0, 0);

		while ( !l2[now].empty() ) 
		{
			int x = *l2[now].begin();
			cerr << now << " ";
			Maintain(x, a[x].a[2] == now, op);
			now = a[x].a[1] + a[x].a[2] - now;
			op ^= 1;
		}
		if ( l1[now].empty() ) { flag = true; break ; } 
			
		if ( flag ) 
		{
			assert(ans3.empty());
			ans3 = A[0]; ans4 = A[1];
		}
		else
		{
			Maintain(*l1[now].begin(), 0, op);
			for ( auto it : A[0] ) ans1.push_back(it);
			for ( auto it : A[1] ) ans2.push_back(it);
		}
	}

	REP(i, 1, m) 
	{
		assert(l1[i].size() % 2 == 0);
		// for ( auto it : l2[i] ) cerr << it << endl;
		// assert(l2[i].size() == 0);
		while ( !l1[i].empty() ) 
		{
			int x = *l1[i].begin(); l1[i].erase(x);
			int y = *l1[i].begin(); l1[i].erase(y);
			ans1.push_back(pii(x, 0)); ans2.push_back(pii(y, 0));
		}
	}
	
	for ( auto it : ans3 ) ans1.push_back(it);
	for ( auto it : ans4 ) ans2.push_back(it);
	
	for ( int i = 0; i < ans1.size(); ++ i ) ans[ans1[i].first] = pii(i + 1, ans1[i].second);
	for ( int i = 0; i < ans2.size(); ++ i ) ans[ans2[i].first] = pii(n - i, ans2[i].second ^ 1);
	REP(i, 1, n) printf("%d ", ans[i].first); puts("");
	REP(i, 1, n) printf("%d ", ans[i].second); puts("");
    return 0;
}
