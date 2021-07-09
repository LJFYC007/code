/***************************************************************
	File name: 1.cpp
	Author: ljfcnyali
	Create time: 2020年11月23日 星期一 09时51分26秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

inline int C(int n, int m)
{
    int ret = 1;
    REP(i, m + 1, n) ret *= i;
    REP(i, 1, n - m) ret /= i;
    return ret;
}

inline int sgn(int x) { return x & 1 ? -1 : 1; }

int main()
{
    int ans = 0, n = 3;
    REP(i, 0, n)
    {
        int x = C(n, i) * sgn(i);
        REP(j, 1, i) x *= j;
        REP(j, 2 * i + 1, 2 * n) x *= j;
        REP(j, 1, n - i) x /= 2;
        cout <<x << endl;
        ans += x;
    }
    printf("%d\n", ans);
    return 0;
}
