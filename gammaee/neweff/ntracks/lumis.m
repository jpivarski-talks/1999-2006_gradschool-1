WeightedSum[ points:{ { ( _Integer | _Real ), ( _Integer | _Real ) } .. } ] :=
    { Plus @@ (#[[1]]& /@ points), Sqrt[ Plus @@ ((#[[2]]^2)& /@ points) ] };

DoStuff[file_] := Prepend[WeightedSum[{#[[2]], #[[3]]}& /@ ReadList[file, {Real, Real, Real, Real}]], file];
DoStuff["/home/mccann/super_hadrons/final_peakfits/y1s/apr02-02/cont.gglumi"]

DoStuff[#]& /@ {"/home/mccann/super_hadrons/final_peakfits/y1s/apr02-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/apr02-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/apr02-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/apr08-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/apr08-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/apr08-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb06-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb06-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb06-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb14-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb14-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb20-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb20-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb20-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb28-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb28-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/feb28-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan16-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan16-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan16-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan30-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan30-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/jan30-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar06-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar06-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar06-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar14-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar14-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar14-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar21-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar21-02/high.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y1s/mar21-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/aug07-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jul11-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jul11-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jul24-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jul24-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun11-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun11-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun11-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun28-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun28-02/high.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/jun28-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/may28-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/may28-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/may28-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/nov04-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/oct22-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/oct22-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y2s/sep29-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec06-01/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec06-01/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec06-01/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec13-01/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec13-01/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec13-01/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec20-01/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec20-01/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec20-01/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec25-01/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec25-01/high.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec25-01/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/dec25-01/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan03-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan03-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan03-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan10-02/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan10-02/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/jan10-02/scan.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/nov29-01/cont.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/nov29-01/peak.gglumi",
		"/home/mccann/super_hadrons/final_peakfits/y3s/nov29-01/scan.gglumi"} // TableForm

y1s/apr02-02/cont.gglumi   15398.6   94.2066
y1s/apr02-02/peak.gglumi   52089.    173.859
y1s/apr02-02/scan.gglumi   5144.8    54.6801
y1s/apr08-02/cont.gglumi   2640.1    38.9955
y1s/apr08-02/peak.gglumi   51350.7   172.561
y1s/apr08-02/scan.gglumi   17231.2   100.022
y1s/feb06-02/cont.gglumi   35982.4   144.045
y1s/feb06-02/peak.gglumi   64726.6   193.828
y1s/feb06-02/scan.gglumi   9476.     74.2016
y1s/feb14-02/cont.gglumi   19821.    106.912
y1s/feb14-02/peak.gglumi   58522.1   184.296
y1s/feb20-02/cont.gglumi   27463.1   125.897
y1s/feb20-02/peak.gglumi   53036.9   175.376
y1s/feb20-02/scan.gglumi   13681.2   89.061
y1s/feb28-02/cont.gglumi   21612.7   111.656
y1s/feb28-02/peak.gglumi   60450.    187.263
y1s/feb28-02/scan.gglumi   9966.4    76.0761
y1s/jan16-02/cont.gglumi   6861.6    62.9151
y1s/jan16-02/peak.gglumi   6351.     61.0388
y1s/jan16-02/scan.gglumi   6723.2    62.818
y1s/jan30-02/cont.gglumi   10806.5   78.9341
y1s/jan30-02/peak.gglumi   59080.8   185.171
y1s/jan30-02/scan.gglumi   12980.2   86.8358
y1s/mar06-02/cont.gglumi   16113.    96.4387
y1s/mar06-02/peak.gglumi   49396.6   169.287
y1s/mar06-02/scan.gglumi   6666.4    62.2452
y1s/mar14-02/cont.gglumi   22224.7   113.231
y1s/mar14-02/peak.gglumi   61893.7   189.543
y1s/mar14-02/scan.gglumi   8206.7    71.832
y1s/mar21-02/cont.gglumi   5812.2    57.8458
y1s/mar21-02/high.gglumi   11523.9   82.6189
y1s/mar21-02/peak.gglumi   32553.5   137.405

y2s/aug07-02/scan.gglumi   9931.1    80.3718
y2s/jul11-02/cont.gglumi   99151.2   253.488
y2s/jul11-02/scan.gglumi   18106.    108.638
y2s/jul24-02/cont.gglumi   935.5     24.601
y2s/jul24-02/scan.gglumi   7953.3    71.9948
y2s/jun11-02/cont.gglumi   26056.1   129.895
y2s/jun11-02/peak.gglumi   43638.6   168.643
y2s/jun11-02/scan.gglumi   18566.9   109.993
y2s/jun28-02/cont.gglumi   12380.9   89.5774
y2s/jun28-02/high.gglumi   4795.     56.2318
y2s/jun28-02/peak.gglumi   76651.5   223.469
y2s/may28-02/cont.gglumi   59959.2   197.149
y2s/may28-02/peak.gglumi   54099.8   187.737
y2s/may28-02/scan.gglumi   19022.8   111.347
y2s/nov04-02/cont.gglumi   27211.5   132.797
y2s/oct22-02/cont.gglumi   30476.8   140.515
y2s/oct22-02/peak.gglumi   97474.5   252.002
y2s/sep29-02/cont.gglumi   16757.2   104.266

y3s/dec06-01/cont.gglumi   7107.1    70.4552
y3s/dec06-01/peak.gglumi   58146.4   202.14
y3s/dec06-01/scan.gglumi   11040.4   88.1007
y3s/dec13-01/cont.gglumi   6645.8    68.1474
y3s/dec13-01/peak.gglumi   59548.5   204.495
y3s/dec13-01/scan.gglumi   9500.1    81.7203
y3s/dec20-01/cont.gglumi   20347.8   119.216
y3s/dec20-01/peak.gglumi   45738.2   179.288
y3s/dec20-01/scan.gglumi   9699.1    82.556
y3s/dec25-01/cont.gglumi   17107.3   109.293
y3s/dec25-01/high.gglumi   11014.6   88.2865
y3s/dec25-01/peak.gglumi   62828.6   210.149
y3s/dec25-01/scan.gglumi   23439.8   128.39
y3s/jan03-02/cont.gglumi   24698.5   131.381
y3s/jan03-02/peak.gglumi   65665.5   214.764
y3s/jan03-02/scan.gglumi   15088.6   102.946
y3s/jan10-02/cont.gglumi   6672.5    68.3104
y3s/jan10-02/peak.gglumi   66649.1   216.415
y3s/jan10-02/scan.gglumi   7995.7    74.9691
y3s/nov29-01/cont.gglumi   11320.4   88.8879
y3s/nov29-01/peak.gglumi   51611.2   190.44
y3s/nov29-01/scan.gglumi   7539.3    72.8371

(* y3s peak without failed jobs *)
WeightedSum[{{59548.5, 204.495}, {45738.2, 179.288}, {51611.2, 190.44}}]

Out[100]= {156898., 332.009}

(* y3s total peak *)
WeightedSum[{{58146.4, 202.14}, {59548.5, 204.495}, {45738.2, 179.288}, {62828.6, 210.149}, {65665.5, 214.764}, {66649.1, 216.415}, {51611.2, 190.44}}]

Out[101]= {410188., 536.854}

(* y3s cont *)
WeightedSum[{{7107.1, 70.4552}, {6645.8, 68.1474}, {20347.8, 119.216}, {17107.3, 109.293}, {24698.5, 131.381}, {6672.5, 68.3104}, {11320.4, 88.8879}}]

Out[102]= {93899.4, 256.113}

