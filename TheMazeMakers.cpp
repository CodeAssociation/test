#include<iostream>
#include<string.h>
#include<stdio.h>
#include<queue>
using namespace std;

const int N = 55;
char s[N];
int H,W,sh[5],sl[5],cnt,vis[N][N],vist,flag,loop;
int dir[4][2]= {0,-1,1,0,0,1,-1,0},go[N][N][4];

struct node
{
    int h,l,step;
    node(int a,int b,int c){h = a ,l = b,step = c;}
};
void maze()
{
    queue<node>q;
    vist = 1,flag = loop = 0;
    node s(sh[0],sl[0],1);
    vis[sh[0]][sl[0]] = 1;
    q.push(s);
    while(!q.empty())
    {
        s = q.front();
        q.pop();
        if(s.h==sh[1]&&s.l==sl[1])
            flag = 1;
        for(int i=0;i<4;i++)
        {
            int hh = s.h + dir[i][0];
            int ll = s.l + dir[i][1];
            if(hh<0||hh>=H||ll<0||ll>=W||go[s.h][s.l][i])
                continue;
            if(vis[hh][ll])
            {
                if(vis[hh][ll]==s.step+1)
                    loop = 1;
                continue;
            }
            vist++;
            vis[hh][ll] = s.step + 1;
            q.push(node(hh,ll,s.step + 1));
        }
    }
}
int main()
{
    while(scanf("%d%d",&H,&W)&&H+W)
    {
        memset(vis,0,sizeof vis);
        memset(go,0,sizeof go);
        cnt = 0;
        for(int i=0; i<H; i++)
        {
            scanf("%s",s);
            for(int j=0; j<W; j++)
            {
                int a,num;
                if(s[j]>='0'&&s[j]<='9')
                    num = s[j] - '0';
                else
                    num = 10 + s[j] - 'A';
                for(int k=0; k<4; k++)
                {
                    a = num % 2;
                    num/=2;
                    int hh = i*2+1+dir[k][0];
                    int ll = j*2+1+dir[k][1];
                    go[i][j][k] = a;
                    if(a==0&&(hh==0||hh==2*H||ll==0||ll==2*W))
                    {
                        sh[cnt] = i;
                        sl[cnt++] = j;
                    }
                }
            }
        }
        maze();
        if(!flag)
            printf("NO SOLUTION\n");
        else if(W*H>vist)
            printf("UNREACHABLE CELL\n");
        else if(loop)
            printf("MULTIPLE PATHS\n");
        else
            printf("MAZE OK\n");
    }
    return 0;
}
