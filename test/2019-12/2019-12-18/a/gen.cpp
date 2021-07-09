/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年12月18日 星期三 11时20分52秒
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
    freopen("a.in", "w", stdout);
    srand(time(0));
    int n = 10; printf("%d\n", n);
    REP(i, 1, n) printf("%d ", rand() % 10 + 1); puts("");
    printf("1\n");
    printf("Q 1\n");
    return 0;
}
