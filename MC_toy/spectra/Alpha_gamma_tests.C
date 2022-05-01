#include <iostream>
#include <iomanip>
#include <fstream>
#include "TGraph.h"
#include "TH2.h"
#include "TFile.h"
#include "TTree.h"
#include "TH1.h"
#include "TStyle.h"

#include "RandomFunctions.h"
using namespace std;

int Alpha_gamma_tests() {

    //Output file
    //const char *output_file_name = "alpha_positions_hist.root"

    double r = 20.0;

    double x;
    double y;
    double z;

    RandomFunctions::Sphere(x, y, z, r);

    std::cout << "x position is " << x << endl;
    std::cout << "y position is " << y << endl;
    std::cout << "z position is " << z << endl;

    //alpha_pos_copy->Draw();

    //output_file.write_output_file();


    return 0;
}

