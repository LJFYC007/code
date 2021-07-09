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
#define int long long
#define pii pair<int, int>
typedef long long LL;
 
const int maxn = 3e4 + 10;
const int Mod = 998244353;
 
int n, k, f[maxn][5][1 << 8], ans;
char S[maxn];
 
signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%s", S + 1); n = str(S + 1); scanf("%lld", &k);
    f[0][0][0] = 1;     
    REP(i, 1, n) REP(j, 0, k) REP(s, 0, (1 << k + k) - 1)
    {
        if ( !f[i - 1][j][s] ) continue ; 
		cout << i - 1 << " " << j << " " << s << " " << f[i - 1][j][s] << endl;
        vector<int> p; int sum = i - 1 - j; REP(o, 0, k - 1) sum -= (s >> o) & 1;
        p.push_back(sum); REP(o, 0, k + k - 1) { sum += (s >> o) & 1; p.push_back(sum); } p.push_back(sum);
        REP(o, 0, 25)
        {
            vector<int> q; int val = p[0];
            REP(t, i - k, i + k)    
            {
                val = max(val, p[t - i + k + 1]);
                if ( t > 0 && t <= n && o + 'A' == S[t] ) val = max(val, p[t - i + k] + 1);
                q.push_back(val);
            }
            int u = 0; REP(t, 1, k + k) u += (q[t] - q[t - 1]) * (1 << t - 1);
            int w = i - q[k]; f[i][w][u] = (f[i][w][u] + f[i - 1][j][s]) % Mod;
        }
    }
    REP(j, 0, k) REP(s, 0, (1 << k + k) - 1) ans = (ans + f[n][j][s]) % Mod;
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
