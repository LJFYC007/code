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
	freopen("output.txt", "r", stdin);
    REP(i, 1, 1000) scanf("%d", &a[i]);
	freopen("output1.txt", "r", stdin);
    REP(i, 1, 1000) { int x; scanf("%d", &x); if ( x != a[i] ) cerr << i << endl; } 
    return 0;
}