/***************************************************************
	File name: T96070.cpp
	Author: ljfcnyali
	Create time: 2019年09月08日 星期日 08时17分31秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

unsigned long long n;

int main()
{
#ifndef ONLINE_JUDGE
    freopen("input.txt", "r", stdin);
    freopen("output.txt", "w", stdout);
#endif
    cin >> n;
    cout << n / 2 + 1 << endl;
    return 0;
}
