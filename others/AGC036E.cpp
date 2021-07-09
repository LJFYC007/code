/***************************************************************
	File name: AGC036E.cpp
	Author: ljfcnyali
	Create time: 2021年02月04日 星期四 15时11分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m, a[maxn], f[maxn];
char s[maxn];
pii b[4];
set<pii> Set[4], p[4];

inline int find(int x) { return x == f[x] ? x : f[x] = find(f[x]); }

inline void Erase(int x)
{
	a[x] = -1;
	f[x] = find(f[x + 1]);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%s", s + 1); m = str(s + 1);
	a[0] = -1; REP(i, 1, m) if ( s[i] - 'A' != a[n] ) a[++ n] = s[i] - 'A';
	REP(i, 0, 2) b[i].second = i; REP(i, 1, n) ++ b[a[i]].first; sort(b, b + 3);	
	int x = b[0].second, y = b[1].second, z = b[2].second;
	REP(i, 1, n + 1) f[i] = i;

	for ( int l = 1, r; l <= n; l = r + 1 ) 
	{
		r = l;
		if ( a[l] == x ) { Set[0].insert(pii(l, l)); continue ; } 
		while ( a[r + 1] != x && r + 1 <= n ) ++ r;	
		if ( l == r && l != 1 && r != n ) 
		{
			if ( a[l] == y ) Set[1].insert(pii(l, l));
			else Set[2].insert(pii(l, l));
			continue ;
		}
		Set[3].insert(pii(l, r));
	}
	while ( b[1].x != b[2].x && !Set[3].empty() ) 
	{
		pii it = *Set[3].begin(); Set[3].erase(it);
		if ( a[it.x] == z ) { -- b[2].x; Erase(it.x); ++ it.x; }
		if ( b[1].x != b[2].x && a[it.y] == z && it.x <= it.y ) { -- b[2].x; Erase(it.y); -- it.y; }
		p[3].insert(it);
	}
	while ( b[1].x != b[2].x ) 
	{
		pii itl = *Set[0].begin(), itr = *Set[2].begin();
		if ( find(f[itl.x + 1]) == itr.x ) 
		{ 
			Erase(itl.x); Erase(itr.x);
			Set[0].erase(itl); Set[2].erase(itr); -- b[0].x; -- b[2].x; 
			continue ; 
		} 
		if ( itl.x < itr.x ) Set[0].erase(itl);
		else Set[2].erase(itr);
	}
	REP(o, 0, 3) for ( auto it : Set[o] ) p[o].insert(it);
	while ( b[1].x != b[0].x ) 
	{
		pii it = *p[3].begin(); p[3].erase(it);
		bool flag = find(f[it.y + 1]) == n + 1;
		if ( find(f[1]) == it.x ) flag = true;
		while ( b[1].x != b[0].x && (it.x + 1 < it.y || (flag && it.x < it.y)) ) 
		{
			Erase(it.x); Erase(it.x + 1);
			it.x += 2; -- b[1].x;
		}
	}

	REP(i, 1, n) if ( a[i] != -1 ) printf("%c", a[i] + 'A'); puts("");
    return 0;
}
