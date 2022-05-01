//light yield DUNE-SP


int FIT_ENERGY() {

	// read output file from toy MC
	TFile *filein = new TFile("scintillation_toy_mc/output/events_unsmeared_foils_Xe.root");

	// set branch addresses 
	TTree *data_tree = (TTree*)filein->Get("data_tree");
	filein->GetObject("data_tree", data_tree);
	int data_event;
	data_tree->SetBranchAddress("data_event", &data_event);

	TTree *event_tree = (TTree*)filein->Get("event_tree");
	filein->GetObject("event_tree", event_tree);
	int event_no; double event_x_pos, event_y_pos, event_z_pos, event_E;
	event_tree->SetBranchAddress("event_no", &event_no);
	event_tree->SetBranchAddress("event_x_pos", &event_x_pos);
	event_tree->SetBranchAddress("event_y_pos", &event_y_pos);
	event_tree->SetBranchAddress("event_z_pos", &event_z_pos);
	event_tree->SetBranchAddress("event_E", &event_E); 

        double p_0 = 2.676e2;
        double p_1 = -7.750e2;
        double p_2 = 3.980e2;

        TH2D *photons_vs_energy = new TH2D("","",100,0,20,100,0,1800);

	// loop through data trees counting entries to get total hits for each event
	int number_events = event_tree->GetEntries();
	vector<int> hits_both(number_events,0); 
        vector<double> photons;
	int size_data_tree = data_tree->GetEntries();
	for (int i = 0; i < size_data_tree; i++) {
		data_tree->GetEntry(i);
		hits_both[data_event]++; // increment hit count for this event
	}

        for(int i = 0;i<event_tree->GetEntries();i++){
                event_tree->GetEntry(i);
                double gauss_pos = p_0*exp(-0.5*((event_x_pos-p_1)/p_2)*((event_x_pos-p_1)/p_2));
                photons.push_back(hits_both[i]-gauss_pos*event_E+40*event_E);
                photons_vs_energy->Fill(event_E, hits_both[i]-gauss_pos*event_E+40*event_E);
}

	cout << "total tree complete" << endl;

	vector<double> LY_both;
	vector<double> x_bin;
	vector<double> err_x;
	vector<double> err_y_both;
	

	double bin_step = 0.2;
	double drift_size = 16;
	
	// loop over bins in x, calculating light yield
	for (int bin = 0; bin < drift_size/bin_step; bin++){
		vector<double> LY_vals_both; //LY_vals_both.reserve(1e6);

		double xbin_min = bin*bin_step;
		double xbin_max = (bin+1)*bin_step;
		x_bin.push_back((xbin_max + xbin_min)/2);
		err_x.push_back(bin_step/2);

		// loop over events selecting those within current bin
		for (int i = 0; i < number_events; i++){
			event_tree->GetEntry(i);
			// LY of events occuring within bin
			if (event_E > xbin_min && event_E <= xbin_max) {
				double LY_val_both = hits_both[event_no];
				LY_vals_both.push_back(LY_val_both);
			}
		}

		// calculate mean and stdev of LY for this bin for plotting 
		double m_both; double stdev_both;		
		
		// both
		// mean
		double sum_both = std::accumulate(std::begin(LY_vals_both), std::end(LY_vals_both), 0.0);
		m_both =  sum_both / LY_vals_both.size();
		// stdev
		double accum_both = 0.0;
		std::for_each (std::begin(LY_vals_both), std::end(LY_vals_both), [&](const double d) { accum_both += (d - m_both) * (d - m_both); } );
		stdev_both = sqrt(accum_both / (LY_vals_both.size()-1));

		
		// add mean and stdev to vectors for plotting
		LY_both.push_back(m_both);		
		err_y_both.push_back(stdev_both);
		

	}
	cout << "LY values:" << endl;
	cout << "x: ";
	for (int n = 0; n < x_bin.size(); n++) {
		cout << x_bin[n] << ", ";
	}
	cout << endl;
	cout << "LY: ";
	for (int n = 0; n < x_bin.size(); n++) {
		cout << LY_both[n] << ", ";
	}
	cout << endl;
	
	// create plot
    TCanvas *c1 = new TCanvas("c1","",200,10,1080,1080);
    auto mg = new TMultiGraph();
    auto legend = new TLegend(0.7,0.7,0.9,0.9);

	TGraph *gr1 = new TGraphErrors(x_bin.size(), &(x_bin[0]),&(LY_both[0]),&(err_x[0]),&(err_y_both[0]));
	
	gr1->SetMarkerColor(1);
	
	gr1->SetLineColor(1);
	
	gr1->SetMarkerStyle(20);
	
	gr1->SetMarkerSize(1);
	
	legend->AddEntry(gr1, "Total" ,"p");
	
	mg->Add(gr1);

        TF1 *f1 = new TF1("f1","pol1",3,15);
        gr1->Fit("f1", "R");
	
	// draw graph
	mg->GetXaxis()->SetTitle("Energy (MeV)");
	mg->GetYaxis()->SetTitle("Light Detected");
	mg->GetHistogram()->SetTitle("Light Yield DUNE-SP");

	mg->GetXaxis()->SetRangeUser(0,17);
	mg->GetYaxis()->SetRangeUser(0,1000);

	mg->Draw("ap");
  
	legend->Draw("same");
	c1->Update();


        //photons_vs_energy->Draw();

    return 0;
}
