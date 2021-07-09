/***************************************************************
	File name: fast.cpp
	Author: ljfcnyali
	Create time: 2019年09月24日 星期二 19时09分07秒
***************************************************************/
#include<bits/stdc++.h>

using namespace std;

#define REP(i, a, b) for ( int i = (a), _end_ = (b); i <= _end_; ++ i ) 
#define mem(a) memset ( (a), 0, sizeof ( a ) ) 
#define str(a) strlen ( a ) 
typedef long long LL;

int main()
{
    freopen("chem.in", "r", stdin);
    freopen("chem.out", "w", stdout);
    REP(i, 2, 9)
    {
        int a; cin >> a;
        string x; cin >> x;
        cout << "Name_Substituent_C[" << i << "] = \"" << x << "\"; " ;
    }
    return 0;
}
