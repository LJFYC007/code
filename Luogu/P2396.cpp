/***************************************************************
	File name: P2396.cpp
	Author: ljfcnyali
	Create time: 2019年11月15日 星期五 14时46分58秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 16777216;
const int Mod = 1e9 + 7;

int f[maxn], n, a[25], m, b[3], N;
bool p[maxn];

inline void DFS(int x, int sum, int ret)
{
    if ( x == n ) 
    {
        if ( sum == b[1] || sum == b[2] ) p[ret] = true;
        return ;
    }
    DFS(x + 1, sum, ret);
    DFS(x + 1, sum + a[x], ret | (1 << x));
}

inline int lowbit(int x) { return x & -x; }

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n); N = (1 << n) - 1;
    REP(i, 0, n - 1) scanf("%d", &a[i]); 
    sort(a, a + n);
    b[1] = b[2] = -1;
    scanf("%d", &m);
    REP(i, 1, m) scanf("%d", &b[i]);
    if ( m ) DFS(0, 0, 0); f[0] = 1;
    for ( int i = 1; i <= N; ++ i ) if ( !p[i] )
        for ( int j = i, k = lowbit(j); j; j ^= k, k = lowbit(j) )
        {
            const int x = i ^ k;
            f[i] += f[x]; f[i] = f[i] >= Mod ? f[i] - Mod : f[i];
        }
    printf("%d\n", f[N]);
    return 0;
}
