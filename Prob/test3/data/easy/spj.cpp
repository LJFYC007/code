#include<fstream>
#include<math.h>
using namespace std;
ifstream f1,f2,f3;
//f1表示输入文件
//f2表示选手输出文件
//f3表示std输出文件
ofstream f5,f6;
//f5输出最终得分
//f6输出报告文件
int main(int argc,char *argv[]){
	f1.open(argv[1]);
	f2.open(argv[2]);
	f3.open(argv[3]);
	f5.open(argv[5]);
	f6.open(argv[6]);
	int score=atoi(argv[4]);
	double a,b;
	f2>>a;
	f3>>b;
	if(fabs(a/b-1)<1e-3||fabs(a-b)<1e-3)
		f5<<score<<endl;
	else
		f5<<0<<endl;
	//score表示当前测试点总分
	f1.close();
	f2.close();
	f3.close();
	f5.close();
	f6.close();
	return 0;
}
