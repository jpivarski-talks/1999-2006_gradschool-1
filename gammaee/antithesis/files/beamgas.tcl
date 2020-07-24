\begin{verbatim}
default prompt off
\end{verbatim}\begin{verbatim}exception continueEventLoop on
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}run_file $env(C3_SCRIPTS)/getNewestConstants.tcl
\end{verbatim}\begin{verbatim}run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
\end{verbatim}\begin{verbatim}run_file $env(C3_SCRIPTS)/CcP2.tcl
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}prod sel CesrBeamEnergyProd
\end{verbatim}\begin{verbatim}prod sel EventPropertiesProd
\end{verbatim}\begin{verbatim}prod sel TrackShowerMatchingProd
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}param DRHitCorrectorProd ApplyEntranceAngleCorr true
\end{verbatim}\begin{verbatim}param DRHitCorrectorProd ApplyStandardCorrections true
\end{verbatim}\begin{verbatim}param KalmanProd HyposToFit pion
\end{verbatim}\begin{verbatim}param KalmanProd OptimizeForAllHypos true
\end{verbatim}\begin{verbatim}param KalmanProd HitListFromOneHypo true
\end{verbatim}\begin{verbatim}param KalmanProd ScaleCathodeResolution true
\end{verbatim}\begin{verbatim}param KalmanProd CathodeResolutionScale 0.7    
\end{verbatim}\begin{verbatim}param DetectorConfigurationProd UseZDnotSI false
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}run_file $env(C3_SCRIPTS)/CcHotList.tcl
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}proc sel Level4Proc
\end{verbatim}\begin{verbatim}param Level4Proc TagOnly true
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}module sel DBModule
\end{verbatim}\begin{verbatim}database in /nfs/cleo3/database/data21/db event \
\end{verbatim}\begin{verbatim}                                   startrun beginrun endrun
\end{verbatim}\begin{verbatim}database read_collection rawdata
\end{verbatim}\begin{verbatim}database run [RUN NUMBER]
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}sink_format sel PDSSinkFormat
\end{verbatim}\begin{verbatim}file out ../../data_method_rzn/beamgas/r[RUN NUMBER].pds {event{\
\end{verbatim}\begin{verbatim}    DBTrackerValues FATable<TRTrack> FATable<TRHelixPionFit> \
\end{verbatim}\begin{verbatim}    FATable<TRPionQuality> FATable<TRSeedTrack> \
\end{verbatim}\begin{verbatim}    FATable<TRSeedTrackQuality> FATable<CcBasicShowerAttsArg> \
\end{verbatim}\begin{verbatim}    TrackShowerLattice FATable<CcConRegAttributes> \
\end{verbatim}\begin{verbatim}    CcConRegShowerLattice TriggerL1Data Level3TagWord \
\end{verbatim}\begin{verbatim}    Level4Decision EventProperties DBEventHeader \
\end{verbatim}\begin{verbatim}}} startrun beginrun endrun
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}go
\end{verbatim}
