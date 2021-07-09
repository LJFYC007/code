/***************************************************************
	File name: P5056.cpp
	Author: ljfcnyali
	Create time: 2019年09月17日 星期二 15时41分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 20;
// const int M = 10000000ll;

map<LL, LL> f;
int n, m, p[maxn], X, Y;
char a[maxn][maxn];

inline char read()
{
    char c = getchar();
    while ( c != '*' && c != '.' ) c = getchar();
    return c;
}

inline LL DFS(int x, int y, int s)
{
    long long t = s * m * n + x * m + y, ans = 0; 
    if ( f.count(t) ) return f[t];
    if ( a[x][y] == '*' ) 
    {
        if ( s / p[y - 1] % 9 == 0 ) 
        {
            if ( y == m ) ans = DFS(x + 1, 1, s * 3);
            else ans = DFS(x, y + 1, s);
        }
        f[t] = ans; return ans;
    }
    if ( x == X && y == Y ) { if ( !(s - 7 * p[y - 1]) ) ans = 1; f[t] = ans; return ans; }
    switch ( s / p[y - 1] % 9 )
    {
        case 0:
        {
            int S = s + 7 * p[y - 1];
            if ( y != m ) ans += DFS(x, y + 1, S);
            break ;
        }
        case 4:
        {
            int S = s - 4 * p[y - 1], tot = 1;
            for ( int i = y + 2; i <= m; ++ i )
                if ( s / p[i - 1] % 3 == 1 ) ++ tot;
                else if ( s / p[i - 1] % 3 == 2 ) 
                {
                    -- tot;
                    if ( !tot ) { S -= p[i - 1]; break ; }
                }
            if ( y != m ) ans += DFS(x, y + 1, S);
            break ;
        }
        case 8:
        {
            int S = s - 8 * p[y - 1], tot = 1;
            for ( int i = y - 1; i >= 1; -- i ) 
                if ( s / p[i - 1] % 3 == 2 ) ++ tot;
                else if ( s / p[i - 1] % 3 == 1 )
                {
                    -- tot;
                    if ( !tot ) { S += p[i - 1]; break ; }
                }
            if ( y != m ) ans += DFS(x, y + 1, S);
            else ans += DFS(x + 1, 1, S * 3);
            break ;
        } 
        case 5:
        {
            int S = s - 5 * p[y - 1];
            if ( y != m ) ans += DFS(x, y + 1, S);
            break ;
        }
        case 1:
        case 2:
        {
            int k = s / p[y - 1] % 3, S = s - k * p[y - 1];
            if ( y != m ) ans += DFS(x, y + 1, S + k * p[y - 1]) + DFS(x, y + 1, S + k * p[y]);
            else ans += DFS(x + 1, 1, (S + k * p[y - 1]) * 3);
            break ;
        }
        case 3:
        case 6:
        {
            int k = s / p[y] % 3, S = s - k * p[y];
            if ( y != m ) ans += DFS(x, y + 1, S + k * p[y - 1]) + DFS(x, y + 1, S + k * p[y]);
            else ans += DFS(x + 1, 1, (S + k * p[y - 1]) * 3);
            break ;
        }
    }
    f[t] = ans; return ans;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) REP(j, 1, m) { a[i][j] = read(); if ( a[i][j] == '.' ) { X = i; Y = j; } } 
    p[0] = 1; REP(i, 1, 12) p[i] = p[i - 1] * 3;
    printf("%lld\n", DFS(1, 1, 0));
    return 0;
}
