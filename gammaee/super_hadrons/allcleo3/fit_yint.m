<< Graphics`MultipleListPlot`

(0.01864 - 5. * 0.00061)

jan16 = ReadList["y1s/jan16-02/scan_chi2.dat", {Real, Real}];
jan30 = ReadList["y1s/jan30-02/scan_chi2.dat", {Real, Real}];
feb06 = ReadList["y1s/feb06-02/scan_chi2.dat", {Real, Real}];
feb20 = ReadList["y1s/feb20-02/scan_chi2.dat", {Real, Real}];
feb28 = ReadList["y1s/feb28-02/scan_chi2.dat", {Real, Real}];
mar06 = ReadList["y1s/mar06-02/scan_chi2.dat", {Real, Real}];

(0.01792 - 5. * 0.00060)

jun11 = ReadList["y2s/jun11-02/scan_chi2.dat", {Real, Real}];
may28 = ReadList["y2s/may28-02/scan_chi2.dat", {Real, Real}];

(0.01823 - 5. * 0.00060)

dec06 = ReadList["y3s/dec06-01/scan_chi2.dat", {Real, Real}];
dec13 = ReadList["y3s/dec13-01/scan_chi2.dat", {Real, Real}];
dec20 = ReadList["y3s/dec20-01/scan_chi2.dat", {Real, Real}];
dec25 = ReadList["y3s/dec25-01/scan_chi2.dat", {Real, Real}];
jan03 = ReadList["y3s/jan03-02/scan_chi2.dat", {Real, Real}];
jan10 = ReadList["y3s/jan10-02/scan_chi2.dat", {Real, Real}];
nov29 = ReadList["y3s/nov29-01/scan_chi2.dat", {Real, Real}];

jan16func = Fit[jan16, {1, x, x^2}, {x}];
jan30func = Fit[jan30, {1, x, x^2}, {x}];
feb06func = Fit[feb06, {1, x, x^2}, {x}];
feb20func = Fit[feb20, {1, x, x^2}, {x}];
feb28func = Fit[feb28, {1, x, x^2}, {x}];
mar06func = Fit[mar06, {1, x, x^2}, {x}];

jun11func = Fit[jun11, {1, x, x^2}, {x}];
may28func = Fit[may28, {1, x, x^2}, {x}];

dec06func = Fit[dec06, {1, x, x^2}, {x}];
dec13func = Fit[dec13, {1, x, x^2}, {x}];
dec20func = Fit[dec20, {1, x, x^2}, {x}];
dec25func = Fit[dec25, {1, x, x^2}, {x}];
jan03func = Fit[jan03, {1, x, x^2}, {x}];
jan10func = Fit[jan10, {1, x, x^2}, {x}];
nov29func = Fit[nov29, {1, x, x^2}, {x}];

MultipleListPlot[{
    {0.01864, ErrorBar[0.00061]},
    {min = x /. Solve[D[jan16func, x] == 0, x][[1]], ErrorBar[Abs[x-min] /. #[[1]], Abs[x-min] /. #[[2]]]&[Solve[jan16func == (jan16func /. x -> min) + 1, x]]},
    {min = x /. Solve[D[jan30func, x] == 0, x][[1]], ErrorBar[Abs[x-min] /. #[[1]], Abs[x-min] /. #[[2]]]&[Solve[jan30func == (jan30func /. x -> min) + 1, x]]},
    {min = x /. Solve[D[feb06func, x] == 0, x][[1]], ErrorBar[Abs[x-min] /. #[[1]], Abs[x-min] /. #[[2]]]&[Solve[feb06func == (feb06func /. x -> min) + 1, x]]},
    {min = x /. Solve[D[feb20func, x] == 0, x][[1]], ErrorBar[Abs[x-min] /. #[[1]], Abs[x-min] /. #[[2]]]&[Solve[feb20func == (feb20func /. x -> min) + 1, x]]},
    {min = x /. Solve[D[feb28func, x] == 0, x][[1]], ErrorBar[Abs[x-min] /. #[[1]], Abs[x-min] /. #[[2]]]&[Solve[feb28func == (feb28func /. x -> min) + 1, x]]},
    {min = x /. Solve[D[mar06func, x] == 0, x][[1]], ErrorBar[Abs[x-min] /. #[[1]], Abs[x-min] /. #[[2]]]&[Solve[mar06func == (mar06func /. x -> min) + 1, x]]}
		 }, DisplayFunction -> (Display["yint_y1s.eps", #, "EPS"]&)];

MultipleListPlot[{
    {0.01792, ErrorBar[0.00060]},
    {min = x /. Solve[D[may28func, x] == 0, x][[1]], ErrorBar[Abs[x-min] /. #[[1]], Abs[x-min] /. #[[2]]]&[Solve[may28func == (may28func /. x -> min) + 1, x]]},
    {min = x /. Solve[D[jun11func, x] == 0, x][[1]], ErrorBar[Abs[x-min] /. #[[1]], Abs[x-min] /. #[[2]]]&[Solve[jun11func == (jun11func /. x -> min) + 1, x]]}
		 }, DisplayFunction -> (Display["yint_y2s.eps", #, "EPS"]&)];

MultipleListPlot[{
    {0.01823, ErrorBar[0.00060]},
    {min = x /. Solve[D[nov29func, x] == 0, x][[1]], ErrorBar[Abs[x-min] /. #[[1]], Abs[x-min] /. #[[2]]]&[Solve[nov29func == (nov29func /. x -> min) + 1, x]]},
    {min = x /. Solve[D[dec06func, x] == 0, x][[1]], ErrorBar[Abs[x-min] /. #[[1]], Abs[x-min] /. #[[2]]]&[Solve[dec06func == (dec06func /. x -> min) + 1, x]]},
    {min = x /. Solve[D[dec13func, x] == 0, x][[1]], ErrorBar[Abs[x-min] /. #[[1]], Abs[x-min] /. #[[2]]]&[Solve[dec13func == (dec13func /. x -> min) + 1, x]]},
    {min = x /. Solve[D[dec20func, x] == 0, x][[1]], ErrorBar[Abs[x-min] /. #[[1]], Abs[x-min] /. #[[2]]]&[Solve[dec20func == (dec20func /. x -> min) + 1, x]]},
    {min = x /. Solve[D[dec25func, x] == 0, x][[1]], ErrorBar[Abs[x-min] /. #[[1]], Abs[x-min] /. #[[2]]]&[Solve[dec25func == (dec25func /. x -> min) + 1, x]]},
    {min = x /. Solve[D[jan03func, x] == 0, x][[1]], ErrorBar[Abs[x-min] /. #[[1]], Abs[x-min] /. #[[2]]]&[Solve[jan03func == (jan03func /. x -> min) + 1, x]]},
    {min = x /. Solve[D[jan10func, x] == 0, x][[1]], ErrorBar[Abs[x-min] /. #[[1]], Abs[x-min] /. #[[2]]]&[Solve[jan10func == (jan10func /. x -> min) + 1, x]]}
		 }, DisplayFunction -> (Display["yint_y3s.eps", #, "EPS"]&)];


Exit

[Mathematica finished.]
