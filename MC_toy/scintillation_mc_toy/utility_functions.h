#ifndef UTILITY_FUNCTION_H
#define UTILITY_FUNCTION_H

// class containing energy spectrums and other utility functions required by main code

#include "TF1.h"
#include<string>
#include<iostream>
#include<fstream>
#include<chrono>
#include <sstream>
#include <vector>
#include <algorithm>
#include "TH1.h"
#include "TRandom.h"
#include "TRandom3.h"
#include "TVector3.h"

class utility_functions {

private:
	TF1 *fScintillation_function_electron = nullptr;
        TF1 *fScintillation_function_alpha = nullptr;
        TF1 *fScintillation_function_prompt = nullptr;
        TF1 *fScintillation_function_xenon = nullptr;      
        TF1 *fScintillation_function_slow = nullptr;  
        TF1 *fScintillation_function_ArXe = nullptr;   

public:

	// constructor
	utility_functions(){};

	// destructor 
	~utility_functions();

	// poisson distribution function
	int poisson(const double mean, const double draw, const double eng) const;
        
	// scintillation function
	static double scintillation_function( const double *t, const double *par);

        void initalise_scintillation_functions_argon(const double t_singlet, const double t_triplet, const double singlet_fraction_electron, const double triplet_fraction_electron,
                                                        const double singlet_fraction_alpha, const double triplet_fraction_alpha, const double scint_time_window);
        void initalise_scintillation_functions_xenon(const double t_singlet_Xe, const double t_triplet_Xe, const double t_triplet_ArXe, const double triplet_fraction_ArXe, const double triplet_fraction_Xedoping, const double singlet_fraction_Xe,
                                                        const double scint_time_window); 
        void initalise_scintillation_functions_slow(const double t_singlet, const double t_triplet, const double singlet_fraction_electron, const double triplet_fraction_electron, const double scint_time_window);
        void initalise_scintillation_functions_ArXe(const double t_singlet_ArXe, const double singlet_fraction_ArXe, const double scint_time_window);
 
        TRandom3 *fGauss = new TRandom3();
        double get_scintillation_time_electron() { return fScintillation_function_electron->GetRandom(); }
        double get_scintillation_time_alpha() { return fScintillation_function_alpha->GetRandom(); }
        double get_scintillation_time_prompt() { return fScintillation_function_prompt->GetRandom(); }
        double get_scintillation_time_xenon() { return fScintillation_function_xenon->GetRandom(); }
        double get_scintillation_time_slow() { return fScintillation_function_slow->GetRandom(); }
        double get_scintillation_time_ArXe() { return fScintillation_function_ArXe->GetRandom(); }
                
        // Spectrum Function (Beta Decay) /////chrisflynn
        static double SpectrumFunction(double *x, double *par);

        //Supernova Spectrum
        static double fsn(double *x, double *par);

        // HEP spectrum ////chrisflynn
        static double fhep(double *x, double *par);

        //Solar spectrum ////chrisflynn
        static double fso(double *x, double *par);

        //Solar spectrum, 8B CC
        static double fcc(double *x, double *par);

        //Solar spectrum, 8B ES
        //static double fes(double *x, double *par);

        //hep spectrum, hep CC
        static double fhep_cc(double *x, double *par);

        //hep spectrum, hep ES
        //static double fhep_es(double *x, double *par);

        //Rn Spectrum ////chrisflynn
        static double Rn_function(double *x, double *par);

        //Betas//
        static double fbetas(double *x, double *par);

        //Alphas//
        static double falphas(double *x, double *par);

};

#endif
