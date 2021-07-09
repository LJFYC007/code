/***************************************************************
	File name: a.cpp
	Author: ljfcnyali
	Create time: 2019年09月22日 星期日 08时53分48秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
typedef long long LL;

const int maxn = 4000010;

int n, a[maxn], c[maxn], ans, sum;

inline int lowbit(int x) { return x & -x; }

inline void Modify(int pos, int val)
{
    for ( int i = pos; i <= 2 * n; i += lowbit(i) ) 
        c[i] += val;
}

inline int Query(int pos)
{
    int sum = 0;
    for ( int i = pos; i > 0; i -= lowbit(i) ) sum += c[i];
    return sum;
}

signed main()
{
    freopen("a.in", "r", stdin);
    freopen("a.out", "w", stdout);
    scanf("%lld", &n);
    REP(i, 1, n) 
    { 
        scanf("%lld", &a[i]); 
        if ( a[i] > i ) Modify(a[i] - i, 1);
        // if ( a[i] > i ) ++ p[a[i] - i]; 
        sum += abs(a[i] - i);
    }
    ans = sum;
    REP(i, 1, n - 1)
    {
        int t = n - i + 1;
        if ( a[t] > t ) Modify(a[t] - t, -1); 
        int x = Query(2 * n) - Query(i - 1);
        sum = sum - x + (n - x - 1) - abs(a[t] - n) + abs(a[t] - 1);
        // printf("%lld ", sum);
        ans = min(ans, sum);
        Modify(i + a[t] - 1, 1);
    }
    printf("%lld\n", ans);
    return 0;
}
