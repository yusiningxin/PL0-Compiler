# include <cstdio>
# include <cstring>
# include <algorithm>
# include <string>
# include <cstring>
# include <iomanip>
# include <fstream>
# include <iostream>
# include <stdio.h>
# include <locale.h>
using namespace std;
# define MAXNUMBER 10 //最大数字位数限制
# define MAXWORD 100 // 最大单词,数字长度
# define MAXERRORNUM 10000 // 最大错误数量
# define MAXTABLE 100 // 符号表最大容量
# define MAXSTACK 1000 // 运行栈最大容量
# define MAXCODE 1000 // 指令集最大容量
# define MAXPARA 100 // 最大参数个数
# define MAXLEVEL 10 // 最大嵌套层数
# define MAXSTR 1000 // 写语句最大字符串长度
# define MAXSTRNUM 100 // 写语句最大字符串数量
# define WORKNUM  22 //保留字表长度
enum symbol
{
    nul,
    inumber,rnumber,charnumber,iArray,rArray,chAarray,ident,
    plussym,minussym,times,division,
    eql,neq,lss,leq,gtr,geq,
    lparen,rparen,
    lbracket,rbracket,
    comma,squote,dquote,colon,semicolon,period,becomes,
    beginsym,endsym,ifsym,thensym,forsym,elsesym,dosym,arraysym,ofsym,constsym,realsym,intesym,charsym,
    varsym,strnumber,procsym,funcsym,addrsym,readsym,writesym,tosym,downtosym,untilsym,repeatsym,endfile
};
enum FCT
{
    LIT,//l小于0，将常量值放入栈顶，否则将地址放入栈顶
    OPR, //数字 逻辑运算
    LOD, // 将变量放到栈顶，x为变量在说明层中的相对位置，y为调用层和说明层的层差
    STO, //存变量值
    CAL, //子程序调用
    INT, //分配存储空间
    JMP, //无条件跳转
    JPC, //条件跳转
    SRV, //保存函数的返回值
    RED, //读语句
    WRT, //写语句
    STA, //存值到数组元素
    LOA, //取数组元素的值
    SAD, //存传址参数
    LAD //取传址参数

};
struct TABLE
{
    string name;
    enum symbol type;// char integer real array
    enum symbol kind; // function procedure const var
    int level,address; // 层次和偏移，过程的address保存的是该过程起始代码指针
    int siz; //过程，函数所需内存空间 ; 数组大小
    double value; //常量值，参数个数
    int paraIndex;//过程 函数参数表指针
};
struct CODE
{
    enum FCT f;
    int l;
    double a;
};

struct ERROR
{
    int index,line;
    string content;
};
void getsym();
void ConstDeclaration();
void VarDeclaration();
void ProceDeclaration();
void FuncDeclaration();
void error(int n);
void block();
void SubBlock();

void statement();
void ForStatement();
void IfStatement();
void RepeatStatement();
void ActualParaList(int index);
void Expression();
void Condition();
void WriteStatement();
void ReadStatement();
void ProceCalStatement();
void AssignStatement();
void Term();
void Factor();
void gen (FCT x,int y,double z);
int FirstPosition(int x);
int FindPosition();
void enterTable(symbol kind);
void enterVar();
void enterArray();
void enterPara();
void enterFunc ( int index);
void FormalParaList();
void CompStatement();
void State ();
void PCODELIST();
void ERRORLIST ();
void Execute();
int base(int l,int b);
