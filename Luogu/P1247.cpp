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

const int maxn = 500010;

int a[maxn], n, p;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) { scanf("%d", &a[i]); p ^= a[i]; }
    if ( p <= 0 ) printf("lose\n");
    else 
    {
        REP(i, 1, n) if ( (p ^ a[i]) < a[i] ) 
        {
            printf("%d %d\n", a[i] - (p ^ a[i]), i);
            a[i] ^= p;
            REP(j, 1, n) printf("%d ", a[j]);
            puts("");
            return 0;
        }
    }
    return 0;
}
