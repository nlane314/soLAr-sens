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

int make_TGraph() {

    TGraph *nue = new TGraph("../scintillation_toy_mc/smeared_combine.txt");    

    TFile f("AA.root","new");
    nue->Write();


    return 0;
}




