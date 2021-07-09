/***************************************************************
	File name: P3864.cpp
	Author: ljfcnyali
	Create time: 2019年05月05日 星期日 15时34分53秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

char name[5010][15], s[15], a[15];
char dic[10][4], k[30];

int len, n = 4617;
bool flag = false;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
#endif
	scanf("%s", s);
	len = str(s);
	k[1] = k[2] = k[3] = '2'; k[4] = k[5] = k[6] = '3';
	k[7] = k[8] = k[9] = '4'; k[10] = k[11] = k[12] = '5';
	k[13] = k[14] = k[15] = '6'; k[16] = k[18] = k[19] = '7';
	k[20] = k[21] = k[22] = '8'; k[23] = k[24] = k[25] = '9';
	REP(i, 1, n) 
	{
		getchar();
		scanf("%s", name[i]);
		if ( str(name[i]) != len ) continue ;
		REP(j, 0, len - 1) a[j] = k[name[i][j] - 'A' + 1];
		if ( strcmp(a, s) == 0 ) 
		{
			printf("%s\n", name[i]);
			flag = true;
		}
	}
	if ( flag == false ) printf("NONE\n");
	return 0;
}
