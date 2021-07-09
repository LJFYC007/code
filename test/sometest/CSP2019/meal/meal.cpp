#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset((a), 0, sizeof(a))
#define str(a) strlen(a)
#define int long long

const int maxn = 2010;
const int Mod = 998244353;
const int x = 101;

int f[110][210], n, m, a[110][maxn], ans = 1, sum[110];

signed main()
{
	freopen("meal.in", "r", stdin);
	freopen("meal.out", "w", stdout);
	scanf("%lld%lld", &n, &m);
	REP(i, 1, n) 
    {
        REP(j, 1, m) { scanf("%lld", &a[i][j]); sum[i] = (sum[i] + a[i][j]) % Mod; }
        ans = ans * (sum[i] + 1) % Mod;
    }
    -- ans;
	REP(y, 1, m)
	{
        mem(f);
		f[0][0 + x] = 1;
		REP(i, 1, n) 
        {
            REP(j, -i, i)
    		{
	    		f[i][j + x] = (f[i][j + x] + f[i - 1][j + 1 + x] * (sum[i] - a[i][y])) % Mod;
                f[i][j + x] = (f[i][j + x] + f[i - 1][j - 1 + x] * a[i][y]) % Mod;
		    }
            REP(j, -i + 1, i) f[i][j + x] = (f[i][j + x] + f[i - 1][j + x]) % Mod;
        }
        REP(i, 1, n) ans = (ans - f[n][i + x]) % Mod;
	}
	printf("%lld\n", (ans + Mod) % Mod);
	return 0;
}
