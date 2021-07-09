/***************************************************************
	File name: bf.cpp
	Author: ljfcnyali
	Create time: 2021年05月07日 星期五 09时17分21秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int n, m, a[maxn], ans, f[maxn], pre[maxn];
char s[21][maxn], t[maxn];

int main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
#endif
	scanf("%d", &n); REP(i, 1, n) scanf("%s", s[i] + 1);
	REP(i, 1, n) a[i] = i;	
	do
	{
		m = 0;
		REP(i, 1, n) REP(j, 1, str(s[a[i]] + 1))
			t[++ m] = s[a[i]][j];
		f[0] = 1;
		REP(i, 1, 26) pre[i] = 0;
		REP(i, 1, m)
		{
			f[i] = 0; int c = t[i] - 'a' + 1;
			if ( pre[c] && f[pre[c] - 1] == 1 ) f[i] = 1;
			pre[c] = i;
		}
		if ( f[m] == 0 ) 
		{
			REP(i, 1, m) printf("%c", t[i]); puts("");
			++ ans;
		}
	} while ( next_permutation(a + 1, a + n + 1) ) ;
	printf("%d\n", ans);
    return 0;
}
