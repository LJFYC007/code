/***************************************************************
	File name: anticipate.cpp
	Author: ljfcnyali
	Create time: 2020年07月18日 星期六 10时41分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<double, double>
typedef long long LL;

const int maxn = 51;
const double eps = 1e-12;

int op, n, l, r, x[maxn], y[maxn];
vector<double> a;
stack<int> Stack;

signed main()
{
    freopen("anticipate.in", "r", stdin);
    freopen("anticipate.out", "w", stdout);
    scanf("%lld", &op);
    scanf("%lld%lld%lld", &n, &l, &r);
    REP(i, 1, n) scanf("%lld", &x[i]);
    REP(i, 1, n) scanf("%lld", &y[i]);

    REP(i, 1, n)
    {
        while ( !Stack.empty() && 
    }
    return 0;
}
