# include "header.h"
# include "VarDef.h"

#define MAX_STR 1000 // 最大字符串长度
int str_out = 0; // 当前输出字符串数量
double runStack[MAXSTACK]; // 运行栈
int stackNum=0; // 运行栈栈顶指针
void Execute()   // 解释执行
{
    int i = 0; // 当前指令集第i条指令
    int b = 0;// 指令基址 最新分配的数据区的起始地址
    CODE p; // 当前指令
    int index; // 传址调用时临时保存变量地址
    int cnt; // 子程序参数个数
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
            case LIT: // 取值
                if(p.l < 0) runStack[stackNum++] = p.a; // 将当前指令a值存入栈顶
                else runStack[stackNum++] = base(p.l, b) + p.a; // 将当前变量地址存入栈顶（传址调用）
                break;
            case OPR: // 数字|逻辑运算
                switch((int)p.a)
                {
                    case 0: // 分程序出口，恢复现场
                        stackNum = b;
                        i = (int)runStack[stackNum+2];
                        b = (int)runStack[stackNum+1];
                        break;
                    case 1: // 取反
                        runStack[stackNum-1] *= -1;
                        break;
                    case 2: // 加法
                        stackNum--;
                       // printf("---%f + %f , %d  %d\n",runStack[stackNum],runStack[stackNum-1],stackNum,stackNum-1);
                        runStack[stackNum-1] += runStack[stackNum];
                        break;
                    case 3: // 减法
                        stackNum--;
                        runStack[stackNum-1] -= runStack[stackNum];
                        break;
                    case 4: // 乘法
                        stackNum--;
                       //  printf("---%f * %f , %d  %d\n",runStack[stackNum],runStack[stackNum-1],stackNum,stackNum-1);
                        runStack[stackNum-1] *= runStack[stackNum];
                        break;
                    case 5: // 除法
                        stackNum--;
                       // printf("---%f / %f = ",runStack[stackNum-1],runStack[stackNum]);
                        if(runStack[stackNum]!=0)
                        {
                            if(p.l==-1) runStack[stackNum-1] = (int)runStack[stackNum-1]/(int)runStack[stackNum];
                            else runStack[stackNum-1] /= runStack[stackNum];
                        }
                        break;
                    case 6: // 判等
                        stackNum--;
                        runStack[stackNum-1] = (runStack[stackNum-1] == runStack[stackNum]);
                        break;
                    case 7: // 判不等
                        stackNum--;
                        runStack[stackNum-1] = (runStack[stackNum-1] != runStack[stackNum]);
                        break;
                    case 8: // 判大
                        stackNum--;
                        runStack[stackNum-1] = (runStack[stackNum-1] > runStack[stackNum]);
                        break;
                    case 9: // 判不大
                        stackNum--;
                        runStack[stackNum-1] = (runStack[stackNum-1] <= runStack[stackNum]);
                        break;
                    case 10: // 判小
                        stackNum--;
                        runStack[stackNum-1] = (runStack[stackNum-1] < runStack[stackNum]);
                        break;
                    case 11: // 判不小
                        stackNum--;
                        runStack[stackNum-1] = (runStack[stackNum-1] >= runStack[stackNum]);
                        break;
                    case 12: // 返回值入栈
                        runStack[stackNum++] = runStack[stackNum+3]; //此处有修改！
                      //  printf("return == %f , %d\n",runStack[stackNum-1],stackNum-1);
                        break;
                    default: ;
                }
            break;
            case LOD: // 取变量值
                runStack[stackNum++] = runStack[base(p.l, b)+(int)p.a];
                break;
            case STO: // 存变量值
                runStack[base(p.l, b)+(int)p.a] = runStack[--stackNum];
                break;
            case LAD: // 取传址参数
                index = (int)runStack[base(p.l, b)+(int)p.a];
                runStack[stackNum++] = runStack[index];
                break;
            case SAD: // 存传址参数
                index = (int)runStack[base(p.l, b)+(int)p.a];
                runStack[index] = runStack[--stackNum];
                break;
            case CAL: // 子程序调用  l和a分别代表层差和参数个数
                stackNum -= (int)p.a; // 子过程基址
                for(cnt = (int)p.a; cnt >0; cnt--)   // 转移参数,腾出空间
                {
                    runStack[stackNum+cnt+3] = runStack[stackNum+cnt-1];
                }
                runStack[stackNum] = base(p.l, b); // 保存调用该过程的父过程基地址
                runStack[stackNum+1] = b; // 保存本过程基地址
                runStack[stackNum+2] = i+2; // 保存调用节点的下一条指令，+3为函数返回值
                b = stackNum; // 改变基地址指针值为新过程的基地址
                break;
            case INT: // 分配存储空间
                stackNum += (int)p.a;
                //runStack[stackNum]=3;
                break;
            case JMP: // 无条件跳转
                i = (int)p.a;
                break;
            case JPC: // 条件跳转
               // printf("JPC--%f\n",runStack[stackNum-1]);
                if(runStack[--stackNum] == 0)
                    i = (int)p.a;
                break;
            case STA: // 存值到数组元素
                stackNum -= 2;
                index = base(p.l, b) + (int)runStack[stackNum];
                runStack[index] = runStack[stackNum+1];
                break;
            case LOA: // 取数组元素的值或地址 ，l为层差
                if(p.a == -1) //取数组元素的地址
                {
                    runStack[stackNum-1] = base(p.l ,b) + runStack[stackNum-1];
                }
                else //取数组元素的值
                {
                    index=base(p.l, b) + (int)runStack[stackNum-1];
                    runStack[stackNum-1] = runStack[index];
                }
                break;
            case SRV: // 保存函数的返回值
                runStack[b] = runStack[b+3]; // 存储返回值。
              //  printf("func == %f \n",runStack[b]);
                stackNum = b;
                i = (int)runStack[stackNum+2];
                b = (int)runStack[stackNum+1]; //
               // stackNum++;

                break;
            case WRT: // 写语句输出
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
            case RED: // 读语句输入
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

int base(int l, int b)   // 通过静态链求出数据区的基地址,l为层差,b为当前数据区的基地址
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
