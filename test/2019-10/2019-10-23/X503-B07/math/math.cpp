/***************************************************************
	File name: math.cpp
	Author: ljfcnyali
	Create time: 2019年10月23日 星期三 08时35分09秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;
#define int long long

int n, ans;
map<int, int> Map1, Map2;

signed main()
{
    freopen("math.in", "r", stdin);
    freopen("math.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) { int x; scanf("%lld", &x); ++ Map1[x]; }
    REP(i, 1, n) { int x; scanf("%lld", &x); ++ Map2[x]; }
    for ( auto i : Map1 )
        for ( auto j : Map2 )
            ans += i.second * j.second * (int) (sqrt(abs(i.first - j.first)));
    printf("%lld\n", ans);
    return 0;
}
