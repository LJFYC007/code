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

const int maxn = 4e5 + 10;
const int INF= 1e9;

int T, n, m, a[maxn], b[maxn];
int preMin[maxn], preMax[maxn], sufMin[maxn], sufMax[maxn];
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &T);
	while (T -- )
	{
		scanf("%d%d",&n,&m);
		a[0] = 0;
		scanf("%s", s + 1); REP(i, 1, n) { a[i] = s[i] == '+' ? 1 : -1; b[i] = b[i - 1] + a[i]; }
		preMin[0] = 0; sufMin[n + 1] = INF;
		preMax[0] = 0; sufMax[n + 1] = -INF;
		REP(i, 1, n)
		{
			preMin[i] = min(preMin[i - 1], b[i]);
			preMax[i] = max(preMax[i - 1], b[i]);
		}
		for ( int i = n; i >= 1; -- i )
		{
			sufMin[i] = min(sufMin[i + 1], b[i]);
			sufMax[i] = max(sufMax[i + 1], b[i]);
		}
		while ( m -- )
		{
			int l, r; scanf("%d%d",&l, &r);
			int Max = max(preMax[l - 1], sufMax[r + 1] - (b[r] - b[l - 1]));
			int Min = min(preMin[l - 1], sufMin[r + 1] - (b[r] - b[l - 1]));
			printf("%d\n", Max - Min +1);
		}
	}
    return 0;
}
