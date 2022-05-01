#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>
#include <sstream>
#include <unistd.h>
#include <stdio.h>
#include <algorithm>
#include <vector>

#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TH2.h"
#include "TF1.h"
#include "TStyle.h"

using namespace std;

//This code is to calculate the pile-up of background//

int pile_up(){

//////////////////////
//Reading parameter///
//////////////////////

////////////////////////
//Define needed number//
////////////////////////

    double detector_threshold = 5.0;
    double r = 840000; //Rate
    double t = 100*10^(-9); //Time resolution
    int N = 100; //Number of samples
    int NUM_BINS = 100;

///////////////////
//Open root files//
///////////////////


    TFile *fS = new TFile("output/events_39Ar.root");
    TTree* data_treeS = (TTree*)fS->Get("data_tree");
    TTree* event_treeS = (TTree*)fS->Get("event_tree"); 

    int data_eventS; double data_timeS; double event_ES;

    data_treeS->SetBranchAddress("data_time", &data_timeS);
    data_treeS->SetBranchAddress("data_event", &data_eventS);
    event_treeS->SetBranchAddress("event_E", &event_ES);


//////////////
//Histograms//
//////////////

    TH1D *energy_pileup = new TH1D("Energy Spectrum","energy_spectrum;Energy[MeV];entries",NUM_BINS,0,0.6);
    TH1D *energy = new TH1D("Energy Spectrum", "energy_spectrum;Energy[MeV];entries", NUM_BINS, 0, 0.6);

///////////
//Filling//
///////////


    for(int i = 0; i<event_treeS->GetEntries(); i++){
      event_treeS->GetEntry(i);
      double uniform_real_distribution = (float) rand()/RAND_MAX;
      if(uniform_real_distribution < (1-exp(-r*t))){
        energy_pileup->Fill(event_ES);
      }
      energy->Fill(event_ES);
    }

////////
//Plot//
////////

     energy->Draw();
     return 0;
}
