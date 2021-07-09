/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年10月15日 星期四 10时43分50秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

bool vis[9][9];

int main()
{
    freopen("travel.in", "w", stdout);
    srand(time(0));
    int n = 4, m = 4, q = 0; printf("%d %d %d\n", n, m, q);
    REP(i, 1, m)
    {
        int u = rand() % n + 1, v = rand() % n + 1;
        while ( u == v || vis[u][v] ) { u = rand() % n + 1; v = rand() % n + 1; }
        vis[u][v] = vis[v][u] = true;
        printf("%d %d %d\n", u, v, rand() % 10);
    }
    return 0;
}
