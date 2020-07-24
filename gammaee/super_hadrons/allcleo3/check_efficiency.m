effr := Pp/Np/(1-sigc/sigp) - Pc/Nc/(sigp/sigc-1);
deffr := Sqrt[dPp^2*(1/Np/(1-sigc/sigp))^2 + dPc^2*(1/Nc/(sigp/sigc-1))^2 +
	      dNp^2*(Pp/Np^2/(1-sigc/sigp))^2 + dNc^2*(Pc/Nc^2/(sigp/sigc-1))^2 +
	      dsigc^2*((Pp*(1/sigp)/Np/(1-sigc/sigp)^2) - (Pc*(sigp/sigc^2)/Nc/(sigp/sigc-1)^2))^2 +
	      dsigp^2*(-(Pp*(sigc/sigp^2)/Np/(1-sigc/sigp)^2) + (Pc*(1/sigc)/Nc/(sigp/sigc-1)^2))^2]

(* lumi is 138823 +/- 282.981377479155 +/- 3470.6 *)

(* For Y(1S) *)
Pc = 653041.861800001;
dPc = 813.265493806049;
stepPc = 1945.916;
Nc = 8119255;
dNc = Sqrt[Nc];
sigc = 4.70413304567687;
dsigc = 0.0112369763805192;
stepsigc = 0.128411117213466; "Evaluated."
Out[7]= Evaluated.

(* lumi is 622152.1 +/- 600.881244506766 +/- 15555 *)

(* For Y(1S) *)
Pp = 14142114.3195;
dPp = 3766.59940416041;
stepPp = 12462.69;
Np = 47928760;
dNp = Sqrt[Np];
sigp = 22.7309597114596;
dsigp = 0.0227732812135753;
stepsigp = 0.573998263954962; "Evaluated."
Out[8]= Evaluated.

(* Y(1S) efficiency *)
effr
Out[9]= 0.351074

(* statistical uncertainty in Y(1S) efficiency *)
deffr
Out[10]= 0.000216595

Pc = Pc + stepPc;
sigc = sigc + stepsigc;
effr
Out[11]= 0.352951

(* systematic uncertainty in Y(1S) efficiency *)
Out[11] - Out[9]
Out[13]= 0.001877








(* lumi is 97969.3 +/- 261.59860473634 +/- 2449.4 *)

(* For Y(3S) *)
Pc = 395521.7864;
dPc = 635.540323100467;
stepPc = 1761.048;
Nc = 4962886;
dNc = Sqrt[Nc];
sigc = 4.03720131102294;
dsigc = 0.0125815393853911;
stepsigc = 0.116011946890565; "Evaluated."
Out[14]= Evaluated.

(* lumi is 695482.3 +/- 699.038146312488 +/- 17387.6 *)

(* For Y(3S) *)
Pp = 5512608.9022;
dPp = 2360.26693970949;
stepPp = 13297.244;
Np = 38084268;
dNp = Sqrt[Np];
sigp = 7.92631085248324;
dsigp = 0.00865954762608848;
stepsigp = 0.211983654491005; "Evaluated."
Out[15]= Evaluated.

(* Y(3S) efficiency *)
effr
Out[16]= 0.212276

(* statistical uncertainty in Y(3S) efficiency *)
deffr
Out[17]= 0.000493822

Pc = Pc + stepPc;
sigc = sigc + stepsigc;
effr
Out[18]= 0.215962

(* systematic uncertainty in Y(3S) efficiency *)
Out[18] - Out[16]
Out[19]= 0.00368588








(* Fractional difference between Y(1S) efficiency and Y(3S) efficiency *)
2*(Out[16] - Out[9])/(Out[16] + Out[9])
Out[20]= -0.492758
(* Them's not the same! *)

