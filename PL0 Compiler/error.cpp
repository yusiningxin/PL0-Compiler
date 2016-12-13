# include "header.h"
# include "VarDef.h"
string st;
void error (int n)
{
    switch(n)
    {
        case 0: st="程序应以.结尾";break;
        case 1: st="标识符长度太长";break;
        case 2: st="数字位数超过精度限制";break;
        case 3: st="字符串超过最大长度限制";break;
        case 4: st="两个单引号中间不是单个字符";break;
        case 5: st="单引号后面加不合法字符";break;
        case 6: st="没有后双引号";break;
        case 7: st="语句没有以分号结尾";break;
        case 8: st="常量名不是标识符";break;
        case 9: st="常量名后没有等号";break;
        case 10: st="正负号后面没有加数字";break;
        case 11: st="常量定义不合法";break;
        case 12: st="变量名不是标示符";break;
        case 13: st="类型定义没用:";break;
        case 14: st="变量定义非法类型";break;
        case 15: st="非法数组，无左中括号";break;
        case 16: st="非法数组下标";break;
        case 17: st="数组无右中括号";break;
        case 18: st="数组定义无of";break;
        case 19: st="非法数组类型";break;
        case 20: st="过程名不是标识符";break;
        case 21: st="缺少左括号";break;
        case 22: st="缺少右括号";break;
        case 23: st="函数名不是标识符";break;
        case 24: st="函数返回值类型没有冒号";break;
        case 25: st="函数类型不是基本类型";break;
        case 26: st="形参不是标识符";break;
        case 27: st="形参类型没有冒号";break;
        case 28: st="形参不是基本类型";break;
        case 29: st="复合语句未以begin开头";break;
        case 30: st="复合语句未以end结尾";break;
        case 31: st="不合法语句";break;
        case 32: st="标识符未定义";break;
        case 33: st="赋值符号不正确";break;
        case 34: st="变量或过程不能赋值";break;
        case 35: st="不合法<因子>";break;
        case 36: st="过程名不能作为因子";break;
        case 37: st="实参调用和形参声明不符";break;
        case 38: st="if语句中缺少then";break;
        case 39: st="条件语句中不是关系运算符";break;
        case 40: st="repeat语句中缺少until";break;
        case 41: st="for语句开头不是标识符";break;
        case 42: st="for语句中缺少to downto";break;
        case 43: st="for语句中缺少do";break;
        case 44: st="读语句处缺少标识符";break;
        case 45: st="读语句输入不合法";break;
        case 46: st="符号表重定义";break;
        case 47: st="程序末尾有多余字符";break;
        case 48: st="函数没有返回值";break;
        case 49: st="浮点数以.结尾";break;
        case 50: st="符号表超过最大长度";break;
        case 51: st="数组长度不能为0";break;
        case 52: st="实在参数表中缺少左括号";break;
        case 53: st="实在参数表中缺少右括号";break;
        case 54: st="形式参数表中缺少左括号";break;
        case 55: st="形式参数表中缺少右括号";break;
        case 56: st="for循环语句中循环变量类型错误";break;
        case 57: st="写语句中缺少右括号";break;
        case 58: st="写语句中缺少右括号";break;
        case 59: st="读语句中缺少左括号";break;
        case 60: st="读语句中缺少右括号";break;

    }
    errorList[errorNum].index=n;
    errorList[errorNum].line=line;
    errorList[errorNum++].content=st;
}
void ERRORLIST ()
{
    fprintf(ferr,"Error Number : %d\n",errorNum);
    printf("\nError Number : %d\n",errorNum);
    for(int i=0;i<errorNum;i++ )
    {
        fprintf(ferr,"%d: ERROR %d in Line %d : %s\n",i+1,errorList[i].index,errorList[i].line,errorList[i].content.c_str());
       // printf("%d: ERROR %d in Line %d : %s\n",i+1,errorList[i].index,errorList[i].line,errorList[i].content.c_str());
    }
}
