/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年11月26日 星期四 15时31分54秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

bool vis[maxn];

int main()
{
    freopen("stone.in", "w", stdout);
    int n = 10; printf("%d\n", n); srand(time(0));
    REP(i ,2, n) printf("%d ", rand() % (i - 1) + 1); puts("");
    printf("%d\n", 3);
    REP(i, 1, 3)
    {
        int m = 3; printf("%d ", m);
        REP(j, 1, m) 
        {
            int x = rand() % n + 1;
            while ( vis[x] ) x = rand() % n + 1;
            vis[x] = true; printf("%d " ,x);
        }
        puts("");
        mem(vis);
    }
    return 0;
}
