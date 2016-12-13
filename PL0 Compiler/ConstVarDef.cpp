# include "header.h"
# include "VarDef.h"
/*
< ����˵������>      ::=  const<��������>{,<��������>};
< ��������>          ::=  <��ʶ��>�� <����>
< ����>              ::=  [+| -] (<�޷�������>| <�޷���ʵ��>)|<�ַ�>
< �ַ�>              ::=  '<��ĸ>' | '<����>'*/

void ConstDeclaration ()
{
    do
    {
        getsym();
        if(sym==ident) //��ʶ��
        {
            iden=id;
            getsym();
            if(sym==eql)
            {
                getsym();
                if((sym == plussym) || (sym == minussym))   // +|-
                {
                    int flag;
                    if(sym == minussym) flag = 1;
                    getsym();
                    if((sym == inumber) || (sym == rnumber))   // �޷�����|ʵ��
                    {

                        if(sym == inumber) constValue = (double)inum;
                        if(sym == rnumber) constValue = dnum;
                        if(flag) constValue = -constValue;
                        enterTable(constsym);
                        getsym();
                    }
                    else error(10); // �����ź���û�м�����
                }
                else if((sym == inumber) || (sym == rnumber))   // �޷�����|ʵ��
                {
                    if(sym == inumber) constValue = (double)inum;
                    if(sym == rnumber) constValue = dnum;
                    enterTable(constsym);
                    getsym();
                }
                else if(sym == charnumber)   // �Ƿ�Ϊ�ַ�
                {
                    char str = id[0];
                    constValue = (double)str;
                    enterTable(constsym);
                    getsym();
                }
                else  error(11);//�������岻�Ϸ�
            }
            else error(9); //��������û�еȺ�
        }
        else error(8); //���������Ǳ�ʶ��
    }
    while(sym == comma);
    if(sym == semicolon)  getsym();
    else error(7); //���û���ԷֺŽ�β
}
/*
< ����˵������>     ::=  var <����˵��> ; {<����˵��>;}
< ����˵��>         ::=  <��ʶ��>{, <��ʶ��>} :  <����>
< ����>             ::=   <��������>|array'['<�޷�������>']' of <��������>
< ��������>         ::=   integer | real | char*/

void VarDeclaration ()
{
    if(sym == varsym)
    {
        getsym();
        do
        {
            varNum = 0;
            if(sym==ident)
            {
                iden=id;
                enterTable(varsym);
                varNum++;
                getsym();
                while(sym == comma)   // ,
                {
                    getsym();
                    if(sym == ident)   // <��ʾ��>
                    {
                        iden=id;
                        enterTable(varsym);
                        varNum++;
                        getsym();
                    }
                    else   error(12);// ���������Ǳ�ʾ��
                }
                if(sym == colon)   // :
                {
                    getsym();
                    if((sym == intesym) || (sym == realsym) || (sym == charsym))   // ���͡�ʵ�ͻ��ַ�����
                    {
                        enterVar();
                        getsym();
                    }
                    else if(sym == arraysym)   // ��������
                    {
                        getsym();
                        if(sym == lbracket)
                        {
                            getsym();
                            if(sym == inumber)
                            {
                                constValue = (double)inum;
                                if(inum==0) error(51);
                                getsym();
                                if(sym == rbracket)
                                {
                                    getsym();
                                    if(sym == ofsym)
                                    {
                                        getsym();
                                        if((sym == intesym) || (sym == realsym) || (sym == charsym))   // ������������
                                        {
                                            enterArray();
                                            getsym();
                                        }
                                        else   error(19);// �Ƿ���������
                                    }
                                    else  error(18);// ���鶨����of
                                }
                                else error(17);//��������������
                            }
                            else   error(16);// �Ƿ������±�
                        }
                        else   error(15);// �Ƿ����飬����������
                    }
                    else   error(14);// ��������Ƿ�����
                }
                else    error(13);// ���Ͷ���û��:
                if(sym == semicolon)  getsym();
                else error(7);//���û���ԷֺŽ�β
            }
            else error(12); //���������Ǳ�ʶ��
        }
        while(sym==ident);
    }
}
