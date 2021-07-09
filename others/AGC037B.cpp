/***************************************************************
	File name: AGC037B.cpp
	Author: ljfcnyali
	Create time: 2021年02月03日 星期三 21时40分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 3e5 + 10;
const int Mod = 998244353;

int n, num[10];
char s[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n); scanf("%s", s + 1);
	int ans = 1; REP(i, 1, n) ans = ans * i % Mod;
	REP(i, 1, n + n + n)
	{
		int c = s[i] == 'R' ? 0 : (s[i] == 'G' ? 1 : 2); 
		if ( num[c + 3] ) ans = ans * (num[c + 3] --) % Mod; 
		else if ( num[(c + 1) % 3] ) { ans = ans * (num[(c + 1) % 3] --) % Mod; ++ num[(c + 2) % 3 + 3]; }
		else if ( num[(c + 2) % 3] ) { ans = ans * (num[(c + 2) % 3] --) % Mod; ++ num[(c + 1) % 3 + 3]; }
		else ++ num[c];
	}
	printf("%lld\n", ans);
    return 0;
}
