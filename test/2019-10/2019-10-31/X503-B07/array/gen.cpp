/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年10月31日 星期四 11时24分05秒
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
    freopen("array.in", "w", stdout);
    srand(time(0));
    int n = 5, k = 6, a[1000010];
    printf("%d %d\n", n, k);
    REP(i, 1, n) a[i] = i;
    random_shuffle(a + 1, a + n + 1);
    REP(i, 1, n) printf("%d ", a[i]); puts("");
    random_shuffle(a + 1, a + n + 1);
    REP(i, 1, n) printf("%d ", a[i]); puts("");
    return 0;
}
