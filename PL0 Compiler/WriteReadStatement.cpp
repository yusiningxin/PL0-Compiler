# include "header.h"
# include "VarDef.h"
extern symbol expreType;
//< 写语句>  ::=   write '(' <字符串>,<表达式>')'|write '(' <字符串>')'|write'('<表达式>')'
void WriteStatement()
{
    int i;
    getsym();
    if(sym == lparen)   // (
    {
        getsym();
        if(sym == strnumber)   // <字符串>
        {
            for(i = id.size()-1; i >= 0; i--)
                gen(LIT, -1, id[i]);
            for(i = 0; i < id.size(); i++)
                gen(WRT, 0, 2);
            getsym();
            if(sym == comma)   // ,
            {
                getsym();
                expreType=charnumber;
                Expression(); // 调用<表达式>
                switch(expreType)
                {
                case inumber:
                    gen(WRT, 0, 0);
                    break;
                case rnumber:
                    gen(WRT, 0, 1);
                    break;
                case charnumber:
                    gen(WRT, 0, 2);
                    break;
                default:
                    gen(WRT, 0, 1);
                }
            }
        }
        else
        {
            expreType=charnumber;
            Expression(); // 调用<表达式>

            switch(expreType)
            {
            case inumber:
                gen(WRT, 0, 0);
                break;
            case rnumber:
                gen(WRT, 0, 1);
                break;
            case charnumber:
                gen(WRT, 0, 2);
                break;
            default:
                gen(WRT, 0, 1);
            }
        }
        if(sym == rparen)   gen(WRT,0,3),getsym(); // )
        else  error(58); // 缺少)
    }
    else   error(57);// 不是(

}

//< 读语句>  ::=  read'('<标识符>{,<标识符>}')'
void ReadStatement()
{
    int i;
    getsym();
    if(sym == lparen)   // (
    {
        do
        {
            getsym();
            if(sym == ident)   // <标识符>
            {
                iden=id;
                i = FindPosition();
                if(i == 0) error(32);
                else
                {
                    if(symTable[i].kind==varsym) //假定若出现传地址参数则为错误
                    {
                        switch(symTable[i].type)
                        {
                            case inumber:
                                gen(RED, 0, 0);
                                break;
                            case rnumber:
                                gen(RED, 0, 1);
                                break;
                            case charnumber:
                                gen(RED, 0, 2);
                                break;
                            default: ;
                        }
                    }
                    else error(45); //读语句输入不合法
                    gen(STO,level-symTable[i].level,symTable[i].address);
                }
                getsym();
            }
            else  error(44); // 读语句处缺少标识符
        }
        while(sym == comma);  // ,
        if(sym == rparen)   getsym(); // )
        else  error(60); // 不是)
    }
    else   error(59); // 缺少(
}
