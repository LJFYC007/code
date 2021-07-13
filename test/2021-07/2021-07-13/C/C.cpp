/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年07月13日 星期二 08时28分18秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<double, double>
#define x first
#define y second
typedef long long LL;

const int maxn = 2e5 + 10;
const double pi = acos(-1);

int n; pii a[maxn]; double ans[maxn], val[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	REP(i, 1, n) scanf("%lf%lf", &a[i].first, &a[i].second);
	vector<int> p; REP(i, 1, n) p.push_back(i);
	double theta = 0;
	REP(o, 1, 50)
	{
		theta += pi / 50; double A = cos(theta), B = sin(theta);
		REP(i, 1, n) val[i] = A * a[i].first + B * a[i].second;
		sort(p.begin(), p.end(), [](const int &a, const int &b) { return val[a] < val[b]; });
		double pre = 0, suf = 0; REP(i, 1, n) suf += val[i];
		REP(i, 0, n - 1)
		{
			int pos = p[i]; suf -= val[pos];
			ans[pos] += suf - pre + val[pos] * (i - (n - 1 - i));
			pre += val[pos];
		}
	}
	REP(i, 1, n) printf("%.10lf\n", ans[i] * pi / 100);
    return 0;
}
