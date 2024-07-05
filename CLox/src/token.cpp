#include "./token.h"
using namespace std;

Token::Token(tokenType tp,string lex,int l){
    this->token_type = tp;
    this->lexeme = lex;
    this->line = l;
}

Token::Token(const Token &t){
    this->token_type = t.token_type;
    this->lexeme = t.lexeme;
    this->line = t.line;
} //copy constructor

Token::Token() = default; //default constructor para poder pasar token como param.

bool Token::operator<(const Token& t) const{	
    return true;
}

bool Token::operator ==(const Token& t) const{
    return (this->token_type == t.token_type && 
            this->lexeme == t.lexeme &&
            this->line == t.line);
}

//friend...como está funcionando esto?
ostream& operator<< (ostream &out, const Token& t){
    out << "[ " <<  tokenTypeString[t.token_type] << " | " << ((t.lexeme == "\n")? "/n" : t.lexeme) << " | " << t.line << " ]";
    return out;
}

