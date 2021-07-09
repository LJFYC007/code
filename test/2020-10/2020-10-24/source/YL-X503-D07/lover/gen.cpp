/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年10月24日 星期六 10时03分34秒
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
    freopen("lover.in", "w", stdout);
    srand(time(0));
    int n = rand() % 1000 + 1, m = rand() % n + 1;
    printf("%d %d\n", n, m);
    return 0;
}
