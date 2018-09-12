import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

#process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
 #   fileNames = cms.untracked.vstring(
#        'file:/eos/user/a/amarini/ZeroBiasScouting_Run2017_v2/JetHT/JetHT_1/170624_222405/0000/outputScoutingCalo_9.root',
  #  )
#)


import FWCore.Utilities.FileUtils as FileUtils
mylist = FileUtils.loadListFromFile ('infile5.txt') 
readFiles = cms.untracked.vstring( *mylist)

myParentlist = FileUtils.loadListFromFile ('infile5_parent.txt')
readParentFiles = cms.untracked.vstring( *myParentlist)

process.source = cms.Source('PoolSource', 
                            fileNames = readFiles,
                            secondaryFileNames = readParentFiles)

import FWCore.PythonUtilities.LumiList as LumiList
process.source.lumisToProcess = LumiList.LumiList(filename = 'json_DCSONLY.txt').getVLuminosityBlockRange()

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('AnalysisOutput.root'),
 #                                  closeFileFast = cms.untracked.bool(True)
)

## process.demo = cms.EDAnalyzer('DimuonScoutingAnalyzer',
##      triggerResults  = cms.InputTag("TriggerResults", "", "TEST"),
##      muons           = cms.InputTag("hltScoutingMuonPackerCalo", "", "TEST"),
## )

process.demo = cms.EDAnalyzer('HTScoutingL1Analyzer',
     ## JECs ################
     doJECs          = cms.bool(True),
     L1corrAK4_DATA  = cms.FileInPath('DarkPhotonSearch/DimuonScoutingAnalyzer/data/92X_dataRun2_HLT_v7/92X_dataRun2_HLT_v7_L1FastJet_AK4CaloHLT.txt'),
     L2corrAK4_DATA  = cms.FileInPath('DarkPhotonSearch/DimuonScoutingAnalyzer/data/92X_dataRun2_HLT_v7/92X_dataRun2_HLT_v7_L2Relative_AK4CaloHLT.txt'),
     L3corrAK4_DATA  = cms.FileInPath('DarkPhotonSearch/DimuonScoutingAnalyzer/data/92X_dataRun2_HLT_v7/92X_dataRun2_HLT_v7_L3Absolute_AK4CaloHLT.txt'),
     triggerResults  = cms.InputTag("TriggerResults", "", "HLT"),
     caloJets        = cms.InputTag("hltScoutingCaloPacker", "", "HLT"),
     caloRho         = cms.InputTag("hltScoutingCaloPacker", "rho", "HLT"),
     pfJets          = cms.InputTag("hltScoutingPFPacker", "", "HLT"),
     recoJets        = cms.InputTag("slimmedJets", "", "RECO"),
     muons           = cms.InputTag("hltScoutingMuonPacker", "", "HLT"),
)


process.p = cms.Path(process.demo)
