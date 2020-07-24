def get_overunderflow_right(bins, low, high, values):
  tmp = hist.h1(bins, low, high, vals=values[1])
  tmp.underflow = values[0]
  tmp.overflow = values[2]
  return tmp

def histogramize(comb):
  comb.mt_all = get_overunderflow_right(100, 0., 1., comb.t_all).rootn()
  comb.mT_all = get_overunderflow_right(100, 0., 1., comb.T_all).rootn()
  comb.mh_had_trig = get_overunderflow_right(8, -0.5, 7.5, comb.h_had_trig).rootn()
  comb.mh_had_d0close1 = get_overunderflow_right(120, -0.06, 0.06, comb.h_had_d0close1).rootn()
  comb.mh_had_d0close2 = get_overunderflow_right(140, -7., 0., comb.h_had_d0close2).rootn()
  comb.mh_had_p2 = get_overunderflow_right(120, 0., 1.2, comb.h_had_p2).rootn()
  comb.mh_had_wz1 = get_overunderflow_right(100, -0.10, 0.10, comb.h_had_wz1).rootn()
  comb.mh_had_wz2 = get_overunderflow_right(120, -6., 0., comb.h_had_wz2).rootn()
  comb.mh_had_z0close1 = get_overunderflow_right(100, -0.10, 0.10, comb.h_had_z0close1).rootn()
  comb.mh_had_z0close2 = get_overunderflow_right(120, -6., 0., comb.h_had_z0close2).rootn()
  comb.mh_had_visen = get_overunderflow_right(120, 0., 1.2, comb.h_had_visen).rootn()
  comb.mH_had_trig = get_overunderflow_right(8, -0.5, 7.5, comb.H_had_trig).rootn()
  comb.mH_had_d0close1 = get_overunderflow_right(120, -0.06, 0.06, comb.H_had_d0close1).rootn()
  comb.mH_had_d0close2 = get_overunderflow_right(120, -6., 0., comb.H_had_d0close2).rootn()
  comb.mH_had_p2 = get_overunderflow_right(120, 0., 1.2, comb.H_had_p2).rootn()
  comb.mH_had_wz1 = get_overunderflow_right(100, -0.10, 0.10, comb.H_had_wz1).rootn()
  comb.mH_had_wz2 = get_overunderflow_right(120, -6., 0., comb.H_had_wz2).rootn()
  comb.mH_had_z0close1 = get_overunderflow_right(100, -0.10, 0.10, comb.H_had_z0close1).rootn()
  comb.mH_had_z0close2 = get_overunderflow_right(120, -6., 0., comb.H_had_z0close2).rootn()
  comb.mH_had_visen = get_overunderflow_right(120, 0., 1.2, comb.H_had_visen).rootn()
  comb.mh_had_ntracks = get_overunderflow_right(19, -0.5, 18.5, comb.h_had_ntracks).rootn()
  comb.mh_had_coolvisen = get_overunderflow_right(120, 0., 1.2, comb.h_had_coolvisen).rootn()
  comb.mh_had_coolvisen_nol4dec = get_overunderflow_right(120, 0., 1.2, comb.h_had_coolvisen_nol4dec).rootn()
  comb.mt_had = get_overunderflow_right(100, 0., 1., comb.t_had).rootn()
  comb.mT_had = get_overunderflow_right(100, 0., 1., comb.T_had).rootn()
  comb.mh_gam_e2 = get_overunderflow_right(120, 0., 1.2, comb.h_gam_e2).rootn()
  comb.mh_gam_ntracks = get_overunderflow_right(5, -0.5, 4.5, comb.h_gam_ntracks).rootn()
  comb.mh_gam_zback = get_overunderflow_right(9, -4.5, 4.5, comb.h_gam_zback).rootn()
  comb.mh_gam_z1 = get_overunderflow_right(48, -24., 24., comb.h_gam_z1).rootn()
  comb.mh_gam_z2 = get_overunderflow_right(48, -24., 24., comb.h_gam_z2).rootn()
  comb.mh_gam_z1_noexclude = get_overunderflow_right(48, -24., 24., comb.h_gam_z1_noexclude).rootn()
  comb.mh_gam_z2_noexclude = get_overunderflow_right(48, -24., 24., comb.h_gam_z2_noexclude).rootn()
  comb.mh_gam_phiback = get_overunderflow_right(11, -5.5, 5.5, comb.h_gam_phiback).rootn()
  comb.mh_gam_phiback_notracks = get_overunderflow_right(11, -5.5, 5.5, comb.h_gam_phiback_notracks).rootn()
  comb.mh_gam_trigcorrect = get_overunderflow_right(130, 0., 1.3, comb.h_gam_trigcorrect).rootn()
  comb.mh_gam_e3in = get_overunderflow_right(125, 0.060, 0.185, comb.h_gam_e3in).rootn()
  comb.mh_gam_e3out = get_overunderflow_right(125, 0.060, 0.185, comb.h_gam_e3out).rootn()
  comb.mt_gam = get_overunderflow_right(100, 0., 1., comb.t_gam).rootn()
  comb.mT_gam = get_overunderflow_right(100, 0., 1., comb.T_gam).rootn()
  comb.mh_tkl_e2 = get_overunderflow_right(120, 0., 1.2, comb.h_tkl_e2).rootn()
  comb.mh_tkl_ntracks = get_overunderflow_right(5, -0.5, 4.5, comb.h_tkl_ntracks).rootn()
  comb.mh_tkl_zback = get_overunderflow_right(9, -4.5, 4.5, comb.h_tkl_zback).rootn()
  comb.mh_tkl_z1 = get_overunderflow_right(48, -24., 24., comb.h_tkl_z1).rootn()
  comb.mh_tkl_z2 = get_overunderflow_right(48, -24., 24., comb.h_tkl_z2).rootn()
  comb.mh_tkl_z1_noexclude = get_overunderflow_right(48, -24., 24., comb.h_tkl_z1_noexclude).rootn()
  comb.mh_tkl_z2_noexclude = get_overunderflow_right(48, -24., 24., comb.h_tkl_z2_noexclude).rootn()
  comb.mh_tkl_phiback = get_overunderflow_right(11, -5.5, 5.5, comb.h_tkl_phiback).rootn()
  comb.mh_tkl_phiback_notrackcut = get_overunderflow_right(11, -5.5, 5.5, comb.h_tkl_phiback_notrackcut).rootn()
  comb.mt_tkl = get_overunderflow_right(100, 0., 1., comb.t_tkl).rootn()
  comb.mt_tkl_nontracks = get_overunderflow_right(100, 0., 1., comb.t_tkl_nontracks).rootn()
  comb.mt_tkl_eltrack = get_overunderflow_right(100, 0., 1., comb.t_tkl_eltrack).rootn()
  comb.mT_tkl = get_overunderflow_right(100, 0., 1., comb.T_tkl).rootn()
  comb.mT_tkl_nontracks = get_overunderflow_right(100, 0., 1., comb.T_tkl_nontracks).rootn()
  comb.mT_tkl_eltrack = get_overunderflow_right(100, 0., 1., comb.T_tkl_eltrack).rootn()
  comb.mh_bha_trig = get_overunderflow_right(4, -0.5, 3.5, comb.h_bha_trig).rootn()
  comb.mh_bha_p2 = get_overunderflow_right(120, 0., 1.2, comb.h_bha_p2).rootn()
  comb.mh_bha_d0close1 = get_overunderflow_right(120, -0.06, 0.06, comb.h_bha_d0close1).rootn()
  comb.mh_bha_d0close2 = get_overunderflow_right(140, -7., 0., comb.h_bha_d0close2).rootn()
  comb.mh_bha_wz1 = get_overunderflow_right(100, -0.10, 0.10, comb.h_bha_wz1).rootn()
  comb.mh_bha_wz2 = get_overunderflow_right(120, -6., 0., comb.h_bha_wz2).rootn()
  comb.mh_bha_z0close1 = get_overunderflow_right(100, -0.10, 0.10, comb.h_bha_z0close1).rootn()
  comb.mh_bha_z0close2 = get_overunderflow_right(120, -6., 0., comb.h_bha_z0close2).rootn()
  comb.mh_bha_eisr = get_overunderflow_right(100, 0., 1., comb.h_bha_eisr).rootn()
  comb.mh_bha_econstraint = get_overunderflow_right(100, 0., 1., comb.h_bha_econstraint).rootn()
  comb.mh_bha_costheta1 = get_overunderflow_right(100, -1., 1., comb.h_bha_costheta1).rootn()
  comb.mh_bha_costheta2 = get_overunderflow_right(100, -1., 1., comb.h_bha_costheta2).rootn()
  comb.mh_bha_e2 = get_overunderflow_right(120, 0., 1.2, comb.h_bha_e2).rootn()
  comb.mh_bha_trignumer = get_overunderflow_right(130, 0., 1.3, comb.h_bha_trignumer).rootn()
  comb.mh_bha_trigdenom = get_overunderflow_right(130, 0., 1.3, comb.h_bha_trigdenom).rootn()
  comb.mh_bha_trignumer_showergeometry = get_overunderflow_right(130, 0., 1.3, comb.h_bha_trignumer_showergeometry).rootn()
  comb.mh_bha_trigdenom_showergeometry = get_overunderflow_right(130, 0., 1.3, comb.h_bha_trigdenom_showergeometry).rootn()
  comb.mh_bha_trignumer_showergeometry2 = get_overunderflow_right(130, 0., 1.3, comb.h_bha_trignumer_showergeometry2).rootn()
  comb.mh_bha_trigdenom_showergeometry2 = get_overunderflow_right(130, 0., 1.3, comb.h_bha_trigdenom_showergeometry2).rootn()
  comb.mh_bha_trignumer_excludeblocks = get_overunderflow_right(130, 0., 1.3, comb.h_bha_trignumer_excludeblocks).rootn()
  comb.mh_bha_trigdenom_excludeblocks = get_overunderflow_right(130, 0., 1.3, comb.h_bha_trigdenom_excludeblocks).rootn()
  comb.mh_bha_trignumer_showergeometry_excludeblocks = get_overunderflow_right(130, 0., 1.3, comb.h_bha_trignumer_showergeometry_excludeblocks).rootn()
  comb.mh_bha_trigdenom_showergeometry_excludeblocks = get_overunderflow_right(130, 0., 1.3, comb.h_bha_trigdenom_showergeometry_excludeblocks).rootn()
  comb.mh_bha_trignumer_showergeometry2_excludeblocks = get_overunderflow_right(130, 0., 1.3, comb.h_bha_trignumer_showergeometry2_excludeblocks).rootn()
  comb.mh_bha_trigdenom_showergeometry2_excludeblocks = get_overunderflow_right(130, 0., 1.3, comb.h_bha_trigdenom_showergeometry2_excludeblocks).rootn()
  comb.mt_bha = get_overunderflow_right(100, 0., 1., comb.t_bha).rootn()
  comb.mT_bha = get_overunderflow_right(100, 0., 1., comb.T_bha).rootn()
  comb.mh_mup_trig = get_overunderflow_right(4, -0.5, 3.5, comb.h_mup_trig).rootn()
  comb.mh_mup_p2 = get_overunderflow_right(120, 0., 1.2, comb.h_mup_p2).rootn()
  comb.mh_mup_d0close1 = get_overunderflow_right(120, -0.06, 0.06, comb.h_mup_d0close1).rootn()
  comb.mh_mup_d0close2 = get_overunderflow_right(140, -7., 0., comb.h_mup_d0close2).rootn()
  comb.mh_mup_wz1 = get_overunderflow_right(100, -0.10, 0.10, comb.h_mup_wz1).rootn()
  comb.mh_mup_wz2 = get_overunderflow_right(120, -6., 0., comb.h_mup_wz2).rootn()
  comb.mh_mup_z0close1 = get_overunderflow_right(100, -0.10, 0.10, comb.h_mup_z0close1).rootn()
  comb.mh_mup_z0close2 = get_overunderflow_right(120, -6., 0., comb.h_mup_z0close2).rootn()
  comb.mh_mup_eisr = get_overunderflow_right(100, 0., 1., comb.h_mup_eisr).rootn()
  comb.mh_mup_econstraint = get_overunderflow_right(100, 0., 1., comb.h_mup_econstraint).rootn()
  comb.mh_mup_costheta1 = get_overunderflow_right(100, -1., 1., comb.h_mup_costheta1).rootn()
  comb.mh_mup_costheta2 = get_overunderflow_right(100, -1., 1., comb.h_mup_costheta2).rootn()
  comb.mh_mup_e2 = get_overunderflow_right(120, 0., 6., comb.h_mup_e2).rootn()
  comb.mt_mup = get_overunderflow_right(100, 0., 1., comb.t_mup).rootn()
  comb.mT_mup = get_overunderflow_right(100, 0., 1., comb.T_mup).rootn()
  comb.mh_cos_trig = get_overunderflow_right(8, -0.5, 7.5, comb.h_cos_trig).rootn()
  comb.mh_cos_ntracks = get_overunderflow_right(19, -0.5, 18.5, comb.h_cos_ntracks).rootn()
  comb.mh_cos_d0close1 = get_overunderflow_right(120, -0.06, 0.06, comb.h_cos_d0close1).rootn()
  comb.mh_cos_d0close2 = get_overunderflow_right(140, -7., 0., comb.h_cos_d0close2).rootn()
  comb.mh_cos_pdotp1 = get_overunderflow_right(100, -1., 1., comb.h_cos_pdotp1).rootn()
  comb.mh_cos_pdotp2 = get_overunderflow_right(100, -10., 0., comb.h_cos_pdotp2).rootn()
  comb.mh_cos_ccen = get_overunderflow_right(120, 0., 1.2, comb.h_cos_ccen).rootn()
  comb.mt_cos = get_overunderflow_right(100, 0., 1., comb.t_cos).rootn()
  comb.mT_cos = get_overunderflow_right(100, 0., 1., comb.T_cos).rootn()
  comb.mh_cos_visen = get_overunderflow_right(120, 0., 1.2, comb.h_cos_visen).rootn()
  comb.mh_bge_trig = get_overunderflow_right(8, -0.5, 7.5, comb.h_bge_trig).rootn()
  comb.mh_bge_ntracks = get_overunderflow_right(19, -0.5, 18.5, comb.h_bge_ntracks).rootn()
  comb.mh_bge_d0close1 = get_overunderflow_right(120, -0.06, 0.06, comb.h_bge_d0close1).rootn()
  comb.mh_bge_d0close2 = get_overunderflow_right(140, -7., 0., comb.h_bge_d0close2).rootn()
  comb.mh_bge_wz1 = get_overunderflow_right(100, -0.50, 0.50, comb.h_bge_wz1).rootn()
  comb.mh_bge_wz2 = get_overunderflow_right(120, -6., 0., comb.h_bge_wz2).rootn()
  comb.mh_bge_z0close1 = get_overunderflow_right(100, -0.10, 0.10, comb.h_bge_z0close1).rootn()
  comb.mh_bge_z0close2 = get_overunderflow_right(120, -6., 0., comb.h_bge_z0close2).rootn()
  comb.mh_bge_pdotp1 = get_overunderflow_right(100, -1., 1., comb.h_bge_pdotp1).rootn()
  comb.mh_bge_pdotp2 = get_overunderflow_right(100, -10., 0., comb.h_bge_pdotp2).rootn()
  comb.mh_bge_wpz = get_overunderflow_right(100, -1., 1., comb.h_bge_wpz).rootn()
  comb.mt_bge = get_overunderflow_right(100, 0., 1., comb.t_bge).rootn()
  comb.mT_bge = get_overunderflow_right(100, 0., 1., comb.T_bge).rootn()
  comb.mh_bge_visen = get_overunderflow_right(120, 0., 1.2, comb.h_bge_visen).rootn()
  comb.mh_bgp_trig = get_overunderflow_right(8, -0.5, 7.5, comb.h_bgp_trig).rootn()
  comb.mh_bgp_ntracks = get_overunderflow_right(19, -0.5, 18.5, comb.h_bgp_ntracks).rootn()
  comb.mh_bgp_d0close1 = get_overunderflow_right(120, -0.06, 0.06, comb.h_bgp_d0close1).rootn()
  comb.mh_bgp_d0close2 = get_overunderflow_right(140, -7., 0., comb.h_bgp_d0close2).rootn()
  comb.mh_bgp_wz1 = get_overunderflow_right(100, -0.50, 0.50, comb.h_bgp_wz1).rootn()
  comb.mh_bgp_wz2 = get_overunderflow_right(120, -6., 0., comb.h_bgp_wz2).rootn()
  comb.mh_bgp_z0close1 = get_overunderflow_right(100, -0.10, 0.10, comb.h_bgp_z0close1).rootn()
  comb.mh_bgp_z0close2 = get_overunderflow_right(120, -6., 0., comb.h_bgp_z0close2).rootn()
  comb.mh_bgp_pdotp1 = get_overunderflow_right(100, -1., 1., comb.h_bgp_pdotp1).rootn()
  comb.mh_bgp_pdotp2 = get_overunderflow_right(100, -10., 0., comb.h_bgp_pdotp2).rootn()
  comb.mh_bgp_wpz = get_overunderflow_right(100, -1., 1., comb.h_bgp_wpz).rootn()
  comb.mt_bgp = get_overunderflow_right(100, 0., 1., comb.t_bgp).rootn()
  comb.mT_bgp = get_overunderflow_right(100, 0., 1., comb.T_bgp).rootn()
  comb.mh_bgp_visen = get_overunderflow_right(120, 0., 1.2, comb.h_bgp_visen).rootn()
  comb.mh_ccs_d0close1 = get_overunderflow_right(120, -0.06, 0.06, comb.h_ccs_d0close1).rootn()
  comb.mh_ccs_d0close2 = get_overunderflow_right(140, -7., 0., comb.h_ccs_d0close2).rootn()
  comb.mh_ccs_p2 = get_overunderflow_right(120, 0., 1.2, comb.h_ccs_p2).rootn()
  comb.mh_ccs_wz1 = get_overunderflow_right(100, -0.10, 0.10, comb.h_ccs_wz1).rootn()
  comb.mh_ccs_wz2 = get_overunderflow_right(120, -6., 0., comb.h_ccs_wz2).rootn()
  comb.mh_ccs_z0close1 = get_overunderflow_right(100, -0.10, 0.10, comb.h_ccs_z0close1).rootn()
  comb.mh_ccs_z0close2 = get_overunderflow_right(120, -6., 0., comb.h_ccs_z0close2).rootn()
  comb.mh_ccs_ntracks = get_overunderflow_right(19, -0.5, 18.5, comb.h_ccs_ntracks).rootn()
  comb.mh_ccs_chen = get_overunderflow_right(120, 0., 1.2, comb.h_ccs_chen).rootn()
  comb.mh_ccs_hadtrig = get_overunderflow_right(8, -0.5, 7.5, comb.h_ccs_hadtrig).rootn()
  comb.mh_ccs_e1 = get_overunderflow_right(80, 0., 4., comb.h_ccs_e1).rootn()
  comb.mh_ccs_e2 = get_overunderflow_right(80, 0., 4., comb.h_ccs_e2).rootn()
  comb.mh_ncs_hadtrig = get_overunderflow_right(8, -0.5, 7.5, comb.h_ncs_hadtrig).rootn()
  comb.mh_ncs_e1 = get_overunderflow_right(80, 0., 4., comb.h_ncs_e1).rootn()
  comb.mh_ncs_e2 = get_overunderflow_right(80, 0., 4., comb.h_ncs_e2).rootn()
  comb.mt_ccs = get_overunderflow_right(100, 0., 1., comb.t_ccs).rootn()
  comb.mt_ncs = get_overunderflow_right(100, 0., 1., comb.t_ncs).rootn()
  comb.mT_ccs = get_overunderflow_right(100, 0., 1., comb.T_ccs).rootn()
  comb.mT_ncs = get_overunderflow_right(100, 0., 1., comb.T_ncs).rootn()