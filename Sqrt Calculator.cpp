#include <bits/stdc++.h>
using namespace std;
int bit;

char* mulsgl(char *x,int time){
    char *p=(char*)malloc(sizeof(char)*(bit+10));
    memset(p,0,sizeof(char)*(bit+10));
    int now=0;
    int maxlen=strlen(x);
    while(now<maxlen){
        if(!p[now]) p[now]='0';
        if(p[now]-'0'+(x[now]-'0')*time>=10){
            p[now+1]=(p[now]-'0'+(x[now]-'0')*time)/10+'0';
            p[now]=(p[now]-'0'+(x[now]-'0')*time)%10+'0';
        }
        else p[now]=p[now]-'0'+(x[now]-'0')*time+'0';
        now++;
    }
    return p;
}

bool cmps(char *x,char *y){
    int lenx=strlen(x);
    int leny=strlen(y);
    if(lenx>leny) return 1;
    else if(lenx<leny) return 0;
    else{
        while(lenx){
            if(x[lenx-1]>y[lenx-1]) return 1;
            else if(x[lenx-1]<y[lenx-1]) return 0;
            lenx--;
        }
        return 0;
    }
}

char* minuss(char *x,char *y){                                    //x>y
    char *p=(char*)malloc(sizeof(char)*(bit+10));
    memset(p,0,sizeof(char)*(bit+10));
    if(strlen(x)==0) {strcpy(p,x);return p;}
    int now=0;
    int maxlen=strlen(x);
    while(now<maxlen){
        if(!p[now]) p[now]='0';
        if(!x[now]) x[now]='0';
        if(!y[now]) y[now]='0';
        if(x[now]+p[now]-48<y[now]){
            p[now+1]='0'-1;
            p[now]=10+x[now]+p[now]-y[now];
        }
        else p[now]+=x[now]-y[now];
        now++;
    }
    int tmp=maxlen;
    while(p[tmp-1]=='0') {p[tmp-1]=0;tmp--;}
    tmp=maxlen;
    while(y[tmp-1]=='0') {y[tmp-1]=0;tmp--;}
    return p;
}

int main(){
    long long num,fa,fsqrt;
    int now=0,times=0;              //first sqrt  first a
    printf("Sqrt:");
    scanf("%lld",&num);
    printf("How many decimal places round to:");
    scanf("%d",&bit);
    char *a=(char *)malloc(sizeof(char)*(bit+10));
    char *ans=(char *)malloc(sizeof(char)*(bit+10));
    memset(a,0,sizeof(char)*(bit+10));
    memset(ans,0,sizeof(char)*(bit+10));
    fsqrt=(long long)sqrt(num);
    fa=num-fsqrt*fsqrt;
    while(fsqrt){
        ans[now++]=fsqrt%10+'0';
        fsqrt/=10;
        times++;
    }
    now=0;
    while(fa){
        a[now++]=fa%10+'0';
        fa/=10;
    }
    string fin=to_string(bit)+"sqrt"+to_string(num)+".txt";
    const char *o=fin.data();
    FILE *fp=fopen(o,"w");
    char *p1=NULL,*p2=NULL;
    int i,j,k,lena,lenp1;
    clock_t start,end;
    start=clock();
    for(i=0;i<bit;i++){
        for(k=strlen(a)-1;k>=0;k--) a[k+2]=a[k];
        a[0]=a[1]='0';
        lena=strlen(a);
        p1=mulsgl(ans,2);
        for(k=strlen(p1)-1;k>=0;k--) p1[k+1]=p1[k];
        lenp1=strlen(p1);
        j=0;
        if(!(lena<lenp1))j=(int)((a[lena-1]-'0')*(1+9*(lena-lenp1))+(a[lena-2]-'0')*(lena-lenp1))/((p1[lenp1-1]-'0')+1);
        do{
            free(p2);
            j++;
            p1[0]=j+'0';
            p2=mulsgl(p1,j);
        }while(cmps(a,p2));
        free(p2);
        p1[0]--;
        p2=mulsgl(p1,j-1);
        free(p1);
        for(k=strlen(ans)-1;k>=0;k--) ans[k+1]=ans[k];
        ans[0]=j-1+'0';
        p1=a;
        a=minuss(a,p2);
        free(p1);
        if(i%1000==0&&i!=0) printf("%d\n",i);
    }
    end=clock();
    printf("Finish!\ntime=%.3fs\n",(double)(end-start)/CLK_TCK);
    cout<<"File "<<fin<<" has been generated.\n";
    for(i=strlen(ans)-1;i>(int)strlen(ans)-1-times;i--) fprintf(fp,"%c",ans[i]);
    if(i+1)fprintf(fp,".");
    for(i=(int)strlen(ans)-1-times;i>=0;i--) fprintf(fp,"%c",ans[i]);
    fclose(fp);
    system("pause");
    return 0;
}