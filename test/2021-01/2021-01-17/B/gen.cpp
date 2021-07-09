/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年01月17日 星期日 10时27分22秒
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
    // int n = 4, s = rand() % n + 1;
    int n = 40, s = rand() % n + 1;
    printf("%d %d\n", n, s);
    REP(i, 1, n) printf("%d ", rand() % 100 + 1); puts("");
    REP(i, 2, n) printf("%d %d\n", i, rand() % (i - 1) + 1);
    return 0;
}
