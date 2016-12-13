# include "header.h"
# include "VarDef.h"
symbol expreType; // ��ǰ���ʽ�ķ���ֵ����
bool paraType=false; //��Ǵ�ֵ���Ǵ����ã�trueΪ����
//< ��ֵ���>   ::=  <��ʶ��> := <���ʽ>| <������ʶ��> := <���ʽ>|<��ʶ��>'['<���ʽ>']':= <���ʽ>
void AssignStatement ()
{
    int i;
    i = FindPosition();
    if(symTable[i].kind == funcsym)
    {
        getsym();
        if(sym == becomes)
        {
            getsym();
            Expression();
            gen(STO, 0, 3); //�����ֵ����������ֵ����ƫ����Ϊ3��
            returned[level] = true; //��Ǵ˲����з���ֵ
        }
        else error(33); //��ֵ���Ų���ȷ
    }
    else if(symTable[i].kind == addrsym) //�ββ���������
    {
        getsym();
        if(sym == becomes)
        {
            getsym();
            Expression();
            gen(SAD, level-symTable[i].level, symTable[i].address);//���ַ
        }
        else error(33);
    }
    else if(symTable[i].kind == varsym)
    {
        if(symTable[i].type == inumber|| symTable[i].type == rnumber|| symTable[i].type == charnumber)
        {
            getsym();
            if(sym == becomes)
            {
                getsym();
                Expression();
                gen(STO, level-symTable[i].level, symTable[i].address); //��ֵ
            }
            else error(33);
        }
        else //����Ϊ�������
        {
            getsym();
            if(sym == lbracket)
            {
                getsym();
                Expression();
                gen(LIT, -1, symTable[i].address);
                gen(OPR, 0, 2);
                if(sym == rbracket)
                {
                    getsym();
                    if(sym == becomes)
                    {
                        getsym();
                        Expression();
                        gen(STA, level-symTable[i].level, 0); // ��ֵ������Ԫ��
                    }
                    else error(33);
                }
                else  error(17);
            }
            else  error(15);
        }
    }
    else  error(34); //��������̲��ܸ�ֵ
}

void Expression()   // <���ʽ> ::= [+|-]<��>{(+|-)<��>}
{
    expreType=charnumber;
    symbol op=nul;
    int tmp = 0;
    do
    {
        if((sym == plussym) || (sym == minussym))
        {
            op = sym;
            getsym();
        }
        Term(); // ����<��>
        if(tmp == 0)
        {
            if(op == minussym) gen(OPR, 0, 1);
        }
        else
        {
            if(op == plussym) gen(OPR, 0, 2);
            if(op == minussym) gen(OPR, 0, 3);
        }
        tmp++;
    }
    while((sym ==plussym) || (sym == minussym));  // +|-
}

void Term()   // <��> ::= <����>{(*|/)<����>}
{
    symbol op;
    Factor(); // ����<����>
    while((sym == times) || (sym == division))
    {
        op = sym;
        getsym();
        Factor(); // ����<����>
        if(op == times)    gen(OPR, 0, 4);
        if(op == division)
        {
            if(expreType==inumber) gen(OPR, -1, 5);
            else gen(OPR, 0, 5);
        }
    }
}
// <����> ::= <��ʶ��>|<��ʶ��>'['<���ʽ>']'|
//             <��ʶ��>'('[<ʵ�ڲ�����>]')'|<�޷�������>|<�޷���ʵ��>|'('<���ʽ>')'
void Factor()
{
    int i;
    bool tmpParaType;
    if(sym == inumber)   // <�޷�������>
    {
        if(expreType != rnumber) expreType = inumber;
        gen(LIT, -1, inum);
        getsym();
    }
    else if(sym == rnumber)   // <�޷���ʵ��>
    {
        expreType = rnumber;
        gen(LIT, -1, dnum);
        getsym();
    }
    else if(sym == lparen)   // (
    {
        getsym();
        Expression(); // ����<���ʽ>
        if(sym == rparen)  getsym(); // )
        else   error(22);// ȱ��)
    }
    else if(sym == ident)   // <��ʶ��>
    {
        iden=id;
        i =FindPosition();
        if(i == 0) error(32);
        else
        {
            if(symTable[i].type == inumber || symTable[i].type == iArray)
                if(expreType != rnumber) expreType = inumber;
            if(symTable[i].type == charnumber || symTable[i].type == chAarray)
                if(expreType != rnumber && expreType!=inumber) expreType = charnumber;
            if(symTable[i].type == rnumber || symTable[i].type == rArray)
                expreType = rnumber;
            switch(symTable[i].kind)
            {
                case constsym:
                    gen(LIT, -1, symTable[i].value);
                    getsym();
                    break;
                case varsym: //�������paraTypeΪtrue�������Ϊ�ⲿ���̻�������
                    if(symTable[i].type == inumber || symTable[i].type == rnumber || symTable[i].type == charnumber)
                    {
                        if(paraType == false)
                            gen(LOD, level-symTable[i].level, symTable[i].address); // �ҵ�������ַ������ֵ��ջ
                        else //������õ�ʱ�򴫵�ַ
                            gen(LIT, level-symTable[i].level, symTable[i].address); // ���ر����ĵ�ַ��var����´���ַ
                        getsym();
                    }
                    else //�������
                    {
                        getsym();
                        if(sym == lbracket)
                        {
                            getsym();
                            tmpParaType = paraType;
                            paraType = false; // �����±�һ����ȡֵ
                            Expression();
                            paraType = tmpParaType;
                            if(paraType == false)
                            {
                                gen(LIT, -1, symTable[i].address);
                                gen(OPR, 0, 2);
                                gen(LOA, level-symTable[i].level, 0);//ȡ����Ԫ��ֵ�ŵ�ջ��
                            }
                            else
                            {
                                gen(LIT, -1, symTable[i].address);
                                gen(OPR, 0, 2);
                                gen(LOA, level-symTable[i].level, -1);//��������Ԫ�ص�ַ
                            }
                            if(sym == rbracket) getsym();
                            else  error(17);
                        }
                        else error(15);
                    }
                    break;
                case addrsym: //������̻����ڲ�
                    if(paraType == true) //ֱ��ȡ������ֵ���ǵ�ַ //����ַ������Ƕ�״���ַ
                        gen(LOD, level-symTable[i].level, symTable[i].address); // ���ر�����ַ
                    else
                        gen(LAD, level-symTable[i].level, symTable[i].address); // ����ַ����
                    getsym();
                    break;
                case funcsym:
                    getsym();
                    if(sym == lparen)   // (
                    {
                        getsym();
                        ActualParaList(i); // ����<ʵ�ڲ�����>
                        if(sym == rparen)   getsym();// )
                        else  error(22); // ȱ��)
                        gen(CAL, level-symTable[i].level, symTable[i].value);
                        gen(INT, 0, symTable[i].value+4); // ��������ռ�
                        gen(JMP, 0, symTable[i].address); // ִ���������ֵ����ת
                        gen(OPR, 0, 12); // ������ֵ������������
                    }
                    else  error(21); // ȱ��(
                    break;
                default:
                    error(36); //������������Ϊ����
            }
        }
    }
    else error(35);// ���Ϸ�<����>
}

void ActualParaList(int index)   // <ʵ�ڲ�����> ::= <���ʽ>{,<���ʽ>}
{
    int cnt= (int)symTable[index].value; //��������
    int callcnt = 0;
    int current = symTable[index].paraIndex; //�ڲ������е���ʼλ��
    bool flag=true;
    if(cnt == 0) return; //���β�ֱ�ӷ���
    do
    {
        callcnt++;
        cnt--;
        if(cnt < 0) break;
        if(callcnt > 1)  getsym();
        paraType=paraTable[current++];
        expreType=charnumber;
        Expression();
        if(expreType!=paraSym[current-1]) flag=false;
        paraType = false;
    }
    while(sym == comma);  // ,
    if(cnt!= 0 || sym == comma|| !flag) error(37); // ʵ�ε��ú��β���������
}

