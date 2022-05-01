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

//This code is to calculate the Fprompt of Rn222 from it's pulse shape//

int energy_bkg(){

////////////////////////
////Reading parameter///
////////////////////////

//////////////////////////
////Define needed number//
//////////////////////////

        const int NUM_BINS = 2000;//10000[ns]/NUM_BINS is the timing resolution
        int reso = 10000/NUM_BINS;//Timing resolution
        bool photon_cut = false;
        int photon_cut_num = 10;

                ///////////////////
                //Open root files//
                ///////////////////

                  //Solar//
                  TFile *fS = new TFile("scintillation_toy_mc/output/events_unsmeared.root");
                  TTree* data_treeS = (TTree*)fS->Get("data_tree");//If it works on total photon, it works on vuv
                  TTree* data_treeS_vuv = (TTree*)fS->Get("data_tree_vuv");//Without foils
                  TTree* event_treeS = (TTree*)fS->Get("event_tree"); //Haven't consider energy ye

                  int data_eventS;int data_eventS_vuv;int data_pmtS; double data_timeS;double data_timeS_vuv;double event_decay_timeS;double event_ES;double event_x_posS;//[cm]

                  data_treeS->SetBranchAddress("data_time", &data_timeS);
                  data_treeS->SetBranchAddress("data_event", &data_eventS);
                  data_treeS_vuv->SetBranchAddress("data_time_vuv", &data_timeS_vuv);//VUV only
                  data_treeS_vuv->SetBranchAddress("data_event_vuv", &data_eventS_vuv);
                  event_treeS->SetBranchAddress("event_decay_time", &event_decay_timeS);
                  event_treeS->SetBranchAddress("event_E", &event_ES);
                  event_treeS->SetBranchAddress("event_x_pos", &event_x_posS);



                  //Bi214//
                  TFile *fBi = new TFile("scintillation_toy_mc/output/events_Bi214.root");
                  TTree* data_treeBi = (TTree*)fBi->Get("data_tree");//If it works on total photon, it works on vuv
                  TTree* data_treeBi_vuv = (TTree*)fBi->Get("data_tree_vuv");//Without foils
                  TTree* event_treeBi = (TTree*)fBi->Get("event_tree"); //Haven't consider energy ye

                  int data_eventBi;int data_eventBi_vuv;int data_pmtBi; double data_timeBi;double data_timeBi_vuv;double event_decay_timeBi;double event_EBi;double event_x_posBi;//[cm]

                  data_treeBi->SetBranchAddress("data_time", &data_timeBi);
                  data_treeBi->SetBranchAddress("data_event", &data_eventBi);
                  data_treeBi_vuv->SetBranchAddress("data_time_vuv", &data_timeBi_vuv);//VUV only
                  data_treeBi_vuv->SetBranchAddress("data_event_vuv", &data_eventBi_vuv);
                  event_treeBi->SetBranchAddress("event_decay_time", &event_decay_timeBi);
                  event_treeBi->SetBranchAddress("event_E", &event_EBi);
                  event_treeBi->SetBranchAddress("event_x_pos", &event_x_posBi);



                  //Ar39//
                  TFile *fAr = new TFile("scintillation_toy_mc/output/events_39Ar_2.root");
                  TTree* data_treeAr = (TTree*)fAr->Get("data_tree");//If it works on total photon, it works on vuv
                  TTree* data_treeAr_vuv = (TTree*)fAr->Get("data_tree_vuv");//Without foils
                  TTree* event_treeAr = (TTree*)fAr->Get("event_tree"); //Haven't consider energy ye

                  int data_eventAr;int data_eventAr_vuv;int data_pmtAr; double data_timeAr;double data_timeAr_vuv;double event_decay_timeAr;double event_EAr;double event_x_posAr;//[cm]

                  data_treeAr->SetBranchAddress("data_time", &data_timeAr);
                  data_treeAr->SetBranchAddress("data_event", &data_eventAr);
                  data_treeAr_vuv->SetBranchAddress("data_time_vuv", &data_timeAr_vuv);//VUV only
                  data_treeAr_vuv->SetBranchAddress("data_event_vuv", &data_eventAr_vuv);
                  event_treeAr->SetBranchAddress("event_decay_time", &event_decay_timeAr);
                  event_treeAr->SetBranchAddress("event_E", &event_EAr);
                  event_treeAr->SetBranchAddress("event_x_pos", &event_x_posAr);

                  //Ar42//
                  TFile *fAr42 = new TFile("scintillation_toy_mc/output/events_42Ar_2.root");
                  TTree* data_treeAr42 = (TTree*)fAr42->Get("data_tree");//If it works on total photon, it works on vuv
                  TTree* data_treeAr42_vuv = (TTree*)fAr42->Get("data_tree_vuv");//Without foils
                  TTree* event_treeAr42 = (TTree*)fAr42->Get("event_tree"); //Haven't consider energy ye

                  int data_eventAr42;int data_eventAr42_vuv;int data_pmtAr42; double data_timeAr42;double data_timeAr42_vuv;double event_decay_timeAr42;double event_EAr42;double event_x_posAr42;//[cm]

                  data_treeAr42->SetBranchAddress("data_time", &data_timeAr42);
                  data_treeAr42->SetBranchAddress("data_event", &data_eventAr42);
                  data_treeAr42_vuv->SetBranchAddress("data_time_vuv", &data_timeAr42_vuv);//VUV only
                  data_treeAr42_vuv->SetBranchAddress("data_event_vuv", &data_eventAr42_vuv);
                  event_treeAr42->SetBranchAddress("event_decay_time", &event_decay_timeAr42);
                  event_treeAr42->SetBranchAddress("event_E", &event_EAr42);
                  event_treeAr42->SetBranchAddress("event_x_pos", &event_x_posAr42);

                  //K42//
                  TFile *fK = new TFile("scintillation_toy_mc/output/events_K42_2.root");
                  TTree* data_treeK = (TTree*)fK->Get("data_tree");//If it works on total photon, it works on vuv
                  TTree* data_treeK_vuv = (TTree*)fK->Get("data_tree_vuv");//Without foils
                  TTree* event_treeK = (TTree*)fK->Get("event_tree"); //Haven't consider energy ye

                  int data_eventK;int data_eventK_vuv;int data_pmtK; double data_timeK;double data_timeK_vuv;double event_decay_timeK;double event_EK;double event_x_posK;//[cm]

                  data_treeK->SetBranchAddress("data_time", &data_timeK);
                  data_treeK->SetBranchAddress("data_event", &data_eventK);
                  data_treeK_vuv->SetBranchAddress("data_time_vuv", &data_timeK_vuv);//VUV only
                  data_treeK_vuv->SetBranchAddress("data_event_vuv", &data_eventK_vuv);
                  event_treeK->SetBranchAddress("event_decay_time", &event_decay_timeK);
                  event_treeK->SetBranchAddress("event_E", &event_EK);
                  event_treeK->SetBranchAddress("event_x_pos", &event_x_posK);

                  //kr85B1//
                  TFile *fkrb1 = new TFile("scintillation_toy_mc/output/events_Kr85B1_2.root");
                  TTree* data_treekrb1 = (TTree*)fkrb1->Get("data_tree");//If it works on total photon, it works on vuv
                  TTree* data_treekrb1_vuv = (TTree*)fkrb1->Get("data_tree_vuv");//Without foils
                  TTree* event_treekrb1 = (TTree*)fkrb1->Get("event_tree"); //Haven't consider energy ye

                  int data_eventkrb1;int data_eventkrb1_vuv;int data_pmtkrb1; double data_timekrb1;double data_timekrb1_vuv;double event_decay_timekrb1;double event_Ekrb1;double event_x_poskrb1;//[cm]

                  data_treekrb1->SetBranchAddress("data_time", &data_timekrb1);
                  data_treekrb1->SetBranchAddress("data_event", &data_eventkrb1);
                  data_treekrb1_vuv->SetBranchAddress("data_time_vuv", &data_timekrb1_vuv);//VUV only
                  data_treekrb1_vuv->SetBranchAddress("data_event_vuv", &data_eventkrb1_vuv);
                  event_treekrb1->SetBranchAddress("event_decay_time", &event_decay_timekrb1);
                  event_treekrb1->SetBranchAddress("event_E", &event_Ekrb1);
                  event_treekrb1->SetBranchAddress("event_x_pos", &event_x_poskrb1);

                  //kr85B2//

                  TFile *fkrb2 = new TFile("scintillation_toy_mc/output/events_Kr85B2_2.root");
                  TTree* data_treekrb2 = (TTree*)fkrb2->Get("data_tree");//If it works on total photon, it works on vuv
                  TTree* data_treekrb2_vuv = (TTree*)fkrb2->Get("data_tree_vuv");//Without foils
                  TTree* event_treekrb2 = (TTree*)fkrb2->Get("event_tree"); //Haven't consider energy ye

                  int data_eventkrb2;int data_eventkrb2_vuv;int data_pmtkrb2; double data_timekrb2;double data_timekrb2_vuv;double event_decay_timekrb2;double event_Ekrb2;double event_x_poskrb2;//[cm]

                  data_treekrb2->SetBranchAddress("data_time", &data_timekrb2);
                  data_treekrb2->SetBranchAddress("data_event", &data_eventkrb2);
                  data_treekrb2_vuv->SetBranchAddress("data_time_vuv", &data_timekrb2_vuv);//VUV only
                  data_treekrb2_vuv->SetBranchAddress("data_event_vuv", &data_eventkrb2_vuv);
                  event_treekrb2->SetBranchAddress("event_decay_time", &event_decay_timekrb2);
                  event_treekrb2->SetBranchAddress("event_E", &event_Ekrb2);
                  event_treekrb2->SetBranchAddress("event_x_pos", &event_x_poskrb2);

                  //kr85G1//
                  TFile *fkrg1 = new TFile("scintillation_toy_mc/output/events_Kr85G1_2.root");
                  TTree* data_treekrg1 = (TTree*)fkrg1->Get("data_tree");//If it works on total photon, it works on vuv
                  TTree* data_treekrg1_vuv = (TTree*)fkrg1->Get("data_tree_vuv");//Without foils
                  TTree* event_treekrg1 = (TTree*)fkrg1->Get("event_tree"); //Haven't consider energy ye

                  int data_eventkrg1;int data_eventkrg1_vuv;int data_pmtkrg1; double data_timekrg1;double data_timekrg1_vuv;double event_decay_timekrg1;double event_Ekrg1;double event_x_poskrg1;//[cm]

                  data_treekrg1->SetBranchAddress("data_time", &data_timekrg1);
                  data_treekrg1->SetBranchAddress("data_event", &data_eventkrg1);
                  data_treekrg1_vuv->SetBranchAddress("data_time_vuv", &data_timekrg1_vuv);//VUV only
                  data_treekrg1_vuv->SetBranchAddress("data_event_vuv", &data_eventkrg1_vuv);
                  event_treekrg1->SetBranchAddress("event_decay_time", &event_decay_timekrg1);
                  event_treekrg1->SetBranchAddress("event_E", &event_Ekrg1);
                  event_treekrg1->SetBranchAddress("event_x_pos", &event_x_poskrg1);

                  //kr85G2//
                  TFile *fkrg2 = new TFile("scintillation_toy_mc/output/events_Kr85G2_2.root");
                  TTree* data_treekrg2 = (TTree*)fkrg2->Get("data_tree");//If it works on total photon, it works on vuv
                  TTree* data_treekrg2_vuv = (TTree*)fkrg2->Get("data_tree_vuv");//Without foils
                  TTree* event_treekrg2 = (TTree*)fkrg2->Get("event_tree"); //Haven't consider energy ye

                  int data_eventkrg2;int data_eventkrg2_vuv;int data_pmtkrg2; double data_timekrg2;double data_timekrg2_vuv;double event_decay_timekrg2;double event_Ekrg2;double event_x_poskrg2;//[cm]

                  data_treekrg2->SetBranchAddress("data_time", &data_timekrg2);
                  data_treekrg2->SetBranchAddress("data_event", &data_eventkrg2);
                  data_treekrg2_vuv->SetBranchAddress("data_time_vuv", &data_timekrg2_vuv);//VUV only
                  data_treekrg2_vuv->SetBranchAddress("data_event_vuv", &data_eventkrg2_vuv);
                  event_treekrg2->SetBranchAddress("event_decay_time", &event_decay_timekrg2);
                  event_treekrg2->SetBranchAddress("event_E", &event_Ekrg2);
                  event_treekrg2->SetBranchAddress("event_x_pos", &event_x_poskrg2);
                
                  //Po214//
                  TFile *fpo = new TFile("scintillation_toy_mc/output/events_Po214.root");
                  TTree* data_treepo = (TTree*)fpo->Get("data_tree");//If it works on total photon, it works on vuv
                  TTree* data_treepo_vuv = (TTree*)fpo->Get("data_tree_vuv");//Without foils
                  TTree* event_treepo = (TTree*)fpo->Get("event_tree"); //Haven't consider energy ye

                  int data_eventpo;int data_eventpo_vuv;int data_pmtpo; double data_timepo;double data_timepo_vuv;double event_decay_timepo;double event_Epo;double event_x_pospo;//[cm]

                  data_treepo->SetBranchAddress("data_time", &data_timepo);
                  data_treepo->SetBranchAddress("data_event", &data_eventpo);
                  data_treepo_vuv->SetBranchAddress("data_time_vuv", &data_timepo_vuv);//VUV only
                  data_treepo_vuv->SetBranchAddress("data_event_vuv", &data_eventpo_vuv);
                  event_treepo->SetBranchAddress("event_decay_time", &event_decay_timepo);
                  event_treepo->SetBranchAddress("event_E", &event_Epo);
                  event_treepo->SetBranchAddress("event_x_pos", &event_x_pospo);

                  //Po218//
                  TFile *fpo218 = new TFile("scintillation_toy_mc/output/events_Po218.root");
                  TTree* data_treepo218 = (TTree*)fpo218->Get("data_tree");//If it works on total photon, it works on vuv
                  TTree* data_treepo218_vuv = (TTree*)fpo218->Get("data_tree_vuv");//Without foils
                  TTree* event_treepo218 = (TTree*)fpo218->Get("event_tree"); //Haven't consider energy ye

                  int data_eventpo218;int data_eventpo218_vuv;int data_pmtpo218; double data_timepo218;double data_timepo218_vuv;double event_decay_timepo218;double event_Epo218;double event_x_pospo218;//[cm]

                  data_treepo218->SetBranchAddress("data_time", &data_timepo218);
                  data_treepo218->SetBranchAddress("data_event", &data_eventpo218);
                  data_treepo218_vuv->SetBranchAddress("data_time_vuv", &data_timepo218_vuv);//VUV only
                  data_treepo218_vuv->SetBranchAddress("data_event_vuv", &data_eventpo218_vuv);
                  event_treepo218->SetBranchAddress("event_decay_time", &event_decay_timepo218);
                  event_treepo218->SetBranchAddress("event_E", &event_Epo218);
                  event_treepo218->SetBranchAddress("event_x_pos", &event_x_pospo218);

                  //Rn222//
                  TFile *frn = new TFile("scintillation_toy_mc/output/events_Rn222.root");
                  TTree* data_treern = (TTree*)frn->Get("data_tree");//If it works on total photon, it works on vuv
                  TTree* data_treern_vuv = (TTree*)frn->Get("data_tree_vuv");//Without foils
                  TTree* event_treern = (TTree*)frn->Get("event_tree"); //Haven't consider energy ye

                  int data_eventrn;int data_eventrn_vuv;int data_pmtrn; double data_timern;double data_timern_vuv;double event_decay_timern;double event_Ern;double event_x_posrn;//[cm]

                  data_treern->SetBranchAddress("data_time", &data_timern);
                  data_treern->SetBranchAddress("data_event", &data_eventrn);
                  data_treern_vuv->SetBranchAddress("data_time_vuv", &data_timern_vuv);//VUV only
                  data_treern_vuv->SetBranchAddress("data_event_vuv", &data_eventrn_vuv);
                  event_treern->SetBranchAddress("event_decay_time", &event_decay_timern);
                  event_treern->SetBranchAddress("event_E", &event_Ern);
                  event_treern->SetBranchAddress("event_x_pos", &event_x_posrn);

                  //Pb214//
                  TFile *fpb = new TFile("scintillation_toy_mc/output/events_Po210.root");
                  TTree* data_treepb = (TTree*)fpb->Get("data_tree");//If it works on total photon, it works on vuv
                  TTree* data_treepb_vuv = (TTree*)fpb->Get("data_tree_vuv");//Without foils
                  TTree* event_treepb = (TTree*)fpb->Get("event_tree"); //Haven't consider energy ye

                  int data_eventpb;int data_eventpb_vuv;int data_pmtpb; double data_timepb;double data_timepb_vuv;double event_decay_timepb;double event_Epb;double event_x_pospb;//[cm]

                  data_treepb->SetBranchAddress("data_time", &data_timepb);
                  data_treepb->SetBranchAddress("data_event", &data_eventpb);
                  data_treepb_vuv->SetBranchAddress("data_time_vuv", &data_timepb_vuv);//VUV only
                  data_treepb_vuv->SetBranchAddress("data_event_vuv", &data_eventpb_vuv);
                  event_treepb->SetBranchAddress("event_decay_time", &event_decay_timepb);
                  event_treepb->SetBranchAddress("event_E", &event_Epb);
                  event_treepb->SetBranchAddress("event_x_pos", &event_x_pospb);

                  //neutrons//
                  TFile *fneutrons = new TFile("scintillation_toy_mc/output/events_neutrons.root");
                  TTree* data_treeneutrons = (TTree*)fneutrons->Get("data_tree");
                  TTree* data_treeneutrons_vuv = (TTree*)fneutrons->Get("data_tree_vuv");
                  TTree* event_treeneutrons = (TTree*)fneutrons->Get("event_tree");

                  int data_eventneutrons;int data_eventneutrons_vuv;int data_pmtneutrons;double data_timeneutrons;double data_timeneutrons_vuv;double event_decay_timeneutrons;double event_Eneutrons;double event_x_posneutrons;
  
                  data_treeneutrons->SetBranchAddress("data_time", &data_timeneutrons);
                  data_treeneutrons->SetBranchAddress("data_event", &data_eventneutrons);
                  data_treeneutrons_vuv->SetBranchAddress("data_time_vuv", &data_timeneutrons_vuv);
                  data_treeneutrons_vuv->SetBranchAddress("data_event_vuv", &data_eventneutrons_vuv);
                  event_treeneutrons->SetBranchAddress("event_decay_time", &event_decay_timeneutrons);
                  event_treeneutrons->SetBranchAddress("event_E", &event_Eneutrons);
                  event_treeneutrons->SetBranchAddress("event_x_pos", &event_x_posneutrons);



             TH1D *energy_S = new TH1D("Energy","Energy;Energy[MeV]",100,0,15);
             TH1D *energy_Ar39 = new TH1D("Energy","Energy;Energy[MeV]",100,0,15);
             TH1D *energy_Ar42 = new TH1D("Energy","Energy;Energy[MeV]",100,0,15);
             TH1D *energy_K = new TH1D("Energy","Energy;Energy[MeV]",100,0,15);
             TH1D *energy_kr85b1 = new TH1D("Energy","Energy;Energy[MeV]",100,0,15);
             TH1D *energy_kr85b2 = new TH1D("Energy","Energy;Energy[MeV]",100,0,15);
             TH1D *energy_kr85g1 = new TH1D("Energy","Energy;Energy[MeV]",100,0,15);
             TH1D *energy_kr85g2 = new TH1D("Energy","Energy;Energy[MeV]",100,0,15);
             TH1D *energy_po = new TH1D("Energy","Energy;Energy[MeV]",100,0,15);
             TH1D *energy_po218 = new TH1D("Energy","Energy;Energy[MeV]",100,0,15);
             TH1D *energy_rn = new TH1D("Energy","Energy;Energy[MeV]",100,0,15);
             TH1D *energy_Bi = new TH1D("Energy","Energy;Energy[MeV]",100,0,15);
             TH1D *energy_pb = new TH1D("Energy","Energy;Energy[MeV]",100,0,15);
             TH1D *energy_neutrons = new TH1D("Energy","Energy;Energy[MeV]",100,0,15);


            for(int i = 0;i<event_treeS->GetEntries();i++){
                  event_treeS->GetEntry(i);
                  energy_S->Fill(event_ES);}
            for(int i = 0;i<event_treeAr->GetEntries();i++){
                  event_treeAr->GetEntry(i);
                   energy_Ar39->Fill(event_EAr);}
            for(int i = 0;i<event_treeAr42->GetEntries();i++){
                  event_treeAr42->GetEntry(i);
                   energy_Ar42->Fill(event_EAr42);}
            for(int i = 0;i<event_treeK->GetEntries();i++){
                  event_treeK->GetEntry(i);
                   energy_K->Fill(event_EK);}
            for(int i = 0;i<event_treekrb1->GetEntries();i++){
                  event_treekrb1->GetEntry(i);
                   energy_kr85b1->Fill(event_Ekrb1);}
            for(int i = 0;i<event_treekrb2->GetEntries();i++){
                  event_treekrb2->GetEntry(i);
                   energy_kr85b2->Fill(event_Ekrb2);}
            for(int i = 0;i<event_treekrg1->GetEntries();i++){
                  event_treekrg1->GetEntry(i);
                   energy_kr85g1->Fill(event_Ekrg1);}
            for(int i = 0;i<event_treekrg2->GetEntries();i++){
                  event_treekrg2->GetEntry(i);
                   energy_kr85g2->Fill(event_Ekrg2);}
            for(int i = 0;i<event_treepo->GetEntries();i++){
                  event_treepo->GetEntry(i);
                   energy_po->Fill(event_Epo);}
            for(int i = 0;i<event_treeBi->GetEntries();i++){
                  event_treeBi->GetEntry(i);
                   energy_Bi->Fill(event_EBi);}
            for(int i = 0;i<event_treepo218->GetEntries();i++){
                  event_treepo218->GetEntry(i);
                   energy_po218->Fill(event_Epo218);}
            for(int i = 0;i<event_treern->GetEntries();i++){
                  event_treern->GetEntry(i);
                   energy_rn->Fill(event_Ern);}
            for(int i = 0;i<event_treepb->GetEntries();i++){
                  event_treepb->GetEntry(i);
                   energy_pb->Fill(event_Epb);}
            for(int i = 0;i<event_treeneutrons->GetEntries();i++){
                  event_treeneutrons->GetEntry(i);
                  energy_neutrons->Fill(event_Eneutrons);


    energy_Ar39->SetLineWidth(0);
    energy_Ar39->SetFillColor(kTeal+4);
    energy_Ar42->SetLineWidth(0);
    energy_Ar42->SetFillColor(2);
    energy_rn->SetLineWidth(0);
    energy_rn->SetFillColor(kBlue+2);
    energy_kr85b1->SetLineWidth(0);
    energy_kr85b1->SetFillColor(kOrange+1);
    energy_kr85b2->SetLineWidth(0);
    energy_kr85b2->SetFillColor(6);
    energy_kr85g1->SetLineWidth(0);
    energy_kr85g1->SetFillColor(7);
    energy_kr85g2->SetLineWidth(0);
    energy_kr85g2->SetFillColor(8);
    energy_po->SetLineWidth(0);
    energy_po->SetFillColor(kGreen+3);
    energy_po218->SetLineWidth(0);
    energy_po218->SetFillColor(kViolet-5);
    energy_Bi->SetLineWidth(0);
    energy_Bi->SetFillColor(11);
    energy_K->SetLineWidth(0);
    energy_K->SetFillColor(kBlue-7);
    energy_pb->SetLineWidth(0);
    energy_pb->SetFillColor(kAzure+8);
    energy_neutrons->SetLineWidth(0);
    energy_neutrons->SetFillColor(kAzure+9);
    
   
    THStack *h_stack = new THStack("stack", ";Energy [MeV];Events per second per 10kT");
 
 
    h_stack->Add(energy_Ar39);
    h_stack->Add(energy_Ar42);
    h_stack->Add(energy_kr85b1);
    h_stack->Add(energy_kr85b2);
    h_stack->Add(energy_kr85g1);
    h_stack->Add(energy_kr85g2);
    h_stack->Add(energy_Bi);
    h_stack->Add(energy_K);
    h_stack->Add(energy_po);
    h_stack->Add(energy_po218);
    h_stack->Add(energy_rn);
    h_stack->Add(energy_pb);        
    h_stack->Add(energy_neutrons);  
    h_stack->Draw("hist");
    TLegend *legend = new TLegend(0.5,0.4,0.7,0.6);
    legend->AddEntry(energy_Ar39, "^{39}Ar","f");
    legend->AddEntry(energy_Ar42,"^{42}Ar", "f");
    legend->AddEntry(energy_kr85b1, "^{85}Kr#beta_{1}","f");
    legend->AddEntry(energy_kr85b2, "^{85}Kr#beta_{2}","f");
    legend->AddEntry(energy_kr85g1, "^{85}Kr#gamma_{1}","f");
    legend->AddEntry(energy_kr85g2, "^{85}Kr#gamma_{2}","f");
    legend->AddEntry(energy_Bi, "^{214}Bi","f");
    legend->AddEntry(energy_po, "^{214}Po","f");
    legend->AddEntry(energy_po218, "^{218}Po","f");
    legend->AddEntry(energy_rn, "^{222}Rn","f");
    legend->AddEntry(energy_K, "^{42}K","f");
    legend->AddEntry(energy_pb, "^{210}Po", "f");
    legend->AddEntry(energy_neutrons, "neutrons", "f"
    legend->SetTextFont(42);
    legend->Draw();
    gPad->SetLogy();
   
    TChain ch("T");
    ch.Add("events_Bi214.root");
    ch.Add("events_Po218.root");
    ch.Add("events_Po214.root");
    ch.Merge("all_bkgs.root");
 
      
/*

             //energy_S->Draw();
             //energy_Ar39->SetFillStyle(3001);
             energy_Ar39->SetLineWidth(0);
             energy_Ar39->SetFillColor(9);
             //energy_Ar42->SetFillStyle(3001);
             energy_Ar42->SetLineWidth(0);
             energy_Ar42->SetFillColor(24);
             //energy_K->SetFillStyle(3001);
             energy_K->SetLineWidth(0);
             energy_K->SetFillColor(30);
             //energy_kr85b1->SetFillStyle(3001);
             energy_kr85b1->SetLineWidth(0);
             energy_kr85b1->SetFillColor(38);
             //energy_Bi->SetFillStyle(3001);
             energy_Bi->SetLineWidth(0);
             energy_Bi->SetFillColor(39);
             //energy_kr85b2->SetFillStyle(3001);
             energy_kr85b2->SetLineWidth(0);
             energy_kr85b2->SetFillColor(46);
             //energy_kr85g1->SetFillStyle(3001);
             energy_kr85g1->SetLineWidth(0);
             energy_kr85g1->SetFillColor(34);
             //energy_kr85g2->SetFillStyle(3001);
             energy_kr85g2->SetLineWidth(0);
             energy_kr85g2->SetFillColor(8);
             //energy_po->SetFillStyle(3001);
             energy_po->SetLineWidth(0);
             energy_po->SetFillColor(9);
             //energy_po218->SetFillStyle(3001);
             energy_po218->SetLineWidth(0);
             energy_po218->SetFillColor(29);
             //energy_rn->SetFillStyle(3001);
             energy_rn->SetLineWidth(0);
             energy_rn->SetFillColor(41);
             energy_Ar39->Draw();
             energy_Ar42->Draw("same");
             energy_K->Draw("same");
             energy_kr85b1->Draw("same");
             energy_kr85b2->Draw("same");
             energy_kr85g1->Draw("same");
             energy_kr85g2->Draw("same");
             energy_po->Draw("same");
             energy_Bi->Draw("same");
             energy_po218->Draw("same");
             energy_rn->Draw("same");
             TLegend *legend = new TLegend(0.5,0.4,0.7,0.6);
             legend->AddEntry(energy_Ar39, "Ar39","f");
             legend->AddEntry(energy_Ar42,"Ar42", "f");
             legend->AddEntry(energy_kr85b1, "Kr85B1","f");
             legend->AddEntry(energy_kr85b2, "Kr85B2","f");
             legend->AddEntry(energy_kr85g1, "Kr85G1","f");
             legend->AddEntry(energy_kr85g2, "Kr85G2","f");
             legend->AddEntry(energy_Bi, "Bi214","f");
             legend->AddEntry(energy_po, "Po214","f");
             legend->AddEntry(energy_po218, "Po218","f");
             legend->AddEntry(energy_rn, "Rn222","f");
             legend->AddEntry(energy_K, "K42","f");
             legend->Draw();
             gPad->SetLogy();
*/


return 0;
}                   
           
