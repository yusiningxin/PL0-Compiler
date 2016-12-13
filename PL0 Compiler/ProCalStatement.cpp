# include "header.h"
# include "VarDef.h"
void ProceCalStatement()
{
    int i;
    i = FindPosition();
    getsym();
    if(sym == lparen)   // (
    {
        getsym();
        ActualParaList(i); // 调用<实在参数表>
        if(sym == rparen)  getsym();  // )
        else   error(53); // 缺少)
        gen(CAL, level-symTable[i].level, symTable[i].value);
        gen(INT, 0, symTable[i].value+4); // 分配参数空间，参数个数加上必要存储空间
        gen(JMP, 0, symTable[i].address); // 跳转到该过程起始代码处
    }
    else  error(52); // 缺少(
}
