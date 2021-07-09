/***************************************************************
	File name: K.cpp
	Author: ljfcnyali
	Create time: 2019年05月07日 星期二 12时19分12秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( long long i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

const int maxn = 1000010;

long long a[maxn], n, sum, ans;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%lld", &n);
	REP(i, 1, n) { scanf("%lld", &a[i]); sum += a[i]; }
	sum /= n;
	REP(i, 1, n) a[i] = a[i - 1] + a[i] - sum;
	sort ( a + 1, a + n + 1 );
	sum = a[n / 2 + 1];
	REP(i, 1, n) ans += abs(a[i] - sum);
	printf("%lld\n", ans);
    return 0;
}

/*
x1 x2 x3 .. xn sum
a1-x1+x2=sum x2=x1+sum-a1=|x1-(a1-sum)|	
a2-x2+x3=sum x3=x2+sum-a2=|x2-(a2-sum)|=|x1-a1+sum-a2+sum|=|x1-(a1+a2-2sum)|

an-xn+x1=sum xn=an+x1-sum=|x1-(sum-an)|

x1+x2+x3...
*/
