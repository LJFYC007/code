/***************************************************************
	File name: medium.cpp
	Author: ljfcnyali
	Create time: 2020年05月27日 星期三 09时56分52秒
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

int n, m, q, a[20][20], b[20][20], c[20][20];
int p[maxn], ans;
pii f[maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r = r * a % Mod; a = a * a % Mod; b >>= 1; } return r; }

inline void DFS(int x, int y)
{
    if ( y > 0 && c[x][y - 1] && a[x][y - 1] != 2 ) return ;
    if ( x == 2 * n + 2 ) 
    {
        ++ ans;
        REP(i, 0, 2 * n + 1) REP(j, 0, p[i] - 1)
            if ( a[i][j] == 2 ) ++ b[i][j];
        return ;
    }
    if ( y >= p[x] ) { DFS(x + 1, 0); return ; }
    int fax, fay;
    if ( x <= n ) fax = a[x - 1][(y / 4) * 2], fay = a[x - 1][(y / 4) * 2 + 1];
    else fax = a[x - 1][y * 2], fay = a[x - 1][y * 2 + 1];
    if ( fax > fay ) swap(fax, fay);
    if ( fax == 0 && fay == 0 ) 
    {
        a[x][y] = 0; DFS(x, y + 1);
        a[x][y] = 0; DFS(x, y + 1);
        a[x][y] = 0; DFS(x, y + 1);
        a[x][y] = 0; DFS(x, y + 1);
    }
    else if ( fax == 0 && fay == 1 ) 
    {
        a[x][y] = 0; DFS(x, y + 1);
        a[x][y] = 0; DFS(x, y + 1);
        a[x][y] = 1; DFS(x, y + 1);
        a[x][y] = 1; DFS(x, y + 1);
    }
    else if ( fax == 0 && fay == 2 ) 
    {
        a[x][y] = 1; DFS(x, y + 1);
        a[x][y] = 1; DFS(x, y + 1);
        a[x][y] = 1; DFS(x, y + 1);
        a[x][y] = 1; DFS(x, y + 1);
    }
    else if ( fax == 1 && fay == 1 ) 
    {
        a[x][y] = 0; DFS(x, y + 1);
        a[x][y] = 1; DFS(x, y + 1);
        a[x][y] = 1; DFS(x, y + 1);
        a[x][y] = 2; DFS(x, y + 1);
    }
    else if ( fax == 1 && fay == 2 ) 
    {
        a[x][y] = 1; DFS(x, y + 1);
        a[x][y] = 1; DFS(x, y + 1);
        a[x][y] = 2; DFS(x, y + 1);
        a[x][y] = 2; DFS(x, y + 1);
    }
    else if ( fax == 2 && fay == 2 ) 
    {
        a[x][y] = 2; DFS(x, y + 1);
        a[x][y] = 2; DFS(x, y + 1);
        a[x][y] = 2; DFS(x, y + 1);
        a[x][y] = 2; DFS(x, y + 1);
    }
}

signed main()
{
    freopen("medium.in", "r", stdin);
    freopen("medium.out", "w", stdout);
    scanf("%lld%lld%lld", &n, &m, &q);
    REP(i, 0, 2 * n + 1) 
    {
        if ( i <= n ) p[i] = power(2, i + 1);
        else p[i] = power(2, 2 * n + 1 - i);
    }
    a[0][0] = a[0][1] = 1;
    getchar();
    REP(i, 1, m) 
    {
        scanf("(%lld,%lld)", &f[i].first, &f[i].second);
        c[f[i].first][f[i].second] = 1;
        getchar();
    }
    DFS(1, 0);
    REP(i, 1, q) 
    {
        int x, y; scanf("(%lld,%lld)", &x, &y);
        getchar();
        printf("%lld\n", b[x][y] * power(ans, Mod - 2) % Mod);
    }
    return 0;
}
