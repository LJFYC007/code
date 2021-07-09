/***************************************************************
	File name: b.cpp
	Author: ljfcnyali
	Create time: 2019年11月11日 星期一 09时26分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 50010;
const int Mod = 1e9 + 7;

int n, a[maxn], ans, c[maxn][2], sum, Map[maxn], ret, N;

inline int lowbit(int x) { return x & -x; }

inline void add(int pos, int val, int opt) 
{
    for ( int i = pos; i <= N; i += lowbit(i) ) c[i][opt] += val;
}

inline int Get(int pos, int opt)
{
    LL sum = 0;
    for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i][opt];
    return sum % Mod;
}

int main()
{
    freopen("b.in", "r", stdin);
    freopen("b.out", "w", stdout);
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d", &a[i]); N = max(N, a[i]); }
    REP(i, 1, n)
    {   
        if ( a[i] == a[i - 1] ) { ans += sum + a[i]; ans = ans >= Mod ? ans - Mod : ans; continue ; }
        sum = ret = 0; int val = 0;
        for ( int j = i; j >= 1; -- j )
        {
            if ( Map[a[j]] ) { sum += val; sum = sum >= Mod ? sum - Mod : sum; continue ; }
            Map[a[j]] = true; 
            val += (((LL)(a[j])) * (Get(a[j], 0) + 1)) % Mod; val = val >= Mod ? val - Mod : val;
            val -= Get(a[j], 1); val = val < 0 ? val + Mod : val;
            val += ret; val = val >= Mod ? val - Mod : val;
            ret += a[j]; ret = ret >= Mod ? ret - Mod : ret;
            add(a[j], 1, 0);
            add(a[j], a[j], 1);
            sum += val; sum = sum >= Mod ? sum - Mod : sum;
        }
        ans += sum; ans = ans >= Mod ? ans - Mod : ans;
        for ( int j = i; j >= 1; -- j )
        {
            if ( !Map[a[j]] ) continue ;
            Map[a[j]] = 0; add(a[j], -1, 0); add(a[j], -a[j], 1);
        }
    }
    printf("%d\n", ans);
    return 0;
}
