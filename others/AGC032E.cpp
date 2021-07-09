/***************************************************************
	File name: AGC032E.cpp
	Author: ljfcnyali
	Create time: 2021年01月18日 星期一 20时53分41秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2e5 + 10;

int n, m, a[maxn], ans;

inline bool Check(int x)
{
    REP(i, 1, n - x) if ( a[x + x + i] + a[n + n - i + 1] < m ) return false;
    return true;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d%d", &n, &m);
    REP(i, 1, n + n) scanf("%d", &a[i]);
    sort(a + 1, a + n + n + 1);
    int L = 0, R = n, pos = 0;
    while ( L <= R ) 
    {
        int Mid = L + R >> 1;
        if ( Check(Mid) ) { pos = Mid; R = Mid - 1; } 
        else L = Mid + 1;
    }
    REP(i, 1, pos) ans = max(ans, a[i] + a[pos + pos - i + 1]);
    REP(i, 1, n - pos) ans = max(ans, a[pos + pos + i] + a[n + n - i + 1] - m);
    printf("%d\n", ans);
    return 0;
}
