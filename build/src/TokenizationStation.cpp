#include "TokenizationStation.h"
#include "Functions.h"

using namespace std;

TokenizationStation::TokenizationStation(){
	cout << "Welcome to the Tokenization Station!" << endl << endl;
}

int main(int argc, char *argv[]){
	Functions func;

	string lookupToken = "";

	srand(time(NULL));

	string cmd = string(argv[1]);
	if(argc >= 2){
		if(cmd.compare("generateTokens") == 0){
			if(argc == 3){
				func.loadData(string(argv[2]));
				func.dumpDBContents();
			}else{
				cout << "Please supply the db file name when running the generateTokens command." << endl;
			}
		}else if(cmd.compare("detokenize") == 0){
			if(argc == 3){
				cout << "detokenizing..." << endl;
				string foundVal = func.detokenizeData(string(argv[2]));

				cout << "PAN = " << foundVal << endl;
			}else{
				cout << "Please use format detokenize token" << endl;
			}
		}else if(cmd.compare("tokenize") == 0){
			if(argc == 3){
				cout << "tokenizing..." << endl;
				string token = func.tokenizeData(8, string(argv[2]), 2);

				cout << "Generated Token : " << token << endl;
			}else{
				cout << "Please use format tokenize token" << endl;
			}
		}
	}else{

		cout << "Please enter a command." << endl;
	}

	return 1;
}