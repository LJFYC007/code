#include <cstdio>
#include <iostream>
#include <windows.h>
using namespace std;
char In[50],Out[50];
char op[50];
int main() {
	int L,R; scanf("%d%d",&L,&R);
	for(int i=L;i<=R;++i) {
		sprintf(In,"%d.in",i);
		sprintf(Out,"%d.ans",i);
		sprintf(op,"rand.exe > %s",In);
		system(op);
		sprintf(op,"std.exe < %s > %s",In,Out);
		system(op);
		Sleep(1000);
	}
	return 0;
}

