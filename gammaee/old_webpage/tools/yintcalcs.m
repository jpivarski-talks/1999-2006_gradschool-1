<< Statistics`DescriptiveStatistics`
<< Statistics`ContinuousDistributions`
<< Graphics`Graphics`

results = {{2.60, 2.64, 0.05, 0.19},
	   {3.20, 2.21, 0.07, 0.13},
	   {3.40, 2.38, 0.07, 0.16},
	   {3.55, 2.23, 0.06, 0.16},
	   {4.60, 2.58, 0.20, 0.29},
	   {5.00, 3.47, 0.32, 0.29}};

stuff = Table[Interpolation[{#[[1]], Random[NormalDistribution[#[[2]], #[[3]]]] + #[[4]]*syst}& /@ results,
			    InterpolationOrder -> 1], {30}];
Show[
    Plot[{stuff[[1]][x], stuff[[2]][x], stuff[[3]][x], stuff[[4]][x], stuff[[5]][x],
	  stuff[[6]][x], stuff[[7]][x], stuff[[8]][x], stuff[[9]][x], stuff[[10]][x],
	  stuff[[11]][x], stuff[[12]][x], stuff[[13]][x], stuff[[14]][x], stuff[[15]][x],
	  stuff[[16]][x], stuff[[17]][x], stuff[[18]][x], stuff[[19]][x], stuff[[20]][x],
	  stuff[[21]][x], stuff[[22]][x], stuff[[23]][x], stuff[[24]][x], stuff[[25]][x],
	  stuff[[26]][x], stuff[[27]][x], stuff[[28]][x], stuff[[29]][x], stuff[[30]][x]}, {x, 2.6, 5},
	 DisplayFunction -> Identity],
    Graphics[{Line[{{3.09687, 0}, {3.09687, 5}}],
	      Line[{{3.68596, 0}, {3.68596, 5}}]}],
    Axes -> False,
    Frame -> True,
    DisplayFunction -> $DisplayFunction
    ];

trials = Table[(
    syst = Random[NormalDistribution[0,1]];
    func = Interpolation[{#[[1]], Random[NormalDistribution[#[[2]], #[[3]]]] + #[[4]]*syst}& /@ results,
			 InterpolationOrder -> 1];
    func[3.09687]
	 ), {10000}];
Histogram[trials];
{Mean[trials], StandardDeviation[trials]}

Out[80]= {2.28331, 0.150598}

trials = Table[(
    syst = Random[NormalDistribution[0,1]];
    func = Interpolation[{#[[1]], Random[NormalDistribution[#[[2]], #[[3]]]] + #[[4]]*syst}& /@ results,
			 InterpolationOrder -> 1];
    func[3.68596]
	 ), {10000}];
Histogram[trials];
{Mean[trials], StandardDeviation[trials]}

Out[81]= {2.27413, 0.18707}




Exit

[Mathematica finished.]
