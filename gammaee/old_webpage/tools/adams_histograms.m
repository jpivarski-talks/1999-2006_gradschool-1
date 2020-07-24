<< Statistics`DescriptiveStatistics`;

HistogramBins[ frequencyData_?VectorQ,
	       { low_?NumericQ, high_?NumericQ },
	       opts___?OptionQ ] :=
    Histogram[ frequencyData,
	       FrequencyData -> True,
	       HistogramRange -> {low, high},
	       FilterOptions[ Histogram, opts ],
	       BarEdges -> False
	     ];

Histogram1D[ data_?VectorQ,
	     { nBins_:Automatic, low_?NumericQ, high_?NumericQ },
	     opts___?OptionQ ] :=
    Module[ {binCounts, dx, numberOfBins = nBins},
	    dx = (high - low) / numberOfBins;
	    binCounts = BinCounts[ data, {low, high, dx} ];
	    {
		Entries -> Plus @@ binCounts,
		UnderFlows -> Length[ Select[ data, (# < low)& ] ],
		OverFlows -> Length[ Select[ data, (# > high)& ] ],
		HistogramMean -> ( mean = N[ Mean[
		    Select[ data, (low <= # <= high)& ]
						 ] ] ),
		HistogramRMS -> N[ StandardDeviation[
		    Select[ data, (low <= # <= high)& ]
						    ] ],
		Histogram -> HistogramBins[ binCounts, {low, high}, opts ]
	    }
	  ] /; ( NumericQ[ nBins ]  ||  nBins === Automatic );

Histogram1D[ data_?VectorQ, opts___?OptionQ ] :=
    Module[ {max,min,mean,rms,low,high,showAll},
	    showAll = ( ShowAll /. {opts} ) /. Options[ Histogram1D ];
	    (* Find the mean, max, min, and rms of the distribution *)
	    max = Max[ data ];
	    min = Min[ data ];
	    mean = Mean[ data ];
	    rms = StandardDeviation[ data ];
	    If[ showAll === True,
		( low = min;  high = max; ),
		( low = Max[ min, mean - 5 * rms ];
		  high = Min[ max, mean + 5 * rms ]; )
	      ];
	    Histogram1D[ data, {low, high}, opts ]
	  ];

Options[ Histogram1D ] = { ShowAll -> False };

Histogram1D::usage =
    "Histogram1D[data, {nBins, low, high}] and Histogram1D[ data ] display
a histogram of the specified data. In its first form, you specify the
number of bins, low and high edges (if you do not specify the number
of bins, a resonable value is used as a default). In the second form,
you give the data list and resonable ranges will be calculated (5
sigma about the mean). The second form has an option, ShowAll, which
if true, will show the entire data range (default is false).";

ShowAll::usage =
    "ShowAll specifies whether or not to show the entire data range when
Histogram1D[data] is given. The default is false.";

(* here I'm just testing his ntuple stuff, to see how it works *)

(*
   << HbookLink`

   HbookDirectories[ "/home/mccann/diagnostics/dafedir/standalone_123592.rzn" ]

   Out[18]= {{SEEDDIAGPROC}, {FITDIAGPROC}}

   LoadNtuple[ "/home/mccann/diagnostics/dafedir/standalone_123592.rzn", "SEEDDIAGPROC", 1 ]
   [Mathematica exited abnormally with code 1.]
*)
