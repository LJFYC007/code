#include"testlib.h"
#include<bits/stdc++.h>
#define Space inf.readSpace()
#define Eoln inf.readEoln()
using namespace std;
const double eps = 1e-9;
int main(int argc, char **argv){
	registerLemonChecker(argc, argv);
	double your = ouf.readDouble();
	double answ = ans.readDouble();
	if (fabs(your - answ) < eps * max(1.0, answ)) {
		quitf(_ok, "accepted");
	} else {
		quitf(_wa, "wrong answer");
	}
}
