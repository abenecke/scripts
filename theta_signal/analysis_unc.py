model = build_model_from_rootfile('/nfs/dust/cms/user/abenecke/ZPrimeTotTPrime/CMSSW_8X/rootfiles/uncertainties/theta_histograms_MZPrime.root',include_mc_uncertainties = True)
model.fill_histogram_zerobins()
model.set_signal_processes('MC_ZPrime*')
for p in model.processes:
    model.add_lognormal_uncertainty('lumi', math.log(1.026), p)
    model.add_lognormal_uncertainty('wj_rate', math.log(1.5), 'WJets')
    model.add_lognormal_uncertainty('zj_rate', math.log(1.5), 'DYJetsToLL')
    model.add_lognormal_uncertainty('ttbar_rate', math.log(1.5), 'TTbar')
    model.add_lognormal_uncertainty('qcd_rate', math.log(2.0), 'QCD')
    model.add_lognormal_uncertainty('st_rate', math.log(1.5), 'ST')

#results = bayesian_limits(model, 'all', n_toy = 2500, n_data = 201)
results = bayesian_limits(model, 'all', n_toy = 2500)
#expected, observed = results
model_summary(model)

#options = Options()
#options.set('minimizer', 'strategy', 'newton_vanilla')

#execfile("postfit-uncertainties.py")
#ps, C = postfit_rate_uncertainties(model, options=options)

#total = 0

#print result
print 'writing results to html file...'
report.write_html('')
