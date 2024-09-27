#ifndef TOKEN_H
#define TOKEN_H

#include "./enums_and_maps.h"

class Token{
    public:
        Token(tokenType tp,string lex,int l);
        Token(const Token &t);
        Token();
        bool operator<(const Token& t) const;
        bool operator ==(const Token& t) const;
        friend ostream& operator<< (ostream &out, const Token& t);
    // al ser clases bastante anemicas no hago privados los miembros. Debería hacerlos const!!!
        tokenType token_type; 
        string lexeme;  
        int line;
};

#endif