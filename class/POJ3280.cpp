#include<cstdio>
#include<cstdlib>
#include<iostream>

using namespace std;

int n, m, f[2010][2010], a[26], b[26];
char s[2010], t[10];

signed main()
{
    scanf("%d%d", &n, &m);
    scanf("%s", s + 1);
    for ( int i = 1; i <= n; ++ i )
    {
        scanf("%s", t + 1);
        int x = t[1] - 'a';
        scanf("%d%d", &a[x], &b[x]);
    }
    for ( int len = 2; len <= m; ++ len ) 
        for ( int l = 1; l + len - 1 <= m; ++ l ) 
        {
            int r = l + len - 1;
            f[l][r] = 2147483647;
            f[l][r] = min(f[l][r], f[l + 1][r] + min(a[s[l] - 'a'], b[s[l] - 'a']));
            f[l][r] = min(f[l][r], f[l][r - 1] + min(a[s[r] - 'a'], b[s[r] - 'a']));
            if ( s[l] == s[r] ) f[l][r] = min(f[l][r], f[l + 1][r - 1]);
        }
    printf("%d\n", f[1][m]);
    return 0;
}