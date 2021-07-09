/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年10月25日 星期五 10时57分32秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int main()
{
    freopen("simulation.in", "w", stdout);
    srand(time(0));
    int n = 4, m = 5, k = 3;
    printf("%d %d %d\n", n, m, k);
    REP(i, 1, m) printf("%d %d %d\n", rand() % n + 1, rand() % n + 1, rand() % 10);
    printf("2 1 4\n");
    REP(i, 1, 2) printf("%d %d %d %d\n", 3, rand() % n + 1, rand() % n + 1, rand() % n + 1);
    return 0;
}
