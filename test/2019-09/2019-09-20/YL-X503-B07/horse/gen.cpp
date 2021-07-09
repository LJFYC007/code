/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年09月20日 星期五 21时15分35秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int main()
{
    freopen("horse.in", "w", stdout);
    int n = 100000; cout << n << endl;
    srand(time(0));
    REP(i ,1, n) printf("%d ", rand()); puts("");
    REP(i, 2, n) printf("%d %d %d\n", i, (rand() % (i - 1)) + 1, rand());
    return 0;
}
