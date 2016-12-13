# include "header.h"
# include "VarDef.h"
// <当循环语句> ::= while<条件>do<语句>
//< repeat循环语句>  ::=  repeat <语句>until<条件>
void RepeatStatement()
{
    int code1;
    code1=codeNum;
    getsym();
    State();
    if(sym==untilsym)
    {
        getsym();
        Condition();
        gen(JPC,0,code1);
    }
    else error(40); //repeat语句中缺少until

}

//< for循环语句>  ::=  for <标识符> := <表达式> (to|downto) <表达式> do <语句>
void ForStatement ()
{
    int i;
    int code1, code2;
    bool down = false;
    getsym();
    if(sym == ident)   // <标识符>
    {
        iden=id;
        i = FindPosition();
        if(i == 0)  error(32);
        if(symTable[i].kind != varsym) //此处有问题！！！
        {
            error(56);
            i = 0;
        }
        getsym();
        if(sym == becomes)   // :=
        {
            getsym();
            Expression(); // 调用<表达式>
            if(i != 0) //分形参和实参！！！
                gen(STO, level-symTable[i].level, symTable[i].address);
            if(sym == tosym || sym==downtosym) // to downto
            {
                if(sym==tosym) down=false;
                else down=true;
                code1 = codeNum; // for循环开始位置
                gen(LOD, level-symTable[i].level, symTable[i].address);
                getsym();
                Expression(); // 调用<表达式>
                if(down) gen(OPR, 0, 11);
                else gen(OPR,0,9);
                code2 = codeNum; // do开始位置
                gen(JPC, 0, 0);
                if(sym == dosym)   // do
                {
                    getsym();
                    State(); // 调用<语句>
                    gen(LOD, level-symTable[i].level, symTable[i].address);
                    gen(LIT, -1, 1);
                    if(down) gen(OPR, 0, 3);
                    else gen(OPR, 0, 2);
                    gen(STO, level-symTable[i].level, symTable[i].address);
                    gen(JMP, 0, code1);
                    Pcode[code2].a = codeNum;
                }
                else  error(43); // for语句中缺少do
            }
            else   error(42);// for语句中缺少to downto
        }
        else    error(33);// for语句中不是:=
    }
    else   error(41);// for语句开头不是标识符

}

