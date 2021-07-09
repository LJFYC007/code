/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年01月12日 星期二 21时12分32秒
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
    freopen("ttds.in", "w", stdout);
    int n = 5; printf("%d %d %d\n", n, rand() % ((1 << n) - 1) + 1, rand() % 10 + 1);
    REP(i, 1, n) printf("%d " ,rand() % 5 + 1); puts("");
    return 0;
}
