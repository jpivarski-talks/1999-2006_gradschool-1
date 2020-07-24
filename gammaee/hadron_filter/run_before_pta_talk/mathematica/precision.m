For all three peaks, number of events is 20053834, so goodevents is 13159392.
(* N[ 20053834 * 7024/10704, 20 ] == 13159392 *)

For U(1S), number of events is 13800053, so goodevents is 9055640
(* Round[ 13800053 * 7024/10704 ] == 9055640 *)

For U(2S), number of events is 2651578, so goodevents is 1739974
(* Round[ 2651578 * 7024/10704 ] == 1739974 *)

For U(3S), number of events is 3602203, so goodevents is 2363777
(* Round[ 3602203 * 7024/10704 ] == 2363777 *)

prec[ bdata_ ] := Module[ { goodevents = 9055640,
			    badevents,
			    goodsb = 142.7 * bdata,
			    badsb = 469.2 * bdata,
			    sbratio, sbratioerr,
			    bkindata, bkindataerr,
			    truedata, truedataerr
			  },
			  badevents = goodevents * 181729/13159392;
			  sbratio = goodsb / badsb;
			  sbratioerr = sbratio * Sqrt[ 1/goodsb + 1/badsb ];
			  Print[ "Single-beam ratio is ", sbratio, " +/- ", sbratioerr ];
			  bkindata = badevents * sbratio;
			  bkindataerr = bkindata * Sqrt[ 1/badevents + (sbratioerr/sbratio)^2 ];
			  Print[ "Background events in data is ", bkindata, " +/- ", bkindataerr ];
			  truedata = goodevents - bkindata;
			  truedataerr = Sqrt[ goodevents + bkindataerr^2 ];
			  Print[ "Yield is ", truedata, " +/- ", truedataerr ];
			  N[ truedataerr / truedata ]
			];

prec[1.]

Out[57]= 0.000523529

Single-beam ratio is 0.304135 +/- 0.0290747
Background events in data is 55270.1 +/- 5285.31
                   7
Yield is 1.31041 10  +/- 6410.45

Out[5]= 0.000489193


<< Graphics`Graphics`

Show[
    LogLinearPlot[ prec[x], {x,0.1,100.}
		   , PlotRange -> {{0.1,100.},{0,0.001}}
		   , PlotPoints -> 1000
		   , DisplayFunction -> Identity
		 ]
    , Graphics[{ Dashing[{0.02,0.02}]
		 , Line[{{0,0},{0,0.001}}]
		 , Line[{{-1,prec[1.]},{2,prec[1.]}}]
	       }]
    , ImageSize -> 6*72
    , AspectRatio -> 1
    , Axes -> False
    , Frame -> True
    , FrameLabel -> {"Quantity of Single-Beam Data (1 = present amount, note log scale)",
		     "Fractional Uncertainty in U(1S) yield (after background subtraction)",
		     "Single-Beam Data needed to Improve Yield Measurement",
		     None}
    , DisplayFunction -> $DisplayFunction
(*    , DisplayFunction -> (Display["precision.eps",#,"EPS"]&) *)
    ];




Expand[ (pp1mu*p1nu + pp1nv*p1mu - gmunu*(p1.pp1)) *
	(p2mu*pp2nu + p2nu*pp2mu - gmunu*(pp2.p2)) *
	(kkMu*kNu + kkNu*kMu - gMuNu*(k.kk + m2))    ]
    /. { pp1mu -> {pp1,mu}, p1nu -> {p1,nu}, pp1nu -> {pp1,nu}, p1mu -> {p1,mu},
	 pp2mu -> {pp2,mu}, p2nu -> {p2,nu}, pp2nu -> {pp2,nu}, p2mu -> {p2,mu}, 
	 
