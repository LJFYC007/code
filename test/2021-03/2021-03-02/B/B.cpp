/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2021年03月02日 星期二 14时48分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 3e4 + 10;
const int Mod = 998244353;

int n, k, ans, num[1 << 9], len[maxn];
LL f[maxn][5][1 << 8];
pii h[maxn][10];
struct node { int u, w; } g[5][1 << 8][1 << 9];
char S[maxn];

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%s", S + 1); n = str(S + 1); scanf("%d", &k);
	f[0][0][0] = 1;		

	REP(j, 0, k) REP(s, 0, (1 << k + k) - 1)
	{
		vector<int> p; int sum = -j; REP(o, 0, k - 1) sum -= (s >> o) & 1;
		p.push_back(sum); REP(o, 0, k + k - 1) { sum += (s >> o) & 1; p.push_back(sum); } p.push_back(sum);
		REP(o, 0, (1 << k + k + 1) - 1)
		{
			vector<int> q; int val = p[0];
			REP(t, 0, k + k)	
			{
				val = max(val, p[t + 1]);
				if ( (o >> t) & 1 ) val = max(val, p[t] + 1);
				q.push_back(val);
			}
			int u = 0; REP(t, 1, k + k) u += (q[t] - q[t - 1]) * (1 << t - 1);
			int w = -q[k] + 1; g[j][s][o] = {w, u};
		}
	}

	REP(i, 1, n) 
	{
		REP(j, 0, 25)
		{
			int s = 0;
			REP(o, i - k, i + k) if ( o >= 1 && o <= n && S[o] == j + 'A' ) s += 1 << (o - i + k);
			++ num[s];
		}
		REP(j, 0, (1 << k + k + 1) - 1) if ( num[j] ) { h[i][++ len[i]] = pii(j, num[j]); num[j] = 0; } 
	}

	REP(i, 1, n) REP(j, 0, k) REP(s, 0, (1 << k + k) - 1) 
	{
		if ( !f[i - 1][j][s] ) continue ; f[i - 1][j][s] %= Mod;
		REP(o, 1, len[i])
		{
			node t = g[j][s][h[i][o].first]; 
			if ( t.u <= k ) f[i][t.u][t.w] += f[i - 1][j][s] * h[i][o].second;
		}
	}

	REP(j, 0, k) REP(s, 0, (1 << k + k) - 1) ans = (ans + f[n][j][s] % Mod) % Mod;
	printf("%d\n", ans);
    return 0;
}
