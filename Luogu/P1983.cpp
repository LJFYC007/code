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

int a[maxn], s[maxn], f[maxn][maxn]; 
bool vis[maxn][maxn];
int n, m, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) a[i] = 1;
    REP(i, 1, m)
    {
        scanf("%d", &s[i]);
        REP(j, 1, s[i]) 
        {
            int x; scanf("%d", &x);
            f[i][j] = x; vis[i][x] = true;
        }
    }
    while ( 1 )
    {
        bool flag = false;
        REP(i, 1, m)
        {
            int sum = 0;
            REP(j, f[i][1], f[i][s[i]])
                if ( !vis[i][j] ) sum = max(sum, a[j]);
            ++ sum;
            REP(j, 1, s[i])
                if ( a[f[i][j]] < sum ) a[f[i][j]] = sum, flag = true;
        }
        if ( flag == false ) break ;
    }
    REP(i, 1, n) ans = max(ans, a[i]);
    printf("%d\n", ans);
    return 0;
}
