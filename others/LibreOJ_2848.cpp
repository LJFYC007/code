/***************************************************************
	File name: LibreOJ_2848.cpp
	Author: ljfcnyali
	Create time: 2021年06月29日 星期二 09时11分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, a[maxn], b[maxn], p[maxn];
vector<pii> ans;

inline void Solve(int l, int r)
{
	if ( l == r ) return ;
	int m = l; REP(i, l, r) b[i] = a[i];
	for ( int i = l + 1; i <= r; i += 2 ) a[m ++] = b[i];
	for ( int i = l; i <= r; i += 2 ) a[m ++] = b[i];
	REP(i, l, r) p[a[i]] = i;
	ans.push_back(pii(l, r));
}

inline void Move(int x, int y)
{
	if ( x == y ) return ;
	int t = p[x];
	REP(i, 1, n) cerr << a[i] << " "; cerr << endl;
	REP(i, 1, n) cerr << p[i] << " "; cerr << endl;
	Solve(max(1, x + x - y + 1), y);
	cerr << x << " " << y << endl; 
	REP(i, 1, n) cerr << p[i] << " "; cerr << endl;
	return ;
	Move(a[t], y);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) { scanf("%d", &a[i]); p[a[i]] = i; }
	/*
	REP(i, 1, 100)
	{
		int l = rand() % n + 1, r = rand() % n + 1;
		if ( l > r ) swap(l, r);
		Solve(l, r);
	}
	*/

	for ( int o = n; o >= 1; -- o ) Move(a[o], o);
	printf("%zu\n", ans.size());
	reverse(ans.begin(), ans.end());
	for ( auto it : ans ) printf("%d %d\n", it.first, it.second);
    return 0;
}
