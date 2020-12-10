/*--------------------------------------------------------------------*/
/*  Author: Dayne Farris
/*  Date: 11/27/2020
/*  Assignment: Final Project
* Vulnerabilities:
/*--------------------------------------------------------------------*/

// Includes
#include <iostream>
#include <iomanip>
#include <cstdlib>
#include <fstream>
#include <cstdlib>
//#include <ctime> --------------------------------------------
#include<string>
//#include<conio.h> -------------------------------------------
#include<vector>
#include <sstream>
#include <algorithm>

using namespace std;

// Funtion Prototypes
void displayLine(vector<string> data);
void viewLine(vector<string> data, int fileLine);
vector<string> editLine(vector<string> data, int fileLine);
vector<string> addLine(vector<string> data, int fileLine);
void saveAndEncodeFile(vector <string> data);
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
	// Variable Declarations
	char option;
	string userIn;
	ifstream inputFile;
	char line;
	int fileLine = 0;
	int lineCounter = 0;
	string strFile;
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
	} // end else if E1
	else if (encodelevel == "E2;")
	{
		decodedData = decode2(data);
	} // end else if E2
	else if (encodelevel == "E3;")
	{
		decodedData = decode3(data);
	} // end else if E3
	else if (encodelevel == "E0;")
	{
		for (int j = 0; j < 11; j++)
		{
			if (j != 0)
			{
				decodedData.push_back(data[j]);
			} // end if index 0 checker
		} // end for j
	} // end else if E0
	getDescriptions(decodedData);
	displayOptions();
	do {
		do {
			cin >> option;
			option = toupper(option);
			cout << endl;
			if (isdigit(option)) {
				cout << "recieved a numeric value when unexpected. Please select an available option listed above." << endl;
			} // end if isdigit()
			else if (isalpha(option)) {
				if (option == 'D' || option == 'V' || option == 'E' || option == 'A' || option == 'S' || option == 'X') {
					break;
				} // end if option checker
				cout << "An unexpected character was entered. Please select an available option listed above." << endl;
			} // end else if isalpha()
			else
			{
				cout << "An unexpected character was entered. Please select an available option listed above." << endl;
			} // end else
		} while (option != 'D' || option != 'V' || option != 'E' || option != 'A' || option != 'S' || option != 'X'); // end do

		switch (option) {
		case 'D':
			displayLine(decodedData);
			break;
		case 'V':
			viewLine(decodedData, fileLine);
			break;
		case 'E':
			decodedData = editLine(decodedData, fileLine);
			break;
		case 'A':
			decodedData = addLine(decodedData, fileLine);
			break;
		case 'S':
			saveAndEncodeFile(decodedData);
			break;
		case 'X':
			cout << "Thank you for using this program." << endl;
			return 0;
		default: // if no selection matches we default this statement. This should be unreachable.
			cout << "No selection chosen exists. Please select a value shown listed. " << endl;
		} // end switch option

		while (inputFile >> line) {
			inputFile >> noskipws;
			if (line != ';') {
				cout << line;
			} // end if
			else if (line == ';') {
				cout << endl;
			} // end else if
		} // end while
	} while (option != 'x'); // end do
} // end main

void displayLine(vector<string> data) // Displays descriptions
{ 
	getDescriptions(data);
	displayOptions();
} // end displayLine

void viewLine(vector<string> data, int fileLine) // Selects which line to view out of available options from data
{
	do {
		for (;;) {
			cout << "Enter line number you wish to view: (Values 1-" << data.size() << ")" << endl;
			if (cin >> fileLine) {
				break;
			} // end if
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} // end for loop

	} while (fileLine < 1 || fileLine > data.size()); // end do loop
	getFullLine(data, fileLine);
	displayOptions();
} // end viewLine

vector<string> editLine(vector<string> data, int fileLine) // Selects which line to edit and carries data into newEdit to gather new information
{
	do {
		for (;;) {
			cout << "Enter line number you wish to edit: (Values 1-" << data.size() << ")" << endl;
			if (cin >> fileLine) {
				break;
			} // end if 
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
		} // end for loop

	} while (fileLine < 1 || fileLine > data.size()); // end do loop
	getFullLine(data, fileLine);

	cout << "WARNING: You cannot use semi-colons in these fields. Any semicolons entered will be removed." << endl << endl;

	data = newEdit(data, fileLine);
	displayOptions();
	return data;
} // end editLine

vector<string> addLine(vector<string> data, int fileLine) // Carries data into new add which updates the vector information to hold the new addition
{
	cout << "WARNING: You cannot use semi-colons in these fields. Any semicolons entered will be removed." << endl << endl;
	data = newAdd(data, fileLine);
	displayOptions();
	return data;
} // end addLine



void saveAndEncodeFile(vector<string> decodedData) // Select new file name/encode level and send to specific encode method based on user selection
{
	int encodeLevel;
	string throwAway;
	vector<string> encodedVector;
	string userIn;
	int newEncodeLevel = 0;
	cout << "Enter file name: " << endl;
	cin >> userIn;
	// getline potential ------------------------------------------------------------------------------
	cout << endl;
	do {
		cout << "Enter encoding level <0, 1, 2, or 3>" << endl;
		cin >> encodeLevel;
		cout << endl;
		//-------------------------------------------------------------------------------------------------
	} while (encodeLevel < 0 || encodeLevel > 3); // end do loop
	cout << endl;
	bool encode = false;

	switch (encodeLevel) {
	case 1:
		encodedVector = encode1(decodedData, encode);
		saveFile(encodedVector, userIn);
		break;
	case 2:
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
	} // end switch encodeLevel

	displayOptions();
} // end saveAndEncodeFile

vector<string> readFile(string strFile, vector<string> data, ifstream& inputFile, string userIn) //Read the file into the vector 
{
	string inputString;
	string line;
	inputFile.open(userIn);
	if (!inputFile.is_open())
	{
		cout << "Error opening file." << endl;
		exit(1);
	} // end if not in inputFile

	while (getline(inputFile, line))
	{
		vector<string> columns = split(line, '\n');

		data.push_back(line);
	} // end while
	inputFile.close();

	return data;
} // end readFile

vector<string>split(const string& s, char delim = ',') // ----------------------------------------------------------------------
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
void getDescriptionByValue(vector<string> data, int fileLine) // gathers info from data at the specific line selected by user and gets sent to substring fullLine
{
	string fullLine = data.at(fileLine - 1);
	string splitLine = process(fullLine);
	cout << splitLine;
} // end getDescriptionByValue

string process(string const& s) // substring method of finding semi colons
{
	string::size_type pos = s.find(';');
	if (pos != string::npos)
	{
		return s.substr(0, pos);
	} // end if pos
	else
	{
		return s;
	} // end else
} // end process

void getDescriptions(vector<string> data) // gathering line info from vector
{ 
	int counter = 1; // counter to track current line in console
	for (int i = 0; i < data.size(); i++) {
		string fullRow = data.at(i);
		string firstDeclaration = process(fullRow);
		cout << counter++ << "." << '\t' << firstDeclaration << endl;
	} // end for data
	cout << endl;
} // end getDescriptions

void displayOptions() // Displays available options to select for user
{ 
	cout << setw(25) << "AVAILABLE OPTIONS" << endl << endl;
	cout << "D - DISPLAY LINE DESCRIPTIONS" << endl;
	cout << "V - VIEW LINE DATA" << endl;
	cout << "E - EDIT LINE DATA" << endl;
	cout << "A - ADD LINE DATA" << endl;
	cout << "S - SAVE AND ENCODE FILE" << endl;
	cout << "X - EXIT PROGRAM" << endl << endl;
} // end displayOptions

void fileData(string desc, string userName, string passWord, string notes) // Displays desc, userName, passWord, and notes
{
	cout << "Row Desc:" << '\t' << desc << endl;
	cout << "Username:" << '\t' << userName << endl;
	cout << "Password:" << '\t' << passWord << endl;
	cout << "Notes:" << '\t' << notes << endl << endl;
} // end fileData
string getFullLine(vector<string> data, int fileLine) // getting each section of each fullLine through finding semi colon
{
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
				cout << "Row Desc:" << '\t' << fullLine.substr(0, pos) << endl;
			} // end if description
			else if (i == 1) {
				descLine = fullLine.substr(description.length() + 1);
				string::size_type pos = descLine.find(';');
				cout << "Username:" << '\t' << descLine.substr(0, pos) << endl;
				userName = descLine.substr(description.length(), pos);
			} // end else if username
			else if (i == 2) {
				userLine = descLine.substr(userName.length() + 1);
				string::size_type pos = userLine.find(';');
				cout << "Password:" << '\t' << userLine.substr(0, pos) << endl;
				passWord = userLine.substr(0, pos);
			} // end else if password
			else if (i == 3) {
				string test3 = userLine.substr(passWord.length() + 1);
				string::size_type pos = test3.find(';');
				cout << "Notes:" << '\t' << test3.substr(0, pos) << endl << endl;

			} // end else if notes
		} // end if pos
		else
		{
			return fullLine;
		} // end else
	} // end for i

	return fullLine;
} // end getFullLine
vector<string> newEdit(vector<string> data, int fileLine) // Getting new information for the selected line from the user to populate the updated line through finalString
{
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
		} // end if y flag
		else if (flag != 'Y')
		{
			cout << "Line was not changed." << endl << endl;
		} // end else if not y flag

	} while (flag != 'Y' || isdigit(flag)); // end do loop
	finalString = desc + ';' + userName + ';' + passWord + ';' + notes + ';';
	data[fileLine - 1] = finalString;
	return data;
} // end newEdit
vector<string> newAdd(vector<string> data, int fileLine) // Getting new information from the user to build a new line and pushback new line into the vector
{
	string aDesc;
	string aThrowaway;
	string aUserName;
	string aPassWord;
	string aNotes;
	string aFinalString;
	char flag;
	do {
		getline(cin, aThrowaway);
		do {
			cout << "Enter a line description:" << endl;
			getline(cin, aDesc);
			if (!aDesc.empty()) // ------------------------------------------------------------------------------------
			{
				cout << "No information entered in current field." << endl;
			}
		} while (!aDesc.empty());
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
		} // end if y flag
		else if (flag != 'Y')
		{
			cout << "Line has not been added." << endl << endl;
		} // end else if not y flag
	} while (flag != 'Y' || isdigit(flag)); // end do loop
	aFinalString = aDesc + ';' + aUserName + ';' + aPassWord + ';' + aNotes + ';';
	data.push_back(aFinalString);
	return data;
} // end newAdd

void saveFile(vector<string> encodedVector, string userIn) // Saves the file with the name selected from the user
{
	ofstream output_file(userIn);
	ostream_iterator<string> output_iterator(output_file, "\n");
	copy(encodedVector.begin(), encodedVector.end(), output_iterator);
	cout << "File save was successful!" << endl << endl;
} // end saveFile

vector<string> encode1(vector<string> data, bool encode3) // Encode level one converting each character to ascii and applying alterations to receive new encoded vector
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

		}  //  end for index 
		if (j == 0 && encode3 == false)
		{
			encodedVector.push_back("E1;");
		} // end if index 0 checker
		encodedVector.push_back(encodedMsg);
	} // end for j
	return encodedVector;
} // end encode1

vector<string> encode2(vector<string> data, bool encode3) // Encode level two converting each character to ascii and applying alterations and character swap to receive new encoded vector
{
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
			} // end if divisible by 3 checker
		} // end if semi colon checker

			ch = static_cast<char>(x);

			encodedMsg += x;

		}  //  end for index
		if (j == 0 && encode3 == false)
		{
			encodedVector.push_back("E2;");
		} // end if index 0 checker
		else if (j == 0 && encode3 == true)
		{
			encodedVector.push_back("E3;");
		} // end else if index 0 checker
		encodedVector.push_back(encodedMsg);
	} // end for j
	return encodedVector;
} // end encode2

vector<string> encode3(vector<string> data) // Encode level three converting each character to ascii and applying alterations from encode one and two to receive new encoded vector
{ 
	vector<string> encodedVector1;
	vector<string> encodedVector2;
	bool encode3 = true;

	encodedVector1 = encode1(data, encode3);
	encodedVector2 = encode2(encodedVector1, encode3);

	return encodedVector2;
} // end encode3

vector<string> encodeCharSwap(vector<string> data) // going through each full line swapping the first and last char of each field to rebuild data with finalString
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

			} // end if description
			else if (i == 1) {
				descLine = fullLine.substr(description.length() + 1);
				string::size_type pos = descLine.find(';');
				userName = descLine.substr(0, pos);
				iter_swap(userName.begin(), userName.rbegin());

			} // end else if username
			else if (i == 2) {
				userLine = descLine.substr(userName.length() + 1);
				string::size_type pos = userLine.find(';');
				passWord = userLine.substr(0, pos);
				iter_swap(passWord.begin(), passWord.rbegin());

			} // end else if password
			else if (i == 3) {
				passLine = userLine.substr(passWord.length() + 1);
				string::size_type pos = passLine.find(';');
				notes = passLine.substr(0, pos);
				if (notes.length() > 2) {
					iter_swap(notes.begin(), notes.rbegin()); // swapper
				}
				finalString = description + ';' + userName + ';' + passWord + ';' + notes + ';';

			} // end else if notes

		} // end for i
		data[j] = (finalString);
	} // end for j
	return data;
} // end encodeCharSwap

vector<string> decode1(vector<string> data) // Decode level one converting each character to ascii and applying alterations to receive new decoded vector
{ 
	char ch;
	int x = 0;
	string decodedMsg = "";
	vector<string> decodedVector;

	for (int j = 0; j < 11; j++)
	{
		decodedMsg = "";
		for (int i = 0; i < data[j].length(); i++) {
			ch = data[j][i];
			x = static_cast<int>(ch);

			if (x != 59)
			{
				x = x + FIRST_ALTERATION;
				if (i % 2 != 0)
				{
					x = x - SECOND_ALTERATION;
				} // end if divisible by 2 checker
			} // end if semi colon checker
			ch = static_cast<char>(x);

			decodedMsg += x;
		}  //  end for i
		if (j != 0)
		{
			decodedVector.push_back(decodedMsg);
		} // end if skip index 1
	} // end for j
	return decodedVector;
} // end decode1

vector<string> decode2(vector<string> data) // Decode level two converting each character to ascii and applying alterations and character swapping to receive new decoded vector
{
	char ch;
	int x = 0;
	string encodedMsg = "";
	vector<string> encodedVector;
	
	
	for (int j = 0; j < data.size(); j++)
	{
		encodedMsg = "";
		for (int i = 0; i < data[j].length(); i++) {
			ch = data[j][i];
			x = static_cast<int>(ch);
			// -=------------------------------------------------------------TESTTINGNGNGNGNGG
			if (x != 59)
			{ // this line was not here before
				if (x % 3 == 0)
				{
					x = x - FOURTH_ALTERATION;
				} // end if divisible by 3 checker

				x = x - THIRD_ALTERATION;
			} // end if semi colon checker

			ch = static_cast<char>(x);

			encodedMsg += x;

		}  //  end for i

		if (j != 0)
		{
			encodedVector.push_back(encodedMsg);
		} // end if skip index 1

	} // end for j
	data = encodeCharSwap(encodedVector);
	return data;
} // end decode2

vector<string> decode3(vector<string> data) // Decode level three converting each character to ascii and applying decode two and decode one to receive new decoded vector
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
		} // end if skip index 1 
	} // end for j
	encodedVector = encodeCharSwap(encodedVector);
	for (int j = 0; j < 10; j++)
	{
		encodedMsg = "";
		for (int i = 0; i < encodedVector[j].length(); i++) {
			ch = encodedVector[j][i];

			x = static_cast<int>(ch);

			if (x != 59)
			{
				if (x % 3 == 0)
				{
					x = x - FOURTH_ALTERATION;
				} // end if divisible by 3 checker
				x = x - THIRD_ALTERATION;
				x = x + FIRST_ALTERATION;
				if (i % 2 != 0)
				{
					x = x - SECOND_ALTERATION;
				} // end if index checker 
			} // end if semi colon checker

			ch = static_cast<char>(x);

			encodedMsg += x;

		}  //  end for i

		finalDecode.push_back(encodedMsg);
	} // end for j
	return finalDecode;
} // end decode3
