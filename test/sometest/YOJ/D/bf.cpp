/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年02月21日 星期日 14时19分28秒
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

int n, x[maxn], c[maxn], s[maxn], f[maxn], l[maxn];
vector<int> p;

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output1.txt", "w", stdout);
#endif
	scanf("%lld", &n); p.push_back(0);
	REP(i, 1, n) { scanf("%lld%lld%lld", &x[i], &c[i], &s[i]); p.push_back(x[i]); } 
	REP(i, 1, n) 
	{
		l[i] = lower_bound(p.begin(), p.end(), x[i] - s[i]) - p.begin() - 1;
		if ( l[i] < 0 ) l[i] = 0;
	}
	REP(i, 1, n)
	{
		f[i] = 100000000;
		REP(j, 1, i) if ( x[j] + s[j] >= x[i] ) 
			f[i] = min(f[i], f[l[j]] + c[j]);
		cout << f[i] << " ";
	}
	printf("%lld\n", f[n]);
    return 0;
}
