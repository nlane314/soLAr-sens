#include <iostream>
#include <iomanip>
#include <fstream>
#include "TGraph.h"
#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TStyle.h"
#include "TText.h"

using namespace std;

int make_root_files() {

    double x;
    ifstream inFile;
    
    inFile.open("B8_test2_nue_Ar40_ar40kt_events.dat");
    if (!inFile) {
        cout << "Unable to open file";
        exit(1); // terminate with error
    }
   
    string line;
    double value;
    double sum;
    int counter = 0;
    int counter_2 = 0;
    double energy;

    TFile f("B8_nue_Ar_channel_output.root","new");
    TH1D *number_events = new TH1D("number_events", "", 40, 0.00025*1000, 0.02025*1000);


    while (getline(inFile, line)) {
        stringstream lineStream(line);
        sum = 0;

	while(lineStream >> value)
	{
	    counter_2++;
	    if (counter_2 % 2 == 0) {
                sum += value;
		energy = value*1000;
		number_events->SetBinContent(counter, energy);
            }
	}
	counter ++;
    }
    
    number_events->Write();


    inFile.close();



    return 0;
}
