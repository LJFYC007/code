#include<bits/stdc++.h>
using namespace std;
int main(){
	freopen("data5.in","w",stdout);
	srand(time(0));
	int n=rand()%100000+1,v=1000000;
	printf("%d\n",n);
	for(int i=1;i<=n;++i)
		printf("%d ",rand()%v+1);
	fflush(stdout);
	system("./std < data5.in >data5.ans");
	return 0;
}
