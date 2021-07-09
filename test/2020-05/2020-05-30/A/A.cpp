/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2020年05月30日 星期六 10时26分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1010;

int n, k, p[maxn][maxn];

inline int power(int a, int b) { int r = 1; while ( b ) { if ( b & 1 ) r *= a; a *= a; b >>= 1; } return r; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    scanf("%d", &n); 
    int x = 1;
    while ( x < n ) { x <<= 1; ++ k; }
    if ( n == 2 ) { puts("-1"); return 0; }
    if ( n & 1 ) 
    {
        for ( int i = k - 1; i >= 0; -- i ) 
        {
            int x = k - i;
            REP(j, 1, n) p[x][j] = (j + power(2, i) - 1) % n + 1;
        }
        printf("%d\n", k);
        REP(i, 1, k) { REP(j, 1, n) printf("%d ", p[i][j]); puts(""); }
        return 0;
    }
    if ( n % 4 == 0 ) 
    {
        for ( int i = k - 2; i >= 0; -- i ) 
        {
            int x = k - i - 1;
            REP(j, 1, n) p[x + 1][j] = (j + power(2, i) - 1) % n + 1;
        }
        REP(i, 1, n / 4)
        {
            p[1][i * 4 - 3] = i * 4 - 1;
            p[1][i * 4 - 2] = i * 4;
            p[1][i * 4 - 1] = i * 4 - 2;
            p[1][i * 4] = i * 4 - 3;
        }
        printf("%d\n", k);
        REP(i, 1, k) { REP(j, 1, n) printf("%d ", p[i][j]); puts(""); }
    }
    else 
    {
        for ( int i = k - 2; i >= 0; -- i ) 
        {
            int x = k - i - 1;
            REP(j, 1, n) p[x + 2][j] = (j + power(2, i) - 1) % n + 1;
        }
        ++ k;
        REP(i, 1, n / 4)
        {
            p[2][i * 4 - 3] = i * 4 - 1;
            p[2][i * 4 - 2] = i * 4;
            p[2][i * 4 - 1] = i * 4 - 2;
            p[2][i * 4] = i * 4 - 3;
        }
        p[2][n] = n; p[2][n - 1] = n - 1;
        REP(i, 2, n - 2) p[1][i] = i;
        p[1][1] = n - 1; p[1][n - 1] = n; p[1][n] = 1;
        printf("%d\n", k);
        REP(i, 1, k) { REP(j, 1, n) printf("%d ", p[i][j]); puts(""); }
    }
    return 0;
}
