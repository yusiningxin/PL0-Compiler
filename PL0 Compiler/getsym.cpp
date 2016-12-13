# include "header.h"
# include "VarDef.h"
int lexNum=0;
char ch='\n';
void getch ()
{
   if(ch=='\n') printf("%d ",line);
   ch=fgetc(fsource);
   printf("%c",ch);
}
void getsym ()
{
    bool flag=true;
    while(ch==' '||ch=='\n'||ch=='\r'||ch=='\t')
    {
        if(ch=='\n') line++;
        getch();
    }
    if(isalpha(ch)) //如果是字母
    {
        id="";
        int k=0; //记录标识符长度
        while((isalnum(ch)||isalpha(ch)) )
        {
            k++;
            if(k<MAXWORD) id=id+ch; //标识符长度太长，从此处截断
            else if(flag) flag=false,error(1);
            getch();
        }
        int l=0,r=WORKNUM-1,mid;
        while(l<=r)
        {
            mid=(r+l)/2;
            if(id==work[mid]) break;
            if(id<work[mid]) r=mid-1;
            else l=mid+1;
        }
        if(l>r) sym=ident; //不是保留字，表明为标识符
        else sym=wsym[mid]; //是保留字，类型设为保留字的类型
    }
    else if(isalnum(ch)) //如果是数字
    {
        inum=0,id="";
        int k=0;
        while(isalnum(ch))
        {
            k++;
            if(k<MAXNUMBER) id=id+ch,inum=10*inum+ch-'0';
            else if(flag) flag=false,error(2);//数字位数超过精度限制
            getch();
        }
        if(ch=='.')
        {
            id=id+ch;
            getch();
            dnum=inum;
            if(isalnum(ch))
            {
                double tmp=0.1;
                while(isalnum(ch))
                {
                    k++;
                    if(k<MAXNUMBER) id=id+ch,dnum=dnum+tmp*(ch-'0');
                    else if(flag) flag=false,error(2);//数字位数超过精度限制
                    tmp=tmp*0.1;
                    getch();
                }
                sym=rnumber;
            }
            else error(49); //浮点数以 点 结尾
        }
        else sym=inumber;

    }
    else if(ch==':')
    {
        getch();
        if(ch=='=')
        {
            sym=becomes;
            id=":=";
            getch();
        }
        else id=":",sym=colon;
    }
    else if(ch=='<')
    {
        getch();
        if(ch=='=')
        {
            sym=leq;
            id="<=";
            getch();
        }
        else if(ch=='>')
        {
            id="<>";
            sym=neq;
            getch();
        }
        else id="<",sym=lss;
    }
    else if(ch=='>')
    {
        getch();
        if(ch=='=')
        {
            id=">=";
            sym=geq;
            getch();
        }
        else id=">",sym=gtr;
    }
    else if(ch=='\'') //单引号，两个单引号中间应为单个字符
    {
        getch();
        if(isalnum(ch)||isalpha(ch))
        {
            id=ch;
            getch();
            if(ch=='\'')
            {
                getch();
                sym=charnumber;
            }
            else error(4); //两个单引号中间不是单个字符
        }
        else error(5); //单引号后面加不合法字符
    }
    else if(ch=='\"') //双引号
    {
        getch();
        id="";
        int k=0;
        while((ch == 32) || (ch == 33) || ((ch >= 35) && (ch <= 126)))
        {
            k++;
            if(k>MAXSTR&&flag) flag=false,error(3); //字符串超过最大长度限制
            else id=id+ch;
            getch();
        }
        sym=strnumber;
        if(ch=='\"')  getch();
        else error(6); //没有后双引号
    }
    else if(ch==-1)
    {
        sym=endfile;
        fclose(fsource);
    }
    else id=ch,sym=ssym[ch],getch();
    fprintf(flex,"%d %15s %10s\n", ++lexNum,trans[sym],id.c_str());
    //printf("%d %15s %10s\n", lexNum,trans[sym],id.c_str());
}
