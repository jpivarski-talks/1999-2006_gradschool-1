WeightedSum[ points:{ { ( _Integer | _Real ), ( _Integer | _Real ) } .. } ] :=
    { Plus @@ (#[[1]]& /@ points), Sqrt[ Plus @@ ((#[[2]]^2)& /@ points) ] };

DoStuff[file_] := Prepend[WeightedSum[{#[[2]] + #[[4]], Sqrt[#[[3]]^2 + #[[5]]^2]}& /@ ReadList[file, {Real, Real, Real, Real, Real}]], file];

DoStuff[#]& /@ {"/home/mccann/super_hadrons/final_peakfits/y1s/apr02-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/apr02-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/apr02-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/apr08-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/apr08-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/apr08-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb06-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb06-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb06-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb14-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb14-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb20-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb20-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb20-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb28-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb28-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb28-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan16-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan16-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan16-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan30-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan30-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan30-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar06-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar06-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar06-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar14-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar14-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar14-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar21-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar21-02/high.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar21-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/aug07-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jul11-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jul11-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jul24-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jul24-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun11-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun11-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun11-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun28-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun28-02/high.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun28-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/may28-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/may28-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/may28-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/nov04-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/oct22-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/oct22-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y2s/sep29-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec06-01/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec06-01/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec06-01/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec13-01/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec13-01/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec13-01/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec20-01/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec20-01/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec20-01/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec25-01/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec25-01/high.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec25-01/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec25-01/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan03-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan03-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan03-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan10-02/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan10-02/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan10-02/scan.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/nov29-01/cont.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/nov29-01/peak.beamgas",
		"/home/mccann/super_hadrons/final_peakfits/y3s/nov29-01/scan.beamgas"} // TableForm

y1s/apr02-02/cont.beamgas   4838.6    68.437
y1s/apr02-02/peak.beamgas   21524.3   144.135
y1s/apr02-02/scan.beamgas   1941.4    43.2629
y1s/apr08-02/cont.beamgas   840.3     28.5168
y1s/apr08-02/peak.beamgas   21262.6   143.335
y1s/apr08-02/scan.beamgas   6464.5    79.0123
y1s/feb06-02/cont.beamgas   11748.5   106.706
y1s/feb06-02/peak.beamgas   26360.8   159.934
y1s/feb06-02/scan.beamgas   3782.     60.4649
y1s/feb14-02/cont.beamgas   7112.5    82.9991
y1s/feb14-02/peak.beamgas   25445.5   156.892
y1s/feb20-02/cont.beamgas   9179.     94.4161
y1s/feb20-02/peak.beamgas   22593.4   148.057
y1s/feb20-02/scan.beamgas   5607.1    73.5892
y1s/feb28-02/cont.beamgas   7383.5    84.6035
y1s/feb28-02/peak.beamgas   25016.6   155.813
y1s/feb28-02/scan.beamgas   3753.9    60.307
y1s/jan16-02/cont.beamgas   2274.     46.9319
y1s/jan16-02/peak.beamgas   2951.1    53.4216
y1s/jan16-02/scan.beamgas   2834.7    52.2244
y1s/jan30-02/cont.beamgas   3501.8    58.1847
y1s/jan30-02/peak.beamgas   24788.3   154.97
y1s/jan30-02/scan.beamgas   5004.1    69.4922
y1s/mar06-02/cont.beamgas   6132.5    76.9919
y1s/mar06-02/peak.beamgas   21082.9   143.082
y1s/mar06-02/scan.beamgas   2543.3    49.5934
y1s/mar14-02/cont.beamgas   7470.1    85.0792
y1s/mar14-02/peak.beamgas   25606.2   157.402
y1s/mar14-02/scan.beamgas   3103.5    54.7681
y1s/mar21-02/cont.beamgas   1878.3    42.6581
y1s/mar21-02/high.beamgas   3638.8    59.2263
y1s/mar21-02/peak.beamgas   13556.7   114.495

y2s/aug07-02/scan.beamgas   3034.9    54.2893
y2s/jul11-02/cont.beamgas   26985.7   161.994
y2s/jul11-02/scan.beamgas   5550.9    73.4584
y2s/jul24-02/cont.beamgas   333.4     17.8992
y2s/jul24-02/scan.beamgas   2596.5    50.1772
y2s/jun11-02/cont.beamgas   7787.2    87.0278
y2s/jun11-02/peak.beamgas   15015.1   120.695
y2s/jun11-02/scan.beamgas   5654.     74.0959
y2s/jun28-02/cont.beamgas   3442.7    57.8618
y2s/jun28-02/high.beamgas   1284.3    35.3088
y2s/jun28-02/peak.beamgas   23800.3   152.053
y2s/may28-02/cont.beamgas   18852.4   135.416
y2s/may28-02/peak.beamgas   18882.1   135.486
y2s/may28-02/scan.beamgas   6083.8    76.8268
y2s/nov04-02/cont.beamgas   7576.4    85.9231
y2s/oct22-02/cont.beamgas   9124.8    94.2357
y2s/oct22-02/peak.beamgas   30569.9   172.383
y2s/sep29-02/cont.beamgas   5119.5    70.687

y3s/dec06-01/cont.beamgas   3300.4    56.1701
y3s/dec06-01/peak.beamgas   28490.    165.352
y3s/dec06-01/scan.beamgas   4906.8    68.6036
y3s/dec13-01/cont.beamgas   2668.6    50.5739
y3s/dec13-01/peak.beamgas   24161.9   152.214
y3s/dec13-01/scan.beamgas   3648.6    59.1956
y3s/dec20-01/cont.beamgas   6771.7    80.5611
y3s/dec20-01/peak.beamgas   15175.7   120.64
y3s/dec20-01/scan.beamgas   3078.1    54.3274
y3s/dec25-01/cont.beamgas   5526.2    72.6295
y3s/dec25-01/high.beamgas   3679.9    59.2489
y3s/dec25-01/peak.beamgas   20679.7   140.979
y3s/dec25-01/scan.beamgas   7471.     84.5559
y3s/jan03-02/cont.beamgas   7775.1    86.429
y3s/jan03-02/peak.beamgas   21322.7   143.322
y3s/jan03-02/scan.beamgas   4880.     68.4449
y3s/jan10-02/cont.beamgas   2361.2    47.6187
y3s/jan10-02/peak.beamgas   21602.5   144.365
y3s/jan10-02/scan.beamgas   2786.5    51.7528
y3s/nov29-01/cont.beamgas   4989.7    68.9818
y3s/nov29-01/peak.beamgas   24711.2   153.763
y3s/nov29-01/scan.beamgas   3277.6    55.8992



(* y3s peak without failed jobs *)
WeightedSum[{{24161.9, 152.214}, {15175.7, 120.64}, {24711.2, 153.763}}]

Out[7]= {64048.8, 247.722}


(* y3s cont *)
WeightedSum[{{3300.4, 56.1701}, {2668.6, 50.5739}, {6771.7, 80.5611}, {5526.2, 72.6295}, {7775.1, 86.429}, {2361.2, 47.6187}, {4989.7, 68.9818}}]

Out[8]= {33392.9, 178.813}


