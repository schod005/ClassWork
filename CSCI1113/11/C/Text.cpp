#include <iostream>
using namespace std;
#include <string.h>
#include "Text.h"



// destructor
Text::~Text()
{
	delete [] txtarray;
}

// copy constructor
Text::Text(const Text& rside)
{
	txtarray = new string[rside.wordcnt];
	wordcnt = rside.wordcnt;
	for(int i=0; i<wordcnt; i++)
		txtarray[i] = rside.txtarray[i];
}


// assignment operator
Text& Text::operator = (const Text& rside )
{
	if( this != &rside )
	{
		if(txtarray)
		delete [] txtarray;
		txtarray = new string[rside.wordcnt];
		wordcnt = rside.wordcnt;
		for(int i=0; i<wordcnt; i++)
			txtarray[i] = rside.txtarray[i];
	}
	return *this;
}

Text::Text()
{
	wordcnt = 0;
	txtarray=new string[0];
}

Text::Text(string a)
{
    wordcnt = 1;
    int i=0;
    for(int i=0;i<a.size();i++)
    {
        if(isspace(a[i]))
            wordcnt++;
    }
	txtarray=new string[wordcnt];
	*txtarray=a;
}


ostream & operator <<(ostream &a, Text &b)
{
	int i=0;
	while(b.txtarray!=NULL)
	{
		cout<<b.txtarray[i]<<' ';
		i++;
	}
	return a;
}

Text operator +(const Text& a, const Text& b)
{
	Text c;
	c.txtarray=new string[a.wordcnt+b.wordcnt];
	for(int i=0;i<a.wordcnt;i++)
	c.txtarray[i]=a.txtarray[i];
	for(int i=0;i<b.wordcnt;i++)
    c.txtarray[i+a.wordcnt]=b.txtarray[i];
	return c;
}

Text operator +(const Text &a, string c)
{
    Text b;
    for(int i=0;i<a.wordcnt;i++)
    b.txtarray[i]=a.txtarray[i];
    b.txtarray[a.wordcnt+1]=c;
    return b;
    
}

Text operator +(const Text &a, const char* b)
{
	Text d;
	string c(b);
    for(int i=0;i<a.wordcnt;i++)
    d.txtarray[i]=a.txtarray[i];
    d.txtarray[a.wordcnt+1]=c;
    return d;	
	
	
}


