extern FILE *fsource, *fresult, *flex, *ferr, *fobjcode;
//词法分析中用到的变量
extern string id;
extern int line;
extern double dnum;
extern int inum;
extern symbol sym; // 存放当前所识别单词的类型代号

extern string iden;
extern int level; // 当前单词所在层次
extern double constValue; // 存放当前常量值
extern int varNum; // 当前登陆同类型变量个数
extern char str[MAXSTRNUM][MAXSTR]; // 暂存写语句字符串
extern int strNum; // 当前字符串数量
extern ERROR errorList[MAXERRORNUM];
extern int errorNum; // 当前错误个数
extern bool returned[50];
extern TABLE symTable[MAXTABLE];
extern int symNum; // 符号表尾指针 tx

extern bool  paraTable[MAXPARA]; // 参数标记表,标记传值或者传地址
extern symbol paraSym[MAXPARA];
extern int paraIndex; // 当前总参数个数

extern CODE Pcode[MAXCODE];//指令集
extern int codeNum ; // 当前指令总条数 cx


extern int varAddress[MAXLEVEL]; // 各层变量偏移地址 dx
extern int tableStart[MAXLEVEL]; // 本层开始时符号表位置 tx0
extern int codeStart[MAXLEVEL]; // 本层对应指令集位置 cx0

extern string work[22];// 共22个保留字符
extern enum symbol wsym[22]; //22个保留字符对应的标识符类型
extern char fct[15][30];
extern char trans[][50];
extern enum symbol ssym[300];
