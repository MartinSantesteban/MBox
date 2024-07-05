#include "./enums_and_maps.h"

const string tokenTypeString[] = {
	// Single character token types (){}+-*/,;.            <- fijate que estos son independientes de todos los demas operadores
	"L_PAREN", "R_PAREN", "L_BRACE", "R_BRACE", "PLUS", "MINUS", "STAR", "SLASH", "COMMA", "SEMICOLON", "DOT",
	// Two character token types or dependant single types <- siempre que te encontras un !, tenes que chequear si el siguiente es un =. ! = no funca.
	"BANG", "BANG_EQUAL", "EQUAL", "EQUAL_EQUAL", "GREATER", "GREATER_EQUAL", "LESS", "LESS_EQUAL", 
	// Literals
	"IDENTIFIER", "STRING", "NUMBER",
	// Keywords           
	"AND", "CLASS", "ELSE", "FALSE", "FUN", "FOR", "IF", "NIL", "OR", "PRINT", "RETURN", "SUPER", "THIS", "TRUE", "VAR", "WHILE", "END_OF_LINE"
};

const map<string,tokenType> keywords = {{"and", AND},{"class", CLASS},{"else", ELSE},{"false", FALSE},{"fun", FUN},{"for", FOR},{"if", IF},
								  {"nil", NIL},{"or", OR},{"print", PRINT},{"return", RETURN},{"super", SUPER},{"this", THIS},{"tre", TRUE},{"var", VAR},{"while", WHILE}};

