/***************************************************************
	File name: SA.cpp
	Author: ljfcnyali
	Create time: 2021年02月04日 星期四 16时31分40秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e6 + 10;

int n, m = 150, sa[maxn], x[maxn], y[maxn], c[maxn];
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%s", s + 1); n = str(s + 1);
	REP(i, 1, n) { x[i] = s[i]; ++ c[x[i]]; } 
	REP(i, 1, m) c[i] += c[i - 1];
	for ( int i = n; i >= 1; -- i ) sa[c[x[i]] --] = i;
	for ( int k = 1; k <= n; k <<= 1 ) 
	{
		int tot = 0;		
		REP(i, n - k + 1, n) y[++ tot] = i;
		REP(i, 1, n) if ( sa[i] > k ) y[++ tot] = sa[i] - k;
		REP(i, 0, m) c[i] = 0;
		REP(i, 1, n) ++ c[x[i]]; REP(i, 1, m) c[i] += c[i - 1];
		for ( int i = n; i >= 1; -- i ) sa[c[x[y[i]]] --] = y[i];
		REP(i, 1, n) y[i] = x[i];
		tot = 1; x[sa[1]] = tot;
		REP(i, 2, n) x[sa[i]] = (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k]) ? tot : ++ tot;
		m = tot;
	}
	REP(i, 1, n) printf("%d ", sa[i]); puts("");
    return 0;
}
