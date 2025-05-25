#include <stdio.h>
#include <ctype.h>
#include <string.h>
int prec(char c){
    if(c=='^'){
        return 3;
    }
    else if(c== '*' || c== '/'){
        return 2;
    }
    else if(c=='+' || c=='-'){
        return 1;
    }
    else{
        return -1;
    }
}
 
void infixtopostfix(char* exp){
    int len= strlen(exp);
    char stack[len];
    char postfix[len+1];
    int top=-1;
    int j=0;

    for(int i=0; i<len; i++){
        char c= exp[i];
        if(c==' '){
            continue;
        }
        else if(isalnum(c)){
            postfix[j++]=c;
        }
        else if(c=='('){
            stack[++top]='(';
        }
        else if(c==')'){
            while(top!=-1 && stack[top]!='('){
                postfix[j++]=stack[top--];
            }
            top--;
        }
        else {
            while(top!=-1 && ((prec(c) < prec(stack[top])) || (prec(c)== prec(stack[top])) )){
                postfix[j++]=stack[top--];
            }
            stack[++top]=c;
        }
    }
    while(top!=-1){
        postfix[j++]=stack[top--];
    }
    postfix[j]='\0';
    printf("%s\n",postfix);
}

void infixtoprefix(char* exp){
    int len= strlen(exp);
    char prefix[len+1];
    char stack[len];
    int top=-1;
    int j=0;
    char temp;
    for(int i=0; i<(len/2); i++){
        temp=exp[i];
        exp[i]=exp[len-i-1];
        exp[len-i-1]=temp;     
    }
    for(int i=0; i<len; i++){
        if(exp[i]=='('){
            exp[i]=')';
        }
        else if(exp[i]==')'){
            exp[i]='(';
        }
    }
    for(int i=0; i<len; i++){
        char c= exp[i];
        if(c==' '){
            continue;
        }
        else if(isalnum(c)){
            prefix[j++]=c;
        }
        else if(c=='('){
            stack[++top]='(';
        }
        else if(c== ')'){
            while(top!=-1 && stack[top]!='('){
                prefix[j++]=stack[top--];
            }
            top--;
        }
        else{
            while(top != -1 && (
                prec(c) < prec(stack[top]) || 
                (prec(c) == prec(stack[top]) && c != '^')
            )) {
            prefix[j++]=stack[top--];
        }
        stack[++top]=c;
    }
    }
    while(top!=-1){
        prefix[j++]=stack[top--];
    }
    prefix[j]='\0';
    int len1= strlen(prefix);
    char temp1;
    for(int i=0; i<(len1/2); i++){
        temp1=prefix[i];
        prefix[i]=prefix[len1-i-1];
        prefix[len1-i-1]=temp1;     
    }
    printf("%s\n",prefix);

}

int main(){
    char exp[101];
    printf("Enter expression: ");
    fgets(exp, sizeof(exp), stdin);          
    exp[strcspn(exp, "\n")] = '\0';

    printf("Postfix:\n");
    infixtopostfix(exp);
    
    printf("Prefix:\n");
    infixtoprefix(exp);
    return 0;
}