//MD Abir A. Choudhury
//CIS 3100 
//Diagnostic Assistant

#include <iostream>
#include <string>
#include <fstream>

using namespace std;

//class definitions
class Disease {
public:
	string description;
	string sympton;
};

//function protocols
void displayMenu();
void checkUserInput(int &choice);
void readFromFile(Disease diseaseList[], int &count);
void writeToFile(Disease diseaseList[], int count);
void displayNumDiseases(Disease diseaseList[], int count);
void numSymptonsPerDiseaseReport(Disease diseaseList[], int count);
void diagnoseUser(Disease diseaseList[], int count);

int main() {
	const int SIZE = 1000;
	Disease diseaseList[SIZE];
	int count = 0;
	int menuChoice = 0;

	readFromFile(diseaseList, count);

	do {
		displayMenu();
		cin >> menuChoice;
		checkUserInput(menuChoice);

		if (menuChoice == 1) {
			displayNumDiseases(diseaseList, count);
		}
		else if (menuChoice == 2) {
			numSymptonsPerDiseaseReport(diseaseList, count);
		}
		else if (menuChoice == 3) {
			diagnoseUser(diseaseList, count);
		}
	} while (menuChoice != 0);

	writeToFile(diseaseList, count);

	system("PAUSE");
	return 0;
}

//function defintions
void displayMenu() {
	cout << "=======================\n"
		<< "   Diagnostic Assist   \n"
		<< "=======================\n"
		<< "1 - Display Disease Count\n"
		<< "2 - Symptom Count by Disease\n"
		<< "3 - Diagnose\n"
		<< "0 - Exit\n"
		<< "Choose one: \n";
}
void checkUserInput(int &choice) {
	if (choice < 0 || choice > 3) {
		cout << "You have entered an invalid number\n"
			<< "Choose another number: ";
		cin >> choice;
		checkUserInput(choice);
	}
	else {
		choice = choice;
	}
}
void readFromFile(Disease diseaseList[], int &count) {
	ifstream fileIn("diagnostic.txt");

	if (!fileIn) {
		cout << "Failed to find file.\n";
		exit(EXIT_FAILURE);
	}
	while (!fileIn.eof()) {
		fileIn >> diseaseList[count].description;
		fileIn >> diseaseList[count].sympton;
		count++;
	}
	fileIn.close();
}
void writeToFile(Disease diseaseList[], int count) {
	ofstream fileOut("fileOutput.txt");

	for (int i = 0; i < count; i++) {
		fileOut << diseaseList[i].description << " " << diseaseList[i].sympton;
		if (i < count - 1) {
			fileOut << endl;
			}
	}
	
	fileOut.close();
}
void displayNumDiseases(Disease diseaseList[], int count) {
	int counter = 0;
	string current = diseaseList[0].description;
	for (int i = 0; i < count; i++) {
		if (diseaseList[i].description != current) {
			current = diseaseList[i].description;
			counter++;
		}
	}
	cout << "There are " << counter << " diseases in the database.\n" << endl;
}
void numSymptonsPerDiseaseReport(Disease diseaseList[], int count) {
	string current = diseaseList[0].description;
	int counter = 0;
	for (int i = 0; i < count; i++) {
		if (diseaseList[i].description != current) {
			current = diseaseList[i].description;
			cout << "There are " << counter << " symptoms for " << diseaseList[i].description << endl;
			counter = 0;
		}
		else if (diseaseList[i].description == current) {
			counter++;
		}
	}
}
void diagnoseUser(Disease diseaseList[], int count) {
	string input;
	cout << "What is the sympton?\n";
	cin >> input;

	for (int i = 0; i < count; i++) {
		if (diseaseList[i].sympton == input) {
			cout << "You may have " << diseaseList[i].description << endl;
		}
	}
}