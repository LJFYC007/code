/***************************************************************
	File name: divisor.cpp
	Author: ljfcnyali
	Create time: 2020年07月21日 星期二 18时55分01秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int long long
typedef long long LL;

const int maxn = 210;
const int Mod = 1e9 + 7;

int n, m, a[maxn], ans;
unordered_map<int, int> Map;
vector<int> p;

inline void DFS(int x, int sum, int val)
{
    if ( sum > m ) return ;
    if ( x == n + 1 ) 
    {
        int ret = 1, num = 0;
        for ( auto i : p ) ret = (ret * (a[i] + 1) * (a[i] + 2) / 2) % Mod;
        int M = m / sum;
        if ( Map.count(M) ) num = Map[M];
        else
        {
            double cur = clock();
            for ( int i = 1, j; i <= M; i = j + 1 ) 
            {
                j = M / (M / i);
                num = (num + (j - i + 1) * (M / i)) % Mod;
            }
            Map[M] = num;
        }
        ans = (ans + val * ret * num) % Mod;
        return ;
    }
    DFS(x + 1, sum, val);
    if ( a[x] ) { -- a[x]; DFS(x + 1, sum * x, -val); ++ a[x]; }
}

signed main()
{
    freopen("divisor.in", "r", stdin);
    freopen("divisor.out", "w", stdout);
    scanf("%lld%lld", &n, &m);
    REP(i, 1, n)
    {
        int x = i;
        for ( int j = 2; j * j <= x; ++ j ) while ( x % j == 0 ) { x /= j; ++ a[j]; }
        ++ a[x];
    }
    REP(i, 2, n) if ( a[i] ) p.push_back(i);
    DFS(2, 1, 1);
    printf("%lld\n", (ans + Mod) % Mod);
    return 0;
}
