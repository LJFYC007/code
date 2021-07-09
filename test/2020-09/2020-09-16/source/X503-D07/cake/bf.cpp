/***************************************************************
	File name: cake.cpp
	Author: ljfcnyali
	Create time: 2020年09月16日 星期三 19时12分33秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, f[maxn], m;
struct node { int x, y, id; } a[maxn];

int main()
{
    freopen("cake.in", "r", stdin);
    freopen("cake1.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d%d", &a[i].x, &a[i].y); a[i].id = i; }
    sort(a + 1, a + n + 1, [](node &a, node &b) { return a.y < b.y; });
    f[0] = 0; a[0].x = maxn;
    REP(i, 1, n) REP(j, 0, i - 1) if ( a[i].x < a[j].x ) f[i] = max(f[i], f[j] + 1);
    int ans = 0;
    REP(i, 1, n) ans = max(ans, f[i]);
    printf("%d\n", ans);
    return 0;
}
