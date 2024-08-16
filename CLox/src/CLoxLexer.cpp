#include "./CLoxLexer.h"
using namespace std;

CLoxLexer::CLoxLexer(string source){
	src_code = source;
}

vector<Token> CLoxLexer::scan(){
	while(!isAtEnd()){
		start = current;
		scanToken();
	}
	return tokens;
}

bool CLoxLexer::isAtEnd(){
	return current == src_code.size();
}

void CLoxLexer::scanToken(){
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

void CLoxLexer::addToken(int start, int end, tokenType t){
	string s = src_code.substr(start, end - start + 1);
	if(t == END_OF_LINE) s = "/n"; 
	//cout << Token(t,s,line) << endl;
	tokens.push_back(Token(t,s,line));
	current++;
}

int CLoxLexer::scanNumber(){
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

void CLoxLexer::scanKeyword(){
	// como ya scaneaste los numeros, nunca empezas chequeando por uno de ellos.
	while(current < src_code.size() && (isalpha(src_code[current]) || isdigit(src_code[current]))) current++;
	current--;
	string lexeme = src_code.substr(start, current - start + 1);
	// 	cout << lexeme << endl;
	if(auto f = keywords.find(lexeme); f != keywords.end()){
		addToken(start, current, keywords.at(lexeme));
	}else{
		addToken(start, current, IDENTIFIER);
	}
	return;
}
