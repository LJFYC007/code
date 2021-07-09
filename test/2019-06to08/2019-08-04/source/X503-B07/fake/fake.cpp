/***************************************************************
	File name: fake.cpp
	Author: ljfcnyali
	Create time: 2019年08月04日 星期日 09时55分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

const int maxn = 5010;

int n, A, B, Begin[maxn], Next[maxn], To[maxn], e, num, sum;
char s[2000010];

struct node
{
    int x, sum1, sum2;
    map<int, int> Map;
} a[maxn];

inline void add(int u, int v) { To[++ e] = v; Next[e] = Begin[u]; Begin[u] = e; }

namespace Subtask1 
{
    inline void Solve()
    {
        int T = 1;
        while ( num < sum || T <= 50 ) 
        {
            REP(i, 1, n) 
            {
                if ( a[i].Map[T % a[i].x] == 0 ) continue ;
                for ( int j = Begin[i]; j; j = Next[j] ) 
                {
                    int v = To[j];
                    if ( a[v].Map[T % a[v].x] == 0 ) { a[v].Map[T % a[v].x] = 1; ++ num; }
                }
            }
            ++ T; 
        }
        REP(i, 1, n) REP(j, 0, a[i].x - 1) if ( a[i].Map[j] == 1 ) ++ a[i].sum1; else if ( a[i].Map[j] == 2 ) ++ a[i].sum2;
        int ans = 0, Max = 0;
        REP(i, 1, n) Max = max(Max, a[i].sum2);
        REP(i, 1, n) if ( a[i].sum1 + a[i].sum2 >= Max ) ++ ans;
        printf("%d\n", ans);
    }
}

int main()
{
    freopen("fake.in", "r", stdin);
    freopen("fake.out", "w", stdout);
    scanf("%d%d%d", &n, &A, &B);
    REP(i, 1, n) { getchar(); REP(j, 1, n) { char c = getchar(); if ( c == '1' ) add(i, j); } }
    REP(i, 1, n) 
    { 
        scanf("%d %s", &a[i].x, s); 
        sum += a[i].x;
        REP(j, 0, a[i].x - 1) 
        {
            if ( s[j] == '1' ) { a[i].Map[j] = 2; ++ num; } 
        }
    }
    Subtask1 :: Solve();
    return 0;
}
