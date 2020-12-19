#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


FILE *fa, *fb;

typedef struct ste
{
    char lexeme[30];
    int index;
    char type[15];
    int size;

} ste;

typedef struct token
{
    char token_name[100];
    unsigned int row, col;
} token;

typedef struct localTableData
{
    char fn_name[30];
    int size;
} localTableData;

FILE *file;

int row = 1, col = 0;

ste table[10][100];

localTableData tableData[10];

int st_index = 0;

int st_num = -1;

int scope = 0;

char dbuf[15] = "";

int isKeyword(char *word)

{

    char *keylist[30] = {"const", "int", "struct", "break", "else", "char",

                         "float", "long", "switch", "case", "enum", "return", "continue",

                         "for", "signed", "void", "do", "if", "static", "while", "double", "sizeof", "short",

                         "unsigned", "typedef", "true", "false", "bool", "printf", "scanf"};

    for (int i = 0; i < 30; ++i)

    {

        if (strcmp(word, keylist[i]) == 0)
        {

            return 1;
        }
    }

    return 0;
}

int isSpecialSymbol(char ch)

{

    return (strchr("[]{}(),;:.#", ch) != NULL);
}

int isOperator(char ch)

{

    return (strchr("+-*/%<>^=!", ch) != NULL);
}

token newToken(char name[50], int r, int c)

{

    token t;

    strcpy(t.token_name, name);

    t.row = r;

    t.col = c;

    return t;
}

void insertSt(char lexeme[100], char type[15], int size)

{

    ste t;

    strcpy(t.lexeme, lexeme);

    strcpy(t.type, type);

    t.size = size;

    t.index = st_index + 1;

    for (int i = 0; i < st_index; i++)

    {

        if (strcmp(table[st_num][i].lexeme, lexeme) == 0)

        {

            return;
        }
    }

    table[st_num][st_index++] = t;

    tableData[st_num].size += 1;
}

void printSt()

{

    for (int j = 0; j <= st_num; j++)

    {

        printf("\n------------------------------------\n");

        printf("\nSymbol table for %s\n\n", tableData[j].fn_name);

        printf("Index\tLexeme\tType\tSize\n");

        for (int i = 0; i < tableData[j].size; i++)

        {

            printf("%d\t%s\t%s\t%d\n", table[j][i].index, table[j][i].lexeme,

                   table[j][i].type, table[j][i].size);
        }
    }
}

token getNextToken()

{

    char buf[30];

    int idx = 0;

    int ca = getc(file);

    col++;

    token t;

    while (ca == '\n')

    {

        strcpy(dbuf, "");

        ca = getc(file);

        col = 1;

        row += 1;
    }

    if (ca == EOF)

    {

        return newToken("EOF", row, col);
    }

    if (ca == ' ')

    {

        ca = getc(file);

        col += 1;
    }

    if (isalpha(ca))

    {

        while (isalpha(ca) || isdigit(ca) || ca == '_')

        {

            buf[idx++] = ca;

            ca = getc(file);

            col++;
        }

        ungetc(ca, file);

        col--;

        buf[idx] = '\0';

        if (isKeyword(buf))

        {

            strcpy(dbuf, buf);

            t = newToken(buf, row, col - strlen(buf) + 1);
        }

        else

        {

            int num = 1;

             if(strcmp(buf, "main")==0)
        {

             t = newToken(buf, row, col - strlen(buf) + 1);
        }
         else   t = newToken("id", row, col - strlen(buf) + 1);

            ca = getc(file);

            if (ca == '(')

            {

                if (scope != 0)

                {

                    insertSt(buf, "func", -1);
                }

                else

                {

                    //printf("New function %s\n\n", buf);

                    st_num++;

                    strcpy(tableData[st_num].fn_name, buf);

                    st_index = 0;
                }

                ungetc(ca, file);

                return t;
            }

            if (ca == '[')

            {

                int pos = ftell(file);

                int cb;

                num = 0;

                while ((cb = getc(file)) != ']')

                {

                    num = num * 10 + (cb - '0');
                }

                fseek(file, pos, SEEK_SET);
            }

            ungetc(ca, file);

            int sz = 0;

            if (strcmp(dbuf, "int") == 0 || strcmp(dbuf, "float") == 0)
                sz = 4;

            else if (strcmp(dbuf, "char") == 0 || strcmp(dbuf, "bool") == 0)
                sz = 1;

            else if (strcmp(dbuf, "double") == 0 || strcmp(dbuf, "long") == 0)
                sz = 8;

            insertSt(buf, dbuf, sz * num);
        }
    }

    else if (isdigit(ca))

    {

        t = newToken("num", row, col);

        while (isdigit(ca) || ca == '.' || ca == 'e' || ca == 'E')

        {

            buf[idx++] = ca;

            ca = getc(file);

            col++;
        }

        ungetc(ca, file);

        col--;

        buf[idx] = '\0';
    }

    else if (ca == '"')

    {

        t = newToken("string", row, col);

        do

        {

            ca = getc(file);

            col++;

        } while (ca != '"');
    }

    else if (isSpecialSymbol(ca))

    {

        if (ca == '{')
            scope++;

        if (ca == '}')
            scope--;

        buf[idx++] = ca;

        buf[idx] = '\0';

        t = newToken(buf, row, col);
    }

    else if (isOperator(ca))

    {

        buf[idx++] = ca;

        ca = getc(file);
        col++;

        if (ca == '=')

        {

            buf[idx++] = ca;
        }

        else

        {

            ungetc(ca, file);

            col--;
        }

        buf[idx] = '\0';

        t = newToken(buf, row, col - strlen(buf) + 1);
    }

    else if (ca == '&')

    {

        buf[idx++] = ca;

        ca = getc(file);
        col++;

        if (ca == '&')

            buf[idx++] = ca;

        else

        {

            ungetc(ca, file);

            col--;
        }

        buf[idx] = '\0';

        t = newToken(buf, row, col - strlen(buf) + 1);
    }

    else if (ca == '|')

    {

        buf[idx++] = ca;

        ca = getc(file);

        col++;

        if (ca == '|')

            buf[idx++] = ca;

        else

        {

            ungetc(ca, file);

            col--;
        }

        buf[idx] = '\0';

        t = newToken(buf, row, col - strlen(buf) + 1);
    }

    return t;
}





// //header
// #include<stdio.h>
// #include<stdlib.h>
// #include<string.h>
// #include<ctype.h>

// typedef struct token{
// 	char lexeme[64];
// 	int row,col;
// 	char type[20];
// }token;

// static int row=1,col=1;
// char buff[2048];
// const char specialsymbols[]={'?',';',':',','};
// const char *keywords[]={"const","char","int","return","for","while","do","switch","if","else","unsigned","case","break"};
// const char *datatypes[]={"int","char","void","float","bool"};

// const char arithmeticsymbols[]={'*'};

// int isdatatype(char *w){
// 	int i;
// 	for(i=0;i<sizeof(datatypes)/sizeof(char *);i++){
// 		if(strcmp(w,datatypes[i])==0){
// 			return 1;
// 		}
// 	}
// 	return 0;
// }

// int iskeyword(char *str){
// 	for(int i=0;i<sizeof(keywords)/sizeof(char *);i++){
// 		if(strcmp(str,keywords[i])==0){
// 			return 1;
// 		}
// 	}
// 	return 0;
// }

// int charbelongsto(int c, const char *arr){
// 	int len;
// 	if(arr==specialsymbols){
// 		len=sizeof(specialsymbols)/sizeof(char);
// 	}else if(arr==arithmeticsymbols){
// 		len=sizeof(arithmeticsymbols)/sizeof(char);
// 	}
// 	for(int i=0;i<len;i++){
// 		if(c==arr[i]){
// 			return 1;
// 		}
// 	}
// 	return 0;
// }


// void filltoken(struct token *tkn, char c, int row, int col, char *type){
// 	tkn->row=row;
// 	tkn->col=col;
// 	strcpy(tkn->type,type);
// 	tkn->lexeme[0]=c;
// 	tkn->lexeme[1]='\0';
// }

// void newline(){
// 	row++;
// 	col=1;

// }

// struct token getnexttoken(FILE *f1){
// 	int c;
// 	struct token tkn={
// 		row=-1
// 	};
// 	int gottoken=0;

// 	while(!gottoken &&(c=fgetc(f1))!=EOF){
// 		if(charbelongsto(c,specialsymbols)){
// 			filltoken(&tkn,c,row,col,"specialsymbols");
// 			gottoken=1;
// 			col++;
// 		}

// 		else if(charbelongsto(c,arithmeticsymbols)){
// 			filltoken(&tkn,c,row,col,"arithmeticoperator");
// 			gottoken=1;
// 			col++;
// 		}

// 		else if(c=='('){
// 			filltoken(&tkn,c,row,col,"leftbracket");
// 			gottoken=1;
// 			col++;
// 		}
// 		else if(c==')'){
// 			filltoken(&tkn,c,row,col,"rightbracket");
// 			gottoken=1;
// 			col++;
// 		}
// 		else if(c=='{'){
// 			filltoken(&tkn,c,row,col,"left curly");
// 			gottoken=1;
// 			col++;
// 		}
// 		else if(c=='}'){
// 			filltoken(&tkn,c,row,col,"right curly");
// 			gottoken=1;
// 			col++;
// 		}
// 		else if(c=='+'){
// 			int d=fgetc(f1);
// 			if(d!='+'){
// 				filltoken(&tkn,c,row,col,"arithmeticoperator");
// 				gottoken=1;
// 				col++;
// 				fseek(f1,-1,SEEK_CUR);
// 			}else{
// 				filltoken(&tkn,c,row,col,"unary coperator");
// 				strcpy(tkn.lexeme,"++");
// 				gottoken=1;
// 				col+=2;
				
// 			}
// 		}
// 		else if(c=='+'){
// 			int d=fgetc(f1);
// 			if(d!='-'){
// 				filltoken(&tkn,c,row,col,"arithmeticoperator");
// 				gottoken=1;
// 				col++;
// 				fseek(f1,-1,SEEK_CUR);
// 			}else{
// 				filltoken(&tkn,c,row,col,"unary operator");
// 				strcpy(tkn.lexeme,"--");
// 				gottoken=1;
// 				col+=2;
				
// 			}
// 		}
// 		else if(c=='='){
// 			int d=fgetc(f1);
// 			if(d!='-'){
// 				filltoken(&tkn,c,row,col,"arithmeticoperator");
// 				gottoken=1;
// 				col++;
// 				fseek(f1,-1,SEEK_CUR);
// 			}else{
// 				filltoken(&tkn,c,row,col,"relational operator");
// 				strcpy(tkn.lexeme,"==");
// 				gottoken=1;
// 				col+=2;
				
// 			}
// 		}
// 		else if(isdigit(c)){
// 			tkn.row=row;
// 			tkn.col=col;
// 			tkn.lexeme[0]=c;
// 			int k=1;
// 			while((c=fgetc(f1))!=EOF&&isdigit(c)){
// 				tkn.lexeme[k++]=c;
// 				col++;
// 			}
// 			tkn.lexeme[k]='\0';
// 			strcpy(tkn.type,"number");
// 			gottoken=1;
// 			fseek(f1,-1,SEEK_CUR);
// 		}

// 		else if(c=='#'){
// 			while((c=fgetc(f1))!=EOF&&c!='\n');
// 			newline();
			
// 		}

// 		else if(c=='\n'){
// 			newline();
// 			c=fgetc(f1);
// 			if(c=='#'){
// 				while((c=fgetc(f1))!=EOF&&c!='\n');
// 				newline();
			
// 			}

// 			else if(c!=EOF){
// 				fseek(f1,-1,SEEK_CUR);
// 			}
// 		}

// 		else if(isspace(c)){
// 			col++;
// 		}

// 		else if(isalpha(c)||c=='_'){
// 			tkn.row=row;
// 			tkn.col=col++;
// 			tkn.lexeme[0]=c;
// 			int k=1;
// 			while((c=fgetc(f1))!=EOF && isalnum(c)){
// 				tkn.lexeme[k++]=c;
// 				col++;
// 			}
// 			tkn.lexeme[k]='\0';
// 			if(iskeyword(tkn.lexeme)){
// 				strcpy(tkn.type,"keyword");
// 			}else{
// 				strcpy(tkn.type,"identifier");
// 			}
// 			gottoken=1;
// 			fseek(f1,-1,SEEK_CUR);
// 		}

// 		else if(c=='/'){
// 			int d=fgetc(f1);
// 			col++;
// 			if(d=='/'){
// 				while((c=fgetc(f1))!=EOF&&c!='\n'){
// 					col++;
// 				}
// 				if(c=='\n'){
// 					newline();
// 				}
// 			}else if(d=='*'){
// 				do{
// 					if(d=='\n'){
// 						newline();
// 					}
// 					while((c=fgetc(f1))!=EOF &&c!='*'){
// 						col++;
// 						if(c=='\n'){
// 							newline();
// 						}
// 					}
// 					col++;
// 				}
// 				while((d=fgetc(f1))!=EOF &&d!='/' &&col++);
// 					col++;
				

// 			}else{
// 				filltoken(&tkn,c,row,col--,"arithmeticoperator");
// 				gottoken=1;
// 				fseek(f1,-1,SEEK_CUR);
// 			}
// 		}
// 		else if(c=='"'){
// 			tkn.row=row;
// 			tkn.col=col;
// 			strcpy(tkn.type,"String literal");
// 			int k=1;
// 			tkn.lexeme[0]='"';
// 			while((c=fgetc(f1))!=EOF &&c!='"'){
// 				tkn.lexeme[k++]=c;
// 				col++;
// 			}
// 			tkn.lexeme[k]='"';
// 			gottoken=1;
// 		}

// 		else if(c=='<' || c=='>' || c=='!'){
// 			filltoken(&tkn,c,row,col,"relational operator");
// 			col++;
// 			int d=fgetc(f1);
// 			if(d=='='){
// 				col++;
// 				strcat(tkn.lexeme,"=");
// 			}
// 			else{
// 				if(c=='!'){
// 					strcpy(tkn.type,"logical operator");
// 				}
// 				fseek(f1,-1,SEEK_CUR);
// 			}
// 				gottoken=1;
			
// 		}

// 		else if(c=='&'||c=='|'){
// 			int d=fgetc(f1);
// 			if(c==d){
// 				tkn.lexeme[0]=tkn.lexeme[1]=c;
// 				tkn.lexeme[2]='\0';
// 				tkn.row=row;
// 				tkn.col=col;
// 				col++;
// 				gottoken=1;
// 				strcpy(tkn.type,"logical operator");
// 			}else{
// 				fseek(f1,-1,SEEK_CUR);
// 			}
// 			col++;
// 		}
// 		else{
// 			col++;
// 		}
// 	}	
// 		return tkn;

	
// }

