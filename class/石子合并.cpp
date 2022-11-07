#include<bits/stdc++.h>

using namespace std;

int n, f[210][210], g[210][210], a[210];

int main()
{
    scanf("%d", &n);
    for ( int i = 1; i <= n; ++ i ) { scanf("%d", &a[i]); a[n + i] = a[i]; }
    // f[i][i] = 0;
    for ( int len = 2; len <= n + n; ++ len ) 
        for ( int l = 1; l + len - 1 <= n + n; ++ l )
        {
            int r = l + len - 1;
            f[l][r] = 2147483647;
            for ( int k = l; k < r; ++ k ) 
            {
                f[l][r] = min(f[l][r], f[l][k] + f[k + 1][r]);
                g[l][r] = max(g[l][r], g[l][k] + g[k + 1][r]);
            }
            int sum = 0; for ( int k = l; k <= r; ++ k ) sum += a[k];
            f[l][r] += sum; g[l][r] += sum;
        }
    int ansMin = 2147483647, ansMax = 0;
    for ( int i = 1; i <= n; ++ i ) ansMin = min(ansMin, f[i][i + n - 1]);
    for ( int i = 1; i <= n; ++ i ) ansMax = max(ansMax, g[i][i + n - 1]);
    printf("%d\n", ansMin);
    printf("%d\n", ansMax);
    return 0;
}