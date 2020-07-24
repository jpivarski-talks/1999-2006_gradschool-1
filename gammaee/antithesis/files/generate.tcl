\begin{verbatim}
default prompt off
\end{verbatim}\begin{verbatim}exception continueEventLoop on
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}prod sel CustomBeamEnergyProd
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}run_file $env(C3_SCRIPTS)/cleog_command.tcl
\end{verbatim}\begin{verbatim}cleog gen EvtGenProd 3000 out $env(USER_GEN) run $env(USER_RUN) \
\end{verbatim}\begin{verbatim}                                    -user_decay $env(USER_DEC) -post {
\end{verbatim}\begin{verbatim}    prod desel CesrBeamEnergyProd;
\end{verbatim}\begin{verbatim}    param CustomBeamEnergyProd BeamEnergy $env(USER_EBEAM);
\end{verbatim}\begin{verbatim}    param CustomBeamEnergyProd NoRunStat true;
\end{verbatim}\begin{verbatim}    param MCSymmetricBeamProd resonantProduction true;
\end{verbatim}\begin{verbatim}    param MCSymmetricBeamProd BWResonanceMass $env(USER_RES);
\end{verbatim}\begin{verbatim}    param MCSymmetricBeamProd BWResonanceWidth $env(USER_WIDE);
\end{verbatim}\begin{verbatim}    param MCSymmetricBeamProd totalEnergySpreadAt10GeV 0.0042036;
\end{verbatim}\begin{verbatim}    run_file qqonly.tcl;
\end{verbatim}\begin{verbatim}    prod lss;
\end{verbatim}\begin{verbatim}}
\end{verbatim}
