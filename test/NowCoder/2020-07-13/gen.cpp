/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月13日 星期一 16时06分54秒
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
    freopen("input.txt", "w", stdout);
    srand(time(0));
    int n = 200000; printf("%d\n", n);
    REP(i, 2, n) printf("%d %d\n", i, rand() % (i - 1) + 1);
    return 0;
}