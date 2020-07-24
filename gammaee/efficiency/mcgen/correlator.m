<< Statistics`ContinuousDistributions`;
<< Graphics`Graphics`;
<< Statistics`DescriptiveStatistics`;

WeightedMean[ points:{ { ( _Integer | _Real ), ( _Integer | _Real ) } .. } ] := Module[
    { xoversig2sum, oneoversig2sum },
    xoversig2sum = Plus @@ ( ( #[[1]] / #[[2]]^2 )& /@ points );
    oneoversig2sum = Plus @@ ( ( 1 / #[[2]]^2 )& /@ points );
    If[ oneoversig2sum == 0, { 0, 0 },
	{ xoversig2sum / oneoversig2sum, Sqrt[ 1 / oneoversig2sum ] } ] ];

PDGy1ll = WeightedMean[{{2.38, 0.11}, {2.48, 0.06}, {2.67, 0.15}/0.9277}]/100;
PDGx0y1 = {3, 3}/100;   (* This one is just an upper limit *)
PDGx1y1 = {35, 8}/100;
PDGx2y1 = {22, 4}/100;
PDGy2ll = WeightedMean[{{1.18, 0.20}, {1.31, 0.21}, {1.7, 1.6}/0.9355}]/100;
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
colfla = 3*(2*(-1/3)^2 + 2*(2/3)^2);

world[] := {y1ll -> Random[NormalDistribution @@ PDGy1ll],
	    x0y1 -> Random[Real, PDGx0y1[[1]]],
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

dirName[chain_] :=
    Module[{chain2 = Reverse[chain], i, out = ""},
	   For[i = 1, i <= Length[chain2], i++,
	       Switch[chain2[[i]],
		      ee, out = out <> "ee",
		      mm, out = out <> "mm",
		      tt, out = out <> "tt",
		      qq, out = out <> "qq",
		      gg, out = out <> "gg",
		      qg, out = out <> "qg",
		      x0, out = out <> "x0",
		      x1, out = out <> "x1",
		      x2, out = out <> "x2",
		      X0, out = out <> "X0",
		      X1, out = out <> "X1",
		      X2, out = out <> "X2",
		      y1, out = out <> "y1",
		      y2, out = out <> "y2",
		      y3, out = out <> "y3",
		      pm, (i++; out = out <> Switch[chain2[[i]], y1, "p1", y2, "p2"]),
		      zz, (i++; out = out <> Switch[chain2[[i]], y1, "z1", y2, "z2"])
		     ]];
	   out];

latex[chain_] :=
    Module[{chain2 = Reverse[chain], i, out = ""},
	   For[i = 1, i <= Length[chain2], i++,
	       Switch[chain2[[i]],
		      ee, out = out <> "e^+ e^-",
		      mm, out = out <> "\\mu^+ \\mu^-",
		      tt, out = out <> "\\tau^+ \\tau^-",
		      qq, out = out <> "q\\bar{q}",
		      gg, out = out <> "ggg, gg\\gamma",
		      qg, out = out <> "{\\tt Channel -1}",
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

TableForm[{CForm[#[[1]] /. PDGworld[]], latex[#[[2]]]}& /@ Join[decay[{1, {y1}}], decay[{1, {y2}}], decay[{1, {y3}}]]]

y1columns = Transpose[{#[[1]], latex[#[[2]]]}& /@ decay[{1, {y1}}]];
y2columns = Transpose[{#[[1]], latex[#[[2]]]}& /@ decay[{1, {y2}}]];
y3columns = Transpose[{#[[1]], latex[#[[2]]]}& /@ decay[{1, {y3}}]];

y1uncerts = StandardDeviation /@ Transpose[Table[y1columns[[1]] /. world[], {5000}]];
y2uncerts = StandardDeviation /@ Transpose[Table[y2columns[[1]] /. world[], {5000}]];
y3uncerts = StandardDeviation /@ Transpose[Table[y3columns[[1]] /. world[], {5000}]];

SetOptions[$Output, PageWidth -> Infinity, PageHeight -> Infinity];

{"$", #[[1]], "$ & $", CForm[#[[2]]], "$ & $", CForm[#[[3]]], "$ \\\\ "}& /@ Sort[Transpose[Join[Reverse[y1columns /. PDGworld[]], {y1uncerts}]], (#1[[3]] > #2[[3]])&] // TableForm

Out[67]//TableForm= $   \Upsilon(1S) \to ggg, gg\gamma   $ & $   0.8436329567155215     $ & $   0.003141464699494952    $ \\ 

                    $   \Upsilon(1S) \to q\bar{q}        $ & $   0.0832487945464159     $ & $   0.0016724953279783142   $ \\ 

                    $   \Upsilon(1S) \to \mu^+ \mu^-     $ & $   0.02497463836392477    $ & $   0.0005017485983934946   $ \\ 

                    $   \Upsilon(1S) \to e^+ e^-         $ & $   0.02497463836392477    $ & $   0.0005017485983934946   $ \\ 

                    $   \Upsilon(1S) \to \tau^+ \tau^-   $ & $   0.023168972010213007   $ & $   0.0004654721747296451   $ \\ 

{"$", #[[1]], "$ & $", CForm[#[[2]]], "$ & $", CForm[#[[3]]], "$ \\\\ "}& /@ Sort[Transpose[Join[Reverse[y2columns /. PDGworld[]], {y2uncerts}]], (#1[[3]] > #2[[3]])&] // TableForm

Out[68]//TableForm= $   \Upsilon(2S) \to ggg, gg\gamma                                             $ & $   0.4678948789505143        $ & $   0.01720096912997229       $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to {\tt Channel -1}                 $ & $   0.0442                    $ & $   0.007110777790067498      $ \\ 

                    $   \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to ggg, gg\gamma                $ & $   0.07592696610439693       $ & $   0.006677653308142459      $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to {\tt Channel -1}                 $ & $   0.03686                   $ & $   0.005950274322944534      $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to {\tt Channel -1}                 $ & $   0.05460000000000001       $ & $   0.005481912766803801      $ \\ 

                    $   \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to ggg, gg\gamma                $ & $   0.15860299586251805       $ & $   0.005130245366371323      $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to ggg, gg\gamma   $ & $   0.020078464369829414      $ & $   0.004949411786873756      $ \\ 

                    $   \Upsilon(2S) \to q\bar{q}                                                  $ & $   0.04153091805997163       $ & $   0.004779906268075147      $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to ggg, gg\gamma   $ & $   0.012991947533419031      $ & $   0.002604930483370686      $ \\ 

                    $   \Upsilon(2S) \to \mu^+ \mu^-                                               $ & $   0.01245927541799149       $ & $   0.0014339718804225444     $ \\ 

                    $   \Upsilon(2S) \to e^+ e^-                                                   $ & $   0.01245927541799149       $ & $   0.0014339718804225444     $ \\ 

                    $   \Upsilon(2S) \to \tau^+ \tau^-                                             $ & $   0.011655652153531038      $ & $   0.0013414806941352885     $ \\ 

                    $   \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to q\bar{q}                     $ & $   0.00749239150917743       $ & $   0.000675425794994511      $ \\ 

                    $   \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to q\bar{q}                     $ & $   0.015650773374726187      $ & $   0.0005813145029558868     $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to q\bar{q}        $ & $   0.0019813213102046986     $ & $   0.0004892869420996431     $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to ggg, gg\gamma   $ & $   0.0009617415706556945     $ & $   0.00028956284288712863    $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to q\bar{q}        $ & $   0.0012820314360148049     $ & $   0.0002583880395903322     $ \\ 

                    $   \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \mu^+ \mu^-                  $ & $   0.002247717452753229      $ & $   0.00020262773849835357    $ \\ 

                    $   \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to e^+ e^-                      $ & $   0.002247717452753229      $ & $   0.00020262773849835357    $ \\ 

                    $   \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \tau^+ \tau^-                $ & $   0.0020852074809191708     $ & $   0.00018797775300492242    $ \\ 

                    $   \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \mu^+ \mu^-                  $ & $   0.004695232012417856      $ & $   0.00017439435088676577    $ \\ 

                    $   \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to e^+ e^-                      $ & $   0.004695232012417856      $ & $   0.00017439435088676577    $ \\ 

                    $   \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \tau^+ \tau^-                $ & $   0.004355766737920046      $ & $   0.00016178563931765278    $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-     $ & $   0.0005943963930614096     $ & $   0.00014678608262989323    $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to e^+ e^-         $ & $   0.0005943963930614096     $ & $   0.00014678608262989323    $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-   $ & $   0.0005514215338430696     $ & $   0.0001361734488557518     $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-     $ & $   0.00038460943080444144    $ & $   0.0000775164118770998     $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to e^+ e^-         $ & $   0.00038460943080444144    $ & $   0.0000775164118770998     $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-   $ & $   0.0003568021689572804     $ & $   0.0000719119752983854     $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to q\bar{q}        $ & $   0.00009490362578291412    $ & $   0.000028583302675163613   $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-     $ & $   0.000028471087734874235   $ & $   8.574990802549073e-6      $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to e^+ e^-         $ & $   0.000028471087734874235   $ & $   8.574990802549073e-6      $ \\ 

                    $   \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-   $ & $   0.000026412628091642824   $ & $   7.95501896752479e-6       $ \\ 

{"$", #[[1]], "$ & $", CForm[#[[2]]], "$ & $", CForm[#[[3]]], "$ \\\\ "}& /@ Sort[Transpose[Join[Reverse[y3columns /. PDGworld[]], {y3uncerts}]], (#1[[3]] > #2[[3]])&] // TableForm

Out[69]//TableForm= $   \Upsilon(3S) \to ggg, gg\gamma                                                                                       $ & $   0.4912671266666667        $ & $   0.017642169902263676      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to {\tt Channel -1}                                                           $ & $   0.087438                  $ & $   0.006841480564421012      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to {\tt Channel -1}                                                           $ & $   0.07966500000000001       $ & $   0.006411165930070826      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to {\tt Channel -1}                                                           $ & $   0.046656                  $ & $   0.0061649390705526075     $ \\ 

                    $   \Upsilon(3S) \to q\bar{q}                                                                                            $ & $   0.06033333333333334       $ & $   0.005676791133850991      $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to ggg, gg\gamma                                                          $ & $   0.0131010566106144        $ & $   0.002868697342982044      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(1S) \to ggg, gg\gamma                                             $ & $   0.004100056169637435      $ & $   0.0027669158078517365     $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(1S) \to ggg, gg\gamma                                                          $ & $   0.017378838908339744      $ & $   0.002340826198356129      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to ggg, gg\gamma                                             $ & $   0.011103145477495704      $ & $   0.0022377918791107476     $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(1S) \to ggg, gg\gamma                                                          $ & $   0.03779475646085537       $ & $   0.001770956494351466      $ \\ 

                    $   \Upsilon(3S) \to \mu^+ \mu^-                                                                                         $ & $   0.0181                    $ & $   0.0017030373401552956     $ \\ 

                    $   \Upsilon(3S) \to e^+ e^-                                                                                             $ & $   0.0181                    $ & $   0.0017030373401552956     $ \\ 

                    $   \Upsilon(3S) \to \tau^+ \tau^-                                                                                       $ & $   0.017799540000000003      $ & $   0.0016747669203087167     $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to ggg, gg\gamma                                                          $ & $   0.009357897579010286      $ & $   0.0015397642741301018     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to ggg, gg\gamma                                             $ & $   0.0086410826244581        $ & $   0.0014577941866345636     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(1S) \to ggg, gg\gamma                                             $ & $   0.008103094549252584      $ & $   0.0013370916440071212     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(1S) \to ggg, gg\gamma                                             $ & $   0.00682836515165543       $ & $   0.0010516710493727421     $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to ggg, gg\gamma                             $ & $   0.004440883884150505      $ & $   0.0009637372051599356     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to ggg, gg\gamma                $ & $   0.0037636490918175535     $ & $   0.0007515311014302686     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to ggg, gg\gamma                                             $ & $   0.0011622508793130775     $ & $   0.0005539468891637664     $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to ggg, gg\gamma                             $ & $   0.0031720599172503612     $ & $   0.0005193263164659966     $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to ggg, gg\gamma                             $ & $   0.002125955050923114      $ & $   0.0004967993844571649     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to ggg, gg\gamma                $ & $   0.002929080127588984      $ & $   0.000490028603948561      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to ggg, gg\gamma                $ & $   0.0018017469056573394     $ & $   0.000389084941115037      $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to {\tt Channel -1}                              $ & $   0.0015288                 $ & $   0.00036341229746350773    $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to {\tt Channel -1}                              $ & $   0.0012376000000000002     $ & $   0.0003352014030056047     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to {\tt Channel -1}                 $ & $   0.0012956580000000003     $ & $   0.00028615437687749904    $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to q\bar{q}                                                               $ & $   0.0011628657056792055     $ & $   0.00028435832479392506    $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to {\tt Channel -1}                              $ & $   0.0010320799999999999     $ & $   0.00028195325876733556    $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to ggg, gg\gamma                             $ & $   0.001518539322087939      $ & $   0.00027543202602067       $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(1S) \to q\bar{q}                                                  $ & $   0.0004045891414955813     $ & $   0.0002735484828908395     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to {\tt Channel -1}                 $ & $   0.001048866               $ & $   0.0002695288599091853     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to ggg, gg\gamma                $ & $   0.0014022192100160028     $ & $   0.0002596199056776362     $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(1S) \to q\bar{q}                                                               $ & $   0.0017149251676561676     $ & $   0.0002334182995362071     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to {\tt Channel -1}                 $ & $   0.0008746877999999999     $ & $   0.00022728238960974595    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to q\bar{q}                                                  $ & $   0.0009855286855631272     $ & $   0.00022427546975040843    $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to {\tt Channel -1}                              $ & $   0.001092                  $ & $   0.00020480332059446158    $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to {\tt Channel -1}                              $ & $   0.0008840000000000001     $ & $   0.00020394760422306032    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to {\tt Channel -1}                 $ & $   0.0010083528000000002     $ & $   0.0001966824697709904     $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(1S) \to q\bar{q}                                                               $ & $   0.0037295459956794325     $ & $   0.00018761663346851675    $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to ggg, gg\gamma                $ & $   0.0005621970023552235     $ & $   0.00018750685101356692    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to ggg, gg\gamma                $ & $   0.00039396984172249485    $ & $   0.00018736719691554815    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to {\tt Channel -1}                 $ & $   0.0008162856000000001     $ & $   0.0001871638453024341     $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to {\tt Channel -1}                              $ & $   0.0007372                 $ & $   0.0001740057926188925     $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to q\bar{q}                                                               $ & $   0.0008306183611994326     $ & $   0.00016219759542369136    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to {\tt Channel -1}                 $ & $   0.00068073048             $ & $   0.00015960467949639845    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to q\bar{q}                                                  $ & $   0.0007669929947315563     $ & $   0.00015503378398290312    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to ggg, gg\gamma   $ & $   0.000476461959496052      $ & $   0.00015442189227197236    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(1S) \to q\bar{q}                                                  $ & $   0.0007996046716183248     $ & $   0.00013275222950623499    $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to ggg, gg\gamma                $ & $   0.0004015692873965883     $ & $   0.00012028974041309474    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to ggg, gg\gamma   $ & $   0.00037080907998200967    $ & $   0.00011269129748399197    $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to ggg, gg\gamma                $ & $   0.00036377453093573286    $ & $   0.00010826009605356232    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(1S) \to q\bar{q}                                                  $ & $   0.0006738157430586903     $ & $   0.00010458158118734347    $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to q\bar{q}                                  $ & $   0.0004382216544923332     $ & $   0.00009548261541595423    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to ggg, gg\gamma                $ & $   0.000188602583803322      $ & $   0.00009106870114701827    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to ggg, gg\gamma   $ & $   0.00030829891496803367    $ & $   0.00008988205372716712    $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \mu^+ \mu^-                                                            $ & $   0.00034885971170376165    $ & $   0.0000853074974381775     $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to e^+ e^-                                                                $ & $   0.00034885971170376165    $ & $   0.0000853074974381775     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(1S) \to \mu^+ \mu^-                                               $ & $   0.0001213767424486744     $ & $   0.00008206454486725192    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(1S) \to e^+ e^-                                                   $ & $   0.0001213767424486744     $ & $   0.00008206454486725192    $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \tau^+ \tau^-                                                          $ & $   0.00032635826029886906    $ & $   0.000079805163853415      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(1S) \to \tau^+ \tau^-                                             $ & $   0.00011260120396963522    $ & $   0.00007613127827334953    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to q\bar{q}                     $ & $   0.0003713928521822525     $ & $   0.00007467808532349398    $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(1S) \to \mu^+ \mu^-                                                            $ & $   0.0005144775502968502     $ & $   0.00007002548986086229    $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(1S) \to e^+ e^-                                                                $ & $   0.0005144775502968502     $ & $   0.00007002548986086229    $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to ggg, gg\gamma                $ & $   0.0002598389506683807     $ & $   0.00006798300731147231    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \mu^+ \mu^-                                               $ & $   0.00029565860566893804    $ & $   0.00006728264092512277    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to e^+ e^-                                                   $ & $   0.00029565860566893804    $ & $   0.00006728264092512277    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to {\tt Channel -1}                 $ & $   0.00013562640000000002    $ & $   0.00006557999835066234    $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(1S) \to \tau^+ \tau^-                                                          $ & $   0.00047728082341038795    $ & $   0.00006496264694392182    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \tau^+ \tau^-                                             $ & $   0.0002765886256032916     $ & $   0.00006294291058545226    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to ggg, gg\gamma   $ & $   0.00023993528704718272    $ & $   0.00006289164421349195    $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(1S) \to \mu^+ \mu^-                                                            $ & $   0.0011188637987038297     $ & $   0.00005628499004055508    $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(1S) \to e^+ e^-                                                                $ & $   0.0011188637987038297     $ & $   0.00005628499004055508    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to {\tt Channel -1}                 $ & $   0.00010979280000000001    $ & $   0.0000554898927146328     $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(1S) \to \tau^+ \tau^-                                                          $ & $   0.001037969946057543      $ & $   0.00005221558526062286    $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to q\bar{q}                                  $ & $   0.00031301546749452376    $ & $   0.000051710499352278166   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to q\bar{q}                                                  $ & $   0.00010316280046096955    $ & $   0.00005071179567111086    $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to q\bar{q}                                  $ & $   0.00020978696225696804    $ & $   0.0000492283085457416     $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \mu^+ \mu^-                                                            $ & $   0.0002491855083598298     $ & $   0.00004865927862710732    $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to e^+ e^-                                                                $ & $   0.0002491855083598298     $ & $   0.00004865927862710732    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to q\bar{q}                     $ & $   0.0002890384826844433     $ & $   0.00004852224495810803    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to {\tt Channel -1}                 $ & $   0.00009156024             $ & $   0.00004655188157155197    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \mu^+ \mu^-                                               $ & $   0.00023009789841946685    $ & $   0.00004651013519487099    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to e^+ e^-                                                   $ & $   0.00023009789841946685    $ & $   0.00004651013519487099    $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \tau^+ \tau^-                                                          $ & $   0.00023311304307062076    $ & $   0.00004552075515565897    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \tau^+ \tau^-                                             $ & $   0.00021525658397141125    $ & $   0.0000435102314748019     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(1S) \to \mu^+ \mu^-                                               $ & $   0.00023988140148549744    $ & $   0.000039825668851870474   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(1S) \to e^+ e^-                                                   $ & $   0.00023988140148549744    $ & $   0.000039825668851870474   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to q\bar{q}                     $ & $   0.00017779445051278045    $ & $   0.000038662094652366996   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(1S) \to \tau^+ \tau^-                                             $ & $   0.00022253797615809595    $ & $   0.00003694627299388023    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(1S) \to \mu^+ \mu^-                                               $ & $   0.00020214472291760704    $ & $   0.00003137447435620302    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(1S) \to e^+ e^-                                                   $ & $   0.00020214472291760704    $ & $   0.00003137447435620302    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(1S) \to \tau^+ \tau^-                                             $ & $   0.00018752965945066408    $ & $   0.00002910609986024953    $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \mu^+ \mu^-                               $ & $   0.00013146649634769998    $ & $   0.00002864478462478629    $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to e^+ e^-                                   $ & $   0.00013146649634769998    $ & $   0.00002864478462478629    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to ggg, gg\gamma   $ & $   0.00004987490549465626    $ & $   0.000027737326647118163   $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to q\bar{q}                                  $ & $   0.0001498478301835486     $ & $   0.00002738387916746006    $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \tau^+ \tau^-                             $ & $   0.00012196146866176126    $ & $   0.000026573766696414284   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to q\bar{q}                     $ & $   0.0001383694863914888     $ & $   0.000025710016371110427   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \mu^+ \mu^-                  $ & $   0.00011141785565467574    $ & $   0.000022403425597048234   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to e^+ e^-                      $ & $   0.00011141785565467574    $ & $   0.000022403425597048234   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \tau^+ \tau^-                $ & $   0.00010336234469084267    $ & $   0.000020783657926381626   $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to q\bar{q}                     $ & $   0.000055476996685731555   $ & $   0.000018550780003421506   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to q\bar{q}                     $ & $   0.00003887652106281986    $ & $   0.000018504133979659216   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to ggg, gg\gamma   $ & $   0.00003227199767301287    $ & $   0.000016979424137618447   $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \mu^+ \mu^-                               $ & $   0.00009390464024835714    $ & $   0.00001551314980568344    $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to e^+ e^-                                   $ & $   0.00009390464024835714    $ & $   0.00001551314980568344    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to q\bar{q}        $ & $   0.00004701675469115749    $ & $   0.000015273741256372324   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \mu^+ \mu^-                                               $ & $   0.00003094884013829086    $ & $   0.000015213538701333248   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to e^+ e^-                                                   $ & $   0.00003094884013829086    $ & $   0.000015213538701333248   $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \mu^+ \mu^-                               $ & $   0.00006293608867709042    $ & $   0.000014768492563722457   $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to e^+ e^-                                   $ & $   0.00006293608867709042    $ & $   0.000014768492563722457   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \mu^+ \mu^-                  $ & $   0.00008671154480533299    $ & $   0.000014556673487432394   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to e^+ e^-                      $ & $   0.00008671154480533299    $ & $   0.000014556673487432394   $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \tau^+ \tau^-                             $ & $   0.00008711533475840091    $ & $   0.00001439154907473255    $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \tau^+ \tau^-                                             $ & $   0.000028952639949371103   $ & $   0.000014232265455097264   $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \tau^+ \tau^-                             $ & $   0.000058385809465736774   $ & $   0.000013700730551365361   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \tau^+ \tau^-                $ & $   0.0000804423001159074     $ & $   0.00001350422599429105    $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to q\bar{q}                     $ & $   0.000039626426204093966   $ & $   0.000011906383933847882   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \mu^+ \mu^-                  $ & $   0.00005333833515383413    $ & $   0.000011598628395710123   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to e^+ e^-                      $ & $   0.00005333833515383413    $ & $   0.000011598628395710123   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to q\bar{q}        $ & $   0.00003659104195686038    $ & $   0.000011140429508945442   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \tau^+ \tau^-                $ & $   0.00004948197352221192    $ & $   0.000010760047562700283   $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to q\bar{q}                     $ & $   0.000035896880208414534   $ & $   0.000010715033030118046   $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to q\bar{q}                     $ & $   0.00001861110050879674    $ & $   8.991786517502635e-6      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to q\bar{q}        $ & $   0.000030422605976631322   $ & $   8.897294975899656e-6      $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to ggg, gg\gamma                $ & $   0.000026928763978359447   $ & $   8.71931988941713e-6       $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \mu^+ \mu^-                               $ & $   0.00004495434905506459    $ & $   8.21516375023803e-6       $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to e^+ e^-                                   $ & $   0.00004495434905506459    $ & $   8.21516375023803e-6       $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \mu^+ \mu^-                  $ & $   0.00004151084591744664    $ & $   7.713004911333137e-6      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to e^+ e^-                      $ & $   0.00004151084591744664    $ & $   7.713004911333137e-6      $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \tau^+ \tau^-                             $ & $   0.00004170414961838342    $ & $   7.621207411095817e-6      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to ggg, gg\gamma   $ & $   0.00002282212747165963    $ & $   7.4149493153856204e-6     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \tau^+ \tau^-                $ & $   0.00003850961175761524    $ & $   7.15535465624375e-6       $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to q\bar{q}                     $ & $   0.000025640628720296096   $ & $   6.738885857880931e-6      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to q\bar{q}        $ & $   0.00002367655656032142    $ & $   6.2181868417610405e-6     $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to ggg, gg\gamma                $ & $   0.000019234831413113888   $ & $   6.140403248286412e-6      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to ggg, gg\gamma   $ & $   0.000017761443326869367   $ & $   5.707912792659658e-6      $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-                  $ & $   0.000016643099005719465   $ & $   5.565234001026459e-6      $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to e^+ e^-                      $ & $   0.000016643099005719465   $ & $   5.565234001026459e-6      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \mu^+ \mu^-                  $ & $   0.000011662956318845956   $ & $   5.551240193897766e-6      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to e^+ e^-                      $ & $   0.000011662956318845956   $ & $   5.551240193897766e-6      $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-                $ & $   0.00001543980294760595    $ & $   5.162867582752242e-6      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \pi^+ \pi^- \Upsilon(1S) \to \tau^+ \tau^-                $ & $   0.000010819724576993394   $ & $   5.149885527878965e-6      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-     $ & $   0.000014105026407347249   $ & $   4.582122376911698e-6      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to e^+ e^-         $ & $   0.000014105026407347249   $ & $   4.582122376911698e-6      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-   $ & $   0.000013085232998096041   $ & $   4.250834929060985e-6      $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-                  $ & $   0.000011887927861228192   $ & $   3.5719151801543684e-6     $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to e^+ e^-                      $ & $   0.000011887927861228192   $ & $   3.5719151801543684e-6     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-     $ & $   0.000010977312587058114   $ & $   3.342128852683638e-6      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to e^+ e^-         $ & $   0.000010977312587058114   $ & $   3.342128852683638e-6      $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-                $ & $   0.000011028430676861394   $ & $   3.313665712629197e-6      $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-                  $ & $   0.00001076906406252436    $ & $   3.2145099090354108e-6     $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to e^+ e^-                      $ & $   0.00001076906406252436    $ & $   3.2145099090354108e-6     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-   $ & $   0.000010183652887013811   $ & $   3.1004929366346034e-6     $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-                $ & $   9.99046073080385e-6       $ & $   2.982100842612146e-6      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to q\bar{q}        $ & $   4.9216021345484716e-6     $ & $   2.7379266693906547e-6     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \mu^+ \mu^-                  $ & $   5.583330152639022e-6      $ & $   2.6975359552507888e-6     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to e^+ e^-                      $ & $   5.583330152639022e-6      $ & $   2.6975359552507888e-6     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-     $ & $   9.126781792989396e-6      $ & $   2.6691884927698974e-6     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to e^+ e^-         $ & $   9.126781792989396e-6      $ & $   2.6691884927698974e-6     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \pi^0 \pi^0 \Upsilon(1S) \to \tau^+ \tau^-                $ & $   5.17965538260322e-6       $ & $   2.5025041056861557e-6     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-   $ & $   8.466915469356262e-6      $ & $   2.476206164742634e-6      $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-                  $ & $   7.692188616088831e-6      $ & $   2.021665757364281e-6      $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to e^+ e^-                      $ & $   7.692188616088831e-6      $ & $   2.021665757364281e-6      $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-                $ & $   7.136043379145607e-6      $ & $   1.8754993231068418e-6     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-     $ & $   7.102966968096426e-6      $ & $   1.8654560525283148e-6     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to e^+ e^-         $ & $   7.102966968096426e-6      $ & $   1.8654560525283148e-6     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-   $ & $   6.589422456303054e-6      $ & $   1.7305835799305155e-6     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to q\bar{q}        $ & $   3.1845660870607758e-6     $ & $   1.6777525883513626e-6     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to ggg, gg\gamma   $ & $   2.3889660615087457e-6     $ & $   9.750647091115286e-7      $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to q\bar{q}                     $ & $   2.6573015219215954e-6     $ & $   8.610051379315052e-7      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-     $ & $   1.4764806403645412e-6     $ & $   8.213780008171976e-7      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to e^+ e^-         $ & $   1.4764806403645412e-6     $ & $   8.213780008171976e-7      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b1}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-   $ & $   1.369731090066185e-6      $ & $   7.619923713581144e-7      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to q\bar{q}        $ & $   2.252063039828552e-6      $ & $   7.325461271612913e-7      $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to q\bar{q}                     $ & $   1.8980725156582823e-6     $ & $   6.065574851157433e-7      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to q\bar{q}        $ & $   1.7526801609588584e-6     $ & $   5.636129412081605e-7      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-     $ & $   9.553698261182325e-7      $ & $   5.033257765054086e-7      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to e^+ e^-         $ & $   9.553698261182325e-7      $ & $   5.033257765054086e-7      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b2}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-   $ & $   8.862965876898844e-7      $ & $   4.66935322864067e-7       $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-                  $ & $   7.971904565764785e-7      $ & $   2.583015413794512e-7      $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to e^+ e^-                      $ & $   7.971904565764785e-7      $ & $   2.583015413794512e-7      $ \\ 

                    $   \Upsilon(3S) \to \pi^+ \pi^- \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-                $ & $   7.395535865659992e-7      $ & $   2.396263399377173e-7      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-     $ & $   6.756189119485657e-7      $ & $   2.1976383814838715e-7     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to e^+ e^-         $ & $   6.756189119485657e-7      $ & $   2.1976383814838715e-7     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b1}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-   $ & $   6.267716646146843e-7      $ & $   2.0387491265025874e-7     $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-                  $ & $   5.694217546974847e-7      $ & $   1.8196724553472297e-7     $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to e^+ e^-                      $ & $   5.694217546974847e-7      $ & $   1.8196724553472297e-7     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-     $ & $   5.258040482876574e-7      $ & $   1.6908388236244844e-7     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to e^+ e^-         $ & $   5.258040482876574e-7      $ & $   1.6908388236244844e-7     $ \\ 

                    $   \Upsilon(3S) \to \pi^0 \pi^0 \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-                $ & $   5.282525618328565e-7      $ & $   1.6881101368256256e-7     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b2}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-   $ & $   4.877884155964598e-7      $ & $   1.5685911766764298e-7     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to q\bar{q}        $ & $   2.3574060644475868e-7     $ & $   9.626605360989657e-8      $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \mu^+ \mu^-     $ & $   7.072218193342762e-8      $ & $   2.8879816082968994e-8     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to e^+ e^-         $ & $   7.072218193342762e-8      $ & $   2.8879816082968994e-8     $ \\ 

                    $   \Upsilon(3S) \to \gamma \chi_{b0}(2P) \to \Upsilon(2S) \to \gamma \chi_{b0}(1P) \to \Upsilon(1S) \to \tau^+ \tau^-   $ & $   6.560896817964079e-8      $ & $   2.6791805380170307e-8     $ \\ 

