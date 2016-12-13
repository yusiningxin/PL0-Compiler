# include "header.h"
# include "VarDef.h"
void IfStatement()
{
    int code1, code2;
    getsym();
    Condition(); // 调用<条件>
    if(sym == thensym)   // then
    {
        getsym();
        code1 = codeNum;
        gen(JPC, 0, 0); //非真跳转
        State(); // 调用<语句>
        if(sym == elsesym)   // else
        {
            getsym();
            code2 = codeNum;
            gen(JMP, 0, 0);
            Pcode[code1].a = codeNum;
            State(); // 调用<语句>
            Pcode[code2].a = codeNum;
        }
        else Pcode[code1].a = codeNum;
    }
    else   error(38);// if语句中缺少then

}
// <条件> ::= <表达式>(<|<=|>|>=|=|<>)<表达式>
void Condition()
{
    symbol op;
    Expression(); // 调用<表达式>
    if((sym == lss) || (sym == leq) || (sym == gtr) || (sym == geq) || (sym == eql) || (sym == neq))   // <|<=|>|>=|=|<>
    {
        op = sym;
        getsym();
        Expression(); // 调用<表达式>
        switch(op)
        {
            case eql:
                gen(OPR, 0, 6);
                break;
            case neq:
                gen(OPR, 0, 7);
                break;
            case gtr:
                gen(OPR, 0, 8);
                break;
            case leq:
                gen(OPR, 0, 9);
                break;
            case lss:
                gen(OPR, 0, 10);
                break;
            case geq:
                gen(OPR, 0, 11);
                break;
            default: ;
        }
    }
    else    error(39);// 条件语句中不是关系运算符
}

