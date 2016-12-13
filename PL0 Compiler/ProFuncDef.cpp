# include "header.h"
# include "VarDef.h"
// <过程说明部分> ::= <过程首部><分程序>{;<过程首部><分程序>};
// < 过程首部>    ::=   procedure<标识符>'('[<形式参数表>]')';
//< 形式参数表>   ::= [var] <标识符>{, <标识符>}: <基本类型>{; <形式参数表>}
int para=0; // 过程或函数参数个数
int num=0; //记录过程名或函数名在符号表中的位置，用以添加参数个数
int index;
void ProceDeclaration ()
{
    index = symNum;
    getsym();
    if(sym == ident)   // <标识符>
    {
        iden=id;
        enterTable(procsym);
        level++; //以下参数声明为下一层
        varAddress[level] = 4; //新的一层偏移地址从4开始
        getsym();
        if(sym == lparen)   // (
        {
            getsym();
            para = 0;
            num = symNum;
            if((sym == varsym) || (sym == ident))   // var|<标识符>
            {
                FormalParaList(); // 调用<形式参数表>
            }
            symTable[num].value = para;
            if(sym == rparen)   // )
            {
                getsym();
                if(sym == semicolon) getsym();
                else  error(7); // 语句未以;结束
            }
            else   error(55); // 没有) 括号
        }
        else  error(54); // 没有( 括号
    }
    else  error(20); // 过程名不是标识符
    SubBlock(); // 调用<分程序>
    symNum = index+1; //加 1 是因为后面存了一个过程名
    level--;
    if(sym == semicolon) getsym();  // ;
    else  error(7); //语句后面没有以分号结尾

}
// <函数说明部分> ::= <函数首部><分程序>{;<函数首部><分程序>};
// <函数首部> ::= function<标识符>'('[<形式参数表>]')':<基本类型>;
//< 形式参数表>   ::= [var] <标识符>{, <标识符>}: <基本类型>{; <形式参数表>}
void FuncDeclaration()
{
    if(sym == funcsym)   // function
    {
        index = symNum;
        getsym();
        if(sym == ident)   // <标识符>
        {
            iden=id;
            enterTable(funcsym);
            level++;
            varAddress[level] = 4;
            getsym();
            if(sym == lparen)   // (
            {
                getsym();
                para = 0; //记录参数数量
                num = symNum;
                if((sym == varsym) || (sym == ident))   // var|<标识符>
                {
                    FormalParaList(); // 调用<形式参数表>
                }
                symTable[num].value = para;
                if(sym == rparen)   // )
                {
                    getsym();
                    if(sym == colon)   // :
                    {
                        getsym();
                        if((sym == intesym) || (sym == realsym) || (sym == charsym))   // 函数类型声明
                        {
                            enterFunc(num);
                            returned[level] = false;
                            getsym();
                            if(sym == semicolon) getsym();
                            else   error(7);// 函数首部未以;结束
                        }
                        else   error(25);// 函数类型不是基本类型
                    }
                    else  error(24); // 函数返回值类型没有冒号
                }
                else   error(54);// 没有)
            }
            else  error(53); // 函数后没有()
        }
        else   error(23);// 函数名不是标识符
        SubBlock(); // 调用<分程序>
        symNum = index + 1;
        level--;
        if(sym == semicolon)  getsym(); // ;
        else error(7);
    }
}

// <形式参数表> ::= [var]<标识符>{,<标识符>}:<基本类型>{;<形式参数表>}
void FormalParaList()
{
    symbol type=varsym;
    varNum = 0;
    if(sym == varsym)
    {
        type=addrsym;
        getsym();
    }
    if(sym == ident)   // <标识符>
    {
        iden=id;
        enterTable(type);
        varNum++;
        if(type==addrsym) paraTable[paraIndex++] = true; //true表示传地址
        else paraTable[paraIndex++] = false;
        getsym();
        while(sym == comma)   // ,
        {
            getsym();
            if(sym == ident)   // <标识符>
            {
                iden=id;
                enterTable(type);
                varNum++;
                if(type==addrsym) paraTable[paraIndex++] = true;
                else paraTable[paraIndex++] = false;
                getsym();
            }
            else   error(26);// 形参不是标识符
        }
        if(sym == colon)   // :
        {
            getsym();
            if((sym == intesym) || (sym == realsym) || (sym == charsym))   // <基本类型>
            {
                enterVar();
                enterPara();
                para += varNum;
                getsym();
                while(sym == semicolon)   // ;
                {
                    getsym();
                    FormalParaList(); // 调用<形式参数表>
                }
            }
            else   error(28);// 形参不是基本类型
        }
        else  error(27); // 形参类型没有冒号
    }
    else   error(26); // 形参不是标识符
}
