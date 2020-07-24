Print[ "Start!" ];

(* $DisplayFunction = ( Display[ "/cdat/dafe/mccann/tmp.eps", #, "EPS" ]; *)
(* 		     Run[ "kill `ps -u mccann | grep psrender | grep -v grep | awk '{print $1}'`" ] ; *)
(* 		     Run[ "gv", "/cdat/dafe/mccann/tmp.eps" ]; *)
(* 		     # )& *)

SetDirectory["/home/mccann/public_html/private/my_gammaee"];
<< tools/kf_fits.m;

Print[ "Loaded kf_fits.m." ];

(* each data set must be handled separately *)
jan16 = ToCOM[ { #[[3]], #[[4]], #[[5]] }& /@
	       Select[
		   ReadList[ "fits/jan16-02/pass1/data.dat",
			     { Number, Word, Number, Number, Number }
			   ],
		   ( #[[2]] == "S" )&
		     ]
	     ];
jan30 = ToCOM[ { #[[3]], #[[4]], #[[5]] }& /@
	       Select[
		   ReadList[ "fits/jan30-02/pass1/data.dat",
			     { Number, Word, Number, Number, Number }
			   ],
		   ( #[[2]] == "S"  ||  #[[2]] == "P" )&
		     ]
	     ];
feb06 = ToCOM[ { #[[3]], #[[4]], #[[5]] }& /@
	       Select[
		   ReadList[ "fits/feb06-02/pass1/data.dat",
			     { Number, Word, Number, Number, Number }
			   ],
		   ( #[[2]] == "S"  ||  #[[2]] == "P"  ||  #[[2]] == "C" )&
		     ]
	     ];
feb14 = ToCOM[ { #[[3]], #[[4]], #[[5]] }& /@
	       Select[
		   ReadList[ "fits/feb14-02/pass1/data.dat",
			     { Number, Word, Number, Number, Number }
			   ],
		   ( #[[2]] == "C" )&
		     ]
	     ];
feb20 = ToCOM[ { #[[3]], #[[4]], #[[5]] }& /@
	       Select[
		   ReadList[ "fits/feb20-02/pass1/data.dat",
			     { Number, Word, Number, Number, Number }
			   ],
		   ( #[[2]] == "S"  ||  #[[2]] == "P"  ||  #[[2]] == "C" )&
		     ]
	     ];
feb28 = ToCOM[ { #[[3]], #[[4]], #[[5]] }& /@
	       Select[
		   ReadList[ "fits/feb28-02/pass1/data.dat",
			     { Number, Word, Number, Number, Number }
			   ],
		   ( #[[2]] == "S"  ||  #[[2]] == "P"  ||  #[[2]] == "C" )&
		     ]
	     ];
mar06 = ToCOM[ { #[[3]], #[[4]], #[[5]] }& /@
	       Select[
		   ReadList[ "fits/mar06-02/pass1/data.dat",
			     { Number, Word, Number, Number, Number }
			   ],
		   ( #[[2]] == "S"  ||  #[[2]] == "P"  ||  #[[2]] == "C" )&
		     ]
	     ];
mar14 = ToCOM[ { #[[3]], #[[4]], #[[5]] }& /@
	       Select[
		   ReadList[ "fits/mar14-02/pass1/data.dat",
			     { Number, Word, Number, Number, Number }
			   ],
		   ( #[[2]] == "S"  ||  #[[2]] == "P"  ||  #[[2]] == "C" )&
		     ]
	     ];
mar21 = ToCOM[ { #[[3]], #[[4]], #[[5]] }& /@
	       Select[
		   ReadList[ "fits/mar06-02/pass1/data.dat",
			     { Number, Word, Number, Number, Number }
			   ],
		   ( #[[2]] == "C"  ||  #[[2]] == "H" )&
		     ]
	     ];
apr02 = ToCOM[ { #[[3]], #[[4]], #[[5]] }& /@
	       Select[
		   ReadList[ "fits/apr02-02/pass1/data.dat",
			     { Number, Word, Number, Number, Number }
			   ],
		   ( #[[2]] == "S"  ||  #[[2]] == "P"  ||  #[[2]] == "C" )&
		     ]
	     ];
apr08 = ToCOM[ { #[[3]], #[[4]], #[[5]] }& /@
	       Select[
		   ReadList[ "fits/apr08-02/pass1/data.dat",
			     { Number, Word, Number, Number, Number }
			   ],
		   ( #[[2]] == "S"  ||  #[[2]] == "P" )&
		     ]
	     ];

y1sTags = { "jan16-02", "jan30-02", "feb06-02", "feb20-02", "feb28-02",
	    "mar06-02", "mar14-02", "apr02-02", "apr08-02" };
y1sData = { jan16, jan30, feb06, feb20, feb28, mar06, mar14, apr02, apr08 };
y1sExtra = { feb14, mar21 };

y1sTags = { "apr08-02" };
y1sData = { apr08 };
y1sExtra = {};

Print[ "Loaded all pass1 data, about to do the fits." ];

(* Careful! This does all of the fits again! *)
y1sfits = Table[ Module[ {chi2, dof, fittedfunc, html},
			 {chi2, dof, fittedfunc} = FitToFunc[ KuraevFadinY1s, y1sData[[i]] ];
			 Print[ "Finished fit for " <> y1sTags[[i]] ];
			 $DisplayFunction = Display[
			     "fits/" <> y1sTags[[i]] <> "/pass1/kf_fit.gif", #, "GIF" ]&;
			 PlotFuncData[ fittedfunc, y1sData[[i]],
				       "Kuraev-Fadin Fit to " <> y1sTags[[i]],
				       { ImageSize -> 72 5 } ];
			 html = OpenWrite[ "fits/" <> y1sTags[[i]] <> "/pass1/kf_fit.html" ];
			 WriteString[ html,
				      HTMLFitOutput[ { chi2, dof, fittedfunc }, "Kuraev-Fadin" ] ];
			 Close[ html ];
			 {chi2, dof, fittedfunc}
		       ], {i,1,Length[y1sData]} ];

Finished fit for jan16-02
Finished fit for jan30-02
Finished fit for feb06-02
Finished fit for feb20-02
Finished fit for feb28-02
Finished fit for mar06-02
Finished fit for mar14-02
Finished fit for apr02-02
Finished fit for apr08-02

Print[ "Finished all the fits." ];

WeightedMean[ points:{ { ( _Integer | _Real ), ( _Integer | _Real ) } .. } ] := Module[
    { xoversig2sum, oneoversig2sum },
    xoversig2sum = Plus @@ ( ( #[[1]] / #[[2]]^2 )& /@ points );
    oneoversig2sum = Plus @@ ( ( 1 / #[[2]]^2 )& /@ points );
    If[ oneoversig2sum == 0, { 0, 0 },
	{ xoversig2sum / oneoversig2sum, Sqrt[ 1 / oneoversig2sum ] } ] ];

y1scollectedfitresults = WeightedMean /@ Table[ { y1sfits[[i, 3, 2, j]],
					       Sqrt[ y1sfits[[i, 3, 5]][[j, j]] ] },
					     {j,1,Length[GetNames[KuraevFadinY1s]]},
					     {i,1,Length[y1sfits]} ];

y1sidealfit = { GetFunc[KuraevFadinY1s],
		#[[1]]& /@ y1scollectedfitresults,
		GetNames[KuraevFadinY1s],
		GetLabels[KuraevFadinY1s],
		DiagonalMatrix[ #[[2]]^2& /@ y1scollectedfitresults ]
	      };

WriteString[ OpenWrite[ "fits/y1s_kf_merged.html" ],
	     HTMLFitOutput[ { 1, 1, y1sidealfit }, "Merged Kuraev-Fadin" ]
	   ]

ShiftData[ data:Data, amount:FParam ] := { X[#] + amount, Y[#], ErrY[#] }& /@ data;
ally1sData = Sort[ Join @@ Table[
    ShiftData[ y1sData[[i]], y1scollectedfitresults[[2,1]] - y1sfits[[i, 3, 2, 2]] ],
    {i,1,Length[y1sData]} ],
		   ( #1[[1]] < #2[[1]] )& ];

(* This was useful to find the boundaries between the data points. *)
(* ListPlot[ ( 1000 * #[[1]] )& /@ ally1sData, *)
(* 	  GridLines -> { None, Range[10328, 10400, 1] }, *)
(* 	  ImageSize -> 72 5, *)
(* 	  PlotRange -> { { 360, 420 }, { 10360, 10400 } } *)
(* 	] *)

tmp = Range[ 2 * 4.73 - 0.100, 2 * 4.73 + 0.100, 0.001 ];
y1sboundaries = Table[ { tmp[[i]], tmp[[i+1]] }, {i,1,Length[tmp]-1} ];

(* This is for checking that the boundaries are in the right places (they are). *)
(* Show[ *)
(*     MultipleListPlot[ PlotDataPoints[ ally1sData ], DisplayFunction -> Identity ], *)
(*     Table[ Line[ { {y1sboundaries[[i]][[1]], 0}, {y1sboundaries[[i]][[1]], 10} } ], *)
(* 	   {i,1,Length[y1sboundaries]} *)
(* 	 ] // Graphics, *)
(*     ImageSize -> 72 10, *)
(*     DisplayFunction -> $DisplayFunction ] *)

Schooch[ { energy:FParam, hxc:FParam, hxcerr:FParam },
	 newenergy:FParam, f:Func ] :=
    { newenergy, hxc + EvalFunc[ f, newenergy ] - EvalFunc[ f, energy ], hxcerr };

SchoochAll[ alldata:Data, boundaries:{ { _Real, _Real } .. }, ideal:Func ] :=
    Module[ {groups,middle},
	    (* partition the whole dataset according to datapoint *)
	    groups = Table[ Select[ alldata, ( boundaries[[i,1]] < #[[1]]  &&
					       #[[1]] < boundaries[[i,2]] )& ],
			    {i,1,Length[boundaries]} ];
	    (* for each, schooch all the points to their appropriate middle *)
	    Join @@ Table[ ( middle = Mean[ X /@ groups[[i]] ];
			     Schooch[ #, middle, ideal ]& /@ groups[[i]] ),
			   {i,1,Length[groups]} ]
	  ];

Merge[ data:Data ] := Prepend[ WeightedMean[ { Y[#], ErrY[#] }& /@ data ],
			       Mean[ X /@ data ] ];

MergeAll[ alldata:Data, boundaries:{ { _Real, _Real } .. }, ideal:Func ] :=
    Module[ {groups,middle},
	    (* partition the whole dataset according to datapoint *)
	    groups = Table[ Select[ alldata, ( boundaries[[i,1]] < #[[1]]  &&
					       #[[1]] < boundaries[[i,2]] )& ],
			    {i,1,Length[boundaries]} ];
	    (* for each, schooch all the points to their appropriate
	       middle and merge *)
	    Table[ Merge[ ( middle = Mean[ X /@ groups[[i]] ];
			    Schooch[ #, middle, ideal ]& /@ groups[[i]] ) ],
		   {i,1,Length[groups]} ]
	  ];
          
Print[ "Ready to plot data." ];

y1smergeddata = MergeAll[ ally1sData, y1sboundaries, y1sidealfit ];

$DisplayFunction = Display[ "fits/y1s_kf_merged.eps", #, "EPS" ]&;
PlotFuncData[ y1sidealfit, y1smergeddata, "Kuraev-Fadin Fit to All Upsilon-3s Data",
	      { ImageSize -> 72 * 7 } ];

$DisplayFunction = Display[ "fits/y1s_kf_merged.gif", #, "GIF" ]&;
PlotFuncData[ y1sidealfit, y1smergeddata, "Kuraev-Fadin Fit to All Upsilon-3s Data",
	      { ImageSize -> 72 * 7 } ];

$DisplayFunction = Display[ "fits/y1s_kf_merged_diff.gif", #, "GIF" ]&;
PlotDiffFuncData[ y1sidealfit, y1smergeddata,
		  "Difference Plot of All Upsilon-3s Data to Kuraev-Fadin Fit",
		  { ImageSize -> 72 * 7 } ];

DumpSave[ "fits/y1s_kf_dumpsave.mx",
	  { background, JSJustFunc, JSParams, JSNames, JSLabels, JSErrorMatrix, JacksonSharre,
	    KFJustFunc, KFParams, KFNames, KFLabels, KFErrorMatrix, KuraevFadinY1s,
	    y3sTags, y1sTags, y1sData, y1sExtra,
	    y1sfits, y1scollectedfitresults, y1sidealfit,
	    ally1sData, y1sboundaries, y1smergeddata } ];

Run[ "kill -9 `ps -fu mccann | grep psrender | grep -v grep | awk '{print $2}'`" ];

Print[ "Done!" ];

Exit
[Mathematica finished.]

fittedfunc = y1sfits[[1,3]]

Out[9]= {KFJustFunc, {298.537, 9.45971, 3.78883, 3.60196}, 
 
>    {area, mean, sigma, back}, {MeV nb, GeV, MeV, nb}, 
 
                          -6
>    {{1.84182, 4.74674 10  , 0.0177656, -0.0318977}, 
 
                 -6            -10            -8             -8
>     {4.74674 10  , 2.18445 10   , 7.23522 10  , -6.14679 10  }, 
 
                            -8
>     {0.0177656, 7.23522 10  , 0.000208377, -0.000259346}, 
 
                              -8
>     {-0.0318977, -6.14679 10  , -0.000259346, 0.00079124}}}

$DisplayFunction = Module[{System`Private`file = OpenTemporary[]}, 
			  Display[{$Display, System`Private`file}, #1]; System`Private`file = 
			  Close[System`Private`file]; System`Private`$DisplayLinkCommands[
			      System`Private`file, $DisplayTitle]; #1]&

(* 125254 *)
(* sen lock failed for two (which two?) of these readings *)
d = { 4.73035, 4.73035, 4.73035, 4.73035, 4.73035, 4.73035,
      4.73035, 4.73035, 4.73035, 4.73035, 4.73035, 4.73035, 4.73035,
      4.73035, 4.73035, 4.73035, 4.73035, 4.73035, 4.72933, 4.72939,
      4.72939, 4.72773, 4.72773, 4.72773, 4.72773, 4.72936 };
2000 * { Mean[d], StandardDeviation[d] }

Out[24]= {9459.59, 1.93225}

(* 125262 *)
d = { 4.73279, 4.73279, 4.73279, 4.72929, 4.72928, 4.72928, 4.72928,
      4.72928, 4.72928, 4.72928, 4.72931, 4.72931 };
2000 * { Mean[d], StandardDeviation[d] }

Out[25]= {9460.33, 3.16796}

(* 125285 *)
d = { 4.72999, 4.72999, 4.72999, 4.72999, 4.72999, 4.72999, 4.72931,
      4.72931, 4.72931, 4.72931, 4.72931, 4.72933 };
2000 * { Mean[d], StandardDeviation[d] }

Out[26]= {9459.3, 0.706841}

(* 125295 *)
d = { 4.73284, 4.73284, 4.73284, 4.7293, 4.72934, 4.72934, 4.72935,
      4.72935, 4.72934, 4.72934, 4.72934 };
2000 * { Mean[d], StandardDeviation[d] }

Out[27]= {9460.59, 3.27214}



Plot[ EvalFunc[ fittedfunc, x/1000 ], { x, 9400, 9500 } ]

Out[33]= -Graphics-


Show[ 
    MultipleListPlot[ { { { 9459.59, 19.24 }, ErrorBar[ 1.93, 0.24 ] },
			{ { 9460.33, 18.68 }, ErrorBar[ 3.17, 0.23 ] },
			{ { 9459.3, 18.67 }, ErrorBar[ 0.71, 0.28 ] },
			{ { 9460.59, 19.36 }, ErrorBar[ 3.27, 0.24 ] } },
		      DisplayFunction -> Identity ],
    Plot[ EvalFunc[ fittedfunc, x/1000 ], { x, 9458, 9464 },
	  DisplayFunction -> Identity ],
    DisplayFunction -> $DisplayFunction ]

Out[43]= -Graphics-

Out[42]= -Graphics-
    

Out[41]= -Graphics-

Out[34]= -Graphics-



(* 125254 *)
d = { 4.72933, 4.72939, 4.72939, 4.72773, 4.72773, 4.72773, 4.72773, 4.72936 };
2000 * { Mean[d], StandardDeviation[d] }

Out[44]= {9457.1, 1.75097}

(* 125262 *)
d = { 4.72929, 4.72928, 4.72928, 4.72928,
      4.72928, 4.72928, 4.72928, 4.72931, 4.72931 };
2000 * { Mean[d], StandardDeviation[d] }

Out[45]= {9458.58, 0.0260342}

(* 125285 *)
d = { 4.72931,
      4.72931, 4.72931, 4.72931, 4.72931, 4.72933 };
2000 * { Mean[d], StandardDeviation[d] }

Out[46]= {9458.63, 0.0163299}

(* 125295 *)
d = { 4.7293, 4.72934, 4.72934, 4.72935,
      4.72935, 4.72934, 4.72934, 4.72934 };
2000 * { Mean[d], StandardDeviation[d] }

Out[47]= {9458.68, 0.0316228}

Show[ 
    MultipleListPlot[ { { { 9458.58, 18.68 }, ErrorBar[ 0.026, 0.23 ] },
			{ { 9458.63, 18.67 }, ErrorBar[ 0.016, 0.28 ] },
			{ { 9458.68, 19.36 }, ErrorBar[ 0.032, 0.24 ] } },
		      DisplayFunction -> Identity ],
    Plot[ EvalFunc[ fittedfunc, x/1000 ], { x, 9458, 9460 },
	  DisplayFunction -> Identity ],
    DisplayFunction -> $DisplayFunction ]

Out[49]= -Graphics-

Out[48]= -Graphics-

Series[ EvalFunc[ fittedfunc, x/1000 ], { x, 9455.56, 1 } ] // Chop

                                                              2
Out[51]= 11.9028 + 0.00488661 (-9455.56 + x) + O[-9455.56 + x]

Plot[ EvalFunc[ fittedfunc, x/1000 ], { x, 9455.44, 9455.64 } ]

Out[53]= -Graphics-

Out[52]= -Graphics-

Simplify[ 11.9028 + 0.00488661 (-9455.56 + x) ]

Out[54]= -34.3028 + 0.00488661 x

D[ EvalFunc[ fittedfunc, x ], x ] /. x -> 9.45556 // Chop

Out[62]= 2520.55

EvalFunc[ fittedfunc, 9.45556 ]

Out[63]= 11.9028

Solve[ 11.9028 == int + 2.52055 * 9455.56, int ]

Out[65]= {{int -> -23821.3}}

Exit
[Mathematica finished.]
