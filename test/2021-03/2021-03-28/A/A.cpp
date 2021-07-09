/***************************************************************
    File name: A.cpp
    Author: ljfcnyali
    Create time: 2021年03月28日 星期日 08时54分29秒
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
 
const int maxn = 1e5 + 10;
 
int n, m, match[maxn], ans;
pii a[maxn];
struct node { int x, y, id; } b[maxn];
bool vis[maxn];
 
int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d%d", &a[i].x, &a[i].y); sort(a + 1, a + n + 1);
    REP(i, 1, m) { scanf("%d%d", &b[i].x, &b[i].y); b[i].id = i; }
	sort(b + 1, b + m + 1, [](const node &a, const node &b) { return a.x < b.x; });
	REP(i, 1, m)
	{
		int pos = 0, Max = -1;
		REP(j, 1, n) if ( !vis[j] && a[j].x <= b[i].x && a[j].y <= b[i].y && a[j].y > Max ) { Max = a[j].y; pos = j; } 
		if ( !pos ) continue ; 
		match[b[i].id] = pos; vis[pos] = true;
	}
	mem(vis); vis[0] = true;
	sort(b + 1, b + m + 1, [](const node &a, const node &b) { return a.id < b.id; });
	REP(i, 1, m)
	{
		if ( !vis[match[i]] ) { vis[match[i]] = true; ++ ans; }
		else
		{
			REP(j, 1, n) if ( !vis[j] && a[j].x <= b[i].x && a[j].y <= b[i].y ) { vis[j] = true; ++ ans; break ; } 
		}
		printf("%d ", ans);
	}
	puts("");
    return 0;
}
