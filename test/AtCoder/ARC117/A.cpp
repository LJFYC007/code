/***************************************************************
	File name: A.cpp
	Author: ljfcnyali
	Create time: 2021年04月18日 星期日 19时59分19秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;
const int N = 1e9;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	int n, m; scanf("%d%d", &n, &m);
	int sum1 = N, sum2 = N;	
	REP(i, 1, n - 1) { printf("%d ", i); sum1 -= i; } printf("%d ", sum1);
	REP(i, 1, m - 1) { printf("%d ", -i); sum2 -= i; } printf("%d ", -sum2);
	puts("");
    return 0;
}
