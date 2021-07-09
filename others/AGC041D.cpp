/***************************************************************
	File name: AGC041D.cpp
	Author: ljfcnyali
	Create time: 2021年07月02日 星期五 20时17分15秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5010;

int n, Mod, a[maxn], f[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d%d", &n, &Mod);
	if ( n & 1 ) 
	{
		REP(i, 1, n / 2 + 1) a[i] = i;
		int sum = n / 2 + 1;
		REP(i, n / 2 + 2, n) { -- sum; a[i] = sum; }
	}
	else
	{
		REP(i, 1, n / 2) a[i] = i;
		int sum = n / 2;
		REP(i, n / 2 + 1, n) { a[i] = sum; sum -- ; }
	}

	f[0] = 1;
	REP(i, 1, n) REP(j, a[i], n - 1) f[j] = (f[j] + f[j - a[i]]) % Mod;
	int ans = 0; REP(i, 0, n - 1) ans = (ans + f[i]) % Mod;
	printf("%d\n", (ans + Mod) % Mod);
    return 0;
}
