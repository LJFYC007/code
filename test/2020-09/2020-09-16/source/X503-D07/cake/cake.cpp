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

int n, f[maxn], m, ans[maxn];
struct node { int x, y, id; } a[maxn];

int main()
{
    freopen("cake.in", "r", stdin);
    freopen("cake.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d%d", &a[i].x, &a[i].y); a[i].id = i; }
    sort(a + 1, a + n + 1, [](node &a, node &b) { return a.y < b.y; });
    f[0] = maxn;
    REP(i, 1, n) if ( a[i].x < f[m] ) { f[++ m] = a[i].x; ans[a[i].id] = m; }
    else 
    {
        int l = 1, r = m, pos = 0;
        while ( l <= r ) 
        {
            int Mid = l + r >> 1;
            if ( f[Mid] < a[i].x ) { pos = Mid; r = Mid - 1; }
            else l = Mid + 1;
        }
        f[pos] = a[i].x; ans[a[i].id] = pos;
    }
    printf("%d\n", m);
    REP(i, 1, n) printf("%d ", ans[i]); puts("");
    return 0;
}
