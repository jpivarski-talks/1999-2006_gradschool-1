<< Graphics`Graphics`;
<< Graphics`MultipleListPlot`;
<< Statistics`DescriptiveStatistics`;

<< "../dafedir/finalstates_strangesmall.mx";
<< "../dafedir/finalstates_updownsmall.mx";

inElectron = {0,0,-5000,5000};
inPositron = {0,0,5000,5000};
initialstate = inElectron + inPositron;
quarkmass = 170;  (* strange is somewhere between 75 and 170 MeV *)
quarkmass = 0;

OnShell[{x_,y_,z_}, mass_] := N[Sqrt[x^2 + y^2 + z^2 + mass^2]];

MomentumBalance[{electron_, positron_, quark_, antiquark_}] :=
    initialstate - electron - positron - quark - antiquark;

MomentumBalanceChi2[{electron_, positron_, quark_, antiquark_}] :=
    (#.#)&[ MomentumBalance[{electron, positron, quark, antiquark}] ];

template = {
    {electronPx, electronPy, electronPz, OnShell[{electronPx, electronPy, electronPz}, 0]},
    {positronPx, positronPy, positronPz, OnShell[{positronPx, positronPy, positronPz}, 0]},
    {quarkPx, quarkPy, quarkPz, OnShell[{quarkPx, quarkPy, quarkPz}, quarkmass]},
    {antiquarkPx, antiquarkPy, antiquarkPz, OnShell[{antiquarkPx, antiquarkPy, antiquarkPz}, quarkmass]}
	   };

Rand[bound_] := Random[Real, {-bound,bound}];

FinalState[] := template /. FindMinimum[ MomentumBalanceChi2[template],
					 {electronPx, Rand[5000]}, {electronPy, Rand[5000]}, {electronPz, Rand[5000]},
					 {positronPx, Rand[5000]}, {positronPy, Rand[5000]}, {positronPz, Rand[5000]},
					 {quarkPx, Rand[5000]}, {quarkPy, Rand[5000]}, {quarkPz, Rand[5000]},
					 {antiquarkPx, Rand[5000]}, {antiquarkPy, Rand[5000]}, {antiquarkPz, Rand[5000]}
				       ][[2]];


sig0 = {{1,0},{0,1}};
sig1 = {{0,1},{1,0}};
sig2 = {{0,-I},{I,0}};
sig3 = {{1,0},{0,-1}};
sigma = {sig1, sig2, sig3, sig0};
sigbar = {-sig1, -sig2, -sig3, sig0};

gam0 = {{0,0,1,0},{0,0,0,1},{1,0,0,0},{0,1,0,0}};
gam1 = {{0,0,0,1},{0,0,1,0},{0,-1,0,0},{-1,0,0,0}};
gam2 = {{0,0,0,-I},{0,0,I,0},{0,I,0,0},{-I,0,0,0}};
gam3 = {{0,0,1,0},{0,0,0,-1},{-1,0,0,0},{0,1,0,0}};
gamma = {gam1, gam2, gam3, gam0};

(* Remember that index number 4 is the time coordinate! *)
g = {{-1,0,0,0},{0,-1,0,0},{0,0,-1,0},{0,0,0,1}};

Slash[{px_,py_,pz_,en_}] := en*gam0 + px*gam1 + py*gam2 + pz*gam3;

RandomSpin[] := Module[{angle=Random[Real,{0,2 Pi}]},
		       {Cos[angle]*Exp[I*Random[Real,{0,2 Pi}]],
			Sin[angle]*Exp[I*Random[Real,{0,2 Pi}]]
		       }];

Spinor[momentum_, spin_] := Join[
    MatrixPower[momentum . sigma, 1/2] . spin,
    MatrixPower[momentum . sigbar, 1/2] . spin
				];
AntiSpinor[momentum_, spin_] := Join[
    MatrixPower[momentum . sigma, 1/2] . spin,
    -MatrixPower[momentum . sigbar, 1/2] . spin
				];

Bar[spinor_] := Conjugate[spinor] . gam0;

OuterProd[v1_, v2_] := Outer[Times, v1, v2];

e = Sqrt[4 Pi / 137];

Square[{x_,y_,z_,en_}] := en^2 - x^2 - y^2 - z^2;

MuPairFinalState[theta_] := Module[{phi = Random[Real,{0,2 Pi}]},
				   { initialstate[[4]]/2 * {Cos[phi]*Sin[theta], Sin[phi]*Sin[theta], Cos[theta], 1},
				     initialstate[[4]]/2 * {-Cos[phi]*Sin[theta], -Sin[phi]*Sin[theta], -Cos[theta], 1} }
				  ];
MuPairFinalState[] := MuPairFinalState[Random[Real,{0,Pi}]];

MuPairMatrixElement[{muon_, antimuon_}] :=
    Module[{q = inElectron + inPositron},
	   Sum[
	       ( Bar[AntiSpinor[inPositron,RandomSpin[]]] . (-I*e*gamma[[mu]]) . Spinor[inElectron,RandomSpin[]] )
	       * (-I*g[[mu,nu]] / Square[q]) *
	       ( Bar[Spinor[muon,RandomSpin[]]] . (-I*e*gamma[[nu]]) . AntiSpinor[antimuon,RandomSpin[]] )
	       , {mu, 1, 4}, {nu, 1, 4}
	      ]
	  ];

DiffXSMuPair[{muon_, antimuon_}] := DiffXSMuPair[MuPairMatrixElement[muon,antimuon]];
DiffXSMuPair[element_] := (1/2/initialstate[[4]]^2/16/Pi^2/4/2) * Abs[element];

MeanErr[ data_ ] := {Mean[data], StandardDeviation[data]/Sqrt[Length[data]]};

Table[ {theta, N[(1 + Cos[theta]^2)/137^2/4/initialstate[[4]]^2]},
       {theta, 0, Pi/2, Pi/2/5} ] // TableForm

Out[26]//TableForm=                  -13
                    0      2.66397 10

                    Pi
                    --               -13
                    10     2.53677 10

                    Pi
                    --               -13
                    5      2.20378 10

                    3 Pi
                    ----             -13
                     10    1.79217 10

                    2 Pi
                    ----             -13
                     5     1.45918 10

                    Pi
                    --               -13
                    2      1.33198 10

Timing[ thetaMuME = Table[ {theta, Table[ MuPairMatrixElement[MuPairFinalState[theta]], {i,1,30000} ]},
			   {theta, 0, Pi/2, Pi/2/5} ] ][[1]]

thetaMuXS = Join[ {#[[1]]}, MeanErr[DiffXSMuPair[#[[2]]]] ]& /@ thetaMuME;
Show[ 
    MultipleListPlot[ {{#[[1]], #[[2]]}, ErrorBar[#[[3]]]}& /@ thetaMuXS
		      , DisplayFunction -> Identity
		    ]
    , Plot[ (1 + Cos[theta]^2)/137^2/4/initialstate[[4]]^2, {theta, 0, Pi/2}
	    , DisplayFunction -> Identity
	  ]
    , PlotRange -> {{0,Pi/2},{0,3.5*^-13}}
    , DisplayFunction -> $DisplayFunction
    ];
(* TableForm[thetaMuXS] *)


SpinlessMatrixElement[{electron_,positron_,quark_,antiquark_}] :=
    Module[{q1 = inPositron - positron, q2 = inElectron - electron, virtualquark = quark + antiquark},
	   (* virtualquark also equals q1 + q2 because of the way that the final states were chosen *)
	   3 * (I*e) * (-I/Square[q1]) * (-I*(5/9)*e) * (I/(Square[virtualquark] - quarkmass^2))
	   * (I*e) * (-I/Square[q2]) * (-I*e)
	  ];

CrossSection[{{electron_,positron_,quark_,antiquark_},element_}] :=
    { {electron,positron,quark,antiquark},
      (1/8/initialstate[[4]]^2) * (1/(2 Pi)^12) * (1/2/2/2/2)
      * (1/electron[[4]]/positron[[4]]/quark[[4]]/antiquark[[4]]) * (2 Pi)^4 / 4
      * Abs[element]
    };

quarkmass = 170;
strangeSME = CrossSection[{#, SpinlessMatrixElement[#]}]& /@ strangesmall;


quarkmass = 0;
updownSME = CrossSection[{#, SpinlessMatrixElement[#]}]& /@ updownsmall;


Export["updown_spinless_ntuple.dat", { #[[1,1,3]] / Sqrt[#[[1,1,1]]^2 + #[[1,1,2]]^2],
				       #[[1,2,3]] / Sqrt[#[[1,2,1]]^2 + #[[1,2,2]]^2],
				       ( #[[1,3]] + #[[1,4]] )[[1]],
				       ( #[[1,3]] + #[[1,4]] )[[2]],
				       ( #[[1,3]] + #[[1,4]] )[[3]],
				       ( #[[1,3]] + #[[1,4]] )[[4]],
				       #[[2]]*10^40
				     }& /@ updownSME];

Export["strange_spinless_ntuple.dat", { #[[1,1,3]] / Sqrt[#[[1,1,1]]^2 + #[[1,1,2]]^2],
					#[[1,2,3]] / Sqrt[#[[1,2,1]]^2 + #[[1,2,2]]^2],
					( #[[1,3]] + #[[1,4]] )[[1]],
					( #[[1,3]] + #[[1,4]] )[[2]],
					( #[[1,3]] + #[[1,4]] )[[3]],
					( #[[1,3]] + #[[1,4]] )[[4]],
					#[[2]]*10^40
				      }& /@ strangeSME];





MatrixElement[{electron_,positron_,quark_,antiquark_}] :=
    Module[{q1 = inPositron - positron, q2 = inElectron - electron, virtualquark = quark + antiquark},
	   (* virtualquark also equals q1 + q2 because of the way that the final states were chosen *)
	   3 * Sum[
	       ( Bar[AntiSpinor[inPositron,RandomSpin[]]] . (I*e*gamma[[mu]]) . AntiSpinor[positron,RandomSpin[]] )
	       * (-I*g[[mu,mu]] / Square[q1]) *
	       ( Bar[Spinor[quark,RandomSpin[]]]
		 . ( (-I*(5/9)*e*gamma[[mu]])
		  (* . (I * Slash[virtualquark] + quarkmass) was an error *)
		     . (I * (Slash[virtualquark] + quarkmass)) / (Square[virtualquark] - quarkmass^2) )
		 . (I*e*gamma[[nu]]) . AntiSpinor[antiquark,RandomSpin[]] )
	       * (-I*g[[nu,nu]] / Square[q2]) *
	       ( Bar[Spinor[electron,RandomSpin[]]] . (-I*e*gamma[[nu]]) . Spinor[inElectron,RandomSpin[]] )
	       , {mu, 1, 4}, {nu, 1, 4}
		  ]
	  ];

CrossSection[{{electron_,positron_,quark_,antiquark_},element_}] :=
    { {electron,positron,quark,antiquark},
      (1/8/initialstate[[4]]^2) * (1/(2 Pi)^12) * (1/2/2/2/2)
      * (1/electron[[4]]/positron[[4]]/quark[[4]]/antiquark[[4]]) * (2 Pi)^4 / 4
      * Abs[element]
    };

quarkmass = 170;
Timing[ strangeME = {#,MatrixElement[#]}& /@ strangesmall ][[1]]

Out[33]= 7725.98 Second

quarkmass = 0;
Timing[ updownME = {#,MatrixElement[#]}& /@ updownsmall ][[1]]

Out[34]= 7679.49 Second

CrossSection[strangeME[[1]]]

Out[35]= {{{665.526, 1470.38, -490.889, 1686.99}, 
 
>     {-14.3478, -2182.46, 148.058, 2187.52}, 
 
>     {-34.6967, 3373.13, 122.411, 3379.81}, 
 
                                                        -40
>     {-616.482, -2661.06, 220.42, 2745.68}}, 6.85442 10   }

Out[32]= {{{665.526, 1470.38, -490.889, 1686.99}, 
 
>     {-14.3478, -2182.46, 148.058, 2187.52}, 
 
>     {-34.6967, 3373.13, 122.411, 3379.81}, 
 
                                                        -39
>     {-616.482, -2661.06, 220.42, 2745.68}}, 1.29293 10   }

DumpSave[ "../dafedir/fs_me_strange.mx", strangeME ];
DumpSave[ "../dafedir/fs_me_updown.mx", updownME ];

<< "../dafedir/fs_me_updown.mx"

strangeXS = CrossSection /@ strangeME;

updownXS = CrossSection /@ updownME;

goodstrangeXS = Select[ strangeXS, (#[[2]]>500*^-40 || Random[Real,{0,500*^-40}]<#[[2]])& ];

goodupdownXS = Select[ updownXS, (#[[2]]>500*^-40 || Random[Real,{0,500*^-40}]<#[[2]])& ];



Histogram[Select[#[[2]]&/@updownXS,(#<100*^-40)&]
	  , HistogramRange -> {0,100*^-40} ];

goodupdownXS = Select[updownXS, (#[[2]]<100*^-40 && Random[Real,{0,100*^-40}]<#[[2]])& ];








Length[Select[updownXS, (#[[2]]<100*^-40 && Random[Real,{0,100*^-40}]<#[[2]])&]]
    / Length[Select[updownXS, (#[[2]]<100*^-40)&]]
    * 100*^-40 * 10000^11 // N

Out[28]= 102727.








            (* question *)
ListPlot[ { Sqrt[#[[1]]^2 + #[[2]]^2]&[ ( #[[1,3]] + #[[1,4]] ) ]
	    (* above is the expression under question *)
	    ,#[[2]]}& /@ strangeXS
	  , PlotRange -> {{0,10000},{0,10^-36}}
	];

            (* question *)
ListPlot[ { (#[[3]] / Sqrt[#[[1]]^2 + #[[2]]^2])&[ ( #[[1,1]] ) ]
	    (* above is the expression under question *)
	    ,#[[2]]}& /@ updownXS
	  , PlotRange -> {{0,5},{0,10^-35}}
	];



Export["updown_ntuple.dat", { #[[1,1,3]] / Sqrt[#[[1,1,1]]^2 + #[[1,1,2]]^2],
			      #[[1,2,3]] / Sqrt[#[[1,2,1]]^2 + #[[1,2,2]]^2],
			      ( #[[1,3]] + #[[1,4]] )[[1]],
			      ( #[[1,3]] + #[[1,4]] )[[2]],
			      ( #[[1,3]] + #[[1,4]] )[[3]],
			      ( #[[1,3]] + #[[1,4]] )[[4]],
			      #[[2]]*10^40
			    }& /@ updownXS];

Export["strange_ntuple.dat", { #[[1,1,3]] / Sqrt[#[[1,1,1]]^2 + #[[1,1,2]]^2],
			       #[[1,2,3]] / Sqrt[#[[1,2,1]]^2 + #[[1,2,2]]^2],
			       ( #[[1,3]] + #[[1,4]] )[[1]],
			       ( #[[1,3]] + #[[1,4]] )[[2]],
			       ( #[[1,3]] + #[[1,4]] )[[3]],
			       ( #[[1,3]] + #[[1,4]] )[[4]],
			       #[[2]]*10^40
			     }& /@ strangeXS];























    Module[{q1 = inPositron - positron, q2 = inElectron - electron, virtualquark = quark + antiquark},
	   (* virtualquark also equals q1 + q2 because of the way that the final states were chosen *)
	   3 * Sum[
	       ( Bar[AntiSpinor[inPositron,RandomSpin[]]] . (I*e*gamma[[mu]]) . AntiSpinor[positron,RandomSpin[]] )
	       * (-I*g[[mu,mu]] / Square[q1]) *
	       ( Bar[Spinor[quark,RandomSpin[]]]
		 . ( (-I*(5/9)*e*gamma[[mu]])
		  (* . (I * Slash[virtualquark] + quarkmass) was an error *)
		     . (I * (Slash[virtualquark] + quarkmass)) / (Square[virtualquark] - quarkmass^2) )
		 . (I*e*gamma[[nu]]) . AntiSpinor[antiquark,RandomSpin[]] )
	       * (-I*g[[nu,nu]] / Square[q2]) *
	       ( Bar[Spinor[electron,RandomSpin[]]] . (-I*e*gamma[[nu]]) . Spinor[inElectron,RandomSpin[]] )
	       , {mu, 1, 4}, {nu, 1, 4}
		  ]
	  ];

CrossSection[{{electron_,positron_,quark_,antiquark_},element_}] :=
    { {electron,positron,quark,antiquark},
      (1/8/initialstate[[4]]^2) * (1/(2 Pi)^12) * (1/2/2/2/2)
      * (1/electron[[4]]/positron[[4]]/quark[[4]]/antiquark[[4]]) * (2 Pi)^4 / 4
      * Abs[element]
    };












http://www.quark.lu.se/~delphi/delphi-twophoton.html


http://www.hep.ucl.ac.uk/opal/gammagamma/gg-tutorial.html




http://www.quark.lu.se/~delphi/delphi-twophoton.html
http://l3.web.cern.ch/l3/analysis/gg/ggpicutres.html









Exit

[Mathematica finished.]










Module[{electron,positron,quark,antiquark},
       electron = Random[Real, {0,10000}];
       positron = Random[Real, {0,10000}];
       quark = Random[Real, {0,10000}];
       antiquark = initialstate[[4]] - electron - positron - quark;
       {electron,positron,quark,antiquark}
      ]
      



