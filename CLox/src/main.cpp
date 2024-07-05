#include<iostream>
#include<vector>
#include<string>
#include<map>

#include "../src/AST.h"
#include "../src/visitor.h"
#include "../src/token.h"


using namespace std;

int main(){
	Token t(STRING, "SFD", 0);
	Literal l(&t);
	Grouping g(&l);
	auto g2 = g;
	Token tb(PLUS, "+", 0);
	Binary b(&g,&tb,&g2);
	cout << "todo bien" << endl;
	return 0;
}
