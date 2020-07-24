$DisplayFunction =
    Module[{System`Private`file = OpenTemporary[]}, 
	   Display[{$Display, System`Private`file}, #1]; System`Private`file = 
	   Close[System`Private`file]; System`Private`$DisplayLinkCommands[
	       System`Private`file, $DisplayTitle]; #1] &;

<< Graphics`MultipleListPlot`

theoy1s = Interpolation[ ReadList[ "scanonlyY1s.theo", {Number, Number} ] ];
theoy3s = Interpolation[ ReadList[ "scanonlyY3s.theo", {Number, Number} ] ];
theofeb20 = Interpolation[ ReadList[ "scanonly_feb20.theo", {Number, Number} ] ];
theodec25 = Interpolation[ ReadList[ "scanonly_dec25.theo", {Number, Number} ] ];

Plot[theoy1s[x], {x, 9440, 9480}];
Plot[theoy3s[x], {x, 10340, 10390}];
Plot[theodec25[x], {x, 10340, 10390}];
Plot[theofeb20[x], {x, 9440, 9480}];

conty1s = ReadList[ "realY1s.cont", {Number, Number, Number} ];
scany1s = ReadList[ "realY1s.scan", {Number, Number, Number} ];
peaky1s = ReadList[ "realY1s.peak", {Number, Number, Number} ];
highy1s = ReadList[ "realY1s.high", {Number, Number, Number} ];

conty3s = ReadList[ "realY3s.cont", {Number, Number, Number} ];
scany3s = ReadList[ "realY3s.scan", {Number, Number, Number} ];
peaky3s = ReadList[ "realY3s.peak", {Number, Number, Number} ];
highy3s = ReadList[ "realY3s.high", {Number, Number, Number} ];

contfeb20 = { #[[1]]*1000, #[[2]], #[[3]] }& /@ ReadList[ "feb20.cont", {Number, Number, Number} ];
scanfeb20 = { #[[1]]*1000, #[[2]], #[[3]] }& /@ ReadList[ "feb20.scan", {Number, Number, Number} ];
peakfeb20 = { #[[1]]*1000, #[[2]], #[[3]] }& /@ ReadList[ "feb20.peak", {Number, Number, Number} ];
highfeb20 = { #[[1]]*1000, #[[2]], #[[3]] }& /@ ReadList[ "feb20.high", {Number, Number, Number} ];

contdec25 = { #[[1]]*1000, #[[2]], #[[3]] }& /@ ReadList[ "dec25.cont", {Number, Number, Number} ];
scandec25 = { #[[1]]*1000, #[[2]], #[[3]] }& /@ ReadList[ "dec25.scan", {Number, Number, Number} ];
peakdec25 = { #[[1]]*1000, #[[2]], #[[3]] }& /@ ReadList[ "dec25.peak", {Number, Number, Number} ];
highdec25 = { #[[1]]*1000, #[[2]], #[[3]] }& /@ ReadList[ "dec25.high", {Number, Number, Number} ];

Residualize[ data_, func_ ] := { { #[[1]], #[[2]]-func[#[[1]]] }, ErrorBar[ #[[3]] ] }& /@ data;
AbsResidualize[ data_, func_ ] := { #[[1]], (#[[2]]-func[#[[1]]]) / #[[3]] }& /@ data;

MultipleListPlot[ Residualize[ Join[peaky1s], theoy3s ] ];
MultipleListPlot[ AbsResidualize[ Join[peaky1s], theoy3s ] ];

MultipleListPlot[ Residualize[ Join[peaky3s], theoy3s ] ];
MultipleListPlot[ AbsResidualize[ Join[peaky3s], theoy3s ] ];

MultipleListPlot[ Residualize[ Join[peakfeb20], theofeb20 ] ];
MultipleListPlot[ AbsResidualize[ Join[peakfeb20], theofeb20 ] ];

MultipleListPlot[ Residualize[ Join[peakdec25], theodec25 ] ];
MultipleListPlot[ AbsResidualize[ Join[peakdec25], theodec25 ] ];

Residual[ f:Func, energy_, hxc_, uncert_ ] :=
    { EvalFunc[ f, energy ] - hxc, Sqrt[ uncert^2 + EvalUncertFunc[ f, energy ] ] };
Residualizer[ f:Func, run_, energy_, hxc_, uncert_ ] :=
    {
	{ run, EvalFunc[ f, energy ] - hxc }, ErrorBar[uncert]
    };
AbsResidualizer[ f:Func, run_, energy_, hxc_, uncert_ ] :=
    {
	{ run, ( EvalFunc[ f, energy ] - hxc ) / uncert }
    };

$DisplayFunction = Display["feb20plot.eps", #, "EPS"]&;
Show[ GraphicsArray[ {
    {
	MultipleListPlot[ Residualize[ peakfeb20, theofeb20 ]
			  , PlotRange -> {Automatic,{-1,1}}
			  , Axes -> {True,False}
			  , Frame -> True
			  , FrameLabel -> {"Energy", "nb from Fit", None, None}
			  , AspectRatio -> 0.6
			  , DisplayFunction -> Identity
			]
    },
    {
	MultipleListPlot[ AbsResidualize[ peakfeb20, theofeb20 ]
			  , PlotRange -> {Automatic,{-5,5}}
			  , Axes -> {True,False}
			  , Frame -> True
			  , FrameLabel -> {"Energy", "Sigmas from Fit", None, None}
			  , AspectRatio -> 0.6
			  , DisplayFunction -> Identity
			]
    } }
		     , Frame -> True
		     , FrameLabel -> { None, None, "Residuals of Feb 20 Y(1s) peak data to scan-only fit", None }
		   ]
      , ImageSize -> 72 * 7
      , DisplayFunction -> $DisplayFunction
    ];

