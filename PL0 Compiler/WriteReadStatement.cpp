# include "header.h"
# include "VarDef.h"
extern symbol expreType;
//< д���>  ::=   write '(' <�ַ���>,<���ʽ>')'|write '(' <�ַ���>')'|write'('<���ʽ>')'
void WriteStatement()
{
    int i;
    getsym();
    if(sym == lparen)   // (
    {
        getsym();
        if(sym == strnumber)   // <�ַ���>
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
                Expression(); // ����<���ʽ>
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
            Expression(); // ����<���ʽ>

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
        else  error(58); // ȱ��)
    }
    else   error(57);// ����(

}

//< �����>  ::=  read'('<��ʶ��>{,<��ʶ��>}')'
void ReadStatement()
{
    int i;
    getsym();
    if(sym == lparen)   // (
    {
        do
        {
            getsym();
            if(sym == ident)   // <��ʶ��>
            {
                iden=id;
                i = FindPosition();
                if(i == 0) error(32);
                else
                {
                    if(symTable[i].kind==varsym) //�ٶ������ִ���ַ������Ϊ����
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
                    else error(45); //��������벻�Ϸ�
                    gen(STO,level-symTable[i].level,symTable[i].address);
                }
                getsym();
            }
            else  error(44); // ����䴦ȱ�ٱ�ʶ��
        }
        while(sym == comma);  // ,
        if(sym == rparen)   getsym(); // )
        else  error(60); // ����)
    }
    else   error(59); // ȱ��(
}
