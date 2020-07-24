Off[General::spell1];
<< Statistics`ContinuousDistributions`;
<< Graphics`MultipleListPlot`;
<< Graphics`Graphics`;
<< Statistics`DescriptiveStatistics`;

FParam = ( _Symbol | _Integer | _Real );
FParams = { FParam .. };
FNames = { _Symbol .. };
FLabels = { _String .. };
FMatrix = { { FParam .. } .. };
JustFunc = _Symbol;
Func = { JustFunc, FParams, FNames, FLabels, FMatrix };
GetFunc[ f:Func ] := f[[1]];
GetParams[ f:Func ] := f[[2]];
GetNames[ f:Func ] := f[[3]];
GetLabels[ f:Func ] := f[[4]];
GetErrorMatrix[ f:Func ] := f[[5]];
EvalFunc[ f:Func, x_ ] := ( GetFunc[f] @@ Prepend[ GetParams[f], x ] ) // Chop;
AbstractFunc[ f:Func, x_ ] := GetFunc[f] @@ Prepend[ GetNames[f], x ];
(* DerivFunc[ f:Func, x_ ] :=
    Module[ {xi}, D[ EvalFunc[ f, xi ], xi ] /. xi -> x ] // Chop; *)
CheapMax[ f:Func ] := EvalFunc[ f, GetParams[f][[2]] ];
GetVD[ f:Func, x_ ] := Chop[ { D[ AbstractFunc[ f, x ], # ] }& /@ GetNames[ f ] /.
			     Table[ GetNames[ f ][[i]] -> GetParams[ f ][[i]],
				    {i, 1, Length[GetParams[ f ]]} ] ]
EvalUncertFunc[ f:Func, x_ ] := Sqrt[ Module[ {vd = GetVD[ f, x ] },
					      Transpose[vd] . GetErrorMatrix[f] . vd ][[1,1]] ]

DataPoint = { ( _Integer | _Real ),
	      ( _Integer | _Real ),
	      ( _Integer | _Real ) };
Data = { DataPoint .. };
X[ dp:DataPoint ] := dp[[1]];
Y[ dp:DataPoint ] := dp[[2]];
ErrY[ dp:DataPoint ] := dp[[3]];
PlotDataPoints[ data:Data ] :=
    { { X[#], Y[#] }, ErrorBar[ ErrY[#] ] }& /@ data;
ToCOM[ data:Data ] := { 2 #[[1]], #[[2]], #[[3]] }& /@ data;

PlotFuncData[ f:Func, data:Data, title_String, atts:{ _Rule .. } ] :=
    Show @@ Join[ { { Plot[ EvalFunc[ f, x ],
			    {x, Min @@ ( X /@ data ) - 0.005, Max @@ ( X /@ data ) + 0.005 },
			    PlotStyle -> { RGBColor[1,0,0] },
			    DisplayFunction -> Identity ],
		      MultipleListPlot[ PlotDataPoints[ data ],
					DisplayFunction -> Identity ]
		    },
		    PlotRange -> { { Min @@ ( X /@ data ) - 0.005,
				     Max @@ ( X /@ data ) + 0.005 },
				   { 0.,
				     Max @@ Append[ Y /@ data,
						    CheapMax[ f ] ] + 1. } },
		    Axes -> False, Frame -> True,
		    FrameLabel -> {"Energy in GeV", "Cross-section in nb", title, None},
		    DisplayFunction -> $DisplayFunction
		  }, atts ];
PlotFuncData[ f:Func, data:Data, title_String ] := PlotFuncData[ f, data, title, {} ];
PlotFuncData[ f:Func, data:Data ] := PlotFuncData[ f, data, "" ];

PlotDiffFuncData[ f:Func, data:Data, title_String, atts:{ _Rule .. } ] :=
    Show @@ Join[
	{ { Plot[ { -1, 1 }, { x, Min @@ ( X /@ data ) - 0.005, Max @@ ( X /@ data ) + 0.005 },
		  PlotStyle -> { { RGBColor[0.7,0.7,0.7], Dashing[{0.01,0.01}] } },
		  DisplayFunction -> Identity
		],
	    ListPlot[ { X[#], ( Y[#] - EvalFunc[ f, X[#] ] ) / ErrY[#] }& /@ data,
		      DisplayFunction -> Identity
		    ] },
	  Axes -> False, Frame -> True,
	  FrameLabel -> {"Energy in GeV", "Sigmas from Best Fit", title, None },
	  PlotRange -> { { Min @@ ( X /@ data ) - 0.005, Max @@ ( X /@ data ) + 0.005 },
			 { -3.0000001, 3. } },
	  DisplayFunction -> $DisplayFunction
	}, atts
		];
PlotDiffFuncData[ f:Func, data:Data, title_String ] := PlotDiffFuncData[ f, data, title, {} ];
PlotDiffFuncData[ f:Func, data:Data ] := PlotDiffFuncData[ f, data, "" ];

Chi2ToFunc[ f:Func, data:Data ] :=
    Plus @@ ( ( ( AbstractFunc[ f, X[#] ] - Y[#] ) / ErrY[#] )^2 & /@ data );
ErrorMatrix[ f:Func, data:Data ] := 
    ( Table[ D[ D[ Chi2ToFunc[ f, data ],
		   GetNames[f][[i]] ],
		GetNames[f][[j]] ],
	     {i,1,Length[GetNames[f]]}, {j,1,Length[GetNames[f]]} ]
      /. Table[ GetNames[f][[k]] -> GetParams[f][[k]], {k,1,Length[GetNames[f]]} ]
    ) // Chop // Inverse;
FitToFunc[ f:Func, data:Data ] :=
    Module[ {chi2,replacements,tmpfunc},
	    {chi2,replacements} = FindMinimum @@
	    Prepend[ Table[ { GetNames[f][[i]], GetParams[f][[i]] },
			    {i,1,Length[GetNames[f]]}
			  ],
		     Chi2ToFunc[ f, data ]
		   ];
	    tmpfunc = { GetFunc[f],
			GetNames[f] /. replacements,
			GetNames[f],
			GetLabels[f],
			GetErrorMatrix[f] };
	    { chi2, Length[data] - Length[ GetNames[tmpfunc] ],
	      { GetFunc[tmpfunc],
		GetParams[tmpfunc],
		GetNames[tmpfunc],
		GetLabels[tmpfunc],
		ErrorMatrix[ tmpfunc, data ] } }
	  ];

HTMLFitOutput[ { chi2:FParam, dof_Integer, f:Func }, funcName_String ] :=
    "<table><tr><td>Fit Function</td><td>" <>
    funcName <> "</td><td>=</td>\n    " <>
    Module[ {str,start},
	    str = ( ( ToString[ GetFunc[f] ] <> "// Definition" )
		    // ToExpression // InputForm // ToString );
	    start = StringPosition[ str, ":= " ][[1]][[2]];
	    StringDrop[ str, start ]
	  ] <> "</td></tr></table>\n" <>
    "<table>" <>
    StringJoin[ Table[ "  <tr><td>" <> ToString[ GetNames[f][[i]] ] <>
		       "</td><td>=</td><td>" <>
		       ToString[ GetParams[f][[i]] // CForm ]
		       <> "</td><td>+/-</td><td>" <>
		       ToString[ Sqrt[ GetErrorMatrix[f][[i,i]] ] // CForm ] <>
		       "</td><td>" <>
		       GetLabels[f][[i]] <> "</td></tr>\n",
		       {i,1,Length[GetNames[f]]}
		       ]
		] <> "</table>\n" <>
    "<table><tr><td>Chi^2 / ndf</td><td>=</td><td>\n" <>
    ToString[ chi2 // CForm ] <> " / " <> ToString[ dof ] <> "</td><td>=</td><td>" <>
    ToString[ chi2 / dof // CForm ] <> "</td></tr></table>\n" <>
    "<table>\n" <> StringJoin @@ Table[
	"  <tr>\n" <> StringJoin @@ Table[
	"    <td align=center>" <>
	ToString[ GetErrorMatrix[f][[i,j]] // CForm ] <>
	"</td>\n", {j,1,Length[GetErrorMatrix[f]]}
					 ], {i,1,Length[GetErrorMatrix[f]]}
				      ]	<> "</table>\n";
HTMLFitOutput[ { chi2:FParam, dof_Integer, f:Func } ] :=
    HTMLFitOutput[ { chi2, dof, f }, "" ];

(* ********************************************************************************* *)
(* here's an example of how you specify data and functions:                          *)
(*                                                                                   *)
(* someData = { {5.19045, 3.4, 0.06},                                                *)
(* 	     {5.17431, 3.59, 0.06},                                                  *)
(* 	     {5.18236, 5.03, 0.07},                                                  *)
(* 	     {5.1724, 3.23, 0.06},                                                   *)
(* 	     {5.18535, 3.68, 0.06},                                                  *)
(* 	     {5.18846, 3.56, 0.06},                                                  *)
(* 	     {5.17743, 5.92, 0.09},                                                  *)
(* 	     {5.19046, 3.4, 0.06},                                                   *)
(* 	     {5.17451, 3.74, 0.17},                                                  *)
(* 	     {5.17449, 3.77, 0.07},                                                  *)
(* 	     {5.1824, 5.04, 0.07},                                                   *)
(* 	     {5.17246, 3.34, 0.06},                                                  *)
(* 	     {5.18554, 3.75, 0.06},                                                  *)
(* 	     {5.18845, 3.56, 0.07},                                                  *)
(* 	     {5.17739, 6.14, 0.1},                                                   *)
(* 	     {5.19046, 3.49, 0.07},                                                  *)
(* 	     {5.17432, 3.57, 0.06},                                                  *)
(* 	     {5.18237, 5.04, 0.08} };                                                *)
(* GaussJustFunc[ x:FParam, area:FParam, mean:FParam, sigma:FParam, back:FParam ] := *)
(*     area * Exp[ -( (x - mean) / sigma )^2 / 2 ] / Sqrt[ 2 * Pi ] / sigma          *)
(*     + back;                                                                       *)
(* GaussParams = { 0.022, 5.1794, 0.0023, 3.3 };                                     *)
(* GaussNames = { area, mean, sigma, back };                                         *)
(* GaussLabels = { "GeV nb", "GeV", "GeV", "nb" };                                   *)
(* GaussMatrix = IdentityMatrix[ 4 ];                                                *)
(* Gauss = { GaussJustFunc, GaussParams, GaussNames, GaussLabels, GaussMatrix };     *)
(*                                                                                   *)
(* ********************************************************************************* *)

background[ x:FParam, back:FParam ] :=
    back * (9.4326)^2 / x^2 (* + *)
    (* need to determine Y(1s) contribution *)
    (* If[x > 9.74178, 0 / (x - 9.46), 0] + *)
    (* need to determine Y(2s) contribution *)
    (* If[x > 10.18923, 0 / (x - 10.02326), 0]; *)
    (* This compromise may be off by 0.02 nb point-by-point *)
(*    0.5 * ( If[ x > 9.74178, 0.49953 / 1.1495113397820034 / (x - 9.46), 0 ] +
	    If[ x > 10.18923, 0.49953 / 3.260782320205553 / (x - 10.02326), 0 ] ); *)

JSJustFunc[ x:FParam, area:FParam, mean:FParam, sigma:FParam, back:FParam ] :=
    (* x GeV, area MeV nb, mean GeV, sigma MeV, back nb *)
    Module[ {xMeV,areaGeV,sigmaGeV,t,z,F},
	    xMeV = x * 1000;
	    areaGeV = area / 1000;
	    sigmaGeV = sigma / 1000;
	    t = 2 * ( 1 / 137.0359997650 / Pi ) * ( Log[
		xMeV^2 / 0.51099890221^2 - 1 ] );
	    z = ( x - mean ) / sigmaGeV;
	    F = ( Gamma[ 1 + t ] * Exp[ -z^2 / 2 ] / Sqrt[ 2 Pi ] *
		  ( 0.31 - 0.73 * z / Sqrt[ 1 + ( z / ( 1 + 1.37 t ) )^2 ]
		    + z^2 )^( - t / 2 ) +
		  If[ z > 0, 1, 0 ] * ( t * z^t * ( z^2.18 / ( 1 + z^3.18 ) ) *
					( 1 + ( 1 - t ) * ( 2 - t ) / 2 /
					  ( 1.5 * t + 2.44 + ( z - 46 /
							       ( z^2 + 21 ) )^2 ) )
				      )
		);
	    areaGeV * ( 2 * sigmaGeV / mean )^t * F / sigmaGeV + background[ x, back ]
	  ];
JSParams = { 82.78, 10.3583, 4.648, 3.236 };
JSNames = { area, mean, sigma, back };
JSLabels = { "MeV nb", "GeV", "MeV", "nb" };
JSErrorMatrix = IdentityMatrix[4];
JacksonSharre = { JSJustFunc, JSParams, JSNames, JSLabels, JSErrorMatrix };

KFJustFunc[ x:FParam, area:FParam, mean:FParam, sigma:FParam, back:FParam ] :=
    (* x GeV, area MeV nb, mean GeV, sigma MeV, back nb *)
    Module[ {xMeV,areaGeV,sigmaGeV,t,z,F},
	    xMeV = x * 1000;
	    areaGeV = area / 1000;
	    sigmaGeV = sigma / 1000;
	    t = 2 * ( 1 / 137.0359997650 / Pi ) * ( Log[
		xMeV^2 / 0.51099890221^2 - 1 ] );
	    z = ( x - mean ) / sigmaGeV;
	    F = ( Gamma[ 1 + t ] * Exp[ -z^2 / 2 ] / Sqrt[ 2 Pi ] *
		  ( 0.31 - 0.73 * z / Sqrt[ 1 + ( z / ( 1 + 1.37 t ) )^2 ]
		    + z^2 )^( - t / 2 ) +
		  (1.052) * (* yes, this is the only difference *)
		  If[ z > 0, 1, 0 ] * ( t * z^t * ( z^2.18 / ( 1 + z^3.18 ) ) *
					( 1 + ( 1 - t ) * ( 2 - t ) / 2 /
					  ( 1.5 * t + 2.44 + ( z - 46 /
							       ( z^2 + 21 ) )^2 ) )
				      )
		);
	    areaGeV * ( 2 * sigmaGeV / mean )^t * F / sigmaGeV + background[ x, back ]
	  ];
KFParams = { 82.78, 10.3583, 4.648, 3.236 };
KFNames = { area, mean, sigma, back };
KFLabels = { "MeV nb", "GeV", "MeV", "nb" };
KFErrorMatrix = IdentityMatrix[4];
KuraevFadin = { KFJustFunc, KFParams, KFNames, KFLabels, KFErrorMatrix };

KFParamsY1s = { 2 * 139.3, 2 * 4.73, 2 * 1.908, 2.931 };
KuraevFadinY1s = { KFJustFunc, KFParamsY1s, KFNames, KFLabels, KFErrorMatrix };

KFParams = { 82.63698977976541, 10.358011369294552, 4.664889567682248, 3.292945963515927 };
KuraevFadin = { KFJustFunc, KFParams, KFNames, KFLabels, KFErrorMatrix };

KFParamsY2s = { 109.111, 2 * 5.01163, 2 * 2.16595, 2.931 };
KuraevFadinY2s = { KFJustFunc, KFParamsY2s, KFNames, KFLabels, KFErrorMatrix };
