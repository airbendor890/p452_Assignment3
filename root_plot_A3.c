#include<TGraph.h>
#include<TF1.h>
#include<TLegend.h>
#include<TCanvas.h>

{	c=new TCanvas("c","plots",1200,500);
	c->Divide(3,1);
	c->cd(1);
	TGraph g("q2_output1.txt");
	g.SetMarkerStyle(kOpenCircle);
	g.SetMarkerColor(kBlue);
	g.SetMarkerSize(0.5);
	g.SetLineColor(kBlue);
		
	g.DrawClone();
	
	c->cd(2);
	TGraph g1("q2_output2.txt");
	g1.SetMarkerStyle(kOpenCircle);
	g1.SetMarkerColor(kBlue);
	g1.SetMarkerSize(0.5);
	g1.DrawClone();


	c->cd(3);
	TGraph g2("q2_output3.txt");
	g2.SetMarkerStyle(kOpenCircle);
	g2.SetMarkerColor(kBlue);
	g2.SetMarkerSize(0.5);
	g2.DrawClone();
	
}	