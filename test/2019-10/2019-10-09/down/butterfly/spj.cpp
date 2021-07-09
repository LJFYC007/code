#include <iostream>
#include <cmath>
#include <cstdio>
#include <algorithm>
#define fo(i,a,b) for(int i=a;i<=b;i++)
using namespace std;

const int N=5e3+5;

char a[N][N];

int main(int argc,char *argv[]){
        FILE *f_stdin=fopen(argv[1],"r");//标准输入
        FILE *f_out=fopen(argv[2],"r");//选手输出
        FILE *f_stdout=fopen(argv[3],"r");//标准输出
        FILE *f_score=fopen(argv[5],"w");//分数输出
        FILE *f_wrong=fopen(argv[6],"w");//错误信息

        int n,m,ans,tmp;
        bool pd=1;
        fscanf(f_stdin,"%d%d",&n,&m);
        fo(i,1,n) fscanf(f_out,"%s",a[i]+1);
        fscanf(f_stdout,"%d",&ans);
        tmp=0;
        fo(i,1,n) {
                int s=0;bool ok=1;
                fo(j,1,m) {
                        s+=a[i][j]=='('?1:-1;
                        if (s<0) {ok=0;break;}
                }
                ok&=s==0;
                tmp+=ok;
        }
        fo(j,1,m) {
                int s=0;bool ok=1;
                fo(i,1,n) {
                        s+=a[i][j]=='('?1:-1;
                        if (s<0) {ok=0;break;}
                }
                ok&=s==0;
                tmp+=ok;
        }
        int score=atoi(argv[4]);
        if (tmp==ans) {
                fprintf(f_score,"%d\n",score);
                fprintf(f_wrong,"Correct Answer");
                return 0;
        }
        fprintf(f_score,"0");
        fprintf(f_wrong,"Wrong Answer");
        fprintf(f_wrong,"Your Answer is %d,Correct Answer is %d\n",tmp,ans);
        return 0;
}
