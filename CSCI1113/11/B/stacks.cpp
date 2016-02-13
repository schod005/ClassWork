#include <iostream>
#include <string>
#include <cstdlib>
#include "Token.h"
using namespace std;
void push(Token* &stack, Token* tok)
{
	tok->setLink(stack);
	stack=tok;
}
Token* pop(Token* &stack)
{
	
	Token* temp=stack;
	if (stack!=NULL)
	stack=stack->getLink();
	else
	return NULL;
	return temp;
}

void displayStack(Token* stack)
{
	while(stack!=NULL)
	{
		cout<<stack->getChar()<<endl;
		stack=stack->getLink();
	}
}

int main()
{
	Token *stack=NULL;
	char x[10];


	cin.getline(x,10);
	int i=0;
	while(x[i]!='\0')
	{
		push(stack, new Token(x[i]));
		i++;
	}
	
	displayStack(stack);
	
	string rev;
	
	while(stack!=NULL)
	{
		rev+=(*pop(stack)).getChar();
	}
	cout<<rev<<endl;

	
	return 0;
}
