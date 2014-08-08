// -*- mode: c++ -*-

#ifndef ROOATGCFUNCTION_WZ
#define ROOATGCFUNCTION_WZ

#include "RooRealProxy.h"
#include "RooAbsReal.h"
#include "TProfile2D.h"
#include "TH2D.h"
#include "TString.h"
  
class RooATGCFunction_wz : public RooAbsReal {
public:
  
  enum LimitType{ dkglZ, dg1lZ, dkdg1, notype };

  RooATGCFunction_wz ();
  RooATGCFunction_wz (const char * name, const char * title,
		   RooAbsReal& _x, RooAbsReal& _lZ,
		   RooAbsReal& _dkg, RooAbsReal& _dg1,
		   const char * parFilename);
  RooATGCFunction_wz (const RooATGCFunction_wz& other, const char * name);
  virtual TObject * clone(const char * newname) const { 
    return new RooATGCFunction_wz(*this, newname);
  }
  
  virtual ~RooATGCFunction_wz ();
    
  void readProfiles(std::vector<double> bins,TDirectory& dir) const ;
  TString getProfileFilename() const { return profileFilename; }
  
protected:
  
  RooRealProxy x;
  RooRealProxy lZ;
  RooRealProxy dkg;
  RooRealProxy dg1;
  
  LimitType type_;

  std::vector<double> bins;
  TString profileFilename;
  
  TH2D ** P_dk; //!
  TH2D ** P_dg1; //!
  
  void initializeProfiles();
  void initializeBins(const RooAbsReal& dep);
  void readProfiles(RooATGCFunction_wz const& other);
  
  virtual double evaluate() const ;
  
private:
  
  ClassDef(RooATGCFunction_wz, 1) // aTGC function 
};

#endif
