# include "header.h"
# include "VarDef.h"
void block ()
{
    level++;
    varAddress[level] = 4; //各层变量偏移地址从4开始
    gen(INT,0,4); //运行栈空间分配4个
    SubBlock(); // 调用<分程序>
    level--;
    if(sym == period)   // <程序>以.结束
    {
        getsym();
        if(sym == endfile)   // 源程序到达结尾
        {
            printf("\nSyntax Analysis Complete.\n");
        }
        else   // 结尾还有其他部分
        {
            error(47);
            printf("\nSyntax Analysis Complete.\n");
        }
    }
    else   // 程序结尾应为.
    {
        error(0);
    }
}

// <分程序> ::= [<常量说明部分>][<变量说明部分>]{[<过程说明部分>]|[<函数说明部分>]}<复合语句>
void SubBlock ()
{
    tableStart[level] = symNum; // 记录本层对应符号表起始位置，此时还不是起始位置，上面可能有形参中变量定义。
    tableStart[level] = FirstPosition(tableStart[level]);  // 记录本层符号表开始位置，同时记下当前层代码开始位置
    gen(JMP, 0, 0); // 由各种声明部分跳转到复合语句执行部分，声明部分只登记符号表，不生成目标代码
    if(sym == constsym)
    {
        ConstDeclaration(); // 常量说明部分
    }
    if(sym == varsym)
    {
        VarDeclaration(); // 变量说明部分
    }
    while(true)
    {
        if(sym == procsym)
        {
            ProceDeclaration(); // 过程说明部分
        }
        else if(sym == funcsym)
        {
            FuncDeclaration(); //函数说明部分
        }
        else break;
    }
    if(sym == beginsym)   // begin
    {
        //codeNum中自动记录的是下一条指令，即begin后面的指令。
        Pcode[symTable[tableStart[level]].address].a = codeNum; // 跳转语句的跳转位置改成当前位置
        symTable[tableStart[level]].address = codeNum; // 在符号表中记录，地址为当前代码分配地址
        symTable[tableStart[level]].siz = varAddress[level]; // 长度为当前数据待分配位置
       // tableStart[level] = codeNum;
        gen(INT,0,(varAddress[level]-symTable[tableStart[level]].value-4)); // 内存分配
        //此时参数和每个数据区固定内存已经分配完毕，只需要考虑变量定义个数即可
       // printf("%d  %d %f \n",tableStart[level],varAddress[level],symTable[tableStart[level]].value);
        CompStatement(); // 调用<复合语句>
        if(symTable[tableStart[level]].kind == funcsym && !returned[level])   // 函数没有返回值
        {
            error(48);//函数没有返回值
            gen(OPR,0,0); // 如果没有返回值，则调用OPR,0,0 返回。
        }
        else if(symTable[tableStart[level]].kind == funcsym && returned[level])  // 保存函数的返回值
        {
            gen(SRV, 0, 0);
        }
        else   // 过程出口需要释放数据段命令
        {
            gen(OPR, 0, 0);
        }
    }
    else  error(29); //复合语句未以begin开头
}

