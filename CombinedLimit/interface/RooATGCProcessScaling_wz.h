// -*- mode: c++ -*-

#ifndef ROOATGCPROCESSSCALING_WZ
#define ROOATGCPROCESSSCALING_WZ

#include "RooRealProxy.h"
#include "RooAbsPdf.h"
#include "TProfile2D.h"
#include "TH2D.h"
#include "TString.h"
  
class RooATGCProcessScaling_wz : public RooAbsReal {
public:
  
  enum LimitType{ dkglZ, dg1lZ, dkdg1, notype };

  RooATGCProcessScaling_wz ();
  RooATGCProcessScaling_wz (const char * name, const char * title,
			 RooAbsReal& _x, RooAbsReal& _dkg,
			 RooAbsReal& _lZ, RooAbsReal& _dg1,
			 RooAbsReal& _SM_shape,
			 const char * parFilename);
  //  RooATGCProcessScaling_wz (const RooATGCProcessScaling_wz& other, const char * name);
  //here
  RooATGCProcessScaling_wz (const RooATGCProcessScaling_wz& other, const char * name);
  virtual TObject * clone(const char * newname) const { 
    return new RooATGCProcessScaling_wz(*this, newname);
    }
  
  void setLimitType(const unsigned& lt) { type_ = (LimitType)lt; }

  virtual ~RooATGCProcessScaling_wz ();  
  
  //here:
  //  void readProfiles(const RooAbsReal& dep,TDirectory& dir) const ;
  void readProfiles(std::vector<double> bins,TDirectory& dir) const ;


  TString getProfileFilename() const { return profileFilename; }
  
protected:
  
  //  RooRealProxy x;
  //  const RooAbsReal& x;
  RooRealProxy lZ;
  RooRealProxy dkg;
  RooRealProxy dg1;
  
  LimitType type_;

  double SM_integral;
  std::vector<double> integral_basis;
  //here:
  std::vector<double> bins;

  TString profileFilename;
  
  TH2D ** P_dk; //!
  TH2D ** P_dg1; //!
  TH2D ** P_dkdg1; //!
  
  void initializeProfiles();
  void initializeNormalization(const RooAbsReal& dep,
			       const RooAbsReal& shape);
  void readProfiles(RooATGCProcessScaling_wz const& other);
  
  virtual double evaluate() const ;
  
private:
  
  ClassDef(RooATGCProcessScaling_wz, 3) // aTGC function 
};

#endif
