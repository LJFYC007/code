/***************************************************************
	File name: C.cpp
	Author: ljfcnyali
	Create time: 2021年02月23日 星期二 17时46分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, pre[maxn], suf[maxn], ans;
char s[maxn], t[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &m);
	scanf("%s", s + 1); scanf("%s", t + 1);
	int pos = 0;
	REP(i, 1, n) if ( t[pos + 1] == s[i] ) { ++ pos; pre[pos] = i; } 
	pos = m + 1;
	for ( int i = n; i >= 1; -- i ) if ( t[pos - 1] == s[i] ) { -- pos; suf[pos] = i; }
	REP(i, 2, m) ans = max(ans, suf[i] - pre[i - 1]);
	printf("%d\n", ans);
    return 0;
}
