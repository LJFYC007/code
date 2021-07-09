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

const int maxn = 100010;

int a[maxn], b[maxn], m, n, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n) scanf("%d", &a[i]);
    REP(i, 1, m) scanf("%d", &b[i]);
    sort ( a + 1, a + n + 1 ) ;
    sort ( b + 1, b + m + 1 ) ;
    int cnt1 = 1, cnt2 = 1;
    while ( cnt1 <= n && cnt2 <= m ) 
    {
        while ( a[cnt1] >= b[cnt2] && cnt2 <= m ) { ans += b[cnt2]; ++ cnt2; }
        if ( cnt2 > m ) { printf("0\n"); return 0; }
        ++ cnt1; ++ cnt2; 
    }
    if ( cnt1 <= n ) { printf("0\n"); return 0; }
    REP(i, cnt2, m) ans += b[i];
    printf("%d\n", ans);
    return 0;
}
