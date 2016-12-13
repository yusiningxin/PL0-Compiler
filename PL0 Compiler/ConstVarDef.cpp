# include "header.h"
# include "VarDef.h"
/*
< 常量说明部分>      ::=  const<常量定义>{,<常量定义>};
< 常量定义>          ::=  <标识符>＝ <常量>
< 常量>              ::=  [+| -] (<无符号整数>| <无符号实数>)|<字符>
< 字符>              ::=  '<字母>' | '<数字>'*/

void ConstDeclaration ()
{
    do
    {
        getsym();
        if(sym==ident) //标识符
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
                    if((sym == inumber) || (sym == rnumber))   // 无符号整|实数
                    {

                        if(sym == inumber) constValue = (double)inum;
                        if(sym == rnumber) constValue = dnum;
                        if(flag) constValue = -constValue;
                        enterTable(constsym);
                        getsym();
                    }
                    else error(10); // 正负号后面没有加数字
                }
                else if((sym == inumber) || (sym == rnumber))   // 无符号整|实数
                {
                    if(sym == inumber) constValue = (double)inum;
                    if(sym == rnumber) constValue = dnum;
                    enterTable(constsym);
                    getsym();
                }
                else if(sym == charnumber)   // 是否为字符
                {
                    char str = id[0];
                    constValue = (double)str;
                    enterTable(constsym);
                    getsym();
                }
                else  error(11);//常量定义不合法
            }
            else error(9); //常量名后没有等号
        }
        else error(8); //常量名不是标识符
    }
    while(sym == comma);
    if(sym == semicolon)  getsym();
    else error(7); //语句没有以分号结尾
}
/*
< 变量说明部分>     ::=  var <变量说明> ; {<变量说明>;}
< 变量说明>         ::=  <标识符>{, <标识符>} :  <类型>
< 类型>             ::=   <基本类型>|array'['<无符号整数>']' of <基本类型>
< 基本类型>         ::=   integer | real | char*/

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
                    if(sym == ident)   // <标示符>
                    {
                        iden=id;
                        enterTable(varsym);
                        varNum++;
                        getsym();
                    }
                    else   error(12);// 变量名不是标示符
                }
                if(sym == colon)   // :
                {
                    getsym();
                    if((sym == intesym) || (sym == realsym) || (sym == charsym))   // 整型、实型或字符类型
                    {
                        enterVar();
                        getsym();
                    }
                    else if(sym == arraysym)   // 数组类型
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
                                        if((sym == intesym) || (sym == realsym) || (sym == charsym))   // 数组类型声明
                                        {
                                            enterArray();
                                            getsym();
                                        }
                                        else   error(19);// 非法数组类型
                                    }
                                    else  error(18);// 数组定义无of
                                }
                                else error(17);//数组无右中括号
                            }
                            else   error(16);// 非法数组下标
                        }
                        else   error(15);// 非法数组，无左中括号
                    }
                    else   error(14);// 变量定义非法类型
                }
                else    error(13);// 类型定义没用:
                if(sym == semicolon)  getsym();
                else error(7);//语句没有以分号结尾
            }
            else error(12); //变量名不是标识符
        }
        while(sym==ident);
    }
}
