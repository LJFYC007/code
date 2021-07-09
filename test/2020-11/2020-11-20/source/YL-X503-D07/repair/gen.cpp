/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年11月20日 星期五 15时28分18秒
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
    freopen("repair.in", "w", stdout);
    int n = 18; printf("%d 101092\n", n); 
    srand(time(0));
    int x = rand() + 100;
    REP(i, 1, n) printf("%d ", rand() % 10 + x); puts("");
    return 0;
}
