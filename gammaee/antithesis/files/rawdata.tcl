\begin{verbatim}
default prompt off
\end{verbatim}\begin{verbatim}exception continueEventLoop on
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}module select LoadGeantModule
\end{verbatim}\begin{verbatim}module select LoadHbookModule
\end{verbatim}\begin{verbatim}module select HbookHistogramModule
\end{verbatim}\begin{verbatim}hbook init
\end{verbatim}\begin{verbatim}source_format sel AsciiSourceFormat
\end{verbatim}\begin{verbatim}sink_format sel AsciiSinkFormat
\end{verbatim}\begin{verbatim}run_file $env(C3_SCRIPTS)/getPass2Constants.tcl
\end{verbatim}\begin{verbatim}run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
\end{verbatim}\begin{verbatim}prod sel MutrReconProd
\end{verbatim}\begin{verbatim}prod sel MuConsProd
\end{verbatim}\begin{verbatim}run_file $env(C3_SCRIPTS)/load_geometry_producers.tcl
\end{verbatim}\begin{verbatim}run_file $env(C3_SCRIPTS)/load_dg_to_geant3_converter.tcl
\end{verbatim}\begin{verbatim}prod sel MagFieldProd
\end{verbatim}\begin{verbatim}prod sel RawDataProd
\end{verbatim}\begin{verbatim}prod sel DBRunHeaderProd
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}run_file $env(C3_SCRIPTS)/CcP2.tcl
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}prod sel CesrBeamEnergyProd
\end{verbatim}\begin{verbatim}prod sel EventPropertiesProd
\end{verbatim}\begin{verbatim}prod sel TrackShowerMatchingProd
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}param DRHitCorrectorProd ApplyEntranceAngleCorr $env(USER_EA)
\end{verbatim}\begin{verbatim}param DRHitCorrectorProd ApplyStandardCorrections $env(USER_EA)
\end{verbatim}\begin{verbatim}param KalmanProd HyposToFit pion
\end{verbatim}\begin{verbatim}param KalmanProd OptimizeForAllHypos true
\end{verbatim}\begin{verbatim}param KalmanProd HitListFromOneHypo true
\end{verbatim}\begin{verbatim}param KalmanProd ScaleCathodeResolution true
\end{verbatim}\begin{verbatim}param KalmanProd CathodeResolutionScale 0.7    
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}proc sel Level4Proc
\end{verbatim}\begin{verbatim}param Level4Proc TagOnly true
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}module sel DBModule
\end{verbatim}\begin{verbatim}database in /nfs/cleo3/database/data$env(USER_DB)/db event \
\end{verbatim}\begin{verbatim}                                         startrun beginrun endrun
\end{verbatim}\begin{verbatim}database read_collection rawdata
\end{verbatim}\begin{verbatim}database run $env(USER_RUN)
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}source_format sel IndexAsciiSourceFormat
\end{verbatim}\begin{verbatim}file in ../idxa/comp$env(USER_RUN).idxa event
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}sink_format sel PDSSinkFormat
\end{verbatim}\begin{verbatim}file out ../rzn3/raw$env(USER_RUN).pds {event{\
\end{verbatim}\begin{verbatim}    DBTrackerValues FATable<TRTrack> FATable<TRHelixPionFit> \
\end{verbatim}\begin{verbatim}    FATable<TRPionQuality> FATable<TRSeedTrack> \
\end{verbatim}\begin{verbatim}    FATable<TRSeedTrackQuality> FATable<CcBasicShowerAttsArg> \
\end{verbatim}\begin{verbatim}    TrackShowerLattice FATable<CcConRegAttributes> \
\end{verbatim}\begin{verbatim}    CcConRegShowerLattice TriggerL1Data Level3TagWord \
\end{verbatim}\begin{verbatim}    Level4Decision EventProperties DBEventHeader\
\end{verbatim}\begin{verbatim}}} startrun beginrun endrun
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}go
\end{verbatim}\begin{verbatim}exit
\end{verbatim}
