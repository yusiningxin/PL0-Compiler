# include "header.h"
# include "VarDef.h"
// <��ѭ�����> ::= while<����>do<���>
//< repeatѭ�����>  ::=  repeat <���>until<����>
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
    else error(40); //repeat�����ȱ��until

}

//< forѭ�����>  ::=  for <��ʶ��> := <���ʽ> (to|downto) <���ʽ> do <���>
void ForStatement ()
{
    int i;
    int code1, code2;
    bool down = false;
    getsym();
    if(sym == ident)   // <��ʶ��>
    {
        iden=id;
        i = FindPosition();
        if(i == 0)  error(32);
        if(symTable[i].kind != varsym) //�˴������⣡����
        {
            error(56);
            i = 0;
        }
        getsym();
        if(sym == becomes)   // :=
        {
            getsym();
            Expression(); // ����<���ʽ>
            if(i != 0) //���βκ�ʵ�Σ�����
                gen(STO, level-symTable[i].level, symTable[i].address);
            if(sym == tosym || sym==downtosym) // to downto
            {
                if(sym==tosym) down=false;
                else down=true;
                code1 = codeNum; // forѭ����ʼλ��
                gen(LOD, level-symTable[i].level, symTable[i].address);
                getsym();
                Expression(); // ����<���ʽ>
                if(down) gen(OPR, 0, 11);
                else gen(OPR,0,9);
                code2 = codeNum; // do��ʼλ��
                gen(JPC, 0, 0);
                if(sym == dosym)   // do
                {
                    getsym();
                    State(); // ����<���>
                    gen(LOD, level-symTable[i].level, symTable[i].address);
                    gen(LIT, -1, 1);
                    if(down) gen(OPR, 0, 3);
                    else gen(OPR, 0, 2);
                    gen(STO, level-symTable[i].level, symTable[i].address);
                    gen(JMP, 0, code1);
                    Pcode[code2].a = codeNum;
                }
                else  error(43); // for�����ȱ��do
            }
            else   error(42);// for�����ȱ��to downto
        }
        else    error(33);// for����в���:=
    }
    else   error(41);// for��俪ͷ���Ǳ�ʶ��

}

