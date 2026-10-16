// Distributed Systems - 2022
// Assignment 1 Part 1 - template
// TODO: Emir Sahin - 3010269

#include <iostream>
#include <fstream>
#include <mpi.h>

//Global variables
int arraySize = 520;
std::string textArray[520];
std::string finalArray[520];
char* needle = "of";

// searchData helper method - Do not modify
int searchData(std::string* searchArray, const int size, const char* needle){
    /* SEARCH METHOD
    This method examines the search space,
    and returns the number of hits found.
    */
    
    int foundhits = 0;
    
    for(int i = 0; i < size; i++){
        if (searchArray[i].compare(needle) == 0) foundhits++;
    }

    return foundhits;
}

//createData helper method - Do not modify
void createData(int rank){
    /* DATA METHOD
    This method populates an array with the text read from file.examines the search
    */
    
    std::string myText;

    // Read from the text file (each node reads from a different file concurrently)
    std::string nodeFileName = "searchText" + std::to_string(rank) + ".txt";
    std::ifstream MyReadFile(nodeFileName);
    
    std::cout << "Node " << rank <<  "  reading file: " << nodeFileName << std::endl;
    
    // Use a while loop together with the getline() function to read the file line by line
    int i = 0;
    while (getline (MyReadFile, myText, ' ')) {
        // add text from file into array
        textArray[i] = myText;
        i++;
    }

    // Close the file
    MyReadFile.close();
    
}

int main(int argc, char** argv) {
    // TODO: Work to be done here

    createData();
    int x = searchData(textArray,sizeof(textArray),needle);
    cout << x;


}


