#include "G4SystemOfUnits.hh"

#include "MagneticField.hh"
#include "TMath.h"
# include <stdio.h>
# include <math.h>
#include <stdlib.h>
#include <vector>
#include "fstream"
#include <iterator>
#include "iostream"
using namespace std;
double zvalexp[100]=
{-489.636064,-480.547295,-470.159824,-459.772353,-449.382742,
-440.296112,-429.906502,-419.519031,-410.430262,-400.042791,
-389.655320,-379.269989,-368.882518,-359.795888,-349.410556,
-340.323926,-329.938595,-320.854105,-310.470913,-300.089861,
-289.708808,-280.626458,-270.249684,-259.872911,-250.796979,
-239.127923,-230.060549,-220.999593,-210.646355,-200.305954,
-189.978391,-180.979482,-170.711825,-160.480541,-151.550097,
-139.968763,-130.927063,-121.855410,-110.173517,-101.086887,
-90.701555,-80.311945,-71.225315,-60.835705,-51.744796,
-41.359464,-30.969854,-21.878945,-10.192773,-1.099724,
9.289886,  19.679497,28.770406,39.162156,49.551766,
58.644815,69.034425,78.129613,89.817925,98.910974,
108.008301,119.705171,128.815336,137.957594,149.757162,
160.309378,169.554334,180.063758,189.244528,199.698325,
210.135005,220.560988,229.681850,240.092856,250.501722,
259.609748,270.012195,280.412503,289.514110,299.910139,
310.308308,320.704337,329.801665,341.494255,350.589444,
359.684632,370.078521,380.470271,389.565459,399.957209,
410.348959,420.740709,429.833758,441.524209,450.617258,
459.708167,470.099917,480.489527,489.582576,501.273027
};
 double Bvalexp[100]={
0.00453,0.004942,0.005354,0.005766,0.005766,
0.00659,0.00659,0.007002,0.007414,0.007825,
0.008237,0.009061,0.009473,0.010297,0.01112,
0.011944,0.012768,0.014003,0.015239,0.016886,
0.018534,0.020181,0.022652,0.025124,0.028007,
0.031713,0.036244,0.04201,0.049012,0.058484,
0.070428,0.088138,0.111614,0.142092,0.172982,
0.193575,0.203048,0.206755,0.20799,0.208814,
0.209638,0.209638,0.210461,0.210461,0.210461,
0.211285,0.211285,0.211285,0.211697,0.211285,
0.211285,0.211285,0.211285,0.210873,0.210873,
0.210461,0.210461,0.209638,0.209638,0.209226,
0.20799,0.206343,0.202636,0.192751,0.171334,
0.140033,0.110379,0.087315,0.070016,0.057661,
0.0486,0.041598,0.035832,0.031713,0.028007,
0.024712,0.022241,0.020181,0.018122,0.016886,
0.015239,0.014003,0.012768,0.011944,0.01112,
0.010297,0.009473,0.009061,0.008237,0.007825,
0.007414,0.007002,0.00659,0.006178,0.005766,
0.005766,0.005354,0.005354,0.004942,0.00453
};
MagneticField::MagneticField()
{
    G4cout << "MagneticField::MagneticField()" << G4endl;
    _BfieldY = 0.0*gauss;
    
	_xc1 = 0;
	_yc1 = 0;
	_zc1 = 0;

	_dx1 = 0;
	_dy1 = 0;
	_dz1 = 0;

}

MagneticField::~MagneticField()
{}

void MagneticField::GetFieldValue(const double Point[4],double *Bfield) const
{
    SetField(Point, Bfield[0],Bfield[1],Bfield[2]); //set mag field for some point
}

bool MagneticField::SetField( const double *Point,  G4double & Bx, G4double & By, G4double & Bz) const
{
//from -25 to 25 on Z

	G4double xx1 = Point[0] - _xc1;
	G4double yy1 = Point[1] - _yc1;
	G4double zz1 = Point[2] - _zc1;

	vector<double>::iterator it;
	vector<double> Zval(10);
	Zval.insert(Zval.begin(),zvalexp,zvalexp+100);
   vector<double> Bval(10);
   Bval.insert(Bval.begin(),Bvalexp,Bvalexp+100);
   G4int z_left=0;
	G4int a=0;
G4double Bneed=0.06;
G4double Coef=10000/(0.211285/ Bneed);

	if(xx1>=-536 && xx1<=536){
		if(yy1>=-56 && yy1<=56)  {
		 if(zz1>=-500 && zz1<=500){
			 for(a=0;a<99;a++)
			 {
				if(zz1>=Zval[a]&&zz1<=Zval[a+1])
				  { z_left=a;
				    break;
				  }
			 }

				Bx = 0.0;
				By = Bval[z_left]*Coef*gauss;
				Bz = 0.0;

				//G4cout<<"By = "<<By<<G4endl
				//<<"1400*gauss "<<1400*gauss<<G4endl;
				return true;
		 }

		}
	}
	Bx = 0.0;
	By = 0.0;
	Bz = 0.0;

	return false;

}

// gauss
void MagneticField::setBfieldY(G4double byVal){
	G4cout  << " Set B-field Y-component" << G4endl
			<<" _BfieldY "<<byVal<<" gauss"<<G4endl;
	_BfieldY = byVal;
}

void MagneticField::setFieldBox1( G4double valxc, G4double valyc, G4double valzc,
				  G4double valdx, G4double valdy, G4double valdz)
{
	_xc1 = valxc;
	_yc1 = valyc;
	_zc1 = valzc;
	_dx1 = valdx;
	_dy1 = valdy;
	_dz1 = valdz;

	G4cout  <<" Set Field Box 1 "<<G4endl
			<<"_xc1 = "<<_xc1<<G4endl
			<<"_yc1 = "<<_yc1<<G4endl
			<<"_zc1 = "<<_zc1<<G4endl
			<<"_dx1 = "<<_dx1<<G4endl
			<<"_dy1 = "<<_dy1<<G4endl
			<<"_dz1 = "<<_dz1<<G4endl;
}

