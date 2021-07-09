#include "explore.h"
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 200010;

bool vis[maxn], use[maxn];

void Solve1(int n, int m)
{
    REP(i, 0, n - 2)
    {
        modify(i);
        REP(j, i + 1, n - 1)
        {
            int x = query(j);
            if ( x != use[j] ) { use[j] = x; report(i, j); }
        }
    }
}

void explore(int n, int m)
{
    if ( n <= 500 ) Solve1(n, m);
}
