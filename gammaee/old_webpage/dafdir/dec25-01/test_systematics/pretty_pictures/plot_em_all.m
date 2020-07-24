<< Graphics`Graphics`

<< Graphics`MultipleListPlot`

SetDirectory["~/public_html/private/my_gammaee/fits/dec25-01/test_systematics/pretty_pictures/"]

Out[2]= /A/lns101/nfs/homes/cleo/mccann/public_html/private/my_gammaee/fits/d\
 
>    ec25-01/test_systematics/pretty_pictures

data = ReadList["data.dat", {Real,Real,Real} ];

theo = ReadList["curve.dat", {Real,Real}];

tau = ReadList["tau.dat", {Real, Real}];

twophoton = ReadList["twophoton.dat", {Real,Real} ];

y1stail = ReadList["y1stail.dat", {Real,Real} ];

y2stail = ReadList["y2stail.dat", {Real,Real} ];

Show[
    ListPlot[{#[[1]],Log[10,#[[2]]]}& /@ theo, PlotJoined -> True, DisplayFunction -> Identity]
    , MultipleListPlot[{#[[1]],Log[10,#[[2]]]}& /@ data, PlotJoined -> False, DisplayFunction -> Identity]
    , Graphics[Line[{{#[[1]],Log[10,#[[2]]-#[[3]]]},{#[[1]],Log[10,#[[2]]+#[[3]]]}}]& /@ data]
    , Graphics[Line[{{#[[1]]-.5,Log[10,#[[2]]-#[[3]]]},{#[[1]]+.5,Log[10,#[[2]]-#[[3]]]}}]& /@ data]
    , Graphics[Line[{{#[[1]]-.5,Log[10,#[[2]]+#[[3]]]},{#[[1]]+.5,Log[10,#[[2]]+#[[3]]]}}]& /@ data]
    , Graphics[Text["Data", {10337,Log[10,5.5]}]]
    , ListPlot[{#[[1]],Log[10,#[[2]]]}& /@ tau, PlotJoined -> True, DisplayFunction -> Identity]
    , Graphics[Text["U(3S) to Tau Pair (0.46%)", {10390,Log[10,0.002]}]]
    , ListPlot[{#[[1]],Log[10,#[[2]]]}& /@ twophoton, PlotJoined -> True, DisplayFunction -> Identity]
    , Graphics[Text["TwoPhoton (0.026%)", {10337,Log[10,1.1]}]]
    , ListPlot[{#[[1]],Log[10,#[[2]]]}& /@ y1stail, PlotJoined -> True, DisplayFunction -> Identity]
    , Graphics[Text["U(1S) ISR Tail (0.0026%)", {10337,Log[10,0.015]}]]
    , ListPlot[{#[[1]],Log[10,#[[2]]]}& /@ y2stail, PlotJoined -> True, DisplayFunction -> Identity]
    , Graphics[Text["U(2S) ISR Tail (0.049%)", {10337,Log[10,0.035]}]]
    , Plot[Log[10,0.82*4.00559*10322^2/x^2], {x,10322, 10405.928}, DisplayFunction -> Identity]
    , Graphics[Text["Continuum Hadrons (zero bias)", {10337,Log[10,2.7]}]]
    , Plot[Log[10,0.06*4.00559*10322^2/x^2], {x,10322, 10405.928}, DisplayFunction -> Identity]
    , Graphics[Text["e+e- to Tau Pair (zero bias)", {10337,Log[10,0.30]}]]
    , Plot[Log[10,0.016*4.00559], {x,10322, 10405.928}, DisplayFunction -> Identity]
    , Graphics[Text["e- Beamgas (0.24%)", {10337,Log[10,0.075]}]]
    , Plot[Log[10,0.028*4.00559], {x,10322, 10405.928}, DisplayFunction -> Identity]
    , Graphics[Text["e+ Beamgas (0.42%)", {10337,Log[10,0.13]}]]
    , Plot[Log[10,0.04*4.00559], {x,10322, 10405.928}, PlotStyle -> Dashing[{0.01,0.02}], DisplayFunction -> Identity]
    , Graphics[Text["Cosmic Rays (< 0.04%)", {10380,Log[10,0.19]}]]
    , Frame -> True
    , FrameLabel -> {"Energy in MeV", "Hadronic Cross-Section in nb", "Contribution of Various Effects to Area of the Peak", None}
    , FrameTicks -> {Automatic, Table[{i,ToString[N[10^i]],{0.01,0}},{i,-4,2}], None, None}
    , Axes -> False
    , AspectRatio -> 1
    , PlotRange -> {{10322, 10405.928},{-3.1,2}}
    , ImageSize -> 8*72
    , DisplayFunction -> (Display["plot_em_all.eps",#,"EPS"]&)
    ];

curve = Interpolation[theo][x] - 4.00559*10322^2/x^2;

curve /. x -> 10322

Maybe not.



gauss = 78.8615*Exp[-(x-10358.0837)^2/2/4.713^2]/Sqrt[2 Pi]/4.713

No, I'll just use the values from the last talk.


Exit

[Mathematica finished.]
