# include "header.h"
FILE *fsource, *fresult, *flex, *ferr, *fobjcode;
string id;
string iden; //��ŵ�ǰ��ʶ��,���ڵǼǷ��ű�
int line=0; //���ڴ�������к�
double dnum;
int inum;
symbol sym; // ��ŵ�ǰ��ʶ�𵥴ʵ����ʹ���
int level = 0; // ��ǰ�������ڲ��
double constValue; // ��ŵ�ǰ����ֵ
int varNum; // ��ǰ�Ǽ�ͬ���ͱ�������
char str[MAXSTRNUM][MAXSTR]; // �ݴ�д����ַ���
int strNum = 0; // ��ǰ�ַ�������
bool returned[50];

ERROR errorList[MAXERRORNUM]; //�����б�
int errorNum = 0; // ��ǰ�������

TABLE symTable[MAXTABLE];
int symNum = 0; // ���ű�βָ�� tx

bool  paraTable[MAXPARA]; // ������Ǳ�
symbol paraSym[MAXPARA];
int paraIndex = 0; // ��ǰ�ܲ�������


CODE Pcode[MAXCODE];//ָ�
int codeNum = 0; // ��ǰָ�������� cx


int varAddress[MAXLEVEL]; // �������ƫ�Ƶ�ַ dx
int tableStart[MAXLEVEL]; // ���㿪ʼʱ���ű�λ�� tx0
int codeStart[MAXLEVEL]; // �����Ӧָ�λ�� cx0

string work[22]={"array","begin","char","const","do","downto","else","end","for","function",
"if","integer","of","procedure","read","real","repeat","then","to","until","var","write"};
// ��22�������ַ�
enum symbol wsym[22]={arraysym,beginsym,charsym,constsym,dosym,downtosym,elsesym,endsym,forsym,funcsym,
ifsym,intesym,ofsym,procsym,readsym,realsym,repeatsym,thensym,tosym,untilsym,varsym,writesym};
//22�������ַ���Ӧ�ı�ʶ������

char trans[54][50]={"nul","inumber","rnumber","charnumber","iArray","rArray","chAarray","ident","plussym",
"minussym","times","division","eql","neq","lss","leq","gtr","geq","lparen","rparen","lbracket","rbracket",
"comma","squote","dquote","colon","semicolon","period","becomes","beginsym","endsym","ifsym",
"thensym","forsym","elsesym","dosym","arraysym","ofsym","constsym","realsym","intesym",
"charsym","varsym","strnumber","procsym","funcsym","addrsym","readsym","writesym","tosym","downtosym","untilsym",
"repeatsym","endfile"};

char fct[15][30]={"LIT",//lС��0��������ֵ����ջ�������򽫵�ַ����ջ��
    "OPR", //���� �߼�����
    "LOD", // �������ŵ�ջ����xΪ������˵�����е����λ�ã�yΪ���ò��˵����Ĳ��
    "STO", //�����ֵ
    "CAL", //�ӳ������
    "INT", //����洢�ռ�
    "JMP", //��������ת
    "JPC", //������ת
    "SRV", //���溯���ķ���ֵ
    "RED", //�����
    "WRT", //д���
    "STA", //��ֵ������Ԫ��
    "LOA", //ȡ����Ԫ�ص�ֵ
    "SAD", //�洫ַ����
    "LAD"}; //ȡ��ַ����
enum symbol ssym[300];





