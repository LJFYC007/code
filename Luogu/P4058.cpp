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

const int maxn = 200010;

LL a[maxn], h[maxn], n, S, L;

inline bool judge(LL x)
{
    LL sum = 0;
    REP(i, 1, n)
    {
        LL s = h[i] + a[i] * x;   
        if ( s >= L ) sum += s;
        if ( sum >= S ) return true;
    }
    if ( sum >= S ) return true;
    return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld%lld", &n, &S, &L);
    REP(i, 1, n) scanf("%lld", &h[i]);
    REP(i, 1, n) scanf("%lld", &a[i]);
    if ( n == 1 ) 
    {
        S -= h[1]; L -= h[1];
        if ( S < L ) printf("0\n");
        else printf("%lld\n", S % a[1] == 0 ? S / a[1] : S / a[1] + 1);
        return 0;
    }
    LL l = 0, r = 1000000000000000000;
    LL ans = 0;
    while ( l <= r ) 
    {
        LL Mid = (l + r) / 2;
        if ( judge(Mid) )
        {
            ans = Mid; 
            r = Mid - 1;
        }
        else l = Mid + 1;
    }
    printf("%lld\n", ans);
    return 0;
}
