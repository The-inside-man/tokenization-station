
//////////////////////////////////////////////////////////
//Name:		Jacob Brown									//	
//Title:	functions							 		//
//Date:		27 June 2019								//
//////////////////////////////////////////////////////////

#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <iostream>
#include <iomanip>
#include <map>
#include <algorithm>
#include <string>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <fstream>
#include <vector>

class Functions{
	
private:

	/* Characters Array for Quick HASH method*/
	std::string chars [26]= {	"A","B","C","D","E","F","G","H","I",
								"J","K","L","M","N","O","P","Q","R",
								"S","T","U","V","W","X","Y","Z"};

	/* Map to act as DB */
	std::map<std::string, std::string> dbMap;

	/* Converts ASCII to Binary */
	std::string a_to_b(int);

	/* Converts Binary string to Char int value*/
	int b_to_a(std::string);

public:

	/*
	 * constructor
	 */
	Functions();

	/*
	 * Tokenize Data
	 * 
	 * int -> Value of how many bytes to preserve starting at position 0
	 * string -> The data value to tokenize
	 * 
	 * Note -> The preserved values are used to preserve the BIN to allow for legacy routing
	 */
	std::string tokenizeData(int binLength, std::string panValue);

	/*
	 * Tokenize Data
	 * 
	 * string -> The data value to detokenize
	 * 
	 * Note -> Data is retrieved from the database and in the format:
	 *
	 *	Key: {Name: DataAtRestDB, {key:12345678HWTFJSWORF; value: OKHID&S%WHS^#D(YW@)}}
	 *
	 *	The return value will be the Sensitive Data (PAN)
	 *
	 */
	std::string detokenizeData(std::string token);


	/*
	 * Load Database in Memory
	 *
	 * string -> The name of the database to read in
	 */
	std::map<std::string, std::string> loadData(std::string databaseName);


	/*
	 * Add the pair into database
	 *
	 *	token (string)
	 *  sData (string) -> The PAN
	 */
	int addToDB(std::string token, std::string sdata);

	/*
	 * Dump comntents of the Database
	 *
	 */
	void dumpDBContents();

};

#endif

