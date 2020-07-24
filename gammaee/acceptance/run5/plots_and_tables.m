<< Statistics`ContinuousDistributions`;
<< Statistics`DiscreteDistributions`;
<< Graphics`Graphics`;
<< Graphics`MultipleListPlot`;

Rand[numer_, denom_] := If[numer == denom, numer,			
			   If[CDF[NormalDistribution[numer, Sqrt[numer*(1-numer/denom)]], denom] < 0.9999,
			      Random[BinomialDistribution[denom, numer/denom]],
			      Module[{trial = denom},
				     While[trial >= denom,
					   trial = Random[NormalDistribution[numer, Sqrt[numer*(1-numer/denom)]]]];
				     trial]]];
unjiggle[] := (
    nptoc = hptoc;
    nptocerr = hptocerr;
    Clear[n];
    n[110] = h[110];
    n[111] = h[111];
    n[120] = h[120];
    n[122] = h[122];
    n[210] = h[210];
    n[211] = h[211];
    n[220] = h[220];
    n[222] = h[222];
    n[300] = h[300];
    n[301] = h[301];
    n[302] = h[302];
    n[350] = h[350];
    n[351] = h[351];
    n[352] = h[352];
    n[400] = h[400];
    n[401] = h[401];
    n[402] = h[402];
    n[403] = h[403];
    n[404] = h[404];
    n[1401] = h[1401];
    n[1409] = h[1409];
    n[1402] = h[1402];
    n[1403] = h[1403];
    n[1404] = h[1404];
    n[1405] = h[1405];
    n[1406] = h[1406];
    n[1407] = h[1407];
    n[1501] = h[1501];
    n[1509] = h[1509];
    n[1502] = h[1502];
    n[1503] = h[1503];
    n[1504] = h[1504];
    n[1505] = h[1505];
    n[1506] = h[1506];
    n[1507] = h[1507];
    n[1601] = h[1601];
    n[1609] = h[1609];
    n[1602] = h[1602];
    n[1603] = h[1603];
    n[1604] = h[1604];
    n[1605] = h[1605];
    n[1606] = h[1606];
    n[1607] = h[1607];
    n[1701] = h[1701];
    n[1709] = h[1709];
    n[1702] = h[1702];
    n[1703] = h[1703];
    n[1704] = h[1704];
    n[1705] = h[1705];
    n[1706] = h[1706];
    n[1707] = h[1707];
    n[1801] = h[1801];
    n[1809] = h[1809];
    n[1802] = h[1802];
    n[1803] = h[1803];
    n[1804] = h[1804];
    n[1805] = h[1805];
    n[1806] = h[1806];
    n[1807] = h[1807];
    n[1901] = h[1901];
    n[1909] = h[1909];
    n[1902] = h[1902];
    n[1903] = h[1903];
    n[1904] = h[1904];
    n[1905] = h[1905];
    n[1906] = h[1906];
    n[1907] = h[1907];
    n[2001] = h[2001];
    n[2009] = h[2009];
    n[2002] = h[2002];
    n[2003] = h[2003];
    n[2004] = h[2004];
    n[2005] = h[2005];
    n[2006] = h[2006];
    n[2007] = h[2007];
    n[2101] = h[2101];
    n[2109] = h[2109];
    n[2102] = h[2102];
    n[2103] = h[2103];
    n[2104] = h[2104];
    n[2105] = h[2105];
    n[2106] = h[2106];
    n[2107] = h[2107];
    n[2201] = h[2201];
    n[2209] = h[2209];
    n[2202] = h[2202];
    n[2203] = h[2203];
    n[2204] = h[2204];
    n[2205] = h[2205];
    n[2206] = h[2206];
    n[2207] = h[2207];
    n[2701] = h[2701];
    n[2709] = h[2709];
    n[2702] = h[2702];
    n[2703] = h[2703];
    n[2704] = h[2704];
    n[2705] = h[2705];
    n[2706] = h[2706];
    n[2707] = h[2707];
    n[2901] = h[2901];
    n[2909] = h[2909];
    n[2902] = h[2902];
    n[2903] = h[2903];
    n[2904] = h[2904];
    n[2905] = h[2905];
    n[2906] = h[2906];
    n[2907] = h[2907];
    n[2301] = h[2301];
    n[2309] = h[2309];
    n[2302] = h[2302];
		     );
calcMCll[which_] := n[which+01];
calcMCtau[which_] := n[which+09];
calcMChad[which_] := n[which+02];
calcMCtot[which_] := n[which+01] + n[which+09] + n[which+02];
calcData[which_] := Module[{nptobge, nctobge, nptobgp, nctobgp, ndtocos},
			   nptobge = n[110]/n[111];
			   nctobge = n[210]/n[211];
			   nptobgp = n[120]/n[122];
			   nctobgp = n[220]/n[222];
			   ndtocos = (n[400]-nptoc*n[401]
				      - (nptobge-nptoc*nctobge)*n[402]
				      - (nptobgp-nptoc*nctobgp)*n[403])/n[404];
			   n[which+03] - nptoc*n[which+04] -
			   ((nptobge-nptoc*nctobge)*n[which+05]
			   + (nptobgp-nptoc*nctobgp)*n[which+06]
			   + ndtocos*n[which+07])];
jiggleMCll[numer_, denom_] := (n[numer+01] = Rand[h[numer+01], h[denom+01]];);
jiggleMCtau[numer_, denom_] := (n[numer+09] = Rand[h[numer+09], h[denom+09]];);
jiggleMChad[numer_, denom_] := (n[numer+02] = Rand[h[numer+02], h[denom+02]];);
jiggleMCtot[numer_, denom_] := (n[numer+01] = Rand[h[numer+01], h[denom+01]];
				n[numer+09] = Rand[h[numer+09], h[denom+09]];
				n[numer+02] = Rand[h[numer+02], h[denom+02]];);
jiggledata[numer_, denom_] := (n[numer+03] = Rand[h[numer+03], h[denom+03]];
			       n[numer+04] = Rand[h[numer+04], h[denom+04]];
			       n[numer+05] = Rand[h[numer+05], h[denom+05]];
			       n[numer+06] = Rand[h[numer+06], h[denom+06]];
			       n[numer+07] = Rand[h[numer+07], h[denom+07]];);
jiggleptoc[] := (nptoc = Random[NormalDistribution[hptoc, hptocerr]]);
jigglebackgrounds[] := (n[110] = Random[NormalDistribution[h[110], Sqrt[h[110]]]];
			n[111] = Random[NormalDistribution[h[111], Sqrt[h[111]]]];
			n[210] = Random[NormalDistribution[h[210], Sqrt[h[210]]]];
			n[211] = Random[NormalDistribution[h[211], Sqrt[h[211]]]];
			n[120] = Random[NormalDistribution[h[120], Sqrt[h[120]]]];
			n[122] = Random[NormalDistribution[h[122], Sqrt[h[122]]]];
			n[220] = Random[NormalDistribution[h[220], Sqrt[h[220]]]];
			n[222] = Random[NormalDistribution[h[222], Sqrt[h[222]]]];
			n[400] = Random[NormalDistribution[h[400], Sqrt[h[400]]]];
			n[401] = Random[NormalDistribution[h[401], Sqrt[h[401]]]];
			n[402] = Random[NormalDistribution[h[402], Sqrt[h[402]]]];
			n[403] = Random[NormalDistribution[h[403], Sqrt[h[403]]]];
			n[404] = Random[NormalDistribution[h[404], Sqrt[h[404]]]];
		       );
lev[none] = 2300;
lev[trigger] = 1400;
lev[d0close] = 1500;
lev[e1] = 1600;
lev[p2] = 1700;
lev[wz] = 2700;
lev[antiee] = 2900;
lev[antimumu] = 1800;
lev[visen] = 2000;
lev[tracks] = 2100;
lev[l4dec] = 1900;
lev[ccen] = 2200;
lev[all] = 2200;
longline[num_, name_, numer_, denom_, trials_] := (
    unjiggle[];
    Print[name, " ", (N[calcMCll[numer] / calcMCll[denom] * 100, 4]), "\\% & $\\pm$ ",
	  (TeXForm[N[StandardDeviation[Table[(jiggleMCll[numer, denom]; N[calcMCll[numer] / calcMCll[denom]]), {trials}]]*100, 4]]), "\\% & ",
	  (N[calcMCtau[numer] / calcMCtau[denom] * 100, 4]), "\\% & $\\pm$ ",
	  (TeXForm[N[StandardDeviation[Table[(jiggleMCtau[numer, denom]; N[calcMCtau[numer] / calcMCtau[denom]]), {trials}]]*100, 4]]), "\\% & ",
	  (N[calcMChad[numer] / calcMChad[denom]*100, 4]), "\\% & $\\pm$ ",
	  (TeXForm[N[StandardDeviation[Table[(jiggleMChad[numer, denom]; N[calcMChad[numer] / calcMChad[denom]]), {trials}]]*100, 4]]), "\\% & ",
	  (thedata[num] = N[calcData[numer] / calcData[denom]*100, 4]), "\\% & $\\pm$ ",
	  (TeXForm[errdata1[num] = N[StandardDeviation[Table[(jiggledata[numer, denom]; N[calcData[numer] / calcData[denom]]), {trials}]]*100, 4]]), "\\% & $\\pm$ ",
	  (TeXForm[errdata2[num] = N[StandardDeviation[Table[(jiggleptoc[]; N[calcData[numer] / calcData[denom]]), {trials}]]*100, 4]]), "\\% & $\\pm$ ",
	  (TeXForm[errdata3[num] = N[StandardDeviation[Table[(jigglebackgrounds[]; N[calcData[numer] / calcData[denom]]), {trials}]]*100, 4]]), "\\% \\\\ "];
    (themc[num] = N[calcMCtot[numer] / calcMCtot[denom]*100, 4]);
    (errmc[num] = N[StandardDeviation[Table[(jiggleMCtot[numer, denom]; N[calcMCtot[numer] / calcMCtot[denom]]), {trials}]]*100,4]);
			    );
shortline[num_, name_, numer_, denom_, trials_] := (
    unjiggle[];
    Print[name, " ", (N[calcMCll[numer] / calcMCll[denom]*100, 4]), "\\% & $\\pm$ ",
	  (TeXForm[N[StandardDeviation[Table[(jiggleMCll[numer, denom]; N[calcMCll[numer] / calcMCll[denom]]), {trials}]]*100, 4]]), "\\% & ",
	  (N[calcMCtau[numer] / calcMCtau[denom]*100, 4]), "\\% & $\\pm$ ",
	  (TeXForm[N[StandardDeviation[Table[(jiggleMCtau[numer, denom]; N[calcMCtau[numer] / calcMCtau[denom]]), {trials}]]*100, 4]]), "\\% & ",
	  (N[calcMChad[numer] / calcMChad[denom]*100, 4]), "\\% & $\\pm$ ",
	  (TeXForm[N[StandardDeviation[Table[(jiggleMChad[numer, denom]; N[calcMChad[numer] / calcMChad[denom]]), {trials}]]*100, 4]]), "\\% & ",
	  " & & & \\\\ "];
    (themc[num] = N[calcMCtot[numer] / calcMCtot[denom]*100, 4]);
    (errmc[num] = N[StandardDeviation[Table[(jiggleMCtot[numer, denom]; N[calcMCtot[numer] / calcMCtot[denom]]), {trials}]]*100, 4]);
						   );
wholeblock[trials_] := (
    shortline[0, "trigger",                          lev[trigger],    lev[none],       trials];
    longline[1, "closest track d0 $<$ 5 mm",         lev[d0close],    lev[trigger],    trials];
    longline[2, "biggest shower $<$ 85\\%",          lev[e1],         lev[d0close],    trials];
    longline[3, "second-biggest track $<$ 85\\%",    lev[p2],         lev[e1], 	       trials];
    longline[4, "event vertex Z or z0 $<$ 7.5 cm",   lev[wz],         lev[p2], 	       trials];
    longline[5, "1, 2-track e/p $\\in$ (0.88, 1.04)", lev[antiee], lev[wz], trials];
    longline[6, "0, 1, 2-track biggest shower $>$ 5\\%", lev[antimumu],  lev[antiee],     trials];
    longline[7, "visible energy $>$ 35\\%",          lev[visen],      lev[antimumu],   trials];
    longline[8, "number of quality tracks $\\ge$ 2", lev[tracks],     lev[visen],      trials];
    longline[9, "level3/level4",                     lev[l4dec],      lev[tracks],     trials];
    longline[10, "CC energy $<$ 85\\%",               lev[ccen],       lev[l4dec],      trials];
    longline[11, "all cuts except trigger",           lev[all],        lev[trigger],    trials];
    shortline[12, "all cuts",                        lev[all],        lev[none],       trials];
		);
plotagreement[name_, canthavemax_, musthavemax_, musthavemin_, canthavemin_] :=
    Module[{thetop, thebot},
	   thetop = Max[Join[{musthavemax}, Select[Join[Table[themc[i]+errmc[i], {i, 0, 12}],
							Table[thedata[i]+Sqrt[errdata1[i]^2+errdata2[i]^2+errdata3[i]^2], {i, 1, 11}]],
						   (# < canthavemax)&]]];
	   thebot = Min[Join[{musthavemin}, Select[Join[Table[themc[i]-errmc[i], {i, 0, 12}],
							Table[thedata[i]-Sqrt[errdata1[i]^2+errdata2[i]^2+errdata3[i]^2], {i, 1, 11}]],
						   (# > canthavemin)&]]];
	   Display[name, Show[
	       Graphics[{
		   Dashing[{0.01, 0.01}], Line[{{-0.5, 100}, {13, 100}}], Dashing[{}]
		   , Line[{{-0.5, (thetop+thebot)/2-1.1*(thetop-thebot)/2}, {-0.5, (thetop+thebot)/2+1.1*(thetop-thebot)/2}}]
		   , Line[{{13, (thetop+thebot)/2-1.1*(thetop-thebot)/2}, {13, (thetop+thebot)/2+1.1*(thetop-thebot)/2}}]
			}]
	       , (theplot = MultipleListPlot[
		   Table[{{If[i<11,i,i+0.5]+1/6,thedata[i]},ErrorBar[errdata1[i]]}, {i, 1, 11}]
		   , Table[{{If[i<11,i,i+0.5]+1/6,thedata[i]},ErrorBar[Sqrt[errdata1[i]^2+errdata2[i]^2]]}, {i, 1, 11}]
		   , Table[{{If[i<11,i,i+0.5]+1/6,thedata[i]},ErrorBar[Sqrt[errdata1[i]^2+errdata2[i]^2+errdata3[i]^2]]}, {i, 1, 11}]
		   , SymbolShape -> {PlotSymbol[Box, 2], PlotSymbol[Box, 2], PlotSymbol[Box, 2]}
		   , SymbolStyle -> RGBColor[1,0,0]
		   , Axes -> False
		   , PlotRange -> {{-0.5, 13}, {(thetop+thebot)/2-1.1*(thetop-thebot)/2, (thetop+thebot)/2+1.1*(thetop-thebot)/2}}
		   , DisplayFunction -> Identity];
		  ReplacePart[theplot, Prepend[theplot[[1]], RGBColor[1,0,0]], 1])
	       , (theplot = MultipleListPlot[
		   Table[{{If[i<11,i,i+0.5],themc[i]},ErrorBar[errmc[i]]}, {i, 0, 12}]
		   , SymbolShape -> PlotSymbol[Diamond, 3]
		   , SymbolStyle -> RGBColor[0,0,1]
		   , Axes -> False
		   , PlotRange -> {{-0.5, 11}, {(thetop+thebot)/2-1.1*(thetop-thebot)/2, (thetop+thebot)/2+1.1*(thetop-thebot)/2}}
		   , DisplayFunction -> Identity];
		  ReplacePart[theplot, Prepend[theplot[[1]], RGBColor[0,0,1]], 1])
	       , Graphics[Join[{
		   GrayLevel[1], Rectangle[{-0.5, (thetop+thebot)/2-3*(thetop-thebot)/2}, {13, (thetop+thebot)/2-1.1*(thetop-thebot)/2}],
		   Rectangle[{-0.5, (thetop+thebot)/2+1.1*(thetop-thebot)/2}, {13, (thetop+thebot)/2+1.2*(thetop-thebot)/2}], GrayLevel[0]
		   , Text["trigger", {0, (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["closest track d0 < 5 mm", {1+1/12, (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["biggest shower < 85%", {2+1/12, (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["second-biggest track < 85%", {3+1/12, (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["event vertex Z or z0 < 7.5 cm", {4+1/12, (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["1, 2-track e/p in (0.88, 1.04)", {5+1/12, (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["0, 1, 2-track biggest shower > 5%", {6+1/12, (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["visible energy > 35%", {7+1/12, (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["number of quality tracks >= 2", {8+1/12, (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["level3/level4", {9+1/12, (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["CC energy < 85%", {10+1/12, (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["all cuts except trigger", {11.5+1/12, (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["all cuts", {12.5, (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
			       },
			       Flatten[{Line[{{-0.5, #}, {-0.4, #}}], Line[{{13, #}, {13.2, #}}]}& /@
				       Select[Range[canthavemin-10, canthavemax+10, 1],
					      ((thetop+thebot)/2-1.1*(thetop-thebot)/2 < # && # < (thetop+thebot)/2+1.1*(thetop-thebot)/2)&]]
			       , Flatten[{Line[{{-0.6, #}, {-0.4, #}}], Line[{{13, #}, {13.2, #}}],
					  Text[#, {-0.5, #}, {3, 0}, {0, 1}], Text[#, {13, #}, {-3, 0}, {0, 1}]}& /@
					 Select[Range[canthavemin-10, canthavemax+10, 2],
						((thetop+thebot)/2-1.1*(thetop-thebot)/2 < # && # < (thetop+thebot)/2+1.1*(thetop-thebot)/2)&]]
			       , Flatten[{Line[{{-0.5, #}, {-0.47, #}}], Line[{{13, #}, {13.1, #}}]}& /@
					 Select[Range[canthavemin-10, canthavemax+10, 0.1],
						((thetop+thebot)/2-1.1*(thetop-thebot)/2 < # && # < (thetop+thebot)/2+1.1*(thetop-thebot)/2)&]]
			      ]]
	       , PlotRange -> {{-1.1, 14.5}, {(thetop+thebot)/2-3.3*(thetop-thebot)/2, (thetop+thebot)/2+1.2*(thetop-thebot)/2}}
	       , AspectRatio -> 1.5
	       , DisplayFunction -> $DisplayFunction
				    ], "EPS", ImageSize -> 72*4.4];
	   Run["epstopdf --exact ", name];
	  ];

SetOptions[$Output, PageWidth -> Infinity, PageHeight -> Infinity];
SetDirectory["/home/mccann/acceptance/run5/tables5"];
! rm -f *.mx

RunThrough["perl mathemetize_table.pl all1_bblumi.table", Null];
wholeblock[1000];
DumpSave["all1_bblumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["all1_bblumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl all1_gglumi.table", Null];
wholeblock[1000];
DumpSave["all1_gglumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["all1_gglumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl all2_bblumi.table", Null];
wholeblock[1000];
DumpSave["all2_bblumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["all2_bblumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl all2_gglumi.table", Null];
wholeblock[1000];
DumpSave["all2_gglumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["all2_gglumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl all3_bblumi.table", Null];
wholeblock[1000];
DumpSave["all3_bblumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["all3_bblumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl all3_gglumi.table", Null];
wholeblock[1000];
DumpSave["all3_gglumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["all3_gglumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl db16_bblumi.table", Null];
wholeblock[1000];
DumpSave["db16_bblumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["db16_bblumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl db16_gglumi.table", Null];
wholeblock[1000];
DumpSave["db16_gglumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["db16_gglumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl db17_bblumi.table", Null];
wholeblock[1000];
DumpSave["db17_bblumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["db17_bblumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl db17_gglumi.table", Null];
wholeblock[1000];
DumpSave["db17_gglumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["db17_gglumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl db18_bblumi.table", Null];
wholeblock[1000];
DumpSave["db18_bblumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["db18_bblumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl db18_gglumi.table", Null];
wholeblock[1000];
DumpSave["db18_gglumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["db18_gglumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl db19_bblumi.table", Null];
wholeblock[1000];
DumpSave["db19_bblumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["db19_bblumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl db19_gglumi.table", Null];
wholeblock[1000];
DumpSave["db19_gglumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["db19_gglumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl db21_bblumi.table", Null];
wholeblock[1000];
DumpSave["db21_bblumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["db21_bblumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl db21_gglumi.table", Null];
wholeblock[1000];
DumpSave["db21_gglumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["db21_gglumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl db23_bblumi.table", Null];
wholeblock[1000];
DumpSave["db23_bblumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["db23_bblumi.eps", 110, 101, 92, 80];

RunThrough["perl mathemetize_table.pl db23_gglumi.table", Null];
wholeblock[1000];
DumpSave["db23_gglumi.mx", {themc, errmc, thedata, errdata1, errdata2, errdata3}];
plotagreement["db23_gglumi.eps", 110, 101, 92, 80];










(* untested! *)
<< "all1_bblumi.mx";
plotagreement["all1_bblumi.eps", 110, 101, 92, 80];
<< "all1_gglumi.mx";
plotagreement["all1_gglumi.eps", 110, 101, 92, 80];
<< "all2_bblumi.mx";
plotagreement["all2_bblumi.eps", 110, 101, 92, 80];
<< "all2_gglumi.mx";
plotagreement["all2_gglumi.eps", 110, 101, 92, 80];
<< "all3_bblumi.mx";
plotagreement["all3_bblumi.eps", 110, 101, 92, 80];
<< "all3_gglumi.mx";
plotagreement["all3_gglumi.eps", 110, 101, 92, 80];
<< "db16_bblumi.mx";
plotagreement["db16_bblumi.eps", 110, 101, 92, 80];
<< "db16_gglumi.mx";
plotagreement["db16_gglumi.eps", 110, 101, 92, 80];
<< "db17_bblumi.mx";
plotagreement["db17_bblumi.eps", 110, 101, 92, 80];
<< "db17_gglumi.mx";
plotagreement["db17_gglumi.eps", 110, 101, 92, 80];
<< "db18_bblumi.mx";
plotagreement["db18_bblumi.eps", 110, 101, 92, 80];
<< "db18_gglumi.mx";
plotagreement["db18_gglumi.eps", 110, 101, 92, 80];
<< "db19_bblumi.mx";
plotagreement["db19_bblumi.eps", 110, 101, 92, 80];
<< "db19_gglumi.mx";
plotagreement["db19_gglumi.eps", 110, 101, 92, 80];
<< "db21_bblumi.mx";
plotagreement["db21_bblumi.eps", 110, 101, 92, 80];
<< "db21_gglumi.mx";
plotagreement["db21_gglumi.eps", 110, 101, 92, 80];
<< "db23_bblumi.mx";
plotagreement["db23_bblumi.eps", 110, 101, 92, 80];
<< "db23_gglumi.mx";
plotagreement["db23_gglumi.eps", 110, 101, 92, 80];

