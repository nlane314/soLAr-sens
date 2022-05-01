#include <iostream>
#include <iomanip>
#include <fstream>
#include "TGraph.h"
#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TStyle.h"
using namespace std;

int Integrate_dat() {

    double x;
    ifstream inFile;
    
    inFile.open("smeared_hep_and_B8.dat");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
   
    string line;
    double value;
    double sum;
    int counter = 0;
    int counter_2 = 0;

    //ofstream myfile;
    //myfile.open("B8_test2.dat");


    while (getline(inFile, line)) {
        stringstream lineStream(line);
	    //cout << line << endl;

	while(lineStream >> value)
	{
	    counter_2++;
	    if (counter_2 % 2 == 0) {
                sum += value;
            }
	}
	cout << "Value is " << value << " Sum is " << sum << endl;
	counter ++;
    }
    

  //if (myfile.is_open())
  //{
    //myfile << "This is a line.  " << "Two spaces later." << "\n";
    //myfile << "This is another line.\n";
    //myfile.close();
  //}
  //else cout << "Unable to open file";

    //myfile.close();
    inFile.close();

    //output_file.write_output_file();

    cout << "Final sum is " << sum << endl;

    return 0;
}
