/***************************************************************
	File name: game.cpp
	Author: ljfcnyali
	Create time: 2020年08月11日 星期二 10时46分59秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define int long long
#define pii pair<int, int>
#define x first
#define y second
typedef long long LL;

const int maxn = 5e6 + 10;
const int INF = 1e18;

int threshold = 10000000, n, k, a[maxn], b[maxn], c[maxn], t, ans, ret;
pii lst;
priority_queue<pii> Q1, Q2, Q3;
unsigned long long k1, k2;

unsigned long long xorShift128Plus()
{
    unsigned long long k3=k1,k4=k2;
    k1=k4;
    k3^=k3<<23;
    k2=k3^k4^(k3>>17)^(k4>>26);
    return k2+k4;
}
void gen()
{
    scanf("%lld%lld%llu%llu",&n,&k,&k1,&k2);
    for(int i=1;i<=n;i++)
    {
        a[i]=xorShift128Plus()%threshold+1;
        b[i]=xorShift128Plus()%threshold+1;
    }
} 

signed main()
{
#ifndef ONLINE_JUDGE
    freopen("A.in", "r", stdin);
    freopen("A.out", "w", stdout);
#endif
    gen(); REP(i, 1, n) b[i] += a[i];
    sort(a + 1, a + n + 1); sort(b + 1, b + n + 1);
    int m = n;
    while ( k -- ) 
    {
        ans += a[n]; c[++ t] = a[n]; -- n; 
        while ( t > 1 && c[t] + c[t - 1] < b[m] ) 
        {
            ans += b[m] - c[t] - c[t - 1];
            a[++ n] = c[t --]; a[++ n] = c[t --];
            -- m;
        }
        ret ^= ans;
    }
    printf("%lld\n", ret);
    return 0;
}
