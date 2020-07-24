// Here are three routines, get_weighted_z0, get_neutral_energy and
// get_closest_intersection, each of which takes a frame reference and
// returns a value.  Just put in your ProcessorName:: dereferencers!

// Before producing your ntuple, you should find a way to get
// beamspots from Roy's beamspot finder.  It is in some file called
// "beamspot.beamspot", and I think he is working on a way to access
// it in suez.  My closest_intersection resolution is about 1mm, and
// the beamspot does move around on this scale from run to run or
// dataset to dataset: you would stand to gain by using the real
// beamspot, if this is easy.  By the way, if you already know how,
// could you tell me, so that I can include it in mine?
// 
// In the code below,
//     "m_beamX.value()" is the x location of the beamspot
//     "m_beamY.value()" is the y location of the beamspot

double get_weighted_z0( Frame& iFrame )
{
   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   double weighted_z0(1000.);
   double znumer(0.);
   double zdenom(0.);

   vector< KTHelix* > intersecting_helices;
   FATable< NavTrack >::const_iterator track_iter;
   for ( track_iter = tracks.begin();  track_iter != tracks_end;  track_iter++ ) {
      // Quality cuts for weighted z0 determination
      if ( ! track_iter->seedQuality()->originUsed()            &&  // - I want real z information!
	   ! track_iter->pionQuality()->fitAbort()              &&  // - Don't let the fit fail
	   1./abs(track_iter->pionHelix()->curvature()) > 0.42  &&  // - Diameter must be greater than 42 cm
                                                                    //   to guarantee that it pokes through
                                                                    //   the first stereo superlayer
	   ! track_iter->pionHelix()->hasNullErrorMatrix()          // - I want an error matrix for
                                                                    //   weighted means
	 ) {
	 double z0err2( track_iter->pionHelix()->errorMatrix()( KTHelix::kZ0, KTHelix::kZ0 ) );

	 znumer += track_iter->pionHelix()->z0() / z0err2;
	 zdenom += 1. / z0err2;
      } // end passes weighted z0 track cuts
   } // end loop over tracks

   if ( zdenom != 0. )
      weighted_z0 = znumer / zdenom;

   return weighted_z0;
}

double get_neutral_energy( Frame& iFrame )
{
   FAItem< EventProperties > props;
   extract( iFrame.record( Stream::kEvent ), props );

   return props->neutralEnergy();
}

// This is only a guess as to how it works
// You need double m_beam_x and m_beam_y
//

ActionBase::ActionResult ??::beginRun( Frame& iFrame )
{
   FAItem< BeamSpot > spot;
   extract( iFrame.record( Stream::kBeginRun ), spot );
   m_beam_x = spot->center().x();
   m_beam_y = spot->center().y();
   m_beam_z = spot->center().z();
}

double get_closest_intersection( Frame& iFrame )
{
   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   double closest_inter(1000.);

   FATable< NavTrack >::const_iterator track_iter;
   FATable< NavTrack >::const_iterator other_iter;
   for ( track_iter = tracks.begin();  track_iter != tracks_end;  track_iter++ )
      for ( other_iter = track_iter;  other_iter != tracks_end;  other_iter++ )
	 if ( other_iter != track_iter  &&
	      (! track_iter->pionQuality()->fitAbort())  &&
	      (! other_iter->pionQuality()->fitAbort()) ) {
	    double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);
	    KTHelix track( *track_iter->pionHelix() );
	    KTHelix other( *other_iter->pionHelix() );
	    if ( calc_intersection( tx, ty, tz, tsig2z, tzsep, track, other ) ) {
	       
	       double perp( sqrt(sqr(tx - m_beam_x) + sqr(ty - m_beam_y)) );
	       if ( perp < closest_inter ) closest_inter = perp;

	    } // end if successful intersection
	 } // end cuts on track_iter and other_iter

   return closest_inter;
}

double get_weighted_ciz( Frame& iFrame )
{
   FATable< NavTrack > tracks;
   extract( iFrame.record( Stream::kEvent ), tracks );
   FATable< NavTrack >::const_iterator tracks_end = tracks.end();

   double weighted_ciz(1000.);
   double ciznumer(0.);
   double cizdenom(0.);

   FATable< NavTrack >::const_iterator track_iter;
   FATable< NavTrack >::const_iterator other_iter;
   for ( track_iter = tracks.begin();  track_iter != tracks_end;  track_iter++ ) {
      if ( ! track_iter->seedQuality()->originUsed()            &&
	   ! track_iter->pionQuality()->fitAbort()              &&
	   1./abs(track_iter->pionHelix()->curvature()) > 0.42  &&
	   ! track_iter->pionHelix()->hasNullErrorMatrix()        
	 ) {
	 // Secondary track loop to calculate pairwise intersections
	 for ( other_iter = track_iter;  other_iter != tracks_end;  other_iter++ ) {
	    if ( other_iter != track_iter  &&
		 ! other_iter->seedQuality()->originUsed()            &&
		 ! other_iter->pionQuality()->fitAbort()              &&
		 1./abs(other_iter->pionHelix()->curvature()) > 0.42  &&
		 ! other_iter->pionHelix()->hasNullErrorMatrix()        
	       ) { 
	       double tx(-1000.), ty(-1000.), tz(-1000.), tsig2z(-1000.), tzsep(-1000.);
	       KTHelix track( *track_iter->pionHelix() );
	       KTHelix other( *other_iter->pionHelix() );
	       if ( calc_intersection( tx, ty, tz, tsig2z, tzsep, track, other ) ) {

		  // uncertainty in the z intersection + mismatch in z + mismatch in perp
		  double z_uncert2( tsig2z + sqr(tzsep) + sqr(tx - m_beam_x) + sqr(ty - m_beam_y) );
		  ciznumer += tz / z_uncert2;
		  cizdenom += 1. / z_uncert2;

	       } // end if successful intersection
	    } // end if secondary track passes quality cuts
	 } // end loop over secondary track
      } // end if primary track passes quality cuts
   } // end loop over tracks

   if ( cizdenom != 0. ) weighted_ciz = ciznumer / cizdenom;

   return weighted_ciz;
}

///////////////////////////////////////////////////////////////////////////////
// The following are just supporting routines, they are needed by
// get_closest_intersection().

DABoolean HadronFilterProc::calc_intersection(
   double& x, double& y, double& z, double& sig2z, double& zsep,
   KTHelix& a, KTHelix& b )
{
   x = y = z = sig2z = zsep = 1000.;  // To more easily find unchecked failures

   // Express the two helices in terms of (x - xa)^2 + (y - ya)^2 == ra^2
   double ra( 1./2./a.curvature() );
   double xa( -(a.d0() + ra) * sin(a.phi0()) );
   double ya( (a.d0() + ra) * cos(a.phi0()) );

   double rb( 1./2./b.curvature() );
   double xb( -(b.d0() + rb) * sin(b.phi0()) );
   double yb( (b.d0() + rb) * cos(b.phi0()) );

   // Zero or infinitely many solutions
   // I don't want to deal with either case
   if ( xa == xb  &&  ya == yb ) return false;

   double disc( (pow(4.*sqr(ra)*(xa - xb) - 
		     4.*(sqr(rb)*(xa - xb) + 
			(xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)))
		     ,2.) - 16.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))*
		 (pow(xa,4.) - 2.*sqr(xa)*sqr(xb) + pow(xb,4.) + 
		  2.*sqr(xb)*(sqr(ra) - sqr(rb) + sqr(ya - yb)) + 
		  2.*sqr(xa)*(-sqr(ra) + sqr(rb) + sqr(ya - yb)) + 
		  pow(-sqr(ra) + sqr(rb) + sqr(ya - yb),2.) - 
		  4.*sqr(rb)*sqr(ya - yb)))/
		(64.*pow(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb),2.)) );
   // no real solutions
   if ( disc < 0 ) return false;

   double pre( (sqr(rb)*(xa - xb) + sqr(ra)*(-xa + xb) + 
		(xa + xb)*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb)))/
	       (2.*(sqr(xa) - 2.*xa*xb + sqr(xb) + sqr(ya - yb))) );

   // The two x solutions
   double xsol1( pre + sqrt( disc ) );
   double xsol2( pre - sqrt( disc ) );

   // Two possibilities for the y solution to each x solution
   double ysol1a( yb + sqrt( sqr(rb) - sqr(xsol1 - xb) ) );
   double ysol1b( yb - sqrt( sqr(rb) - sqr(xsol1 - xb) ) );
   double ysol1;
   if ( abs( sqr(xsol1 - xa) + sqr(ysol1a - ya) - sqr(ra) ) <
	abs( sqr(xsol1 - xa) + sqr(ysol1b - ya) - sqr(ra) )   )
      ysol1 = ysol1a;
   else
      ysol1 = ysol1b;

   double ysol2a( yb + sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2b( yb - sqrt( sqr(rb) - sqr(xsol2 - xb) ) );
   double ysol2;
   if ( abs( sqr(xsol2 - xa) + sqr(ysol2a - ya) - sqr(ra) ) <
	abs( sqr(xsol2 - xa) + sqr(ysol2b - ya) - sqr(ra) )   )
      ysol2 = ysol2a;
   else
      ysol2 = ysol2b;

   // Calculate the arclength of each solution along the two tracks.
   // Throw out a solution if the particle needs to travel (too far)
   // backward to get to it. If both solutions are okay, take the one
   // closest to the origin.
   DABoolean arclength1_ok( arclength_test( xsol1, ysol1, a, b ) );
   DABoolean arclength2_ok( arclength_test( xsol2, ysol2, a, b ) );
   
   if ( !arclength1_ok  &&  !arclength2_ok ) return false;

   else if ( arclength1_ok  &&  !arclength2_ok ) {
      x = xsol1;  y = ysol1;
   }

   else if ( !arclength1_ok  &&  arclength2_ok ) {
      x = xsol2;  y = ysol2;
   }

   else if ( sqr(xsol1) + sqr(ysol1) < sqr(xsol2) + sqr(ysol2) ) {
      x = xsol1;  y = ysol1;
   }

   else {
      x = xsol2;  y = ysol2;
   }      

   double asinphi1( 2. * a.curvature() * (x * cos(a.phi0()) + y * sin(a.phi0())) );
   double acosphi1( 2. * a.curvature() * (x * sin(a.phi0()) - y * cos(a.phi0())
					  + a.d0()) + 1. );
   double aarclength( atan2(asinphi1, acosphi1) / 2. / a.curvature() );

   double bsinphi1( 2. * b.curvature() * (x * cos(b.phi0()) + y * sin(b.phi0())) );
   double bcosphi1( 2. * b.curvature() * (x * sin(b.phi0()) - y * cos(b.phi0())
					  + b.d0()) + 1. );
   double barclength( atan2(bsinphi1, bcosphi1) / 2. / b.curvature() );

   double az( a.cotTheta() * aarclength + a.z0() );
   double bz( b.cotTheta() * barclength + b.z0() );
   double sig2_az( a.errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta) * sqr(aarclength)
		   + a.errorMatrix()(KTHelix::kZ0, KTHelix::kZ0)
		   + 2. * aarclength * a.errorMatrix()(KTHelix::kCotTheta, KTHelix::kZ0) );
   double sig2_bz( b.errorMatrix()(KTHelix::kCotTheta, KTHelix::kCotTheta) * sqr(barclength)
		   + b.errorMatrix()(KTHelix::kZ0, KTHelix::kZ0)
		   + 2. * barclength * b.errorMatrix()(KTHelix::kCotTheta, KTHelix::kZ0) );

   z = (az/sig2_az + bz/sig2_bz) / (1./sig2_az + 1./sig2_bz);
   sig2z = 1. / (1./sig2_az + 1./sig2_bz);
   zsep = abs(az - bz) + sqrt(sig2_az) + sqrt(sig2_bz);  // so that uncertain intersections may be ruled out

   // Because it is not useful for the `closest_intersection'
   // algorithm, I had to throw out a great deal of lovely code that
   // calculates uncertanties in x and y.  If you want this, ask me
   // about it.
   return true;
}

DABoolean arclength_test( double x, double y, KTHelix& a, KTHelix& b )
{
   const double tailCut = 0.005;

   double asinphi1( 2. * a.curvature() * (x * cos(a.phi0()) + y * sin(a.phi0())) );
   double acosphi1( 2. * a.curvature() * (x * sin(a.phi0()) - y * cos(a.phi0())
					  + a.d0()) + 1. );
   double aarclength( atan2(asinphi1, acosphi1) / 2. / a.curvature() );

   double bsinphi1( 2. * b.curvature() * (x * cos(b.phi0()) + y * sin(b.phi0())) );
   double bcosphi1( 2. * b.curvature() * (x * sin(b.phi0()) - y * cos(b.phi0())
					  + b.d0()) + 1. );
   double barclength( atan2(bsinphi1, bcosphi1) / 2. / b.curvature() );

   return ( aarclength > -tailCut  &&  aarclength < M_PI/2./abs(a.curvature()) )  &&
      ( barclength > -tailCut  &&  barclength < M_PI/2./abs(b.curvature()) );
}
