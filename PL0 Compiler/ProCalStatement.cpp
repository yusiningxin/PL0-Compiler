# include "header.h"
# include "VarDef.h"
void ProceCalStatement()
{
    int i;
    i = FindPosition();
    getsym();
    if(sym == lparen)   // (
    {
        getsym();
        ActualParaList(i); // ����<ʵ�ڲ�����>
        if(sym == rparen)  getsym();  // )
        else   error(53); // ȱ��)
        gen(CAL, level-symTable[i].level, symTable[i].value);
        gen(INT, 0, symTable[i].value+4); // ��������ռ䣬�����������ϱ�Ҫ�洢�ռ�
        gen(JMP, 0, symTable[i].address); // ��ת���ù�����ʼ���봦
    }
    else  error(52); // ȱ��(
}
