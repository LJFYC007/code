/***************************************************************
	File name: AGC037E.cpp
	Author: ljfcnyali
	Create time: 2021年01月29日 星期五 16时06分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 10010;

int n, k;
char S[maxn], T[maxn], ans[maxn];
string s, t;

inline void Maintain()
{
	REP(i, 0, n - 1)
	{
		if ( ans[i] < T[i] ) return ;
		if ( T[i] < ans[i] ) 
		{
			REP(j, 0, n - 1) ans[j] = T[j];
			return ;
		}
	}
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &k);
	cin >> s; REP(i, 0, n - 1) ans[i] = s[i];
	t = s; reverse(t.begin(), t.end()); s = s + t;	
	REP(i, 0, n + n - 1) S[i] = s[i];
	REP(i, n - 1, n + n - 1)
	{
		int j = i; while ( S[j - 1] == S[i] ) -- j;
		int len = k == 1 ? 0 : (i - j + 1) * (k <= 20 ? min(n, 1 << k - 2) : n);
		int num = 0;
		REP(o, 1, len * 2) { T[num ++] = S[i]; if ( num == n ) break ; }
		for ( int o = j - 1; o >= j - n + len; -- o ) { T[num ++] = S[o]; if ( num == n ) break ; }
		Maintain();
	}
	REP(i, 0, n - 1) printf("%c", ans[i]); puts("");
    return 0;
}
