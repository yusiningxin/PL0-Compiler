# include "header.h"
# include "VarDef.h"
symbol expreType; // 当前表达式的返回值类型
bool paraType=false; //标记传值还是传引用，true为引用
//< 赋值语句>   ::=  <标识符> := <表达式>| <函数标识符> := <表达式>|<标识符>'['<表达式>']':= <表达式>
void AssignStatement ()
{
    int i;
    i = FindPosition();
    if(symTable[i].kind == funcsym)
    {
        getsym();
        if(sym == becomes)
        {
            getsym();
            Expression();
            gen(STO, 0, 3); //存变量值，函数返回值存在偏移量为3处
            returned[level] = true; //标记此层已有返回值
        }
        else error(33); //赋值符号不正确
    }
    else if(symTable[i].kind == addrsym) //形参不会是数组
    {
        getsym();
        if(sym == becomes)
        {
            getsym();
            Expression();
            gen(SAD, level-symTable[i].level, symTable[i].address);//存地址
        }
        else error(33);
    }
    else if(symTable[i].kind == varsym)
    {
        if(symTable[i].type == inumber|| symTable[i].type == rnumber|| symTable[i].type == charnumber)
        {
            getsym();
            if(sym == becomes)
            {
                getsym();
                Expression();
                gen(STO, level-symTable[i].level, symTable[i].address); //传值
            }
            else error(33);
        }
        else //表明为数组变量
        {
            getsym();
            if(sym == lbracket)
            {
                getsym();
                Expression();
                gen(LIT, -1, symTable[i].address);
                gen(OPR, 0, 2);
                if(sym == rbracket)
                {
                    getsym();
                    if(sym == becomes)
                    {
                        getsym();
                        Expression();
                        gen(STA, level-symTable[i].level, 0); // 存值到数组元素
                    }
                    else error(33);
                }
                else  error(17);
            }
            else  error(15);
        }
    }
    else  error(34); //变量或过程不能赋值
}

void Expression()   // <表达式> ::= [+|-]<项>{(+|-)<项>}
{
    expreType=charnumber;
    symbol op=nul;
    int tmp = 0;
    do
    {
        if((sym == plussym) || (sym == minussym))
        {
            op = sym;
            getsym();
        }
        Term(); // 调用<项>
        if(tmp == 0)
        {
            if(op == minussym) gen(OPR, 0, 1);
        }
        else
        {
            if(op == plussym) gen(OPR, 0, 2);
            if(op == minussym) gen(OPR, 0, 3);
        }
        tmp++;
    }
    while((sym ==plussym) || (sym == minussym));  // +|-
}

void Term()   // <项> ::= <因子>{(*|/)<因子>}
{
    symbol op;
    Factor(); // 调用<因子>
    while((sym == times) || (sym == division))
    {
        op = sym;
        getsym();
        Factor(); // 调用<因子>
        if(op == times)    gen(OPR, 0, 4);
        if(op == division)
        {
            if(expreType==inumber) gen(OPR, -1, 5);
            else gen(OPR, 0, 5);
        }
    }
}
// <因子> ::= <标识符>|<标识符>'['<表达式>']'|
//             <标识符>'('[<实在参数表>]')'|<无符号整数>|<无符号实数>|'('<表达式>')'
void Factor()
{
    int i;
    bool tmpParaType;
    if(sym == inumber)   // <无符号整数>
    {
        if(expreType != rnumber) expreType = inumber;
        gen(LIT, -1, inum);
        getsym();
    }
    else if(sym == rnumber)   // <无符号实数>
    {
        expreType = rnumber;
        gen(LIT, -1, dnum);
        getsym();
    }
    else if(sym == lparen)   // (
    {
        getsym();
        Expression(); // 调用<表达式>
        if(sym == rparen)  getsym(); // )
        else   error(22);// 缺少)
    }
    else if(sym == ident)   // <标识符>
    {
        iden=id;
        i =FindPosition();
        if(i == 0) error(32);
        else
        {
            if(symTable[i].type == inumber || symTable[i].type == iArray)
                if(expreType != rnumber) expreType = inumber;
            if(symTable[i].type == charnumber || symTable[i].type == chAarray)
                if(expreType != rnumber && expreType!=inumber) expreType = charnumber;
            if(symTable[i].type == rnumber || symTable[i].type == rArray)
                expreType = rnumber;
            switch(symTable[i].kind)
            {
                case constsym:
                    gen(LIT, -1, symTable[i].value);
                    getsym();
                    break;
                case varsym: //此项进入paraType为true的情况均为外部过程或函数调用
                    if(symTable[i].type == inumber || symTable[i].type == rnumber || symTable[i].type == charnumber)
                    {
                        if(paraType == false)
                            gen(LOD, level-symTable[i].level, symTable[i].address); // 找到变量地址并将其值入栈
                        else //程序调用的时候传地址
                            gen(LIT, level-symTable[i].level, symTable[i].address); // 加载变量的地址，var情况下传地址
                        getsym();
                    }
                    else //数组变量
                    {
                        getsym();
                        if(sym == lbracket)
                        {
                            getsym();
                            tmpParaType = paraType;
                            paraType = false; // 数组下标一定是取值
                            Expression();
                            paraType = tmpParaType;
                            if(paraType == false)
                            {
                                gen(LIT, -1, symTable[i].address);
                                gen(OPR, 0, 2);
                                gen(LOA, level-symTable[i].level, 0);//取数组元素值放到栈顶
                            }
                            else
                            {
                                gen(LIT, -1, symTable[i].address);
                                gen(OPR, 0, 2);
                                gen(LOA, level-symTable[i].level, -1);//加载数组元素地址
                            }
                            if(sym == rbracket) getsym();
                            else  error(17);
                        }
                        else error(15);
                    }
                    break;
                case addrsym: //进入过程或函数内部
                    if(paraType == true) //直接取变量的值就是地址 //传地址调用中嵌套传地址
                        gen(LOD, level-symTable[i].level, symTable[i].address); // 加载变量地址
                    else
                        gen(LAD, level-symTable[i].level, symTable[i].address); // 传地址参数
                    getsym();
                    break;
                case funcsym:
                    getsym();
                    if(sym == lparen)   // (
                    {
                        getsym();
                        ActualParaList(i); // 调用<实在参数表>
                        if(sym == rparen)   getsym();// )
                        else  error(22); // 缺少)
                        gen(CAL, level-symTable[i].level, symTable[i].value);
                        gen(INT, 0, symTable[i].value+4); // 分配参数空间
                        gen(JMP, 0, symTable[i].address); // 执行完参数赋值后跳转
                        gen(OPR, 0, 12); // 将返回值继续用来计算
                    }
                    else  error(21); // 缺少(
                    break;
                default:
                    error(36); //过程名不能作为因子
            }
        }
    }
    else error(35);// 不合法<因子>
}

void ActualParaList(int index)   // <实在参数表> ::= <表达式>{,<表达式>}
{
    int cnt= (int)symTable[index].value; //参数个数
    int callcnt = 0;
    int current = symTable[index].paraIndex; //在参数表中的起始位置
    bool flag=true;
    if(cnt == 0) return; //无形参直接返回
    do
    {
        callcnt++;
        cnt--;
        if(cnt < 0) break;
        if(callcnt > 1)  getsym();
        paraType=paraTable[current++];
        expreType=charnumber;
        Expression();
        if(expreType!=paraSym[current-1]) flag=false;
        paraType = false;
    }
    while(sym == comma);  // ,
    if(cnt!= 0 || sym == comma|| !flag) error(37); // 实参调用和形参声明不符
}

