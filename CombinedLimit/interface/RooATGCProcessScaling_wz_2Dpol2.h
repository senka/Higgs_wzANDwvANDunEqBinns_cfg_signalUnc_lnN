// -*- mode: c++ -*-

#ifndef ROOATGCPROCESSSCALING_WZ_2DPOL2
#define ROOATGCPROCESSSCALING_WZ_2DPOL2

#include "RooRealProxy.h"
#include "RooAbsPdf.h"
#include "TProfile2D.h"
#include "TH2D.h"
#include "TString.h"
#include <iostream>
#include <fstream>
#include <vector>

  
class RooATGCProcessScaling_wz_2Dpol2 : public RooAbsReal {
public:
  
  enum LimitType{ dkglZ, dkzdg1zToCW, dkzdg1zToCB, dg1zlZToCWWW
		  //, dg1lZ, dkdg1
		  , notype };

  RooATGCProcessScaling_wz_2Dpol2 ();
  RooATGCProcessScaling_wz_2Dpol2 (const char * name, const char * title,
			 RooAbsReal& _x, RooAbsReal& _dkg,
			 RooAbsReal& _lZ, 
				   //RooAbsReal& _dg1,
			 RooAbsReal& _SM_shape,
			 const char * parFilename);
  //  RooATGCProcessScaling_wz_2Dpol2 (const RooATGCProcessScaling_wz_2Dpol2& other, const char * name);
  //here
  RooATGCProcessScaling_wz_2Dpol2 (const RooATGCProcessScaling_wz_2Dpol2& other, const char * name);
  virtual TObject * clone(const char * newname) const { 
    return new RooATGCProcessScaling_wz_2Dpol2(*this, newname);
    }
  
  void setLimitType(const unsigned& lt) { type_ = (LimitType)lt; }

  virtual ~RooATGCProcessScaling_wz_2Dpol2 ();  
  
  //here:
  //  void readProfiles(const RooAbsReal& dep,TDirectory& dir) const ;
  void readProfiles(std::vector<double> bins,TDirectory& dir) const ;
  //  void readProfiles(std::vector<double> bins,const char * parFilename) const ;


  TString getProfileFilename() const { return profileFilename; }
  
protected:
  
  //  RooRealProxy x;
  //  const RooAbsReal& x;
  RooRealProxy lZ;
  RooRealProxy dkg;
  //  RooRealProxy dg1;
  
  LimitType type_;

  double SM_integral;
  std::vector<double> integral_basis;
  //here:
  std::vector<double> bins;

  TString profileFilename;
  
  TH2D ** P_dk; //!
  //  std::vector<double> P_dk;
  
  //  double ** P_dk;

  //  TH2D ** P_dg1; //!
  //  TH2D ** P_dkdg1; //!
  
  void initializeProfiles();
  void initializeNormalization(const RooAbsReal& dep,
			       const RooAbsReal& shape);
  void readProfiles(RooATGCProcessScaling_wz_2Dpol2 const& other);
  
  virtual double evaluate() const ;
  
private:
  
  ClassDef(RooATGCProcessScaling_wz_2Dpol2, 3) // aTGC function 
};

#endif
