<< Statistics`ContinuousDistributions`;
<< Graphics`Graphics`;

makevisen[partsize_, lossp_, res_] :=
    (particles = {};
     sumsofar = 0.;
     part = Random[ExponentialDistribution[partsize]];
     While[sumsofar + part < 10, (
	 If[Random[Real] > lossp,
	    particles = Append[particles, part + Random[NormalDistribution[0, res]]]];
	 sumsofar += part;
	 part = Random[ExponentialDistribution[partsize]]
				 )];
     If[Random[Real] > lossp,
	particles = Append[particles,
			   (10 - sumsofar + Random[NormalDistribution[0, res]])]];
     Plus @@ particles
    );

makevisen2[lossp_, res_] :=
    (firsthalf = Random[]*10;
     secondhalf = Random[]*10;
     p1 = Random[] * firsthalf;
     p2 = firsthalf - p1;
     p3 = Random[] * secondhalf;
     p4 = secondhalf - p3;
     sumsofar = 0.;
     If[Random[Real] > lossp, sumsofar += Random[NormalDistribution[p1, res]]];
     If[Random[Real] > lossp, sumsofar += Random[NormalDistribution[p2, res]]];
     If[Random[Real] > lossp, sumsofar += Random[NormalDistribution[p3, res]]];
     If[Random[Real] > lossp, sumsofar += Random[NormalDistribution[p4, res]]];
     sumsofar
    );

vhist = Table[0, {24}];
oflow = 0;
Table[Module[{v = Floor[makevisen2[0.10, 0.12]*2]},
	     If[v < 24, vhist[[v+1]]++, oflow++]], {100000}];
Print["ve/cr vp(24)"];
Table[Print["ve/inp vp(", i, ") ", vhist[[i]]], {i, 1, 24}];
Print["h/cr/1d 1000 'vp' 24 0. 1.2"];
Print["h/put_vect/contents 1000 vp"];
Print["normalize 1000 1"];











vhist = Table[0, {120}];
oflow = 0;
Table[Module[{v = Floor[makevisen[1.85, 0.20, 0.12]*10]},
	     If[v < 120, vhist[[v+1]]++, oflow++]], {1000000}];
Print["ve/cr vp(120)"];
Table[Print["ve/inp vp(", i, ") ", vhist[[i]]], {i, 1, 120}];
Print["h/cr/1d 1001 'vp' 120 0. 1.2"];
Print["h/put_vect/contents 1001 vp"];
Print["normalize 1001 1"];
(Plus @@ vhist[[Range[1,35]]]) / (Plus @@ vhist + oflow) * 100 percent // N

Out[176]= 0.2554 percent

vhist = Table[0, {120}];
oflow = 0;
Table[Module[{v = Floor[makevisen[1.55, 0.20, 0.12]*10]},
	     If[v < 120, vhist[[v+1]]++, oflow++]], {1000000}];
Print["ve/cr vp(120)"];
Table[Print["ve/inp vp(", i, ") ", vhist[[i]]], {i, 1, 120}];
Print["h/cr/1d 1002 'vp' 120 0. 1.2"];
Print["h/put_vect/contents 1002 vp"];
Print["normalize 1002 1"];
(Plus @@ vhist[[Range[1,35]]]) / (Plus @@ vhist + oflow) * 100 percent // N

Out[177]= 0.4866 percent

vhist = Table[0, {120}];
oflow = 0;
Table[Module[{v = Floor[makevisen[1.85, 0.22, 0.12]*10]},
	     If[v < 120, vhist[[v+1]]++, oflow++]], {1000000}];
Print["ve/cr vp(120)"];
Table[Print["ve/inp vp(", i, ") ", vhist[[i]]], {i, 1, 120}];
Print["h/cr/1d 1003 'vp' 120 0. 1.2"];
Print["h/put_vect/contents 1003 vp"];
Print["normalize 1003 1"];
(Plus @@ vhist[[Range[1,35]]]) / (Plus @@ vhist + oflow) * 100 percent // N

Out[178]= 0.3955 percent

vhist = Table[0, {120}];
oflow = 0;
Table[Module[{v = Floor[makevisen[1.85, 0.20, 0.2]*10]},
	     If[v < 120, vhist[[v+1]]++, oflow++]], {1000000}];
Print["ve/cr vp(120)"];
Table[Print["ve/inp vp(", i, ") ", vhist[[i]]], {i, 1, 120}];
Print["h/cr/1d 1004 'vp' 120 0. 1.2"];
Print["h/put_vect/contents 1004 vp"];
Print["normalize 1004 1"];
(Plus @@ vhist[[Range[1,35]]]) / (Plus @@ vhist + oflow) * 100 percent // N

Out[179]= 0.3931 percent
