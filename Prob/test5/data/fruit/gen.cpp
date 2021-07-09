/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年10月25日 星期五 11时25分22秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int main(int argc, char* argv[])
{
    REP(i, 1, 1000000000) ;
    srand(time(0));
    int n = atoi(argv[1]), m = rand() % n + 1;
    printf("%d %d\n", n, m);
    REP(i, 1, n) printf("%d\n", rand() % 10 + 1);
    return 0;
}
