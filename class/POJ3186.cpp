#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;

#define int long long

int n, f[2010][2010], a[2010];

signed main()
{
    scanf("%lld", &n);
    for ( int i = 1; i <= n; ++ i ) scanf("%lld", &a[i]);
    for ( int len = 1; len <= n; ++ len ) 
        for ( int l = 1; l + len - 1 <= n; ++ l ) 
        {
            int r = l + len - 1;
            f[l][r] = max(f[l + 1][r] + a[l] * (n - r + l), f[l][r - 1] + a[r] * (n - r + l));
        }
    printf("%lld\n", f[1][n]);
    return 0;
}