# include "header.h"
# include "VarDef.h"
int FirstPosition(int x)   // ���µ�ǰ����뿪ʼλ��
{
    int i;
    for(i = symNum; i > 0; i--)
    {
        if(symTable[i].kind == procsym || symTable[i].kind == funcsym) break;
    }
    //���̺ͺ��������¼��ַƫ�ƣ���������浱ǰ��Ŀ��������ʼλ�ã�������ת���
    if(i!= 0)  x = x-(int)symTable[i].value; //��ȥ��������
    symTable[x].address = codeNum; //��Ҫ����һ�䣡����
    return x;
}
int FindPosition ()
{
    int i;
    symTable[0].name=iden;
    for(i = symNum; symTable[i].name!=iden ; i--) ;
    return i;
}

void enterTable(symbol kind)   // ������ű�
{
    int i;
    i = FindPosition();
    if(i != 0 && level == symTable[i].level) //ͬһ���ظ�����
    {
        error(46); //���ű��ض���
        return;
    }
    symNum++; //�ȼ�
    if(symNum >= MAXTABLE) //�������ű���󳤶�
    {
        error(50); //���ű�����󳤶�
        return;
    }
    symTable[symNum].name=iden;
    symTable[symNum].kind = kind;
    switch(kind)
    {
    case constsym: //����ֵ����仯���������¼��ַƫ��
        symTable[symNum].value = constValue; //����ֵ
        symTable[symNum].type=sym;
        symTable[symNum].level = level;
        break;
    case varsym: //���������ͻ�δ��ֵ ����Ϊ��ͨ����������Ϊarray����
        symTable[symNum].level = level;
        symTable[symNum].address = varAddress[level];
      //  printf("var  %s  %d\n",symTable[symNum].name.c_str(),symNum);
        varAddress[level]++;
        break;
    case procsym: //��¼�����Լ����������ʼλ�ã���ʱ���޷�ȷ�������������͵�
        symTable[symNum].level = level;
        symTable[symNum].paraIndex = paraIndex; //���������ʼλ��
       //  printf("proc  %s  %d\n",symTable[symNum].name.c_str(),symNum);
        break;
    case funcsym: //��¼�����Լ����������ʼλ��,��������δ������������ֵδ��
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
void enterVar() //��ͨ������Ϊ������ֵ��Ӧ����
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
//Ϊÿ����������������ͣ������С���Լ�ƫ������ƫ����Ϊÿ��������ʼλ�õ�ƫ��
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
void enterFunc ( int index)   // ��Ӻ�����������
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

