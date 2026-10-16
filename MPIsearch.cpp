// Distributed Systems - 2022
// Assignment 1 Part 1 - template
// TODO: Emir Sahin - 3010269

#include <iostream>
#include <fstream>
#include <mpi.h>
#include <sstream>;

using namespace std;
//Global variables
int arraySize = 520;
std::string textArray[520];
std::string finalArray[520];
const char* needle="of";
//const char* needle;

//int total_hits;

// searchData helper method - Do not modify
int searchData(std::string* searchArray, const int size, const char* needle) {
    /* SEARCH METHOD
    This method examines the search space,
    and returns the number of hits found.
    */

    int foundhits = 0;
    
    for (int i = 0; i < size; i++) {
        if (searchArray[i].compare(needle) == 0) foundhits++;
    }

    return foundhits;
}

//createData helper method - Do not modify
void createData(int rank) {
    /* DATA METHOD
    This method populates an array with the text read from file.examines the search
    */

    std::string myText;

    // Read from the text file (each node reads from a different file concurrently)
    std::string nodeFileName = "searchText" + std::to_string(rank) + ".txt";
    std::ifstream MyReadFile(nodeFileName);

    std::cout << "Node " << rank << "  reading file: " << nodeFileName << std::endl;

    // Use a while loop together with the getline() function to read the file line by line
    int i = 0;
    while (getline(MyReadFile, myText, ' ')) {
        // add text from file into array
        textArray[i] = myText;
        i++;
    }

    // Close the file
    MyReadFile.close();

}

int main(int argc, char** argv) {
    // TODO: Work to be done here
    //   string a;
    //   std::cout << "Please enter a word" << std::endl;
    //   cin >> a;
    //   needle = a.c_str();
       MPI_Init(&argc,&argv);
        



        //World size
        int world_size;
        MPI_Comm_size(MPI_COMM_WORLD, &world_size);
        std::cout << "world size is: " << world_size << std::endl;

        //World rank
        int rank;
        MPI_Comm_rank(MPI_COMM_WORLD, &rank);
        std::cout << "world rank is: " << rank << std::endl;
        //creating our array
        createData(rank);


       



  

            std::cout << "Searching" << std::endl;
            // x found hits
            int x = searchData(textArray, arraySize, needle);
            int total_hits=0;

            std::cout << "Rank executed =" << rank << " hits found =" << x << std::endl;
            // reduce command for hits
            MPI_Reduce(&x, &total_hits, 1, MPI_INT, MPI_SUM, 3,MPI_COMM_WORLD); 
            //if it's the 3rd node printing the total hits
            if (rank == 3) std::cout << "Total Hits =" << total_hits << std::endl;



           //closing mpi
    MPI_Finalize();


    return 0;


}


