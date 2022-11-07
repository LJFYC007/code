#include<cstdio>
#include<cstdlib>
#include<iostream>
#include<cstring>

using namespace std;

int n, f[2010][2010];
char s[2010];

signed main()
{
    while ( scanf("%s", s + 1) )
    {
        if ( s[1] == 'e' ) return 0;
        n = strlen(s + 1);
        for ( int len = 1; len <= n; ++ len ) 
            for ( int l = 1; l + len - 1 <= n; ++ l ) 
            {
                int r = l + len - 1;
                f[l][r] = max(f[l + 1][r], f[l][r - 1]);
                for ( int k = l; k < r; ++ k ) 
                    f[l][r] = max(f[l][r], f[l][k] + f[k + 1][r]);
                if ( (s[l] == '(' && s[r] == ')') || (s[l] == '[' && s[r] == ']') )
                    f[l][r] = max(f[l][r], f[l + 1][r - 1] + 2);
            }
        printf("%d\n", f[1][n]);
    }
    return 0;
}