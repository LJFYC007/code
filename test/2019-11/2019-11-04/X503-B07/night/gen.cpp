/***************************************************************
	File name: gen.cpp
	Author: ljfcnyali
	Create time: 2019年11月04日 星期一 08时57分28秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
#define pii pair<int, int>
typedef long long LL;

int a[1200010];
int main()
{
    freopen("night.in", "w", stdout);
    int T = 5, n = 100000, m = 20;
    printf("%d\n", T);
    while ( T -- ) 
    {
        printf("%d %d\n", n, m);
        int t = (1 << m) - 1;
        for(int i=0;i<(1<<m);i++)
            a[i]=i;
        sort(a,a+(1<<m),[](int a,int b){return __builtin_popcount(a)<__builtin_popcount(b);});
        for(int i=0;i<n;i++)
            printf("%d\n",((1<<m)-1)^a[i]);
        printf("1\n1\n");
        int q = 100000;
        printf("%d\n", q);
        REP(i, 1, q) printf("0\n");
    }
    return 0;

} 
