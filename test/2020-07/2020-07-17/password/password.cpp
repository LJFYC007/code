/***************************************************************
	File name: password.cpp
	Author: ljfcnyali
	Create time: 2020年07月17日 星期五 11时45分17秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
typedef long long LL;

int C, n, m;
vector<pii> Edge;

signed main()
{
    freopen("password.in", "r", stdin);
    freopen("password.out", "w", stdout);
    scanf("%lld%lld%lld", &C, &n, &m);
    REP(i, 1, 59) Edge.push_back(pii(i, i + 1));
    REP(i, 1, 60) Edge.push_back(pii(i, 61));
    Edge.push_back(pii(60, 62));
    // Edge.push_back(pii(61, 1));
    REP(i, 0, 59) if ( (C >> i) & 1 ) Edge.push_back(pii(61, i + 1));
    printf("%lld %lld\n", 62, Edge.size());
    for ( auto i : Edge ) printf("%lld %lld\n", i.second, i.first);
    // for ( auto i : Edge ) printf("%lld %lld\n", i.first, i.second);
    return 0;
}
