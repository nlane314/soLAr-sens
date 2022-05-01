// light yield DUNE-SP


int LY_DUNESP() {

	// read output file from toy MC
	TFile *filein = new TFile("scintillation_toy_mc/output/events_b8.root");

	// set branch addresses 
	TTree *data_tree = (TTree*)filein->Get("data_tree");
        //TTree *data_tree_vuv = (TTree*)filein->Get("data_tree_vuv");
        //TTree *data_tree_vis = (TTree*)filein->Get("data_tree_vis");

	filein->GetObject("data_tree", data_tree);
        //filein->GetObject("data_tree_vuv", data_tree_vuv);
        //filein->GetObject("data_tree_vis", data_tree_vis);
	int data_event;
        //int data_event_vuv;
        //int data_event_vis;
	data_tree->SetBranchAddress("data_event", &data_event);
        //data_tree_vuv->SetBranchAddress("data_event_vuv", &data_event_vuv);
        //data_tree_vis->SetBranchAddress("data_event_vis", &data_event_vis);
        

	TTree *event_tree = (TTree*)filein->Get("event_tree");
	filein->GetObject("event_tree", event_tree);
	int event_no; double event_x_pos, event_y_pos, event_z_pos, event_E;
	event_tree->SetBranchAddress("event_no", &event_no);
	event_tree->SetBranchAddress("event_x_pos", &event_x_pos);
	event_tree->SetBranchAddress("event_y_pos", &event_y_pos);
	event_tree->SetBranchAddress("event_z_pos", &event_z_pos);
	event_tree->SetBranchAddress("event_E", &event_E); 


	// loop through data trees counting entries to get total hits for each event
	int number_events = event_tree->GetEntries();
        TH1D *visible_energy = new TH1D("Visible Energy", "Visible Energy;Visible energy[MeV];Entries", 100, 0, 20);

	vector<int> hits_both(number_events,0);

	int size_data_tree = data_tree->GetEntries();
	for (int i = 0; i < size_data_tree; i++) {
		data_tree->GetEntry(i);
		hits_both[data_event]++; // increment hit count for this event
	}


	cout << "total tree complete" << endl;

        TH1D *x_recon_h = new TH1D("Position Reconstruction","Position Reconstruction;reconstructed position[cm];entries",100,0,400);
        
        vector<double> x_recon(number_events, 0);    

        for (int i=0;i<number_events;i++){
        event_tree->GetEntry(i);
        //double event_x_recon = gRandom->Gaus(event_x_pos, 1);
        x_recon[i] = gRandom->Gaus(event_x_pos, 1);
        x_recon_h->Fill(gRandom->Gaus(event_x_pos, 1));
        visible_energy->Fill(event_E);}   
        //cout<<x_recon[i]<<endl;
/*
        //vuv hits
        vector<int> hits_vuv(number_events,0);
        int size_data_tree_vuv = data_tree_vuv->GetEntries();
        for(int i=0;i<size_data_tree_vuv; i++){
             data_tree_vuv->GetEntry(i);
             hits_vuv[data_event_vuv]++;
        }

        //vis hits
        vector<int> hits_vis(number_events,0);
        int size_data_tree_vis = data_tree_vis->GetEntries();
        for(int i=0;i<size_data_tree_vis; i++){
             data_tree_vis->GetEntry(i);
             hits_vis[data_event_vis]++;
        }
        
*/
	vector<double> LY_both;
        //vector<double> LY_vuv;
        //vector<double> LY_vis;
	vector<double> x_bin;
	vector<double> err_x;
	vector<double> err_y_both;
        //vector<double> err_y_vuv;
        //vector<double> err_y_vis;
	

	double bin_step = 20;
	double drift_size = 360;
	
	// loop over bins in x, calculating light yield
	for (int bin = 0; bin < drift_size/bin_step; bin++){
		vector<double> LY_vals_both; LY_vals_both.reserve(1e6);
                vector<double> LY_vals_vuv; LY_vals_vuv.reserve(1e6);
                vector<double> LY_vals_vis; LY_vals_vis.reserve(1e6);

		double xbin_min = bin*bin_step;
		double xbin_max = (bin+1)*bin_step;
		x_bin.push_back((xbin_max + xbin_min)/2);
		err_x.push_back(bin_step/2);

		// loop over events selecting those within current bin
		for (int i = 0; i < number_events; i++){
			event_tree->GetEntry(i);
			// LY of events occuring within bin
			if (event_x_pos > xbin_min && event_x_pos <= xbin_max) {
				double LY_val_both = hits_both[event_no]/event_E;
                                //double LY_val_vuv = hits_vuv[event_no]/event_E;
                                //double LY_val_vis = hits_vis[event_no]/event_E;
				LY_vals_both.push_back(LY_val_both);
                                //LY_vals_vuv.push_back(LY_val_vuv);
                                //LY_vals_vis.push_back(LY_val_vis);
			}
		}

		// calculate mean and stdev of LY for this bin for plotting 
		double m_both; double stdev_both;
               // double m_vuv; double stdev_vuv;
                //double m_vis; double stdev_vis;		
		
		// both
		// mean
		double sum_both = std::accumulate(std::begin(LY_vals_both), std::end(LY_vals_both), 0.0);
                //double sum_vuv = std::accumulate(std::begin(LY_vals_vuv), std::end(LY_vals_vuv), 0.0);
                //double sum_vis = std::accumulate(std::begin(LY_vals_vis), std::end(LY_vals_vis), 0.0);
		m_both =  sum_both / LY_vals_both.size();
                //m_vuv = sum_vuv / LY_vals_vuv.size();
                //m_vis = sum_vis / LY_vals_vis.size();
		// stdev
		double accum_both = 0.0;
                //double accum_vuv = 0.0;
                //double accum_vis = 0.0;
		std::for_each (std::begin(LY_vals_both), std::end(LY_vals_both), [&](const double d) { accum_both += (d - m_both) * (d - m_both); } );
		stdev_both = sqrt(accum_both / (LY_vals_both.size()-1));
                //std::for_each (std::begin(LY_vals_vuv), std::end(LY_vals_vuv), [&](const double d) { accum_vuv += (d - m_vuv) * (d - m_vuv); } );
                //stdev_vuv = sqrt(accum_vuv / (LY_vals_vuv.size()-1));
                //std::for_each (std::begin(LY_vals_vis), std::end(LY_vals_vis), [&](const double d) { accum_vis += (d - m_vis) * (d - m_vis); } );
                //stdev_vis = sqrt(accum_vis / (LY_vals_vis.size()-1));

		
		// add mean and stdev to vectors for plotting
		LY_both.push_back(m_both);
                //LY_vuv.push_back(m_vuv);
                //LY_vis.push_back(m_vis);		
		err_y_both.push_back(stdev_both);
                //err_y_vuv.push_back(stdev_vuv);
                //err_y_vis.push_back(stdev_vis);

		

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
        //TGraph *gr2 = new TGraphErrors(x_bin.size(), &(x_bin[0]), &(LY_vuv[0]),&(err_x[0]),&(err_y_vuv[0]));
        //TGraph *gr3 = new TGraphErrors(x_bin.size(), &(x_bin[0]), &(LY_vis[0]),&(err_x[0]),&(err_y_vis[0]));	
        
        gr1->Fit("pol2");

	gr1->SetMarkerColor(1);
        //gr2->SetMarkerColor(kBlue);
        //gr3->SetMarkerColor(kRed);
	
	gr1->SetLineColor(1);
        //gr2->SetLineColor(kBlue);
        //gr3->SetLineColor(kRed);
	
	gr1->SetMarkerStyle(20);
        //gr2->SetMarkerStyle(20);
        //gr3->SetMarkerStyle(20);
	
	gr1->SetMarkerSize(1);
       // gr2->SetMarkerSize(1);
        //gr3->SetMarkerSize(1);
	
	//legend->AddEntry(gr1, "Total" ,"p");
        //legend->AddEntry(gr2, "VUV", "p");
        //legend->AddEntry(gr3, "Visible", "p");
	
	mg->Add(gr1);
        //mg->Add(gr2);
        //mg->Add(gr3);
	
        //TF1 *f1 = new TF1("f1","gaus",1,3);
        //gr1->Fit("f1","F");

	// draw graph
	mg->GetXaxis()->SetTitle("Drift distance [cm]");
	mg->GetYaxis()->SetTitle("Light Yield (photons/MeV)");
	mg->GetHistogram()->SetTitle("");

	mg->GetXaxis()->SetRangeUser(0,380);
	mg->GetYaxis()->SetRangeUser(0,50);

	mg->Draw("ap");

        TF1 *g1 = new TF1("m1", "pol2", 5,350);
        //TF1 *g1 = new TF1("m1", "[a]*exp(-[b]*x-[c])", 5, 350);
        mg->Fit(g1,"R");

        double p0=g1->GetParameter(0);
        double p1=g1->GetParameter(1);
        double p2=g1->GetParameter(2);
     
	//legend->Draw("same");
	c1->Update();

        TH1D *E_recons_h = new TH1D("Reconstructed Energy", "Reconstructed Visible Energy;Reconstructed visible energy [MeV];Entries", 100, 0, 20);

        vector<double> E_recons_vect(number_events,0);

        for (int i = 0; i < event_tree->GetEntries(); i++){
             event_tree->GetEntry(i);
             double recons_E = hits_both[i]/(p2*x_recon[i]*x_recon[i]+p1*x_recon[i]+p0);
             E_recons_vect[i]=recons_E;
             E_recons_h->Fill(recons_E);}
           
        visible_energy->SetLineColor(kBlue);
        E_recons_h->SetLineColor(kRed);
        TLatex *t1 = new TLatex(10, 300,"True visible energy");
        TLatex *t2 = new TLatex(10,250,"Reconstructed visible energy");
        t1->SetTextColor(kBlue);
        t2->SetTextColor(kRed); 
        visible_energy->Draw();
        E_recons_h->Draw("same");
        t1->Draw("same");
        t2->Draw("same"); 
        
   

    return 0;
}
