extern FILE *fsource, *fresult, *flex, *ferr, *fobjcode;
//�ʷ��������õ��ı���
extern string id;
extern int line;
extern double dnum;
extern int inum;
extern symbol sym; // ��ŵ�ǰ��ʶ�𵥴ʵ����ʹ���

extern string iden;
extern int level; // ��ǰ�������ڲ��
extern double constValue; // ��ŵ�ǰ����ֵ
extern int varNum; // ��ǰ��½ͬ���ͱ�������
extern char str[MAXSTRNUM][MAXSTR]; // �ݴ�д����ַ���
extern int strNum; // ��ǰ�ַ�������
extern ERROR errorList[MAXERRORNUM];
extern int errorNum; // ��ǰ�������
extern bool returned[50];
extern TABLE symTable[MAXTABLE];
extern int symNum; // ���ű�βָ�� tx

extern bool  paraTable[MAXPARA]; // ������Ǳ�,��Ǵ�ֵ���ߴ���ַ
extern symbol paraSym[MAXPARA];
extern int paraIndex; // ��ǰ�ܲ�������

extern CODE Pcode[MAXCODE];//ָ�
extern int codeNum ; // ��ǰָ�������� cx


extern int varAddress[MAXLEVEL]; // �������ƫ�Ƶ�ַ dx
extern int tableStart[MAXLEVEL]; // ���㿪ʼʱ���ű�λ�� tx0
extern int codeStart[MAXLEVEL]; // �����Ӧָ�λ�� cx0

extern string work[22];// ��22�������ַ�
extern enum symbol wsym[22]; //22�������ַ���Ӧ�ı�ʶ������
extern char fct[15][30];
extern char trans[][50];
extern enum symbol ssym[300];
