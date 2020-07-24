<< Statistics`ContinuousDistributions`;
<< Graphics`Graphics`;
<< Statistics`DescriptiveStatistics`;

WeightedMean[ points:{ { ( _Integer | _Real ), ( _Integer | _Real ) } .. } ] := Module[
    { xoversig2sum, oneoversig2sum },
    xoversig2sum = Plus @@ ( ( #[[1]] / #[[2]]^2 )& /@ points );
    oneoversig2sum = Plus @@ ( ( 1 / #[[2]]^2 )& /@ points );
    If[ oneoversig2sum == 0, { 0, 0 },
	{ xoversig2sum / oneoversig2sum, Sqrt[ 1 / oneoversig2sum ] } ] ];

PDGy1ll = WeightedMean[{{2.38, 0.11}, {2.48, 0.06}, {2.67, 0.15}/0.8588634}]/100;
PDGx0y1 = {6, 0}/100;   (* This one is just an upper limit *)
PDGx1y1 = {35, 8}/100;
PDGx2y1 = {22, 4}/100;
PDGy2ll = WeightedMean[{{1.18, 0.20}, {1.31, 0.21}, {1.7, 1.6}/0.8742721}]/100;
PDGy2p1 = {18.8, 0.6}/100;
PDGy2z1 = {9.0, 0.8}/100;
PDGy2x0 = {3.8, 0.6}/100;
PDGy2x1 = {6.8, 0.7}/100;
PDGy2x2 = {7.0, 0.6}/100;
PDGX0y1 = {9, 6}/100;
PDGX0y2 = {4.6, 2.1}/100;
PDGX1y1 = {8.5, 1.3}/100;
PDGX1y2 = {21, 4}/100;
PDGX2y1 = {7.1, 1.0}/100;
PDGX2y2 = {16.2, 2.4}/100;
PDGy3ll = {1.81, 0.17}/100;
PDGy3p1 = {4.48, 0.21}/100;
PDGy3z1 = {2.06, 0.28}/100;
PDGy3p2 = {2.8, 0.6}/100;
PDGy3z2 = {2.00, 0.32}/100;
PDGy3X0 = {5.4, 0.6}/100;
PDGy3X1 = {11.3, 0.6}/100;
PDGy3X2 = {11.4, 0.8}/100;
(* for splitting the remaining partial width into ggg and gggamma--- not relevant for l+l- *)
colfla = 3*(2*(-1/3)^2 + 2*(2/3)^2);

world[] := {y1ll -> Random[NormalDistribution @@ PDGy1ll],
	    x0y1 -> Random[Real, PDGx0y1[[1]]/2.],
	    x1y1 -> Random[NormalDistribution @@ PDGx1y1],
	    x2y1 -> Random[NormalDistribution @@ PDGx2y1],
	    y2ll -> Random[NormalDistribution @@ PDGy2ll],
	    y2p1 -> Random[NormalDistribution @@ PDGy2p1],
	    y2z1 -> Random[NormalDistribution @@ PDGy2z1],
	    y2x0 -> Random[NormalDistribution @@ PDGy2x0],
	    y2x1 -> Random[NormalDistribution @@ PDGy2x1],
	    y2x2 -> Random[NormalDistribution @@ PDGy2x2],
	    X0y1 -> Random[NormalDistribution @@ PDGX0y1],
	    X0y2 -> Random[NormalDistribution @@ PDGX0y2],
	    X1y1 -> Random[NormalDistribution @@ PDGX1y1],
	    X1y2 -> Random[NormalDistribution @@ PDGX1y2],
	    X2y1 -> Random[NormalDistribution @@ PDGX2y1],
	    X2y2 -> Random[NormalDistribution @@ PDGX2y2],
	    y3ll -> Random[NormalDistribution @@ PDGy3ll],
	    y3p1 -> Random[NormalDistribution @@ PDGy3p1],
	    y3z1 -> Random[NormalDistribution @@ PDGy3z1],
	    y3p2 -> Random[NormalDistribution @@ PDGy3p2],
	    y3z2 -> Random[NormalDistribution @@ PDGy3z2],
	    y3X0 -> Random[NormalDistribution @@ PDGy3X0],
	    y3X1 -> Random[NormalDistribution @@ PDGy3X1],
	    y3X2 -> Random[NormalDistribution @@ PDGy3X2]};
PDGworld[] := {y1ll -> PDGy1ll[[1]],
	       x0y1 -> PDGx0y1[[1]],
	       x1y1 -> PDGx1y1[[1]],
	       x2y1 -> PDGx2y1[[1]],
	       y2ll -> PDGy2ll[[1]],
	       y2p1 -> PDGy2p1[[1]],
	       y2z1 -> PDGy2z1[[1]],
	       y2x0 -> PDGy2x0[[1]],
	       y2x1 -> PDGy2x1[[1]],
	       y2x2 -> PDGy2x2[[1]],
	       X0y1 -> PDGX0y1[[1]],
	       X0y2 -> PDGX0y2[[1]],
	       X1y1 -> PDGX1y1[[1]],
	       X1y2 -> PDGX1y2[[1]],
	       X2y1 -> PDGX2y1[[1]],
	       X2y2 -> PDGX2y2[[1]],
	       y3ll -> PDGy3ll[[1]],
	       y3p1 -> PDGy3p1[[1]],
	       y3z1 -> PDGy3z1[[1]],
	       y3p2 -> PDGy3p2[[1]],
	       y3z2 -> PDGy3z2[[1]],
	       y3X0 -> PDGy3X0[[1]],
	       y3X1 -> PDGy3X1[[1]],
	       y3X2 -> PDGy3X2[[1]]};
decay[{prob_, chain_}] :=
    Switch[chain[[1]],
	   y1, {{prob * y1ll, Prepend[chain, ee]},
		{prob * y1ll, Prepend[chain, mm]},
		{prob * y1ll*0.9277, Prepend[chain, tt]},
		{prob * colfla * y1ll, Prepend[chain, qq]},
		{prob * (1 - (2.9277+colfla) * y1ll), Prepend[chain, gg]}},
	   x0, Join[{{prob * (1 - x0y1), Prepend[chain, qg]}},
		    decay[{prob * x0y1, Prepend[chain, y1]}]],
	   x1, Join[{{prob * (1 - x1y1), Prepend[chain, qg]}},
		    decay[{prob * x1y1, Prepend[chain, y1]}]],
	   x2, Join[{{prob * (1 - x2y1), Prepend[chain, qg]}},
		    decay[{prob * x2y1, Prepend[chain, y1]}]],
	   y2, Join[{{prob * y2ll, Prepend[chain, ee]},
		     {prob * y2ll, Prepend[chain, mm]},
		     {prob * y2ll*0.9355, Prepend[chain, tt]},
		     {prob * colfla * y2ll, Prepend[chain, qq]},
		     {prob * (1 - (2.9355+colfla) * y2ll
			        - y2p1 - y2z1 - y2x0 - y2x1 - y2x2), Prepend[chain, gg]}},
		    decay[{prob * y2p1, Prepend[Prepend[chain, pm], y1]}],
		    decay[{prob * y2z1, Prepend[Prepend[chain, zz], y1]}],
		    decay[{prob * y2x0, Prepend[chain, x0]}],
		    decay[{prob * y2x1, Prepend[chain, x1]}],
		    decay[{prob * y2x2, Prepend[chain, x2]}]],
	   X0, Join[{{prob * (1 - X0y1 - X0y2), Prepend[chain, qg]}},
		    decay[{prob * X0y1, Prepend[chain, y1]}],
		    decay[{prob * X0y2, Prepend[chain, y2]}]],
	   X1, Join[{{prob * (1 - X1y1 - X1y2), Prepend[chain, qg]}},
		    decay[{prob * X1y1, Prepend[chain, y1]}],
		    decay[{prob * X1y2, Prepend[chain, y2]}]],
	   X2, Join[{{prob * (1 - X2y1 - X2y2), Prepend[chain, qg]}},
		    decay[{prob * X2y1, Prepend[chain, y1]}],
		    decay[{prob * X2y2, Prepend[chain, y2]}]],
	   y3, Join[{{prob * y3ll, Prepend[chain, ee]},
		     {prob * y3ll, Prepend[chain, mm]},
		     {prob * y3ll*0.9834, Prepend[chain, tt]},
		     {prob * colfla * y3ll, Prepend[chain, qq]},
		     {prob * (1 - (2.9834+colfla)*y3ll
			        - y3p1 - y3z1 - y3p2 - y3z2 - y3X0 - y3X1 - y3X2), Prepend[chain, gg]}},
		    decay[{prob * y3p1, Prepend[Prepend[chain, pm], y1]}],
		    decay[{prob * y3z1, Prepend[Prepend[chain, zz], y1]}],
		    decay[{prob * y3p2, Prepend[Prepend[chain, pm], y2]}],
		    decay[{prob * y3z2, Prepend[Prepend[chain, zz], y2]}],
		    decay[{prob * y3X0, Prepend[chain, X0]}],
		    decay[{prob * y3X1, Prepend[chain, X1]}],
		    decay[{prob * y3X2, Prepend[chain, X2]}]]
	  ];
latex[chain_] :=
    Module[{chain2 = Reverse[chain], i, out = ""},
	   For[i = 1, i <= Length[chain2], i++,
	       Switch[chain2[[i]],
		      ee, out = out <> "e^+ e^-",
		      mm, out = out <> "\\mu^+ \\mu^-",
		      ll, out = out <> "\\ldots \\to \\ell^+ \\ell^-",
		      tt, out = out <> "\\tau^+ \\tau^-",
		      qq, out = out <> "q\\bar{q}",
		      gg, out = out <> "ggg, gg\\gamma",
		      qg, out = out <> "gg",
		      x0, out = out <> "\\gamma \\chi_{b0}(1P)",
		      x1, out = out <> "\\gamma \\chi_{b1}(1P)",
		      x2, out = out <> "\\gamma \\chi_{b2}(1P)",
		      X0, out = out <> "\\gamma \\chi_{b0}(2P)",
		      X1, out = out <> "\\gamma \\chi_{b1}(2P)",
		      X2, out = out <> "\\gamma \\chi_{b2}(2P)",
		      y1, out = out <> "\\Upsilon(1S)",
		      y2, out = out <> "\\Upsilon(2S)",
		      y3, out = out <> "\\Upsilon(3S)",
		      pm, (i++; out = out <> Switch[chain2[[i]], y1, "\\pi^+ \\pi^- \\Upsilon(1S)", y2, "\\pi^+ \\pi^- \\Upsilon(2S)"]),
		      zz, (i++; out = out <> Switch[chain2[[i]], y1, "\\pi^0 \\pi^0 \\Upsilon(1S)", y2, "\\pi^0 \\pi^0 \\Upsilon(2S)"])
		     ];
	       If[i != Length[chain2], out = out <> " \\to "]];
	   out];

y1rows = Select[decay[{1, {y1}}], (#[[2,1]] == ee  ||  #[[2,1]] == mm)&];
y2rows = Select[decay[{1, {y2}}], (#[[2,1]] == ee  ||  #[[2,1]] == mm)&];
y3rows = Select[decay[{1, {y3}}], (#[[2,1]] == ee  ||  #[[2,1]] == mm)&];

y1rows = Append[y1rows, {Plus @@ (#[[1]]& /@ y1rows), {ll, y1}}];
y2rows = Append[y2rows, {Plus @@ (#[[1]]& /@ y2rows), {ll, y2}}];
y3rows = Append[y3rows, {Plus @@ (#[[1]]& /@ y3rows), {ll, y3}}];

y1columns = Transpose[{#[[1]], latex[#[[2]]]}& /@ y1rows];
y2columns = Transpose[{#[[1]], latex[#[[2]]]}& /@ y2rows];
y3columns = Transpose[{#[[1]], latex[#[[2]]]}& /@ y3rows];

y1uncerts = StandardDeviation /@ Transpose[Table[y1columns[[1]] /. world[], {20000}]];
y2uncerts = StandardDeviation /@ Transpose[Table[y2columns[[1]] /. world[], {20000}]];
y3uncerts = StandardDeviation /@ Transpose[Table[y3columns[[1]] /. world[], {20000}]];

SetOptions[$Output, PageWidth -> Infinity, PageHeight -> Infinity];

Print[{"$", #[[1]], "$ & $", SetPrecision[#[[2]], 3], "$ & $", SetPrecision[#[[3]], 2], "$ \\\\ "}& /@ Transpose[Join[Reverse[y1columns /. PDGworld[]], {y1uncerts}]] // TableForm]; Print[];
Print[{"$", #[[1]], "$ & $", SetPrecision[#[[2]], 3], "$ & $", SetPrecision[#[[3]], 2], "$ \\\\ "}& /@ Transpose[Join[Reverse[y2columns /. PDGworld[]], {y2uncerts}]] // TableForm]; Print[];
Print[{"$", #[[1]], "$ & $", SetPrecision[#[[2]], 3], "$ & $", SetPrecision[#[[3]], 2], "$ \\\\ "}& /@ Transpose[Join[Reverse[y3columns /. PDGworld[]], {y3uncerts}]] // TableForm];

$   \Upsilon(1S) \to e^+ e^-                    $ & $   0.0251   $ & $   0.00050   $ \\ 
$   \Upsilon(1S) \to \mu^+ \mu^-                $ & $   0.0251   $ & $   0.00050   $ \\ 
$   \Upsilon(1S) \to \ldots \to \ell^+ \ell^-   $ & $   0.0502   $ & $   0.0010    $ \\ 
$   \Upsilon(2S) \to e^+ e^-                                                 $ & $   0.0125      $ & $   0.0014     $ \\ 
$   \Upsilon(2S) \to \mu^+ \mu^-                                             $ & $   0.0125      $ & $   0.0014     $ \\ 
$   \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to e^+ e^-                    $ & $   0.00472     $ & $   0.00018    $ \\ 
$   \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \mu^+ \mu^-                $ & $   0.00472     $ & $   0.00018    $ \\ 
$   \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to e^+ e^-                    $ & $   0.00226     $ & $   0.00020    $ \\ 
$   \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \mu^+ \mu^-                $ & $   0.00226     $ & $   0.00020    $ \\ 
$   \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to e^+ e^-       $ & $   0.0000573   $ & $   8.6 10^-6  $ \\ 
$   \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-   $ & $   0.0000573   $ & $   8.6 10^-6  $ \\ 
$   \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to e^+ e^-       $ & $   0.000598    $ & $   0.00015    $ \\ 
$   \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-   $ & $   0.000598    $ & $   0.00015    $ \\ 
$   \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to e^+ e^-       $ & $   0.000387    $ & $   0.000078   $ \\ 
$   \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-   $ & $   0.000387    $ & $   0.000078   $ \\ 
$   \Upsilon(2S) \to \ldots \to \ell^+ \ell^-                                $ & $   0.0410      $ & $   0.0030     $ \\ 
$   \Upsilon(3S) \to e^+ e^-                                                                                           $ & $   0.0181      $ & $   0.0017     $ \\ 
$   \Upsilon(3S) \to \mu^+ \mu^-                                                                                       $ & $   0.0181      $ & $   0.0017     $ \\ 
$   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(1S) \to e^+ e^-                                                              $ & $   0.00113     $ & $   0.000058   $ \\ 
$   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(1S) \to \mu^+ \mu^-                                                          $ & $   0.00113     $ & $   0.000058   $ \\ 
$   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(1S) \to e^+ e^-                                                              $ & $   0.000517    $ & $   0.000071   $ \\ 
$   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(1S) \to \mu^+ \mu^-                                                          $ & $   0.000517    $ & $   0.000071   $ \\ 
$   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to e^+ e^-                                                              $ & $   0.000349    $ & $   0.000086   $ \\ 
$   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \mu^+ \mu^-                                                          $ & $   0.000349    $ & $   0.000086   $ \\ 
$   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to e^+ e^-                                 $ & $   0.000132    $ & $   0.000029   $ \\ 
$   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \mu^+ \mu^-                             $ & $   0.000132    $ & $   0.000029   $ \\ 
$   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to e^+ e^-                                 $ & $   0.0000633   $ & $   0.000015   $ \\ 
$   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \mu^+ \mu^-                             $ & $   0.0000633   $ & $   0.000015   $ \\ 
$   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to e^+ e^-                    $ & $   1.60 10^-6  $ & $   2.6 10^-7  $ \\ 
$   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-                $ & $   1.60 10^-6  $ & $   2.6 10^-7  $ \\ 
$   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to e^+ e^-                    $ & $   0.0000167   $ & $   5.6 10^-6  $ \\ 
$   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-                $ & $   0.0000167   $ & $   5.6 10^-6  $ \\ 
$   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to e^+ e^-                    $ & $   0.0000108   $ & $   3.2 10^-6  $ \\ 
$   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-                $ & $   0.0000108   $ & $   3.2 10^-6  $ \\ 
$   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to e^+ e^-                                                              $ & $   0.000249    $ & $   0.000049   $ \\ 
$   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \mu^+ \mu^-                                                          $ & $   0.000249    $ & $   0.000049   $ \\ 
$   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to e^+ e^-                                 $ & $   0.0000944   $ & $   0.000016   $ \\ 
$   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \mu^+ \mu^-                             $ & $   0.0000944   $ & $   0.000016   $ \\ 
$   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to e^+ e^-                                 $ & $   0.0000452   $ & $   8.4 10^-6  $ \\ 
$   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \mu^+ \mu^-                             $ & $   0.0000452   $ & $   8.4 10^-6  $ \\ 
$   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to e^+ e^-                    $ & $   1.15 10^-6  $ & $   1.8 10^-7  $ \\ 
$   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-                $ & $   1.15 10^-6  $ & $   1.8 10^-7  $ \\ 
$   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to e^+ e^-                    $ & $   0.0000120   $ & $   3.6 10^-6  $ \\ 
$   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-                $ & $   0.0000120   $ & $   3.6 10^-6  $ \\ 
$   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to e^+ e^-                    $ & $   7.74 10^-6  $ & $   2.0 10^-6  $ \\ 
$   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-                $ & $   7.74 10^-6  $ & $   2.0 10^-6  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(1S) \to e^+ e^-                                                 $ & $   0.000122    $ & $   0.000083   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(1S) \to \mu^+ \mu^-                                             $ & $   0.000122    $ & $   0.000083   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to e^+ e^-                                                 $ & $   0.0000310   $ & $   0.000015   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \mu^+ \mu^-                                             $ & $   0.0000310   $ & $   0.000015   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to e^+ e^-                    $ & $   0.0000117   $ & $   5.6 10^-6  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \mu^+ \mu^-                $ & $   0.0000117   $ & $   5.6 10^-6  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to e^+ e^-                    $ & $   5.61 10^-6  $ & $   2.7 10^-6  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \mu^+ \mu^-                $ & $   5.61 10^-6  $ & $   2.7 10^-6  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to e^+ e^-       $ & $   1.42 10^-7  $ & $   2.9 10^-8  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-   $ & $   1.42 10^-7  $ & $   2.9 10^-8  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to e^+ e^-       $ & $   1.48 10^-6  $ & $   8.2 10^-7  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-   $ & $   1.48 10^-6  $ & $   8.2 10^-7  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to e^+ e^-       $ & $   9.61 10^-7  $ & $   5.0 10^-7  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-   $ & $   9.61 10^-7  $ & $   5.0 10^-7  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(1S) \to e^+ e^-                                                 $ & $   0.000241    $ & $   0.000039   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(1S) \to \mu^+ \mu^-                                             $ & $   0.000241    $ & $   0.000039   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to e^+ e^-                                                 $ & $   0.000296    $ & $   0.000068   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \mu^+ \mu^-                                             $ & $   0.000296    $ & $   0.000068   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to e^+ e^-                    $ & $   0.000112    $ & $   0.000023   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \mu^+ \mu^-                $ & $   0.000112    $ & $   0.000023   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to e^+ e^-                    $ & $   0.0000536   $ & $   0.000012   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \mu^+ \mu^-                $ & $   0.0000536   $ & $   0.000012   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to e^+ e^-       $ & $   1.36 10^-6  $ & $   2.2 10^-7  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-   $ & $   1.36 10^-6  $ & $   2.2 10^-7  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to e^+ e^-       $ & $   0.0000142   $ & $   4.6 10^-6  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-   $ & $   0.0000142   $ & $   4.6 10^-6  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to e^+ e^-       $ & $   9.18 10^-6  $ & $   2.6 10^-6  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-   $ & $   9.18 10^-6  $ & $   2.6 10^-6  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(1S) \to e^+ e^-                                                 $ & $   0.000203    $ & $   0.000032   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(1S) \to \mu^+ \mu^-                                             $ & $   0.000203    $ & $   0.000032   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to e^+ e^-                                                 $ & $   0.000230    $ & $   0.000047   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \mu^+ \mu^-                                             $ & $   0.000230    $ & $   0.000047   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to e^+ e^-                    $ & $   0.0000872   $ & $   0.000015   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \mu^+ \mu^-                $ & $   0.0000872   $ & $   0.000015   $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to e^+ e^-                    $ & $   0.0000417   $ & $   7.9 10^-6  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \mu^+ \mu^-                $ & $   0.0000417   $ & $   7.9 10^-6  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to e^+ e^-       $ & $   1.06 10^-6  $ & $   1.7 10^-7  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-   $ & $   1.06 10^-6  $ & $   1.7 10^-7  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to e^+ e^-       $ & $   0.0000110   $ & $   3.4 10^-6  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-   $ & $   0.0000110   $ & $   3.4 10^-6  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to e^+ e^-       $ & $   7.14 10^-6  $ & $   1.9 10^-6  $ \\ 
$   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-   $ & $   7.14 10^-6  $ & $   1.9 10^-6  $ \\ 
$   \Upsilon(3S) \to \ldots \to \ell^+ \ell^-                                                                          $ & $   0.0444      $ & $   0.0034     $ \\ 

