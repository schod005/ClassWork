#ifndef TOKEN_H
#define TOKEN_H

class Token
{
	public:
	Token(){next=NULL;}
	Token(char c){next=NULL; tchar = c;}
	char getChar(){return tchar;}
	Token* getLink(){return next;}
	void setChar(char);
	void setLink(Token*);

	
	
	private:
	char tchar;
	Token * next;
	
	
	
	
};



#endif
