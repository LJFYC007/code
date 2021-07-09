/***************************************************************
	File name: CF674F.cpp
	Author: ljfcnyali
	Create time: 2021年01月21日 星期四 21时42分14秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
#define int unsigned int 
typedef long long LL;

const int maxn = 310;

int n, p, q, ans, C[maxn];

inline int Get(int m)
{
    vector<int> p; REP(i, n - m + 1, n) p.push_back(i);
    REP(i, 2, m)
    {
        int x = i;
        for ( int j = 0; j < p.size(); ++ j ) 
        {
            int t = __gcd(x, p[j]);
            x /= t; p[j] /= t;
        }
    }
    int val = 1; for ( auto it : p ) val *= it; return val;
}

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%u%u%u", &n, &p, &q); p = min(n - 1, p);
    REP(i, 0, p) C[i] = Get(i);
    REP(m, 1, q)
    {
        int ret = 0, sum = 1;
        REP(i, 0, p) { ret += C[i] * sum; sum *= m; }
        ans ^= m * ret;
    }
    printf("%u\n", ans);
    return 0;
}
