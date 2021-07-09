/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年07月08日 星期三 11时20分45秒
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
    freopen("and.in", "w", stdout);
    srand(time(0));
    int n = 4, m = 5; printf("%d %d\n", n, m);
    REP(i, 1, 2)
        printf("0 %d 1 1 %d\n", rand() % n, rand() % 10 + 1);
    REP(i, 3, 5)
        printf("1 %d 1 1\n", rand() % n);
    return 0;
}
