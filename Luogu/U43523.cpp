#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

const int maxn = 1010;

int a[maxn][maxn], n, m, sum[maxn][maxn], ans, p[maxn][maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) 
    {
        REP(j, 1, m) 
        {
            scanf("%d", &a[i][j]);
            if ( !a[i][j] ) p[i][j] = p[i][j - 1] + 1;
            else p[i][j] = 0;
        }
        for ( int j = m; j >= 1; -- j )
            if ( a[i][j] ) sum[i][j] = sum[i][j + 1] + 1;
            else sum[i][j] = 0;
    }
/*    REP(i, 1, n)
    {
        REP(j, 1, m)
            printf("%d ", sum[i][j]);
        puts("");
    }

    puts("");
    REP(i, 1, n)
    {
        REP(j, 1, m)
            printf("%d ", p[i][j]);
        puts("");
    }
*/
    REP(i, 1, n)
    {
        if ( i + ans > n ) break ;
        for ( int j = 1; j <= m; ++ j ) 
        {
            if ( j + ans > m ) break ; 
            if ( sum[i][j] <= ans ) continue ;
            if ( a[i][j + sum[i][j]] ) continue ;
            REP(k, i + 1, i + sum[i][j] - 1)
            {
                if ( sum[k][j] == sum[i][j] - k + i && p[k][j + sum[i][j]] == k - i + 1 ) continue ; 
                goto no;
            }
            ans = max(ans, sum[i][j]);
no : ;
        }
    } 
    printf("%d\n", ans);
    return 0;
}
