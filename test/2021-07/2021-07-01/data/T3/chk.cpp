#include"testlib.h"
#include<bits/stdc++.h>
#define Space inf.readSpace()
#define Eoln inf.readEoln()
using namespace std;
const double eps = 1e-6;
int main(int argc, char **argv){
	registerTestlibCmd(argc, argv);
	int yourm = ouf.readInt();
	int ansm = ans.readInt();
	if (yourm != ansm) quitf(_wa, "wrong answer");
	int n = inf.readInt(); while (n--) inf.readInt();
	int q = inf.readInt();
	while (q--)
	{
		double your = ouf.readDouble();
		double answ = ans.readDouble();
		if (fabs(your - answ) > eps * max(1.0, answ)) {
			quitp(0.2, "partially correct");
		}
	}
	quitf(_ok, "accepted");
}
