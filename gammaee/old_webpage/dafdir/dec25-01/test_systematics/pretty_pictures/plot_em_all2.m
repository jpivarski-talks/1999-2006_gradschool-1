<< Graphics`Graphics`;
<< Graphics`MultipleListPlot`;

SetDirectory["~/public_html/private/my_gammaee/fits/dec25-01/test_systematics/pretty_pictures/"];
data = ReadList["data.dat", {Real,Real,Real} ];
theo = ReadList["curve.dat", {Real,Real}];
tau = ReadList["tau.dat", {Real, Real}];
twophoton = ReadList["twophoton.dat", {Real,Real} ];
y1stail = ReadList["y1stail.dat", {Real,Real} ];
y2stail = ReadList["y2stail.dat", {Real,Real} ];

normal = ReadList["plot_normal.dat", {Real, Real}];
noqqint = ReadList["plot_noqqint.dat", {Real, Real}];
notauint = ReadList["plot_notauint.dat", {Real, Real}];

notail = ReadList["plot_k0.dat", {Real, Real}];

(* Show[
    ListPlot[{#[[1]],Log[10,#[[2]]]}& /@ theo, PlotJoined -> True, DisplayFunction -> Identity]
    , MultipleListPlot[{#[[1]],Log[10,#[[2]]]}& /@ data, PlotJoined -> False, DisplayFunction -> Identity]
    , Graphics[Line[{{#[[1]],Log[10,#[[2]]-#[[3]]]},{#[[1]],Log[10,#[[2]]+#[[3]]]}}]& /@ data]
    , Graphics[Line[{{#[[1]]-.5,Log[10,#[[2]]-#[[3]]]},{#[[1]]+.5,Log[10,#[[2]]-#[[3]]]}}]& /@ data]
    , Graphics[Line[{{#[[1]]-.5,Log[10,#[[2]]+#[[3]]]},{#[[1]]+.5,Log[10,#[[2]]+#[[3]]]}}]& /@ data]
    , Graphics[Text["Data", {10337,Log[10,5.5]}]]
    , ListPlot[{#[[1]],Log[10,#[[2]]]}& /@ tau, PlotJoined -> True, DisplayFunction -> Identity]
    , Graphics[Text["U(3S) to Tau Pair (0.46%)", {10390,Log[10,0.002]}]]
    , ListPlot[{#[[1]],Log[10,0.22725*#[[2]]]}& /@ twophoton, PlotJoined -> True, DisplayFunction -> Identity]
    , Graphics[Text["TwoPhoton (about 5%)", {10360,1.05*Log[10,0.22725*0.7]}]]
    , ListPlot[{#[[1]],Log[10,#[[2]]]}& /@ y1stail, PlotJoined -> True, DisplayFunction -> Identity]
    , ListPlot[{#[[1]],Log[10,#[[2]]]}& /@ y2stail, PlotJoined -> True, DisplayFunction -> Identity]
    , Graphics[Text["U(1S and 2S) ISR Tails (0.55% + 0.66%)", {10342,Log[10,0.035]}]]
    , Plot[Log[10,0.003*4.00559], {x,10322, 10405.928}, DisplayFunction -> Identity]
    , Graphics[Text["J/psi and psi' Tails (0.3%)", {10337,Log[10,1.5*0.010]}]]
    , Plot[Log[10,0.85*4.00559*10322^2/x^2], {x,10322, 10405.928}, DisplayFunction -> Identity]
    , Graphics[Text["Continuum Hadrons (about 85%)", {10337,0.95*Log[10,2.7]}]]
    , Plot[Log[10,0.01*(2*5.29*1000)^2/x^2], {x,10322, 10405.928}, DisplayFunction -> Identity, PlotStyle -> RGBColor[1,0,0]]
    , Graphics[Text["Bhabha Events (about 0.25%)", {10390,Log[10,0.01]}]]
    , Plot[Log[10,0.06*4.00559*10322^2/x^2], {x,10322, 10405.928}, DisplayFunction -> Identity]
    , Graphics[Text["Continuum Tau Pair (6%)", {10337,Log[10,0.30]}]]
    , Plot[Log[10,0.018*4.00559*(1+0.05*Sin[x])], {x,10322, 10405.928}, DisplayFunction -> Identity]
    , Graphics[Text["Beamgas (1.8%)", {10337,0.95*Log[10,0.09]}]]
    , Plot[Log[10,0.002*4.00559*(1+0.05*Sin[x])], {x,10322, 10405.928}, DisplayFunction -> Identity]
    , Graphics[Text["Cosmic Rays (0.2%)", {10337,1.05*Log[10,0.006]}]]
    , Frame -> True
    , FrameLabel -> {"Energy in MeV", "Hadronic Cross-Section in nb", "Backgrounds to U(3S)", None}
    , FrameTicks -> {Automatic,
		     Join[
			 {Log[10, #], "", {0.005, 0}}& /@ Range[0.001, 0.010, 0.001],
			 {Log[10, #], "", {0.005, 0}}& /@ Range[0.01, 0.10, 0.01],
			 {Log[10, #], "", {0.005, 0}}& /@ Range[0.1, 1.0, 0.1],
			 {Log[10, #], "", {0.005, 0}}& /@ Range[1., 10., 1.],
			 {Log[10, #], "", {0.005, 0}}& /@ Range[10., 100., 10.],
			 Table[{i,ToString[N[10^i]],{0.01,0}},{i,-4,2}]
			 ]
		     , None, None}
    , Axes -> False
    , AspectRatio -> 10./8.5
    , PlotRange -> {{10322, 10405.928}, {Log[10, 0.001], Log[10, 20]}}
    , ImageSize -> 8.5*72
    , DisplayFunction -> (Display["plot_em_all2.eps",#,"EPS"]&) *)
    ];
*)

colorHadrons =   RGBColor[0,0.69,0];
colorTau =       RGBColor[0.58,0,1];
colorTwoPhoton = RGBColor[0.635,0.635,0.447];
colorBeamgas =   RGBColor[1,0,0];
colorUTails = 	 RGBColor[0,0.596,1];
colorJTails = 	 RGBColor[0,0.631,0.729];
colorBhabha = 	 RGBColor[1,0.486,0];
colorCosmic = 	 RGBColor[0.796,0.367,0.357];
colorResTau = 	 RGBColor[1,0,1];
colorContInt =   RGBColor[0,0,1];
colorTauInt =    RGBColor[0.7176,0,1];
Show[
    ListPlot[{#[[1]],Log[10,#[[2]]]}& /@ theo, PlotJoined -> True, DisplayFunction -> Identity]
    , MultipleListPlot[{#[[1]],Log[10,#[[2]]]}& /@ data, PlotJoined -> False, DisplayFunction -> Identity]
    , Graphics[Line[{{#[[1]],Log[10,#[[2]]-#[[3]]]},{#[[1]],Log[10,#[[2]]+#[[3]]]}}]& /@ data]
    , Graphics[Line[{{#[[1]]-.5,Log[10,#[[2]]-#[[3]]]},{#[[1]]+.5,Log[10,#[[2]]-#[[3]]]}}]& /@ data]
    , Graphics[Line[{{#[[1]]-.5,Log[10,#[[2]]+#[[3]]]},{#[[1]]+.5,Log[10,#[[2]]+#[[3]]]}}]& /@ data]
    , ListPlot[Table[{tau[[i,1]], Log[10, Abs[Drop[notauint, 1][[i,2]] - Drop[normal, 1][[i,2]] + tau[[i,2]]]]}, {i, 1, Length[tau]}], PlotJoined -> True, DisplayFunction -> Identity, PlotStyle -> colorResTau]
    , ListPlot[{#[[1]],Log[10,0.22725*#[[2]]]}& /@ twophoton, PlotJoined -> True, DisplayFunction -> Identity, PlotStyle -> colorTwoPhoton]
    , ListPlot[{#[[1]],Log[10,#[[2]]]}& /@ y1stail, PlotJoined -> True, DisplayFunction -> Identity, PlotStyle -> colorUTails]
    , ListPlot[{#[[1]],Log[10,#[[2]]]}& /@ y2stail, PlotJoined -> True, DisplayFunction -> Identity, PlotStyle -> colorUTails]
    , Plot[Log[10,0.003*4.00559], {x,10322, 10405.928}, DisplayFunction -> Identity, PlotStyle -> colorJTails]
    , Plot[Log[10,0.85*4.00559*10322^2/x^2], {x,10322, 10405.928}, DisplayFunction -> Identity, PlotStyle -> colorHadrons]
    , Plot[Log[10,0.01*(2*5.29*1000)^2/x^2], {x,10322, 10405.928}, DisplayFunction -> Identity, PlotStyle -> colorBhabha]
    , Plot[Log[10,0.06*4.00559*10322^2/x^2], {x,10322, 10405.928}, DisplayFunction -> Identity, PlotStyle -> colorTau]
    , Plot[Log[10,0.018*4.00559*(1+0.05*Sin[x])], {x,10322, 10405.928}, DisplayFunction -> Identity, PlotStyle -> colorBeamgas]
    , Plot[Log[10,0.002*4.00559*(1+0.05*Sin[x])], {x,10322, 10405.928}, DisplayFunction -> Identity, PlotStyle -> colorCosmic]
    , ListPlot[Table[{normal[[i,1]], Log[10, Abs[noqqint[[i,2]] - normal[[i,2]]]]}, {i, 1, Length[normal]}], PlotJoined -> True, DisplayFunction -> Identity, PlotStyle -> colorContInt]
    , ListPlot[Table[{normal[[i,1]], Log[10, Abs[notail[[i,2]] - normal[[i,2]]]]}, {i, 1, Length[normal]}], PlotJoined -> True, DisplayFunction -> Identity(*, PlotStyle -> Dashing[{0.01,0.02}]*)]
    , Frame -> True
    , FrameTicks -> {Automatic,
		     Join[
			 {Log[10, #], "", {0.005, 0}}& /@ Range[0.001, 0.010, 0.001],
			 {Log[10, #], "", {0.005, 0}}& /@ Range[0.01, 0.10, 0.01],
			 {Log[10, #], "", {0.005, 0}}& /@ Range[0.1, 1.0, 0.1],
			 {Log[10, #], "", {0.005, 0}}& /@ Range[1., 10., 1.],
			 {Log[10, #], "", {0.005, 0}}& /@ Range[10., 100., 10.],
			 Table[{i,ToString[N[10^i]],{0.01,0}},{i,-4,2}]
			 ]
		     , None, None}
    , Axes -> False
    , AspectRatio -> 7.5/7.
    , PlotRange -> {{10322, 10405.928}, {Log[10, 0.0005], Log[10, 20]}}
    , ImageSize -> 6*72
(*     , DisplayFunction -> (Display["plot_em_all2_realtau.eps",#,"EPS"]&) *)
    , DisplayFunction -> $DisplayFunction
    ];


