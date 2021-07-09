// luogu-judger-enable-o2
/***************************************************************
    File name: P2729.cpp
    Author: ljfcnyali
    Create time: 2019年05月07日 星期二 14时47分24秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

int a[5][4];
int ans = 0x3f3f3f3f, X, Y, Z, sum;

inline bool pd(int A, int B, int C)
{
	if ( a[1][1] == 0 )
	{
		if ( a[1][2] != 0)
		{
			if ( a[1][3] != 0 )
			{
				if ( B % a[1][2] != 0 || C % a[1][3] != 0 || B / a[1][2] != C / a[1][3] ) return false;
				return true;
			}
			if ( B % a[1][2] == 0 ) return true;
			return false;
		}
		if ( C % a[1][3] == 0 ) return true;
		return false;
	}
	if ( a[1][2] == 0 )
	{
		if ( a[1][3] != 0 )
		{
			if ( A % a[1][1] != 0 || C % a[1][3] != 0 || A / a[1][1] != C / a[1][3] ) return false;
			return true;
		}
		if ( A % a[1][1] == 0 ) return true;
		return false;
	}
	if ( a[1][3] == 0 )
	{
		if ( A % a[1][1] != 0 || B % a[1][2] != 0 || A / a[1][1] != B / a[1][2] ) return false;
		return true;
	}

	if ( A % a[1][1] == 0 && B % a[1][2] == 0 && C % a[1][3] == 0 )
    {
    	if ( A / a[1][1] != B / a[1][2] || B / a[1][2] != C / a[1][3] ) return false; 
		//puts("");
		return true;
	}
	return false;
}

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    REP(i, 1, 4) REP(j, 1, 3) scanf("%d", &a[i][j]);
    REP(x, 0, 100)
        REP(y, 0, 100)
            REP(z, 0, 100)
            {
                int A = a[2][1] * x, B = a[2][2] * x, C = a[2][3] * x; 
                A += a[3][1] * y, B += a[3][2] * y, C += a[3][3] * y; 
                A += a[4][1] * z, B += a[4][2] * z, C += a[4][3] * z; 
				if ( a[1][1] == 0 && A != 0 ) continue ;
				if ( a[1][1] != 0 && A == 0 ) continue ;
				if ( a[1][2] == 0 && B != 0 ) continue ;
				if ( a[1][2] != 0 && B == 0 ) continue ;
				if ( a[1][3] == 0 && C != 0 ) continue ;
				if ( a[1][3] != 0 && C == 0 ) continue ;
                if ( pd(A, B, C) )
                {
//				    printf("%d %d %d\n", x, y, z);
                    if ( x + y + z > ans ) continue ;
                    X = x; Y = y; Z = z;
                    ans = X + Y + Z;
                    sum = A / a[1][1];
                }
            }
    if ( ans == 0x3f3f3f3f ) printf("NONE\n");
    else printf("%d %d %d %d\n", X, Y, Z, sum);
    return 0;
}
