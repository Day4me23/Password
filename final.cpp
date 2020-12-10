/*--------------------------------------------------------------------*/
/*  Author: Dayne Farris
/*  Date: 11/27/2020
/*  Assignment: Final Project
* Vulnerabilities:
/*--------------------------------------------------------------------*/

#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include<string>
#include<conio.h>
#include<vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Funtion Prototypes
void validation();
void displayLine(vector<string> data);
void viewLine(vector<string> data, int fileLine);
void editLine(vector<string> data, int fileLine);
void addLine(vector<string> data, int fileLine);
void saveAndEncodeFile(vector <string> data);
void exitProgram();
vector<string> readFile(string, vector<string>, ifstream&, string userIn);
vector<string>split(const string& s, char delim);
void getDescriptionByValue(vector<string> data, int fileLine);
string process(string const& s);
void getDescriptions(vector<string> data);
void displayOptions();
void fileData(string desc, string userName, string passWord, string notes);
string getFullLine(vector<string> data, int fileLine);
vector<string> newEdit(vector<string> data, int fileLine);
vector<string> newAdd(vector<string> data, int fileLine);
vector<string> encode1(vector<string> decodedData, bool encode3);
void saveFile(vector<string> encodedVector, string userIn);
vector<string> decode1(vector<string> data);
vector<string> encode2(vector<string> decodedData, bool encode3);
vector<string> encodeCharSwap(vector<string> data);
vector<string> decode2(vector<string> data);
vector<string> encode3(vector<string> data);
vector<string> decode3(vector<string> data);

//Encode level 1 alterations
const int FIRST_ALTERATION = 3;
const int SECOND_ALTERATION = 5;
//Encode level 2 alterations
const int THIRD_ALTERATION = 4;
const int FOURTH_ALTERATION = 3;


int main() {
	char option;
	
		string userIn;
		ifstream inputFile;
		char line;
		int fileLine = 0;
		
		int lineCounter = 0;
		string strFile; //File name
		vector<string> data;
		vector<string> decodedData;
		bool isRunning = true;

		cout << "Enter the name of the input file: " << '\t';
		getline(cin, userIn);
		cout << userIn;
		cout << endl;
		data = readFile(strFile, data, inputFile, userIn);
		string encodelevel = data[0];

		if (encodelevel == "E1;")
		{
			decodedData = decode1(data);
		}
		else if (encodelevel == "E2;")
		{
			decodedData = decode2(data);
		}
		else if (encodelevel == "E3;")
		{
			decodedData = decode3(data);
		}
		else if (encodelevel == "E0;")
		{
			for (int j = 0; j < 11; j++)
			{
				if (j != 0)
				{
					decodedData.push_back(data[j]);
				}
			}
		}
		//decodedData = decode1(data);
		getDescriptions(decodedData);
		
		displayOptions();
		do {
		do {
			cin >> option;
			option = toupper(option);
			cout << endl;
			if (isdigit(option)) {
				cout << "recieved a numeric value when unexpected. Please select an available option listed below." << endl;
			}
			else if (isalpha(option)) {
				if (option == 'D' || option == 'V' || option == 'E' || option == 'A' || option == 'S' || option == 'X') {
					break;
				}
				else {
					cout << "An unexpected character was entered. Please select an available option listed above." << endl;
				}
			}
		} while (option != 'D' || option != 'V' || option != 'E' || option != 'A' || option != 'S' || option != 'X');

		switch (option) {
		case 'D':
			displayLine(decodedData);
			break;
		case 'V':
			viewLine(decodedData, fileLine);
			break;
		case 'E':
			editLine(decodedData, fileLine);
			break;
		case 'A':
			addLine(decodedData, fileLine);
			break;
		case 'S':
			saveAndEncodeFile(decodedData);
			break;
		case 'X':
			cout << "Thank you for using this program." << endl;
			return 0;
			

		default: // if no selection matches we default this statement. This should be unreachable.
			cout << "No selection chosen exists. Please select a value shown listed. " << endl;
		} // end switch

		while (inputFile >> line) {
			inputFile >> noskipws;
			if (line != ';') {
				cout << line;
			} // end if
			else if (line == ';') {
				cout << endl;
			} // end else if
		} // end while
	} while (option != 'x');
	
} // end main


void validation() {
	// Dont need I dont think yet....
} // end validation

void displayLine(vector<string> data) {
	getDescriptions(data);
	displayOptions();
} // end displayLine

void viewLine(vector<string> data, int fileLine) {
	do {
		cout << "Which description would you like to see? (Values 1-10) " << endl;
		cin >> fileLine;
		cout << endl;
		//-----------------------------------------------------------------------------------NEED VALIDATION UPDATE
	} while (!fileLine > 1 && fileLine < data.size());
	getFullLine(data, fileLine);

	

	displayOptions();
} // end viewLine

void editLine(vector<string> data, int fileLine) {
	do {
		cout << "Enter line number you wish to edit:" << endl;
		cin >> fileLine;
		cout << endl;
		//-----------------------------------------------------------------------------------NEED VALIDATION UPDATE
	} while (!fileLine > 1 && fileLine < data.size());
	//getDescriptionByValue(data, fileLine);
	getFullLine(data, fileLine);
	
	cout << "WARNING: You cannot use semi-colons in these fields. Any semicolons entered will be removed." << endl << endl;

	data = newEdit(data, fileLine);
	displayOptions();
} // end editLine

void addLine(vector<string> data, int fileLine) {
	cout << "WARNING: You cannot use semi-colons in these fields. Any semicolons entered will be removed." << endl << endl;
	// pushback
	data = newAdd(data, fileLine);
	displayOptions();
} // end addLine



void saveAndEncodeFile(vector <string> decodedData) {
	int encodeLevel;
	vector<string> encodedVector;
	string userIn;
	cout << "Enter file name: " << endl;
	cin >> userIn;
	cout << endl;
	cout << "Enter encoding level <0, 1, 2, or 3>" << endl;
	cin >> encodeLevel;
	cout << endl;
	
	bool encode = false;

	switch (encodeLevel) {
	case 1:
		//encodeLevel = encodeLevel + ';';
		encodedVector = encode1(decodedData, encode);
		saveFile(encodedVector, userIn);
		break;
	case 2:
		//encodeLevel = encodeLevel + ';';
		encodedVector = encode2(decodedData, encode);
		saveFile(encodedVector, userIn);
		break;
	case 3:
		encodedVector = encode3(decodedData);
		saveFile(encodedVector, userIn);
		break;

	case 0:
		decodedData.insert(decodedData.begin(), "E0;");
		saveFile(decodedData, userIn);
		break;

	default: 
		cout << "No selection chosen exists. Please select a value shown listed. " << endl;
	} // end switch

	
	displayOptions();
} // end saveAndEncodeFile

void exitProgram() {
	// Also might not be needed.....
} // end exitProgram

vector<string> readFile(string strFile, vector<string> data, ifstream& inputFile, string userIn) //Read the file into the vector 
{
	string inputString;
	string line;
	inputFile.open(userIn);
	while (getline(inputFile, line))
	{
		vector<string> columns = split(line, '\n');
		
		data.push_back(line);
	} // end while
	inputFile.close();
	
	return data;
} // end readFile
vector<string>split(const string& s, char delim = ',')
{
	vector<string> elems;
	stringstream ss(s);
	string item;
	while (getline(ss, item, delim))
	{
		elems.push_back(item);
	} // end while
	return elems;
} // end split
void getDescriptionByValue(vector<string> data, int fileLine) {
	
	string fullLine = data.at(fileLine - 1);
	string splitLine = process(fullLine);
	cout << splitLine;

} // end getDescriptionByValue

string process(string const& s)
{
	string::size_type pos = s.find(';');
	if (pos != string::npos)
	{
		return s.substr(0, pos);
	} // end if
	else
	{
		return s;
	} // end else
} // end process

void getDescriptions(vector<string> data) { // gathering line info from vector
	int counter = 1; // counter to track current line in console
	for (int i = 0; i < data.size(); i++) {
		string fullRow = data.at(i);
		string firstDeclaration = process(fullRow);
		cout << counter++ << "." << '\t' << firstDeclaration << endl;
		}
	cout << endl; // whitespace between list 10/available options
} // end getDescriptions

void displayOptions() {
	cout << setw(25) << "AVAILABLE OPTIONS" << endl << endl;
	cout << "D - DISPLAY LINE DESCRIPTIONS" << endl;
	cout << "V - VIEW LINE DATA" << endl;
	cout << "E - EDIT LINE DATA" << endl;
	cout << "A - ADD LINE DATA" << endl;
	cout << "S - SAVE AND ENCODE FILE" << endl;
	cout << "X - EXIT PROGRAM" << endl << endl;
}

void fileData(string desc, string userName, string passWord, string notes) {
	cout << "Row Desc:" << '\t' << desc << endl;
	cout << "Username:" << '\t' << userName << endl;
	cout << "Password:" << '\t' << passWord << endl;
	cout << "Notes:" << '\t' << notes << endl << endl;
}
string getFullLine(vector<string> data, int fileLine) {
	string description;
	string userName;
	string passWord;
	string descLine;
	string userLine;
	string fullLine = data.at(fileLine - 1);
	for (int i = 0; i < 4; i++) {
		string::size_type pos = fullLine.find(';');
		if (pos != string::npos)
		{
			if (i == 0) {
				description = fullLine.substr(0, pos);
				cout << "Row Desc:"  << '\t' << fullLine.substr(0, pos) << endl;
				
			} // end if
			else if (i == 1) {				
				descLine = fullLine.substr(description.length() + 1);
				string::size_type pos = descLine.find(';');
				cout << "Username:" << '\t' << descLine.substr(0, pos) << endl;
				userName = descLine.substr(description.length(), pos);
			} // end else if
			else if (i == 2) {
				userLine = descLine.substr(userName.length() + 1);
				string::size_type pos = userLine.find(';');
				cout << "Password:" << '\t' << userLine.substr(0, pos) << endl;
				passWord = userLine.substr(0, pos);
			} // end else if
			else if (i == 3) {
				string test3 = userLine.substr(passWord.length() + 1);
				string::size_type pos = test3.find(';');
				cout << "Notes:" << '\t' << test3.substr(0, pos) << endl << endl;
				
			} // end else if
		} // end if
		else
		{
			return fullLine;
		} // end else
	} // end for
	
	return fullLine;
} // end getDescriptionByValue
vector<string> newEdit(vector<string> data, int fileLine) {
	string desc;
	string userName;
	string passWord;
	string notes;
	string finalString;
	string throwaway;
	char flag;
	
	do {
		getline(cin, throwaway);
		cout << "Enter a line description:" << endl;
		getline(cin, desc);
		desc.erase(remove(desc.begin(), desc.end(), ';'), desc.end());
		cout << "Enter a username:" << endl;
		getline(cin, userName);
		userName.erase(remove(userName.begin(), userName.end(), ';'), userName.end());
		cout << "Enter a password:" << endl;
		getline(cin, passWord);
		passWord.erase(remove(passWord.begin(), passWord.end(), ';'), passWord.end());
		cout << "Enter Notes:" << endl;
		getline(cin, notes);
		notes.erase(remove(notes.begin(), notes.end(), ';'), notes.end());
		cout << endl;
		cout << "You have entered:" << endl;
		fileData(desc, userName, passWord, notes);
		cout << "Is this the data you wish to add (Y/N)?" << endl;
		cin >> flag;
		cout << endl;
		flag = toupper(flag);
		if (flag == 'Y')
		{
			cout << "Line was updated." << endl << endl;
		}
		else if (flag != 'Y')
		{
			cout << "Line was not changed." << endl << endl;
		}
		
	} while (flag == 'N' || isdigit(flag));
	finalString = desc + ';' + userName + ';' + passWord + ';' + notes + ';';
	data[fileLine - 1] = finalString;
	return data;
}
vector<string> newAdd(vector<string> data, int fileLine) {
	string aDesc;
	string aThrowaway;
	string aUserName;
	string aPassWord;
	string aNotes;
	string aFinalString;
	char flag;
	do {
		getline(cin, aThrowaway);
		cout << "Enter a line description:" << endl;
		getline(cin, aDesc);
		aDesc.erase(remove(aDesc.begin(), aDesc.end(), ';'), aDesc.end());
		cout << "Enter a username:" << endl;
		getline(cin, aUserName);
		aUserName.erase(remove(aUserName.begin(), aUserName.end(), ';'), aUserName.end());
		cout << "Enter a password:" << endl;
		getline(cin, aPassWord);
		aPassWord.erase(remove(aPassWord.begin(), aPassWord.end(), ';'), aPassWord.end());
		cout << "Enter Notes:" << endl;
		getline(cin, aNotes);
		aNotes.erase(remove(aNotes.begin(), aNotes.end(), ';'), aNotes.end());
		cout << endl;
		cout << "You have entered:" << endl;
		fileData(aDesc, aUserName, aPassWord, aNotes);
		cout << "Is this the data you wish to add (Y/N)?" << endl;
		cin >> flag;
		cout << endl;
		flag = toupper(flag);
		if (flag == 'Y')
		{
			cout << "Line has been added." << endl << endl;
		}
		else if (flag != 'Y')
		{
			cout << "Line has not been added." << endl << endl;
		}
		
	} while (flag == 'N' || flag == 'n' || isdigit(flag));
	aFinalString = aDesc + ';' + aUserName + ';' + aPassWord + ';' + aNotes + ';';
	data.push_back(aFinalString);
	return data;
}

void saveFile(vector<string> encodedVector, string userIn)
{
	ofstream output_file(userIn);
	ostream_iterator<string> output_iterator(output_file, "\n");
	copy(encodedVector.begin(), encodedVector.end(), output_iterator);
	cout << "File save was successful!" << endl << endl;
}

vector<string> encode1(vector<string> data, bool encode3)
{
	char ch;
	int x = 0;
	string encodedMsg = "";
	vector<string> encodedVector;
	for (int j = 0; j < 10; j++)
	{
		encodedMsg = "";
		for (int i = 0; i < data[j].length(); i++) {
			ch = data[j][i];

			x = static_cast<int>(ch);
			if (x != 59) // check for semi colon
			{
				x = x - FIRST_ALTERATION;

				if (i % 2 != 0)
				{
					x = x + SECOND_ALTERATION;
				}
			}
			
			ch = static_cast<char>(x);

			encodedMsg += x;
			
		}  //  end for loop
		if (j == 0 && encode3 == false)
		{
			encodedVector.push_back("E1;");
		}
		encodedVector.push_back(encodedMsg);
	}
	
	return encodedVector;
}

vector<string> encode2(vector<string> data, bool encode3) {
	char ch;
	int x = 0;
	string encodedMsg = "";
	vector<string> encodedVector;
	data = encodeCharSwap(data);
	for (int j = 0; j < 10; j++)
	{
		encodedMsg = "";
		for (int i = 0; i < data[j].length(); i++) {
			ch = data[j][i];

			x = static_cast<int>(ch);
			if (x != 59)
			{
				x = x + THIRD_ALTERATION;

				if (x % 3 == 0)
				{
					x = x + FOURTH_ALTERATION;
				}
			}
			
			ch = static_cast<char>(x);

			encodedMsg += x;

		}  //  end for loop
		if (j == 0 && encode3 == false)
		{
			encodedVector.push_back("E2;");
		}
		else if (j == 0 && encode3 == true)
		{
			encodedVector.push_back("E3;");
		}
		encodedVector.push_back(encodedMsg);
	} // end for loop
	return encodedVector;
}

vector<string> encode3(vector<string> data) {
	vector<string> encodedVector1;
	vector<string> encodedVector2;
	bool encode3 = true;
	
	encodedVector1 = encode1(data, encode3);
	encodedVector2 = encode2(encodedVector1, encode3);
	
	return encodedVector2;
}

vector<string> encodeCharSwap(vector<string> data)
{
	string description;
	string descLine;
	string userName;
	string passWord;
	string userLine;
	string finalString;
	string passLine;
	string notes;
	
	for (int j = 0; j < 10; j++) {
		for (int i = 0; i < 4; i++) {
			string fullLine = data.at(j);
			string::size_type pos = fullLine.find(';');
			if (i == 0) {
				description = fullLine.substr(0, pos);
				iter_swap(description.begin(), description.rbegin());
				
			} // end if
			else if (i == 1) {
				descLine = fullLine.substr(description.length() + 1);
				string::size_type pos = descLine.find(';');				
				userName = descLine.substr(0, pos);
				iter_swap(userName.begin(), userName.rbegin());
				
			} // end else if
			else if (i == 2) {
				userLine = descLine.substr(userName.length() + 1);
				string::size_type pos = userLine.find(';');				
				passWord = userLine.substr(0, pos);
				iter_swap(passWord.begin(), passWord.rbegin());
				
			} // end else if
			else if (i == 3) {
				passLine = userLine.substr(passWord.length() + 1);
				string::size_type pos = passLine.find(';');
				notes = passLine.substr(0, pos);
				if (notes.length() > 2) {
					iter_swap(notes.begin(), notes.rbegin()); // swapper
				}
				finalString = description + ';' + userName + ';' + passWord + ';' + notes + ';';
				
			} // end else if
			
		}
		data[j] = (finalString);
	}
	return data;
}

vector<string> decode1(vector<string> data) {
	char ch;
	int x = 0;
	string decodedMsg = "";
	vector<string> decodedVector;

	for (int j = 0; j < 11; j++)
	{
		decodedMsg = "";
		for (int i = 0; i < data[j].length(); i++) {
			ch = data[j][i];

			x = static_cast<int>(ch) + FIRST_ALTERATION;

			if (i % 2 != 0)
			{
				x = x - SECOND_ALTERATION;
			}
			ch = static_cast<char>(x);

			decodedMsg += x;
		}  //  end for loop
		if (j != 0) {
			decodedVector.push_back(decodedMsg);
		}
	}
	return decodedVector;
}

vector<string> decode2(vector<string> data) {
	char ch;
	int x = 0;
	string encodedMsg = "";
	vector<string> encodedVector;
	
	for (int j = 0; j < 11; j++)
	{
		encodedMsg = "";
		for (int i = 0; i < data[j].length(); i++) {
			ch = data[j][i];
			x = static_cast<int>(ch);
			if (x % 3 == 0)
			{
				x = x - FOURTH_ALTERATION;
			}
			
			x = x - THIRD_ALTERATION;

			
			ch = static_cast<char>(x);

			encodedMsg += x;

		}  //  end for loop
		
		if (j != 0)
		{
			encodedVector.push_back(encodedMsg);
		}
		
	}
	data = encodeCharSwap(encodedVector);
	return data;
}

vector<string> decode3(vector<string> data)
{
	vector<string> decodedVector;
	vector<string> finalDecode;
	char ch;
	int x = 0;
	string encodedMsg = "";
	vector<string> encodedVector;

	for (int j = 0; j < 11; j++)
	{
		if (j != 0)
		{
			encodedVector.push_back(data[j]);
		}
	}
	
	//encodedVector.erase(encodedVector.begin());
	encodedVector = encodeCharSwap(encodedVector);
	//decode2
	for (int j = 0; j < 11; j++)
	{
		encodedMsg = "";
		for (int i = 0; i < data[j].length(); i++) {
			ch = data[j][i];
			
			x = static_cast<int>(ch);
			
			if (x % 3 == 0)
			{
				x = x - FOURTH_ALTERATION;
		
			}

			x = x - THIRD_ALTERATION;
			// decode 1
			if (i % 2 != 0)
			{
				x = x - SECOND_ALTERATION;
				
			}
			x = x + FIRST_ALTERATION;
			
			
			if (x == 58)
			{
				x = 59;
			}
			ch = static_cast<char>(x);

			encodedMsg += x;

		}  //  end for loop

		if (j != 0)
		{
			finalDecode.push_back(encodedMsg);
		}
		
	}
	return finalDecode;
}
