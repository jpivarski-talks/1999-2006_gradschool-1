<< Statistics`ContinuousDistributions`;

WeightedSum[ points:{ { ( _Integer | _Real ), ( _Integer | _Real ) } .. } ] :=
    { Plus @@ (#[[1]]& /@ points), Sqrt[ Plus @@ ((#[[2]]^2)& /@ points) ] };

y1sgoal = Plus @@ (#[[2]]& /@ ReadList["y1s_high.bgxs", {Real, Real}]);
y2sgoal = Plus @@ (#[[2]]& /@ ReadList["y2s_high.bgxs", {Real, Real}]);
y3sgoal = Plus @@ (#[[2]]& /@ ReadList["y3s_high.bgxs", {Real, Real}]);

y1scont = Sort[ReadList["y1s_cont.bgxs", {Real, Real}], (#1[[1]] < #2[[1]])&];
y2scont = Sort[ReadList["y2s_cont.bgxs", {Real, Real}], (#1[[1]] < #2[[1]])&];
y3scont = Sort[ReadList["y3s_cont.bgxs", {Real, Real}], (#1[[1]] < #2[[1]])&];
y1speak = Sort[ReadList["y1s_peak.bgxs", {Real, Real}], (#1[[1]] < #2[[1]])&];
y2speak = Sort[ReadList["y2s_peak.bgxs", {Real, Real}], (#1[[1]] < #2[[1]])&];
y3speak = Sort[ReadList["y3s_peak.bgxs", {Real, Real}], (#1[[1]] < #2[[1]])&];

InitialConf[data_] := Table[0, {Length[data]}];
ConfSum[data_, conf_] := Plus @@ (#[[2]]& /@ (data * conf));
ChangeConf1[conf_] := Module[{i = Random[Integer, Length[conf]-1]+1},
			     ReplacePart[conf, 1 - conf[[i]], i]];
FindOnes[conf_] := Flatten[Table[If[conf[[i]] == 1, {i}, {}], {i, 1, Length[conf]}], 1];
FindZeros[conf_] := Flatten[Table[If[conf[[i]] == 0, {i}, {}], {i, 1, Length[conf]}], 1];
RandElem[list_] := list[[Random[Integer, Length[list]-1]+1]];
ChangeConf2[conf_] := Module[{i = RandElem[FindOnes[conf]],
			      j = RandElem[FindZeros[conf]]},
			     ReplacePart[ReplacePart[conf, 1 - conf[[i]], i], 1 - conf[[j]], j]];
ChangeConf[conf_] := If[(Plus @@ conf) > 0  &&  Random[Integer] == 0,
			ChangeConf2[conf],
			ChangeConf1[conf]];
ConfRuns[data_, conf_] := (Print[TableForm[Select[data * conf, (# != {0, 0})&]]];
			   Print[]; Print["-------------------"]; Print[];
			   Print["          ", ConfSum[data, conf]];);
ListFromConf[data_, conf_] := #[[1]]& /@ Select[data * conf, (# != {0, 0})&];
GapsWeight[list_] := If[Length[list] < 3, 0,
			3./Sum[Abs[list[[i+1]] - list[[i]]], {i, 1, Length[list]-1}]];
FindBest[data_, goal_] := 
    Module[{lastconf = InitialConf[data], lastval, outplot},
	   lastval = Abs[ConfSum[data, lastconf] - goal]; (* + GapsWeight[ListFromConf[data, lastconf]]; *)
	   While[lastval > 0.0001, (
	       newconf = ChangeConf[lastconf];
	       newval = Abs[ConfSum[data, newconf] - goal]; (* + GapsWeight[ListFromConf[data, lastconf]]; *)
	       fall = newval < lastval;
	       grope = If[fall, False, Random[ExponentialDistribution[100]] > (newval - lastval)];
	       Print[lastval, " ", newval, " ", fall, " ", grope];
	       If[fall || grope, {lastval = newval, lastconf = newconf}];
				  )];
	   ConfRuns[data, lastconf];
	   outplot = Table[{i, data[[i, 1]]}, {i, 1, Length[data]}];
	   Show[ListPlot[outplot,
			 AspectRatio -> 3,
			 DisplayFunction -> Identity],
		ListPlot[Select[outplot * lastconf, (# != {0, 0})&],
			 PlotStyle -> RGBColor[1, 0, 0],
			 DisplayFunction -> Identity],
		DisplayFunction -> $DisplayFunction];
	   #[[1]]& /@ Select[data * lastconf, (# != {0, 0})&]];
ConfFromList[data_, list_] := If[MemberQ[list, #[[1]]], 1, 0]& /@ data;

FindBest[y3speak, 0.72673]
