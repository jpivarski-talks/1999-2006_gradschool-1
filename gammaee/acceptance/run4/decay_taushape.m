<< Graphics`MultipleListPlot`;
<< Statistics`ContinuousDistributions`;
<< Graphics`Graphics`;

<< "/cdat/dafe/mccann/acceptance/new_decaymodes_1.fewm";
<< "/cdat/dafe/mccann/acceptance/new_decaymodes_2.fewm";
<< "/cdat/dafe/mccann/acceptance/new_decaymodes_3.fewm";

e1sdirect = (Plus @@ (#[[2]]& /@ ee1s)) / (Plus @@ (#[[2]]& /@ Join[ee1s, ee1spho]));
mu1sdirect = (Plus @@ (#[[2]]& /@ mumu1s)) / (Plus @@ (#[[2]]& /@ Join[mumu1s, mumu1spho]));
tau1sdirect = (Plus @@ (#[[2]]& /@ tautau1s)) / (Plus @@ (#[[2]]& /@ Join[tautau1s, tautau1spho]));
glue1sdirect = (Plus @@ (#[[2]]& /@ glue1s)) / (Plus @@ (#[[2]]& /@ Join[glue1s, glue1spho]));
ggpho1sdirect = (Plus @@ (#[[2]]& /@ ggpho1s)) / (Plus @@ (#[[2]]& /@ Join[ggpho1s, ggpho1spho]));
e2sdirect = (Plus @@ (#[[2]]& /@ ee2s)) / (Plus @@ (#[[2]]& /@ Join[ee2s, ee2spho]));
mu2sdirect = (Plus @@ (#[[2]]& /@ mumu2s)) / (Plus @@ (#[[2]]& /@ Join[mumu2s, mumu2spho]));
tau2sdirect = (Plus @@ (#[[2]]& /@ tautau2s)) / (Plus @@ (#[[2]]& /@ Join[tautau2s, tautau2spho]));
glue2sdirect = (Plus @@ (#[[2]]& /@ glue2s)) / (Plus @@ (#[[2]]& /@ Join[glue2s, glue2spho]));
ggpho2sdirect = (Plus @@ (#[[2]]& /@ ggpho2s)) / (Plus @@ (#[[2]]& /@ Join[ggpho2s, ggpho2spho]));
e3sdirect = (Plus @@ (#[[2]]& /@ ee3s)) / (Plus @@ (#[[2]]& /@ Join[ee3s, ee3spho]));
mu3sdirect = (Plus @@ (#[[2]]& /@ mumu3s)) / (Plus @@ (#[[2]]& /@ Join[mumu3s, mumu3spho]));
tau3sdirect = (Plus @@ (#[[2]]& /@ tautau3s)) / (Plus @@ (#[[2]]& /@ Join[tautau3s, tautau3spho]));
glue3sdirect = (Plus @@ (#[[2]]& /@ glue3s)) / (Plus @@ (#[[2]]& /@ Join[glue3s, glue3spho]));
ggpho3sdirect = (Plus @@ (#[[2]]& /@ ggpho3s)) / (Plus @@ (#[[2]]& /@ Join[ggpho3s, ggpho3spho]));

(* 0 => "vpho", *)
(* 1 => "gamma", *)
(* 7 => "e-", *)
(* 8 => "e+", *)
(* 9 => "nu_e", *)
(* 10 => "anti-nu_e", *)
(* 11 => "mu-", *)
(* 12 => "mu+", *)
(* 13 => "nu_mu", *)
(* 14 => "anti-nu_mu", *)
(* 15 => "tau-", *)
(* 16 => "tau+", *)
(* 17 => "nu_tau", *)
(* 18 => "anti-nu_tau", *)
(* 21 => "pi+", *)
(* 22 => "pi-", *)
(* 51 => "pi0", *)
(* 95 => "Upsilon(1S)", *)
(* 97 => "Upsilon(2S)", *)
(* 98 => "Upsilon(3S)", *)
(* 100 => "chi_b0(1P)", *)
(* 101 => "chi_b1(1P)", *)
(* 102 => "chi_b2(1P)", *)
(* 103 => "chi_b0(2P)", *)
(* 104 => "chi_b1(3P)", *)
(* 105 => "chi_b2(2P)", *)
(* 577 => "Upsilon_1(2D)", *)
(* 578 => "Upsilon_2(2D)", *)
(* 579 => "Upsilon_1(1D)", *)
(* 580 => "Upsilon_2(1D)", *)
(* 581 => "Upsilon_3(2D)", *)
(* 582 => "Upsilon_3(1D)", *)
(* 584 => "chi_b0(3P)", *)
(* 585 => "chi_b1(2P)", *)
(* 586 => "chi_b2(3P)", *)
(* 495 => "string", *)

photoglue = 0.03;
cascadeworldcounter = 0;
cascadeworld[{b1mu_, b1muerr_}, {b2mu_, b2muerr_}, {b3mu_, b3muerr_}] :=
    (cascadeworldcounter++;
     br["0 1 95"] = 1;
     br["0 1 97"] = 1;
     br["0 1 98"] = 1;
     br["95 7 8"] = Random[NormalDistribution @@ ({b1mu, b1muerr}/100)];
     br["95 11 12"] = br["95 7 8"];
     br["95 15 16"] = br["95 7 8"];
     br["97 7 8"] = Random[NormalDistribution @@ ({b2mu, b2muerr}/100)];
     br["97 11 12"] = br["97 7 8"];
     br["97 15 16"] = br["97 7 8"];
     br["98 7 8"] = Random[NormalDistribution @@ ({b3mu, b3muerr}/100)];
     br["98 11 12"] = br["98 7 8"];
     br["98 15 16"] = br["98 7 8"];
     br["100 1 95"] = Random[ExponentialDistribution[1/0.03]];
     br["101 1 95"] = Random[NormalDistribution @@ ({35, 8}/100)];
     br["102 1 95"] = Random[NormalDistribution @@ ({22, 4}/100)];
     br["97 21 22 95"] = Random[NormalDistribution @@ ({18.8, 0.6}/100)];
     br["97 51 51 95"] = Random[NormalDistribution @@ ({9, 0.8}/100)];
     br["97 1 100"] = Random[NormalDistribution @@ ({3.8, 0.6}/100)];
     br["97 1 101"] = Random[NormalDistribution @@ ({6.8, 0.7}/100)];
     br["97 1 102"] = Random[NormalDistribution @@ ({7, 0.6}/100)];
     br["103 1 95"] = Random[NormalDistribution @@ ({9, 6}/100)];
     br["103 1 97"] = Random[NormalDistribution @@ ({4.6, 2.1}/100)];
     br["585 1 95"] = Random[NormalDistribution @@ ({8.5, 1.3}/100)];
     br["585 1 97"] = Random[NormalDistribution @@ ({21, 4}/100)];
     br["105 1 95"] = Random[NormalDistribution @@ ({7.1, 1}/100)];
     br["105 1 97"] = Random[NormalDistribution @@ ({16.2, 2.4}/100)];
     br["98 21 22 95"] = Random[NormalDistribution @@ ({4.48, 0.21}/100)];
     br["98 51 51 95"] = Random[NormalDistribution @@ ({2.06, 0.28}/100)];
     br["98 21 22 97"] = Random[NormalDistribution @@ ({2.8, 0.6}/100)];
     br["98 51 51 97"] = Random[NormalDistribution @@ ({2, 0.32}/100)];
     br["98 1 103"] = Random[NormalDistribution @@ ({5.4, 0.6}/100)];
     br["98 1 585"] = Random[NormalDistribution @@ ({11.3, 0.6}/100)];
     br["98 1 105"] = Random[NormalDistribution @@ ({11.4, 0.8}/100)];
     br["98 1 1 97"] = Random[NormalDistribution @@ ({5, 0.7}/100)];
     br["103 1 579"] = Random[Real, {0., 2*0.15/100}];
     br["585 1 579"] = Random[Real, {0., 2*0.97/100}];
     br["585 1 580"] = Random[Real, {0., 2*2.36/100}];
     br["105 1 579"] = Random[Real, {0., 2*0.023/100}];
     br["105 1 580"] = Random[Real, {0., 2*0.29/100}];
     br["105 1 582"] = Random[Real, {0., 2*1.42/100}];
     br["579 21 22 95"] = Random[Real, {0., 2*0.14/100}];
     br["579 51 51 95"] = Random[Real, {0., 2*0.07/100}];
     br["579 1 101"] = Random[Real, {0., 2*31.8/100}];
     br["579 1 102"] = Random[Real, {0., 2*2.6/100}];
     br["579 1 100"] = Random[Real, {0., 1. - (br["579 21 22 95"] + br["579 51 51 95"] +
					       br["579 1 101"] + br["579 1 102"])}];  (* 60.2% *)
     br["580 21 22 95"] = Random[Real, {0., 2*0.14/100}];
     br["580 51 51 95"] = Random[Real, {0., 2*0.07/100}];
     br["580 1 102"] = Random[Real, {0., 2*20.3/100}];
     br["580 1 101"] = Random[Real, {0., 1. - (br["580 21 22 95"] + br["580 51 51 95"] +
					       br["580 1 102"])}];  (* 78.5% *)
     br["582 21 22 95"] = Random[Real, {0., 2*0.2/100}];
     br["582 51 51 95"] = Random[Real, {0., 2*0.1/100}];
     br["582 1 102"] = Random[Real, {0., 1. - (br["582 21 22 95"] + br["582 51 51 95"])}];  (* 95.4% *)
     br["95 known"] = (br["95 7 8"] + br["95 11 12"] + br["95 15 16"]);
     br["97 known"] = (br["97 7 8"] + br["97 11 12"] + br["97 15 16"] +
		       br["97 21 22 95"] + br["97 51 51 95"] + br["97 1 100"] +
		       br["97 1 101"] + br["97 1 102"]);
     br["98 known"] = (br["98 7 8"] + br["98 11 12"] + br["98 15 16"] +
		       br["98 21 22 95"] + br["98 51 51 95"] + br["98 21 22 97"] +
		       br["98 51 51 97"] + br["98 1 103"] + br["98 1 585"] +
		       br["98 1 105"] + br["98 1 1 97"]);
     br["100 known"] = (br["100 1 95"]);
     br["101 known"] = (br["101 1 95"]);
     br["102 known"] = (br["102 1 95"]);
     br["103 known"] = (br["103 1 95"] + br["103 1 97"] + br["103 1 579"]);
     br["585 known"] = (br["585 1 95"] + br["585 1 97"] + br["585 1 579"] + br["585 1 580"]);
     br["105 known"] = (br["105 1 95"] + br["105 1 97"] + br["105 1 579"] + br["105 1 580"] +
			br["105 1 582"]);
     br["579 known"] = (br["579 21 22 95"] + br["579 51 51 95"] + br["579 1 101"] +
			br["579 1 102"] + br["579 1 100"]);
     br["580 known"] = (br["580 21 22 95"] + br["580 51 51 95"] + br["580 1 102"] +
			br["580 1 101"]);
     br["582 known"] = (br["582 21 22 95"] + br["582 51 51 95"] + br["582 1 102"]);
     br["95 495"] = (1 - photoglue)*(1 - br["95 known"]);
     br["97 495"] = (1 - photoglue)*(1 - br["97 known"]);
     br["98 495"] = (1 - photoglue)*(1 - br["98 known"]);
     br["100 495"] = (1 - br["100 known"]);
     br["101 495"] = (1 - br["101 known"]);
     br["102 495"] = (1 - br["102 known"]);
     br["103 495"] = (1 - br["103 known"]);
     br["585 495"] = (1 - br["585 known"]);
     br["105 495"] = (1 - br["105 known"]);
     br["579 495"] = (1 - photoglue)*(1 - br["579 known"]);
     br["580 495"] = (1 - photoglue)*(1 - br["580 known"]);
     br["582 495"] = (1 - photoglue)*(1 - br["582 known"]);
     br["95 1 495"] = (photoglue)*(1 - br["95 known"]);
     br["97 1 495"] = (photoglue)*(1 - br["97 known"]);
     br["98 1 495"] = (photoglue)*(1 - br["98 known"]);
     br["579 1 495"] = (photoglue)*(1 - br["579 known"]);
     br["580 1 495"] = (photoglue)*(1 - br["580 known"]);
     br["582 1 495"] = (photoglue)*(1 - br["582 known"]);
     If[br["95 known"] >= 1   ||  br["97 known"] >= 1   ||  br["98 known"] >= 1   ||
	br["100 known"] >= 1  ||  br["101 known"] >= 1  ||  br["102 known"] >= 1  ||
	br["103 known"] >= 1  ||  br["585 known"] >= 1  ||  br["105 known"] >= 1  ||
	br["579 known"] >= 1  ||  br["580 known"] >= 1  ||  br["582 known"] >= 1,
	cascadeworld[]
       ];
    );
cascadeworld[] :=
    cascadeworld[{2.480, 0.050}, {1.25, 0.14}, {1.81, 0.17}];
denom[y_] := Plus @@ ((Times @@ (br /@ #[[4]]))& /@ y);
failnumer[y_] := Plus @@ ((#[[1]]/#[[2]]*(Times @@ (br /@ #[[4]])))& /@ y);

tauworldcounter = 0;
tauworld[] :=
    (tauworldcounter++;
     br["17 22 51"] = Random[NormalDistribution @@ ({25.41, 0.14}/100)];
     br["11 14 17"] = Random[NormalDistribution @@ ({17.37, 0.07}/100)];
     br["7 10 17"] = Random[NormalDistribution @@ ({17.84, 0.06}/100)];
     br["17 22"] = Random[NormalDistribution @@ ({11.06, 0.11}/100)];
     br["17 22 51 51"] = Random[NormalDistribution @@ ({9.17, 0.14}/100)];
     br["17 21 22 22"] = Random[NormalDistribution @@ ({9.22, 0.10}/100)];
     br["17 21 22 22 51"] = Random[NormalDistribution @@ ({4.24, 0.10}/100)];
     br["1 7 10 17"] = Random[NormalDistribution @@ ({1.75, 0.18}/100)];
     br["17 64"] = Random[NormalDistribution @@ ({1.29, 0.05}/100)];
     br["17 22 51 51 51 51"] = Random[NormalDistribution @@ ({1.08, 0.10}/100)];
     br["18 21 51"] = br["17 22 51"];
     br["12 13 18"] = br["11 14 17"];
     br["8 9 18"] = br["7 10 17"];
     br["18 21"] = br["17 22"];
     br["18 21 51 51"] = br["17 22 51 51"];
     br["18 21 21 22"] = br["17 21 22 22"];
     br["18 21 21 22 51"] = br["17 21 22 22 51"];
     br["1 8 9 18"] = br["1 7 10 17"];
     br["18 63"] = br["17 64"];
     br["18 21 51 51 51"] = br["17 22 51 51 51 51"];
     br["other"] = 1 - (br["17 22 51"] +
			br["11 14 17"] +
			br["7 10 17"] +
			br["17 22"] +
			br["17 22 51 51"] +
			br["17 21 22 22"] +
			br["17 21 22 22 51"] +
			br["1 7 10 17"] +
			br["17 64"] +
			br["17 22 51 51 51 51"]);
     If[br["other"] < 0, tauworld[]];
    );
taufailnumer[tsh_] := Plus @@ ((#[[1]]/#[[2]]*br[#[[3]]]*br[#[[4]]]*(Times @@ (br /@ #[[5]])))& /@ tsh);

n[x_] := x[[2]];
eff[x_] := (1-x[[1]]/n[x])*100;
erreff[x_] := Sqrt[eff[x]/100*(1-eff[x]/100)/n[x]]*100;
point[x_] := {{eff[x], n[x]}, ErrorBar[erreff[x], Sqrt[n[x]]]};
range[y_, m1_, m2_] := {{Min[m1, N[Min[(eff[#]-erreff[#])& /@ y]]],
			 Max[m2, N[Max[(eff[#]+erreff[#])& /@ y]]]},
			{0, N[Max[(# + 2*Sqrt[#]), 1.1*#]&[(Max @@ (n /@ y))]]}};
events[y_] := Plus @@ (#[[2]]& /@ y);

tweakworld[res_] := If[res == 1,
		       (br["95 7 8"] = e1sdirect * br["95 7 8"];
			br["95 11 12"] = mu1sdirect * br["95 11 12"];
			br["95 15 16"] = tau1sdirect * br["95 15 16"];
			br["97 7 8"] = e1sdirect * br["97 7 8"];
			br["97 11 12"] = mu1sdirect * br["97 11 12"];
			br["97 15 16"] = tau1sdirect * br["97 15 16"];
			br["98 7 8"] = e1sdirect * br["98 7 8"];
			br["98 11 12"] = mu1sdirect * br["98 11 12"];
			br["98 15 16"] = tau1sdirect * br["98 15 16"];
		       ),
		       If[res == 2,
			  (br["95 7 8"] = e2sdirect * br["95 7 8"];
			   br["95 11 12"] = mu2sdirect * br["95 11 12"];
			   br["95 15 16"] = tau2sdirect * br["95 15 16"];
			   br["97 7 8"] = e2sdirect * br["97 7 8"];
			   br["97 11 12"] = mu2sdirect * br["97 11 12"];
			   br["97 15 16"] = tau2sdirect * br["97 15 16"];
			   br["98 7 8"] = e2sdirect * br["98 7 8"];
			   br["98 11 12"] = mu2sdirect * br["98 11 12"];
			   br["98 15 16"] = tau2sdirect * br["98 15 16"];
			  ),
			  If[res == 3,
			     (br["95 7 8"] = e3sdirect * br["95 7 8"];
			      br["95 11 12"] = mu3sdirect * br["95 11 12"];
			      br["95 15 16"] = tau3sdirect * br["95 15 16"];
			      br["97 7 8"] = e3sdirect * br["97 7 8"];
			      br["97 11 12"] = mu3sdirect * br["97 11 12"];
			      br["97 15 16"] = tau3sdirect * br["97 15 16"];
			      br["98 7 8"] = e3sdirect * br["98 7 8"];
			      br["98 11 12"] = mu3sdirect * br["98 11 12"];
			      br["98 15 16"] = tau3sdirect * br["98 15 16"];
			     )
			    ]]];
figureeverythingout[y_, z_, shuffles_, res_] := (
    aggeff = {};
    dens = {};
    Do[(
	cascadeworld[];
	tweakworld[res];
	den = denom[y];
	dens = Append[dens, den];
	aggeff = Append[aggeff, 1 - failnumer[y]/den];
       ), {shuffles}];
    nevents = Plus @@ (#[[2]]& /@ y);
    ave = N[1 - (Plus @@ (#[[1]]& /@ y))/nevents];
    aveerr = Sqrt[ave*(1-ave)/nevents];
    neventspho = (Plus @@ (#[[2]]& /@ z));
    avepho = N[1 - (Plus @@ (#[[1]]& /@ z))/neventspho];
    aveerrpho = Sqrt[avepho*(1-avepho)/neventspho];
    Print[TableForm[{
	{"Average", "Error", "Toy MC", "MC RMS", "Denom", "Denom RMS", "Events"},
	Join[{ave, aveerr, avetoy = Mean[aggeff], rmstoy = StandardDeviation[aggeff],
	      Mean[dens], StandardDeviation[dens]}*100, {nevents}],
	Join[{avepho, aveerrpho}*100, {"n/a", "n/a", "n/a", "n/a", neventspho}]
		    }]];
    Print[];
    modeeff = (avetoy*nevents + avepho*neventspho)/(nevents + neventspho);
    modeefferr = (Sqrt[rmstoy^2/avetoy^2 + aveerr^2/ave^2]*ave*nevents +
		  aveerrpho*neventspho)/(nevents + neventspho);
    Print["Mode efficiency = ", modeeff*100, " +/- ", modeefferr*100];
    modeeff = (avetoy*(nevents - 0.3*neventspho) + avepho*(1.3*neventspho))/(nevents + neventspho);
    Print["Mode efficiency = ", modeeff*100, " with 30% more PHOTOS"];
    modeeff = (avetoy*(nevents + 0.3*neventspho) + avepho*(0.7*neventspho))/(nevents + neventspho);
    Print["Mode efficiency = ", modeeff*100, " with 30% less PHOTOS"];
    Print[];
			 );

figuremostthingsout[y_, z_, shuffles_, res_] := (
    aggeff = {};
    dens = {};
    Do[(
	cascadeworld[];
	tweakworld[res];
	den = denom[y];
	dens = Append[dens, den];
	aggeff = Append[aggeff, 1 - failnumer[y]/den];
       ), {shuffles}];
    nevents = Plus @@ (#[[2]]& /@ y);
    ave = N[1 - (Plus @@ (#[[1]]& /@ y))/nevents];
    aveerr = Sqrt[ave*(1-ave)/nevents];
    Print[TableForm[{
	{"Average", "Error", "Toy MC", "MC RMS", "Denom", "Denom RMS", "Events"},
	Join[{ave, aveerr, avetoy = Mean[aggeff], rmstoy = StandardDeviation[aggeff],
	      Mean[dens], StandardDeviation[dens]}*100, {nevents}],
	Join[{0, 0}*100, {"n/a", "n/a", "n/a", "n/a", 0}]
		    }]];
    Print[];
    modeeff = avetoy;
    modeefferr = Sqrt[rmstoy^2/avetoy^2 + aveerr^2/ave^2]*ave;
    Print["Mode efficiency = ", modeeff*100, " +/- ", modeefferr*100];
    Print[];
			 );

figuretausout[y_, z_, ypho_, zpho_, shuffles_, res_] := (
    aggeff = {};
    dens = {};
    Do[(
	cascadeworld[];
	tweakworld[res];
	tauworld[];
	den = denom[y];
	dens = Append[dens, den];
	aggeff = Append[aggeff, 1 - taufailnumer[z]/den];
       ), {shuffles}];
    nevents = Plus @@ (#[[2]]& /@ z);
    ave = N[1 - (Plus @@ (#[[1]]& /@ z))/nevents];
    aveerr = Sqrt[ave*(1-ave)/nevents];
    neventspho = (Plus @@ (#[[2]]& /@ zpho));
    avepho = N[1 - (Plus @@ (#[[1]]& /@ zpho))/neventspho];
    aveerrpho = Sqrt[avepho*(1-avepho)/neventspho];
    Print[TableForm[{
	{"Average", "Error", "Toy MC", "MC RMS", "Denom", "Denom RMS", "Events"},
	Join[{ave, aveerr, avetoy = Mean[aggeff], rmstoy = StandardDeviation[aggeff],
	      Mean[dens], StandardDeviation[dens]}*100, {nevents}],
	Join[{avepho, aveerrpho}*100, {"n/a", "n/a", "n/a", "n/a", neventspho}]
		    }]];
    Print[];
    modeeff = (avetoy*nevents + avepho*neventspho)/(nevents + neventspho);
    modeefferr = (Sqrt[rmstoy^2/avetoy^2 + aveerr^2/ave^2]*ave*nevents +
		  aveerrpho*neventspho)/(nevents + neventspho);
    Print["Mode efficiency = ", modeeff*100, " +/- ", modeefferr*100];
    modeeff = (avetoy*(nevents - 0.3*neventspho) + avepho*(1.3*neventspho))/(nevents + neventspho);
    Print["Mode efficiency = ", modeeff*100, " with 30% more PHOTOS"];
    modeeff = (avetoy*(nevents + 0.3*neventspho) + avepho*(0.7*neventspho))/(nevents + neventspho);
    Print["Mode efficiency = ", modeeff*100, " with 30% less PHOTOS"];
    Print[];
				    );

Display["decayplot_glue.eps",
    Show[GraphicsArray[{
	Show[
	    MultipleListPlot[point /@ glue1s
			     , SymbolStyle -> GrayLevel[0]
			     , DisplayFunction -> Identity
			    ]
	    , PlotRange -> range[glue1s, 95, 101]
	    , Axes -> False
	    , Frame -> True
	    , FrameTicks -> {Range[0, 100, 1], Automatic, None, None}
	    , FrameLabel -> {None, None, "Upsilon(1S)", None}
	    , AspectRatio -> Sqrt[2]
	    , DisplayFunction -> Identity
	    ]
	, Show[
	    MultipleListPlot[point /@ glue2s
			     , SymbolStyle -> GrayLevel[0]
			     , DisplayFunction -> Identity
			    ]
	    , MultipleListPlot[point /@ glue2spho
			       , SymbolStyle -> RGBColor[1,0,0]
			       , DisplayFunction -> Identity
			      ]
	    , PlotRange -> range[Join[glue2spho, glue2s], 95, 101]
	    , Axes -> False
	    , Frame -> True
	    , FrameTicks -> {Range[0, 100, 1], Automatic, None, None}
	    , FrameLabel -> {None, None, "Upsilon(2S)", None}
	    , AspectRatio -> Sqrt[2]
	    , DisplayFunction -> Identity
	      ]
	, Show[
	    MultipleListPlot[point /@ glue3s
			     , SymbolStyle -> GrayLevel[0]
			     , DisplayFunction -> Identity
			    ]
	    , MultipleListPlot[point /@ glue3spho
			       , SymbolStyle -> RGBColor[1,0,0]
			       , DisplayFunction -> Identity
			      ]
	    , PlotRange -> range[Join[glue3spho, glue3s], 50, 105]
	    , Axes -> False
	    , Frame -> True
	    , FrameTicks -> {Range[0, 100, 10], Automatic, None, None}
	    , FrameLabel -> {None, None, "Upsilon(3S)", None}
	    , AspectRatio -> Sqrt[2]
	    , DisplayFunction -> Identity
	      ]
		       }]
	 , DisplayFunction -> $DisplayFunction
	], "EPS"
	, ImageSize -> 500
       ];

photoglue = 0.03;
figuremostthingsout[glue1s, glue1spho, 10000, 1];
figureeverythingout[glue2s, glue2spho, 10000, 2];
figureeverythingout[glue3s, glue3spho, 10000, 3];

photoglue = 0.04;
figuremostthingsout[glue1s, glue1spho, 10000, 1];
figureeverythingout[glue2s, glue2spho, 10000, 2];
figureeverythingout[glue3s, glue3spho, 10000, 3];

photoglue = 0.02;
figuremostthingsout[glue1s, glue1spho, 10000, 1];
figureeverythingout[glue2s, glue2spho, 10000, 2];
figureeverythingout[glue3s, glue3spho, 10000, 3];

Display["decayplot_ggpho.eps",
	Show[GraphicsArray[{
	    Show[
		MultipleListPlot[point /@ ggpho1s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, PlotRange -> range[ggpho1s, -10, 110]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 20], Automatic, None, None}
		, FrameLabel -> {None, None, "Upsilon(1S)", None}
		, AspectRatio -> Sqrt[2]
		, DisplayFunction -> Identity
		]
	    , Show[
		MultipleListPlot[point /@ ggpho2s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, MultipleListPlot[point /@ ggpho2spho
				   , SymbolStyle -> RGBColor[1,0,0]
				   , DisplayFunction -> Identity
				  ]
		, PlotRange -> range[Join[ggpho2spho, ggpho2s], -10, 110]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 20], Automatic, None, None}
		, FrameLabel -> {None, None, "Upsilon(2S)", None}
		, AspectRatio -> Sqrt[2]
		, DisplayFunction -> Identity
		  ]
	    , Show[
		MultipleListPlot[point /@ ggpho3s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, MultipleListPlot[point /@ ggpho3spho
				   , SymbolStyle -> RGBColor[1,0,0]
				   , DisplayFunction -> Identity
				  ]
		, PlotRange -> range[Join[ggpho3spho, ggpho3s], -10, 110]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 20], Automatic, None, None}
		, FrameLabel -> {None, None, "Upsilon(3S)", None}
		, AspectRatio -> Sqrt[2]
		, DisplayFunction -> Identity
		  ]
			   }]
	     , DisplayFunction -> $DisplayFunction
	    ], "EPS"
	, ImageSize -> 500
       ];

photoglue = 0.03;
figuremostthingsout[ggpho1s, ggpho1spho, 10000, 1];
figureeverythingout[ggpho2s, ggpho2spho, 10000, 2];
figureeverythingout[ggpho3s, ggpho3spho, 10000, 3];

photoglue = 0.04;
figuremostthingsout[ggpho1s, ggpho1spho, 10000, 1];
figureeverythingout[ggpho2s, ggpho2spho, 10000, 2];
figureeverythingout[ggpho3s, ggpho3spho, 10000, 3];

photoglue = 0.02;
figuremostthingsout[ggpho1s, ggpho1spho, 10000, 1];
figureeverythingout[ggpho2s, ggpho2spho, 10000, 2];
figureeverythingout[ggpho3s, ggpho3spho, 10000, 3];

photoglue = 0.03;

Display["decayplot_ee.eps",
	Show[GraphicsArray[{
	    Show[
		MultipleListPlot[point /@ ee1s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, MultipleListPlot[point /@ ee1spho
				   , SymbolStyle -> RGBColor[1,0,0]
				   , DisplayFunction -> Identity
				  ]
		, PlotRange -> range[ee1s, -2, 19]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 5], Automatic, None, None}
		, FrameLabel -> {None, None, "Upsilon(1S)", None}
		, AspectRatio -> Sqrt[2]
		, DisplayFunction -> Identity
		]
	    , Show[
		MultipleListPlot[point /@ ee2s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, MultipleListPlot[point /@ ee2spho
				   , SymbolStyle -> RGBColor[1,0,0]
				   , DisplayFunction -> Identity
				  ]
		, PlotRange -> range[Join[ee2spho, ee2s], -2, 19]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 5], Automatic, None, None}
		, FrameLabel -> {None, None, "Upsilon(2S)", None}
		, AspectRatio -> Sqrt[2]
		, DisplayFunction -> Identity
		  ]
	    , Show[
		MultipleListPlot[point /@ ee3s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, MultipleListPlot[point /@ ee3spho
				   , SymbolStyle -> RGBColor[1,0,0]
				   , DisplayFunction -> Identity
				  ]
		, PlotRange -> range[Join[ee3spho, ee3s], -10, 110]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 20], Automatic, None, None}
		, FrameLabel -> {None, None, "Upsilon(3S)", None}
		, AspectRatio -> Sqrt[2]
		, DisplayFunction -> Identity
		  ]
			   }]
	     , DisplayFunction -> $DisplayFunction
	    ], "EPS"
	, ImageSize -> 500
       ];

figureeverythingout[ee1s, ee1spho, 10000, 1];
figureeverythingout[ee2s, ee2spho, 10000, 2];
figureeverythingout[ee3s, ee3spho, 10000, 3];

Display["decayplot_mumu.eps",
	Show[GraphicsArray[{
	    Show[
		MultipleListPlot[point /@ mumu1s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, MultipleListPlot[point /@ mumu1spho
				   , SymbolStyle -> RGBColor[1,0,0]
				   , DisplayFunction -> Identity
				  ]
		, PlotRange -> range[mumu1s, -10, 110]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 20], Automatic, None, None}
		, FrameLabel -> {None, None, "Upsilon(1S)", None}
		, AspectRatio -> Sqrt[2]
		, DisplayFunction -> Identity
		]
	    , Show[
		MultipleListPlot[point /@ mumu2s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, MultipleListPlot[point /@ mumu2spho
				   , SymbolStyle -> RGBColor[1,0,0]
				   , DisplayFunction -> Identity
				  ]
		, PlotRange -> range[Join[mumu2spho, mumu2s], -10, 110]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 20], Automatic, None, None}
		, FrameLabel -> {None, None, "Upsilon(2S)", None}
		, AspectRatio -> Sqrt[2]
		, DisplayFunction -> Identity
		  ]
	    , Show[
		MultipleListPlot[point /@ mumu3s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, MultipleListPlot[point /@ mumu3spho
				   , SymbolStyle -> RGBColor[1,0,0]
				   , DisplayFunction -> Identity
				  ]
		, PlotRange -> range[Join[mumu3spho, mumu3s], -10, 110]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 20], Automatic, None, None}
		, FrameLabel -> {None, None, "Upsilon(3S)", None}
		, AspectRatio -> Sqrt[2]
		, DisplayFunction -> Identity
		  ]
			   }]
	     , DisplayFunction -> $DisplayFunction
	    ], "EPS"
	, ImageSize -> 500
       ];

figureeverythingout[mumu1s, mumu1spho, 10000, 1];
figureeverythingout[mumu2s, mumu2spho, 10000, 2];
figureeverythingout[mumu3s, mumu3spho, 10000, 3];

Display["decayplot_tautau.eps",
	Show[GraphicsArray[{
	    Show[
		MultipleListPlot[point /@ tautau1s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, MultipleListPlot[point /@ tautau1spho
				   , SymbolStyle -> RGBColor[1,0,0]
				   , DisplayFunction -> Identity
				  ]
		, PlotRange -> range[tautau1s, -10, 110]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 20], Automatic, None, None}
		, FrameLabel -> {None, None, "Upsilon(1S)", None}
		, AspectRatio -> Sqrt[2]
		, DisplayFunction -> Identity
		]
	    , Show[
		MultipleListPlot[point /@ tautau2s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, MultipleListPlot[point /@ tautau2spho
				   , SymbolStyle -> RGBColor[1,0,0]
				   , DisplayFunction -> Identity
				  ]
		, PlotRange -> range[Join[tautau2spho, tautau2s], -10, 110]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 20], Automatic, None, None}
		, FrameLabel -> {None, None, "Upsilon(2S)", None}
		, AspectRatio -> Sqrt[2]
		, DisplayFunction -> Identity
		  ]
	    , Show[
		MultipleListPlot[point /@ tautau3s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, MultipleListPlot[point /@ tautau3spho
				   , SymbolStyle -> RGBColor[1,0,0]
				   , DisplayFunction -> Identity
				  ]
		, PlotRange -> range[Join[tautau3spho, tautau3s], -10, 110]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 20], Automatic, None, None}
		, FrameLabel -> {None, None, "Upsilon(3S)", None}
		, AspectRatio -> Sqrt[2]
		, DisplayFunction -> Identity
		  ]
			   }]
	     , DisplayFunction -> $DisplayFunction
	    ], "EPS"
	, ImageSize -> 500
       ];

figureeverythingout[tautau1s, tautau1spho, 10000, 1];
figureeverythingout[tautau2s, tautau2spho, 10000, 2];
figureeverythingout[tautau3s, tautau3spho, 10000, 3];

Display["decayplot_taushape.eps",
	Show[GraphicsArray[{
	    Show[
		MultipleListPlot[point /@ taushape1s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, MultipleListPlot[point /@ taushape1spho
				   , SymbolStyle -> RGBColor[1,0,0]
				   , DisplayFunction -> Identity
				  ]
		, PlotRange -> range[taushape1s, -10, 110]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 20], Automatic, None, None}
		, FrameLabel -> {None, None, "Upsilon(1S)", None}
		, AspectRatio -> Sqrt[2]
		, DisplayFunction -> Identity
		]
	    , Show[
		MultipleListPlot[point /@ taushape2s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, MultipleListPlot[point /@ taushape2spho
				   , SymbolStyle -> RGBColor[1,0,0]
				   , DisplayFunction -> Identity
				  ]
		, PlotRange -> range[Join[taushape2spho, taushape2s], -10, 110]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 20], Automatic, None, None}
		, FrameLabel -> {None, None, "Upsilon(2S)", None}
		, AspectRatio -> Sqrt[2]
		, DisplayFunction -> Identity
		  ]
	    , Show[
		MultipleListPlot[point /@ taushape3s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, MultipleListPlot[point /@ taushape3spho
				   , SymbolStyle -> RGBColor[1,0,0]
				   , DisplayFunction -> Identity
				  ]
		, PlotRange -> range[Join[taushape3spho, taushape3s], -10, 110]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 20], Automatic, None, None}
		, FrameLabel -> {None, None, "Upsilon(3S)", None}
		, AspectRatio -> Sqrt[2]
		, DisplayFunction -> Identity
		  ]
			   }]
	     , DisplayFunction -> $DisplayFunction
	    ], "EPS"
	, ImageSize -> 500
       ];

figuretausout[tautau1s, taushape1s, tautau1spho, taushape1spho, 10000, 1];
figuretausout[tautau2s, taushape2s, tautau2spho, taushape2spho, 10000, 2];
figuretausout[tautau3s, taushape3s, tautau3spho, taushape3spho, 10000, 3];

(* Save this file, look at the lovely plots, save them in some convenient *)
(* format, make some documentation, proofread it, print it into your *)
(* notebook (along with the .pl and .m code), and send it off to Ritchie! *)

(* ********************************************************************************* *)

all1s = Join[ee1s, mumu1s, tautau1s, glue1s, ggpho1s];
all1spho = Join[ee1spho, mumu1spho, tautau1spho, glue1spho, ggpho1spho];
hadron1s = Select[all1s, ((#[[3]] != "0(1 95(7 8))")    &&
			  (#[[3]] != "0(1 95(11 12))")  &&
			  (#[[3]] != "0(1 95(15 16))")    )&];
hadron1spho = Select[all1spho, ((#[[3]] != "0(1 95(1 7 8))")      &&
				(#[[3]] != "0(1 95(1 1 7 8))")    &&
				(#[[3]] != "0(1 95(1 11 12))")    &&
				(#[[3]] != "0(1 95(1 1 11 12))")  &&
				(#[[3]] != "0(1 95(1 15 16))")    &&
				(#[[3]] != "0(1 95(1 1 15 16))")    )&];
all2s = Join[ee2s, mumu2s, tautau2s, glue2s, ggpho2s];
all2spho = Join[ee2spho, mumu2spho, tautau2spho, glue2spho, ggpho2spho];
hadron2s = Select[all2s, ((#[[3]] != "0(1 97(7 8))")    &&
			  (#[[3]] != "0(1 97(11 12))")  &&
			  (#[[3]] != "0(1 97(15 16))")    )&];
hadron2spho = Select[all2spho, ((#[[3]] != "0(1 97(1 7 8))")      &&
				(#[[3]] != "0(1 97(1 1 7 8))")    &&
				(#[[3]] != "0(1 97(1 11 12))")    &&
				(#[[3]] != "0(1 97(1 1 11 12))")  &&
				(#[[3]] != "0(1 97(1 15 16))")    &&
				(#[[3]] != "0(1 97(1 1 15 16))")    )&];
all3s = Join[ee3s, mumu3s, tautau3s, glue3s, ggpho3s];
all3spho = Join[ee3spho, mumu3spho, tautau3spho, glue3spho, ggpho3spho];
hadron3s = Select[all3s, ((#[[3]] != "0(1 98(7 8))")    &&
			  (#[[3]] != "0(1 98(11 12))")  &&
			  (#[[3]] != "0(1 98(15 16))")    )&];
hadron3spho = Select[all3spho, ((#[[3]] != "0(1 98(1 7 8))")      &&
				(#[[3]] != "0(1 98(1 1 7 8))")    &&
				(#[[3]] != "0(1 98(1 11 12))")    &&
				(#[[3]] != "0(1 98(1 1 11 12))")  &&
				(#[[3]] != "0(1 98(1 15 16))")    &&
				(#[[3]] != "0(1 98(1 1 15 16))")    )&];

jiggleworlds[mess_, all_, allpho_, res_, bmu_] := (
    aggeff = {};
    neventspho = (Plus @@ (#[[2]]& /@ allpho));
    avepho = 1 - ((Plus @@ (#[[1]]& /@ allpho))/neventspho);
    cascadeworldcounter = 0;
    Do[(
	If[bmu == {}, cascadeworld[], cascadeworld[bmu[[1]], bmu[[2]], bmu[[3]]]];
	tweakworld[res];
	ave = 1 - (failnumer[all]/denom[all]);
	nevents = (Plus @@ (#[[2]]& /@ all));
	aggeff = Append[aggeff, (ave    * (nevents    - photosfrac*neventspho) +
				 avepho * (neventspho + photosfrac*neventspho)
				)/(nevents + neventspho)];
       ),
       {1000}];
    Print["(* ", mess, " ", Mean[aggeff], " ", StandardDeviation[aggeff], " ", cascadeworldcounter, " *)"]
				     );
jigglemost[mess_, all_, res_, bmu_] := (
    aggeff = {};
    cascadeworldcounter = 0;
    Do[(
	If[bmu == {}, cascadeworld[], cascadeworld[bmu[[1]], bmu[[2]], bmu[[3]]]];
	tweakworld[res];
	ave = 1 - (failnumer[all]/denom[all]);
	nevents = (Plus @@ (#[[2]]& /@ all));
	aggeff = Append[aggeff, ave];
       ),
       {1000}];
    Print["(* ", mess, " ", Mean[aggeff], " ", StandardDeviation[aggeff], " ", cascadeworldcounter, " *)"]
				     );

{N[1 - (Plus @@ (#[[1]]& /@ Join[all1s, all1spho])) / (Plus @@ (#[[2]]& /@ Join[all1s, all1spho]))],
 N[1 - (Plus @@ (#[[1]]& /@ Join[hadron1s, hadron1spho])) / (Plus @@ (#[[2]]& /@ Join[hadron1s, hadron1spho]))]}

Out[22]= {0.907482, 0.962898}

{N[1 - (Plus @@ (#[[1]]& /@ Join[all2s, all2spho])) / (Plus @@ (#[[2]]& /@ Join[all2s, all2spho]))],
 N[1 - (Plus @@ (#[[1]]& /@ Join[hadron2s, hadron2spho])) / (Plus @@ (#[[2]]& /@ Join[hadron2s, hadron2spho]))]}

Out[23]= {0.919828, 0.951467}

{N[1 - (Plus @@ (#[[1]]& /@ Join[all1s, all3spho])) / (Plus @@ (#[[2]]& /@ Join[all3s, all3spho]))],
 N[1 - (Plus @@ (#[[1]]& /@ Join[hadron3s, hadron3spho])) / (Plus @@ (#[[2]]& /@ Join[hadron3s, hadron3spho]))]}

Out[24]= {0.868166, 0.961622}

istvan1s = {2.49, Sqrt[0.02^2+0.05^2]};
istvan2s = {2.03, Sqrt[0.03^2+0.05^2]};
istvan3s = {2.40, Sqrt[0.07^2+0.05^2]};
istvan = {istvan1s, istvan2s, istvan3s}

Out[25]= {{2.49, 0.0538516}, {2.03, 0.0583095}, {2.4, 0.0860233}}

photoglue = 0.03; photosfrac = -0.30; jiggleworlds["all PHOTOSfrac-", all1s, all1spho, 1, {}];
photoglue = 0.03; photosfrac =  0.30; jiggleworlds["all PHOTOSfrac+", all1s, all1spho, 1, {}];
Print[];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["all PDG", all1s, all1spho, 1, {}];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["all Istvan", all1s, all1spho, 1, istvan];
Print[];
photoglue = 0.02; photosfrac =  0.00; jiggleworlds["all ggg/ggp-", all1s, all1spho, 1, {}];
photoglue = 0.04; photosfrac =  0.00; jiggleworlds["all ggg/ggp+", all1s, all1spho, 1, {}];

(* all PHOTOSfrac- 0.913737 0.000854172 1000 *)
(* all PHOTOSfrac+ 0.906117 0.000827429 1000 *)

(* all PDG 0.909863 0.000837537 1000 *)
(* all Istvan 0.909762 0.00089542 1000 *)

(* all ggg/ggp- 0.915857 0.000841985 1000 *)
(* all ggg/ggp+ 0.903982 0.000810311 1000 *)

photoglue = 0.03; photosfrac =  0.00; jigglemost["hadron PDG", hadron1s, 1, {}];
photoglue = 0.03; photosfrac =  0.00; jigglemost["hadron Istvan", hadron1s, 1, istvan];
Print[];
photoglue = 0.02; photosfrac =  0.00; jigglemost["hadron ggg/ggp-", hadron1s, 1, {}];
photoglue = 0.04; photosfrac =  0.00; jigglemost["hadron ggg/ggp+", hadron1s, 1, {}];

                                 -14
(* hadron PDG 0.963936 1.93275 10    1000 *)
                                    -14
(* hadron Istvan 0.963936 1.93275 10    1000 *)

                                      -15
(* hadron ggg/ggp- 0.970372 8.10868 10    1000 *)
                                     -14
(* hadron ggg/ggp+ 0.957499 1.9582 10    1000 *)

photoglue = 0.03; photosfrac = -0.30; jiggleworlds["all PHOTOSfrac-", all2s, all2spho, 2, {}];
photoglue = 0.03; photosfrac =  0.30; jiggleworlds["all PHOTOSfrac+", all2s, all2spho, 2, {}];
Print[];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["all PDG", all2s, all2spho, 2, {}];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["all Istvan", all2s, all2spho, 2, istvan];
Print[];
photoglue = 0.02; photosfrac =  0.00; jiggleworlds["all ggg/ggp-", all2s, all2spho, 2, {}];
photoglue = 0.04; photosfrac =  0.00; jiggleworlds["all ggg/ggp+", all2s, all2spho, 2, {}];

(* all PHOTOSfrac- 0.928076 0.00247395 1000 *)
(* all PHOTOSfrac+ 0.921348 0.00225865 1000 *)

(* all PDG 0.924591 0.00238587 1000 *)
(* all Istvan 0.911678 0.00112138 1000 *)

(* all ggg/ggp- 0.930002 0.00239129 1000 *)
(* all ggg/ggp+ 0.919314 0.0023059 1000 *)

photoglue = 0.03; photosfrac = -0.30; jiggleworlds["hadron PHOTOSfrac-", hadron2s, hadron2spho, 2, {}];
photoglue = 0.03; photosfrac =  0.30; jiggleworlds["hadron PHOTOSfrac+", hadron2s, hadron2spho, 2, {}];
Print[];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["hadron PDG", hadron2s, hadron2spho, 2, {}];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["hadron Istvan", hadron2s, hadron2spho, 2, istvan];
Print[];
photoglue = 0.02; photosfrac =  0.00; jiggleworlds["hadron ggg/ggp-", hadron2s, hadron2spho, 2, {}];
photoglue = 0.04; photosfrac =  0.00; jiggleworlds["hadron ggg/ggp+", hadron2s, hadron2spho, 2, {}];

(* hadron PHOTOSfrac- 0.953724 0.000582614 1000 *)
(* hadron PHOTOSfrac+ 0.951359 0.000575084 1000 *)

(* hadron PDG 0.952516 0.000604708 1000 *)
(* hadron Istvan 0.95226 0.000614453 1000 *)

(* hadron ggg/ggp- 0.95802 0.00058254 1000 *)
(* hadron ggg/ggp+ 0.946976 0.000639758 1000 *)

photoglue = 0.03; photosfrac = -0.30; jiggleworlds["all PHOTOSfrac-", all3s, all3spho, 3, {}];
photoglue = 0.03; photosfrac =  0.30; jiggleworlds["all PHOTOSfrac+", all3s, all3spho, 3, {}];
Print[];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["all PDG", all3s, all3spho, 3, {}];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["all Istvan", all3s, all3spho, 3, istvan];
Print[];
photoglue = 0.02; photosfrac =  0.00; jiggleworlds["all ggg/ggp-", all3s, all3spho, 3, {}];
photoglue = 0.04; photosfrac =  0.00; jiggleworlds["all ggg/ggp+", all3s, all3spho, 3, {}];

(* all PHOTOSfrac- 0.925908 0.00299896 1000 *)
(* all PHOTOSfrac+ 0.91917 0.00286168 1000 *)

(* all PDG 0.92255 0.00285108 1000 *)
(* all Istvan 0.910599 0.00165083 1000 *)

(* all ggg/ggp- 0.927104 0.00308911 1000 *)
(* all ggg/ggp+ 0.918075 0.0029445 1000 *)

photoglue = 0.03; photosfrac = -0.30; jiggleworlds["hadron PHOTOSfrac-", hadron3s, hadron3spho, 3, {}];
photoglue = 0.03; photosfrac =  0.30; jiggleworlds["hadron PHOTOSfrac+", hadron3s, hadron3spho, 3, {}];
Print[];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["hadron PDG", hadron3s, hadron3spho, 3, {}];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["hadron Istvan", hadron3s, hadron3spho, 3, istvan];
Print[];
photoglue = 0.02; photosfrac =  0.00; jiggleworlds["hadron ggg/ggp-", hadron3s, hadron3spho, 3, {}];
photoglue = 0.04; photosfrac =  0.00; jiggleworlds["hadron ggg/ggp+", hadron3s, hadron3spho, 3, {}];

(* hadron PHOTOSfrac- 0.962763 0.000555669 1000 *)
(* hadron PHOTOSfrac+ 0.961093 0.000577483 1000 *)

(* hadron PDG 0.961953 0.000574447 1000 *)
(* hadron Istvan 0.959948 0.000600337 1000 *)

(* hadron ggg/ggp- 0.966806 0.000551688 1000 *)
(* hadron ggg/ggp+ 0.957011 0.000603586 1000 *)

(* OOPS!  I need statistical errors, too! *)

nevents = (Plus @@ (#[[2]]& /@ Join[all1s, all1spho]));
theeff = 1 - (Plus @@ (#[[1]]& /@ Join[all1s, all1spho]))/nevents;
Print["(* all1s ", N[theeff], " ", N[Sqrt[theeff*(1 - theeff)/nevents]], " *)"];
nevents = (Plus @@ (#[[2]]& /@ Join[hadron1s, hadron1spho]));
theeff = 1 - (Plus @@ (#[[1]]& /@ Join[hadron1s, hadron1spho]))/nevents;
Print["(* hadron1s ", N[theeff], " ", N[Sqrt[theeff*(1 - theeff)/nevents]], " *)"];

(* all1s 0.907482 0.00073522 *)
(* hadron1s 0.962898 0.000499199 *)

nevents = (Plus @@ (#[[2]]& /@ Join[all2s, all2spho]));
theeff = 1 - (Plus @@ (#[[1]]& /@ Join[all2s, all2spho]))/nevents;
Print["(* all2s ", N[theeff], " ", N[Sqrt[theeff*(1 - theeff)/nevents]], " *)"];
nevents = (Plus @@ (#[[2]]& /@ Join[hadron2s, hadron2spho]));
theeff = 1 - (Plus @@ (#[[1]]& /@ Join[hadron2s, hadron2spho]))/nevents;
Print["(* hadron2s ", N[theeff], " ", N[Sqrt[theeff*(1 - theeff)/nevents]], " *)"];

(* all2s 0.919828 0.000633454 *)
(* hadron2s 0.951467 0.000512843 *)

nevents = (Plus @@ (#[[2]]& /@ Join[all3s, all3spho]));
theeff = 1 - (Plus @@ (#[[1]]& /@ Join[all3s, all3spho]))/nevents;
Print["(* all3s ", N[theeff], " ", N[Sqrt[theeff*(1 - theeff)/nevents]], " *)"];
nevents = (Plus @@ (#[[2]]& /@ Join[hadron3s, hadron3spho]));
theeff = 1 - (Plus @@ (#[[1]]& /@ Join[hadron3s, hadron3spho]))/nevents;
Print["(* hadron3s ", N[theeff], " ", N[Sqrt[theeff*(1 - theeff)/nevents]], " *)"];

(* all3s 0.922983 0.000834166 *)
(* hadron3s 0.961622 0.000616954 *)
