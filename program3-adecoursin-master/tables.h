/* tables.h
Author: Abby DeCoursin
Date: 10-10-2019
Description: This header file contains the declarations for the readTable and
writeTable functions. readTable takes in the number of rows in the file, the 
number of columns in the file, the ifstream of the file, and the 2d vector that
the data is going to be stored in. writeTable takes in the output file stream, 
the first input file 2d vector, and the second input file 2d vector. Both 
functions have no return. 
*/
#ifndef TABLES_H
#define TABLES_H

using namespace std;

void readTable(int numRow, int numCol, ifstream& inpFile, 
    vector < vector <string> >& table); 
void writeTable(ofstream& outFile, vector < vector <string> > table1, 
    vector < vector <string> > table2); 

#endif