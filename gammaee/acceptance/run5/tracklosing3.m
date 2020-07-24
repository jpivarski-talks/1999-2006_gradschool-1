<< Graphics`Graphics`;
<< Statistics`ContinuousDistributions`;

(* no strange, no baryons *)
plain = { {-0.02,0}, {0.02, 0}, {0.06, 0}, {0.1, 0}, {0.14, 0}, {0.18,
0}, {0.22, 0}, {0.26, 0}, {0.3, 2}, {0.34, 1}, {0.38, 6}, {0.42, 4},
{0.46, 7}, {0.5, 5}, {0.54, 16}, {0.58, 37}, {0.62, 48}, {0.66, 89},
{0.7, 164}, {0.74, 208}, {0.78, 363}, {0.82, 515}, {0.86, 653}, {0.9,
934}, {0.94, 1052}, {0.98, 994}, {1.02, 536}, {1.06, 143}, {1.1, 51},
{1.14, 19}, {1.18, 4}, {1.22, 5}, {1.26, 2}, {1.3, 1}, {1.34, 1},
{1.38, 0}, {1.42, 1}, {1.46, 0}, {1.5, 0}, {1.54, 0}, {1.58, 0},
{1.62, 0}, {1.66, 0}, {1.7, 0}, {1.74, 0}, {1.78, 0}, {1.82, 0},
{1.86, 0}, {1.9, 0}, {1.94, 0}, {1.98, 0}};
plain = Interpolation[{#[[1]], (#[[2]]/(Plus @@ (#[[2]]& /@ plain))+0.00001)}& /@ plain, InterpolationOrder -> 1];
(* with strange, but without baryons *)
strange = { {-0.02,0}, {0.02, 0}, {0.06, 0}, {0.1, 0}, {0.14, 0},
{0.18, 1}, {0.22, 2}, {0.26, 1}, {0.3, 5}, {0.34, 12}, {0.38, 30},
{0.42, 41}, {0.46, 73}, {0.5, 126}, {0.54, 227}, {0.58, 363}, {0.62,
637}, {0.66, 916}, {0.7, 1349}, {0.74, 1827}, {0.78, 2335}, {0.82,
2751}, {0.86, 2937}, {0.9, 2862}, {0.94, 2309}, {0.98, 1477}, {1.02,
573}, {1.06, 198}, {1.1, 55}, {1.14, 17}, {1.18, 12}, {1.22, 5},
{1.26, 9}, {1.3, 3}, {1.34, 4}, {1.38, 2}, {1.42, 1}, {1.46, 1}, {1.5,
0}, {1.54, 0}, {1.58, 0}, {1.62, 1}, {1.66, 0}, {1.7, 0}, {1.74, 1},
{1.78, 0}, {1.82, 1}, {1.86, 0}, {1.9, 0}, {1.94, 1}, {1.98, 0}};
strange = Interpolation[{#[[1]], (#[[2]]/(Plus @@ (#[[2]]& /@ strange))+0.00001)}& /@ strange, InterpolationOrder -> 1];
(* without strange, but with baryons *)
baryons = { {-0.02,0}, {0.02, 0}, {0.06, 1}, {0.1, 0}, {0.14, 0},
{0.18, 0}, {0.22, 1}, {0.26, 5}, {0.3, 3}, {0.34, 13}, {0.38, 31},
{0.42, 45}, {0.46, 78}, {0.5, 130}, {0.54, 203}, {0.58, 303}, {0.62,
417}, {0.66, 629}, {0.7, 802}, {0.74, 954}, {0.78, 1077}, {0.82,
1127}, {0.86, 1078}, {0.9, 907}, {0.94, 610}, {0.98, 311}, {1.02,
144}, {1.06, 60}, {1.1, 21}, {1.14, 9}, {1.18, 8}, {1.22, 3}, {1.26,
1}, {1.3, 1}, {1.34, 1}, {1.38, 2}, {1.42, 0}, {1.46, 1}, {1.5, 1},
{1.54, 1}, {1.58, 0}, {1.62, 0}, {1.66, 0}, {1.7, 0}, {1.74, 0},
{1.78, 0}, {1.82, 0}, {1.86, 0}, {1.9, 0}, {1.94, 0}, {1.98, 0}};
baryons = Interpolation[{#[[1]], (#[[2]]/(Plus @@ (#[[2]]& /@ baryons))+0.00001)}& /@ baryons, InterpolationOrder -> 1];
(* with strange and with baryons *)
stangyons = { {-0.02,0}, {0.02, 0}, {0.06, 0}, {0.1, 0}, {0.14, 2},
{0.18, 4}, {0.22, 7}, {0.26, 12}, {0.3, 33}, {0.34, 58}, {0.38, 104},
{0.42, 184}, {0.46, 309}, {0.5, 516}, {0.54, 774}, {0.58, 1161},
{0.62, 1543}, {0.66, 2041}, {0.7, 2307}, {0.74, 2468}, {0.78, 2524},
{0.82, 2284}, {0.86, 1797}, {0.9, 1292}, {0.94, 757}, {0.98, 378},
{1.02, 154}, {1.06, 71}, {1.1, 24}, {1.14, 16}, {1.18, 5}, {1.22, 4},
{1.26, 3}, {1.3, 2}, {1.34, 2}, {1.38, 1}, {1.42, 2}, {1.46, 0}, {1.5,
1}, {1.54, 0}, {1.58, 0}, {1.62, 0}, {1.66, 0}, {1.7, 0}, {1.74, 0},
{1.78, 0}, {1.82, 0}, {1.86, 0}, {1.9, 0}, {1.94, 0}, {1.98, 0}};
stangyons = Interpolation[{#[[1]], (#[[2]]/(Plus @@ (#[[2]]& /@ stangyons))+0.00001)}& /@ stangyons, InterpolationOrder -> 1];
(* absolutely everything *)
everything = { {-0.02,0}, {0.02, 0}, {0.06, 1}, {0.1, 0}, {0.14, 2},
{0.18, 5}, {0.22, 10}, {0.26, 18}, {0.3, 43}, {0.34, 84}, {0.38, 171},
{0.42, 274}, {0.46, 467}, {0.5, 777}, {0.54, 1220}, {0.58, 1864},
{0.62, 2645}, {0.66, 3675}, {0.7, 4622}, {0.74, 5457}, {0.78, 6299},
{0.82, 6677}, {0.86, 6465}, {0.9, 5995}, {0.94, 4728}, {0.98, 3160},
{1.02, 1407}, {1.06, 472}, {1.1, 151}, {1.14, 61}, {1.18, 29}, {1.22,
17}, {1.26, 15}, {1.3, 7}, {1.34, 8}, {1.38, 5}, {1.42, 4}, {1.46, 2},
{1.5, 2}, {1.54, 1}, {1.58, 0}, {1.62, 1}, {1.66, 0}, {1.7, 0}, {1.74,
1}, {1.78, 0}, {1.82, 1}, {1.86, 0}, {1.9, 0}, {1.94, 1}, {1.98, 0}};
everything = Interpolation[{#[[1]], (#[[2]]/(Plus @@ (#[[2]]& /@ everything))+0.00001)}& /@ everything, InterpolationOrder -> 1];
expo[] := Random[ExponentialDistribution[partsize]];
norm[] := Random[NormalDistribution[0, res]];
makevisen =
    Compile[{},
	    (particles = {};
	     sumsofar = 0.;
	     part = expo[];
	     While[sumsofar + part < 10, (
		 If[Random[Real] > lossp,
		    particles = Append[particles, part + norm[]]];
		 sumsofar += part;
		 part = expo[]
					 )];
	     If[Random[Real] > lossp,
		particles = Append[particles,
				   (10 - sumsofar + norm[])]];
	     Plus @@ particles
	    )/10, {{particles, _Real, 1}}];

partsize = 1.85;
lossp = 0.21;
res = 0.120;

bowl = Flatten[Table[{partsize = p, lossp = l, res = r, Sum[Log[everything[makevisen[]]], {1000}]},
		     {p, 1, 3, 1/2},
		     {l, 0.1, 0.3, 0.1/2},
		     {r, 0.050, 0.200, 0.075/2}], 2];


Plot3D[Interpolation[bowl, InterpolationOrder -> 2][p, l, 0.120], {p, 1, 3}, {l, 0.1, 0.3}];

NMaximize[Interpolation[bowl, InterpolationOrder -> 2][p, l, r], {p, l, r}]








NMinimize[Sum[makevisen[partsize, lossp, res], {1000}], {partsize, lossp, res}, Compiled -> False, EvaluationMonitor -> Print[partsize, " ", lossp, " ", res]]




{partsize, 1.85}, {lossp, 0.21}, {res, 0.120}

FindMinimum[minimePlain[partsize, lossp, res], {{partsize, 1.85}, {lossp, 0.10}, {res, 0.110}}]

FindMinimum[minimeStrange[partsize, lossp, res], {{partsize, 1.85}, {lossp, 0.18}, {res, 0.080}}]

FindMinimum[minimeBaryons[partsize, lossp, res], {{partsize, 2.8}, {lossp, 0.21}, {res, 0.150}}]
















Show[
    Histogram[Table[makevisen[1.85, 0.21, 0.120], {20000}], HistogramCategories -> 24, HistogramRange -> {0., 1.2}, DisplayFunction -> Identity],
    Plot[25000*everything[x], {x, 0, 1.2}, DisplayFunction -> Identity],
    DisplayFunction -> $DisplayFunction
    ];
Show[
    Histogram[Table[makevisen[1.85, 0.10, 0.110], {20000}], HistogramCategories -> 24, HistogramRange -> {0., 1.2}, DisplayFunction -> Identity],
    Plot[25000*plain[x], {x, 0, 1.2}, DisplayFunction -> Identity],
    DisplayFunction -> $DisplayFunction
    ];
Show[
    Histogram[Table[makevisen[1.85, 0.18, 0.080], {20000}], HistogramCategories -> 24, HistogramRange -> {0., 1.2}, DisplayFunction -> Identity],
    Plot[25000*strange[x], {x, 0, 1.2}, DisplayFunction -> Identity],
    DisplayFunction -> $DisplayFunction
    ];
Show[
    Histogram[Table[makevisen[2.8, 0.21, 0.150], {20000}], HistogramCategories -> 24, HistogramRange -> {0., 1.2}, DisplayFunction -> Identity],
    Plot[25000*baryons[x], {x, 0, 1.2}, DisplayFunction -> Identity],
    DisplayFunction -> $DisplayFunction
    ];

