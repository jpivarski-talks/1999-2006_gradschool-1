<< "kf_fits.m"

badlist = { 126253, 126261, 126263, 126264, 126267, 126270, 126271, 126272, 126273, 126274, 126422, 126424, 126428, 126430, 126450, 126452, 126453, 126455, 126456, 126457, 126458, 126459, 126462, 126466, 126468, 126497, 126498, 126499, 126500, 126503, 126504, 126515, 126516, 126519, 126520, 126521, 126524, 126525, 126526, 126528, 126529, 126530, 126531, 126533, 126534, 126535, 126537, 126544, 126545, 126546, 126553, 126558, 126560, 126561, 126648, 126649, 126650, 126651, 126655, 126659, 126660, 126661, 126663, 126671, 126672 };

y2s = { 2 * #[[3]], #[[4]], #[[5]] }& /@
    Select[ 
	ReadList[ "../fits/may28-02/pass1/data.dat", {Number,Word,Number,Number,Number} ],
	(!MemberQ[badlist,#[[1]]]&) ];

PlotFuncData[ KuraevFadinY2s, y2s, "First Y(2s) Data --- May 22 through June 7, 2002", {ImageSize->72*10} ]

fit = FitToFunc[ KuraevFadinY2s, y2s ]

Out[41]= {89.6291, 68, {KFJustFunc, {121.87, 10.0245, 4.13306, 3.27165}, 
 
>     {area, mean, sigma, back}, {MeV nb, GeV, MeV, nb}, 
 
>     {{0.66324, 0.0000117448, 0.0247693, -0.00267965}, 
 
                                -10            -7            -8
>      {0.0000117448, 8.07325 10   , 5.26016 10  , -1.3064 10  }, 
 
                             -7
>      {0.0247693, 5.26016 10  , 0.00104692, -0.000059057}, 
 
                               -8
>      {-0.00267965, -1.3064 10  , -0.000059057, 0.0000700264}}}}

$DisplayFunction

Out[59]= Module[{System`Private`file = OpenTemporary[]}, 
 
>     Display[{$Display, System`Private`file}, #1]; 
 
>      System`Private`file = Close[System`Private`file]; 
 
>      System`Private`$DisplayLinkCommands[System`Private`file, 
 
>       $DisplayTitle]; #1] & 

$DisplayFunction = Display["first_y2s.eps",#,"EPS"]&;
PlotFuncData[ fit[[3]], y2s, "First Y(2s) Data --- May 22 through June 7, 2002", {ImageSize->72*5} ]

PlotDiffFuncData[ fit[[3]], y2s, "First Y(2s) Data --- May 22 through June 7, 2002", {ImageSize->72*10} ]

<< Statistics`DescriptiveStatistics`

126429  S       5.01062 7.43    0.09
126431  S       5.01065 7.43    0.09
126432  S       5.01061 7.60    0.09
126433  S       5.01063 7.57    0.09
126434  S       5.01063 7.39    0.09

... time passes ...

126462  S       5.01067 7.69    0.17
126464  S       5.01071 7.69    0.11
126465  S       5.01063 7.58    0.10
126467  S       5.01065 7.51    0.13

WeightedMean[ points:{ { _, _ } .. } ] := Module[
    { xoversig2sum, oneoversig2sum },
    xoversig2sum = Plus @@ ( ( #[[1]] / #[[2]]^2 )& /@ points );
    oneoversig2sum = Plus @@ ( ( 1 / #[[2]]^2 )& /@ points );
    If[ oneoversig2sum == 0, { 0, 0 },
	{ xoversig2sum / oneoversig2sum, Sqrt[ 1 / oneoversig2sum ] } ] ];

firstenergy = Mean[ { 5.01062,
		      5.01065,
		      5.01061,
		      5.01063,
		      5.01063 } ]

Out[52]= 5.01063

firsthxc = WeightedMean[ { {7.43, 0.09},
			     {7.43, 0.09},
			     {7.60, 0.09},
			     {7.57, 0.09},
			     {7.39, 0.09} } ]

Out[49]= {7.484, 0.0402492}

secondenergy = Mean[ { 5.01067,
		       5.01071,
		       5.01063,
		       5.01065 } ]

Out[53]= 5.01067

secondhxc = WeightedMean[ { {7.69, 0.17},
			      {7.69, 0.11},
			      {7.58, 0.10},
			      {7.51, 0.13} } ]

Out[50]= {7.61167, 0.0601474}

seperationizer[ { en1_, hxc1_, err1_ }, { en2_, hxc2_, err2_ },
		{ area_, mean_, sigma_, back_ } ] :=
    Module[ {ediff,eave,thisfunc,d,val,int,eproj1,eproj2,eprojdiff},
	    ediff = en1 - en2;
	    eave = ( en1 + en2 ) / 2.;
	    theseparams = { area, mean, sigma, back };
	    thisfunc = { KFJustFunc, theseparams, KFNames, KFLabels, KFErrorMatrix };
	    d = D[ EvalFunc[ thisfunc, x ], x ] /. x -> 2*eave // Chop;
	    val = EvalFunc[ thisfunc, 2*eave ] // Chop;
	    int = val - 2*eave*d;
	    eproj1 = ((# - int)/d)& /@ { hxc1, hxc1 + err1 }; (* project hxcs to energy axis *)
	    eproj2 = ((# - int)/d)& /@ { hxc2, hxc2 + err2 };
	    eproj1[[2]] = Abs[ eproj1[[2]] - eproj1[[1]] ]; (* we want uncertainty, *)
	    eproj2[[2]] = Abs[ eproj2[[2]] - eproj2[[1]] ]; (* not an upper bound *)
	    eprojdiff = { eproj1[[1]] - eproj2[[1]], Sqrt[ eproj1[[2]]^2 + eproj2[[2]]^2 ] };
	    Print[ "derivative and nominal value = ", d, " nb/GeV and ", val, " nb" ];
	    Print[ "ediff = ", ediff*1000, " MeV" ];
	    Print[ "eprojdiff = ", eprojdiff[[1]]*1000, " +/- ", eprojdiff[[2]]*1000, " MeV" ];
	    Print[ "miscalibration = ", (ediff - eprojdiff[[1]])*1000, " +/- ",
		   eprojdiff[[2]]*1000, " MeV" ];
	  ]

seperationizer[ { firstenergy, firsthxc[[1]], firsthxc[[2]] },
		{ secondenergy, secondhxc[[1]], secondhxc[[2]] },
		fit[[3,2]] ]

derivative and nominal value = 867.762 nb/GeV and 7.54209 nb
ediff = -0.037 MeV
eprojdiff = -0.14713 +/- 0.0834007 MeV
miscalibration = 0.11013 +/- 0.0834007 MeV

