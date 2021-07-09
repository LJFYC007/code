/***************************************************************
	File name: AGC027E.cpp
	Author: ljfcnyali
	Create time: 2021年04月22日 星期四 16时10分06秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int Mod = 1e9 + 7;

int n, f[maxn], suf[maxn], ans, pre[maxn], nxt[maxn];
vector<int> p[3];
char s[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%s", s + 1); n = str(s + 1);
	REP(i, 1, n) pre[i] = (pre[i - 1] + s[i] - 'a' + 1) % 3;
	for ( int i = n; i >= 1; -- i ) suf[i] = (suf[i + 1] + s[i] - 'a' + 1) % 3;
	for ( int i = n; i >= 1; -- i ) p[pre[i]].push_back(i); 
	nxt[n] = n + 1; for ( int i = n - 1; i >= 1; -- i ) { nxt[i] = nxt[i + 1]; if ( s[i] == s[i + 1] ) nxt[i] = i + 1; } 
	if ( nxt[1] == n + 1 ) { puts("1"); return 0; } 
	f[0] = 1;
	REP(i, 1, n) 
	{
		f[i] = (f[i] + f[i - 1]) % Mod; int c = s[i] - 'a' + 1;
		REP(o, 0, 2) while ( !p[o].empty() && p[o].back() < nxt[i] ) p[o].pop_back();
		if ( !p[3 - c].empty() ) f[p[3 - c].back()] = (f[p[3 - c].back()] + f[i - 1]) % Mod;
		if ( c == 1 ) { swap(p[1], p[2]); swap(p[0], p[2]); }
		else { swap(p[0], p[2]); swap(p[1], p[2]); }
		if ( suf[i + 1] == 0 ) ans = (ans + f[i]) % Mod;
	}
	printf("%d\n", ans);
    return 0;
}
