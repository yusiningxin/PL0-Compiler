# include "header.h"
# include "VarDef.h"
void Init ()
{
    //fsource=fopen("13182002_test.txt","r");
    flex=fopen("Lexical Analysis.txt","w");
    ferr=fopen("error.txt","w");
    fobjcode=fopen("Pcode.txt","w");
    fresult=fopen("runResult.txt","w");
    for(int i=0;i<256;i++) ssym[i]=nul;
    ssym['\'']=squote;
    ssym['\"']=dquote;
    ssym[':']=colon;
    ssym['[']=lbracket;
    ssym[']']=rbracket;
    ssym['+'] = plussym;
    ssym['-'] = minussym;
    ssym['*'] = times;
    ssym['/'] = division;
    ssym['('] = lparen;
    ssym[')'] = rparen;
    ssym['='] = eql;
    ssym[','] = comma;
    ssym['.'] = period;
    ssym['<'] = lss;
    ssym['>'] = gtr;
    ssym[';'] = semicolon;
}
int main ()
{
  //  freopen("result.txt","w",stdout);
    Init();
    printf("Please Input Source File Path:\n");
    string path;
    getline(cin,path);
    if(path[0]=='\"') path=path.substr(1,path.size()-2);
    while((fsource=fopen(path.c_str(),"r"))==NULL)
    {
        printf("%s ERROR.\n",path.c_str());
        printf("Please Input Source File Path Again:\n");
        getline(cin,path);
        if(path[0]=='\"') path=path.substr(1,path.size()-2);
    }
    getsym();
    block();
    ERRORLIST();
    if(errorNum==0)
    {
        PCODELIST();
        printf("Pcode Complete.\n");
        Execute();
        printf("\nProgram Run Over.\n");
    }
    return 0;
}


