<< Statistics`ContinuousDistributions`

y1scont = ReadList["y1s_cont.lubg", {Number, Number, Number}];
y1speak = ReadList["y1s_peak.lubg", {Number, Number, Number}];
y1shigh = ReadList["y1s_high.lubg", {Number, Number, Number}];
y2scont = ReadList["y2s_cont.lubg", {Number, Number, Number}];
y2speak = ReadList["y2s_peak.lubg", {Number, Number, Number}];
y2shigh = ReadList["y2s_high.lubg", {Number, Number, Number}];
y3scont = ReadList["y3s_cont.lubg", {Number, Number, Number}];
y3speak = ReadList["y3s_peak.lubg", {Number, Number, Number}];
y3shigh = ReadList["y3s_high.lubg", {Number, Number, Number}];

ListFromConf[data_, conf_] := #[[1]]& /@ Select[data * conf, (# != {0, 0, 0})&];
ConfFromList[data_, list_] := If[MemberQ[list, #[[1]]], 1, 0]& /@ data;
EmptyConf[data_] := Table[0, {Length[data]}];
FilledConf[data_] := Table[1, {Length[data]}];
ConfSum[data_, conf_] := (Plus @@ (#[[3]]& /@ (data * conf)) /
			  Plus @@ (#[[2]]& /@ (data * conf))  );
ChangeConf1[conf_] := Module[{i = Random[Integer, Length[conf]-1]+1},
			     ReplacePart[conf, 1 - conf[[i]], i]];
FindOnes[conf_] := Flatten[Table[If[conf[[i]] == 1, {i}, {}], {i, 1, Length[conf]}], 1];
FindZeros[conf_] := Flatten[Table[If[conf[[i]] == 0, {i}, {}], {i, 1, Length[conf]}], 1];
RandElem[list_] := list[[Random[Integer, Length[list]-1]+1]];
ChangeConf2[conf_] := Module[{i = RandElem[FindOnes[conf]],
			      j = RandElem[FindZeros[conf]]},
			     ReplacePart[ReplacePart[conf, 1 - conf[[i]], i], 1 - conf[[j]], j]];
ChangeConf[conf_] := If[(Plus @@ conf) > 0  &&  Random[Integer, 500] > 0,
			ChangeConf2[conf],
			ChangeConf1[conf]];
PickARun[list_, range_] :=
    Module[{sublist = Select[list, (# >= range[[1]]  &&  # <= range[[2]])&]},
	   sublist[[Random[Integer, Length[sublist] - 1] + 1]]];
LumiSum[data_, conf_] := Plus @@ (#[[2]]& /@ (data * conf));
BeefItUp[data_, conf_] := If[LumiSum[data, conf] > 21000, conf,
			     BeefItUp[data, ChangeConf1[conf]]];
InitialConf[data_, ranges_] :=
    BeefItUp[data, ConfFromList[data, Module[{thelist = #[[1]]& /@ data},
					     PickARun[thelist, #]& /@ ranges]]];
ConfRuns[data_, conf_] := (Print[TableForm[Select[data * conf, (# != {0, 0, 0})&]]];
			   Print[]; Print["-----------------------"]; Print[];
			   Print["       ",
				 Plus @@ (#[[2]]& /@ (data * conf)), "  ",
				 Plus @@ (#[[3]]& /@ (data * conf)), "  ==>  ",
				 ConfSum[data, conf]]);
RangeFilled[range_, list_] := Or @@ ((# >= range[[1]] && # <= range[[2]])& /@ list);
RangesFilled[ranges_, list_] := And @@ (RangeFilled[#, list]& /@ ranges);
FindBest[data_, goal_, ranges_] := 
    Module[{lastconf, lastval, newconf, newval, inranges, fall, grope, outplot},
	   lastconf = InitialConf[data, ranges];
	   lastval = Abs[ConfSum[data, lastconf] - goal];
	   (* Print[lastval]; *)
	   While[lastval > 0.000001, (
	       inranges = False;
	       While[!inranges, (
		   newconf = ChangeConf[lastconf];
		   inranges = RangesFilled[ranges, ListFromConf[data, newconf]];
				)];
	       newval = Abs[ConfSum[data, newconf] - goal];
	       fall = newval < lastval;
	       grope = If[fall, False, Random[ExponentialDistribution[50000]] > (newval - lastval)];
	       (* Print[lastval, " ", newval, " ", fall, " ", grope]; *)
	       If[(fall || grope), {lastval = newval, lastconf = newconf}]
				   )];
	   ConfRuns[data, lastconf];
	   outplot = Table[{i, data[[i, 1]]}, {i, 1, Length[data]}];
	   Show[ListPlot[outplot,
			 AspectRatio -> 3,
			 DisplayFunction -> Identity],
		ListPlot[Select[outplot * lastconf, (# != {0, 0})&],
			 PlotStyle -> RGBColor[1, 0, 0],
			 DisplayFunction -> Identity],
		DisplayFunction -> $DisplayFunction];
	   #[[1]]& /@ Select[data * lastconf, (# != {0, 0, 0})&]];
PrintRuns[data_] := Print[TableForm[(#[[1]]& /@ data)]];
PlotData[data_, lines_] := (Show[ListPlot[Table[{i, data[[i, 1]]}, {i, 1, Length[data]}],
					  AspectRatio -> 3,
					  DisplayFunction -> Identity],
				 Graphics[Prepend[Line[{{1, #}, {Length[data], #}}]& /@ lines, RGBColor[1, 0, 0]]],
				 DisplayFunction -> $DisplayFunction];
			    Table[{lines[[i]], lines[[i+1]]}, {i, 1, Length[lines]-1}]);






	                                          FIRST THE UPSILON-1S!!!!!

	  ConfRuns[y1shigh, FilledConf[y1shigh]];

	  124960   286.8    8.4
	  124961   1437.    53.9
	  124962   1215.4   53.2
	  124963   1233.2   44.8
	  124966   517.3    14.7
	  124967   878.8    35
	  124968   905.5    45.5
	  124969   1013.3   39.9
	  124970   1029.3   33.6
	  124971   1058.9   44.1
	  124972   941.     24.5
	  124973   1007.4   39.2
	  -----------------------
	         11523.9  436.8  ==>  0.0379038

	  y1scontRanges = PlotData[
	      y1scont, {123300, 123500, 123700, 123900, 124000, 124200, 124400,
	  	      124600, 124750, 125000, 125250, 125500}];

	  FindBest[y1scont, 0.0379038, y1scontRanges];

	  123370   1699.    60.2
	  123566   1562.2   59.5
	  123570   1691.5   59.5
	  123774   1366.5   43.4
	  123944   718.3    50.4
	  123961   1811.4   72.8
	  124126   1565.1   56
	  124300   1213.2   35.7
	  124475   1543.3   58.1
	  124665   1502.9   58.1
	  124667   901.1    35
	  124807   497.9    15.4
	  124808   1092.2   45.5
	  125175   1616.1   61.6
	  125176   1564.1   58.1
	  125297   819.3    32.9
	  -----------------------
	         21164.1  802.2  ==>  0.0379038

	  y1speakRanges = PlotData[
	      y1speak, {123100, 123500, 123700, 123900, 124075, 124120, 124250, 124420,
	  	      124600, 124775, 125000, 125170, 125250, 125280, 126000}];

	  FindBest[y1speak, 0.0379038, y1speakRanges];

	  123197   1094.1   44.8
	  123636   1500.3   51.1
	  123864   2266.2   73.5
	  123865   2323.    88.9
	  123996   278.5    12.6
	  124092   595.9    28.7
	  124146   1022.9   28.7
	  124328   1778.2   59.5
	  124343   794.9    27.3
	  124373   2019.1   70
	  124481   1905.3   65.1
	  124498   1694.8   68.6
	  124699   1709.2   74.2
	  124702   2185.5   91
	  124853   1733.1   63.7
	  125155   1846.9   75.6
	  125183   201.9    7
	  125222   1517.3   58.8
	  125264   835.5    38.5
	  125318   1544.6   65.8
	  -----------------------
	         28847.2  1093.4  ==>  0.0379032














	                                          NEXT THE UPSILON-2S!!!!!

	  ConfRuns[y2shigh, FilledConf[y2shigh]];

	  127206   311.9   10.5
	  127213   749.7   19.6
	  127214   884.9   24.5
	  127215   863.8   23.8
	  127217   815.6   19.6
	  127218   538.7   14.7
	  127219   630.4   12.6
	  -----------------------
	         4795.  125.3  ==>  0.0261314

	  y2scontRanges = PlotData[
	      y2scont, {126200, 126300, 126600, 126800, 127000, 127433, 127500,
	  	      127800, 128100, 129200, 129600, 129700, 129800, 130000}];

	  FindBest[y2scont, 0.0261314, y2scontRanges];

	  126265   1664.5   46.2
	  126476   548.8    11.9
	  126673   1220.7   35.7
	  126846   1818.3   44.1
	  126851   1100.2   24.5
	  127422   1366.4   37.8
	  127444   1608.2   42.7
	  127680   2295.1   58.8
	  127690   1737.2   40.6
	  127955   287.     11.9
	  129066   2316.7   51.1
	  129531   843.2    28.7
	  129689   1085.1   30.1
	  129724   504.9    18.2
	  129853   1962.8   49.7
	  -----------------------
	         20359.1  532.  ==>  0.0261308

	  y2speakRanges = PlotData[
	      y2speak, {126400, 126700, 126845, 127000, 127500, 129602, 129800}];

	  FindBest[y2speak, 0.0261308, y2speakRanges];

	  126503   375.3    11.9
	  126509   1649.1   57.4
	  126831   711.5    29.4
	  126892   1790.7   49
	  127268   1792.3   44.1
	  127269   1835.9   45.5
	  127279   1399.5   32.9
	  127285   2348.2   60.2
	  127306   1060.1   29.4
	  127327   2252.    53.2
	  129553   534.9    7
	  129564   2711.4   71.4
	  129573   680.9    9.1
	  129617   2292.8   59.5
	  129635   2703.9   72.1
	  129651   2783.6   71.4
	  -----------------------
	         26922.1  703.5  ==>  0.0261309

























	                                          FINALLY THE UPSILON-3S!!!!!

	  ConfRuns[y3shigh, FilledConf[y3shigh]];

	  122568   994.9    56.7
	  122569   956.7    37.8
	  122570   1591.8   90.3
	  122571   1635.    86.1
	  122572   1693.1   93.8
	  122573   1706.5   80.5
	  122574   1247.    56.7
	  122575   1189.6   63
	  -----------------------
	         11014.6  564.9  ==>  0.0512865

	  y3scontRanges = PlotData[
	      y3scont, Union[{121800, 122000, 122000, 122220, 122400, 122500,
	  		    122700, 122900, 123200}]];

	  FindBest[y3scont, 0.0512865, y3scontRanges];

	  121906   678.4    60.2
	  121914   469.5    34.3
	  121915   1265.9   68.6
	  122081   1714.4   107.1
	  122083   1196.8   64.4
	  122264   788.     49.7
	  122269   1553.    86.8
	  122418   1571.9   68.6
	  122427   1581.7   83.3
	  122428   1779.4   86.1
	  122585   1673.4   87.5
	  122593   682.     30.1
	  122797   1613.7   69.3
	  122800   1628.    62.3
	  122810   1618.9   70
	  123011   1340.8   56.7
	  -----------------------
	         21155.8  1085.  ==>  0.0512862

	  y3speakRanges = PlotData[
	      y3speak, Union[{121800, 121958, 122000, 122085, 122120, 122200,
	  		    122270, 122375, 122458, 122477, 122500, 122600,
	  		    122637, 122800, 122850, 123000, 123032, 123046, 123200}]];

	  FindBest[y3speak, 0.0512862, y3speakRanges];

	  121946   448.2    35
	  121966   2536.1   182.7
	  122079   1962.3   114.8
	  122105   1720.    119
	  122123   1781.1   137.2
	  122263   255.8    20.3
	  122301   2224.3   133
	  122454   1954.    98
	  122472   2562.4   118.3
	  122480   1412.3   61.6
	  122577   1280.1   63
	  122619   2287.6   102.9
	  122649   2275.1   94.5
	  122831   2271.1   98
	  122859   2547.1   97.3
	  123026   2113.8   71.4
	  123042   2274.7   100.8
	  123056   673.7    23.1
	  -----------------------
	         32579.7  1670.9  ==>  0.0512865
	            

