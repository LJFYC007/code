#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i )
#define mem(a) memset ( (a), 0, sizeof ( a ) )
#define str(a) strlen ( a )
typedef long long LL;
template<class T> int maxx(T a, T b) { return a > b ? a : b; }
template<class T> int minn(T a, T b) { return a < b ? a : b; }
template<class T> int abss(T a) { return a > 0 ? a : -a; }
#define max maxx
#define min minn
#define abs abss

int a, b;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    int T; scanf("%d", &T);
    while ( T -- ) 
    {
        scanf("%d%d", &a, &b);
        if ( a < b ) swap(a, b);
        if ( a >= 2 * b ) { printf("Stan wins\n"); continue ; }
        int ans = 1;
        while ( a / b == 1 && a % b != 0 ) 
        {
            a %= b; if ( a < b ) swap(a, b);
            ans = 0 - ans;
        }
        if ( ans == 1 ) printf("Stan wins\n");
        else printf("Ollie wins\n");
    }
    return 0;
}
