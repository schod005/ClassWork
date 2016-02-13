#ifndef TEXT_H
#define TEXT_H
using namespace std;
#include <string>

class Text
{
	public:
		Text();
		Text(string);
		Text(const Text&);
		~Text();
		int getcnt(){return wordcnt;}
		Text& operator = (const Text&);
		friend ostream & operator <<(ostream &, Text &);
		friend Text operator +(const Text&, const Text&);

		friend Text operator +(const Text&, const char*);
		friend Text operator +(const Text&, string);


	private:
		string* txtarray;
		int wordcnt;

};



#endif
