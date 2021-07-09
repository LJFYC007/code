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

const int maxn = 10010;

int a[maxn], b[maxn], sum1, sum2, n, m, ans, cnt1, cnt2;

inline bool cmp(int a, int b)
{
    return a > b;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n - 1) scanf("%d", &a[i]);
    REP(i, 1, m - 1) scanf("%d", &b[i]);
    sort ( a + 1, a + n, cmp );
    sort ( b + 1, b + m, cmp );
    cnt1 = cnt2 = 1;
    REP(i, 1, n + m - 2) 
    {
        if ( a[cnt1] > b[cnt2] ) 
        {
            ++ sum1;
            ans += (sum2 + 1) * a[cnt1 ++];
        }
        else
        {
            ++ sum2;
            ans += (sum1 + 1) * b[cnt2 ++];
        }
    }
    printf("%d\n", ans);
    return 0;
}
