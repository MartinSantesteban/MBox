#ifndef ENUMS_AND_MAPS_H
#define ENUMS_AND_MAPS_H

#include<map>
#include<string>
#include<vector>
#include<typeinfo>
#include<any>
#include<functional>
#include <stdexcept>
#include<iostream>
#include<cstdlib>
#include<sstream>
#include<fstream>

using namespace std;


enum tokenType {
	// Single character token types (){}+-*/,;.
	L_PAREN, R_PAREN, L_BRACE, R_BRACE, PLUS, MINUS, STAR, SLASH, COMMA, SEMICOLON, DOT,
	// Two character token
	BANG, BANG_EQUAL, EQUAL, EQUAL_EQUAL, GREATER, GREATER_EQUAL, LESS, LESS_EQUAL, 
	// Literals
	IDENTIFIER, STRING, NUMBER,
	// Keywords
	AND, CLASS, ELSE, FALSE, FUN, FOR, IF, NIL, OR, PRINT, RETURN, SUPER, THIS, TRUE, VAR, WHILE, END_OF_LINE
};

extern const string tokenTypeString[];

extern const map<string,tokenType> keywords;

#endif