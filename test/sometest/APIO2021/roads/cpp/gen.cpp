/***************************************************************
	File name: HaHa
	Author: ljfcnyali
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int a[maxn];

int main()
{
	freopen("input.txt", "w", stdout);
	srand(time(0));
	int n = 1000; printf("%d\n", n);
	REP(i, 2, n) printf("%d %d %d\n", i - 1, rand() % (i - 1), rand() % 100); 
    return 0;
}
