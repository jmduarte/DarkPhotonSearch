# Instructions to run Scouting DQM
```bash
cmsrel CMSSW_9_2_7_patch1
cd CMSSW_9_2_7_patch1/src/
# install CMSSW area a la https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGlobalHLT#Running_the_HLT_with_CMSSW_9_2_0
git clone git@github.com:jmduarte/DarkPhotonSearch
scram b -j 6

# to get the name of a data file for testing
das_client.py --query="file run=299443 dataset=/ParkingHLTPhysics1/Run2017C-v1/RAW" --limit 0

# I created a ConfDB area called /users/woodson/ScoutingDQM_926 which is just the ParkingMonitoringStream (but removing the Smart Prescale module)

hltGetConfiguration /users/woodson/ScoutingDQM_926 --full --offline --data --prescale 2.0e34 --process TEST --globaltag auto:run2_hlt_GRun --input root://xrootd-cms.infn.it//store/data/Run2017C/ParkingHLTPhysics1/RAW/v1/000/299/443/00000/004849F9-E26C-E711-9EAD-02163E014252.root --max-events 100 --setup /dev/CMSSW_9_2_0/GRun > hlt.py
cp setup_dev_CMSSW_9_2_0_GRun_cff.py ../../Configuration/python/
# replace process.load("setup_dev_CMSSW_9_2_0_GRun_cff") with process.load("HLTrigger.Configuration.setup_dev_CMSSW_9_2_0_GRun_cff") in hlt.py
# comment out these lines in hlt.py (otherwise crab jobs will not submit because they will look for this output file)
#
# process.dqmOutput = cms.OutputModule("DQMRootOutputModule",                                                                                                                           
#    fileName = cms.untracked.string("DQMIO.root")                                                                                                                                     
# )                                                                                                                                                                                     
#                                                                                                                                                                                      
# process.DQMOutput = cms.EndPath( process.dqmOutput )       
#
# run cmsRun hlt.py locally to make sure it works

voms-proxy-init --voms cms
source /cvmfs/cms.cern.ch/crab3/crab.sh

# submit SingleMuon Run2017B and Run2017C using python script
python multicrab_data.py

# once your crab jobs finish get the list of output files and put them in infile3.txt then you can do
cd $CMSSW_BASE/src/DarkPhotonSearch/DimuonScoutingAnalyzer/python
cmsRun ConfFile_cfg.py
# then you can plot the HT or mjj turn-on
cd $CMSSW_BASE/src/DarkPhotonSearch/DimuonScoutingAnalyzer/test
python plotTurnOn.py -i AnalysisOutput.root --numerator demo/histoDir/HT_nominal_monitoring --denominator demo/histoDir/HT_monitoring --lumi 5.8
python plotTurnOn.py -i AnalysisOutput.root --numerator demo/histoDir/mjj_nominal_monitoring --denominator demo/histoDir/mjj_monitoring --lumi 5.8
```
