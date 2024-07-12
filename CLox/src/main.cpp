#include "./CLoxParser.h"

int main(){
	Token t(STRING, "SFD", 0);
	Literal l(&t);
	vector<Token> v();
	v.push_back(t);
	Parser p(v);
	cout << typeid(p.parse()) << endl;
	return 0;
}
