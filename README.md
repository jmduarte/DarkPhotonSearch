# Instructions to run Scouting DQM
```bash
# install CMSSW area a la https://twiki.cern.ch/twiki/bin/view/CMSPublic/SWGuideGlobalHLT#Running_the_HLT_with_CMSSW_9_2_0
cmsrel CMSSW_9_2_8
cd CMSSW_9_2_8/src
cmsenv
git cms-init

git remote add cms-l1t-offline git@github.com:cms-l1t-offline/cmssw.git
git fetch cms-l1t-offline
git cms-merge-topic -u cms-l1t-offline:l1t-integration-v96.26.1-CMSSW_9_2_8
git cms-addpkg L1Trigger/L1TCommon
git cms-addpkg L1Trigger/L1TMuon
git clone https://github.com/cms-l1t-offline/L1Trigger-L1TMuon.git L1Trigger/L1TMuon/data

git cms-addpkg L1Trigger/L1TGlobal

# L1T 2017 menu 
# to get the updated L1T menu circulated May 17th (L1Menu_Collisions2017_dev_r3)
git clone https://github.com/cms-l1-dpg/2017-pp-menu-dev -b 2017-06-26 ../2017-pp-menu-dev
# alternatively, to checkout the work-in-progress branch (updated without notice!)
# git clone https://github.com/cms-l1-dpg/2017-pp-menu-dev -b work-in-progress ../2017-pp-menu-dev
mkdir -p L1Trigger/L1TGlobal/data/Luminosity/startup
cp ../2017-pp-menu-dev/Apr12/*.xml L1Trigger/L1TGlobal/data/Luminosity/startup/

# HLT
git cms-addpkg HLTrigger/Configuration

git cms-merge-topic -u 20069
git cms-merge-topic -u 20071
git cms-merge-topic -u 20086

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
cp setup_dev_CMSSW_9_2_0_GRun_cff.py ../python/
# replace process.load("setup_dev_CMSSW_9_2_0_GRun_cff") with process.load("HLTrigger.Configuration.setup_dev_CMSSW_9_2_0_GRun_cff") in hlt.py
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
source plotTurnOns.sh
```
