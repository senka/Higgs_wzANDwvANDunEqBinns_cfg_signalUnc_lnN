// -*- mode: c++ -*-

#ifndef ROOATGCSEMIANALYTICPDF_WZ_2DPOL2
#define ROOATGCSEMIANALYTICPDF_WZ_2DPOL2

#include "RooRealProxy.h"
#include "RooAbsPdf.h"
//#include "RooAbsData.h"
#include "TProfile2D.h"
#include "TH2D.h"
#include "TString.h"
  
class RooATGCSemiAnalyticPdf_wz_2Dpol2 : public RooAbsPdf {
public:
  
  enum LimitType{ dkglZ, dkzdg1zToCW, dkzdg1zToCB, dg1zlZToCWWW
		  //, dg1lZ, dkdg1
		  , notype };

  RooATGCSemiAnalyticPdf_wz_2Dpol2 ();
  RooATGCSemiAnalyticPdf_wz_2Dpol2 (const char * name, const char * title,
			     RooAbsReal& _x, 
			     RooAbsReal& _dkg, 
			     RooAbsReal& _lZ,
				    //    RooAbsReal& _dg1,
			     RooAbsReal& _SM_shape,
			     //			  RooAbsData& _SM_shape,
			     const char * parFilename,
			     const unsigned& lt);
  RooATGCSemiAnalyticPdf_wz_2Dpol2 (const RooATGCSemiAnalyticPdf_wz_2Dpol2& other, const char * name);
  virtual TObject * clone(const char * newname) const { 
    return new RooATGCSemiAnalyticPdf_wz_2Dpol2(*this, newname);
    }
  
  virtual ~RooATGCSemiAnalyticPdf_wz_2Dpol2 ();
  
  void setLimitType(const unsigned& lt) { type_ = (LimitType)lt; }

  Int_t getAnalyticalIntegral(RooArgSet& allVars, 
			    RooArgSet& analVars, 
			    const char* rangeName = 0) const;

  Double_t analyticalIntegral(Int_t code, const char* rangeName = 0) const;

  //  void readProfiles(std::vector<double> bins,const char * parFilename) const ;
  // 13.08.
  void readProfiles(std::vector<double> bins,TDirectory& dir) const ;
  //  void readProfiles(std::vector<double> bins,TDirectory& dir) ;
  TString getProfileFilename() const { return profileFilename; }
  
protected:
  
  RooRealProxy x;
  RooRealProxy lZ;
  RooRealProxy dkg;
  //  RooRealProxy dg1;
  RooRealProxy SM_shape;
  //  RooAbsData SM_shape;
  //  RooArgProxy SM_shape;
  //  RooAbsData SM_shape;
  
  LimitType type_;

  mutable std::map<std::string,std::vector<double> > integral_basis;

  mutable std::vector<double> bins; // imporatant to be mutable!!!
  //  mutable std::vector<double> bins;

  TString profileFilename;
  
  //  TH2D ** P_dk; //!
  TH2D ** P_dk; //!
  //  double ** P_dk;
  //  TH2D ** P_dg1; //!
  //  TH2D ** P_dkdg1; //!
  
  void initializeProfiles();
  void initializeBins(const RooAbsReal& shape) const;
  void initializeNormalization(const std::string& rName,
			       const RooAbsReal& dep,
			       const RooAbsReal& shape) const;
			       //			       const RooAbsData& shape) const;
  void readProfiles(RooATGCSemiAnalyticPdf_wz_2Dpol2 const& other);
  
  virtual double evaluate() const ;
  
private:
  
  ClassDef(RooATGCSemiAnalyticPdf_wz_2Dpol2, 2) // aTGC function 
};

#endif
