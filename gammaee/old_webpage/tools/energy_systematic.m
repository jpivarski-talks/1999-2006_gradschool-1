<< kf_fits.m

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

(* ************* NOW FOR THE Y(1S) STUDIES ************************ *)

(* Jan 30 *)
seperationizer[ { 4.72848, 15.30, 0.16 },
		{ 4.72997, 19.83, 0.17 },
		{ 297.28896794619465, 9.459783069692769, 3.8448965272527498, 3.598381614667817 } ]

derivative and nominal value = 1676.09 nb/GeV and 18.3304 nb
ediff = -1.49 MeV
eprojdiff = -2.70272 +/- 0.139284 MeV
miscalibration = 1.21272 +/- 0.139284 MeV

(* Feb 6 *)
seperationizer[ { 4.72836, 13.27, 0.14 },
		{ 4.72836, 13.32, 0.16 },
		{ 295.29822945647675, 9.460289903273866, 3.8366424204190475, 3.5711695265323233 } ]

derivative and nominal value = 2499.1 nb/GeV and 13.2466 nb
ediff = 0. MeV
eprojdiff = -0.0200072 +/- 0.0850719 MeV
miscalibration = 0.0200072 +/- 0.0850719 MeV

(* Feb 20 (1) *)
seperationizer[ { 4.72846, 13.97, 0.16 },
		{ 4.72830, 13.12, 0.15 },
		{ 296.94597884885496, 9.460242161897161, 3.86566319496112, 3.5927986775381 } ]

derivative and nominal value = 2476.06 nb/GeV and 13.54 nb
ediff = 0.16 MeV
eprojdiff = 0.343287 +/- 0.088575 MeV
miscalibration = -0.183287 +/- 0.088575 MeV

(* Feb 20 (2) *)
seperationizer[ { 4.72830, 13.10, 0.10 },
		{ 4.72842, 13.81, 0.17 },
		{ 296.94597884885496, 9.460242161897161, 3.86566319496112, 3.5927986775381 } ]

derivative and nominal value = 2476.91 nb/GeV and 13.4409 nb
ediff = -0.12 MeV
eprojdiff = -0.286648 +/- 0.0796278 MeV
miscalibration = 0.166648 +/- 0.0796278 MeV

(* Mar 6 *)
seperationizer[ { 4.72910, 17.88, 0.27 },
		{ 4.72902, 17.63, 0.21 },
		{ 295.6489702226542, 9.459901954344254, 3.802160710204467, 3.5798137258962597 } ]

derivative and nominal value = 2018.72 nb/GeV and 17.5148 nb
ediff = 0.08 MeV
eprojdiff = 0.123841 +/- 0.16944 MeV
miscalibration = -0.0438407 +/- 0.16944 MeV

(* Mar 14 *)
seperationizer[ { 4.72912, 17.36, 0.20 },
		{ 4.72901, 17.22, 0.19 },
		{ 297.51360407899114, 9.46000860947111, 3.836229424255173, 3.5697850585614357 } ]

derivative and nominal value = 2044.22 nb/GeV and 17.3163 nb
ediff = 0.11 MeV
eprojdiff = 0.0684859 +/- 0.134948 MeV
miscalibration = 0.0415141 +/- 0.134948 MeV

(* Apr 8 (1) *)
seperationizer[ { 4.72933, 19.24, 0.24 },
		{ 4.72929, 18.68, 0.23 },
		{ 298.53681153791666, 9.459706911862897, 3.7888288825633203, 3.6019598465701996 } ]

derivative and nominal value = 1549.53 nb/GeV and 18.9672 nb
ediff = 0.04 MeV
eprojdiff = 0.361401 +/- 0.214527 MeV
miscalibration = -0.321401 +/- 0.214527 MeV

(* Apr 8 (2) *)
seperationizer[ { 4.72931, 18.67, 0.28 },
		{ 4.72930, 19.36, 0.24 },
		{ 298.53681153791666, 9.459706911862897, 3.7888288825633203, 3.6019598465701996 } ]

derivative and nominal value = 1557.85 nb/GeV and 18.9517 nb
ediff = 0.01 MeV
eprojdiff = -0.442919 +/- 0.236725 MeV
miscalibration = 0.452919 +/- 0.236725 MeV

(* ************* NOW FOR THE Y(3S) STUDIES ************************ *)

(* dec 6 *)
seperationizer[ { 5.18141, 6.10, 0.08 },
		{ 5.18141, 6.25, 0.09 },
		{ 81.29918155682427, 10.358973109732164, 4.614094116381001, 3.3245364189039153 } ]

derivative and nominal value = -381.629 nb/GeV and 6.23556 nb
ediff = 0. MeV
eprojdiff = 0.393052 +/- 0.315531 MeV
miscalibration = -0.393052 +/- 0.315531 MeV

(* dec 13 *)
seperationizer[ { 5.17740, 5.78, 0.09 },
		{ 5.17725, 5.77, 0.10 },
		{ 82.96291817985245, 10.358201777289368, 4.629658387469288, 3.192245590818771 } ]

derivative and nominal value = 470.883 nb/GeV and 5.74831 nb
ediff = 0.15 MeV
eprojdiff = 0.0212367 +/- 0.28571 MeV
miscalibration = 0.128763 +/- 0.28571 MeV

(* dec 20 *)
seperationizer[ { 5.17730, 5.71, 0.10 },
		{ 5.17730, 5.94, 0.09 },
		{ 82.99390484348535, 10.358027698473462, 4.621726510947831, 3.2194037694735393 } ]

derivative and nominal value = 468.469 nb/GeV and 5.8317 nb
ediff = 0. MeV
eprojdiff = -0.490961 +/- 0.287183 MeV
miscalibration = 0.490961 +/- 0.287183 MeV

(* dec 25 *)
seperationizer[ { 5.17743, 5.92, 0.09 },
		{ 5.17742, 5.99, 0.08 },
		{ 82.63698977976541, 10.358011369294552, 4.664889567682248, 3.292945963515927 } ]

derivative and nominal value = 445.282 nb/GeV and 5.99365 nb
ediff = 0.01 MeV
eprojdiff = -0.157204 +/- 0.270426 MeV
miscalibration = 0.167204 +/- 0.270426 MeV

(* jan 3 *)
seperationizer[ { 5.17702, 5.56, 0.08 },
		{ 5.17679, 5.41, 0.09 },
		{ 83.44424552480679, 10.358020491828539, 4.628150358570155, 3.228366887145856 } ]

derivative and nominal value = 485.308 nb/GeV and 5.47701 nb
ediff = 0.23 MeV
eprojdiff = 0.309082 +/- 0.248123 MeV
miscalibration = -0.0790822 +/- 0.248123 MeV

(* jan 10 *)
seperationizer[ { 5.17692, 5.54, 0.10 },
		{ 5.17678, 5.35, 0.09 },
		{ 86.31259284838467, 10.358198529280855, 4.839528867783157, 3.233651743651425 } ]

derivative and nominal value = 460.964 nb/GeV and 5.42166 nb
ediff = 0.14 MeV
eprojdiff = 0.41218 +/- 0.291859 MeV
miscalibration = -0.27218 +/- 0.291859 MeV

(* weighted standard deviation?!? *)

miscalibration = 1.21272    +/- 0.139284  MeV
miscalibration = 0.0200072  +/- 0.0850719 MeV
miscalibration = -0.183287  +/- 0.088575  MeV
miscalibration = 0.166648   +/- 0.0796278 MeV
miscalibration = -0.0438407 +/- 0.16944   MeV
miscalibration = 0.0415141  +/- 0.134948  MeV
miscalibration = -0.321401  +/- 0.214527  MeV
miscalibration = 0.452919   +/- 0.236725  MeV

miscalibration = -0.393052  +/- 0.315531  MeV
miscalibration = 0.128763   +/- 0.28571   MeV
miscalibration = 0.490961   +/- 0.287183  MeV
miscalibration = 0.167204   +/- 0.270426  MeV
miscalibration = -0.0790822 +/- 0.248123  MeV
miscalibration = -0.27218   +/- 0.291859  MeV

<< Statistics`DescriptiveStatistics`

RootMeanSquare[ { 1.21272, 0.0200072, -0.183287, 0.166648, -0.0438407,
0.0415141, -0.321401, 0.452919 } ]

Out[42]= 0.480174

RootMeanSquare[ { -0.183287, 0.166648, -0.0438407, 0.0415141,
-0.321401, 0.452919 } ]

Out[44]= 0.249481

RootMeanSquare[ { -0.393052, 0.128763, 0.490961, 0.167204, -0.0790822,
-0.27218 } ]

Out[43]= 0.294507

y1svars = {
    { 1.21272,       0.139284  },
    { 0.0200072,     0.0850719 },
    { -0.183287,     0.088575  },
    { 0.166648,      0.0796278 },
    { -0.0438407,    0.16944   },
    { 0.0415141,     0.134948  },
    { -0.321401,     0.214527  },
    { 0.452919,      0.236725  }
	  };
n = Length[y1svars];
wxisum = Sum[ y1svars[[i,1]]^2/y1svars[[i,2]]^2, {i,1,n} ];
wisum = Sum[ 1/y1svars[[i,2]]^2, {i,1,n} ];
Sqrt[ wxisum / ( (n-1)*wisum / n ) ]

Out[46]= 0.41395

y1svars = {
    { 0.0200072,     0.0850719 },
    { -0.183287,     0.088575  },
    { 0.166648,      0.0796278 },
    { -0.0438407,    0.16944   },
    { 0.0415141,     0.134948  },
    { -0.321401,     0.214527  },
    { 0.452919,      0.236725  }
	  };
n = Length[y1svars];
wxisum = Sum[ y1svars[[i,1]]^2/y1svars[[i,2]]^2, {i,1,n} ];
wisum = Sum[ 1/y1svars[[i,2]]^2, {i,1,n} ];
Sqrt[ wxisum / ( (n-1)*wisum / n ) ]

Out[50]= 0.17666

y3svars = {
    { -0.393052,     0.315531  },
    { 0.128763,      0.28571   },
    { 0.490961,      0.287183  },
    { 0.167204,      0.270426  },
    { -0.0790822,    0.248123  },
    { -0.27218,      0.291859  }
	  };
n = Length[y3svars];
wxisum = Sum[ y3svars[[i,1]]^2/y3svars[[i,2]]^2, {i,1,n} ];
wisum = Sum[ 1/y3svars[[i,2]]^2, {i,1,n} ];
Sqrt[ wxisum / ( (n-1)*wisum / n ) ]

Out[49]= 0.308434

{ Mean[ { 250.871, 264.051, 263.082, 264.059, 263.314, 275.239, 264.876 } ],
  StandardDeviation[ { 250.871, 264.051, 263.082, 264.059, 263.314, 275.239, 264.876 } ] }

Out[64]= {263.642, 7.06958}

7.06958/263.642

Out[67]= 0.0268151

y1sareas = {
    { 250.871, 0.009 },
    { 264.051, 0.149 },
    { 263.082, 0.031 },
    { 264.059, 1.848 },
    { 263.314, 1.416 },
    { 275.239, 0.264 },
    { 264.876, 3.883 }
	   };
n = Length[y1sareas];
wxsum = Sum[ y1sareas[[i,1]]/y1sareas[[i,2]]^2, {i,1,n} ];
wisum = Sum[ 1/y1sareas[[i,2]]^2, {i,1,n} ];
wmean = wxsum / wisum;
wxisum = Sum[ ( y1sareas[[i,1]] - wmean )^2/y1sareas[[i,2]]^2, {i,1,n} ];
{ wmean, Sqrt[ wxisum / ( (n-1)*wisum / n ) ] }

Out[66]= {251.887, 3.69978}

3.69978 / 251.887

Out[68]= 0.0146883

{ Mean[ { 76.402, 74.960, 76.924, 77.555, 76.629, 77.518 } ],
  StandardDeviation[ { 76.402, 74.960, 76.924, 77.555, 76.629, 77.518 } ] }

Out[69]= {76.6647, 0.955435}

0.955435 / 76.6647

Out[70]= 0.0124625

y3sareas = {
    { 76.402, 0.635 },
    { 74.960, 0.182 },
    { 76.924, 0.010 },
    { 77.555, 0.936 },
    { 76.629, 0.014 },
    { 77.518, 1.157 }
	   };
n = Length[y3sareas];
wxsum = Sum[ y3sareas[[i,1]]/y3sareas[[i,2]]^2, {i,1,n} ];
wisum = Sum[ 1/y3sareas[[i,2]]^2, {i,1,n} ];
wmean = wxsum / wisum;
wxisum = Sum[ ( y3sareas[[i,1]] - wmean )^2/y3sareas[[i,2]]^2, {i,1,n} ];
{ wmean, Sqrt[ wxisum / ( (n-1)*wisum / n ) ] }

Out[71]= {76.8206, 0.178107}

0.178107 / 76.8206

Out[72]= 0.00231848
