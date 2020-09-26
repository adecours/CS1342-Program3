/* tables.cpp
Author: Abby DeCoursin
Date: 10-10-2019
Description: This file contains the initialization of the functions. The 
readTable function stores the data from an input file into a 2d vector. The
writeTable function takes both of the 2d vectors for the input files and 
compares their first value to see if it matches. If it matches, both rows from
the files are added to the output table. Since it performs a left join, the 
first file parameter is considered the primary one. The final table is then 
displayed in the output file specified from the user in the main program.
*/
#include <iostream>
#include <iomanip>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;

/* readTables goes through a string stream until there are no lines left and for
each line, it stores each word in a temporary variable and appends this word and a comma
onto a current line which is then pushed back onto the final table. It has no 
return since the 2d vector is passed by reference.
*/
void readTable(int numRow, int numCol, ifstream& inpFile, 
    vector < vector <string> >& table) {

    while (!inpFile.eof()) {
        
        // seperates lines of files
        string currLine;
        getline(inpFile, currLine);
        int index = 0;

        vector<string> singleLine;
        istringstream ss(currLine);

        for(int i = 0; i < numCol - 1; i++) {
            string word;
            getline(ss, word, ',');
            word.append(1, ',');
            singleLine.push_back(word);
        }
        string lastWord;
        getline(ss, lastWord);
        singleLine.push_back(lastWord);
        table.push_back(singleLine);
    }
    /*
    // prints the table
   for (int i = 0; i < numRow; i++) {
        for (int k = 0; k < numCol; k++) {
            cout << table[i][k];
        }
        cout << endl;
    } */
}

/* writeTable takes two 2d vectors and compares the first column of each table to
see where there are matches found. If the two ids match, the rows are combined 
using push_back onto the final table. If an id in the primary table is not found
in the second table, the missing values are filled in with null. If the second 
table has two matching ids for the first table, the id is repeated with the differing
values replaced. The table is displayed in the output file specified by the user, which
is passed by reference. The function has no return.
*/
void writeTable(ofstream& outFile, vector < vector <string> > table1, 
    vector < vector <string> > table2) {

    vector < vector <string> > outTable;

    for (int i = 0; i < table1.size(); i++) { // loop goes through each row of table1
        bool isMatch = false;
        string table1ID = table1[i].at(0); // gets table1 id
        for(int k = 0; k < table2.size(); k++) { // goes through each row of table2
            string table2ID = table2[k].at(0); // gets table2 id
            if (table2ID == table1ID) { // if the ids match 
                isMatch = true;
                vector <string> headers; // create a temp vector 
                for (int temp = 0; temp < table1[i].size(); temp++) { 
                    headers.push_back(table1[i].at(temp)); // pushes back all data from table1
                }

                (headers[headers.size() - 1]).append(1, ',');

                for (int t = 1; t < table2[k].size(); t++) {
                    headers.push_back(table2[k].at(t)); // pushes back all data from table2 after the id
                }

                 outTable.push_back(headers); // pushes temp vector onto output table
            }
        }

        if (!isMatch) { // if no matching id was ever found
            vector <string> missingID; // temp vector 
            string noVal = "null,";
            for (int k = 0; k < table1[0].size(); k++) {
                missingID.push_back(table1[i].at(k)); // pushes back all data from first table
            }

            (missingID[missingID.size() - 1]).append(1, ',');

            for (int r = 1; r < table2[0].size(); r++) {
                missingID.push_back(noVal); // pushes back "null," for each value that is missing
            }
            missingID[missingID.size() - 1].pop_back(); // removes comma from last element
            outTable.push_back(missingID); // pushes temp vector onto output table
        } 
    } 

    // prints the output table to the outfile
    for (int i = 0; i < outTable.size(); i++) {
        for (int k = 0; k < outTable[0].size(); k++) {
            outFile << outTable[i][k];
        }
        outFile << endl;
    } 
}