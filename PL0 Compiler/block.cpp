# include "header.h"
# include "VarDef.h"
void block ()
{
    level++;
    varAddress[level] = 4; //�������ƫ�Ƶ�ַ��4��ʼ
    gen(INT,0,4); //����ջ�ռ����4��
    SubBlock(); // ����<�ֳ���>
    level--;
    if(sym == period)   // <����>��.����
    {
        getsym();
        if(sym == endfile)   // Դ���򵽴��β
        {
            printf("\nSyntax Analysis Complete.\n");
        }
        else   // ��β������������
        {
            error(47);
            printf("\nSyntax Analysis Complete.\n");
        }
    }
    else   // �����βӦΪ.
    {
        error(0);
    }
}

// <�ֳ���> ::= [<����˵������>][<����˵������>]{[<����˵������>]|[<����˵������>]}<�������>
void SubBlock ()
{
    tableStart[level] = symNum; // ��¼�����Ӧ���ű���ʼλ�ã���ʱ��������ʼλ�ã�����������β��б������塣
    tableStart[level] = FirstPosition(tableStart[level]);  // ��¼������ű�ʼλ�ã�ͬʱ���µ�ǰ����뿪ʼλ��
    gen(JMP, 0, 0); // �ɸ�������������ת���������ִ�в��֣���������ֻ�ǼǷ��ű�������Ŀ�����
    if(sym == constsym)
    {
        ConstDeclaration(); // ����˵������
    }
    if(sym == varsym)
    {
        VarDeclaration(); // ����˵������
    }
    while(true)
    {
        if(sym == procsym)
        {
            ProceDeclaration(); // ����˵������
        }
        else if(sym == funcsym)
        {
            FuncDeclaration(); //����˵������
        }
        else break;
    }
    if(sym == beginsym)   // begin
    {
        //codeNum���Զ���¼������һ��ָ���begin�����ָ�
        Pcode[symTable[tableStart[level]].address].a = codeNum; // ��ת������תλ�øĳɵ�ǰλ��
        symTable[tableStart[level]].address = codeNum; // �ڷ��ű��м�¼����ַΪ��ǰ��������ַ
        symTable[tableStart[level]].siz = varAddress[level]; // ����Ϊ��ǰ���ݴ�����λ��
       // tableStart[level] = codeNum;
        gen(INT,0,(varAddress[level]-symTable[tableStart[level]].value-4)); // �ڴ����
        //��ʱ������ÿ���������̶��ڴ��Ѿ�������ϣ�ֻ��Ҫ���Ǳ��������������
       // printf("%d  %d %f \n",tableStart[level],varAddress[level],symTable[tableStart[level]].value);
        CompStatement(); // ����<�������>
        if(symTable[tableStart[level]].kind == funcsym && !returned[level])   // ����û�з���ֵ
        {
            error(48);//����û�з���ֵ
            gen(OPR,0,0); // ���û�з���ֵ�������OPR,0,0 ���ء�
        }
        else if(symTable[tableStart[level]].kind == funcsym && returned[level])  // ���溯���ķ���ֵ
        {
            gen(SRV, 0, 0);
        }
        else   // ���̳�����Ҫ�ͷ����ݶ�����
        {
            gen(OPR, 0, 0);
        }
    }
    else  error(29); //�������δ��begin��ͷ
}

