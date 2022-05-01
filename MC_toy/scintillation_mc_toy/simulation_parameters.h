// this file contains parameters used in simulation

#include "TRandom3.h"
namespace parameters {
	
	// output file
	const char *output_file_name = "output/events_b8_foils_40.root";


    ///-------------------------------------
    //--------Simulation Settings-----------
    ///-------------------------------------
    // Xenon doping
    const bool simulate_xenon = false;   // enables xenon doping, false = pure argon

    // WLS Reflective foils
    const bool include_reflected = true; // enables WLS relfective foils on the cathode (visible light)

    // Timings
    const bool include_timings = true;   // enables timings (emission and transport)  


    ///-------------------------------------
    //--------WHAT events to generate?------
    ///-------------------------------------
    bool fixed_energy = false; //If gamma activity this will be set to true in the analyze_light.cpp
    double fixedE = 20.0; //Set to -1.0 to check if fixed value has been correctly assigned
    
    const double particle_type = 0;   // ionising particle type: 0 - electron, 1 - alpha

    bool supernova = false;
    bool solar = true;
    bool so_CC = false;
    //bool so_ES = false;
    bool hep_CC = false;
    //bool hep_ES = false;
    bool gen_hep = false;
    bool gen_argon = false; //This is Ar39
    bool gen_Co60B = false;
    bool gen_Co60G1 = false; //fixed energy = 1.173 Mev
    bool gen_Co60G2 = false; //fixed energy = 1.332 Mev
    bool gen_Ar42 = false;
    bool gen_K42 = false;
    bool gen_40KB = false;
    bool gen_40KG = false; //fixed energy = 1.46 MeV
    bool gen_Kr85B1 = false;
    bool gen_Kr85B2 = false;
    bool gen_Kr85G1 = false; //fixed energy = 0.151 Mev
    bool gen_Kr85G2 = false; //fixed energy = 0.305 Mev
    bool gen_Pb214 = false;
    bool pileup = false;
	//////-------------------------------///////
	//////--Radon alpha chain daughters--///////
	//////-------------------------------///////
	bool gen_Rn222 = false;
	bool gen_Po218 = false;
	bool gen_Po214 = false;
	bool gen_Po210 = false;
    bool gen_Bi214 = false;
	bool gen_alpha_gamma = false; //specifically for generating an alpha event followed by a rare gamma emission
        bool gen_neutrons_40Ar = false;
        bool gen_neutrons_36Ar = false; 
   
        bool gen_betas = false;
        bool gen_alphas = false;     
       

	//---alpha scintillation properties---//
    const double massAlpha = 3727.3794;     // alpha particle mass - MeV/c^2
	const double activity_Rn = 0.000021;    // Bq/kg
	const double activity_Ar = 1.01;

	//----------------------------------------------
	//---------Dimensions of event region-----------
	//----------------------------------------------
	// region to generate events in
    const double x_position_range[2] {5,360};	// cm from anode [Note can get problems from too much light if generating events < 5 cm from anode]
	const double y_position_range[2] {-600,600};	// cm
	//const double z_position_range[2] {400,1000};	// cm [this comes from the "middle third"]
    const double z_position_range[2] {0,1400};   // cm



    //chrisflynn mass
    const double entire_mass = 0.001396*(x_position_range[1]-x_position_range[0])*(y_position_range[1]-y_position_range[0])*(z_position_range[1]-z_position_range[0]); //density = 1.396 g/cm^3

    //chrisflynn random variables
    const double frame_time = 0.0025; // 2.5 miliseconds; equivalent to the drift time of electrons in DUNE
    const double time_window = 1; //readout window (running time of the simulation in seconds)
    const double time_frames = int(time_window/frame_time); // number of frames registered
    
    //-------------------------------------
    //----Number of Events-----------------
    //-------------------------------------
    // Fixed energy (electron like) events:
    const int max_events_FE = 10000;
    
	// Ar-39 events:
    //const int max_events_Ar = activity_Ar * entire_mass * time_window;//FULL volume for 1 TPC
	const int max_events_Ar = 10000;
    const int Ar_decays_per_sec = activity_Ar* entire_mass; // decay rate in one TPC
        
	// Radon events:
    const int max_events_Rn = 100000; //the 0.01 is included because of design changes to reduce alpha see https://indico.fnal.gov/event/20794/contribution/0/material/slides/0.pdf
    const int max_events_Rn222 = 100000;
	const int max_events_Po218 = 10000; //0.25 comes from 4 alpha decays in chain from Rn222, each contributes 10Bq/kg * 0.01 with new Rn222 condition
    const int max_events_Po214 = 10000;
	//Will want a new variable for Po210 here if including events from Rn222 decay chain 
    const int max_events_Po210 = 10000;//Activity from Po210 in the APAs
    const int max_events_Pb214 = 10000;  
    const int max_events_Bi214 = 10000;  
    const double Rn_decays_per_sec = activity_Rn* entire_mass; // decay rate in one TPC
        
	//Supernova events:
    const int max_events_SN = time_frames;

        //pileup
    const int max_events_pileup = 20000;
        
	//8B Solar neutrino events:
    const int max_events_SO = 10000;
    const int max_events_SO_CC = 10000;
    //const int max_events_SO_ES = 0.326*26742;

	// Other radiactive bkgs
    const int max_events_Co60B = 10000;//For beta decay, near 100% would have beta decay and 200% gamma decay
    const int max_events_Co60G1 = 10000;
    const int max_events_Co60G2 = 10000;
    const int max_events_Ar42 = 10000;//1.41e-3 Bq*cm^-3 from mcc11 simulation
    const int max_events_K42 = 10000;
	const int max_events_40KB = 10000;
    const int max_events_40KG = 10000;//10.72% ratio for gamma
    const int max_events_Kr85B1 = 10000;//near 100% of Kr82 would have beta decay
    const int max_events_Kr85B2 = 10000;
    const int max_events_Kr85G1 =  10000;
    const int max_events_Kr85G2 = 10000;
    const int max_events_hep = 10000;
    const int max_events_hep_CC = 20000;
    //const int max_events_hep_ES = 120;
    const int max_events_betas = 10000;
    const int max_events_alphas = 10000;
	
	// Alpha-gamma events
    const int max_events_alpha_gamma = 20000; //This is the number of alpha and gammas added together, e.g for 2 events get 1 alpha and 1 gamma
    const int max_events_neutrons_40Ar = 10000;
    const int max_events_neutrons_36Ar = 10000;

    // TPC boundaries (for alpha-gammas)
    const double max_x = 363.0;
    const double min_x = 1.0;
    const double max_y = 600.0;
    const double min_y = -600.0;
    const double max_z = 1400.0;
    const double min_z = 0.0;

    // timing parametersiation properties
    const double timing_discretisation_step_size = 1.0; // cm
    
	// photon detection system properties
	const double quantum_efficiency = 0.035;	   // arapuca QE
	const double wireplane_factor = 1.0;           // included in parameterisations	
	const double vuv_transmission = 0.5;           // PD window transmission: VUV Ar/Xe scintillation light
	const double vis_transmission = 0.7;           // PD window transmission: Visible light (foils)
    
    // fraction PDs sensitive to each component
    const double opdet_fraction_vuv_only = 0.0;
    const double opdet_fraction_visible_only = 0.0;
    const double opdet_fraction_both = 1.0 - opdet_fraction_vuv_only - opdet_fraction_visible_only;
 
    // cathode foils/TPB coverage
	const double cathode_tpb_frac = 0.80;

	// scintillation properties
	const int scintillation_yield = 24000; 		// 24000 photons/MeV at 500 V/m
    const int scint_yield_alpha = 16800;        // SY of alpha particles at 500 V/cm - from larsoft  

    // scintillation timing properties
    const double scint_time_window = 0.00001;   // 10 us
    // argon
    // timing
    const double t_singlet = 0.000000006;       // 6ns 
    const double t_triplet = 0.0000015;         // 1.5 us
    // prompt/late ratio
    // electron-like
    const double singlet_fraction_electron = 0.30;
    const double triplet_fraction_electron = 0.70;
    // alpha
    const double singlet_fraction_alpha = 0.75;
    const double triplet_fraction_alpha = 0.25;   
	
    // xenon -- Aprile, Doke https://arxiv.org/abs/0910.4956
    // timing
    const double t_singlet_Xe = 0.0000000042;      // 4.2 ns 
    const double t_triplet_Xe = 0.000000022;       // 22 ns

    //Xe doping concentration and time variables
    const double frac_Xe_photons = 0.53;  //fraction of photons coming from Xe excimers
    const double frac_ArXe_photons = 0.47;  //fraction of photons coming from ArXe excimers
    const double singlet_fraction_Ardoping = 0.23;
    const double triplet_fraction_Ardoping = 0.24;
    const double triplet_fraction_Xedoping = 0.44;
    const double triplet_fraction_ArXe = 0.09;
    const double t_triplet_ArXe = 0.0000047;

    // prompt/late ratio
    // minimal dependence on particle type, approximate as single value
    const double singlet_fraction_Xe = 0.30;
    const double triplet_fraction_Xe = 0.70;    
		
}
