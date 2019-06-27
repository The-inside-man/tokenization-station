#include "functions.h"

Functions::Functions(){
	// std::cout << "Created functions object!" << std::endl;
}

std::string Functions::tokenizeData(int binLength, std::string panValue){

	std::string bin = panValue.substr(0, binLength);
	std::string token = panValue.substr(binLength);

	std::string tokenStr = bin;

	int success = 0;

	while(!success){
		for(char c: token){
			/*Convert each char to Binary*/
			std::string tmp = a_to_b(c);

			int rndVal = rand() % 25 + 1;

			int num = b_to_a(tmp);

			std::string x = Functions::chars[rndVal%num];

			tokenStr += x;
		}


		success = Functions::addToDB(tokenStr, panValue);
	}

	return tokenStr;
}

std::string Functions::detokenizeData(std::string token){
	std::map<std::string, std::string>::iterator it;

	it = this->dbMap.find(token);

	if(it == this->dbMap.end()){
		return "NO TOKEN FOUND";
	}

	return it->second;
}

std::map<std::string, std::string> Functions::loadData(std::string dbName){

	std::map<std::string, std::string> dbMap;

	std::fstream fin;

	fin.open(dbName, std::ios::in);

	std::vector<std::string> row;
	std::string line, word, temp;

	while(!fin.eof()){
		row.clear();

		std::getline(fin, line);
		std::stringstream ss(line);

		while(getline(ss, word, ',')){
			row.push_back(word);
		}

		if(row.size() == 2){
			Functions::addToDB(row[0], row[1]);
			dbMap.insert(std::pair<std::string, std::string>(row[0], row[1]));
		}else{
			std::cout << "[ERROR] - Unable to read data from csv file." << std::endl;
		}

	}

	fin.close();

	return dbMap;
}

/*	Function to convert ascii values
	to binary string */
std::string Functions::a_to_b(int n){
	int result = 0, m = 1, remainder;
    while (n > 0) {
        remainder = n % 2;
        result = result + (m * remainder);
        n = n / 2;
        m = m * 10;
    }
	std::string num = std::to_string(result);
	while (num.length() < 8){
		num.insert(num.begin(),'0');
	}
	
	return num;
}

/* 	Takes an 8 bit input string 
	and returns the numerical 
	ascii value */
int Functions::b_to_a(std::string bits){
	int i = 0;
	int ctr = 7;
	int accum = 0;
	if(bits.length() != 8) exit(1); // Confirms 8 bit length of bitstring
	for(i = 0; i < 8; i ++){
		std::string str;
		str.push_back(bits[i]);
		int tmp = stoi(str);
		if(tmp == 0){
			ctr--;
		} else if(tmp == 1){
			accum += pow(2,ctr);
			ctr--;
		}
	}
	return accum;
}

int Functions::addToDB(std::string token, std::string sData){

	try{
		std::map<std::string, std::string>::iterator it;
		std::map<std::string, std::string>::iterator itr;

		it = this->dbMap.find(token);
		itr = this->dbMap.find(sData);

		if(it == this->dbMap.end()){
			this->dbMap.insert(std::pair<std::string, std::string>(token, sData));
		}else{
			return 0;
		}
	}catch(const std::exception& e){
		std::cout << e.what() << std::endl;
	}

	std::cout << "[INFO] - Successfully added " << token << " to the database." << std::endl;
	return 1;
}

void Functions::dumpDBContents(){
	std::map<std::string, std::string>::iterator it;
	std::cout << "[DUMP] - Database dump..." << std::endl;
	for(it = this->dbMap.begin(); it != this->dbMap.end(); it++){
		std::cout << it->first << " : " << it->second << std::endl;
	}

}
