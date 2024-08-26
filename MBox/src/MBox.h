#ifndef MBOX_H
#define MBOX_H

#include "./MBoxLexer.h"
#include "./MBoxParser.h"
#include "./MBoxInterpreter.h"


class MBox {
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