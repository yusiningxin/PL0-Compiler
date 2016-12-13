# include "header.h"
# include "VarDef.h"
void CompStatement()
{
    if(sym == beginsym)   // begin
    {
        do
        {
            getsym();
            State(); // ����<���>
        }
        while(sym == semicolon);  // ;
        if(sym == endsym) getsym(); // end
        else   error(30); // �������δ��end��β
    }
    else  error(29); // �������δ��begin��ͷ
}

//< ���>   ::=  <��ֵ���>|<�������>|<repeatѭ�����>|<���̵������>|<�������>|
//              <�����>|<д���>|<forѭ�����>|<��>
void State ()
{
    int i;
    if(sym == ident)   // ��ʶ����ͷΪ���̵��������߸�ֵ���
    {
        iden=id;
        i = FindPosition();
        if(i == 0)
        {
            error(32); //��ʶ��δ����
            return;
        }
        if(symTable[i].kind == procsym) ProceCalStatement(); // ���̵������
        else AssignStatement(); // ��ֵ���
    }
    else if(sym == ifsym)   IfStatement(); // �������
    else if(sym == repeatsym)   RepeatStatement(); // repeatѭ��
    else if(sym == beginsym)  CompStatement(); // �������
    else if(sym == readsym)  ReadStatement(); // �����
    else if(sym == writesym)   WriteStatement(); // д���
    else if(sym == forsym)    ForStatement(); // forѭ�����
    else if(sym==endsym) return ;
    else  error(31); //���Ϸ����
}
