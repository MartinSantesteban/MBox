#include "./MBox.h"

int MBox::scan(int argc, const char *args[]){
	if(argc > 2){
		cout << "USAGE: MBox <path of lox sourcefile>" << endl; 
		return -1;
	}else if(argc == 2){
		return runFile(args[1]);
	}else{
		return runPrompt();
	}
}		

bool MBox::codeHadError(){
	return had_error;
}

string MBox::error(int line, string message){ // este se volvio public solo para poder testear
	return report(line, "", message);
}

int MBox::runFile(const char *filepath){
	//auto *file = fopen(filepath, "r");
	ifstream o(filepath);
	if(o.fail()){
		cout << "File not in directory!" << endl;
		return -1;
	}
	stringstream strStream;
	strStream << o.rdbuf();
	run(strStream.str());
	if(had_error) return -1;
	return 0;
}

int MBox::runPrompt(){
	//REPL = Read line of Input - Evaluate - Print - Loop
	string input; 
	cout << "--------------- MBox REPL ---------------" << endl;
	while(true){
		cout << ">> " ;
		string input;
		getline(cin, input);
		if(input == ":q" ){
			cout << "Exiting MBox" << endl;
			break;
		}
		run(input);
		cout << endl;
		had_error = false;
	}
	return 0;
}

void MBox::run(string src){
	MBoxLexer l(src);
	vector<Token> tokens = l.scan();
	cout << endl;
	MBoxParser p(tokens);
	vector<Stmt*> program_statements = p.parseProgram();
	MBoxInterpreter i;
	cout << "Result of execution: ";
	i.interpretProgram(program_statements);
}


string MBox::report(int line, string where, string message){
	string res = "[line " + to_string(line) + "] Error" + where + ": " + message;
	cout << res << endl;
	this->had_error = true;
	return res;
}


		

