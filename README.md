# Instructions to run Scouting DQM
```bash
# install CMSSW area a la https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGlobalHLT
cmsrel CMSSW_10_1_4
cd CMSSW_10_1_4/src
cmsenv
git cms-init

git remote add cms-l1t-offline git@github.com:cms-l1t-offline/cmssw.git
git fetch cms-l1t-offline

git cms-addpkg L1Trigger/L1TCommon
git cms-addpkg L1Trigger/L1TMuon
git cms-addpkg L1Trigger/L1TGlobal

# HLT
git cms-addpkg HLTrigger/Configuration

# Dependencies and Compilation
git cms-checkdeps -A -a
scram b -j 6
git clone git@github.com:jmduarte/DarkPhotonSearch
scram b -j 6

# to get the name of a data file and parents for testing 
das_client.py --query="file run=300636 dataset=/SingleMuon/Run2017C-PromptReco-v2/MINIAOD" --limit 0
das_client.py --query="parent file=/store/data/Run2017C/SingleMuon/MINIAOD/PromptReco-v2/000/300/636/00000/000111FF-C87D-E711-9853-02163E01207C.root" --limit 0


# I created a ConfDB area called /users/woodson/ScoutingDQM_928 which is just the ParkingMonitoringStream (but removing the Smart Prescale module)
hltGetConfiguration /users/woodson/ScoutingDQM_928 --full --offline --data --prescale 2.0e34 --process TEST --globaltag auto:run2_hlt_GRun --input root://xrootd-cms.infn.it//store/data/Run2017C/SingleMuon/RAW/v1/000/299/368/00000/007D8F18-DB6B-E711-9943-02163E01A2AF.root --max-events 100 --setup /dev/CMSSW_9_2_0/GRun > hlt.py
# confDB menu based on CMSSW_10X
hltGetConfiguration /users/jiajing/ScoutingDQM_101/V1 --full --offline --data --prescale 2.0e34 --process TEST --globaltag auto:run2_hlt_GRun --input root://eoscms//eos/cms//store/data/Run2018A/SingleMuon/MINIAOD/PromptReco-v1/000/315/252/00000/A4345B88-404B-E811-894C-FA163EECC2C3.root --max-events 100 --setup /dev/CMSSW_10_1_0/GRun > hlt101.py
cp setup_dev_CMSSW_9_2_0_GRun_cff.py HLTrigger/Configuration/python/  
cp hlt101.py  DarkPhotonSearch/DimuonScoutingAnalyzer/test/ 
# replace process.load("setup_dev_CMSSW_10_1_0_GRun_cff") with process.load("HLTrigger.Configuration.setup_dev_CMSSW_10_1_0_GRun_cff") in hlt101.py
# remove smart prescaler (already done in latest ConfDB)
# comment out these lines in hlt.py (otherwise crab jobs will not submit because they will look for this output file)
#
# process.dqmOutput = cms.OutputModule("DQMRootOutputModule",                                                                                                                           
#    fileName = cms.untracked.string("DQMIO.root")                                                                                                                                     
# )                                                                                                                                                                                     
#                                                                                                                                                                                      
# process.DQMOutput = cms.EndPath( process.dqmOutput )       
#
# 
# run cmsRun hlt101.py locally to make sure it works
voms-proxy-init --voms cms
cmsRun hlt101.py >& log101 &


voms-proxy-init --voms cms
source /cvmfs/cms.cern.ch/crab3/crab.sh

# if HLT is needed to run ourself,submit SingleMuon Run2017B and Run2017C using python script
# HLT step, run on RAW data
cd $CMSSW_BASE/src/DarkPhotonSearch/DimuonScoutingAnalyzer/test
python multicrab_data.py

# once your crab jobs finish get the list of output files and put them in infile3.txt then you can do
# if HLT is online, run on ParkingScoutingMonotor MINIAOD dataset
cd $CMSSW_BASE/src/DarkPhotonSearch/DimuonScoutingAnalyzer/python

# run locally
cmsRun ConfFile_cfg.py

# run on grid
python multicrab_psm.py


# then you can plot the HT or mjj turn-on
cd $CMSSW_BASE/src/DarkPhotonSearch/DimuonScoutingAnalyzer/test
source plotTurnOns.sh
```
