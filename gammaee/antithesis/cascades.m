Clear[be, sigbe, bmu, sigbmu, btau, sigbtau]

sigehad2 = FullSimplify[
    sigetot^2*D[(etot - etau*btau)/(1-be-bmu-btau), etot]^2 +
    sigbe^2*D[(etot - etau*btau)/(1-be-bmu-btau), be]^2 +
    sigbmu^2*D[(etot - etau*btau)/(1-be-bmu-btau), bmu]^2 +
    sigbtau^2*D[(etot - etau*btau)/(1-be-bmu-btau), btau]^2]

                                  2         2
Out[10]= (-2 btau etau etot (sigbe  + sigbmu ) + 
 
                                          2
>      2 (-1 + be + bmu) etau etot sigbtau  + 
 
           2       2         2          2
>      etot  (sigbe  + sigbmu  + sigbtau ) + 
 
                                     2
>      2 (-1 + be + bmu) btau sigetot  + 
 
           2      2       2         2           2
>      btau  (etau  (sigbe  + sigbmu ) + sigetot ) + 
 
                      2      2        2          2                           4
>      (-1 + be + bmu)  (etau  sigbtau  + sigetot )) / (-1 + be + bmu + btau)



  \mathcal{B}_{ee} &=& 2.38 \pm 0.11\% \\
  \mathcal{B}_{\mu\mu} &=& 2.49 \pm 0.07\% \\
  \mathcal{B}_{\tau\tau} &=& 2.67 \pm 0.15\% \mbox{.}

      \pone\ $<$ 80\% \ebeam\ given previous & 94.68 $\pm$ 0.21\%
      everything given trigger               & 92.87 $\pm$ 0.42\%



be = 0.0238;
sigbe = 0.0011;
bmu = 0.0249;
sigbmu = 0.0007;
btau = 0.0267;
sigbtau = 0.0015;

FullSimplify[sigehad2 /. {etau -> 0.93}] // InputForm


\sqrt{2.41\times 10^{-6} + (-5.56\times 10^{-6} + 5.40\times 10^{-6} {\varepsilon_\subs{all modes}}) {\varepsilon_\subs{all modes}} + 1.17 {\sigma_{\varepsilon_\subs{all modes}}}^2}

FullSimplify[sigehad2 /. {etau -> 0.57}] // InputForm

Out[17]//InputForm= 
9.057536156834611*^-7 + (-3.4095942257419586*^-6 + 
   5.404823786543283*^-6*etot)*etot + 1.1697477588685719*sigetot^2


\sqrt{0.91\times 10^{-6} + (-3.41\times 10^{-6} + 5.40\times 10^{-6} {\varepsilon_\subs{all modes}}) {\varepsilon_\subs{all modes}} + 1.17 {\sigma_{\varepsilon_\subs{all modes}}}^2}

FullSimplify[Sqrt[sigehad2] /. {etau -> 0.93, etot -> 0.9184, sigetot -> 0.0084}]

Out[29]= 0.00918685

FullSimplify[Sqrt[sigehad2] /. {etau -> 0.57, etot -> 0.9245, sigetot -> 0.0048}]

Out[20]= 0.00541517






%% Propagating uncertainties for $\varepsilon_\subs{had}$, I obtain
%% \begin{multline}
%%   {\sigma_{\varepsilon_\subs{had}}}^2 = 
%% (-2 {\mathcal{B}_{\tau\tau}} {\varepsilon_{\tau\tau}} {\varepsilon_\subs{all modes}} ({\sigma_{\mathcal{B}_{ee}}}^2 + {\sigma_{\mathcal{B}_{\mu\mu}}}^2) + 2 ({\mathcal{B}_{ee}} + {\mathcal{B}_{\mu\mu}} - 1) {\varepsilon_{\tau\tau}} {\varepsilon_\subs{all modes}} 
%%    {\sigma_{\mathcal{B}_{\tau\tau}}}^2 + \\ + {\varepsilon_\subs{all modes}}^2 ({\sigma_{\mathcal{B}_{ee}}}^2 + {\sigma_{\mathcal{B}_{\mu\mu}}}^2 + {\sigma_{\mathcal{B}_{\tau\tau}}}^2) + 
%%   2 ({\mathcal{B}_{ee}} + {\mathcal{B}_{\mu\mu}} - 1)
%%   {\mathcal{B}_{\tau\tau}}^3 {\sigma_{\varepsilon_{\tau\tau}}}^2 + \\ + {\mathcal{B}_{\tau\tau}}^4 {\sigma_{\varepsilon_{\tau\tau}}}^2 + 
%%   2 ({\mathcal{B}_{ee}} + {\mathcal{B}_{\mu\mu}} - 1) {\mathcal{B}_{\tau\tau}} {\sigma_{\varepsilon_\subs{all modes}}}^2 + ({\mathcal{B}_{ee}} + {\mathcal{B}_{\mu\mu}} - 1)^2 
%%    ({\varepsilon_{\tau\tau}}^2 {\sigma_{\mathcal{B}_{\tau\tau}}}^2 +
%%    {\sigma_{\varepsilon_\subs{all modes}}}^2) + \\ + {\mathcal{B}_{\tau\tau}}^2 ({\varepsilon_{\tau\tau}}^2 ({\sigma_{\mathcal{B}_{ee}}}^2 + {\sigma_{\mathcal{B}_{\mu\mu}}}^2) + 
%%     ({\mathcal{B}_{ee}} + {\mathcal{B}_{\mu\mu}} -
%%    1)^2 {\sigma_{\varepsilon_{\tau\tau}}}^2 +
%%    {\sigma_{\varepsilon_\subs{all modes}}}^2)) / 
%% ({\mathcal{B}_{ee}} + {\mathcal{B}_{\mu\mu}} +
%% {\mathcal{B}_{\tau\tau}} - 1)^4 \mbox{.}
%% \end{multline}




102.5 $\pm$ 1.9

Integrate[Exp[-(x-102.5)^2/2/1.9^2]/Sqrt[2 Pi]/1.9, {x, 0., 100.}]

Out[23]= 0.0941223

Integrate[x*Exp[-(x-102.5)^2/2/1.9^2]/Sqrt[2 Pi]/1.9, {x, 0., 100.}] / Integrate[Exp[-(x-102.5)^2/2/1.9^2]/Sqrt[2 Pi]/1.9, {x, 0., 100.}]

Out[25]= 99.1114

Sqrt[Integrate[x^2*Exp[-(x-102.5)^2/2/1.9^2]/Sqrt[2 Pi]/1.9, {x, 0., 100.}] / Integrate[Exp[-(x-102.5)^2/2/1.9^2]/Sqrt[2 Pi]/1.9, {x, 0., 100.}] - Out[25]^2]

Out[28]= 0.773812

Exit

[Mathematica finished.]
