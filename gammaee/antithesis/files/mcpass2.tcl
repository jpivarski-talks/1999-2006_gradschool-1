\begin{verbatim}
default prompt off
\end{verbatim}\begin{verbatim}exception continueEventLoop on
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}prod sel DBEventHeaderProd
\end{verbatim}\begin{verbatim}prod sel MCInfoDelivery
\end{verbatim}\begin{verbatim}prod sel MCTriggerPhaseProd
\end{verbatim}\begin{verbatim}prod sel MCSymmetricBeamProd
\end{verbatim}\begin{verbatim}prod desel MCInfoDelivery
\end{verbatim}\begin{verbatim}prod desel MCTriggerPhaseProd
\end{verbatim}\begin{verbatim}prod desel MCSymmetricBeamProd
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}prod sel CustomBeamEnergyProd
\end{verbatim}\begin{verbatim}prod sel TriggerInfoProd
\end{verbatim}\begin{verbatim}prod desel TriggerInfoProd
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}run_file scripts_$env(CMLIB)/mcpass2_command.tcl
\end{verbatim}\begin{verbatim}mcpass2 file $env(USER_CLEOG) out $env(USER_MCPASS2) -post {
\end{verbatim}\begin{verbatim}    global env;
\end{verbatim}\begin{verbatim}    param CustomBeamEnergyProd BeamEnergy $env(USER_EBEAM);
\end{verbatim}\begin{verbatim}    param CustomBeamEnergyProd NoRunStat true;
\end{verbatim}\begin{verbatim}    prod lss
\end{verbatim}\begin{verbatim}}
\end{verbatim}
