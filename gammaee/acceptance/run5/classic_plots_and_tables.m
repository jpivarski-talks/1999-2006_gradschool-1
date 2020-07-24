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
    n[2301] = h[2301];
    n[2309] = h[2309];
    n[2302] = h[2302];
		     );
calcMC[which_] := n[which+02];
preQuick[] := (
    (* nptoc is already defined *)
    If[isbblumi, 
       nptomc = (n[301] - n[351]*n[302]/n[352])/(n[300] - n[350]*n[302]/n[352]),
       nptomc = (n[301] - nptoc*n[302])/n[300]
      ];
    nptobge = n[110]/n[111];
    nctobge = n[210]/n[211];
    ndtobge = (nptobge-nptoc*nctobge);
    nptobgp = n[120]/n[122];
    nctobgp = n[220]/n[222];
    ndtobgp = (nptobgp-nptoc*nctobgp);
    ndtocos = (n[400]-nptoc*n[401] - ndtobge*n[402] - ndtobgp*n[403])/n[404];
	      );
calcDataQuick[which_] :=
    (n[which+03] - nptoc*n[which+04] - nptomc*(n[which+01] + n[which+09])
     - ndtobge*n[which+05] - ndtobgp*n[which+06] - ndtocos*n[which+07]);
calcData[which_] := (preQuick[];  calcDataQuick[which]);
jiggleMC[numer_, denom_] := (n[numer+02] = Rand[h[numer+02], h[denom+02]]);
jiggledata[numer_, denom_] := (n[numer+01] = Rand[h[numer+01], h[denom+01]];
			       n[numer+09] = Rand[h[numer+09], h[denom+09]];
			       n[numer+03] = Rand[h[numer+03], h[denom+03]];
			       n[numer+04] = Rand[h[numer+04], h[denom+04]];
			       n[numer+05] = Rand[h[numer+05], h[denom+05]];
			       n[numer+06] = Rand[h[numer+06], h[denom+06]];
			       n[numer+07] = Rand[h[numer+07], h[denom+07]];
			      );
jigglesyst[denom_] := (
    nptoc = Random[NormalDistribution[hptoc, hptocerr]];
    n[300] = Random[NormalDistribution[h[300], Sqrt[h[300]]]];
    n[301] = Random[NormalDistribution[h[301], Sqrt[h[301]]]];
    n[302] = Random[NormalDistribution[h[302], Sqrt[h[302]]]];
    If[isbblumi,
       n[350] = Random[NormalDistribution[h[350], Sqrt[h[350]]]];
       n[351] = Random[NormalDistribution[h[351], Sqrt[h[351]]]];
       n[352] = Random[NormalDistribution[h[352], Sqrt[h[352]]]];
      ];
    n[110] = Random[NormalDistribution[h[110], Sqrt[h[110]]]];
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
    n[denom+04] = Random[NormalDistribution[h[denom+04], Sqrt[h[denom+04]]]];
    n[denom+01] = Random[NormalDistribution[h[denom+01], Sqrt[h[denom+01]]]];
    n[denom+09] = Random[NormalDistribution[h[denom+09], Sqrt[h[denom+09]]]];
    n[denom+05] = Random[NormalDistribution[h[denom+05], Sqrt[h[denom+05]]]];
    n[denom+06] = Random[NormalDistribution[h[denom+06], Sqrt[h[denom+06]]]];
    n[denom+07] = Random[NormalDistribution[h[denom+07], Sqrt[h[denom+07]]]];
		      );
lev[none] = 2300;
lev[trigger] = 1400;
lev[d0close] = 1500;
lev[e1] = 1600;
lev[p2] = 1700;
lev[wz] = 1800;
lev[visen] = 2000;
lev[tracks] = 2100;
lev[l4dec] = 1900;
lev[ccen] = 2200;
pp[x_] := TeXForm[N[x, 4]];
longline[num_, name_, numer_, denom_, trials_] := (
    unjiggle[];
    Print[name, " ",
	  pp[themc[num] = (calcMC[numer]/calcMC[denom]*100)], "\\% & $\\pm$ ", 
	  pp[errmc[num] = (StandardDeviation[Table[(jiggleMC[numer, denom]; N[calcMC[numer]/calcMC[denom]]), {trials}]]*100)], "\\% & ",
	  pp[thedata[num] = (calcData[numer]/calcData[denom]*100)], "\\% & $\\pm$ ",
	  pp[errdata1[num] = (StandardDeviation[Table[(jiggledata[numer, denom]; N[calcData[numer]/calcData[denom]]), {trials}]]*100)],
	  "\\% & ", (unjiggle[]), " & $\\pm$ ",
	  pp[errdata2[num] = (StandardDeviation[Table[(jigglesyst[denom]; N[calcData[numer]/calcData[denom]]), {trials}]]*100)],
	  "\\% \\\\ "];
						  );
shortline[num_, name_, numer_, denom_, trials_] := (
    unjiggle[];
    Print[name, " ",
	  pp[themc[num] = (calcMC[numer]/calcMC[denom]*100)], "\\% & $\\pm$ ", 
	  pp[errmc[num] = (StandardDeviation[Table[(jiggleMC[numer, denom]; N[calcMC[numer]/calcMC[denom]]), {trials}]]*100)],
	  "\\% & & & Null & \\\\ "];
						   );
wholeblock[trials_] := (
    shortline[0, "trigger",                          lev[trigger],    lev[none],       trials];
    longline[1, "closest track d0 $<$ 5 mm",         lev[d0close],    lev[trigger],    trials];
    longline[2, "biggest shower $<$ 85\\%",          lev[e1],         lev[d0close],    trials];
    longline[3, "second-biggest track $<$ 85\\%",    lev[p2],         lev[e1], 	       trials];
    longline[4, "event vertex Z or z0 $<$ 7.5 cm",   lev[wz],         lev[p2], 	       trials];
    longline[5, "visible energy $>$ 35\\%",          lev[visen],      lev[wz],         trials];
    longline[6, "number of quality tracks $\\ge$ 2", lev[tracks],     lev[visen],      trials];
    longline[7, "level3/level4",                     lev[l4dec],      lev[tracks],     trials];
    longline[8, "CC energy $<$ 85\\%",               lev[ccen],       lev[l4dec],      trials];
    longline[9, "all cuts except trigger",           lev[ccen],       lev[trigger],    trials];
    shortline[10, "all cuts",                        lev[ccen],       lev[none],       trials];
		);
plotagreement[name_, canthavemax_, musthavemax_, musthavemin_, canthavemin_] :=
    Module[{thetop, thebot},
	   thetop = Max[Join[{musthavemax}, Select[Join[Table[themc[i]+errmc[i], {i, 0, 10}],
							Table[thedata[i]+Sqrt[errdata1[i]^2+errdata2[i]^2], {i, 1, 9}]],
						   (# < canthavemax)&]]];
	   thebot = Min[Join[{musthavemin}, Select[Join[Table[themc[i]-errmc[i], {i, 0, 10}],
							Table[thedata[i]-Sqrt[errdata1[i]^2+errdata2[i]^2], {i, 1, 9}]],
						   (# > canthavemin)&]]];
	   Display[name, Show[
	       Graphics[{
		   Dashing[{0.01, 0.01}], Line[{{-0.5, 100}, {11, 100}}], Dashing[{}]
		   , Line[{{-0.5, (thetop+thebot)/2-1.1*(thetop-thebot)/2}, {-0.5, (thetop+thebot)/2+1.1*(thetop-thebot)/2}}]
		   , Line[{{11, (thetop+thebot)/2-1.1*(thetop-thebot)/2}, {11, (thetop+thebot)/2+1.1*(thetop-thebot)/2}}]
			}]
	       , (theplot = MultipleListPlot[
		   Table[{{If[i<9,i,i+0.5]+1/6,thedata[i]},ErrorBar[errdata1[i]]}, {i, 1, 9}]
		   , Table[{{If[i<9,i,i+0.5]+1/6,thedata[i]},ErrorBar[Sqrt[errdata1[i]^2+errdata2[i]^2]]}, {i, 1, 9}]
		   , SymbolShape -> {PlotSymbol[Box, 2], PlotSymbol[Box, 2]}
		   , SymbolStyle -> RGBColor[1,0,0]
		   , Axes -> False
		   , PlotRange -> {{-0.5, 11}, {(thetop+thebot)/2-1.1*(thetop-thebot)/2, (thetop+thebot)/2+1.1*(thetop-thebot)/2}}
		   , DisplayFunction -> Identity];
		  ReplacePart[theplot, Prepend[theplot[[1]], RGBColor[1,0,0]], 1])
	       , (theplot = MultipleListPlot[
		   Table[{{If[i<9,i,i+0.5],themc[i]},ErrorBar[errmc[i]]}, {i, 0, 10}]
		   , SymbolShape -> PlotSymbol[Diamond, 3]
		   , SymbolStyle -> RGBColor[0,0,1]
		   , Axes -> False
		   , PlotRange -> {{-0.5, 11}, {(thetop+thebot)/2-1.1*(thetop-thebot)/2, (thetop+thebot)/2+1.1*(thetop-thebot)/2}}
		   , DisplayFunction -> Identity];
		  ReplacePart[theplot, Prepend[theplot[[1]], RGBColor[0,0,1]], 1])
	       , Graphics[Join[{
		   GrayLevel[1], Rectangle[{-0.5, (thetop+thebot)/2-3*(thetop-thebot)/2}, {11, (thetop+thebot)/2-1.1*(thetop-thebot)/2}],
		   Rectangle[{-0.5, (thetop+thebot)/2+1.1*(thetop-thebot)/2}, {11, (thetop+thebot)/2+1.2*(thetop-thebot)/2}], GrayLevel[0]
		   , Text["trigger",                       {0,        (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["closest track d0 < 5 mm",       {1+1/12,   (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["biggest shower < 85%",          {2+1/12,   (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["second-biggest track < 85%",    {3+1/12,   (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["event vertex Z or z0 < 7.5 cm", {4+1/12,   (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["visible energy > 35%",          {5+1/12,   (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["number of quality tracks >= 2", {6+1/12,   (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["level3/level4",                 {7+1/12,   (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["CC energy < 85%",               {8+1/12,   (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["all cuts except trigger",       {9.5+1/12, (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
		   , Text["all cuts",                      {10.5,     (thetop+thebot)/2-1.2*(thetop-thebot)/2}, {0, 1}, {0, 1}]
			       },
			       Flatten[{Line[{{-0.5, #}, {-0.4, #}}], Line[{{10.9, #}, {11, #}}]}& /@
				       Select[Range[canthavemin-10, canthavemax+10, 1],
					      ((thetop+thebot)/2-1.1*(thetop-thebot)/2 < # && # < (thetop+thebot)/2+1.1*(thetop-thebot)/2)&]]
			       , Flatten[{Line[{{-0.6, #}, {-0.4, #}}], Line[{{10.9, #}, {11.1, #}}],
					  Text[#, {-0.5, #}, {3, 0}, {0, 1}], Text[#, {13, #}, {-3, 0}, {0, 1}]}& /@
					 Select[Range[canthavemin-10, canthavemax+10, 2],
						((thetop+thebot)/2-1.1*(thetop-thebot)/2 < # && # < (thetop+thebot)/2+1.1*(thetop-thebot)/2)&]]
			       , Flatten[{Line[{{-0.5, #}, {-0.47, #}}], Line[{{10.97, #}, {11, #}}]}& /@
					 Select[Range[canthavemin-10, canthavemax+10, 0.1],
						((thetop+thebot)/2-1.1*(thetop-thebot)/2 < # && # < (thetop+thebot)/2+1.1*(thetop-thebot)/2)&]]
			      ]]
	       , PlotRange -> {{-1.1, 11.6}, {(thetop+thebot)/2-3*(thetop-thebot)/2, (thetop+thebot)/2+1.2*(thetop-thebot)/2}}
	       , AspectRatio -> 1.5
(* 	       , DisplayFunction -> $DisplayFunction *)
	       , DisplayFunction -> Identity
				    ], "EPS", ImageSize -> 72*4.4];
	   Run["epstopdf --exact ", name];
	  ];
SetOptions[$Output, PageWidth -> Infinity, PageHeight -> Infinity];
SetDirectory["/home/mccann/acceptance/run5/tables5"];
! rm -f *.mx
