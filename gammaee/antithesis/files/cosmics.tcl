\begin{verbatim}
default prompt off
\end{verbatim}\begin{verbatim}exception continueEventLoop on
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}module select LoadGeantModule
\end{verbatim}\begin{verbatim}module select LoadHbookModule
\end{verbatim}\begin{verbatim}module sel HbookHistogramModule
\end{verbatim}\begin{verbatim}hbook file ../../rzn/test_cosmics1.rzn
\end{verbatim}\begin{verbatim}hbook init
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}run_file $env(C3_SCRIPTS)/getConstants.tcl
\end{verbatim}\begin{verbatim}run_file $env(C3_SCRIPTS)/trackingDataFull.tcl
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}run_file $env(C3_SCRIPTS)/C3cc.tcl
\end{verbatim}\begin{verbatim}prod sel CcfcReconProd
\end{verbatim}\begin{verbatim}prod sel TrackShowerMatchingProd
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}prod sel MutrReconProd
\end{verbatim}\begin{verbatim}prod sel MuConsProd
\end{verbatim}\begin{verbatim}run_file $env(C3_SCRIPTS)/load_geometry_producers.tcl
\end{verbatim}\begin{verbatim}run_file $env(C3_SCRIPTS)/load_dg_to_geant3_converter.tcl
\end{verbatim}\begin{verbatim}prod sel MagFieldProd
\end{verbatim}\begin{verbatim}prod sel RawDataProd
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}prod sel DBEventHeaderProd
\end{verbatim}\begin{verbatim}prod sel CesrBeamEnergyProd
\end{verbatim}\begin{verbatim}prod sel EventPropertiesProd
\end{verbatim}\begin{verbatim}prod sel EventTypeProd
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}source_format sel BinarySourceFormat
\end{verbatim}\begin{verbatim}file in /cdat/sol191/disk1/cleo3/data/r[RUN NUMBER].bin event \
\end{verbatim}\begin{verbatim}                                           startrun beginrun endrun
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}proc sel ../../build_SunOS/shlib/BigNTuple2
\end{verbatim}\begin{verbatim}param BigNTuple2 getBunchData false
\end{verbatim}\begin{verbatim}param BigNTuple2 interestingOnly true
\end{verbatim}\begin{verbatim}# This applies a cut on the number of tracks: all events in the
\end{verbatim}\begin{verbatim}# no-beam sample must, because of this cut, have more than zero
\end{verbatim}\begin{verbatim}# tracks.  This could, in principle, bias the measurement of how many
\end{verbatim}\begin{verbatim}# cosmic rays survive hadron cuts, because the hadron event selection
\end{verbatim}\begin{verbatim}# doesn't have such a cut.  However, the statistical error on that
\end{verbatim}\begin{verbatim}# measurement is 7%, and for such a cosmic ray to survive hadron cuts,
\end{verbatim}\begin{verbatim}# it must have 4 GeV in calorimeter energy, which no pair of muon
\end{verbatim}\begin{verbatim}# showers can provide.
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}sink_format sel PDSSinkFormat
\end{verbatim}\begin{verbatim}file sink $env(USER_TMP)/gencos[RUN NUMBER].pds event \
\end{verbatim}\begin{verbatim}                                           startrun beginrun endrun
\end{verbatim}\begin{verbatim}
\end{verbatim}\begin{verbatim}go
\end{verbatim}\begin{verbatim}exit
\end{verbatim}
