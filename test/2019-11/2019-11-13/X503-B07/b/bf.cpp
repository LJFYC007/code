/***************************************************************
	File name: b.cpp
	Author: ljfcnyali
	Create time: 2019年11月13日 星期三 10时05分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 5010;

int f[maxn][maxn], X, Y, Z, n;
struct node
{
    int a, b, c;
    bool operator < (const node &x) const { return a - b > x.a - x.b; }
} a[maxn];

signed main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%lld%lld%lld", &X, &Y, &Z);
    n = X + Y + Z;
    REP(i, 1, n) scanf("%lld%lld%lld", &a[i].a, &a[i].b, &a[i].c);
    sort(a + 1, a + n + 1);
    REP(i, 1, n) REP(z, 0, min(i, Z))
    {
        f[i][z] = f[i - 1][z - 1] + a[i].c;
        int x = i - z;
        if ( x <= X ) f[i][z] = max(f[i][z], f[i - 1][z] + a[i].a);
        else f[i][z] = max(f[i][z], f[i - 1][z] + a[i].b);
    }
    // REP(i, 1, n) { REP(z, 0, min(i, Z)) printf("%d ", f[i][z]); puts(""); }
    // REP(i, 1, n) { REP(z, 0, min(i, Z) - 1) if ( f[i][z] < f[i][z + 1] ) printf("<"); else printf(">"); puts(""); }
    printf("%lld\n", f[n][Z]);
    return 0;
}
