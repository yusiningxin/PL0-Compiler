# include "header.h"
# include "VarDef.h"
void gen (FCT x,int y,double z)
{
    if(codeNum>MAXCODE)
    {
        error(45);return ;
    }
    Pcode[codeNum].f = x;
	Pcode[codeNum].l = y;
	Pcode[codeNum].a = z;
	codeNum=codeNum+1;
}

void PCODELIST ()
{
    for(int i=0;i<codeNum;i++)
    {
        fprintf(fobjcode,"%d  %s  %d  %lf\n",i,fct[Pcode[i].f],Pcode[i].l,Pcode[i].a);
      //  cout<<i<<"  "<<fct[Pcode[i].f]<<"  "<<Pcode[i].l<<"  "<<Pcode[i].a<<endl;
    }
}
