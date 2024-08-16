#ifndef CLOX_H
#define CLOX_H

#include "./CLoxLexer.h"
#include "./CLoxParser.h"
#include "./CLoxInterpreter.h"


class CLox {
	public:
		int scan(int argc, const char *args[]);		
		bool codeHadError();
		string error(int line, string message);

	private:
		int runFile(const char *filepath);
		int runPrompt();
		void run(string src);
		string report(int line, string where, string message);
		bool had_error = false;
};

#endif