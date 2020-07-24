<< Graphics`MultipleListPlot`;
<< Statistics`ContinuousDistributions`;
<< Graphics`Graphics`;

glue1s = 0.9963;
glue2s = 0.9968;
glue3s = 0.9971;
glpho1s = 0.8078;
glpho2s = 0.8078;
glpho3s = 0.8078;
gfac = 0.0320/0.91;
ee2s0 = N[1/975];
ee2s1 = N[7/338];
ee2s2 = N[10/161];
ee3s0 = N[1/347];
ee3s1 = N[7/126];
ee3s2 = N[3/49];
mm2s0 = N[73/1184];
mm2s1 = N[72/269];
mm2s2 = N[14/35];
mm3s0 = N[41/462];
mm3s1 = N[25/104];
mm3s2 = N[4/14];
ee1p = 0.25*1.5;
ee2p = 0.10*1.5;
ee0p = 1 - ee1p - ee2p;
mm1p = 0.18*1.5;
mm2p = 0.025*1.5;
mm0p = 1 - mm1p - mm2p;
br2 = 0.00795;
br3 = 0.0048;
eff1 = (glue1s*(1-gfac) + glpho1s*gfac);
eff2 = (glue2s*(1-gfac) + glpho2s*gfac)*(1-br2-br2-br2) + 1*br2 +
    br2*(ee0p*ee2s0 + ee1p*ee2s1 + ee2p*ee2s2) +
    br2*(mm0p*mm2s0 + mm1p*mm2s1 + mm2p*mm2s2);
eff3 = (glue3s*(1-gfac) + glpho3s*gfac)*(1-br3-br3-br3) + 1*br3 +
    br3*(ee0p*ee3s0 + ee1p*ee3s1 + ee2p*ee3s2) +
    br3*(mm0p*mm3s0 + mm1p*mm3s1 + mm2p*mm3s2);
Print[eff1];
Print[eff2];
Print[eff3];

0.989671
0.975662
0.98179

0.990268
0.976245
0.98238

0.990811
0.976777
0.982917






0.98942
0.975415
0.98154

0.990268
0.976245
0.98238

Exit

[Mathematica finished.]








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
	    , PlotRange -> range[glue1s, 97, 101]
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
	    , PlotRange -> range[Join[glue2spho, glue2s], 97, 101]
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
	    , PlotRange -> range[Join[glue3spho, glue3s], 89, 101]
	    , Axes -> False
	    , Frame -> True
	    , FrameTicks -> {Range[0, 100, 2], Automatic, None, None}
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

Average   Error       Toy MC    MC RMS          Denom     Denom RMS   Events

                                          -12
99.7521   0.0163265   99.7521   9.29303 10      89.7833   0.0843955   92775

0         0           n/a       n/a             n/a       n/a         0

Mode efficiency = 99.7521 +/- 0.0163265

Average   Error       Toy MC   MC RMS       Denom     Denom RMS   Events

99.8184   0.0137924   99.821   0.00336042   91.4753   0.256979    95277

100.      0.          n/a      n/a          n/a       n/a         198

Mode efficiency = 99.8213 +/- 0.0141664
Mode efficiency = 99.8214 with 30% more PHOTOS
Mode efficiency = 99.8212 with 30% less PHOTOS

Average   Error       Toy MC    MC RMS       Denom     Denom RMS   Events

99.8209   0.0138039   99.8224   0.00165623   90.9136   0.302563    93813

100.      0.          n/a       n/a          n/a       n/a         117

Mode efficiency = 99.8226 +/- 0.0138856
Mode efficiency = 99.8227 with 30% more PHOTOS
Mode efficiency = 99.8225 with 30% less PHOTOS


photoglue = 0.04;
figuremostthingsout[glue1s, glue1spho, 10000, 1];
figureeverythingout[glue2s, glue2spho, 10000, 2];
figureeverythingout[glue3s, glue3spho, 10000, 3];

Average   Error       Toy MC    MC RMS          Denom     Denom RMS   Events

                                          -12
99.7521   0.0163265   99.7521   9.29303 10      88.8573   0.0832025   92775

0         0           n/a       n/a             n/a       n/a         0

Mode efficiency = 99.7521 +/- 0.0163265

Average   Error       Toy MC    MC RMS       Denom     Denom RMS   Events

99.8184   0.0137924   99.8208   0.00340265   90.6688   0.252322    95277

100.      0.          n/a       n/a          n/a       n/a         198

Mode efficiency = 99.8212 +/- 0.0141765
Mode efficiency = 99.8213 with 30% more PHOTOS
Mode efficiency = 99.821 with 30% less PHOTOS

Average   Error       Toy MC    MC RMS       Denom    Denom RMS   Events

99.8209   0.0138039   99.8223   0.00166402   90.216   0.296772    93813

100.      0.          n/a       n/a          n/a      n/a         117

Mode efficiency = 99.8225 +/- 0.0138865
Mode efficiency = 99.8225 with 30% more PHOTOS
Mode efficiency = 99.8224 with 30% less PHOTOS


photoglue = 0.02;
figuremostthingsout[glue1s, glue1spho, 10000, 1];
figureeverythingout[glue2s, glue2spho, 10000, 2];
figureeverythingout[glue3s, glue3spho, 10000, 3];

Average   Error       Toy MC    MC RMS          Denom     Denom RMS   Events

                                          -12
99.7521   0.0163265   99.7521   9.29303 10      90.7093   0.0847548   92775

0         0           n/a       n/a             n/a       n/a         0

Mode efficiency = 99.7521 +/- 0.0163265

Average   Error       Toy MC    MC RMS       Denom     Denom RMS   Events

99.8184   0.0137924   99.8211   0.00334605   92.2795   0.253239    95277

100.      0.          n/a       n/a          n/a       n/a         198

Mode efficiency = 99.8215 +/- 0.014163
Mode efficiency = 99.8216 with 30% more PHOTOS
Mode efficiency = 99.8214 with 30% less PHOTOS

Average   Error       Toy MC    MC RMS       Denom     Denom RMS   Events

99.8209   0.0138039   99.8225   0.00165032   91.6188   0.30435     93813

100.      0.          n/a       n/a          n/a       n/a         117

Mode efficiency = 99.8227 +/- 0.0138849
Mode efficiency = 99.8227 with 30% more PHOTOS
Mode efficiency = 99.8226 with 30% less PHOTOS


Display["decayplot_ggpho.eps",
	Show[GraphicsArray[{
	    Show[
		MultipleListPlot[point /@ ggpho1s
				 , SymbolStyle -> GrayLevel[0]
				 , DisplayFunction -> Identity
				]
		, PlotRange -> range[ggpho1s, 72, 103]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 5], Automatic, None, None}
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
		, PlotRange -> range[Join[ggpho2spho, ggpho2s], 72, 103]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 5], Automatic, None, None}
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

Average   Error      Toy MC    MC RMS          Denom     Denom RMS    Events

                                         -12
88.5149   0.579235   88.5149   8.28268 10      2.77685   0.00259022   3030

0         0          n/a       n/a             n/a       n/a          0

Mode efficiency = 88.5149 +/- 0.579235

Average   Error      Toy MC    MC RMS      Denom     Denom RMS   Events

89.1264   0.597674   89.1478   0.0418412   2.41023   0.0324918   2713

100.      0.         n/a       n/a         n/a       n/a         2

Mode efficiency = 89.1558 +/- 0.598695
Mode efficiency = 89.1582 with 30% more PHOTOS
Mode efficiency = 89.1534 with 30% less PHOTOS

Average   Error      Toy MC    MC RMS      Denom     Denom RMS   Events

89.0449   0.675789   89.1392   0.0907655   2.09139   0.0346844   2136

100.      0.         n/a       n/a         n/a       n/a         9

Mode efficiency = 89.1848 +/- 0.678984
Mode efficiency = 89.1984 with 30% more PHOTOS
Mode efficiency = 89.1711 with 30% less PHOTOS


photoglue = 0.04;
figuremostthingsout[ggpho1s, ggpho1spho, 10000, 1];
figureeverythingout[ggpho2s, ggpho2spho, 10000, 2];
figureeverythingout[ggpho3s, ggpho3spho, 10000, 3];

Average   Error      Toy MC    MC RMS          Denom     Denom RMS    Events

                                         -12
88.5149   0.579235   88.5149   8.28268 10      3.70244   0.00347612   3030

0         0          n/a       n/a             n/a       n/a          0

Mode efficiency = 88.5149 +/- 0.579235

Average   Error      Toy MC    MC RMS      Denom     Denom RMS   Events

89.1264   0.597674   89.1476   0.0420049   3.21304   0.0435531   2713

100.      0.         n/a       n/a         n/a       n/a         2

Mode efficiency = 89.1556 +/- 0.598706
Mode efficiency = 89.158 with 30% more PHOTOS
Mode efficiency = 89.1532 with 30% less PHOTOS

Average   Error      Toy MC    MC RMS      Denom     Denom RMS   Events

89.0449   0.675789   89.1375   0.0906812   2.78916   0.046559    2136

100.      0.         n/a       n/a         n/a       n/a         9

Mode efficiency = 89.1831 +/- 0.678973
Mode efficiency = 89.1968 with 30% more PHOTOS
Mode efficiency = 89.1694 with 30% less PHOTOS


photoglue = 0.02;
figuremostthingsout[ggpho1s, ggpho1spho, 10000, 1];
figureeverythingout[ggpho2s, ggpho2spho, 10000, 2];
figureeverythingout[ggpho3s, ggpho3spho, 10000, 3];

Average   Error      Toy MC    MC RMS          Denom     Denom RMS    Events

                                         -12
88.5149   0.579235   88.5149   8.28268 10      1.85121   0.00174187   3030

0         0          n/a       n/a             n/a       n/a          0

Mode efficiency = 88.5149 +/- 0.579235

Average   Error      Toy MC    MC RMS      Denom     Denom RMS   Events

89.1264   0.597674   89.1488   0.0417201   1.60636   0.0217985   2713

100.      0.         n/a       n/a         n/a       n/a         2

Mode efficiency = 89.1568 +/- 0.598686
Mode efficiency = 89.1592 with 30% more PHOTOS
Mode efficiency = 89.1544 with 30% less PHOTOS

Average   Error      Toy MC    MC RMS      Denom     Denom RMS   Events

89.0449   0.675789   89.1384   0.0903493   1.39447   0.0231804   2136

100.      0.         n/a       n/a         n/a       n/a         9

Mode efficiency = 89.184 +/- 0.678929
Mode efficiency = 89.1976 with 30% more PHOTOS
Mode efficiency = 89.1703 with 30% less PHOTOS


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
		, PlotRange -> range[ee1s, -10, 110]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 20], Automatic, None, None}
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
		, PlotRange -> range[Join[ee2spho, ee2s], -10, 110]
		, Axes -> False
		, Frame -> True
		, FrameTicks -> {Range[0, 100, 20], Automatic, None, None}
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

Average   Error      Toy MC    MC RMS         Denom     Denom RMS   Events

                                        -14
4.89039   0.511324   4.89039   1.9874 10      2.47928   0.0500846   1779

7.61523   0.839608   n/a       n/a            n/a       n/a         998

Mode efficiency = 5.86964 +/- 0.629303
Mode efficiency = 6.16342 with 30% more PHOTOS
Mode efficiency = 5.57587 with 30% less PHOTOS

Average   Error      Toy MC    MC RMS      Denom     Denom RMS   Events

5.62092   0.588838   5.66342   0.0613099   2.03964   0.143064    1530

11.8701   1.08234    n/a       n/a         n/a       n/a         893

Mode efficiency = 7.9509 +/- 0.772698
Mode efficiency = 8.63715 with 30% more PHOTOS
Mode efficiency = 7.26466 with 30% less PHOTOS

Average   Error      Toy MC    MC RMS     Denom    Denom RMS   Events

4.91493   0.542658   4.54923   0.114911   2.3042   0.174919    1587

7.23606   0.892333   n/a       n/a        n/a      n/a         843

Mode efficiency = 5.48133 +/- 0.673122
Mode efficiency = 5.76096 with 30% more PHOTOS
Mode efficiency = 5.2017 with 30% less PHOTOS


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

Average     Error       Toy MC      MC RMS          Denom     Denom RMS    Events

                                              -15
0.0461894   0.0461787   0.0461894   8.56924 10      2.48017   0.0497311      2165

14.0187     1.50099     n/a         n/a             n/a       n/a             535

Mode efficiency = 2.81481 +/- 0.334448
Mode efficiency = 3.6454 with 30% more PHOTOS
Mode efficiency = 1.98423 with 30% less PHOTOS

Average   Error      Toy MC    MC RMS      Denom     Denom RMS   Events

1.02934   0.228979   1.10786   0.0757834   2.03891   0.144937    1943

14.9474   1.63599    n/a       n/a         n/a       n/a         475

Mode efficiency = 3.82654 +/- 0.513879
Mode efficiency = 4.64214 with 30% more PHOTOS
Mode efficiency = 3.01094 with 30% less PHOTOS

Average    Error      Toy MC     MC RMS     Denom     Denom RMS   Events

0.863931   0.215048   0.940073   0.111351   2.30936   0.175084    1852

16.7969    1.65215    n/a        n/a        n/a       n/a         512

Mode efficiency = 4.37437 +/- 0.5444
Mode efficiency = 5.40466 with 30% more PHOTOS
Mode efficiency = 3.34408 with 30% less PHOTOS


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

Average   Error      Toy MC    MC RMS          Denom     Denom RMS   Events

                                         -11
66.0983   0.942613   66.0983   1.06174 10      2.48084   0.0499575   2522

72.2892   3.47382    n/a       n/a             n/a       n/a         166

Mode efficiency = 66.4807 +/- 1.09893
Mode efficiency = 66.5954 with 30% more PHOTOS
Mode efficiency = 66.366 with 30% less PHOTOS

Average   Error      Toy MC    MC RMS     Denom     Denom RMS   Events

69.1021   0.969406   69.7937   0.321812   2.04058   0.143837    2272

74.8299   3.57949    n/a       n/a        n/a       n/a         147

Mode efficiency = 70.0997 +/- 1.17594
Mode efficiency = 70.1915 with 30% more PHOTOS
Mode efficiency = 70.0079 with 30% less PHOTOS

Average   Error     Toy MC    MC RMS     Denom     Denom RMS   Events

68.4211   1.05589   67.9661   0.324151   2.31612   0.17712     1938

65.2778   3.96739   n/a       n/a        n/a       n/a         144

Mode efficiency = 67.7801 +/- 1.30312
Mode efficiency = 67.7244 with 30% more PHOTOS
Mode efficiency = 67.8359 with 30% less PHOTOS


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

Average   Error      Toy MC    MC RMS     Denom     Denom RMS   Events

66.0983   0.942613   65.9833   0.088365   2.48118   0.0501215   2522

72.2892   3.47382    n/a       n/a        n/a       n/a         166

Mode efficiency = 66.3727 +/- 1.10282
Mode efficiency = 66.4895 with 30% more PHOTOS
Mode efficiency = 66.2559 with 30% less PHOTOS

Average   Error      Toy MC    MC RMS     Denom     Denom RMS   Events

69.1021   0.969406   70.2368   0.443722   2.03937   0.14367     2272

74.8299   3.57949    n/a       n/a        n/a       n/a         147

Mode efficiency = 70.5159 +/- 1.21608
Mode efficiency = 70.5997 with 30% more PHOTOS
Mode efficiency = 70.4322 with 30% less PHOTOS

Average   Error     Toy MC    MC RMS     Denom     Denom RMS   Events

68.4211   1.05589   69.6412   0.516315   2.31695   0.173946    1938

65.2778   3.96739   n/a       n/a        n/a       n/a         144

Mode efficiency = 69.3395 +/- 1.3648
Mode efficiency = 69.2489 with 30% more PHOTOS
Mode efficiency = 69.43 with 30% less PHOTOS

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

Out[316]= {0.935395, 0.993967}

{N[1 - (Plus @@ (#[[1]]& /@ Join[all2s, all2spho])) / (Plus @@ (#[[2]]& /@ Join[all2s, all2spho]))],
 N[1 - (Plus @@ (#[[1]]& /@ Join[hadron2s, hadron2spho])) / (Plus @@ (#[[2]]& /@ Join[hadron2s, hadron2spho]))]}

Out[317]= {0.94533, 0.977799}

{N[1 - (Plus @@ (#[[1]]& /@ Join[all1s, all3spho])) / (Plus @@ (#[[2]]& /@ Join[all3s, all3spho]))],
 N[1 - (Plus @@ (#[[1]]& /@ Join[hadron3s, hadron3spho])) / (Plus @@ (#[[2]]& /@ Join[hadron3s, hadron3spho]))]}

Out[318]= {0.936407, 0.984024}

istvan1s = {2.49, Sqrt[0.02^2+0.05^2]};
istvan2s = {2.03, Sqrt[0.03^2+0.05^2]};
istvan3s = {2.40, Sqrt[0.07^2+0.05^2]};
istvan = {istvan1s, istvan2s, istvan3s}

Out[352]= {{2.49, 0.0538516}, {2.03, 0.0583095}, {2.4, 0.0860233}}

photoglue = 0.03; photosfrac = -0.30; jiggleworlds["all PHOTOSfrac-", all1s, all1spho, 1, {}];
photoglue = 0.03; photosfrac =  0.30; jiggleworlds["all PHOTOSfrac+", all1s, all1spho, 1, {}];
Print[];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["all PDG", all1s, all1spho, 1, {}];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["all Istvan", all1s, all1spho, 1, istvan];
Print[];
photoglue = 0.02; photosfrac =  0.00; jiggleworlds["all ggg/ggp-", all1s, all1spho, 1, {}];
photoglue = 0.04; photosfrac =  0.00; jiggleworlds["all ggg/ggp+", all1s, all1spho, 1, {}];

(* all PHOTOSfrac- 0.941894 0.000859718 1000 *)
(* all PHOTOSfrac+ 0.934142 0.000855804 1000 *)

(* all PDG 0.938022 0.000874017 1000 *)
(* all Istvan 0.937809 0.000940222 1000 *)

(* all ggg/ggp- 0.939093 0.000858267 1000 *)
(* all ggg/ggp+ 0.937033 0.000881195 1000 *)

photoglue = 0.03; photosfrac =  0.00; jigglemost["hadron PDG", hadron1s, 1, {}];
photoglue = 0.03; photosfrac =  0.00; jigglemost["hadron Istvan", hadron1s, 1, istvan];
Print[];
photoglue = 0.02; photosfrac =  0.00; jigglemost["hadron ggg/ggp-", hadron1s, 1, {}];
photoglue = 0.04; photosfrac =  0.00; jigglemost["hadron ggg/ggp+", hadron1s, 1, {}];

                                -14
(* hadron PDG 0.99415 1.11078 10    1000 *)
                                   -14
(* hadron Istvan 0.99415 1.11078 10    1000 *)

                                      -14
(* hadron ggg/ggp- 0.995273 1.16874 10    1000 *)
                                      -14
(* hadron ggg/ggp+ 0.993026 2.15818 10    1000 *)

photoglue = 0.03; photosfrac = -0.30; jiggleworlds["all PHOTOSfrac-", all2s, all2spho, 2, {}];
photoglue = 0.03; photosfrac =  0.30; jiggleworlds["all PHOTOSfrac+", all2s, all2spho, 2, {}];
Print[];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["all PDG", all2s, all2spho, 2, {}];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["all Istvan", all2s, all2spho, 2, istvan];
Print[];
photoglue = 0.02; photosfrac =  0.00; jiggleworlds["all ggg/ggp-", all2s, all2spho, 2, {}];
photoglue = 0.04; photosfrac =  0.00; jiggleworlds["all ggg/ggp+", all2s, all2spho, 2, {}];

(* all PHOTOSfrac- 0.953362 0.00259065 1000 *)
(* all PHOTOSfrac+ 0.946854 0.00248099 1000 *)

(* all PDG 0.950024 0.00245939 1000 *)
(* all Istvan 0.936497 0.00114615 1000 *)

(* all ggg/ggp- 0.950863 0.00259859 1000 *)
(* all ggg/ggp+ 0.949192 0.00243808 1000 *)

photoglue = 0.03; photosfrac = -0.30; jiggleworlds["hadron PHOTOSfrac-", hadron2s, hadron2spho, 2, {}];
photoglue = 0.03; photosfrac =  0.30; jiggleworlds["hadron PHOTOSfrac+", hadron2s, hadron2spho, 2, {}];
Print[];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["hadron PDG", hadron2s, hadron2spho, 2, {}];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["hadron Istvan", hadron2s, hadron2spho, 2, istvan];
Print[];
photoglue = 0.02; photosfrac =  0.00; jiggleworlds["hadron ggg/ggp-", hadron2s, hadron2spho, 2, {}];
photoglue = 0.04; photosfrac =  0.00; jiggleworlds["hadron ggg/ggp+", hadron2s, hadron2spho, 2, {}];

(* hadron PHOTOSfrac- 0.979669 0.000566922 1000 *)
(* hadron PHOTOSfrac+ 0.977301 0.000595771 1000 *)

(* hadron PDG 0.978484 0.000563845 1000 *)
(* hadron Istvan 0.978121 0.000599702 1000 *)

(* hadron ggg/ggp- 0.979349 0.000582077 1000 *)
(* hadron ggg/ggp+ 0.977577 0.00055779 1000 *)

photoglue = 0.03; photosfrac = -0.30; jiggleworlds["all PHOTOSfrac-", all3s, all3spho, 3, {}];
photoglue = 0.03; photosfrac =  0.30; jiggleworlds["all PHOTOSfrac+", all3s, all3spho, 3, {}];
Print[];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["all PDG", all3s, all3spho, 3, {}];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["all Istvan", all3s, all3spho, 3, istvan];
Print[];
photoglue = 0.02; photosfrac =  0.00; jiggleworlds["all ggg/ggp-", all3s, all3spho, 3, {}];
photoglue = 0.04; photosfrac =  0.00; jiggleworlds["all ggg/ggp+", all3s, all3spho, 3, {}];

(* all PHOTOSfrac- 0.948311 0.00314023 1000 *)
(* all PHOTOSfrac+ 0.941455 0.00307068 1000 *)

(* all PDG 0.944834 0.00301735 1000 *)
(* all Istvan 0.93245 0.0016751 1000 *)

(* all ggg/ggp- 0.945608 0.00303778 1000 *)
(* all ggg/ggp+ 0.943907 0.00314825 1000 *)

photoglue = 0.03; photosfrac = -0.30; jiggleworlds["hadron PHOTOSfrac-", hadron3s, hadron3spho, 3, {}];
photoglue = 0.03; photosfrac =  0.30; jiggleworlds["hadron PHOTOSfrac+", hadron3s, hadron3spho, 3, {}];
Print[];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["hadron PDG", hadron3s, hadron3spho, 3, {}];
photoglue = 0.03; photosfrac =  0.00; jiggleworlds["hadron Istvan", hadron3s, hadron3spho, 3, istvan];
Print[];
photoglue = 0.02; photosfrac =  0.00; jiggleworlds["hadron ggg/ggp-", hadron3s, hadron3spho, 3, {}];
photoglue = 0.04; photosfrac =  0.00; jiggleworlds["hadron ggg/ggp+", hadron3s, hadron3spho, 3, {}];

(* hadron PHOTOSfrac- 0.985836 0.000545016 1000 *)
(* hadron PHOTOSfrac+ 0.984205 0.000557743 1000 *)

(* hadron PDG 0.985044 0.000552458 1000 *)
(* hadron Istvan 0.982918 0.000626099 1000 *)

(* hadron ggg/ggp- 0.9858 0.00054221 1000 *)
(* hadron ggg/ggp+ 0.984253 0.000533174 1000 *)

(* OOPS!  I need statistical errors, too! *)

nevents = (Plus @@ (#[[2]]& /@ Join[all1s, all1spho]));
theeff = 1 - (Plus @@ (#[[1]]& /@ Join[all1s, all1spho]))/nevents;
Print["(* all1s ", N[theeff], " ", N[Sqrt[theeff*(1 - theeff)/nevents]], " *)"];
nevents = (Plus @@ (#[[2]]& /@ Join[hadron1s, hadron1spho]));
theeff = 1 - (Plus @@ (#[[1]]& /@ Join[hadron1s, hadron1spho]))/nevents;
Print["(* hadron1s ", N[theeff], " ", N[Sqrt[theeff*(1 - theeff)/nevents]], " *)"];

(* all1s 0.935395 0.00076239 *)
(* hadron1s 0.993967 0.000250185 *)

nevents = (Plus @@ (#[[2]]& /@ Join[all2s, all2spho]));
theeff = 1 - (Plus @@ (#[[1]]& /@ Join[all2s, all2spho]))/nevents;
Print["(* all2s ", N[theeff], " ", N[Sqrt[theeff*(1 - theeff)/nevents]], " *)"];
nevents = (Plus @@ (#[[2]]& /@ Join[hadron2s, hadron2spho]));
theeff = 1 - (Plus @@ (#[[1]]& /@ Join[hadron2s, hadron2spho]))/nevents;
Print["(* hadron2s ", N[theeff], " ", N[Sqrt[theeff*(1 - theeff)/nevents]], " *)"];

(* all2s 0.94533 0.000700075 *)
(* hadron2s 0.977799 0.000464252 *)

nevents = (Plus @@ (#[[2]]& /@ Join[all3s, all3spho]));
theeff = 1 - (Plus @@ (#[[1]]& /@ Join[all3s, all3spho]))/nevents;
Print["(* all3s ", N[theeff], " ", N[Sqrt[theeff*(1 - theeff)/nevents]], " *)"];
nevents = (Plus @@ (#[[2]]& /@ Join[hadron3s, hadron3spho]));
theeff = 1 - (Plus @@ (#[[1]]& /@ Join[hadron3s, hadron3spho]))/nevents;
Print["(* hadron3s ", N[theeff], " ", N[Sqrt[theeff*(1 - theeff)/nevents]], " *)"];

(* all3s 0.94544 0.000707846 *)
(* hadron3s 0.984024 0.000400986 *)








$   \Upsilon(3S) \to e^+ e^-                                                                                           $ & $   0.0239      $ & $   0.0012     $ \\ 

$   \Upsilon(3S) \to \mu^+ \mu^-                                                                                       $ & $   0.0239      $ & $   0.0012     $ \\ 







Sqrt[Plus @@ ((#^2)& /@ {
0.000062   ,
0.000072   ,
0.00012    ,
0.000029   ,
0.000015   ,
2.6 10*^-7 ,
5.6 10*^-6 ,
3.2 10*^-6 ,
0.000066   ,
0.000015   ,
8.3 10*^-6 ,
1.8 10*^-7 ,
3.6 10*^-6 ,
2.0 10*^-6 ,
0.000083   ,
0.000024   ,
5.5 10*^-6 ,
2.7 10*^-6 ,
2.9 10*^-8 ,
8.1 10*^-7 ,
5.0 10*^-7 ,
0.000039   ,
0.000098   ,
0.000023   ,
0.000012   ,
2.2 10*^-7 ,
4.6 10*^-6 ,
2.6 10*^-6 ,
0.000032   ,
0.000064   ,
0.000015   ,
7.9 10*^-6 ,
1.7 10*^-7 ,
3.4 10*^-6 ,
1.9 10*^-6 })]

Out[12]= 0.000284325

Out[11]= 0.00123322

Out[10]= 0.000284325





   0.0574         0.0025     

Exit

[Mathematica finished.]
