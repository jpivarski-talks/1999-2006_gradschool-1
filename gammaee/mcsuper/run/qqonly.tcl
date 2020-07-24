set treeMC [list]
set treeMC [concat $treeMC {
	{MCDecayTree Generator}
	MCTriggerPhase \
	MCTrueRfBucket \
	MCBeamParticles
	MCEventVertex
} ]
set treeMC [list $treeMC]
sink rm $env(USER_GEN)
file out $env(USER_GEN) "beginrun {}" "startrun {}" "endrun {}" physics "event $treeMC"
