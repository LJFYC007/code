/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年07月15日 星期四 09时01分44秒
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

const int maxn = 10010;

int T, n, m, q, ans[maxn], preMin[maxn], preMax[maxn], sufMin[maxn], sufMax[maxn];
int t[maxn], p[maxn];
pii QQ[maxn], a[maxn]; 

inline int Query(int l, int r)
{
	int Max = max(preMax[p[l]], sufMax[t[r]]);
	int Min = min(preMin[p[l]], sufMin[t[r]]);
	return Min - Max;
}

inline int Solve(int x, int y)
{
	int pos = 0; REP(i, 1, n) if ( a[i].x <= x ) pos = i;
	preMax[pos + 1] = sufMax[pos] = 0;
	preMin[pos + 1] = sufMin[pos] = m;
	for ( int i = pos; i >= 1; -- i ) 
	{
		preMin[i] = min(preMin[i + 1], a[i].y >= y ? a[i].y : m);
		preMax[i] = max(preMax[i + 1], a[i].y <= y ? a[i].y : 0);
	}
	REP(i, pos + 1, n)
	{
		sufMin[i] = min(sufMin[i - 1], a[i].y >= y ? a[i].y : m);
		sufMax[i] = max(sufMax[i - 1], a[i].y <= y ? a[i].y : 0);
	}
	for ( int i = n; i >= 1; -- i ) 
		if ( a[i].x != a[i + 1].x ) p[i] = i + 1;
		else p[i] = p[i + 1];
	REP(i, 1, n) 
		if ( a[i].x != a[i - 1].x ) t[i] = i - 1;
		else t[i] = t[i - 1];

	++ pos; int ans = 0;
	for ( int i = 1; i <= n; i = p[i] )
	{
		if ( a[i].x >= x ) break ;
		while ( pos <= n && p[pos] <= n && Query(i, p[pos]) >= a[p[pos]].x - a[i].x ) pos = p[pos];
		ans = max(ans, min(Query(i, pos), a[pos].x - a[i].x));
	}
	return ans;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d%d", &m, &n); mem(ans); 
		REP(i, 1, n) scanf("%d%d", &a[i].x, &a[i].y);
		a[++ n] = pii(0, 0); a[++ n] = pii(m, m);
		scanf("%d", &q);
		REP(i, 1, q) scanf("%d%d", &QQ[i].x, &QQ[i].y);
		sort(a + 1, a + n + 1);
		REP(i, 1, q) ans[i] = max(ans[i], Solve(QQ[i].x, QQ[i].y));
		REP(i, 1, n) swap(a[i].x, a[i].y);
		sort(a + 1, a + n + 1);
		REP(i, 1, q) ans[i] = max(ans[i], Solve(QQ[i].y, QQ[i].x));
		REP(i, 1, q) if ( QQ[i].x == 0 || QQ[i].y == 0 || QQ[i].x == m || QQ[i].y == m ) ans[i] = 0;
		REP(i, 1, q) printf("%lld\n", 1ll * ans[i] * ans[i]);
	}
    return 0;
}
