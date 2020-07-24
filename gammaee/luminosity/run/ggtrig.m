<< Graphics`Graphics`;
<< Graphics`MultipleListPlot`;
weight = {1380, 1389, 1371, 1392, 1305, 1402, 1328, 1431, 1370, 1346,
	  1388, 1379, 1345, 1368, 1446, 1350, 1364, 1356, 1381, 1384,
	  1323, 1354, 1357, 1324, 1358, 1454, 1341, 1449, 1471, 1377,
	  1397, 1381, 1357, 1394, 1388, 1422, 1446, 1422, 1416, 1439,
	  1396, 1385, 1386, 1437, 1378, 1458, 1382, 1432, 1495, 1474,
	  1503, 1419, 1441, 1459, 1537, 1611, 1496, 1475, 1497, 1462,
	  1510, 1493, 1573, 1481, 1524, 1522, 1591, 1608, 1593, 1592,
	  1587, 1590, 1641, 1613, 1584, 1619, 1642, 1637, 1628, 1691,
	  1614, 1622, 1663, 1690, 1648, 1669, 1754, 1727, 1748, 1649,
	  1795, 1780, 1748, 1761, 1807, 1831, 1779, 1743, 1814, 1860,
	  1944, 1937, 1908, 1885, 1890, 1978, 1966, 1897, 1928, 1967,
	  1962, 1913, 1998, 2105, 2007, 2102, 2057, 2042, 2192, 2064,
	  2181, 2165, 2169, 2094, 2224, 2272, 2269, 2244, 2336, 2299,
	  2308, 2371, 2338, 2403, 2440, 2471, 2560, 2518, 2419, 2488,
	  2545, 2549, 2636, 2598, 2655, 2756, 2753, 2684, 2799, 2820,
	  2772, 2837, 2786, 2845, 2962, 2985, 2965, 3049, 3009, 3100,
	  3124, 3127, 3227, 3235, 3235, 3239, 3319, 3499, 3462, 3589,
	  3557, 3615, 3572, 3657, 3706, 3838, 3758, 3765, 3833, 3835,
	  3970, 4026, 4212, 4156, 4168, 4347, 4504, 4584, 4501, 4667,
	  4694, 4722, 4780, 4928, 5027, 4992, 5120, 5325, 5200, 5187};
allweight = Plus @@ weight;
mostweight = Sum[weight[[i]], {i, 26, 200}];
<< allenergy.m;
cont1[run_] := (NumberQ[energy[run]] && energy[run] > 4.715 && energy[run] < 4.72);
peak1[run_] := (NumberQ[energy[run]] && energy[run] > 4.72913 && energy[run] < 4.73113);
high1[run_] := (NumberQ[energy[run]] && energy[run] > 4.78 && energy[run] < 4.781);
all1[run_] := (NumberQ[energy[run]] && energy[run] > 4.715 && energy[run] < 4.781);
cont2[run_] := (NumberQ[energy[run]] && energy[run] > 4.995 && energy[run] < 5.0025);
peak2[run_] := (NumberQ[energy[run]] && energy[run] > 5.01186 && energy[run] < 5.01386);
high2[run_] := (NumberQ[energy[run]] && energy[run] > 5.0423 && energy[run] < 5.043);
all2[run_] := (NumberQ[energy[run]] && energy[run] > 4.995 && energy[run] < 5.043);
cont3[run_] := (NumberQ[energy[run]] && energy[run] > 5.16 && energy[run] < 5.17);
peak3[run_] := (NumberQ[energy[run]] && energy[run] > 5.17826 && energy[run] < 5.18026);
high3[run_] := (NumberQ[energy[run]] && energy[run] > 5.195 && energy[run] < 5.205);
all3[run_] := (NumberQ[energy[run]] && energy[run] > 5.16 && energy[run] < 5.205);

rangea[run_] := run <= 122354;
rangeb[run_] := run >= 122356  &&  run <= 123055;
rangec[run_] := run >= 123056  &&  run <= 126846;
ranged[run_] := run >= 126847  &&  run <= 128821;
rangee[run_] := run >= 128824;

<< ../tpplots/almostall.m;
runs = Sort[runs];

n = Plus @@ (numer /@ Select[runs, rangee]);
d = Plus @@ (denom /@ Select[runs, rangee]);
effplot = Table[{{(i-1)*0.8/200., N[n[[i]]/d[[i]]]}, ErrorBar[N[Sqrt[(n[[i]]/d[[i]])*(1.-n[[i]]/d[[i]])/d[[i]]]]]}, {i, 1, 200}];
MultipleListPlot[effplot, Frame -> True, FrameLabel -> {"CosTheta", "Efficiency", None, None}, PlotRange -> {{0,0.8}, {0,1.1}}, DisplayFunction -> (Display["rangee.eps", #, "EPS"]&)];
MultipleListPlot[effplot, Frame -> True, FrameLabel -> {"CosTheta", "Efficiency", None, None}, PlotRange -> {{0,0.8}, {0.9,1.05}}, DisplayFunction -> (Display["rangee2.eps", #, "EPS"]&)];
effall = Sum[N[weight[[i]]/allweight * n[[i]]/d[[i]]], {i, 1, 200}];
effallerr = Sqrt[Sum[N[(weight[[i]]/allweight * n[[i]]/d[[i]])^2 *
		    ((1-weight[[i]]/allweight)/weight[[i]] + (1-n[[i]]/d[[i]])/n[[i]])],
		  {i, 1, 200}]];
eff = Sum[N[weight[[i]]/mostweight * n[[i]]/d[[i]]], {i, 26, 200}];
efferr = Sqrt[Sum[N[(weight[[i]]/mostweight * n[[i]]/d[[i]])^2 *
		    ((1-weight[[i]]/mostweight)/weight[[i]] + (1-n[[i]]/d[[i]])/n[[i]])],
		  {i, 26, 200}]];
{eff, efferr, effall, effallerr} * 100.

rangea {99.22, 0.15, 98.43, 0.15}

rangeb {98.53, 0.15, 97.83, 0.15}

rangec {98.71, 0.15, 97.99, 0.15}

ranged {98.67, 0.15, 97.91, 0.15}

rangee {99.63, 0.15, 98.79, 0.15}

Exit

[Mathematica finished.]




plottp[x_,y_] :=
    Module[{cum, cum2, intplot, intplot2},
	   cum = 0;
	   cum2 = 0;
	   intplot = {};
	   intplot2 = {};
	   Do[intplot = Append[intplot, cum += thetaphi[runs[[i]]][[x,y]]], {i, 1, Length[runs]}];
	   Do[intplot2 = Append[intplot2, cum2 += Sum[thetaphi[runs[[i]]][[xer,yer]], {xer, 1, 10}, {yer, 1, 10}]], {i, 1, Length[runs]}];
	   Display["/home/mccann/luminosity/tpplots/tpbin"<>ToString[x]<>"_"<>ToString[y]<>".eps",
		   Show[GraphicsArray[{{ListPlot[Table[{intplot2[[i]], intplot[[i]]}, {i, 1, Length[runs]}], DisplayFunction -> Identity]},
				       {ListPlot[Table[{intplot2[[i]], (intplot[[i]] - cum/cum2*intplot2[[i]])}, {i, 1, Length[runs]}], DisplayFunction -> Identity]}}], PlotLabel -> "Bin "<>ToString[x]<>", "<>ToString[y]<>""], "EPS", ImageSize -> 72*5];
	  ];
Do[plottp[x,y], {x, 1, 10}, {y, 1, 10}]


2 6 100
2 7 100
3 1 100
3 3 100
3 8 100
10 1 150
2 5 150
3 6 150
5 7 150
5 8 150
9 10 150
10 10 200
10 2 200
10 9 200
2 1 200
2 3 200
3 4 200
4 2 200
4 6 200
4 7 200
4 8 200
5 1 200
5 9 200
6 10 200
6 9 200
7 3 200
9 1 200
2 2 250
2 8 250
3 7 250
4 1 250
4 5 250
5 4 250
5 5 250
6 3 250
7 5 250
7 9 250
10 3 300
2 10 300
2 9 300
3 2 300
3 5 300
3 9 300
4 3 300
6 1 300
6 5 300
6 7 300
7 1 300
9 2 300
2 4 350
5 3 350
7 7 350
10 8 400
4 4 400
4 9 400
5 2 400
6 2 400
6 4 400
6 6 400
7 10 400
7 2 400
7 4 400
7 8 400
8 10 400
8 5 400
9 7 400
9 8 400
10 6 450
9 4 450
10 5 500
10 7 500
1 7 500
6 8 500
7 6 500
8 1 500
10 4 550
1 1 600
1 3 600
1 4 600
1 8 600
8 2 600
8 3 600
8 7 600
8 8 600
9 3 600
9 5 600
9 6 650
1 10 700
5 10 700
1 5 800
1 6 800
1 9 800
8 4 800
8 6 900
1 2 1000
4 10 1000
5 6 1200
3 10 1600
9 9 2100
8 9 2500



plottp2[x_,y_] :=
    Module[{cum, cum2, intplot, intplot2},
	   cum = 0;
	   cum2 = 0;
	   intplot = {};
	   intplot2 = {};
	   Do[intplot = Append[intplot, cum += thetaphi[runs[[i]]][[x,y]]], {i, 1, Length[runs]}];
	   Do[intplot2 = Append[intplot2, cum2 += Sum[thetaphi[runs[[i]]][[xer,yer]], {xer, 1, 10}, {yer, 1, 10}]], {i, 1, Length[runs]}];
	   ListPlot[Table[{intplot2[[i]], (intplot[[i]] - cum/cum2*intplot2[[i]])}, {i, 1, Length[runs]}], PlotJoined -> True]
	  ];
bin9a9 = plottp2[9,9];
bin8a9 = plottp2[8,9];
bin3a10 = plottp2[3,10];
bin5a6 = plottp2[5,6];
bin4a10 = plottp2[4,10];
bin1a2 = plottp2[1,2];
bin8a6 = plottp2[8,6];
bin8a4 = plottp2[8,4];
bin1a9 = plottp2[1,9];
bin1a6 = plottp2[1,6];
bin1a5 = plottp2[1,5];

ml[x_] := Line[{{x,-3000}, {x,1500}}];
Show[{bin9a9, bin8a9, bin3a10, bin5a6, bin4a10, bin1a2, bin8a6, bin8a4, bin1a9, bin1a6, bin1a5, Graphics[{ml[3730000], ml[540000], ml[1050000], ml[3100000]}]}];

binsall = Flatten[Table[plottp2[x,y], {x,1,10}, {y,1,10}]];

Show[binsall[[Range[1,10]]], Graphics[{ml[3730000], ml[540000], ml[1050000], ml[3100000]}]];
Show[binsall[[Range[11,20]]], Graphics[{ml[3730000], ml[540000], ml[1050000], ml[3100000]}]];
Show[binsall[[Range[21,30]]], Graphics[{ml[3730000], ml[540000], ml[1050000], ml[3100000]}]];
Show[binsall[[Range[31,40]]], Graphics[{ml[3730000], ml[540000], ml[1050000], ml[3100000]}]];
Show[binsall[[Range[41,50]]], Graphics[{ml[3730000], ml[540000], ml[1050000], ml[3100000]}]];
Show[binsall[[Range[51,60]]], Graphics[{ml[3730000], ml[540000], ml[1050000], ml[3100000]}]];
Show[binsall[[Range[61,70]]], Graphics[{ml[3730000], ml[540000], ml[1050000], ml[3100000]}]];
Show[binsall[[Range[71,80]]], Graphics[{ml[3730000], ml[540000], ml[1050000], ml[3100000]}]];
Show[binsall[[Range[81,90]]], Graphics[{ml[3730000], ml[540000], ml[1050000], ml[3100000]}]];
Show[binsall[[Range[91,100]]], Graphics[{ml[3730000], ml[540000], ml[1050000], ml[3100000]}]];

DumpSave["../tpplots/overlayplots.mx", {bin9a9, bin8a9, bin3a10, bin5a6, bin4a10, bin1a2, bin8a6, bin8a4, bin1a9, bin1a6, bin1a5, binsall}]

cum2 = 0;
intplot2 = {};
Do[intplot2 = Append[intplot2, {runs[[i]], cum2 += Sum[thetaphi[runs[[i]]][[xer,yer]], {xer, 1, 10}, {yer, 1, 10}]}], {i, 1, Length[runs]}];
interp = Interpolation[intplot2, InterpolationOrder -> 1];
Plot[interp[x], {x, runs[[1]], runs[[Length[runs]]]}];

bisect[l_,r_,t_] := Module[{m = (l+r)/2},
			   If[Abs[interp[m] - t] < 1, m,
			      If[interp[m] > t, bisect[l,m,t], bisect[m,r,t]]]];
bisect[runs[[1]], runs[[Length[runs]]], 3100000] // N

