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
		int start = 0;
		int current = 0;
		int line = 0;

		bool isAtEnd();
		void scanToken();
		void add_token(int start, int end, tokenType t);
		int scan_number();
		void scan_keyword();
};

#endif
