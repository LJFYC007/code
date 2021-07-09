#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof(a) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long

const int maxn = 1010;
const int Mod = 1e9 + 7;

int n, L, X, Y, K, ans;
int f[maxn][10][maxn];

signed main()
{
#ifndef ONLINE_JUDGE
	freopen("input.txt", "r", stdin);
	freopen("output1.txt", "w", stdout);
#endif
	cin >> n >> L >> Y >> X >> K;
	REP(i, 0, K) f[0][i][0] = 1;
	REP(i, 1, X) REP(j, 0, n - 1) REP(k, 0, L + 1) REP(o, 0, K)
	{
		if ( j + o > n - 1 ) break ; 
		int num = min(L + 1, k + o * i);
		f[i][j + o][num] = (f[i][j + o][num] + f[i - 1][j][k]) % Mod;	
	}
	// REP(k, Y + 1, L + 1) ans = (ans + f[X][n - 1][k] * (k - Y)) % Mod;
	REP(k, 0, L + 1) ans = (ans + f[X][n - 1][k]) % Mod; ans = ans * (L - Y + 1) % Mod;
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
