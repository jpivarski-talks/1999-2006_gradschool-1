P[pdg_,
  hTEff_, lTEff_,
  pAnal_, cAnal_, kAnal_, bAnal_,
  pEff_, cEff_, kEff_, bEff_,
  pCosmic_, cCosmic_, kCosmic_
  pBeamgas_, cBeamgas_, bBeamgas_,
  pLumi_, cLumi_,
  pS_, cS_] :=
(
    ((1-pdg)*hTEff + (pdg)*lTEff)
         *
    ((pAnal - pCosmic*kAnal/kCosmic + pBeamgas*bAnal/bBeamgas) -
     (cAnal - cCosmic*kAnal/kCosmic + cBeamgas*bAnal/bBeamgas)*(pLumi/cLumi)*(pS/cS))
         /
    ((pEff - pCosmic*kEff/kCosmic + pBeamgas*bEff/bBeamgas) -
     (cEff - cCosmic*kEff/kCosmic + cBeamgas*bEff/bBeamgas)*(pLumi/cLumi)*(pS/cS))
)

The only serious correlation is pAnal with pEff, and cAnal with cEff.

For the error propogation take Eff to be certain and Anal to have an
error: Sqrt[Anal * (Eff - Anal) / Eff].  This assumes Anal is a subset
of Eff, which is almost true.  This isn't the dominant error
(pLumi/cLumi is), so I only need the right scaling.
