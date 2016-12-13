# include "header.h"
# include "VarDef.h"
int FirstPosition(int x)   // 记下当前层代码开始位置
{
    int i;
    for(i = symNum; i > 0; i--)
    {
        if(symTable[i].kind == procsym || symTable[i].kind == funcsym) break;
    }
    //过程和函数无需记录地址偏移，因此用来存当前层目标代码的起始位置，用以跳转语句
    if(i!= 0)  x = x-(int)symTable[i].value; //减去参数个数
    symTable[x].address = codeNum; //主要是这一句！！！
    return x;
}
int FindPosition ()
{
    int i;
    symTable[0].name=iden;
    for(i = symNum; symTable[i].name!=iden ; i--) ;
    return i;
}

void enterTable(symbol kind)   // 登入符号表
{
    int i;
    i = FindPosition();
    if(i != 0 && level == symTable[i].level) //同一层重复定义
    {
        error(46); //符号表重定义
        return;
    }
    symNum++; //先加
    if(symNum >= MAXTABLE) //超过符号表最大长度
    {
        error(50); //符号表超过最大长度
        return;
    }
    symTable[symNum].name=iden;
    symTable[symNum].kind = kind;
    switch(kind)
    {
    case constsym: //常量值不会变化，故无需记录地址偏移
        symTable[symNum].value = constValue; //常量值
        symTable[symNum].type=sym;
        symTable[symNum].level = level;
        break;
    case varsym: //变量的类型还未赋值 可能为普通变量，可能为array类型
        symTable[symNum].level = level;
        symTable[symNum].address = varAddress[level];
      //  printf("var  %s  %d\n",symTable[symNum].name.c_str(),symNum);
        varAddress[level]++;
        break;
    case procsym: //记录层数以及参数表的起始位置，此时还无法确定参数数量类型等
        symTable[symNum].level = level;
        symTable[symNum].paraIndex = paraIndex; //参数表的起始位置
       //  printf("proc  %s  %d\n",symTable[symNum].name.c_str(),symNum);
        break;
    case funcsym: //记录层数以及参数表的起始位置,参数数量未定，函数返回值未定
        symTable[symNum].level = level;
        symTable[symNum].paraIndex = paraIndex;
        break;
    case addrsym:
        symTable[symNum].level = level;
        symTable[symNum].address = varAddress[level];
        varAddress[level]++;
        break;
    default:
        ;
    }
}
void enterVar() //普通变量，为变量赋值相应类型
{
    int i;
    for(i = symNum-varNum+1; i<=symNum; i++)
    {
        switch(sym)
        {
        case intesym:
            symTable[i].type = inumber;
            break;
        case realsym:
            symTable[i].type = rnumber;
            break;
        case charsym:
            symTable[i].type = charnumber;
            break;
        default:
            ;
        }
    }
}
void enterArray ()
//为每个数组变量定义类型，数组大小，以及偏移量，偏移量为每个数组起始位置的偏移
{
    int i;
    for(i = symNum - varNum + 1; i <= symNum; i++)
    {
        switch(sym)
        {
        case intesym:
            symTable[i].type = iArray;
            break;
        case realsym:
            symTable[i].type = rArray;
            break;
        case charsym:
            symTable[i].type = chAarray;
            break;
        default:
            ;
        }
        if(i == symNum - varNum + 1)
        {
            varAddress[level] = symTable[i].address;
        }
        symTable[i].siz = (int)constValue;
        symTable[i].address = varAddress[level];
        varAddress[level] += (int)constValue;
    }
}
void enterPara ()
{
    int i;
    for(i = paraIndex-varNum; i<paraIndex; i++)
    {
        switch(sym)
        {
        case intesym:
            paraSym[i]= inumber;
            break;
        case realsym:
            paraSym[i] = rnumber;
            break;
        case charsym:
            paraSym[i] = charnumber;
            break;
        default:
            ;
        }
    }
}
void enterFunc ( int index)   // 添加函数返回类型
{
    switch(sym)
    {
        case intesym: symTable[index].type = inumber; break;
        case realsym: symTable[index].type = rnumber; break;
        case charsym: symTable[index].type = charnumber; break;
        default: ;
    }
}
void TABLELIST ()
{
    for(int i=0;i<symNum;i++)
    {
        if(symTable[i].kind==constsym)
        {
            printf("%d  %s %lf\n",i,symTable[i].name.c_str(),symTable[i].value);
        }
        else printf("%d\n",i);
    }
}

