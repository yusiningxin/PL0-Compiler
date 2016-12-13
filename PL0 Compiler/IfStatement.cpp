# include "header.h"
# include "VarDef.h"
void IfStatement()
{
    int code1, code2;
    getsym();
    Condition(); // ����<����>
    if(sym == thensym)   // then
    {
        getsym();
        code1 = codeNum;
        gen(JPC, 0, 0); //������ת
        State(); // ����<���>
        if(sym == elsesym)   // else
        {
            getsym();
            code2 = codeNum;
            gen(JMP, 0, 0);
            Pcode[code1].a = codeNum;
            State(); // ����<���>
            Pcode[code2].a = codeNum;
        }
        else Pcode[code1].a = codeNum;
    }
    else   error(38);// if�����ȱ��then

}
// <����> ::= <���ʽ>(<|<=|>|>=|=|<>)<���ʽ>
void Condition()
{
    symbol op;
    Expression(); // ����<���ʽ>
    if((sym == lss) || (sym == leq) || (sym == gtr) || (sym == geq) || (sym == eql) || (sym == neq))   // <|<=|>|>=|=|<>
    {
        op = sym;
        getsym();
        Expression(); // ����<���ʽ>
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
    else    error(39);// ��������в��ǹ�ϵ�����
}

