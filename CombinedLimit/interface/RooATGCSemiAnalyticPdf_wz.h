// -*- mode: c++ -*-

#ifndef ROOATGCSEMIANALYTICPDF_WZ
#define ROOATGCSEMIANALYTICPDF_WZ

#include "RooRealProxy.h"
#include "RooAbsPdf.h"
//#include "RooAbsData.h"
#include "TProfile2D.h"
#include "TH2D.h"
#include "TString.h"
  
class RooATGCSemiAnalyticPdf_wz : public RooAbsPdf {
public:
  
  enum LimitType{ dkglZ, dg1lZ, dkdg1, notype };

  RooATGCSemiAnalyticPdf_wz ();
  RooATGCSemiAnalyticPdf_wz (const char * name, const char * title,
			     RooAbsReal& _x, 
			     RooAbsReal& _dkg, 
			     RooAbsReal& _lZ,
			     RooAbsReal& _dg1,
			     RooAbsReal& _SM_shape,
			     //			  RooAbsData& _SM_shape,
			     const char * parFilename,
			     const unsigned& lt);
  RooATGCSemiAnalyticPdf_wz (const RooATGCSemiAnalyticPdf_wz& other, const char * name);
  virtual TObject * clone(const char * newname) const { 
    return new RooATGCSemiAnalyticPdf_wz(*this, newname);
    }
  
  virtual ~RooATGCSemiAnalyticPdf_wz ();
  
  void setLimitType(const unsigned& lt) { type_ = (LimitType)lt; }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, 
			    RooArgSet& analVars, 
			    const char* rangeName = 0) const;

  Double_t analyticalIntegral(Int_t code, const char* rangeName = 0) const;

  void readProfiles(std::vector<double> bins,TDirectory& dir) const ;
  TString getProfileFilename() const { return profileFilename; }
  
protected:
  
  RooRealProxy x;
  RooRealProxy lZ;
  RooRealProxy dkg;
  RooRealProxy dg1;
  RooRealProxy SM_shape;
  //  RooAbsData SM_shape;
  //  RooArgProxy SM_shape;
  //  RooAbsData SM_shape;
  
  LimitType type_;

  mutable std::map<std::string,std::vector<double> > integral_basis;

  mutable std::vector<double> bins; // imporatant to be mutable!!!
  //  mutable std::vector<double> bins;

  TString profileFilename;
  
  TH2D ** P_dk; //!
  TH2D ** P_dg1; //!
  TH2D ** P_dkdg1; //!
  
  void initializeProfiles();
  void initializeBins(const RooAbsReal& shape) const;
  void initializeNormalization(const std::string& rName,
			       const RooAbsReal& dep,
			       const RooAbsReal& shape) const;
			       //			       const RooAbsData& shape) const;
  void readProfiles(RooATGCSemiAnalyticPdf_wz const& other);
  
  virtual double evaluate() const ;
  
private:
  
  ClassDef(RooATGCSemiAnalyticPdf_wz, 2) // aTGC function 
};

#endif
