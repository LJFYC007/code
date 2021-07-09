/***************************************************************
	File name: AGC022D.cpp
	Author: ljfcnyali
	Create time: 2021年01月22日 星期五 19时30分37秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 3e5 + 10;
const int INF = 1e18;

int n, l, x[maxn], t[maxn], ans;
set<int> A, B, C;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%lld%lld", &n, &l);
    REP(i, 1, n) scanf("%lld", &x[i]);
    REP(i, 1, n) scanf("%lld", &t[i]);
    ans = (n + 1) * l * 2;
    REP(i, 1, n)
    {
        ans += t[i] / (2 * l) * (2 * l); t[i] %= 2 * l;
        bool t1 = 2 * x[i] >= t[i], t2 = 2 * (l - x[i]) >= t[i];
        if ( (i == n && t2) || !t[i] ) { ans -= l * 2; continue ; } 
        if ( t1 && t2 ) C.insert(i);
        else if ( t1 ) A.insert(-i);
        else if ( t2 ) B.insert(i);
    }
    for ( auto it : B ) if ( C.size() && *C.begin() < it ) { C.erase(C.begin()); ans -= 2 * l; }
    for ( auto it : A ) if ( C.size() && *C.rbegin() > -it ) { C.erase(*C.rbegin()); ans -= 2 * l; }
    ans -= (C.size() / 2) * 2 * l;
    printf("%lld\n", ans);
    return 0;
}
