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
# define MAXNUMBER 10 //�������λ������
# define MAXWORD 100 // ��󵥴�,���ֳ���
# define MAXERRORNUM 10000 // ����������
# define MAXTABLE 100 // ���ű��������
# define MAXSTACK 1000 // ����ջ�������
# define MAXCODE 1000 // ָ��������
# define MAXPARA 100 // ����������
# define MAXLEVEL 10 // ���Ƕ�ײ���
# define MAXSTR 1000 // д�������ַ�������
# define MAXSTRNUM 100 // д�������ַ�������
# define WORKNUM  22 //�����ֱ���
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
    LIT,//lС��0��������ֵ����ջ�������򽫵�ַ����ջ��
    OPR, //���� �߼�����
    LOD, // �������ŵ�ջ����xΪ������˵�����е����λ�ã�yΪ���ò��˵����Ĳ��
    STO, //�����ֵ
    CAL, //�ӳ������
    INT, //����洢�ռ�
    JMP, //��������ת
    JPC, //������ת
    SRV, //���溯���ķ���ֵ
    RED, //�����
    WRT, //д���
    STA, //��ֵ������Ԫ��
    LOA, //ȡ����Ԫ�ص�ֵ
    SAD, //�洫ַ����
    LAD //ȡ��ַ����

};
struct TABLE
{
    string name;
    enum symbol type;// char integer real array
    enum symbol kind; // function procedure const var
    int level,address; // ��κ�ƫ�ƣ����̵�address������Ǹù�����ʼ����ָ��
    int siz; //���̣����������ڴ�ռ� ; �����С
    double value; //����ֵ����������
    int paraIndex;//���� ����������ָ��
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
