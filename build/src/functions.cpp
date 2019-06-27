#include "functions.h"

Functions::Functions(){
	// std::cout << "Created functions object!" << std::endl;
}

std::string Functions::tokenizeData(int binLength, std::string panValue, int v){

	std::string bin = panValue.substr(0, binLength+1);
	std::string token = panValue.substr(binLength+1);

	std::string tokenStr;

	int success = 0;

	while(!success){
		tokenStr = bin;
		for(char c : token){

			int rndVal = rand() % 25 + 1;

			std::string x = Functions::chars[rndVal%int(c)];

			tokenStr.append(x);
		}


		success = Functions::addToDB(tokenStr, panValue, v);
	}

	return tokenStr;
}

std::string Functions::detokenizeData(std::string token){
	std::map<std::string, std::string>::iterator it;
	this->dbMap = Functions::loadLookupData();

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

		Functions::addToDB(Functions::tokenizeData(8, line, 1), line, 1);
		dbMap.insert(std::pair<std::string, std::string>(Functions::tokenizeData(8, line, 1), line));

	}

	fin.close();

	return dbMap;
}

std::map<std::string, std::string> Functions::loadLookupData(){

	std::map<std::string, std::string> dbMap;

	std::fstream fin;

	fin.open("lookup.db", std::ios::in);

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
			dbMap.insert(std::pair<std::string, std::string>(row[0], row[1]));
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

int Functions::addToDB(std::string token, std::string sData, int v){

	try{
		std::map<std::string, std::string>::iterator it;

		it = this->dbMap.find(token);

		if(it == this->dbMap.end()){
			this->dbMap.insert(std::pair<std::string, std::string>(token, sData));
		}else{
			return 0;
		}
	}catch(const std::exception& e){
		std::cout << e.what() << std::endl;
	}

	std::cout << std::setw(30) << "[INFO] - Successfully added " << std::left << std::setw(20) << token << " to the database." << std::endl;
	Sleep(50);
	if(v == 2)
		Functions::dumpDBContents();

	return 1;
}

void Functions::dumpDBContents(){
	std::map<std::string, std::string>::iterator it;
	std::cout << "-----------------------------------------------------" << std::endl;
	std::cout << "-----------------------------------------------------" << std::endl;
	std::cout << "[DUMP] - Database dump..." << std::endl;
	std::cout << "-----------------------------------------------------" << std::endl;
	std::cout << "-----------------------------------------------------" << std::endl;

	std::fstream fout, fout2;

	fout.open("tokens.db", std::ios::out | std::ios::app);
	fout2.open("lookup.db", std::ios::out | std::ios::app);

	for(it = this->dbMap.begin(); it != this->dbMap.end(); it++){
		std::cout << std::left << std::setw(25) << it->first << "<TKN> : <PAN> " << std::right << std::setw(25) << it->second << std::endl;
		fout << it->first << std::endl;
		fout2 << it->first << "," << it->second << std::endl;
		Sleep(50);
	}

	fout.close();
	fout2.close();
}
