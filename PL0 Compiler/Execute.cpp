# include "header.h"
# include "VarDef.h"

#define MAX_STR 1000 // ����ַ�������
int str_out = 0; // ��ǰ����ַ�������
double runStack[MAXSTACK]; // ����ջ
int stackNum=0; // ����ջջ��ָ��
void Execute()   // ����ִ��
{
    int i = 0; // ��ǰָ���i��ָ��
    int b = 0;// ָ���ַ ���·��������������ʼ��ַ
    CODE p; // ��ǰָ��
    int index; // ��ַ����ʱ��ʱ���������ַ
    int cnt; // �ӳ����������
    int intData;
    char charData;
    runStack[0] = runStack[1] = runStack[2] = 0;
    i=0;
    do
    {
        p=Pcode[i];
        i++;
        //printf("%s   %d  %f , %d\n",fct[p.f],p.l,p.a,stackNum);
        switch(p.f)
        {
            case LIT: // ȡֵ
                if(p.l < 0) runStack[stackNum++] = p.a; // ����ǰָ��aֵ����ջ��
                else runStack[stackNum++] = base(p.l, b) + p.a; // ����ǰ������ַ����ջ������ַ���ã�
                break;
            case OPR: // ����|�߼�����
                switch((int)p.a)
                {
                    case 0: // �ֳ�����ڣ��ָ��ֳ�
                        stackNum = b;
                        i = (int)runStack[stackNum+2];
                        b = (int)runStack[stackNum+1];
                        break;
                    case 1: // ȡ��
                        runStack[stackNum-1] *= -1;
                        break;
                    case 2: // �ӷ�
                        stackNum--;
                       // printf("---%f + %f , %d  %d\n",runStack[stackNum],runStack[stackNum-1],stackNum,stackNum-1);
                        runStack[stackNum-1] += runStack[stackNum];
                        break;
                    case 3: // ����
                        stackNum--;
                        runStack[stackNum-1] -= runStack[stackNum];
                        break;
                    case 4: // �˷�
                        stackNum--;
                       //  printf("---%f * %f , %d  %d\n",runStack[stackNum],runStack[stackNum-1],stackNum,stackNum-1);
                        runStack[stackNum-1] *= runStack[stackNum];
                        break;
                    case 5: // ����
                        stackNum--;
                       // printf("---%f / %f = ",runStack[stackNum-1],runStack[stackNum]);
                        if(runStack[stackNum]!=0)
                        {
                            if(p.l==-1) runStack[stackNum-1] = (int)runStack[stackNum-1]/(int)runStack[stackNum];
                            else runStack[stackNum-1] /= runStack[stackNum];
                        }
                        break;
                    case 6: // �е�
                        stackNum--;
                        runStack[stackNum-1] = (runStack[stackNum-1] == runStack[stackNum]);
                        break;
                    case 7: // �в���
                        stackNum--;
                        runStack[stackNum-1] = (runStack[stackNum-1] != runStack[stackNum]);
                        break;
                    case 8: // �д�
                        stackNum--;
                        runStack[stackNum-1] = (runStack[stackNum-1] > runStack[stackNum]);
                        break;
                    case 9: // �в���
                        stackNum--;
                        runStack[stackNum-1] = (runStack[stackNum-1] <= runStack[stackNum]);
                        break;
                    case 10: // ��С
                        stackNum--;
                        runStack[stackNum-1] = (runStack[stackNum-1] < runStack[stackNum]);
                        break;
                    case 11: // �в�С
                        stackNum--;
                        runStack[stackNum-1] = (runStack[stackNum-1] >= runStack[stackNum]);
                        break;
                    case 12: // ����ֵ��ջ
                        runStack[stackNum++] = runStack[stackNum+3]; //�˴����޸ģ�
                      //  printf("return == %f , %d\n",runStack[stackNum-1],stackNum-1);
                        break;
                    default: ;
                }
            break;
            case LOD: // ȡ����ֵ
                runStack[stackNum++] = runStack[base(p.l, b)+(int)p.a];
                break;
            case STO: // �����ֵ
                runStack[base(p.l, b)+(int)p.a] = runStack[--stackNum];
                break;
            case LAD: // ȡ��ַ����
                index = (int)runStack[base(p.l, b)+(int)p.a];
                runStack[stackNum++] = runStack[index];
                break;
            case SAD: // �洫ַ����
                index = (int)runStack[base(p.l, b)+(int)p.a];
                runStack[index] = runStack[--stackNum];
                break;
            case CAL: // �ӳ������  l��a�ֱ������Ͳ�������
                stackNum -= (int)p.a; // �ӹ��̻�ַ
                for(cnt = (int)p.a; cnt >0; cnt--)   // ת�Ʋ���,�ڳ��ռ�
                {
                    runStack[stackNum+cnt+3] = runStack[stackNum+cnt-1];
                }
                runStack[stackNum] = base(p.l, b); // ������øù��̵ĸ����̻���ַ
                runStack[stackNum+1] = b; // ���汾���̻���ַ
                runStack[stackNum+2] = i+2; // ������ýڵ����һ��ָ�+3Ϊ��������ֵ
                b = stackNum; // �ı����ַָ��ֵΪ�¹��̵Ļ���ַ
                break;
            case INT: // ����洢�ռ�
                stackNum += (int)p.a;
                //runStack[stackNum]=3;
                break;
            case JMP: // ��������ת
                i = (int)p.a;
                break;
            case JPC: // ������ת
               // printf("JPC--%f\n",runStack[stackNum-1]);
                if(runStack[--stackNum] == 0)
                    i = (int)p.a;
                break;
            case STA: // ��ֵ������Ԫ��
                stackNum -= 2;
                index = base(p.l, b) + (int)runStack[stackNum];
                runStack[index] = runStack[stackNum+1];
                break;
            case LOA: // ȡ����Ԫ�ص�ֵ���ַ ��lΪ���
                if(p.a == -1) //ȡ����Ԫ�صĵ�ַ
                {
                    runStack[stackNum-1] = base(p.l ,b) + runStack[stackNum-1];
                }
                else //ȡ����Ԫ�ص�ֵ
                {
                    index=base(p.l, b) + (int)runStack[stackNum-1];
                    runStack[stackNum-1] = runStack[index];
                }
                break;
            case SRV: // ���溯���ķ���ֵ
                runStack[b] = runStack[b+3]; // �洢����ֵ��
              //  printf("func == %f \n",runStack[b]);
                stackNum = b;
                i = (int)runStack[stackNum+2];
                b = (int)runStack[stackNum+1]; //
               // stackNum++;

                break;
            case WRT: // д������
                switch((int)p.a)
                {
                case 0:
                    fprintf(fresult, "%d", (int)runStack[--stackNum]);
                    printf("%d", (int)runStack[stackNum]);
                    break;
                case 1:
                    fprintf(fresult, "%f", runStack[--stackNum]);
                    printf("%f", runStack[stackNum]);
                    break;
                case 2:
                    fprintf(fresult, "%c", (int)runStack[--stackNum]);
                    printf("%c", (int)runStack[stackNum]);
                    break;
                case 3:
                    fprintf(fresult,"\n");
                    printf("\n");
                default:
                    ;
                }
                break;
            case RED: // ���������
                switch((int)p.a)
                {
                    case 0:
                        scanf("%d", &intData);
                        fprintf(fresult, "%d ", intData);
                        runStack[stackNum++] = (double)intData;
                        break;
                    case 1:
                        scanf("%lf", &runStack[stackNum++]);
                        fprintf(fresult, "%lf ", runStack[stackNum-1]);
                        break;
                    case 2:
                        scanf("%c", &charData);
                        getchar();
                        fprintf(fresult, "%c ", charData);
                        intData = (int)charData;
                        runStack[stackNum++] = (double)intData;
                        break;
                    default: ;
                }
                break;
            default:;
        }
    }
    while(i != 0);
}

int base(int l, int b)   // ͨ����̬������������Ļ���ַ,lΪ���,bΪ��ǰ�������Ļ���ַ
{
    int b1;
    b1 = b;
    while(l > 0)
    {
        b1 = (int)runStack[b1];
        l--;
    }
    return b1;
}
