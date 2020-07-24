<< Statistics`ContinuousDistributions`;
<< Statistics`DiscreteDistributions`;
<< Graphics`Graphics`;

itsgglumi = False;
Rand[numer_, denom_] := If[numer == denom, numer,			
			   If[CDF[NormalDistribution[numer, Sqrt[numer*(1-numer/denom)]], denom] < 0.9999,
			      Random[BinomialDistribution[denom, numer/denom]],
			      Module[{trial = denom},
				     While[trial >= denom,
					   trial = Random[NormalDistribution[numer, Sqrt[numer*(1-numer/denom)]]]];
				     trial]]];
unjiggle[] := (
    nptoc = hptoc;
    nptocerr = hptocerr;
    Clear[n];
    n[110] = h[110];
    n[111] = h[111];
    n[120] = h[120];
    n[122] = h[122];
    n[210] = h[210];
    n[211] = h[211];
    n[220] = h[220];
    n[222] = h[222];
    n[300] = h[300];
    n[301] = h[301];
    n[302] = h[302];
    n[350] = h[350];
    n[351] = h[351];
    n[352] = h[352];
    n[400] = h[400];
    n[401] = h[401];
    n[402] = h[402];
    n[403] = h[403];
    n[404] = h[404];
    n[1401] = h[1401];
    n[1402] = h[1402];
    n[1403] = h[1403];
    n[1404] = h[1404];
    n[1405] = h[1405];
    n[1406] = h[1406];
    n[1407] = h[1407];
    n[1501] = h[1501];
    n[1502] = h[1502];
    n[1503] = h[1503];
    n[1504] = h[1504];
    n[1505] = h[1505];
    n[1506] = h[1506];
    n[1507] = h[1507];
    n[1601] = h[1601];
    n[1602] = h[1602];
    n[1603] = h[1603];
    n[1604] = h[1604];
    n[1605] = h[1605];
    n[1606] = h[1606];
    n[1607] = h[1607];
    n[1701] = h[1701];
    n[1702] = h[1702];
    n[1703] = h[1703];
    n[1704] = h[1704];
    n[1705] = h[1705];
    n[1706] = h[1706];
    n[1707] = h[1707];
    n[1801] = h[1801];
    n[1802] = h[1802];
    n[1803] = h[1803];
    n[1804] = h[1804];
    n[1805] = h[1805];
    n[1806] = h[1806];
    n[1807] = h[1807];
    n[1901] = h[1901];
    n[1902] = h[1902];
    n[1903] = h[1903];
    n[1904] = h[1904];
    n[1905] = h[1905];
    n[1906] = h[1906];
    n[1907] = h[1907];
    n[2001] = h[2001];
    n[2002] = h[2002];
    n[2003] = h[2003];
    n[2004] = h[2004];
    n[2005] = h[2005];
    n[2006] = h[2006];
    n[2007] = h[2007];
    n[2101] = h[2101];
    n[2102] = h[2102];
    n[2103] = h[2103];
    n[2104] = h[2104];
    n[2105] = h[2105];
    n[2106] = h[2106];
    n[2107] = h[2107];
    n[2201] = h[2201];
    n[2202] = h[2202];
    n[2203] = h[2203];
    n[2204] = h[2204];
    n[2205] = h[2205];
    n[2206] = h[2206];
    n[2207] = h[2207];
    n[2301] = h[2301];
    n[2302] = h[2302];
		     );
calcMCll[which_] := n[which+01];
calcMCother[which_] := n[which+02];
calcData[which_] := Module[{nptobge, nctobge, nptobgp, nctobgp, ndtocos},
			   nptobge = n[110]/n[111];
			   nctobge = n[210]/n[211];
			   nptobgp = n[120]/n[122];
			   nctobgp = n[220]/n[222];
			   ndtocos = (n[400]-nptoc*n[401]
				      - (nptobge-nptoc*nctobge)*n[402]
				      - (nptobgp-nptoc*nctobgp)*n[403])/n[404];
			   n[which+03] - nptoc*n[which+04] -
			   ((nptobge-nptoc*nctobge)*n[which+05]
			   + (nptobgp-nptoc*nctobgp)*n[which+06]
			   + ndtocos*n[which+07])];
jiggleMCll[numer_, denom_] := (n[numer+01] = Rand[h[numer+01], h[denom+01]];);
jiggleMCother[numer_, denom_] := (n[numer+02] = Rand[h[numer+02], h[denom+02]];);
jiggledata[numer_, denom_] := (n[numer+03] = Rand[h[numer+03], h[denom+03]];
			       n[numer+04] = Rand[h[numer+04], h[denom+04]];
			       n[numer+05] = Rand[h[numer+05], h[denom+05]];
			       n[numer+06] = Rand[h[numer+06], h[denom+06]];
			       n[numer+07] = Rand[h[numer+07], h[denom+07]];);
jiggleptoc[] := (nptoc = Random[NormalDistribution[hptoc, hptocerr]]);
jigglebackgrounds[] := (n[110] = Random[NormalDistribution[h[110], Sqrt[h[110]]]];
			n[111] = Random[NormalDistribution[h[111], Sqrt[h[111]]]];
			n[210] = Random[NormalDistribution[h[210], Sqrt[h[210]]]];
			n[211] = Random[NormalDistribution[h[211], Sqrt[h[211]]]];
			n[120] = Random[NormalDistribution[h[120], Sqrt[h[120]]]];
			n[122] = Random[NormalDistribution[h[122], Sqrt[h[122]]]];
			n[220] = Random[NormalDistribution[h[220], Sqrt[h[220]]]];
			n[222] = Random[NormalDistribution[h[222], Sqrt[h[222]]]];
			n[400] = Random[NormalDistribution[h[400], Sqrt[h[400]]]];
			n[401] = Random[NormalDistribution[h[401], Sqrt[h[401]]]];
			n[402] = Random[NormalDistribution[h[402], Sqrt[h[402]]]];
			n[403] = Random[NormalDistribution[h[403], Sqrt[h[403]]]];
			n[404] = Random[NormalDistribution[h[404], Sqrt[h[404]]]];
		       );
lev[none] = 2300;
lev[trigger] = 1400;
lev[d0close] = 1500;
lev[e1] = 1600;
lev[p2] = 1700;
lev[wz] = 1800;
lev[visen] = 2000;
lev[tracks] = 2100;
lev[l4dec] = 1900;
lev[ccen] = 2200;
lev[all] = 2200;
longline[name_, numer_, denom_, trials_] := (
    unjiggle[];
    Print[name, " ", N[calcMCll[numer] / calcMCll[denom]]*100, "\\% & $\\pm$ ",
	  CForm[StandardDeviation[Table[(jiggleMCll[numer, denom]; N[calcMCll[numer] / calcMCll[denom]]), {trials}]]*100], "\\% & ",
	  N[calcMCother[numer] / calcMCother[denom]]*100, "\\% & $\\pm$ ",
	  CForm[StandardDeviation[Table[(jiggleMCother[numer, denom]; N[calcMCother[numer] / calcMCother[denom]]), {trials}]]*100], "\\% & ",
	  N[calcData[numer] / calcData[denom]]*100, "\\% & $\\pm$ ",
	  CForm[StandardDeviation[Table[(jiggledata[numer, denom]; N[calcData[numer] / calcData[denom]]), {trials}]]*100], "\\% & $\\pm$ ",
	  CForm[StandardDeviation[Table[(jiggleptoc[]; N[calcData[numer] / calcData[denom]]), {trials}]]*100], "\\% & $\\pm$ ",
	  CForm[StandardDeviation[Table[(jigglebackgrounds[]; N[calcData[numer] / calcData[denom]]), {trials}]]*100], "\\% \\\\ "];
			    );
shortline[name_, numer_, denom_, trials_] := (
    unjiggle[];
    Print[name, " ", N[calcMCll[numer] / calcMCll[denom]]*100, "\\% & $\\pm$ ",
	  CForm[StandardDeviation[Table[(jiggleMCll[numer, denom]; N[calcMCll[numer] / calcMCll[denom]]), {trials}]]*100], "\\% & ",
	  N[calcMCother[numer] / calcMCother[denom]]*100, "\\% & $\\pm$ ",
	  CForm[StandardDeviation[Table[(jiggleMCother[numer, denom]; N[calcMCother[numer] / calcMCother[denom]]), {trials}]]*100], "\\% & ",
	  " {\\it n/a} & {\\it n/a} & {\\it n/a} & {\\it n/a} \\\\ "]);
wholeblock[trials_] := (
    shortline["trigger",                          lev[trigger], lev[none], trials];
    longline["closest track d0 $<$ 5 mm",         lev[d0close], lev[trigger], trials];
    longline["biggest shower $<$ 85\\%",          lev[e1],     	lev[d0close], trials];
    longline["second-biggest track $<$ 85\\%",    lev[p2],     	lev[e1], trials];
    longline["event vertex Z or z0 $<$ 7.5 cm",   lev[wz],     	lev[p2], trials];
    longline["visible energy $>$ 20\\%",          lev[visen],  	lev[wz], trials];
    longline["number of quality tracks $\\ge$ 2", lev[tracks], 	lev[visen], trials];
    longline["level3/level4",                     lev[l4dec],  	lev[tracks], trials];
    longline["CC energy $<$ 85\\%",               lev[ccen],   	lev[l4dec], trials];
    longline["all cuts except trigger",           lev[all],    	lev[trigger], trials];
    shortline["all cuts",                         lev[all],    	lev[none], trials];
		);
SetOptions[$Output, PageWidth -> Infinity, PageHeight -> Infinity];

RunThrough["perl mathemetize_table.pl tables/all1.table", Null];
wholeblock[1000];

trigger 69.6652\% & $\pm$ 0.5489803829293581\% & 99.1719\% & $\pm$ 0.02361699475699768\% &  {\it n/a} & {\it n/a} & {\it n/a} & {\it n/a} \\ 
closest track d0 $<$ 5 mm 98.8881\% & $\pm$ 0.13982488898156747\% & 99.883\% & $\pm$ 0.008850567405149933\% & 99.0494\% & $\pm$ 0.398788780616818\% & $\pm$ 0.0964723847067765\% & $\pm$ 5.671624681924363\% \\ 
biggest shower $<$ 85\% 42.9452\% & $\pm$ 0.6693414273765632\% & 99.0173\% & $\pm$ 0.026343362137672806\% & 98.0837\% & $\pm$ 0.4460182738798352\% & $\pm$ 1.194482303525832\% & $\pm$ 0.14612817401949682\% \\ 
second-biggest track $<$ 85\% 11.2753\% & $\pm$ 0.6265586638738573\% & 99.9398\% & $\pm$ 0.0064840020598770295\% & 98.5818\% & $\pm$ 0.1397923466810455\% & $\pm$ 0.03981090752427604\% & $\pm$ 0.07689131696397633\% \\ 
event vertex Z or z0 $<$ 7.5 cm 90.2622\% & $\pm$ 1.823526244122931\% & 99.3878\% & $\pm$ 0.020545690820847458\% & 99.3139\% & $\pm$ 0.1878067007332219\% & $\pm$ 0.09284581709860473\% & $\pm$ 6.757958017431019\% \\ 
visible energy $>$ 20\% 72.1992\% & $\pm$ 2.734478994129465\% & 99.8941\% & $\pm$ 0.008856394785138924\% & 99.4507\% & $\pm$ 0.3069986590744862\% & $\pm$ 0.4195566386795129\% & $\pm$ 0.498727895520215\% \\ 
number of quality tracks $\ge$ 2 78.7356\% & $\pm$ 3.0280127088966844\% & 99.6722\% & $\pm$ 0.014468586861893402\% & 100.109\% & $\pm$ 0.22549026255847537\% & $\pm$ 0.1972388672823042\% & $\pm$ 0.02571784383801785\% \\ 
level3/level4 100.\% & $\pm$ 0.\% & 99.9958\% & $\pm$ 0.0016664558464845394\% & 99.9883\% & $\pm$ 0.015165362867423062\% & $\pm$ 0.0007811547008837806\% & $\pm$ 0.0023487651180368317\% \\ 
CC energy $<$ 85\% 91.2409\% & $\pm$ 2.3415406150119598\% & 98.557\% & $\pm$ 0.031519228065712786\% & 99.8438\% & $\pm$ 0.08834388252799631\% & $\pm$ 0.0232955075627777\% & $\pm$ 0.00022206708542725292\% \\ 
all cuts except trigger 2.24175\% & $\pm$ 0.19968166305622095\% & 96.3955\% & $\pm$ 0.047177566889519885\% & 94.5377\% & $\pm$ 0.41335315433709907\% & $\pm$ 1.6374971718272193\% & $\pm$ 10.820533561588455\% \\ 
all cuts 1.56172\% & $\pm$ 0.13478084052575845\% & 95.5972\% & $\pm$ 0.055945204910094415\% &  {\it n/a} & {\it n/a} & {\it n/a} & {\it n/a} \\ 

RunThrough["perl mathemetize_table.pl tables/all2.table", Null];
wholeblock[1000];

trigger 75.4612\% & $\pm$ 0.4792337260492154\% & 99.388\% & $\pm$ 0.018599179192579463\% &  {\it n/a} & {\it n/a} & {\it n/a} & {\it n/a} \\ 
closest track d0 $<$ 5 mm 99.3731\% & $\pm$ 0.10005362917210239\% & 99.9059\% & $\pm$ 0.007501362772014629\% & 96.0935\% & $\pm$ 0.9957547385368726\% & $\pm$ 0.07437708339966108\% & $\pm$ 35.84106743340183\% \\ 
biggest shower $<$ 85\% 46.0337\% & $\pm$ 0.6029315649014922\% & 99.1326\% & $\pm$ 0.022677656243581607\% & 99.8188\% & $\pm$ 1.093290446929113\% & $\pm$ 1.08719659888197\% & $\pm$ 0.10586338833827275\% \\ 
second-biggest track $<$ 85\% 12.4358\% & $\pm$ 0.6228523129156157\% & 99.9548\% & $\pm$ 0.0051683044795289915\% & 97.3763\% & $\pm$ 0.31642804953827713\% & $\pm$ 0.01672113326548811\% & $\pm$ 2.097221106885026\% \\ 
event vertex Z or z0 $<$ 7.5 cm 92.011\% & $\pm$ 1.4052143839061604\% & 99.4643\% & $\pm$ 0.016791443587819498\% & 101.527\% & $\pm$ 0.5591432102403591\% & $\pm$ 0.0261504462484795\% & $\pm$ 46.05792869064736\% \\ 
visible energy $>$ 20\% 79.6407\% & $\pm$ 2.1318246375533993\% & 99.9213\% & $\pm$ 0.00657957277096706\% & 100.437\% & $\pm$ 0.7349859443903216\% & $\pm$ 0.4594926888660102\% & $\pm$ 1.4125377931925955\% \\ 
number of quality tracks $\ge$ 2 89.0977\% & $\pm$ 1.8217603854154045\% & 99.7877\% & $\pm$ 0.011185305402299704\% & 100.444\% & $\pm$ 0.5008766911597959\% & $\pm$ 0.17349242848632815\% & $\pm$ 0.08928439530658432\% \\ 
level3/level4 99.5781\% & $\pm$ 0.4099439920473752\% & 99.9965\% & $\pm$ 0.001418556499798168\% & 100.014\% & $\pm$ 0.03580108661339131\% & $\pm$ 0.0006287247972297731\% & $\pm$ 0.027048214071746395\% \\ 
CC energy $<$ 85\% 87.2881\% & $\pm$ 2.152668638864632\% & 98.6994\% & $\pm$ 0.027518798304226835\% & 99.4754\% & $\pm$ 0.19263711404690467\% & $\pm$ 0.017192055555077804\% & $\pm$ 0.0038537531895087933\% \\ 
all cuts except trigger 3.22833\% & $\pm$ 0.2132441446861124\% & 96.8976\% & $\pm$ 0.042313693102958086\% & 95.1777\% & $\pm$ 0.8640007552312845\% & $\pm$ 1.6024344266379213\% & $\pm$ 132.64048093378858\% \\ 
all cuts 2.43614\% & $\pm$ 0.1691486913708757\% & 96.3046\% & $\pm$ 0.04426184398533645\% &  {\it n/a} & {\it n/a} & {\it n/a} & {\it n/a} \\ 

RunThrough["perl mathemetize_table.pl tables/all3.table", Null];
wholeblock[1000];

trigger 71.2929\% & $\pm$ 0.638824405539351\% & 99.4009\% & $\pm$ 0.0245867810127052\% &  {\it n/a} & {\it n/a} & {\it n/a} & {\it n/a} \\ 
closest track d0 $<$ 5 mm 98.6095\% & $\pm$ 0.1928192993434492\% & 99.9028\% & $\pm$ 0.009703830075263825\% & 110.599\% & $\pm$ 2.1639476708990273\% & $\pm$ 0.3107964858717807\% & $\pm$ 2229.822362392184\% \\ 
biggest shower $<$ 85\% 44.2714\% & $\pm$ 0.8673855715279997\% & 99.287\% & $\pm$ 0.027142844496259998\% & 96.0704\% & $\pm$ 1.8549863319085935\% & $\pm$ 0.9875527938036394\% & $\pm$ 14.907018702118302\% \\ 
second-biggest track $<$ 85\% 14.0013\% & $\pm$ 0.8698834635974148\% & 99.9677\% & $\pm$ 0.005702056693873337\% & 97.9562\% & $\pm$ 0.5622284488084259\% & $\pm$ 0.027277390280962016\% & $\pm$ 25.255482636216442\% \\ 
event vertex Z or z0 $<$ 7.5 cm 95.2607\% & $\pm$ 1.4876749534030724\% & 99.7477\% & $\pm$ 0.01648877812746049\% & 97.6163\% & $\pm$ 1.1306645928742798\% & $\pm$ 0.14312071950409153\% & $\pm$ 758582.9281200009\% \\ 
visible energy $>$ 20\% 70.1493\% & $\pm$ 3.123753912172307\% & 99.9279\% & $\pm$ 0.008942526123175734\% & 107.293\% & $\pm$ 1.431932082315948\% & $\pm$ 0.5567332843376506\% & $\pm$ 3.5115469029331963\% \\ 
number of quality tracks $\ge$ 2 84.3972\% & $\pm$ 2.994533203827803\% & 99.7699\% & $\pm$ 0.01542506879232549\% & 95.5698\% & $\pm$ 0.8835612935278128\% & $\pm$ 0.13601690622655024\% & $\pm$ 0.24713669314717035\% \\ 
level3/level4 100.\% & $\pm$ 0.\% & 99.9979\% & $\pm$ 0.0014070088080273193\% & 100.033\% & $\pm$ 0.07096068770890471\% & $\pm$ 0.0008822590281976721\% & $\pm$ 0.039464981200838765\% \\ 
CC energy $<$ 85\% 89.916\% & $\pm$ 2.713287042678148\% & 98.7441\% & $\pm$ 0.036280768486337565\% & 99.9053\% & $\pm$ 0.3778286583275359\% & $\pm$ 0.0259705081996425\% & $\pm$ 0.006184797941507725\% \\ 
all cuts except trigger 3.09965\% & $\pm$ 0.30195982881969907\% & 97.3691\% & $\pm$ 0.05219707350622928\% & 104.117\% & $\pm$ 1.6171096490428896\% & $\pm$ 1.8905645491774208\% & $\pm$ 2179.211131291807\% \\ 
all cuts 2.20983\% & $\pm$ 0.2153017293163143\% & 96.7858\% & $\pm$ 0.05721614859117567\% &  {\it n/a} & {\it n/a} & {\it n/a} & {\it n/a} \\ 

RunThrough["perl mathemetize_table.pl tables/db16.table", Null];
wholeblock[1000];

trigger 71.2929\% & $\pm$ 0.6361732031961561\% & 99.4009\% & $\pm$ 0.025666701420527474\% &  {\it n/a} & {\it n/a} & {\it n/a} & {\it n/a} \\ 
closest track d0 $<$ 5 mm 98.6095\% & $\pm$ 0.20091386024287988\% & 99.9028\% & $\pm$ 0.00987296250181142\% & 105.455\% & $\pm$ 3.347207787567927\% & $\pm$ 0.013912313802280843\% & $\pm$ 1052.3521290726258\% \\ 
biggest shower $<$ 85\% 44.2714\% & $\pm$ 0.8436508008984032\% & 99.287\% & $\pm$ 0.027459779361906512\% & 96.009\% & $\pm$ 2.86349409968428\% & $\pm$ 0.9359310475885994\% & $\pm$ 79.05939393141195\% \\ 
second-biggest track $<$ 85\% 14.0013\% & $\pm$ 0.9296211270991577\% & 99.9677\% & $\pm$ 0.005734452084582832\% & 97.8836\% & $\pm$ 0.8342819212771009\% & $\pm$ 0.014922984307345016\% & $\pm$ 6.868507296608252\% \\ 
event vertex Z or z0 $<$ 7.5 cm 95.2607\% & $\pm$ 1.470851816569169\% & 99.7477\% & $\pm$ 0.015882531772436658\% & 93.3893\% & $\pm$ 1.8978658074251298\% & $\pm$ 0.1537182848724279\% & $\pm$ 660.7221421483378\% \\ 
visible energy $>$ 20\% 70.1493\% & $\pm$ 3.393112486951113\% & 99.9279\% & $\pm$ 0.009062449684628162\% & 108.295\% & $\pm$ 2.172610363911287\% & $\pm$ 0.6228593314657033\% & $\pm$ 4.490899054682494\% \\ 
number of quality tracks $\ge$ 2 84.3972\% & $\pm$ 3.0071300088012225\% & 99.7699\% & $\pm$ 0.01510584026648757\% & 96.9229\% & $\pm$ 1.2719056635503159\% & $\pm$ 0.15365068300164697\% & $\pm$ 0.16001854135141808\% \\ 
level3/level4 100.\% & $\pm$ 0.\% & 99.9979\% & $\pm$ 0.0015008759823894092\% & 100.176\% & $\pm$ 0.12143543482697888\% & $\pm$ 0.0020895799553459675\% & $\pm$ 0.07003099742008238\% \\ 
CC energy $<$ 85\% 89.916\% & $\pm$ 2.7327042394408023\% & 98.7441\% & $\pm$ 0.03480750829225534\% & 99.7127\% & $\pm$ 0.5388605849682391\% & $\pm$ 0.022216647988873045\% & $\pm$ 0.018967437943798387\% \\ 
all cuts except trigger 3.09965\% & $\pm$ 0.30375486224645404\% & 97.3691\% & $\pm$ 0.04922140179129614\% & 97.0369\% & $\pm$ 2.3034699909801217\% & $\pm$ 1.7133166110166502\% & $\pm$ 5087.02446684159\% \\ 
all cuts 2.20983\% & $\pm$ 0.2031003746813166\% & 96.7858\% & $\pm$ 0.055242693551864265\% &  {\it n/a} & {\it n/a} & {\it n/a} & {\it n/a} \\ 

RunThrough["perl mathemetize_table.pl tables/db17.table", Null];
wholeblock[1000];

[Calculating...]

RunThrough["perl mathemetize_table.pl tables/db18.table", Null];
wholeblock[1000];

[Calculating...]

RunThrough["perl mathemetize_table.pl tables/db19.table", Null];
wholeblock[1000];

[Calculating...]

RunThrough["perl mathemetize_table.pl tables/db21.table", Null];
wholeblock[1000];

[Calculating...]

RunThrough["perl mathemetize_table.pl tables/db23.table", Null];
wholeblock[1000];

[Calculating...]
