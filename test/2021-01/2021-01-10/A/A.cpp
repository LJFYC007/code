/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年01月10日 星期日 08时28分10秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 5e5 + 10;
const int INF = 0x3f3f3f3f;

int n, a[maxn], Stack[maxn], tot, b[maxn], m, c[maxn];
map<int, int> Map1, Map2;

inline LL Solve(int l, int r)
{
    if ( l + 1 >= r ) return 0;
    int Mid = l + r >> 1; LL ret = Solve(l, Mid) + Solve(Mid + 1, r);
    tot = m = 0;
    REP(i, Mid + 1, r) 
    { 
        if ( !tot || a[i] > a[Stack[tot]] ) Stack[++ tot] = i;
        b[++ m] = a[Stack[tot]] - a[i];
    }
    sort(b + 1, b + m + 1);
    for ( int i = 1, j; i <= m; i = j + 1 ) 
    {
        j = i; while ( j < m && b[j + 1] == b[j] ) ++ j;
        c[i] = j - i + 1;
    }
    int Max = 0, now = 1; Stack[tot + 1] = r + 1;
    for ( int i = Mid; i >= l; -- i ) 
    {
        Max = max(Max, a[i]);
        while ( now <= tot && Max > a[Stack[now]] ) 
        { 
            REP(j, Stack[now], Stack[now + 1] - 1)
                -- c[lower_bound(b + 1, b + m + 1, a[Stack[now]] - a[j]) - b];
            ++ now;
        }
        int x = lower_bound(b + 1, b + m + 1, a[i]) - b;
        if ( x <= m && b[x] == a[i] ) ret += c[x];
    }

    tot = m = 0;
    for ( int i = Mid; i >= l; -- i ) 
    { 
        if ( !tot || a[i] > a[Stack[tot]] ) Stack[++ tot] = i;
        b[++ m] = a[Stack[tot]] - a[i];
    }
    sort(b + 1, b + m + 1);
    for ( int i = 1, j; i <= m; i = j + 1 ) 
    {
        j = i; while ( j < m && b[j + 1] == b[j] ) ++ j;
        c[i] = j - i + 1;
    }
    Max = 0; now = 1; Stack[tot + 1] = l - 1;
    REP(i, Mid + 1, r)
    {
        Max = max(Max, a[i]);
        while ( now <= tot && Max >= a[Stack[now]] ) 
        { 
            for ( int j = Stack[now]; j >= Stack[now + 1] + 1; -- j ) 
                -- c[lower_bound(b + 1, b + m + 1, a[Stack[now]] - a[j]) - b];
            ++ now;
        }
        int x = lower_bound(b + 1, b + m + 1, a[i]) - b;
        if ( x <= m && b[x] == a[i] ) ret += c[x];
    }
    return ret;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); REP(i, 1, n) scanf("%d", &a[i]);
    printf("%lld\n", Solve(1, n));
    return 0;
}
