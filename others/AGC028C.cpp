/***************************************************************
	File name: AGC028C.cpp
	Author: ljfcnyali
	Create time: 2021年06月24日 星期四 15时43分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 2e5 + 10;

int n, a[maxn], b[maxn], sum1, sum2, ans, vis[maxn];
vector<pii> p; 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); 
	REP(i, 1, n) 
	{
		scanf("%lld%lld", &a[i], &b[i]);
		sum1 += a[i]; sum2 += b[i];
		p.push_back(pii(a[i], i)); p.push_back(pii(b[i], -i));		
	}
	ans = min(sum1, sum2);
	sort(p.begin(), p.end());

	bool flag = false; int sum = 0;
	REP(i, 0, n - 1)
	{
		sum += p[i].first;
		int x = p[i].second;
		if ( vis[abs(x)] ) flag = true;
		else vis[abs(x)] = x;
	}
	if ( flag ) ans = min(ans, sum);
	else
	{
		int x;
		if ( abs(p[n - 1].second) != abs(p[n].second) ) x = n - 1;
		else 
		{
			x = n - 2;
			ans = min(ans, sum - p[n - 1].first + p[n + 1].first);
		}
		sum -= p[x].first;
		sum += p[n].first;
		ans = min(ans, sum);
	}

	printf("%lld\n", ans);
    return 0;
}
