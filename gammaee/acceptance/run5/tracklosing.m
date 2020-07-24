<< Statistics`ContinuousDistributions`;
<< Graphics`Graphics`;

makevisen[partsize_, lossp_] :=
    (particles = {};
     sumsofar = 0.;
     part = Random[ExponentialDistribution[partsize]];
     While[sumsofar + part < 10, (
	 If[Random[Real] > lossp,
	    particles = Append[particles, part + Random[NormalDistribution[0, 0.05]]]];
	 sumsofar += part;
	 part = Random[ExponentialDistribution[partsize]]
				 )];
     If[Random[Real] > lossp,
	particles = Append[particles,
			   (10 - sumsofar + Random[NormalDistribution[0, 0.05]])]];
     Plus @@ particles
    );
bisect[f_, {low_, high_}, {flow_, fhigh_}] :=
    Module[{mid, fmid},
	   mid = N[-flow * (high - low)/(fhigh - flow) + low];
(* 	   Print["f[", low, "] = ", flow, " f[", high, "] = ", fhigh]; *)
	   fmid = N[f[mid]];
	   If[Abs[low - high] > 0.001,
	      If[fmid > 0,
		 bisect[f, {low, mid}, {flow, fmid}],
		 bisect[f, {mid, high}, {fmid, fhigh}]],
	      mid]];
bisect[f_, {low_, high_}] := bisect[f, {low, high}, {f[low], f[high]}];
psitem[partsize_] := (
    lossrate = bisect[(Mean[visens = Table[makevisen[partsize, #], {5000}]]-7.969)&,
		      {0.1, 0.3}];
    {lossrate,
     StandardDeviation[visens],
     N[Length[Select[visens, (# > 3.5)&]]/Length[visens]]}
		     );

psitem[0.5]
Out[6]= {0.201571, 2.246, 0.9446}

psitem[0.6]
Out[8]= {0.202103, 2.11631, 0.9556}

psitem[0.7]
Out[9]= {0.20159, 1.94373, 0.9708}

psitem[0.8]
Out[10]= {0.200143, 1.84389, 0.9742}

psitem[0.9]
Out[11]= {0.200458, 1.76771, 0.9802}

psitem[1.0]
Out[4]= {0.20065, 1.68895, 0.9844}

psitem[1.1]
Out[12]= {0.201219, 1.58858, 0.9882}

psitem[1.2]
Out[13]= {0.201381, 1.53411, 0.9932}

psitem[1.3]
Out[14]= {0.201518, 1.50155, 0.994}

psitem[1.4]
Out[15]= {0.202516, 1.44024, 0.9946}

psitem[1.5]
Out[3]= {0.20339, 1.38893, 0.9954}

psitem[1.6]
Out[16]= {0.202102, 1.38338, 0.996}

psitem[1.61]
Out[25]= {0.200901, 1.35339, 0.9966}

psitem[1.62]
Out[26]= {0.201635, 1.36011, 0.997}

psitem[1.63]
Out[27]= {0.200954, 1.352, 0.9962}

psitem[1.64]
Out[28]= {0.201256, 1.35066, 0.997}

psitem[1.65]
Out[29]= {0.202376, 1.34307, 0.9978}

psitem[1.66]
Out[30]= {0.201578, 1.35716, 0.9948}

psitem[1.67]
Out[31]= {0.202787, 1.33303, 0.9974}

psitem[1.68]
Out[32]= {0.201039, 1.33574, 0.9974}

psitem[1.69]
Out[33]= {0.20197, 1.34908, 0.9958}

psitem[1.7]
Out[17]= {0.201042, 1.33085, 0.998}

psitem[1.8]
Out[18]= {0.201298, 1.31477, 0.998}

psitem[1.9]
Out[19]= {0.201508, 1.25509, 0.9986}

psitem[2.0]
Out[5]= {0.200948, 1.21418, 0.9998}

psitem[2.1]
Out[20]= {0.199719, 1.22141, 0.9984}

psitem[2.2]
Out[21]= {0.20008, 1.18571, 0.9994}

psitem[2.3]
Out[22]= {0.203795, 1.16789, 0.9986}

psitem[2.4]
Out[23]= {0.201179, 1.1476, 1.}

psitem[2.5]
Out[24]= {0.2016, 1.11577, 0.9992}

{0.201571, 0.202103, 0.20159, 0.200143, 0.200458, 0.20065, 0.201219,
0.201381, 0.201518, 0.202516, 0.20339, 0.202102, 0.200901, 0.201635,
0.200954, 0.201256, 0.202376, 0.201578, 0.202787, 0.201039, 0.20197,
0.201042, 0.201298, 0.201508, 0.200948, 0.199719, 0.20008, 0.203795,
0.201179, 0.2016} // StandardDeviation

Out[35]= 0.000905773

Out[34]= 0.201477

ps2item[partsize_] := (
    visens = Table[makevisen[partsize, 0.201], {50000}];
    {partsize,
     0.201,
     StandardDeviation[visens],
     N[Length[Select[visens, (# > 3.5)&]]/Length[visens]]});
ps2item /@ Range[1.60, 1.70, 0.01] // TableForm

Out[41]//TableForm= 1.6    0.201   1.3665    0.99604

                    1.61   0.201   1.36407   0.99604

                    1.62   0.201   1.35675   0.99654

                    1.63   0.201   1.35729   0.99638

                    1.64   0.201   1.34372   0.99696

                    1.65   0.201   1.34429   0.99648

                    1.66   0.201   1.34677   0.99612

                    1.67   0.201   1.34268   0.99658

                    1.68   0.201   1.33427   0.99708

                    1.69   0.201   1.33737   0.99664

                    1.7    0.201   1.32684   0.9966

ps2item[partsize_] := (
    visens = Table[makevisen[partsize, 0.201], {500000}];
    {partsize,
     0.201,
     StandardDeviation[visens],
     N[Length[Select[visens, (# > 3.5)&]]/Length[visens]]});
ps2item /@ Range[1.60, 1.70, 0.01] // TableForm

Out[42]//TableForm= 1.6    0.201   1.36419   0.996082

                    1.61   0.201   1.3607    0.996176

                    1.62   0.201   1.3594    0.996138

                    1.63   0.201   1.35424   0.996288

                    1.64   0.201   1.35001   0.99653

                    1.65   0.201   1.3458    0.996526

                    1.66   0.201   1.34438   0.996544

                    1.67   0.201   1.3383    0.996642

                    1.68   0.201   1.33592   0.99674

                    1.69   0.201   1.33244   0.996842

                    1.7    0.201   1.328     0.99687

ps3item[lossp_] := (
    visens = Table[makevisen[1.65, lossp], {500000}];
    {1.65,
     lossp,
     Mean[visens],
     N[Length[Select[visens, (# > 3.5)&]]/Length[visens]]});
ps3item /@ Range[0.19, 0.21, 0.005] // TableForm

Out[46]= $Aborted




