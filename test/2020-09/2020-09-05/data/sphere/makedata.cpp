#include <cstdio>
#include <iostream>
#include <windows.h>
using namespace std;
char In[50],Out[50];
char op[50];
int main() {
	int id,L,R; scanf("%d%d%d",&id,&L,&R);
	for(int i=L;i<=R;++i) {
		sprintf(In,"%d_%d.in",id,i);
		sprintf(Out,"%d_%d.ans",id,i);
		sprintf(op,"rand.exe > %s",In);
		system(op);
		sprintf(op,"std.exe < %s > %s",In,Out);
		system(op);
		Sleep(1000);
	}
	return 0;
}

