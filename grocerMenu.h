#pragma once //tells the linker to only try to add this header once, and prevent linking issues
#include <iostream> 
#include <fstream> 
#include <map> 
#include <sstream>
#include <string>
#include <iomanip>
#include <vector>
#include <cstdio>
#include <cstring>

using namespace std;

class grocerMenu {
private:
	//standard int variables below
	int temp;

	int tempInt;

	int tempHisto;
	

	//standard string variables below
	string holdingString;

	string unalteredString;

	string holdingStringMap;
	
	string localString;

	string tempMapString;


	//objects below for data storage and file handling
	vector<string> wordList;

	vector<string> loweredWord;

	vector<int> wordOccur;

	map <string, int> wordCounter;

	map<string, int>::iterator slide = wordCounter.begin();

	ifstream inPutFile;

	fstream outPutFile;
public:
	//integer variable getters and setters below
	void setInt(int tempNumber);
	int& getInt();
	void setTempInt(int tempNumber);
	int& getTempInt();
	void setTempHisto(int tempNumber);
	int& getTempHisto();

	//string variable getters and setters below
	void setHoldingString(string tempWord);
	string& getHoldingString();
	void setUnalteredString(string tempWord);
	string& getUnalteredString();
	void setHoldingStringMap(string tempWord);
	string& getHoldingStringMap();





	//all necessary methods below
	void initialMenu(); //que's up the necessary method to intake and load the given file and then direct to selection menu
	void populateVec(); 
	void populateMap();
	void printQuants();
	void printHistogram();
	void screenDecorator();
	void menuSelection();
	void itemLookUp();

};
