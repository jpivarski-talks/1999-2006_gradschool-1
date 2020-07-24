execfile("utilities.py")

mc1 = {}
mc1["ggg"] = getmc(1, "ggg")
mc1["gggam"] = getmc(1, "gggam")
mc1["qq"] = getmc(1, "qq")
mc1["ee0"] = getmc(1, "ee0")
mc1["ee"] = getmc(1, "ee")
mc1["mumu0"] = getmc(1, "mumu0")
mc1["mumu"] = getmc(1, "mumu")
mc1["tautau"] = getmc(1, "tautau")

mc2 = {}
mc2["ggg"] = getmc(2, "ggg")
mc2["gggam"] = getmc(2, "gggam")
mc2["qq"] = getmc(2, "qq")
mc2["ee0"] = getmc(2, "ee0")
mc2["ee"] = getmc(2, "ee")
mc2["mumu0"] = getmc(2, "mumu0")
mc2["mumu"] = getmc(2, "mumu")
mc2["tautau"] = getmc(2, "tautau")
mc2["cas"] = getmc(2, "cas")
mc2["casll0"] = getmc(2, "casll0")
mc2["casll"] = getmc(2, "casll")

mc3 = {}
mc3["ggg"] = getmc(3, "ggg")
mc3["gggam"] = getmc(3, "gggam")
mc3["qq"] = getmc(3, "qq")
mc3["ee0"] = getmc(3, "ee0")
mc3["ee"] = getmc(3, "ee")
mc3["mumu0"] = getmc(3, "mumu0")
mc3["mumu"] = getmc(3, "mumu")
mc3["tautau"] = getmc(3, "tautau")
mc3["cas"] = getmc(3, "cas")
mc3["casll0"] = getmc(3, "casll0")
mc3["casll"] = getmc(3, "casll")

mc1all = domc1()
mc2all = domc2()
mc3all = domc3()

mc1all_nolep = domc1(False)
mc2all_nolep = domc2(False)
mc3all_nolep = domc3(False)

print mc1all_nolep.hadron_r_trignum.sum(0.5,7.5) / mc1all_nolep.hadron_r_trignum.sum(-0.5,7.5)
print mc2all_nolep.hadron_r_trignum.sum(0.5,7.5) / mc2all_nolep.hadron_r_trignum.sum(-0.5,7.5)
print mc3all_nolep.hadron_r_trignum.sum(0.5,7.5) / mc3all_nolep.hadron_r_trignum.sum(-0.5,7.5)
