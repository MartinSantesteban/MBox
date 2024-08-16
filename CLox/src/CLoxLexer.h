#ifndef CLOX_LEXER_H
#define CLOX_LEXER_H

#include "./enums_and_maps.h"
#include "./token.h"

class CLoxLexer {
	public:
		CLoxLexer(string source);
		vector<Token> scan();

	private:
		string src_code;
		vector<Token> tokens;
		unsigned int start = 0;
		unsigned int current = 0;
		unsigned int line = 0;

		bool isAtEnd();
		void scanToken();
		void addToken(int start, int end, tokenType t);
		int scanNumber();
		void scanKeyword();
};

#endif
