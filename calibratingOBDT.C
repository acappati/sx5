// **************************
//
// run with: 
//       root -l -b -q calibratingOBDT.C++
//
// **************************

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <math.h>
#include <iomanip>

#include "TString.h"
#include "TLegend.h"
#include "TCanvas.h"
#include "TFile.h"
#include "TH1.h"
#include "TH2.h"
#include "TMath.h"
#include "TStyle.h"
#include "TSystem.h"
#include "TTree.h"
#include "TAxis.h"
#include "TF1.h"
#include "TGraph.h"
#include "TLine.h"
#include "TPaveText.h"
#include "TRandom3.h"
#include "TPaveText.h"
#include "TGraphErrors.h"


void calibratingOBDT(){

  gStyle->SetOptFit(1);

  // width OBDT 4
  float x_[18] = {0x5A000000, 0xBC000000, 0xAB000000, 0x5B000000, 0x4A000000, 0x3A000000, 0xA0000000, 0x2A000000, 0x3D000000, 0x1C000000, 0x1A000000, 0x5C000000, 0x4D000000, 0x6A000000, 0x7A000000, 0x8A000000, 0x9A000000, 0x9D000000};
  float v_[18] = {2.32, 4.34, 4.34, 2.32, 1.91, 1.49, 4.1, 1.0, 1.57, 0.7, 0.66, 2.38, 1.98, 2.7, 3.1, 3.57, 3.99, 4.07};  // V 

  TCanvas* c = new TCanvas("c","c", 800, 600);
  c->cd();
  TGraph* g = new TGraph(18, x_, v_); 
  g->SetMarkerStyle(20);
  g->SetTitle("OBDT 4 width");
  g->GetXaxis()->SetTitle("Width commands (hexa)");
  g->GetYaxis()->SetTitle("Width (V)");
  TF1 *f1 = new TF1("f1", "[0]+[1]*x", 500.e6, 3000.e6);
  f1->SetParameter(0,0.1);
  f1->SetParameter(1,1.);
  f1->SetLineColor(kRed);
  g->Fit("f1","R");
  g->Draw("AP");
  c->SaveAs("obdt_N4_width.png");

  

  // width OBDT 14
  float x1_[15] = {0x5A000000, 0x5B000000, 0x4A000000, 0x4D000000, 0x3A000000, 0x2A000000, 0x1A000000, 0x1B000000, 0x6A000000, 0x7A000000, 0x8A000000, 0x9A000000, 0xAA000000, 0xAD000000, 0xAF000000, };
  float v1_[15] = {2.3, 2.37, 1.89, 1.97, 1.48, 1.08, 0.66, 0.74, 2.7, 3.1, 3.5, 3.9, 4.31, 4.35, 4.35};  // V

  TCanvas* c1 = new TCanvas("c1","c1", 800, 600);
  c1->cd();
  TGraph* g1 = new TGraph(15, x1_, v1_); 
  g1->SetMarkerStyle(20);
  g1->SetTitle("OBDT 14 width");
  g1->GetXaxis()->SetTitle("Width commands (hexa)");
  g1->GetYaxis()->SetTitle("Width (V)");
  TF1 *f2 = new TF1("f2", "[0]+[1]*x", 500.e6, 3000.e6);
  f2->SetParameter(0,0.1);
  f2->SetParameter(1,1.);
  f2->SetLineColor(kBlue);
  g1->Fit("f2","R");
  g1->Draw("AP");
  c1->SaveAs("obdt_N14_width.png");

  
  // width both 14 and 4
  gStyle->SetOptFit(0);
  TCanvas* c2 = new TCanvas("c2","c2",800,600);
  c2->cd();
  g->SetMarkerStyle(20);
  g->SetMarkerColor(kRed);
  g->SetLineColor(kRed);
  g->SetTitle("OBDT 4 and 14 width");
  g->GetXaxis()->SetTitle("Width commands (hexa)");
  g->GetYaxis()->SetTitle("Width (V)");
  g->Draw("AP");
  g1->SetMarkerStyle(24);
  g1->SetMarkerColor(kBlue);
  g1->SetLineColor(kBlue);
  g1->Draw("SAMEP");
  TLegend* l2 = new TLegend(0.78,0.42,0.98,0.57);
  l2->AddEntry(g,"OBDT 4","pl");
  l2->AddEntry(g1,"OBDT 14", "pl");
  l2->SetFillColor(kWhite);
  l2->SetLineColor(kBlack);
  l2->SetTextFont(43);
  l2->SetTextSize(20);
  l2->Draw();
  c2->Update();
  c2->SaveAs("obdt_N14_N4_width.png");




  // threshold OBDT 14
  float x4_[17] = {0x1A000000, 0x2A000000, 0x2D000000, 0x3A000000, 0x4A000000, 0x5A000000, 0x6A000000, 0x7A000000, 0x8A000000, 0x9A000000, 0xAA000000, 0xAD000000, 0xAF000000, 0xBD000000, 0xC0000000, 0xCD000000, 0xFF000000};
  float v4_[17] = {0.001, 1.67, 1.92 , 1.18, 1.43, 1.67, 1.9, 2.17, 2.41, 2.56, 2.71, 2.74, 2.75, 2.95, 2.99 , 3.18 ,3.7};  // V

  TCanvas* c4 = new TCanvas("c4","c4", 800, 600);
  c4->cd();
  TGraph* g4 = new TGraph(18, x4_, v4_); 
  g4->SetMarkerStyle(20);
  g4->SetTitle("OBDT 14 threshold");
  g4->GetXaxis()->SetTitle("Threshold commands (hexa)");
  g4->GetYaxis()->SetTitle("Vthr - Vbias (V)");
  g4->Draw("AP");
  c4->SaveAs("obdt_N14_threshold.png");



  // threshold OBDT 4
  float x5_[14] = {0x1A000000, 0x2A000000, 0x3A000000, 0x4A000000, 0x5A000000, 0x6A000000, 0x7A000000, 0x8A000000, 0x9A000000, 0xAA000000, 0xBB000000, 0xCC000000, 0xDD000000, 0xFF000000};
  float v5_[14] = {0., 0.7, 0.97, 1.24, 1.50, 1.76, 2.02, 2.28, 2.54, 2.8, 3.07, 3.31, 3.5, 3.89};  // V

  TCanvas* c5 = new TCanvas("c5","c5", 800, 600);
  c5->cd();
  TGraph* g5 = new TGraph(14, x5_, v5_); 
  g5->SetMarkerStyle(20);
  g5->SetTitle("OBDT 4 threshold");
  g5->GetXaxis()->SetTitle("Threshold commands (hexa)");
  g5->GetYaxis()->SetTitle("Vthr - Vbias (V)");
  g5->Draw("AP");
  c5->SaveAs("obdt_N4_threshold.png");


  

}
