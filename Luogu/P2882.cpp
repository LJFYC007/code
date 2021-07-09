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

const int maxn = 50010;

int a[maxn], n, f[maxn];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    scanf("%d", &n);
    REP(i, 1, n) 
    {
        char c;
        cin >> c;
        a[i] = c == 'B' ? 0 : 1;
    }
    int ans1 = 2147483647, ans2;
    REP(k, 1, n)
    {
        int t = 0, sum = 0;
        mem(f);
        bool flag = false;
        REP(i, 1, n)
        {
            t ^= f[i];
            if ( (t ^ a[i]) == 0 ) 
            {
                if ( i + k - 1 > n ) { flag = true; break ; }
                f[i + k] ^= 1;
                t ^= 1;
                ++ sum;
            }
        }
        if ( flag == false ) 
        { 
            if ( sum < ans1 ) 
            {
                ans1 = sum;
                ans2 = k;
            }
        }
    }
    printf("%d %d\n", ans2, ans1);
    return 0;
}
