#include "./CLox.h"

int CLox::scan(int argc, const char *args[]){
	if(argc > 2){
		cout << "USAGE: clox <path of lox sourcefile>" << endl; 
		return -1;
	}else if(argc == 2){
		return runFile(args[1]);
	}else{
		return runPrompt();
	}
}		

bool CLox::codeHadError(){
	return hadError;
}

string CLox::error(int line, string message){ // este se volvio public solo para poder testear
	return report(line, "", message);
}

int CLox::runFile(const char *filepath){
	//auto *file = fopen(filepath, "r");
	ifstream o(filepath);
	if(o.fail()){
		cout << "File not in directory!" << endl;
		return -1;
	}
	stringstream strStream;
	strStream << o.rdbuf();
	run(strStream.str());
	if(hadError) return -1;
	return 0;
}

int CLox::runPrompt(){
	//REPL = Read line of Input - Evaluate - Print - Loop
	string input; 
	cout << "--------------- CLox REPL ---------------" << endl;
	while(true){
		cout << ">> " ;
		string input;
		getline(cin, input);
		if(input == ":q" ){
			cout << "Exiting clox" << endl;
			break;
		}
		run(input);
		cout << endl;
		hadError = false;
	}
	return 0;
}

void CLox::run(string src){
	CLoxLexer l(src);
	vector<Token> tokens = l.scan();
	cout << endl;
	CLoxParser p(tokens);
	Expr* ast = p.parse();
	CLoxInterpreter i;
	cout << "Result of execution: ";
	i.printFormatedInterpretation(*ast);
}


string CLox::report(int line, string where, string message){
	string res = "[line " + to_string(line) + "] Error" + where + ": " + message;
	cout << res << endl;
	this->hadError = true;
	return res;
}


		

