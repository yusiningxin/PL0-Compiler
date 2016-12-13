# include "header.h"
FILE *fsource, *fresult, *flex, *ferr, *fobjcode;
string id;
string iden; //存放当前标识符,用于登记符号表
int line=0; //用于存放所在行号
double dnum;
int inum;
symbol sym; // 存放当前所识别单词的类型代号
int level = 0; // 当前单词所在层次
double constValue; // 存放当前常量值
int varNum; // 当前登记同类型变量个数
char str[MAXSTRNUM][MAXSTR]; // 暂存写语句字符串
int strNum = 0; // 当前字符串数量
bool returned[50];

ERROR errorList[MAXERRORNUM]; //错误列表
int errorNum = 0; // 当前错误个数

TABLE symTable[MAXTABLE];
int symNum = 0; // 符号表尾指针 tx

bool  paraTable[MAXPARA]; // 参数标记表
symbol paraSym[MAXPARA];
int paraIndex = 0; // 当前总参数个数


CODE Pcode[MAXCODE];//指令集
int codeNum = 0; // 当前指令总条数 cx


int varAddress[MAXLEVEL]; // 各层变量偏移地址 dx
int tableStart[MAXLEVEL]; // 本层开始时符号表位置 tx0
int codeStart[MAXLEVEL]; // 本层对应指令集位置 cx0

string work[22]={"array","begin","char","const","do","downto","else","end","for","function",
"if","integer","of","procedure","read","real","repeat","then","to","until","var","write"};
// 共22个保留字符
enum symbol wsym[22]={arraysym,beginsym,charsym,constsym,dosym,downtosym,elsesym,endsym,forsym,funcsym,
ifsym,intesym,ofsym,procsym,readsym,realsym,repeatsym,thensym,tosym,untilsym,varsym,writesym};
//22个保留字符对应的标识符类型

char trans[54][50]={"nul","inumber","rnumber","charnumber","iArray","rArray","chAarray","ident","plussym",
"minussym","times","division","eql","neq","lss","leq","gtr","geq","lparen","rparen","lbracket","rbracket",
"comma","squote","dquote","colon","semicolon","period","becomes","beginsym","endsym","ifsym",
"thensym","forsym","elsesym","dosym","arraysym","ofsym","constsym","realsym","intesym",
"charsym","varsym","strnumber","procsym","funcsym","addrsym","readsym","writesym","tosym","downtosym","untilsym",
"repeatsym","endfile"};

char fct[15][30]={"LIT",//l小于0，将常量值放入栈顶，否则将地址放入栈顶
    "OPR", //数字 逻辑运算
    "LOD", // 将变量放到栈顶，x为变量在说明层中的相对位置，y为调用层和说明层的层差
    "STO", //存变量值
    "CAL", //子程序调用
    "INT", //分配存储空间
    "JMP", //无条件跳转
    "JPC", //条件跳转
    "SRV", //保存函数的返回值
    "RED", //读语句
    "WRT", //写语句
    "STA", //存值到数组元素
    "LOA", //取数组元素的值
    "SAD", //存传址参数
    "LAD"}; //取传址参数
enum symbol ssym[300];





