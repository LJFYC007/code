/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年09月02日 星期三 19时15分21秒
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
    freopen("sequence.in", "w", stdout);
    srand(time(0));
    int n = 1000000; printf("%d\n", n);
    REP(i, 1, n) printf("%d ", rand() % 100000000 + 1); puts("");
    return 0;
}