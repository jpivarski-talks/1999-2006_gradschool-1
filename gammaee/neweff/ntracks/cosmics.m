WeightedSum[ points:{ { ( _Integer | _Real ), ( _Integer | _Real ) } .. } ] :=
    { Plus @@ (#[[1]]& /@ points), Sqrt[ Plus @@ ((#[[2]]^2)& /@ points) ] };

DoStuff[file_] := Prepend[WeightedSum[{#[[2]], #[[3]]}& /@ ReadList[file, {Real, Real, Real}]], file];

DoStuff[#]& /@ {"/home/mccann/super_hadrons/final_peakfits/y1s/apr02-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/apr02-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/apr02-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/apr08-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/apr08-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/apr08-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb06-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb06-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb06-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb14-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb14-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb20-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb20-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb20-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb28-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb28-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb28-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan16-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan16-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan16-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan30-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan30-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan30-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar06-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar06-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar06-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar14-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar14-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar14-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar21-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar21-02/high.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar21-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/aug07-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jul11-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jul11-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jul24-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jul24-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun11-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun11-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun11-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun28-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun28-02/high.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun28-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/may28-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/may28-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/may28-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/nov04-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/oct22-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/oct22-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y2s/sep29-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec06-01/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec06-01/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec06-01/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec13-01/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec13-01/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec13-01/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec20-01/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec20-01/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec20-01/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec25-01/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec25-01/high.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec25-01/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec25-01/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan03-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan03-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan03-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan10-02/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan10-02/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan10-02/scan.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/nov29-01/cont.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/nov29-01/peak.cosmics",
		"/home/mccann/super_hadrons/final_peakfits/y3s/nov29-01/scan.cosmics"} // TableForm

y1s/apr02-02/cont.cosmics   0.0089   0.0089
y1s/apr02-02/peak.cosmics   0.1958   0.0417447
y1s/apr02-02/scan.cosmics   0.0178   0.0125865
y1s/apr08-02/cont.cosmics   0.       0.
y1s/apr08-02/peak.cosmics   0.2225   0.0445
y1s/apr08-02/scan.cosmics   0.0801   0.0267
y1s/feb06-02/cont.cosmics   0.089    0.0281443
y1s/feb06-02/peak.cosmics   0.178    0.039802
y1s/feb06-02/scan.cosmics   0.0178   0.0125865
y1s/feb14-02/cont.cosmics   0.0356   0.0178
y1s/feb14-02/peak.cosmics   0.1958   0.0417447
y1s/feb20-02/cont.cosmics   0.0356   0.0178
y1s/feb20-02/peak.cosmics   0.1513   0.0366957
y1s/feb20-02/scan.cosmics   0.0267   0.0154153
y1s/feb28-02/cont.cosmics   0.0623   0.0235472
y1s/feb28-02/peak.cosmics   0.2492   0.0470944
y1s/feb28-02/scan.cosmics   0.0356   0.0178
y1s/jan16-02/cont.cosmics   0.0178   0.0125865
y1s/jan16-02/peak.cosmics   0.0534   0.0218005
y1s/jan16-02/scan.cosmics   0.0356   0.0178
y1s/jan30-02/cont.cosmics   0.0445   0.019901
y1s/jan30-02/peak.cosmics   0.2047   0.0426829
y1s/jan30-02/scan.cosmics   0.0178   0.0125865
y1s/mar06-02/cont.cosmics   0.0534   0.0218005
y1s/mar06-02/peak.cosmics   0.1869   0.0407849
y1s/mar06-02/scan.cosmics   0.0356   0.0178
y1s/mar14-02/cont.cosmics   0.0356   0.0178
y1s/mar14-02/peak.cosmics   0.1691   0.0387942
y1s/mar14-02/scan.cosmics   0.0178   0.0125865
y1s/mar21-02/cont.cosmics   0.0089   0.0089
y1s/mar21-02/high.cosmics   0.0267   0.0154153
y1s/mar21-02/peak.cosmics   0.1424   0.0356

y2s/aug07-02/scan.cosmics   0.0089   0.0089
y2s/jul11-02/cont.cosmics   0.178    0.039802
y2s/jul11-02/scan.cosmics   0.0178   0.0125865
y2s/jul24-02/cont.cosmics   0.       0.
y2s/jul24-02/scan.cosmics   0.0089   0.0089
y2s/jun11-02/cont.cosmics   0.0178   0.0125865
y2s/jun11-02/peak.cosmics   0.0712   0.025173
y2s/jun11-02/scan.cosmics   0.0267   0.0154153
y2s/jun28-02/cont.cosmics   0.0267   0.0154153
y2s/jun28-02/high.cosmics   0.0089   0.0089
y2s/jun28-02/peak.cosmics   0.1602   0.0377595
y2s/may28-02/cont.cosmics   0.1602   0.0377595
y2s/may28-02/peak.cosmics   0.1335   0.0344696
y2s/may28-02/scan.cosmics   0.0534   0.0218005
y2s/nov04-02/cont.cosmics   0.0356   0.0178
y2s/oct22-02/cont.cosmics   0.0089   0.0089
y2s/oct22-02/peak.cosmics   0.2225   0.0445
y2s/sep29-02/cont.cosmics   0.0267   0.0154153

y3s/dec06-01/cont.cosmics   0.0089   0.0089
y3s/dec06-01/peak.cosmics   0.2047   0.0426829
y3s/dec06-01/scan.cosmics   0.0178   0.0125865
y3s/dec13-01/cont.cosmics   0.       0.
y3s/dec13-01/peak.cosmics   0.1157   0.0320894
y3s/dec13-01/scan.cosmics   0.0356   0.0178
y3s/dec20-01/cont.cosmics   0.0267   0.0154153
y3s/dec20-01/peak.cosmics   0.0267   0.0154153
y3s/dec20-01/scan.cosmics   0.0178   0.0125865
y3s/dec25-01/cont.cosmics   0.0445   0.019901
y3s/dec25-01/high.cosmics   0.       0.
y3s/dec25-01/peak.cosmics   0.1513   0.0366957
y3s/dec25-01/scan.cosmics   0.0267   0.0154153
y3s/jan03-02/cont.cosmics   0.0712   0.025173
y3s/jan03-02/peak.cosmics   0.1424   0.0356
y3s/jan03-02/scan.cosmics   0.0356   0.0178
y3s/jan10-02/cont.cosmics   0.0267   0.0154153
y3s/jan10-02/peak.cosmics   0.1869   0.0407849
y3s/jan10-02/scan.cosmics   0.       0.
y3s/nov29-01/cont.cosmics   0.0267   0.0154153
y3s/nov29-01/peak.cosmics   0.2047   0.0426829
y3s/nov29-01/scan.cosmics   0.0178   0.0125865



(* y3s peak without failed jobs *)
WeightedSum[{{0.1157, 0.0320894}, {0.0267, 0.0154153}, {0.2047, 0.0426829}}]

Out[11]= {0.3471, 0.0555805}



(* y3s cont *)
WeightedSum[{{0.0089, 0.0089}, {0., 0.}, {0.0267, 0.0154153}, {0.0445, 0.019901}, {0.0712, 0.025173}, {0.0267, 0.0154153}, {0.0267, 0.0154153}}]

Out[12]= {0.2047, 0.0426829}

