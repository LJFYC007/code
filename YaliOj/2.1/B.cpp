/***************************************************************
	File name: B.cpp
	Author: ljfcnyali
	Create time: 2019年05月10日 星期五 16时07分27秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 

map<string, bool> Map;
int n;
string a;
char c[10];

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
	scanf("%d", &n);
	getchar();
	REP(i, 1, n)
	{
		scanf("%s", c);
		getline(cin, a);
		if ( c[0] == 'a' ) 
		{
			Map[a] = true;
		}
		else
		{
			if ( Map.count(a) == 1 ) printf("yes\n");
			else printf("no\n");
		}
	}
    return 0;
}
