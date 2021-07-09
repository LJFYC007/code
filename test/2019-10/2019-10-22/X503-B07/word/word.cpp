/***************************************************************
	File name: word.cpp
	Author: ljfcnyali
	Create time: 2019年10月22日 星期二 07时46分04秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 100010;

int n, sum1, sum2;
char s[maxn];

int main()
{
    freopen("word.in", "r", stdin);
    freopen("word.out", "w", stdout);
    scanf("%d", &n);
    scanf("%s", s + 1);
    REP(i, 1, n) if ( s[i] == 'z' ) ++ sum1;
    printf("%d %d\n", sum1, (n - sum1 * 4) / 3);
    return 0;
}
