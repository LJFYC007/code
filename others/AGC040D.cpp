/***************************************************************
	File name: AGC040D.cpp
	Author: ljfcnyali
	Create time: 2021年06月27日 星期日 11时20分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
#define x first
#define y second
typedef long long LL;

const int maxn = 1e5 + 10;

int n, suf[maxn], sum; pii a[maxn], ans = pii(0, 1);

inline int Get(int x, int y) { return suf[x] - (y >= x ? max(a[y].first, a[y].second) : 0); }

inline pii calc(pii c)
{
	int d = __gcd(c.first, c.second); c.first /= d; c.second /= d;
	return c;
}

inline pii operator + (pii a, pii b)
{
	int d = __gcd(a.second, b.second); 
	pii c = pii(a.first * (b.second / d) + (a.second / d) * b.first, (a.second / d) * b.second);
	return calc(c);
}

inline pii Max(pii a, pii b) { return (double)(a.first) / a.second > (double)(b.first) / b.second ? a : b;  }

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) { scanf("%lld%lld", &a[i].x, &a[i].y); sum += a[i].x; } 
	sort(a + 1, a + n + 1, [](const pii &a, const pii &b) { return max(a.first, a.second) < max(b.first, b.second); });
	for ( int i = n; i >= 1; -- i ) suf[i] = suf[i + 1] + max(a[i].first, a[i].second);
	REP(i, 1, n)
	{
		int l = 1, r = n, pos = 1;
		while ( l <= r ) 
		{
			int Mid = l + r >> 1;
			if ( sum - a[i].y <= Get(Mid, i) ) { pos = Mid; l = Mid + 1; } 
			else r = Mid - 1;
		}
		if ( pos == 0 ) continue ; 
		int val = a[i].y + Get(pos, i) - sum;
		val = min(val, a[i].y);
		ans = Max(ans, pii(pos - 1 - (i < pos), n) + pii(val, a[i].y * n)); 
	}
	printf("%lld %lld\n", ans.first, ans.second);
    return 0;
}
