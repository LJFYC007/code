/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年05月07日 星期四 14时16分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int main()
{
    freopen("tug.in", "w", stdout);
    srand(time(0));
    int n = 30000;
    printf("%d\n", n);
    REP(i, 1, n)
    {
        printf("%d %d %d\n", i, i, rand() % 15 + 1);
        printf("%d %d %d\n", i, i, rand() % 15 + 1);
    }
    return 0;
}
