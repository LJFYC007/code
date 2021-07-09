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

const int maxn = 100010;

int a[maxn];

int main(int argc, char* argv[])
{
    REP(i, 1, 1000000000) ;
    srand(time(0));
    int n = atoi(argv[1]);
    REP(i, 1, n) a[i] = rand() % 26;
    random_shuffle(a + 1, a + n + 1);
    REP(i, 1, n) printf("%c", a[i] + 'a'); puts("");
    return 0;
}

