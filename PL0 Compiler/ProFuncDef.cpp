# include "header.h"
# include "VarDef.h"
// <����˵������> ::= <�����ײ�><�ֳ���>{;<�����ײ�><�ֳ���>};
// < �����ײ�>    ::=   procedure<��ʶ��>'('[<��ʽ������>]')';
//< ��ʽ������>   ::= [var] <��ʶ��>{, <��ʶ��>}: <��������>{; <��ʽ������>}
int para=0; // ���̻�����������
int num=0; //��¼�������������ڷ��ű��е�λ�ã�������Ӳ�������
int index;
void ProceDeclaration ()
{
    index = symNum;
    getsym();
    if(sym == ident)   // <��ʶ��>
    {
        iden=id;
        enterTable(procsym);
        level++; //���²�������Ϊ��һ��
        varAddress[level] = 4; //�µ�һ��ƫ�Ƶ�ַ��4��ʼ
        getsym();
        if(sym == lparen)   // (
        {
            getsym();
            para = 0;
            num = symNum;
            if((sym == varsym) || (sym == ident))   // var|<��ʶ��>
            {
                FormalParaList(); // ����<��ʽ������>
            }
            symTable[num].value = para;
            if(sym == rparen)   // )
            {
                getsym();
                if(sym == semicolon) getsym();
                else  error(7); // ���δ��;����
            }
            else   error(55); // û��) ����
        }
        else  error(54); // û��( ����
    }
    else  error(20); // ���������Ǳ�ʶ��
    SubBlock(); // ����<�ֳ���>
    symNum = index+1; //�� 1 ����Ϊ�������һ��������
    level--;
    if(sym == semicolon) getsym();  // ;
    else  error(7); //������û���ԷֺŽ�β

}
// <����˵������> ::= <�����ײ�><�ֳ���>{;<�����ײ�><�ֳ���>};
// <�����ײ�> ::= function<��ʶ��>'('[<��ʽ������>]')':<��������>;
//< ��ʽ������>   ::= [var] <��ʶ��>{, <��ʶ��>}: <��������>{; <��ʽ������>}
void FuncDeclaration()
{
    if(sym == funcsym)   // function
    {
        index = symNum;
        getsym();
        if(sym == ident)   // <��ʶ��>
        {
            iden=id;
            enterTable(funcsym);
            level++;
            varAddress[level] = 4;
            getsym();
            if(sym == lparen)   // (
            {
                getsym();
                para = 0; //��¼��������
                num = symNum;
                if((sym == varsym) || (sym == ident))   // var|<��ʶ��>
                {
                    FormalParaList(); // ����<��ʽ������>
                }
                symTable[num].value = para;
                if(sym == rparen)   // )
                {
                    getsym();
                    if(sym == colon)   // :
                    {
                        getsym();
                        if((sym == intesym) || (sym == realsym) || (sym == charsym))   // ������������
                        {
                            enterFunc(num);
                            returned[level] = false;
                            getsym();
                            if(sym == semicolon) getsym();
                            else   error(7);// �����ײ�δ��;����
                        }
                        else   error(25);// �������Ͳ��ǻ�������
                    }
                    else  error(24); // ��������ֵ����û��ð��
                }
                else   error(54);// û��)
            }
            else  error(53); // ������û��()
        }
        else   error(23);// ���������Ǳ�ʶ��
        SubBlock(); // ����<�ֳ���>
        symNum = index + 1;
        level--;
        if(sym == semicolon)  getsym(); // ;
        else error(7);
    }
}

// <��ʽ������> ::= [var]<��ʶ��>{,<��ʶ��>}:<��������>{;<��ʽ������>}
void FormalParaList()
{
    symbol type=varsym;
    varNum = 0;
    if(sym == varsym)
    {
        type=addrsym;
        getsym();
    }
    if(sym == ident)   // <��ʶ��>
    {
        iden=id;
        enterTable(type);
        varNum++;
        if(type==addrsym) paraTable[paraIndex++] = true; //true��ʾ����ַ
        else paraTable[paraIndex++] = false;
        getsym();
        while(sym == comma)   // ,
        {
            getsym();
            if(sym == ident)   // <��ʶ��>
            {
                iden=id;
                enterTable(type);
                varNum++;
                if(type==addrsym) paraTable[paraIndex++] = true;
                else paraTable[paraIndex++] = false;
                getsym();
            }
            else   error(26);// �ββ��Ǳ�ʶ��
        }
        if(sym == colon)   // :
        {
            getsym();
            if((sym == intesym) || (sym == realsym) || (sym == charsym))   // <��������>
            {
                enterVar();
                enterPara();
                para += varNum;
                getsym();
                while(sym == semicolon)   // ;
                {
                    getsym();
                    FormalParaList(); // ����<��ʽ������>
                }
            }
            else   error(28);// �ββ��ǻ�������
        }
        else  error(27); // �β�����û��ð��
    }
    else   error(26); // �ββ��Ǳ�ʶ��
}
