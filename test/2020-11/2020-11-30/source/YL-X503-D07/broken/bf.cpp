/***************************************************************
	File name: broken.cpp
	Author: ljfcnyali
	Create time: 2020年11月30日 星期一 10时52分43秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 998244353;

int n, m, k, f[1010][510];
struct node { int x, y, z; } a[maxn];

signed main()
{
    freopen("broken.in", "r", stdin);
    freopen("broken.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &k);
    REP(i, 1, k) scanf("%lld%lld%lld", &a[i].x, &a[i].y, &a[i].z);
    f[0][0] = 1; 
    int now = 1;
    if ( now <= k && a[now].x == 0 && a[now].y == 0 ) { f[0][0] = a[now].z; ++ now; }
    REP(i, 1, n) REP(j, 0, min(i, m)) 
    {
        if ( j >= 1 ) f[i][j] = f[i - 1][j - 1];
        f[i][j] = (f[i][j] + j * f[i - 1][j]) % Mod;
        if ( now <= k && i == a[now].x && j == a[now].y ) { f[i][j] = a[now].z; ++ now; } 
    }
    printf("%lld\n", (f[n][m] + Mod) % Mod);
    return 0;
}
