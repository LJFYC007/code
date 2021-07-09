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

int n, a[maxn], Stack[maxn], tot;
map<int, int> Map1, Map2;

inline LL Solve(int l, int r)
{
    if ( l + 1 >= r ) return 0;
    int Mid = l + r >> 1; LL ret = Solve(l, Mid) + Solve(Mid + 1, r);
    Map1.clear(); Map2.clear(); tot = 0;
    REP(i, Mid + 1, r) 
    { 
        if ( !tot || a[i] > a[Stack[tot]] ) Stack[++ tot] = i;
        // ++ Map1[a[Stack[tot]] - a[i]]; 
    }
    int Max = 0, now = 1; Stack[tot + 1] = r + 1;
    for ( int i = Mid; i >= l; -- i ) 
    {
        Max = max(Max, a[i]);
        while ( now <= tot && Max > a[Stack[now]] ) 
        { 
            REP(j, Stack[now], Stack[now + 1] - 1)
            {
                // -- Map1[a[Stack[now]] - a[j]];
                ++ Map2[a[j]];
            }
            ++ now;
        }
        ret += Map2[Max - a[i]] + Map1[a[i]];
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
