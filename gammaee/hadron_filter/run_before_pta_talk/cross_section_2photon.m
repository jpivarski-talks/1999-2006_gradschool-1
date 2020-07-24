f[z_] := (1 + z/2)^2 * Log[1/z] - (1 - z)*(3 + z)/2

crossSection[s_, j_, width_, mass_, mv_] := (2*j + 1) * (8 * width) / (mass^3 * 137^2)
    * (f[mass^2/s] * Log[s*mv^2/511^2/mass^2 - 1]^2 - Log[s/mass^2]^3/3)
    * 0.389*^18

<< Graphics`Graphics`

LogPlot[crossSection[(10*^6)^2, 0, 30, mass*1*^3, 135*^3], {mass, 135, 10*^3}, PlotRange -> All];

(* name, \Gamma_{R \to \gamma \gamma} (keV), mass (MeV), J *)
particles = { 
    {"pi0", 0.0079236, 134.9766, 0, False},
    {"eta", 0.46, 547.30, 0, False},
    {"f0", 10, 400, 0, False},
    {"eta_prime", 4.28, 957.78, 0, False},
    {"f0(980)", 0.39, 980, 0, False},
    {"a0(980)", 0.30, 984.8, 0, False},
    {"f2(1270)", 2.60, 1275.4, 2, False},
    {"f1(1285)", 1.2, 1281.9, 1, False},
    {"eta(1295)", 30, 1297.0, 0, False},
    {"pi(1300)", 0.8, 1300, 0, False},
    {"a2(1320)", 1.00, 1318.0, 2, False},
    {"f0(1370)", 4, 1200, 0, False},
    {"eta(1440)", 1, 1400, 2, False},
    {"f0(1500)", 1.01, 1500, 0, False},
    {"f2_prime(1525)", 0.10032, 1525, 2, False},
    {"pi2(1670)", 0.1, 1670, 2, False},
    {"f0(1710)", 1.1, 1715, 0, False},
    {"a2(1750)", 100, 1752, 2, False},  (* all I really know about Gamma+2photons < 150000, the full width *)
    {"f4(2050)", 6.5, 2034, 4, False},
    {"fj(2220)", 0.56, 2231.1, 4, False},
    {"etac(1s)", 7.4, 2979.8, 0, True},
    {"jpsi(1s)", 5.4, 3096.87, 1, True},
    {"chic0(1p)", 4.0, 3415.0, 0, True},
    {"chic1(1p)", 1.32, 3510.51, 1, True},
    {"chic2(1p)", 0.46, 3556.18, 2, True},
    {"etac(2s)", 80, 3594, 2, True},
    {"psi(2s)", 0.043, 3685.96, 1, True}
	    };

{#[[1]], ToString[ crossSection[(10*^6)^2, #[[4]], #[[2]], #[[3]]*1*^3,
				If[#[[5]], #[[3]]*1*^3, 135*^3]] ] <> " nb"}& /@ particles // TableForm

Out[31]//TableForm= pi0              1.37051 nb

                    eta              0.549451 nb

                    f0               37.3765 nb

                    eta_prime        0.629964 nb

                    f0(980)          0.0525798 nb

                    a0(980)          0.0396958 nb

                    f2(1270)         0.630635 nb

                    f1(1285)         0.17118 nb

                    eta(1295)        1.36222 nb

                    pi(1300)         0.0359967 nb

                    a2(1320)         0.213103 nb

                    f0(1370)         0.246392 nb

                    eta(1440)        0.167791 nb

                    f0(1500)         0.0257352 nb

                    f2_prime(1525)   0.0119608 nb

                    pi2(1670)        0.00825996 nb

                    f0(1710)         0.0163067 nb

                    a2(1750)         6.79297 nb

                    f4(2050)         0.428488 nb

                    fj(2220)         0.0249829 nb

                    etac(1s)         0.0221317 nb

                    jpsi(1s)         0.0411216 nb

                    chic0(1p)        0.00664546 nb

                    chic1(1p)        0.00582492 nb

                    chic2(1p)        0.00319444 nb

                    etac(2s)         0.529969 nb

                    psi(2s)          0.000152615 nb

{#[[1]], ToString[#[[2]]] <> " nb"}& /@
    Sort[ {#[[1]], crossSection[(10*^6)^2, #[[4]], #[[2]], #[[3]]*1*^3,
				If[#[[5]], #[[3]]*1*^3, 135*^3]]}& /@ particles
	  , (#1[[2]] > #2[[2]])& ] // TableForm

Out[38]//TableForm= f0               37.3765 nb

                    a2(1750)         6.79297 nb

                    pi0              1.37051 nb

                    eta(1295)        1.36222 nb

                    f2(1270)         0.630635 nb

                    eta_prime        0.629964 nb

                    eta              0.549451 nb

                    etac(2s)         0.529969 nb

                    f4(2050)         0.428488 nb

                    f0(1370)         0.246392 nb

                    a2(1320)         0.213103 nb

                    f1(1285)         0.17118 nb

                    eta(1440)        0.167791 nb

                    f0(980)          0.0525798 nb

                    jpsi(1s)         0.0411216 nb

                    a0(980)          0.0396958 nb

                    pi(1300)         0.0359967 nb

                    f0(1500)         0.0257352 nb

                    fj(2220)         0.0249829 nb

                    etac(1s)         0.0221317 nb

                    f0(1710)         0.0163067 nb

                    f2_prime(1525)   0.0119608 nb

                    pi2(1670)        0.00825996 nb

                    chic0(1p)        0.00664546 nb

                    chic1(1p)        0.00582492 nb

                    chic2(1p)        0.00319444 nb

                    psi(2s)          0.000152615 nb

Exit

[Mathematica finished.]
