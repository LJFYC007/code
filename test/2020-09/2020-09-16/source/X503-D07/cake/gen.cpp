/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2020年09月16日 星期三 19时28分39秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

const int maxn = 1e5 + 10;

int a[maxn], b[maxn];

int main()
{
    freopen("cake.in", "w", stdout);
    srand(time(0));
    int n = 5000; printf("%d\n", n);
    REP(i, 1, n) a[i] = b[i] = i; 
    random_shuffle(a + 1, a + n + 1); 
    random_shuffle(b + 1, b + n + 1); 
    REP(i, 1, n) printf("%d %d\n", a[i], b[i]);
    return 0;
}
