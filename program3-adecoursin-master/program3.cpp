/* program3.cpp
Author: Abby DeCoursin
Date: 10-10-2019
Description: This program takes in two input files into an ifstream and then
determines the number of rows and columns in the first file in order to call
the readTable function. Once this process has been repeated for both input
files, the program calls the writeTable function in order to perform a left join
of the two input tables into an output file. If one of the input files is not
able to be opened, the program must be rerun with correct file names. It also 
asks the user for the name of the output file. If that file could not be found,
it is automatically created.
*/
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include "tables.h"

using namespace std;

int main () {
    ifstream inFile;
    ofstream outFile;

    string inputFile1;
    string inputFile2;
    string outputFile;

    // prompts user for input files
    cout << "Two input file names: ";
    cin >> inputFile1 >> inputFile2;
    cout << endl << "Output file name: ";
    cin >> outputFile;

    // opens first input file
    inFile.open(inputFile1);

    // checks if input file could be opened
    // if it could not be opened, program will need to be rerun
    if(!inFile.is_open()) {
        cout << inputFile1 << " could not be opened." << endl;
        return 1;
    }

    // opens the output file
    outFile.open(outputFile);

    // gets first line of input file
    string firstLine;
    getline(inFile, firstLine);
    
    // gets number of columns in first file
    int numCols1 = 0;
    for (int i = 0; i < firstLine.size(); i++) {
        if (firstLine[i] == ',')
            numCols1++;
    }
    numCols1++; // add extra one because no comma on last element of row

    inFile.clear(); // sets getline to the beginning of the file
    // obtained from stackoverflow.com, "Returning to beginning of file after getline"
    inFile.seekg(0, ios::beg);

    // gets number of rows in first file
    int numRows1 = 0;
    string currLine;
     while (getline(inFile, currLine)) {
         numRows1++;
     }

    inFile.clear(); // sets getline to the beginning of the file
    // obtained from stackoverflow.com, "Returning to beginning of file after getline"
    inFile.seekg(0, ios::beg);

    vector< vector<string> > table1; // creates a 2d vector to hold values of first table

    readTable(numRows1, numCols1, inFile, table1);

    inFile.close(); // closes first input file
    inFile.clear(); // clears ifstream

    // opens second input file
    inFile.open(inputFile2);

    // checks if input file could be opened
    // if it could not be opened, program will need to be rerun
    if (!inFile.is_open()) {
        cout << inputFile1 << " could not be opened." << endl;
        return 1;
    }

    int numRows2 = 0;
    int numCols2 = 0;

    // gets number of columns in second file
    string line;
    getline(inFile, line);
    for (int i = 0; i < line.size(); i++) {
        if (line[i] == ',')
            numCols2++;
    }
    numCols2++; // add extra one because no comma on last element

    inFile.clear(); // sets getline to the beginning of the file
    // obtained from stackoverflow.com, "Returning to beginning of file after getline"
    inFile.seekg(0, ios::beg); 

    // gets number of rows in second file
    string currentLine;
     while (getline(inFile, currentLine)) {
         numRows2++;
     } 

    inFile.clear(); // sets getline to the beginning of the file
    // obtained from stackoverflow.com, "Returning to beginning of file after getline"
    inFile.seekg(0, ios::beg);

    vector< vector<string> > table2; // creates a 2d vector to hold values of second table

    readTable(numRows1, numCols1, inFile, table2);

    inFile.close(); // closes second input file

    writeTable(outFile, table1, table2);
    outFile.close(); // closes output file
}