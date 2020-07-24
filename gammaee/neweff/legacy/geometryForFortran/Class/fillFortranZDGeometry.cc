// -*- C++ -*-
//
// Package:     <geometryForFortran>
// Module:      fillFortranZDGeometry
// 
// Description: Fill the ZD geometry (in ZDGEOMZD).
//
// Implementation:
//     <Notes on implementation>
//
// Author:      Guangshun Huang
// Created:     Mon Jan 2 2003

#include "Experiment/Experiment.h"
#include "Experiment/types.h"
#include "Experiment/fortran_types.h"


// system include files
#include <stdlib.h>   // for ::exit
#include <assert.h>
#if defined(STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG)
#endif /* STL_TEMPLATE_DEFAULT_PARAMS_FIRST_BUG */

// user include files
#include "Experiment/report.h"
#include "geometryForFortran/geometryForFortran.h"

//
// constants, enums and typedefs
//

static const char* const kFacilityString = 
                      "geometryForFortran.fillFortranZDGeometry" ;

extern "C" {
   void gff_fillzdgeomzd_(FInteger*, FInteger*, FInteger*, FInteger*,
			      FReal*, FReal*, FReal*, FReal*, FReal*, FReal*,
			      FInteger*, FReal*, FReal*, FReal*);

   void gff_fillzdgeomglobal_(FInteger*);

   void gff_fillsirphigeom_(FInteger*, FInteger*, FReal*, FInteger*, 
			    FReal*, FReal*, FReal*, FInteger*);

   void gff_fillsirzgeom_(FInteger*, FInteger*, FReal*, FInteger*, 
			  FReal*, FReal*, FReal*, FInteger*);
			
}

//////////////////////////////////////////////////////////////////////
// Fill the appropriate Fortran common blocks with ZD geometry information
//
void fillFortranZDGeometry(const AZDSenseWireStore& g)
{
   FInteger ncanzd = g.kNumberOfSenseLayers;
   gff_fillzdgeomglobal_(&ncanzd);

   // The ordering is ZD-Anodes, SVX-RPHI, SVX-RZ

   // FILL THE ZD ANODES!
   // Set the layer-by-layer constants
   FInteger index = 1;
   int zdlayer = 0;
   unsigned int i;
   for ( i=g.kFirstLayer;
	 i <= (g.kFirstLayer+g.kNumberOfSenseLayers-1); ++i)
   {

      ++zdlayer;

      // Number of wires in the layer
      FInteger nwires = g.numberOfWiresLyr(i);

      // Is this layer stereo?
      FInteger isLayerStereo = g.isStereo(i);

      // Radius, tan of the stereo angle,
      // phi of wire 0, cell width, z at the end (+ side),
      // radius at +z end
      FReal rzd = g.radiusNominal(i);

      FReal tanscd = g.tanStereoAngle(i);

      FReal phifzd = g.phi0Nominal(i);

      FReal cellzd = g.cellPhiWidth(i);

	

      double zend = g.zMax(i);
      FReal zendzd = (FReal)zend;

      DABoolean success;
      double rend = g.radiusAtz(success, i, zend);
      if ( !success )
      {
	 report(EMERGENCY, kFacilityString) << "radiusAtz failed for layer "
					    << i << endl;
	 assert(success);
	 ::exit(1);
      }

      FReal rendzd = (FReal) rend;

      FInteger layerToFill = i;

      // Now need to get more detailed information
      const AEWireLayerCylindrical& layer = g.layer(i);

      report(DEBUG, kFacilityString) 
	             << "i, phi0, cellzd, phimin, phimax, zmin, zmax, tanscd, r" 
		     << i << " " 
		     << g.phi0Nominal(i) << " " << g.cellPhiWidth(i) << " " 
		     << layer.phiOfFirstWireInVolume1() << " "
		     << layer.phiOfFirstWireInVolume2() << " "
		     << layer.zMin() << " " 
		     << layer.zMax() << " " 
		     << layer.tanStereoAngle() << " "
		     << layer.radiusNominal() << " "
		     << endl;

      // Determine the read out end for this layer (WENDZD)
      int readoutEnd = layer.readoutEnd();

      FInteger wendzd = readoutEnd;
      
      // Is the layer stereo?
      DABoolean isStereo = layer.isStereo();

      // Let's try to calculate the number of cells a stereo wire
      //  is offset as it travels down the length of the chamber (DIFSZD)...

      // phi is the change in azimuth of the wire as it goes from one end
      // to the center
      double sinphi = zend * g.tanStereoAngle(i) / rend;
      
      // So number (or fraction thereof) of cells crossed when going down
      // the WHOLE chamber length is
      double cellsOffset = asin(sinphi) / g.cellPhiWidth(i) * 2.0;

      FReal difszd;
      difszd = cellsOffset;

      // Now the actual stereo angle is...
      double stereoAngle = atan(g.tanStereoAngle(i));
      FReal angscd = stereoAngle;
      

      // Get the maximum sag of the wire in y
      double wireSagInY = layer.wireSagy();

      FReal bsagzd = wireSagInY;

      // Save these in the common block
      gff_fillzdgeomzd_(&layerToFill, &nwires, &index, 
			&isLayerStereo, &rzd,
			&tanscd, &phifzd, &cellzd, &zendzd, 
			&rendzd, &wendzd, &difszd, &bsagzd, &angscd);

      // Update the index (should point to wire # of the next layer)
      index += nwires;
      
   }

   // Silicon R-PHI
   for ( i = 1; i <= 4; ++i)
   {
      ++zdlayer;
      
      FInteger siLayer = zdlayer;
      FReal radius = 1.0;
      FInteger nwafers = 1000;
      FReal wafWidth = 0.001;
      FReal zend = 1.0;
      FReal rend = 1.0;
      FInteger laydev = i;
      gff_fillsirphigeom_(&siLayer, &laydev, &radius, &nwafers, 
			  &wafWidth, &zend, &rend, &index);
      index += nwafers;
   }

   // Silicon R-Z
   for ( i = 1; i <= 4; ++i)
   {
      ++zdlayer;
      
      FInteger siLayer = zdlayer;
      FReal radius = 1.0;
      FInteger nwafers = 1000;
      FReal wafWidth = 0.001;
      FReal zend = 1.0;
      FReal rend = 1.0;
      FInteger laydev = i;
      gff_fillsirzgeom_(&siLayer, &laydev, &radius, &nwafers, &wafWidth, &zend,
			&rend, &index);
      index += nwafers;
   }

}
