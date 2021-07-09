/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月29日 星期一 16时21分01秒
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
    freopen("musician.in", "w", stdout);
	int n = 1000000; printf("%d\n", n);
	REP(i, 1, n) printf("%d ", rand() % 998244353); puts("");
    return 0;
}
