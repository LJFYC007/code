/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int T, n, m, x, ans[maxn], sum;
pii a[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while ( T -- ) 
	{
		scanf("%d%d%d", &n, &m, &x);
		REP(i, 1, n) { scanf("%d", &a[i].first); a[i].second = i; } 
		puts("YES");
		priority_queue<pii, vector<pii>, greater<pii> > Q;
		sort(a + 1, a + n + 1);
		REP(i, 1, m) { Q.push(pii(a[i].first, i)); ans[a[i].second] = i; } 
		REP(i, m + 1, n)
		{
			int x = Q.top().first, y = Q.top().second; Q.pop();
			ans[a[i].second] = y; Q.push(pii(x + a[i].first, y));
		}
		REP(i, 1, n) printf("%d ", ans[i]); puts("");
	}
    return 0;
}
