/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年12月27日 星期日 09时04分38秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 610;
const int INF = 0x3f3f3f3f;

int n, f[maxn][maxn][21], g[maxn * maxn], h[maxn][maxn][21];

inline void chkmax(int &x, int y) { x = x > y ? x : y; }

inline int find(int i, int y, int k)
{
    REP(z, i, n) if ( f[z - i + y][0][k - 1] < 0 ) return z - 1;
    return n;
}

inline int Check(int x, int y, int k, int i)
{
    if ( i <= x ) return min(f[x - i][y][k - 1], (0 <= f[i + y][0][k - 1] ? n : -2));
    i -= x; if ( i < y ) return min(f[i][y - i][k - 1], (y - i <= f[x][i][k - 1] ? n : -2));
    i -= y; return min(find(i, y, k), (i <= f[x][y][k - 1] ? n : -2));
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); 
    memset(f, -1, sizeof(f));
    REP(i, 2, n + n) g[i] = g[(i + 1) / 2] + 1;
    REP(i, 0, n) REP(j, 0, n) chkmax(f[i][0][g[i + j]], j);
    chkmax(f[0][1][0], 0);
    memset(h, 1, sizeof(h));

    REP(k, 1, 20) REP(y, 1, n) 
    {
        REP(x, 0 , n - y)
        // for ( int x = n - y; x >= 0; -- x ) 
        {
            // int pos = h[x][y][k - 1];
            // while ( pos < n && Check(x, y, k, pos) <= Check(x, y, k, pos + 1) ) ++ pos;
            // if ( Check(x, y, k, pos) == -2 ) continue ; 
            REP(pos, 1, n)
            chkmax(f[x][y][k], Check(x, y, k, pos));
            // h[x][y][k] = pos;
            // cout << pos << "," << f[x][y][k] << " ";

            // REP(i, 1, n) cout << Check(x, y, k, i) << " "; cout << endl;
            // if ( f[x][y][k] + x + y >= n ) { REP(j, 0, x - 1) f[j][y][k] = n + n; break ; }
        }
        // cout << endl;
    }
    REP(i, 1, n) REP(k, 0, 20) if ( f[i - 1][n - i + 1][k] >= 0 ) { printf("%d ", k); break ; }
    puts("");
    return 0;
}
