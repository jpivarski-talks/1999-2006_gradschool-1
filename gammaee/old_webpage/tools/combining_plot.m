Print[ "Start!" ];

(* $DisplayFunction = ( Display[ "/cdat/dafe/mccann/tmp.eps", #, "EPS" ]; *)
(* 		     Run[ "kill `ps -u mccann | grep psrender | grep -v grep | awk '{print $1}'`" ] ; *)
(* 		     Run[ "gv", "/cdat/dafe/mccann/tmp.eps" ]; *)
(* 		     # )& *)

SetDirectory["/home/mccann/public_html/private/my_gammaee"];
<< tools/kf_fits.m;

Print[ "Loaded kf_fits.m." ];

(* {nov29-01,dec06-01,dec13-01,dec20-01,dec25-01,jan03-02,jan10-02} *)
y3sTags = { "nov29-01", "dec06-01", "dec13-01", "dec20-01",
	    "dec25-01", "jan03-02", "jan10-02" };
y1sTags = { "jan16-02", "jan30-02", "feb06-02", "feb14-02", "feb20-02" };

y1sdata = Table[ { #[[3]], #[[4]], #[[5]] }& /@
		 ReadList[ "fits/" <> y1sTags[[i]] <> "/pass1/data.dat",
			   { Number, Word, Number, Number, Number }
			 ] // ToCOM,
		 {i,1,Length[y1sTags]}
	       ];

Print[ "Loaded all pass1 data, about to do the fits." ];

(* Careful! This does all of the fits again! *)
y1sfits = Table[ Module[ {chi2, dof, fittedfunc, html},
			 {chi2, dof, fittedfunc} = FitToFunc[ KuraevFadinY1s, y1sdata[[i]] ];
			 Print[ "Finished fit for " <> y1sTags[[i]] ];
			 $DisplayFunction = Display[
			     "fits/" <> y1sTags[[i]] <> "/pass1/kf_fit.gif", #, "GIF" ]&;
			 PlotFuncData[ fittedfunc, y1sdata[[i]],
				       "Kuraev-Fadin Fit to " <> y1sTags[[i]],
				       { ImageSize -> 72 5 } ];
			 html = OpenWrite[ "fits/" <> y1sTags[[i]] <> "/pass1/kf_fit.html" ];
			 WriteString[ html,
				      HTMLFitOutput[ { chi2, dof, fittedfunc }, "Kuraev-Fadin" ] ];
			 Close[ html ];
			 {chi2, dof, fittedfunc}
		       ], {i,1,Length[y1sdata]} ];

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
ally1sdata = Sort[ Join @@ Table[
    ShiftData[ y1sdata[[i]], y1scollectedfitresults[[2,1]] - y1sfits[[i, 3, 2, 2]] ],
    {i,1,Length[y1sdata]} ],
		   ( #1[[1]] < #2[[1]] )& ];

(* This was useful to find the boundaries between the data points. *)
(* ListPlot[ ( 1000 * #[[1]] )& /@ ally1sdata, *)
(* 	  GridLines -> { None, Range[10328, 10400, 1] }, *)
(* 	  ImageSize -> 72 5, *)
(* 	  PlotRange -> { { 360, 420 }, { 10360, 10400 } } *)
(* 	] *)

tmp = Range[ 2 * 4.73 - 0.100, 2 * 4.73 + 0.100, 0.001 ];
y1sboundaries = Table[ { tmp[[i]], tmp[[i+1]] }, {i,1,Length[tmp]-1} ];

y3sboundaries = { {10.328, 10.332},    (* cont point *)
		  {10.332, 10.346},
		  {10.346, 10.3475},
		  {10.3475, 10.350},
		  {10.350, 10.352},
		  {10.352, 10.3543},
		  {10.3543, 10.356},
		  {10.356, 10.360},    (* peak point *)
		  {10.360, 10.3635},
		  {10.3635, 10.3658},
		  {10.3658, 10.368},
		  {10.368, 10.3702},
		  {10.3702, 10.372},
		  {10.372, 10.374},
		  {10.374, 10.378},
		  {10.378, 10.380},
		  {10.380, 10.382},
		  {10.382, 10.400}     (* high point *)
		};

(* This is for checking that the boundaries are in the right places (they are). *)
(* Show[ *)
(*     MultipleListPlot[ PlotDataPoints[ ally1sdata ], DisplayFunction -> Identity ], *)
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

y1smergeddata = MergeAll[ ally1sdata, y1sboundaries, y1sidealfit ];

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
	    y3sTags, y1sTags, y1sdata,
	    y1sfits, y1scollectedfitresults, y1sidealfit,
	    ally1sdata, y1sboundaries, y1smergeddata } ];

Run[ "kill -9 `ps -fu mccann | grep psrender | grep -v grep | awk '{print $2}'`" ];

Print[ "Done!" ];
Exit;
