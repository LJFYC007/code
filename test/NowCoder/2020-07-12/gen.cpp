/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月12日 星期日 13时15分36秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 110;

bool vis[maxn][maxn];

int main()
{
    freopen("input.txt", "w", stdout);
    srand(time(0));
    int cnt = 10;
    while ( cnt ) 
    {
        cnt -- ; 
        int n = 100000; printf("%d\n", n);
        REP(i, 1, n) printf("%c", rand() % 2 + 'a'); puts("");
    }
    return 0;
}
