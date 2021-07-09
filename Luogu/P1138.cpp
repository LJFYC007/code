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

int cnt[30010], n, k;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &k);
    REP(i, 1, 30000) cnt[i] = 0x3f3f3f3f;
    REP(i, 1, n)
    {
        int x; scanf("%d", &x);
        cnt[x] = x;
    }
    sort ( cnt + 1, cnt + 30001 );
    if ( cnt[k] == 0x3f3f3f3f ) printf("NO RESULT\n"); 
    else printf("%d\n", cnt[k]);
    return 0;
}
