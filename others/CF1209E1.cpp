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
const int maxn = 120;
 
int T, n, m, a[maxn][maxn], b[20], num, ans;
bool vis[maxn], use[maxn][maxn];
 
inline int calc()
{
    int sum = 0;
    REP(i, 1, n)
    {
        int Max = 0;
        REP(j, 1, m) Max = max(Max, a[i][j]);
        sum += Max;
    }
    return sum;
}
 
inline void Move(int x)
{
    int val = a[1][x];
    REP(i, 2, n) a[i - 1][x] = a[i][x];
    a[n][x] = val;
}
 
inline void DFS(int x)
{
    if ( x == num + 1 ) { ans = max(ans, calc()); return ; }
    REP(i, 1, n) { Move(b[x]); DFS(x + 1); }
}
 
int main()
{
    srand(time(0));
    scanf("%d", &T);
    while ( T -- )
    {
        scanf("%d%d", &n, &m);
        REP(i, 1, m) vis[i] = false;
        num = ans = 0; int s = 0;
        REP(i, 1, n) 
        {
            int Max = 0, Maxx = 0, k1 = 0, k2 = 0;
            REP(j, 1, m) 
            {
                scanf("%d", &a[i][j]); 
                if ( a[i][j] > Max ) { Maxx = Max; Max = a[i][j]; k2 = k1; k1 = j; }
                else if ( a[i][j] > Maxx ) { Maxx = a[i][j]; k2 = j; }
            }
            if ( !vis[k1] && k1 ) { vis[k1] = true; b[++ num] = k1; ++ s; }
            if ( !vis[k2] && k1 ) { vis[k2] = true; b[++ num] = k2; }
        }
        if ( s <= 2 && rand() % 2 == 0 )
        {
            REP(i, 1, n)
            {
                int Max = 0, k1 = 0;
                REP(j, 1, m) 
                {
                    if ( a[i][j] > Max && !vis[j] ) { Max = a[i][j]; k1 = j; }
                }
                if ( !vis[k1] && k1 ) { vis[k1] = true; b[++ num] = k1; }
            }
        }
        if ( m == 1 ) { REP(i, 1, n) ans += a[i][1]; printf("%d\n", ans); continue ; }
        if ( n <= 3 ) 
        { 
            mem(use);
            REP(k, 1, n)
            {
                int Max = 0, x, y;
                REP(i, 1, n) REP(j, 1, m) if ( !use[i][j] && a[i][j] > Max )
                {
                    Max = a[i][j]; x = i; y = j;
                }
                use[x][y] = true; ans += Max;
            }
            printf("%d\n", ans); continue ; 
        }
        DFS(1);
        printf("%d\n", ans);
    }
	return 0;
}
