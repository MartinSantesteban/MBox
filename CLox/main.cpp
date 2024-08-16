#include "./src/CLox.h"

int main(int argc, const char** argv){
	CLox cl;
	return cl.scan(argc, argv);
}