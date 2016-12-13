# include "header.h"
# include "VarDef.h"
void CompStatement()
{
    if(sym == beginsym)   // begin
    {
        do
        {
            getsym();
            State(); // 调用<语句>
        }
        while(sym == semicolon);  // ;
        if(sym == endsym) getsym(); // end
        else   error(30); // 复合语句未以end结尾
    }
    else  error(29); // 复合语句未以begin开头
}

//< 语句>   ::=  <赋值语句>|<条件语句>|<repeat循环语句>|<过程调用语句>|<复合语句>|
//              <读语句>|<写语句>|<for循环语句>|<空>
void State ()
{
    int i;
    if(sym == ident)   // 标识符开头为过程调用语句或者赋值语句
    {
        iden=id;
        i = FindPosition();
        if(i == 0)
        {
            error(32); //标识符未定义
            return;
        }
        if(symTable[i].kind == procsym) ProceCalStatement(); // 过程调用语句
        else AssignStatement(); // 赋值语句
    }
    else if(sym == ifsym)   IfStatement(); // 条件语句
    else if(sym == repeatsym)   RepeatStatement(); // repeat循环
    else if(sym == beginsym)  CompStatement(); // 复合语句
    else if(sym == readsym)  ReadStatement(); // 读语句
    else if(sym == writesym)   WriteStatement(); // 写语句
    else if(sym == forsym)    ForStatement(); // for循环语句
    else if(sym==endsym) return ;
    else  error(31); //不合法语句
}
