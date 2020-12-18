#include"preperl.h"
char keywords[2][20]={"scalar","foreach"};
char delim[]={',','<','>','.','-','(',')',';',':','%','[',']','#','?','\'','&','{','}','\"','^','!','*','/','|','\\','~','+','=','@','_'};
typedef struct TOKEN
{
    char name[100];
    int index;
    unsigned int row,col;
    char type[100];
}token;
int inDelim(char c)
{
    int l=strlen(delim);
    for(int i=0;i<l;i++)
    {
        if(c==delim[i])
            return 1;
    }
    return 0;
}
int isKeyword(char *check)
{
    for(int i=0;i<2;i++)
    {
        if(strcmp(check,keywords[i])==0)
            return 1;
    }
    return 0;
}
int main()
{
    preprocess();
    char c;
    FILE *fr,*fw;
    fr=fopen("output.c","r");
    fw=fopen("tokens.txt","w+");
    int line=0,col=0;
    char temp[100];
    int fill=0;
    token list[1024];
    int listindex=0;
    line=1;
    while((c=getc(fr))!=EOF)
    {
        col++;
        if(c=='\n')
        {
            col=0;
            line=line+1;
            continue;
        }
        if(c!=' ' && inDelim(c)==0 && c!='\n')
        {
            temp[fill++]=c;
        }
        else
        {
            temp[fill]='\0';
            fill=0;
            if(isKeyword(temp))
            {
                strcpy(list[listindex].name,temp);
                list[listindex].row=line;
                list[listindex].col=col-strlen(temp);
                strcpy(list[listindex].type,"KEYWORD");
                listindex++;
            }
            else if(strlen(temp)!=0)
            {
                if(temp[0]=='$')
                {
                    strcpy(list[listindex].name,temp);
                    list[listindex].row=line;
                    list[listindex].col=col-strlen(temp);
                    strcpy(list[listindex].type,"IDENTIFIER");
                    listindex++;
                }
                else if(temp[0]>='0' && temp[0]<='9')
                {
                    
                    strcpy(list[listindex].name,temp);
                    list[listindex].row=line;
                    list[listindex].col=col-strlen(temp);
                    strcpy(list[listindex].type,"NUMBER");
                    listindex++;
                }
            }
            if(inDelim(c)==1)
            {
                if(c=='@')
                {
                    list[listindex].name[0]=c;
                    c=getc(fr);
                    list[listindex].name[1]=c;
                    list[listindex].name[2]='\0';
                    list[listindex].row=line;
                    list[listindex].col=col;
                    listindex++;
                }
                else
                {
                    list[listindex].name[0]=c;
                    list[listindex].name[1]='\0';
                    list[listindex].row=line;
                    list[listindex].col=col;
                    strcpy(list[listindex].type,"DELIMITER");
                    listindex++;
                }
            }
        }
    }
    for(int i=0;i<listindex;i++)
    {
        fprintf(fw,"<%s, %d, %d, %s>\n",list[i].name,list[i].row,list[i].col,list[i].type);
    }
    fclose(fw);
    fclose(fr);
    return 0;
}