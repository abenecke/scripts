model = build_model_from_rootfile('/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/25ns/rootfile/thesis/theta_histograms_MZPrime.root',include_mc_uncertainties = True)
model.fill_histogram_zerobins()
model.set_signal_processes('MC_ZPrime*')
model.add_lognormal_uncertainty('wj_rate', math.log(1.019), 'WJets')
model.add_lognormal_uncertainty('zj_rate', math.log(1.5), 'DYJetsToLL')
model.add_lognormal_uncertainty('ttbar_rate', math.log(1.019), 'TTbar')
model.add_lognormal_uncertainty('qcd_rate', math.log(2.0), 'QCD')
model.add_lognormal_uncertainty('st_rate', math.log(1.5), 'ST')

results = bayesian_limits(model, 'all')
model_summary(model)
#print result
print 'writing results to html file...'
report.write_html('')
