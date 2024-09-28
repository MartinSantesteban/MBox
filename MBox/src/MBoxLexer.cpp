#include "./MBoxLexer.h"
using namespace std;

MBoxLexer::MBoxLexer(string source){
	src_code = source;
}

vector<Token> MBoxLexer::scan(){
	while(!isAtEnd()){
		start = current;
		scanToken();
	}
	return tokens;
}

bool MBoxLexer::isAtEnd(){
	return current == src_code.size();
}

void MBoxLexer::scanToken(){
	char current_char = src_code[start];
	char next_char = src_code[current+1]; 
	switch(current_char){
		case ' ':
			current++;
			break;
		case '\n':
			addToken(start, current, END_OF_LINE);
			line++;
			break;
		case '(':
			addToken(start, current, L_PAREN);
			break;
		case ')':
			addToken(start, current, R_PAREN);
			break;
		case '{':
			addToken(start, current, L_BRACE);
			break;
		case '}':
			addToken(start, current, R_BRACE);
			break;
		case '+':
			addToken(start, current, PLUS);
			break;
		case '-':
			addToken(start, current, MINUS);
			break;
		case '*':
			addToken(start, current, STAR);
			break;
		case '/':
			addToken(start, current, SLASH);
			break;
		case ',':
			addToken(start, current, COMMA);
			break;
		case ';':
			addToken(start, current, SEMICOLON);
			break;
		case ':':
			addToken(start, current, DOTS);
			break;			
		case '.':
			addToken(start, current, DOT);
			break;
		case '!':
			if(current != src_code.size() && next_char == '='){
				addToken(start, ++current, BANG_EQUAL); //ver si anda con current + 1
			}else{
				addToken(start, current, BANG);
			}
			break;
		case '<':
			if(current != src_code.size() && next_char == '='){
				addToken(start, ++current, LESS_EQUAL);
			}else{
				addToken(start, current, LESS);
			}
			break;
		case '>':
			if(current != src_code.size() && next_char == '='){
				addToken(start, ++current, GREATER_EQUAL);
			}else{
				addToken(start, current, GREATER);
			}
			break;
		case '=':
			if(current != src_code.size() && next_char == '='){
				addToken(start, ++current, EQUAL_EQUAL);
			}else{
				addToken(start, current, EQUAL);
			}
			break;
		case '"':
			current++;
			while(src_code[current] != '"')	current++;
			addToken(start, current, STRING);
			break;
		default:
			if(scanNumber()) break;
			scanKeyword();
			break;
	}
	return;
}

void MBoxLexer::addToken(int start, int end, tokenType t){
	string s = src_code.substr(start, end - start + 1);
	if(t == END_OF_LINE) s = "/n"; 
	//cout << Token(t,s,line) << endl;
	tokens.push_back(Token(t,s,line));
	current++;
}

int MBoxLexer::scanNumber(){
	bool dotted = false;
	while(current < src_code.size() && isdigit(src_code[current])) current++;
	int len = current - start;
	if(len > 0){
		if(src_code[current] == '.'){
			dotted = true;
			current++;
			while(isdigit(src_code[current])) current++;
		}
		current--;
		int aux = start;
		while(len > 1 && src_code[aux] == '0') aux++;

		int aux2 = current;
		while(len > 1 && dotted && src_code[aux2] == '0') aux2--;
		
		addToken(aux, aux2, NUMBER);
		return 1;
	}
	return 0;
}

void MBoxLexer::scanKeyword(){
	// como ya scaneaste los numeros, nunca empezas chequeando por uno de ellos.
	while(current < src_code.size() && (isalpha(src_code[current]) || isdigit(src_code[current]))) current++;
	current--;
	string lexeme = src_code.substr(start, current - start + 1);
	if(lexeme.size() == 0) throw invalid_argument("[MBoxLexer] in line " + to_string(this->line) + ": Invalid character encountered.");
	// 	cout << lexeme << endl;
	if(auto f = keywords.find(lexeme); f != keywords.end()){
		addToken(start, current, keywords.at(lexeme));
	}else{
		addToken(start, current, IDENTIFIER);
	}
	return;
}
