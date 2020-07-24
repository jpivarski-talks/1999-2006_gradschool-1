#
# load_geometry_producers.tcl
#
# 02/20/01  modified by Vladimir Savinov
#
#####################################################################
#
# Use:
#   load special geometry and geometry producers necessary for 
#   generating CLEO III geometry in GEANT3 format needed by 
#   muon reconstruction. You will also need to load Geant3MaterialsMediaProd
#   (see load_dg_to_geant3_converter.tcl)
#
#   It is assumed that run_file $env(C3_SCRIPTS)/getConstants.tcl
#   has been already executed
#
#####################################################################

#  Detector Geometry producers - passive and active
prod sel ASiStorePro
prod sel IRGeomProd
prod sel SiGeom
prod sel DRGeom
prod sel CoilGeomProd
prod sel DRWireLayerProd
prod sel ADRGeomProd
prod sel CcGeomProd
prod sel RichGeom
prod sel MUGeomProd


