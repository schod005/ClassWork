#include <iostream>
#include "Token.h"
using namespace std;

void Token::setChar(char x)
{
	tchar=x;
}

void Token::setLink(Token *x)
{
	next=x;
}

