/***************************************************************
	File name: seq.cpp
	Author: ljfcnyali
	Create time: 2020年10月07日 星期三 09时03分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 1e5 + 10;
const int inf = 1e18;
const long double INF = 1e18;

int n, m, s[maxn];
pii Min, Max;
long double a[210], k;
bool vis[210];

signed main()
{
    freopen("seq.in", "r", stdin);
    freopen("seq.out", "w", stdout);
    scanf("%lld", &m);
    REP(i, 1, m) { scanf("%lld", &s[i]); if ( s[i] <= 200 ) vis[s[i]] = true; }
    scanf("%lld", &n);
    while ( n -- ) 
    {
        scanf("%Lf%Lf%Lf", &a[0], &a[1], &k);
        Min = pii(inf, s[1]); Max = pii(-inf, s[1]);
        REP(i, 0, 200)
        {
            if ( i > s[m] ) break ; 
            if ( i >= 2 ) a[i] = a[i - 1] * k + a[i - 2];
            if ( a[i] > INF ) { Max.second = s[m]; break ; }
            if ( a[i] < -INF ) { Min.second = s[m]; break ; }
            if ( vis[i] ) 
            {
                if ( a[i] < Min.first ) Min = pii(a[i], i);
                if ( a[i] > Max.first ) Max = pii(a[i], i);
            }
        }
        printf("%lld %lld\n", Max.second, Min.second);
    }
    return 0;
}
