/***************************************************************************** 
 * Project: RooFit                                                           * 
 *                                                                           * 
 * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/ 

// Your description goes here... 

#include "Riostream.h" 

#include "RooAbsData.h"
#include "HiggsAnalysis/CombinedLimit/interface/RooATGCSemiAnalyticPdf_wz_2Dpol2.h" 

#include <math.h> 
#include "TMath.h" 
#include "RooFormulaVar.h"
#include "RooRealVar.h"
#include "RooFit.h"

#include "TFile.h"

//using namespace RooFit ;

ClassImpUnique(RooATGCSemiAnalyticPdf_wz_2Dpol2,MAGICWORDOFSOMESORT_WZ_2DPOL2) 

RooATGCSemiAnalyticPdf_wz_2Dpol2::RooATGCSemiAnalyticPdf_wz_2Dpol2() : 
  type_(notype), P_dk(0)
								  //, P_dg1(0), P_dkdg1(0)
{
  initializeProfiles();
}

RooATGCSemiAnalyticPdf_wz_2Dpol2::RooATGCSemiAnalyticPdf_wz_2Dpol2(const char *name, 
						     const char *title, 
						     RooAbsReal& _x,
						     RooAbsReal& _dkg,
						     RooAbsReal& _lZ,
								   //    RooAbsReal& _dg1,
						     RooAbsReal& _SM_shape,
						     const char * parFilename,
						     const unsigned& lt) :
  RooAbsPdf(name,title),
  x("observable","observable",this,_x),
  lZ("lZ","lZ",this,_lZ),
  dkg("dkg","dkg",this,_dkg),
  //  dg1("dg1","dg1",this,_dg1),
  SM_shape("SM_shape","SM_shape",this,_SM_shape),
  type_((LimitType)lt),
  profileFilename(parFilename),
  P_dk(0)
								  //, P_dg1(0), P_dkdg1(0)
{ 
  initializeProfiles();
  initializeNormalization(std::string(""),_x,_SM_shape);
  const char* pwd = gDirectory->GetPath();
  TFile *f = TFile::Open(parFilename,"READ");  
  gDirectory->cd(pwd);

  std::vector<double> bins_;

  const RooRealVar& rdep = dynamic_cast<const RooRealVar&>(_x);
  int N_bins=rdep.getBinning("").numBins();
  
  for (int i=0;i<N_bins;i++){
    if (i==0){
      bins_.push_back(rdep.getBinning("").binLow(i));
    }
    bins_.push_back(rdep.getBinning("").binHigh(i));
  }
  
  readProfiles(bins_,*f);
  f->Close();
} 

RooATGCSemiAnalyticPdf_wz_2Dpol2::RooATGCSemiAnalyticPdf_wz_2Dpol2(const RooATGCSemiAnalyticPdf_wz_2Dpol2& other, 
					       const char* name) :  
  RooAbsPdf(other,name),
  x("observable",this,other.x),
  lZ("lZ",this,other.lZ),
  dkg("dkg",this,other.dkg),
  //  dg1("dg1",this,other.dg1),
  SM_shape("SM_shape",this,other.SM_shape),
  type_(other.type_),
  integral_basis(other.integral_basis),
  bins(other.bins),
  profileFilename(other.profileFilename),
  P_dk(0)
								  //, P_dg1(0), P_dkdg1(0)
{ 
  initializeProfiles();
  initializeBins(x.arg());
  const char* pwd = gDirectory->GetPath();
  TFile *f = TFile::Open(profileFilename,"READ");  
  gDirectory->cd(pwd);  
  readProfiles(bins,*f);
  f->Close();
} 

void RooATGCSemiAnalyticPdf_wz_2Dpol2::initializeProfiles() {
  //  int const N_bins=20;
  int const N_bins=1;
  
  P_dk = new TH2D*[N_bins]();
  //  P_dg1 = new TH2D*[N_bins]();
  //  P_dkdg1 = new TH2D*[N_bins]();
  
}


void RooATGCSemiAnalyticPdf_wz_2Dpol2::initializeBins(const RooAbsReal& dep) const {

  std::vector<double> bins;
  const RooRealVar& rdep = dynamic_cast<const RooRealVar&>(dep);
  int N_bins=rdep.getBinning("").numBins();
  for(int i=0; i<N_bins; ++i) {
    if (i==0){
      bins.push_back(rdep.getBinning("").binLow(i));
    }
    bins.push_back(rdep.getBinning("").binHigh(i));

  }
}


void RooATGCSemiAnalyticPdf_wz_2Dpol2::initializeNormalization(const std::string& rName,
						     const RooAbsReal& dep,
						     const RooAbsReal& shape) const {
  integral_basis[rName] = std::vector<double>();


  const RooRealVar& rdep = dynamic_cast<const RooRealVar&>(dep);
  int N_bins=rdep.getBinning("").numBins();
  int i;
  for(i=0; i<N_bins; ++i) {


    Double_t bin_low=rdep.getBinning("").binLow(i);
    Double_t bin_high=rdep.getBinning("").binHigh(i);

    if (i==0){
      bins.push_back(rdep.getBinning("").binLow(i));
      //      cout << i<<" "<< rdep.getBinning("").binLow(i) <<endl;
    }
    bins.push_back(rdep.getBinning("").binHigh(i));
    //    cout << i<<" "<< rdep.getBinning("").binHigh(i) <<endl;

    RooRealVar& b = const_cast<RooRealVar&>(rdep);

    const string intRange="integRange";

    b.setRange((const char*)intRange.c_str(),bin_low,bin_high); 
    RooAbsReal* integral = shape.createIntegral(RooArgSet(rdep),RooArgSet(),(const char*)intRange.c_str());

    //    cout <<"bin "<< bin_low<<"-"<<bin_high<<"  integral: "<<integral->getVal()  << endl;
    integral_basis[rName].push_back(integral->getVal());

    delete integral;
  }


}

void RooATGCSemiAnalyticPdf_wz_2Dpol2::readProfiles(std::vector<double> bins,TDirectory& dir) const {

  //  int N_bins=bins.size()-1;
  int N_bins=1;
  int i;
  for(i=0; i<N_bins; ++i) {
    //    cout <<"bins: "<<bins[i]<<" - "<< bins[i+1]  << endl;
    if (P_dk[i]) delete P_dk[i];
    TString dkname = TString::Format("bin_content_lam_dk_%i",i+1);
    P_dk[i] = dynamic_cast<TH2D *>(dir.Get(dkname)->Clone(dkname+"new"));
    P_dk[i]->SetDirectory(0);
    /*
    if (P_dg1[i]) delete P_dg1[i];
    TString dg1name = TString::Format("bin_content_lam_dk_%i",i+1);
    //    TString dg1name = TString::Format("bin_content_lam_dg_%i",i+1);
    P_dg1[i] = dynamic_cast<TH2D *>(dir.Get(dg1name)->Clone(dg1name+"new"));
    P_dg1[i]->SetDirectory(0);
    TString dkdg1name = TString::Format("bin_content_lam_dk_%i",i+1);
    //    TString dkdg1name = TString::Format("bin_content_dk_dg_%i",i+1);
    P_dkdg1[i] = dynamic_cast<TH2D *>(dir.Get(dkdg1name)->Clone(dkdg1name+"new"));
    P_dkdg1[i]->SetDirectory(0);
    */
  }

}

void RooATGCSemiAnalyticPdf_wz_2Dpol2::readProfiles(RooATGCSemiAnalyticPdf_wz_2Dpol2 const& other) {

  //  int N_bins=other.bins.size()-1;
  int N_bins=1;

  for (int i = 0; i<N_bins; ++i) {
    TString dkname = TString::Format("bin_content_lam_dk_%i",i+1);
    P_dk[i] = dynamic_cast<TH2D *>(other.P_dk[i]->Clone(dkname+"new"));
    P_dk[i]->SetDirectory(0);
    /*
    TString dg1name = TString::Format("bin_content_lam_dk_%i", i+1);
    P_dg1[i] = dynamic_cast<TH2D *>(other.P_dg1[i]->Clone(dg1name+"new"));
    P_dg1[i]->SetDirectory(0);
    TString dkdg1name = TString::Format("bin_content_lam_dk_%i",i+1);
    P_dkdg1[i] = dynamic_cast<TH2D *>(other.P_dkdg1[i]->Clone(dkdg1name+"new"));
    P_dkdg1[i]->SetDirectory(0);
    */
  }
}

RooATGCSemiAnalyticPdf_wz_2Dpol2::~RooATGCSemiAnalyticPdf_wz_2Dpol2() {
  //int const N_bins=20;
int const N_bins=1;

  for(int i = 0; i<N_bins; ++i) {
    if (P_dk[i])
      delete P_dk[i];
    /*
    if (P_dg1[i])
      delete P_dg1[i];
    if (P_dkdg1[i])
      delete P_dkdg1[i];
    */
  }
  delete[] P_dk;
  //  delete[] P_dg1;
  //  delete[] P_dkdg1;
}

Double_t RooATGCSemiAnalyticPdf_wz_2Dpol2::evaluate() const 
{ 

  //  cout <<"evaluate..." << endl;
  // ENTER EXPRESSION IN TERMS OF VARIABLE ARGUMENTS HERE 
  double MZ=0.0911876;
  double MW=0.080385;
  double s=MZ*MZ/(MW*MW);
  double sin2thw=0.23126;
  double tan2thw=-1000.;
  tan2thw=sin2thw/(1-sin2thw);
  double alpha=0.0072973525698;
  double e=sqrt(4.*3.141592*alpha);
  double g=e/sqrt(sin2thw);

  TH2D ** P = NULL;
  double v1(0.0), v2(0.0);
  
  P = P_dk;
  v1 = lZ;
  v2 = dkg;
  
  /*  
  switch(type_) {
  case dkglZ:
    cout<<  "######## case 3 dkglZ SemiAnal"<<endl;
    P = P_dk;
    v1 = lZ;
    v2 = dkg;
    break;
  case dkzdg1zToCW:
    cout<<  "######## case 3 dkzdg1zToCW SemiAnal"<<endl;
    P = P_dk;
    v1 = lZ*2./(MW*MW);
    v2 = dkg;
    break;
  case notype:
    assert(NULL && "invalid limit type!");
    break;
  }
  */
  
  if (not P[0]) {
    TFile f(profileFilename);
    readProfiles(bins,f); 
    f.Close();
  }

  /*
  if (v1 < P[0]->GetXaxis()->GetXmin())
    v1 = P[0]->GetXaxis()->GetXmin();
  if (v1 > P[0]->GetXaxis()->GetXmax())
    v1 = P[0]->GetXaxis()->GetXmax();
  if (v2 < P[0]->GetYaxis()->GetXmin())
    v2 = P[0]->GetYaxis()->GetXmin();
  if (v2 > P[0]->GetYaxis()->GetXmax())
    v2 = P[0]->GetYaxis()->GetXmax();
  */
  double ret(0.);

  int N_bins=bins.size()-1;

    int bin_with_x=1;
    for (int j=0;j<N_bins;j++)
      if (x<bins[j+1] && x>bins[j]) bin_with_x=j+1;
    
    
    //  ret = P[bin_with_x-1]->Interpolate(v1, v2)*SM_shape;
    switch(type_) {
    case dkglZ:
      //      cout<< "######## case 1 dkglZ SemiAnal"<<endl;
      ret = (P[0]->GetBinContent(1,bin_with_x)+P[0]->GetBinContent(2,bin_with_x)*v1+P[0]->GetBinContent(3,bin_with_x)*v2+P[0]->GetBinContent(4,bin_with_x)*v1*v2+P[0]->GetBinContent(5,bin_with_x)*v1*v1+P[0]->GetBinContent(6,bin_with_x)*v2*v2)*SM_shape;
      break;
    case dkzdg1zToCW:
      //      cout<<  "######## case 1 dkzdg1zToCW SemiAnal"<<endl;
      ret =(P[0]->GetBinContent(1,bin_with_x)
	     +(P[0]->GetBinContent(2,bin_with_x)+P[0]->GetBinContent(3,bin_with_x)*s)*v1*MW*MW/2.
	    +(P[0]->GetBinContent(4,bin_with_x)*s+P[0]->GetBinContent(5,bin_with_x)+P[0]->GetBinContent(6,bin_with_x)*s*s)*v1*MW*MW/2.*v1*MW*MW/2.)*SM_shape;	    
      break;
    case dkzdg1zToCB:
      //      cout<<  "######## case 1 dkzdg1zToCB SemiAnal"<<endl;
      ret = (P[0]->GetBinContent(1,bin_with_x)
	     +P[0]->GetBinContent(2,bin_with_x)*v1*MW*MW*tan2thw/(-2.)
	     +P[0]->GetBinContent(5,bin_with_x)*v1*MW*MW*tan2thw/(-2.)*v1*MW*MW*tan2thw/(-2.)
	     )*SM_shape;      
      break;
    case dg1zlZToCWWW:
      //      cout<<  "######## case 1 dg1zlZToCWWW SemiAnal"<<endl;
      ret = (P[0]->GetBinContent(1,bin_with_x)
	     +P[0]->GetBinContent(3,bin_with_x)*v2*3.*g*g*MW*MW/2.
	     +P[0]->GetBinContent(6,bin_with_x)*v2*3.*g*g*MW*MW/2.*v2*3.*g*g*MW*MW/2.
	     )*SM_shape;      
      break;
    case notype:
      assert(NULL && "invalid limit type!");
      break;
    }
    
    //  ret = (P[0]->GetBinContent(1,bin_with_x)+P[0]->GetBinContent(2,bin_with_x)*v1+P[0]->GetBinContent(3,bin_with_x)*v2+P[0]->GetBinContent(4,bin_with_x)*v1*v2+P[0]->GetBinContent(5,bin_with_x)*v1*v1+P[0]->GetBinContent(6,bin_with_x)*v2*v2)*SM_shape;

  
  if (ret < 0.) ret = 0.;
  return ret; 
}

Int_t RooATGCSemiAnalyticPdf_wz_2Dpol2::
getAnalyticalIntegral(RooArgSet& allVars,RooArgSet& analVars, 
		      const char* /*rangeName*/) const {  
  if (matchArgs(allVars,analVars,x)) return 1 ;
  return 0 ;
}

Double_t RooATGCSemiAnalyticPdf_wz_2Dpol2::
analyticalIntegral(Int_t code, const char* rangeName) const {  
  double MZ=0.0911876;
  double MW=0.080385;
  double s=MZ*MZ/(MW*MW);
  double sin2thw=0.23126;
  double tan2thw=-1000.;
  tan2thw=sin2thw/(1-sin2thw);
  double alpha=0.0072973525698;
  double e=sqrt(4.*3.141592*alpha);
  double g=e/sqrt(sin2thw);

  assert(code==1 && "invalid analytic integration code!");

  std::string rName = ( rangeName == 0 ? std::string("") : std::string(rangeName) );
  if( integral_basis.find(rName) == integral_basis.end() ) {
    initializeNormalization(rName,x.arg(),SM_shape.arg());
  }

  TH2D ** P = NULL;
  double v1(0.0), v2(0.0);
  
  P = P_dk;
  v1 = lZ;
  v2 = dkg;
  
  /*
  switch(type_) {
  case dkglZ:
    cout<<  "######## case 4 dkglZ SemiAnal"<<endl;
    P = P_dk;
    v1 = lZ;
    v2 = dkg;
    break;
  case dkzdg1zToCW:
    cout<<  "######## case 4 dkzdg1zToCW SemiAnal"<<endl;
    P = P_dk;
    v1 = lZ*2./(MW*MW);
    v2 = dkg;
    break;
  default:
    assert(code==1 && "invalid limit type!");
    break;
  }
  */

  if (not P[0]) {
    TFile f(profileFilename);
    readProfiles(bins,f);
    f.Close();
  }

  /*
  if (v1 < P[0]->GetXaxis()->GetXmin())
    v1 = P[0]->GetXaxis()->GetXmin();
  if (v1 > P[0]->GetXaxis()->GetXmax())
    v1 = P[0]->GetXaxis()->GetXmax();
  if (v2 < P[0]->GetYaxis()->GetXmin())
    v2 = P[0]->GetYaxis()->GetXmin();
  if (v2 > P[0]->GetYaxis()->GetXmax())
    v2 = P[0]->GetYaxis()->GetXmax();
  */
  double ret(0.);

  int N_bins=bins.size()-1;
  //  cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@--> lZ(v1): "<<v1<<" dk(v2): "<<v2 << endl;
  for(Int_t i=0 ; i<N_bins ; i++) {

    switch(type_) {
    case dkglZ:
      //      cout<< "######## case 2 dkglZ SemiAnal "<<endl;
      ret += (P[0]->GetBinContent(1,i+1)+P[0]->GetBinContent(2,i+1)*v1+P[0]->GetBinContent(3,i+1)*v2+P[0]->GetBinContent(4,i+1)*v1*v2+P[0]->GetBinContent(5,i+1)*v1*v1+P[0]->GetBinContent(6,i+1)*v2*v2)*integral_basis[rName][i];
      break;
    case dkzdg1zToCW:
      //      cout<< "######## case 2 dkzdg1zToCW SemiAnal"<<endl;
      //      ret += (P[0]->GetBinContent(1,i+1)+P[0]->GetBinContent(2,i+1)*v1+P[0]->GetBinContent(3,i+1)*v2+P[0]->GetBinContent(4,i+1)*v1*v2+P[0]->GetBinContent(5,i+1)*v1*v1+P[0]->GetBinContent(6,i+1)*v2*v2)*integral_basis[rName][i];
      ret += (P[0]->GetBinContent(1,i+1)
	     +(P[0]->GetBinContent(2,i+1)+P[0]->GetBinContent(3,i+1)*s)*v1*MW*MW/2.
	     +(P[0]->GetBinContent(4,i+1)*s+P[0]->GetBinContent(5,i+1)+P[0]->GetBinContent(6,i+1)*s*s)*v1*MW*MW/2.*v1*MW*MW/2.)*integral_basis[rName][i];
      break;
    case dkzdg1zToCB:
      //      cout<< "######## case 2 dkzdg1zToCB SemiAnal"<<endl;
      ret += (P[0]->GetBinContent(1,i+1)
	     +P[0]->GetBinContent(2,i+1)*v1*MW*MW*tan2thw/(-2.)
	     +P[0]->GetBinContent(5,i+1)*v1*MW*MW*tan2thw/(-2.)*v1*MW*MW*tan2thw/(-2.))*integral_basis[rName][i];
      break;
    case dg1zlZToCWWW:
      //      cout<< "######## case 2 dg1zlZToCWWW SemiAnal"<<endl;
      ret += (P[0]->GetBinContent(1,i+1)
	     +P[0]->GetBinContent(3,i+1)*v2*3.*g*g*MW*MW/2.
	     +P[0]->GetBinContent(6,i+1)*v2*3.*g*g*MW*MW/2.*v2*3.*g*g*MW*MW/2.)*integral_basis[rName][i];
      break;
    default:
      assert(code==1 && "invalid limit type!");
      break;
    }

    
    //    ret += P[i]->Interpolate(v1, v2)*integral_basis[rName][i]
      //    ret += (P[0]->GetBinContent(1,i+1)+P[0]->GetBinContent(2,i+1)*v1+P[0]->GetBinContent(3,i+1)*v2+P[0]->GetBinContent(4,i+1)*v1*v2+P[0]->GetBinContent(5,i+1)*v1*v1+P[0]->GetBinContent(6,i+1)*v2*v2)*integral_basis[rName][i]      ;
    //    cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@--> += ("<< P[0]->GetBinContent(1,i+1)<<" + "<< P[0]->GetBinContent(2,i+1)<<" * "<<v1<<" + "<< P[0]->GetBinContent(3,i+1)<<" * "<<v2<<" + "<< P[0]->GetBinContent(4,i+1)<<" * "<<v1*v2<<" + "<< P[0]->GetBinContent(5,i+1)<<" * "<<v1*v1<<" + "<< P[0]->GetBinContent(6,i+1)<<" * "<<v2*v2 <<" )* "<< integral_basis[rName][i] <<"  = "<<ret << endl;
  }
  cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@--> lZ(v1): "<<v1<<" dk(v2): "<<v2 <<" ret: "<<ret<< endl;
  
  cout << "@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@---> integral: "<<ret<< endl;

  return ret;
}
