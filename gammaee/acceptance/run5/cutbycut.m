<< Graphics`MultipleListPlot`;

pt[eff_, y_] := {{eff, y}};
pt[eff_, stat_, y_] := {{{eff, y}, ErrorBar[{-stat, stat}, {0,0}]}};
pt[eff_, stat_, syst_, y_] := {{{eff, y}, ErrorBar[{-stat, stat}, {0,0}]}, {{eff, y}, ErrorBar[{-Sqrt[stat^2+syst^2], Sqrt[stat^2+syst^2]}, {0,0}]}};
mybarfunc[pt_, ErrorBar[xerr_, yerr_]] :=
    {Line[{pt-{Max[Abs[xerr]],0}, pt+{Max[Abs[xerr]],0}}],
     Line[{pt-{Max[Abs[xerr]],0}-{0,0.1}, pt-{Max[Abs[xerr]],0}+{0,0.1}}],
     Line[{pt+{Max[Abs[xerr]],0}-{0,0.1}, pt+{Max[Abs[xerr]],0}+{0,0.1}}]};

lowlimit = 90.5;
hilimit = 102;
textplace = 91;
mc =   Flatten[{pt[ 99.82, 0.32,  -1],
	      	pt[ 99.97, 0.05,  -2],
	      	pt[ 99.47, 0.22,  -3],
	      	pt[100.00, 0.00,  -4],
	      	pt[ 99.86, 0.14,  -5],
	      	pt[ 99.79, 0.32,  -6],
	      	pt[ 98.91, 0.47, -10],
	      	pt[ 99.08, 0.34, -11]}, 1];
mc2 =  Flatten[{pt[ 99.91,  -7],
	      	pt[100.00,  -8],
	      	pt[ 99.32,  -9],
	      	pt[ 99.23, -12]}, 1];
data = Flatten[{pt[ 98.29, 0.47, 0.67,  -2.2],
		pt[100.11, 0.66, 0.80,  -3.2],
		pt[100.04, 0.15, 0.05,  -4.2],
		pt[ 99.30, 0.20, 0.04,  -5.2],
		pt[ 99.11 + 0.3, 0.45, Sqrt[0.36^2+0.1^2],  -6.2],
		pt[100.30, 0.19, 0.07,  -7.2],
		pt[ 99.99, 0.01, 0.00,  -8.2],
		pt[ 99.85, 0.09, 0.01,  -9.2],
		pt[ 96.87, 0.92, 1.35, -11.2],
(*		pt[ 98.41, 0.49, 0.37, -12.2], *)
		pt[100.14, 0.21, 0.08, -12.2]}, 1];
Show[{
    MultipleListPlot[data
		     , SymbolShape -> {PlotSymbol[Diamond, 3]}
		     , ErrorBarFunction -> mybarfunc
		     , Prolog -> {AbsoluteThickness[0.01]}
		     , Frame -> True
		     , FrameLabel -> {"Efficiency of Cut", None, None, None}
		     , Axes -> False
		     , PlotRange -> {{lowlimit, hilimit}, {-0.4, -12.6}}
		     , FrameTicks -> {Join[{#, ToString[#], 0.01}& /@ Range[91, 102], {#, "", 0.005}& /@ Range[90.5, 102, 0.25]], None, None, None}
		     , AspectRatio -> 1
		     , DisplayFunction -> Identity
		    ],
    MultipleListPlot[mc
		     , ErrorBarFunction -> mybarfunc
		     , Prolog -> {AbsoluteThickness[0.01]}
		     , SymbolShape -> {PlotSymbol[Box, 2]}
		     , Prolog -> {AbsoluteThickness[0.01]}
		     , DisplayFunction -> Identity],
    MultipleListPlot[mc2
		     , Prolog -> {AbsoluteThickness[0.01]}
		     , SymbolShape -> {PlotSymbol[Box, 2]}
		     , Prolog -> {AbsoluteThickness[0.01]}
		     , DisplayFunction -> Identity],
    Graphics[{Text["1. Trigger", {textplace, -1.1}, {-1,0}],
	      Text["2. Closest XY < 5mm", {textplace, -2.1}, {-1,0}],
	      Text["3. Biggest shower < 85%", {textplace, -3.1}, {-1,0}],
	      Text["4. 2nd-biggest track < 85%", {textplace, -4.1}, {-1,0}],
	      Text["5. Event Z < 7.5cm", {textplace, -5.1}, {-1,0}],
	      Text["6. Visible energy > 35%", {textplace, -6.1}, {-1,0}],
	      Text["7. Two or more tracks", {textplace, -7.1}, {-1,0}],
	      Text["8. Level3/Level4", {textplace, -8.1}, {-1,0}],
	      Text["9. CC energy < 85%", {textplace, -9.1}, {-1,0}],
	      Text["1 - 6", {textplace, -10.1}, {-1,0}],
	      Text["2 - 6", {textplace, -11.1}, {-1,0}],
(*	      Text["5 - 6", {textplace, -12.1}, {-1,0}], *)
	      Text["7 - 9", {textplace, -12.1}, {-1,0}],
	      Line[{{lowlimit, -9.6},{hilimit, -9.6}}],
(*	      Circle[#[[1]], 0.15]& /@ mc,   *)
	      Dashing[{0.005, 0.01}],
	      Line[{{100, -0.4},{100, -12.6}}]}]
     }
     , ImageSize -> 60*7
     , DisplayFunction -> (Display["cutbycut_1s.eps", #, "EPS"]&)];

(* 2S UNcorrected *)
lowlimit = 90.5;
hilimit = 102;
textplace = 91;
mc =   Flatten[{pt[ 99.61, 0.55,  -1],
	      	pt[ 99.97, 0.05,  -2],
	      	pt[ 98.70, 0.08,  -3],
	      	pt[ 99.31, Sqrt[0.03^2+0.42^2],  -4],
	      	pt[ 99.88, 0.12,  -5],
	      	pt[ 99.67, 0.41,  -6],
	      	pt[ 97.17, Sqrt[0.67^2+0.42^2], -10],
	      	pt[ 97.55, Sqrt[0.38^2+0.42^2], -11]}, 1];
mc2 =  Flatten[{pt[ 99.94,  -7],
	      	pt[100.00,  -8],
	      	pt[ 99.15,  -9],
	      	pt[ 99.09, -12]}, 1];
data = Flatten[{pt[100.75, 0.71, 0.98,  -2.2],
		pt[ 99.92, 0.81, 1.00,  -3.2],
		pt[ 98.93, 0.18, 0.06,  -4.2],
		pt[ 99.94, 0.34, (* 0.20 *) 0.98,  -5.2],
		pt[ 97.67 + 0.85, 0.59, Sqrt[0.50^2+0.15^2],  -6.2],
		pt[100.14, 0.25, 0.09,  -7.2],
		pt[100.01, 0.01, 0.00,  -8.2],
		pt[ 99.62, 0.11, 0.02,  -9.2],
		pt[ 97.20, 1.26, (* 1.89 *) 2.79, -11.2],
(*		pt[ 97.61, 0.68, 0.55, -12.2], *)
		pt[ 99.77, 0.27, 0.10, -12.2]}, 1];
Show[{
    MultipleListPlot[data
		     , SymbolShape -> {PlotSymbol[Diamond, 3]}
		     , ErrorBarFunction -> mybarfunc
		     , Prolog -> {AbsoluteThickness[0.01]}
		     , Frame -> True
		     , FrameLabel -> {"Efficiency of Cut", None, None, None}
		     , Axes -> False
		     , PlotRange -> {{lowlimit, hilimit}, {-0.4, -12.6}}
		     , FrameTicks -> {Join[{#, ToString[#], 0.01}& /@ Range[91, 102], {#, "", 0.005}& /@ Range[90.5, 102, 0.25]], None, None, None}
		     , AspectRatio -> 1
		     , DisplayFunction -> Identity
		    ],
    MultipleListPlot[mc
		     , SymbolShape -> {PlotSymbol[Box, 2]}
		     , ErrorBarFunction -> mybarfunc
		     , Prolog -> {AbsoluteThickness[0.01]}
		     , DisplayFunction -> Identity],
    MultipleListPlot[mc2
		     , SymbolShape -> {PlotSymbol[Box, 2]}
		     , Prolog -> {AbsoluteThickness[0.01]}
		     , DisplayFunction -> Identity],
    Graphics[{Text["1. Trigger", {textplace, -1.1}, {-1,0}],
	      Text["2. Closest XY < 5mm", {textplace, -2.1}, {-1,0}],
	      Text["3. Biggest shower < 85%", {textplace, -3.1}, {-1,0}],
	      Text["4. 2nd-biggest track < 85%", {textplace, -4.1}, {-1,0}],
	      Text["5. Event Z < 7.5cm", {textplace, -5.1}, {-1,0}],
	      Text["6. Visible energy > 35%", {textplace, -6.1}, {-1,0}],
	      Text["7. Two or more tracks", {textplace, -7.1}, {-1,0}],
	      Text["8. Level3/Level4", {textplace, -8.1}, {-1,0}],
	      Text["9. CC energy < 85%", {textplace, -9.1}, {-1,0}],
	      Text["1 - 6", {textplace, -10.1}, {-1,0}],
	      Text["2 - 6", {textplace, -11.1}, {-1,0}],
(*	      Text["5 - 6", {textplace, -12.1}, {-1,0}], *)
	      Text["7 - 9", {textplace, -12.1}, {-1,0}],
	      Line[{{lowlimit, -9.6},{hilimit, -9.6}}],
(*	      Circle[#[[1]], 0.15]& /@ mc,   *)
	      Dashing[{0.005, 0.01}],
	      Line[{{100, -0.4},{100, -12.6}}]}]
     }
     , ImageSize -> 60*7
     , DisplayFunction -> (Display["cutbycut_2s.eps", #, "EPS"]&)];

(* 2S CORRECTED *)
lowlimit = 90.5;
hilimit = 102;
textplace = 91;
mc =   Flatten[{pt[ 99.61, 0.55,  -1],
	      	pt[ 99.97, 0.05,  -2],
	      	pt[ 98.70, 0.08,  -3],
	      	pt[ 99.31, Sqrt[0.03^2+0.39^2],  -4],
	      	pt[ 99.88, 0.12,  -5],
	      	pt[ 99.67, 0.41,  -6],
	      	pt[ 97.17, Sqrt[0.67^2+0.39^2], -10],
	      	pt[ 97.55, Sqrt[0.38^2+0.39^2], -11]}, 1];
mc2 =  Flatten[{pt[ 99.94,  -7],
	      	pt[100.00,  -8],
	      	pt[ 99.15,  -9],
	      	pt[ 99.09, -12]}, 1];
data = Flatten[{pt[100.12, 0.63, 0.88,  -2.2],
		pt[ 99.64, 0.77, 0.94,  -3.2],
		pt[ 98.97, 0.17, 0.06,  -4.2],
		pt[ 99.71, 0.32, (* 0.98 *) 0.14,  -5.2],
		pt[ 97.78 + 0.76, 0.57, Sqrt[0.47^2+0.15^2],  -6.2],
		pt[100.09, 0.23, 0.08,  -7.2],
		pt[100.01, 0.01, 0.00,  -8.2],
		pt[ 99.65, 0.11, 0.02,  -9.2],
		pt[ 96.26, 1.16, (* 2.79 *) 1.67, -11.2],
(*		pt[ 97.61, 0.68, 0.55, -12.2], *)
		pt[ 99.74, 0.26, 0.10, -12.2]}, 1];
Show[{
    MultipleListPlot[data
		     , SymbolShape -> {PlotSymbol[Diamond, 3]}
		     , ErrorBarFunction -> mybarfunc
		     , Prolog -> {AbsoluteThickness[0.01]}
		     , Frame -> True
		     , FrameLabel -> {"Efficiency of Cut", None, None, None}
		     , Axes -> False
		     , PlotRange -> {{lowlimit, hilimit}, {-0.4, -12.6}}
		     , FrameTicks -> {Join[{#, ToString[#], 0.01}& /@ Range[91, 102], {#, "", 0.005}& /@ Range[90.5, 102, 0.25]], None, None, None}
		     , AspectRatio -> 1
		     , DisplayFunction -> Identity
		    ],
    MultipleListPlot[mc
		     , SymbolShape -> {PlotSymbol[Box, 2]}
		     , ErrorBarFunction -> mybarfunc
		     , Prolog -> {AbsoluteThickness[0.01]}
		     , DisplayFunction -> Identity],
    MultipleListPlot[mc2
		     , SymbolShape -> {PlotSymbol[Box, 2]}
		     , Prolog -> {AbsoluteThickness[0.01]}
		     , DisplayFunction -> Identity],
    Graphics[{Text["1. Trigger", {textplace, -1.1}, {-1,0}],
	      Text["2. Closest XY < 5mm", {textplace, -2.1}, {-1,0}],
	      Text["3. Biggest shower < 85%", {textplace, -3.1}, {-1,0}],
	      Text["4. 2nd-biggest track < 85%", {textplace, -4.1}, {-1,0}],
	      Text["5. Event Z < 7.5cm", {textplace, -5.1}, {-1,0}],
	      Text["6. Visible energy > 35%", {textplace, -6.1}, {-1,0}],
	      Text["7. Two or more tracks", {textplace, -7.1}, {-1,0}],
	      Text["8. Level3/Level4", {textplace, -8.1}, {-1,0}],
	      Text["9. CC energy < 85%", {textplace, -9.1}, {-1,0}],
	      Text["1 - 6", {textplace, -10.1}, {-1,0}],
	      Text["2 - 6", {textplace, -11.1}, {-1,0}],
(*	      Text["5 - 6", {textplace, -12.1}, {-1,0}], *)
	      Text["7 - 9", {textplace, -12.1}, {-1,0}],
	      Line[{{lowlimit, -9.6},{hilimit, -9.6}}],
(*	      Circle[#[[1]], 0.15]& /@ mc,   *)
	      Dashing[{0.005, 0.01}],
	      Line[{{100, -0.4},{100, -12.6}}]}]
     }
     , ImageSize -> 60*7
     , DisplayFunction -> (Display["cutbycut_2s.eps", #, "EPS"]&)];

lowlimit = 90.5;
hilimit = 102;
textplace = 91;
mc =   Flatten[{pt[ 99.66, 0.55,  -1],
	      	pt[ 99.98, 0.04,  -2],
	      	pt[ 99.19, 0.08,  -3],
	      	pt[ 99.73, Sqrt[0.03^2+0.70^2],  -4],
	      	pt[ 99.88, 0.12,  -5],
	      	pt[ 99.69, 0.40,  -6],
	      	pt[ 98.15, Sqrt[0.65^2+0.70^2], -10],
	      	pt[ 98.48, Sqrt[0.35^2+0.70^2], -11]}, 1];
mc2 =  Flatten[{pt[ 99.94,  -7],
	      	pt[100.00,  -8],
	      	pt[ 99.09,  -9],
	      	pt[ 99.03, -12]}, 1];
data = Flatten[{pt[ 96.85, 0.91, 1.27,  -2.2],
		pt[ 99.50, 1.08, 1.33,  -3.2],
		pt[ 99.07, 0.24, 0.08,  -4.2],
		pt[ 99.52, 0.45, 0.09,  -5.2],
		pt[ 99.42+1.4, 0.85, Sqrt[0.75^2+0.3^2],  -6.2],
		pt[ 99.21, 0.32, 0.11,  -7.2],
		pt[ 99.98, 0.02, 0.00,  -8.2],
		pt[ 99.43, 0.16, 0.02,  -9.2],
		pt[ 94.46, 1.60, 2.37, -11.2],
(*		pt[ 98.94, 0.95, 0.78, -12.2], *)
		pt[ 98.62, 0.36, 0.14, -12.2]}, 1];
Show[{
    MultipleListPlot[data
		     , SymbolShape -> {PlotSymbol[Diamond, 3]}
		     , ErrorBarFunction -> mybarfunc
		     , Prolog -> {AbsoluteThickness[0.01]}
		     , Frame -> True
		     , FrameLabel -> {"Efficiency of Cut", None, None, None}
		     , Axes -> False
		     , PlotRange -> {{lowlimit, hilimit}, {-0.4, -12.6}}
		     , FrameTicks -> {Join[{#, ToString[#], 0.01}& /@ Range[91, 102], {#, "", 0.005}& /@ Range[90.5, 102, 0.25]], None, None, None}
		     , AspectRatio -> 1
		     , DisplayFunction -> Identity
		    ],
    MultipleListPlot[mc
		     , SymbolShape -> {PlotSymbol[Box, 2]}
		     , ErrorBarFunction -> mybarfunc
		     , Prolog -> {AbsoluteThickness[0.01]}
		     , DisplayFunction -> Identity],
    MultipleListPlot[mc2
		     , SymbolShape -> {PlotSymbol[Box, 2]}
		     , Prolog -> {AbsoluteThickness[0.01]}
		     , DisplayFunction -> Identity],
    Graphics[{Text["1. Trigger", {textplace, -1.1}, {-1,0}],
	      Text["2. Closest XY < 5mm", {textplace, -2.1}, {-1,0}],
	      Text["3. Biggest shower < 85%", {textplace, -3.1}, {-1,0}],
	      Text["4. 2nd-biggest track < 85%", {textplace, -4.1}, {-1,0}],
	      Text["5. Event Z < 7.5cm", {textplace, -5.1}, {-1,0}],
	      Text["6. Visible energy > 35%", {textplace, -6.1}, {-1,0}],
	      Text["7. Two or more tracks", {textplace, -7.1}, {-1,0}],
	      Text["8. Level3/Level4", {textplace, -8.1}, {-1,0}],
	      Text["9. CC energy < 85%", {textplace, -9.1}, {-1,0}],
	      Text["1 - 6", {textplace, -10.1}, {-1,0}],
	      Text["2 - 6", {textplace, -11.1}, {-1,0}],
(*	      Text["5 - 6", {textplace, -12.1}, {-1,0}], *)
	      Text["7 - 9", {textplace, -12.1}, {-1,0}],
	      Line[{{lowlimit, -9.6},{hilimit, -9.6}}],
(*	      Circle[#[[1]], 0.15]& /@ mc,   *)
	      Dashing[{0.005, 0.01}],
	      Line[{{100, -0.4},{100, -12.6}}]}]
     }
     , ImageSize -> 60*7
     , DisplayFunction -> (Display["cutbycut_3s.eps", #, "EPS"]&)];

Exit
























lowlimit = 90.5;
hilimit = 102;
textplace = 91;
mc =   Flatten[{pt[ 99.61, 0.55,  -1],
	      	pt[ 99.97, 0.05,  -2],
	      	pt[ 98.70, 0.08,  -3],
	      	pt[ 99.31, 0.03,  -4],
	      	pt[ 99.88, 0.12,  -5],
	      	pt[ 99.67, 0.41,  -6],
	      	pt[ 97.17, 0.67, -10],
	      	pt[ 97.55, 0.38, -11]}, 1];
mc2 =  Flatten[{pt[ 99.94,  -7],
	      	pt[100.00,  -8],
	      	pt[ 99.15,  -9],
	      	pt[ 99.09, -12]}, 1];
data = Flatten[{pt[100.75, 0.71, 0.98,  -2.2],
		pt[ 99.92, 0.81, 1.00,  -3.2],
		pt[ 98.93, 0.18, 0.06,  -4.2],
		pt[ 99.94, 0.34, 0.20,  -5.2],
		pt[ 97.67 + 0.85, 0.59, Sqrt[0.50^2+0.15^2],  -6.2],
		pt[ 97.67, 0., 0.,  -6.2],
		pt[100.14, 0.25, 0.09,  -7.2],
		pt[100.01, 0.01, 0.00,  -8.2],
		pt[ 99.62, 0.11, 0.02,  -9.2],
		pt[ 97.20, 1.26, 1.89, -11.2],
(*		pt[ 97.61, 0.68, 0.55, -12.2], *)
		pt[ 99.77, 0.27, 0.10, -12.2]}, 1];
first = MultipleListPlot[data
			 , SymbolShape -> {PlotSymbol[Diamond, 3]}
			 , ErrorBarFunction -> mybarfunc
			 , Prolog -> {AbsoluteThickness[0.01]}
			 , SymbolStyle -> RGBColor[1,0,0]
			 , Frame -> True
			 , FrameLabel -> {"Efficiency of Cut", None, None, None}
			 , Axes -> False
			 , PlotRange -> {{lowlimit, hilimit}, {-0.4, -12.6}}
			 , FrameTicks -> {Join[{#, ToString[#], 0.01}& /@ Range[91, 102], {#, "", 0.005}& /@ Range[90.5, 102, 0.25]], None, None, None}
			 , AspectRatio -> 1
			 , DisplayFunction -> Identity
			];
second = MultipleListPlot[mc
			  , SymbolShape -> {PlotSymbol[Box, 2]}
			  , ErrorBarFunction -> mybarfunc
			  , Prolog -> {AbsoluteThickness[0.01]}
			  , SymbolStyle -> RGBColor[0,0,1]
			  , DisplayFunction -> Identity];
third = MultipleListPlot[mc2
			 , SymbolShape -> {PlotSymbol[Box, 2]}
			 , Prolog -> {AbsoluteThickness[0.01]}
			 , SymbolStyle -> RGBColor[0,0,1]
		         , DisplayFunction -> Identity];
Show[{
    Graphics[Prepend[first[[1]], RGBColor[1,0,0]], first[[2]]],
    Graphics[Prepend[second[[1]], RGBColor[0,0,1]], second[[2]]],
    Graphics[Prepend[third[[1]], RGBColor[0,0,1]], third[[2]]],
    Graphics[{RGBColor[0,0,0],
	      Text["1. Trigger", {textplace, -1.1}, {-1,0}],
	      Text["2. Closest XY < 5mm", {textplace, -2.1}, {-1,0}],
	      Text["3. Biggest shower < 85%", {textplace, -3.1}, {-1,0}],
	      Text["4. 2nd-biggest track < 85%", {textplace, -4.1}, {-1,0}],
	      Text["5. Event Z < 7.5cm", {textplace, -5.1}, {-1,0}],
	      Text["6. Visible energy > 35%", {textplace, -6.1}, {-1,0}],
	      Text["7. Two or more tracks", {textplace, -7.1}, {-1,0}],
	      Text["8. Level3/Level4", {textplace, -8.1}, {-1,0}],
	      Text["9. CC energy < 85%", {textplace, -9.1}, {-1,0}],
	      Text["1 - 6", {textplace, -10.1}, {-1,0}],
	      Text["2 - 6", {textplace, -11.1}, {-1,0}],
(*	      Text["5 - 6", {textplace, -12.1}, {-1,0}], *)
	      Text["7 - 9", {textplace, -12.1}, {-1,0}],
	      Line[{{lowlimit, -6.6},{hilimit, -6.6}}],
	      Line[{{lowlimit, -9.6},{hilimit, -9.6}}],
(*	      Circle[#[[1]], 0.15]& /@ mc,   *)
	      Dashing[{0.005, 0.01}],
	      Line[{{100, -0.4},{100, -12.6}}]}]
     }
     , ImageSize -> 60*7
     , DisplayFunction -> (Display["cutbycut_2s_redux.eps", #, "EPS"]&)];

