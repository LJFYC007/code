/***************************************************************
	File name: D.cpp
	Author: ljfcnyali
	Create time: 2021年04月05日 星期一 19时27分49秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 4e5 + 10;

int n, p[maxn], a[maxn];
bool vis[maxn];

inline void out() { puts("-1"); exit(0); } 

inline int Solve(int l, int r)
{
	if ( l > r + 1 ) out();
	if ( l > r ) return 0; 
	int ret = 0, m = r - l + 1, lst = r, Max = l;
	REP(i, l, r) if ( !vis[i] ) 
	{
		ret += a[i];
		for ( int j = lst; j >= p[i] + 1; -- j ) 
		{ 
			ret += a[j]; vis[p[j]] = true; 
			if ( p[j] < Max ) out(); Max = p[j];
		} 
		lst = p[i] - 1; Max = max(Max, i);
		if ( Max - l + 1 == r - lst ) break ; 
	}
	int x = Solve(Max + 1, lst), len = lst - Max;
	return min(ret, (m - len) / 2 - ret) + x;
	// ret = min(ret + x, ret + len / 2 - x);
	// return min(ret, m / 2 - ret);
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) { int x, y; scanf("%d%d", &x, &y); p[x] = y; p[y] = x; a[y] = 1; } 
	printf("%d\n", Solve(1, n + n));
    return 0;
}
