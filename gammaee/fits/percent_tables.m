<< /home/mccann/acceptance/run5/tables5/classic_plots_and_tables.m

(* lev[none] = 2300; *)
(* lev[trigger] = 1400; *)
(* lev[d0close] = 1500; *)
(* lev[e1] = 1600; *)
(* lev[p2] = 1700; *)
(* lev[wz] = 1800; *)
(* lev[visen] = 2000; *)
(* lev[tracks] = 2100; *)
(* lev[l4dec] = 1900; *)
(* lev[ccen] = 2200; *)

isbblumi = True;
RunThrough["perl mathemetize_table.pl all1_bblumi_normcc.table", Null];
longline[2, "data part", lev[ccen], lev[wz], 1000];

data part 98.02\% & $\pm$ 0.0360723\% & 99.4925\% & $\pm$ 0.340792\% & Null & $\pm$ 0.806316\% \\ 

isbblumi = True;
RunThrough["perl mathemetize_table.pl all1_bblumi_normcc.table", Null];
longline[2, "data part", lev[ccen], lev[p2], 1000];

data part 97.45\% & $\pm$ 0.0424895\% & 98.8427\% & $\pm$ 0.335224\% & Null & $\pm$ 0.922309\% \\ 





isbblumi = True;
RunThrough["perl mathemetize_table.pl all2_bblumi_normcc.table", Null];
longline[2, "data part", lev[ccen], lev[wz], 1000];

data part 98.15\% & $\pm$ 0.033555\% & 97.9202\% & $\pm$ 0.394099\% & Null & $\pm$ 0.877904\% \\ 

isbblumi = True;
RunThrough["perl mathemetize_table.pl all3_bblumi_normcc.table", Null];
longline[2, "data part", lev[ccen], lev[wz], 1000];

data part 98.21\% & $\pm$ 0.0429199\% & 98.7423\% & $\pm$ 0.545903\% & Null & $\pm$ 1.1035\% \\ 

