/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2021年03月02日 星期二 15时43分02秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 2010;

int main()
{
    freopen("input.txt", "w", stdout);
	srand(time(0));
	int n = 300; REP(i ,1, n) printf("%c", rand()% 26 + 'A'); puts("");
	printf("4\n");

    return 0;
}
