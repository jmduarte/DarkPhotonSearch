import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

#process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
 #   fileNames = cms.untracked.vstring(
#        'file:/eos/user/a/amarini/ZeroBiasScouting_Run2017_v2/JetHT/JetHT_1/170624_222405/0000/outputScoutingCalo_9.root',
  #  )
#)


import FWCore.Utilities.FileUtils as FileUtils
mylist = FileUtils.loadListFromFile ('infile_new.txt') 
readFiles = cms.untracked.vstring( *mylist)

myParentlist = FileUtils.loadListFromFile ('infile_new_parent.txt')
readParentFiles = cms.untracked.vstring( *myParentlist)

process.source = cms.Source('PoolSource', 
                            fileNames = readFiles,
                            secondaryFileNames = readParentFiles,
                            skipEvents = cms.untracked.uint32(54)
                            )

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
     ## JECs for Calo ################
     doJECsCalo          = cms.bool(True),
     L1corrAK4Calo_DATA  = cms.FileInPath('DarkPhotonSearch/DimuonScoutingAnalyzer/data/102X_dataRun2_HLT_v2/102X_dataRun2_HLT_v2_L1FastJet_AK4CaloHLT.txt'),
     L2corrAK4Calo_DATA  = cms.FileInPath('DarkPhotonSearch/DimuonScoutingAnalyzer/data/102X_dataRun2_HLT_v2/102X_dataRun2_HLT_v2_L2Relative_AK4CaloHLT.txt'),
     L3corrAK4Calo_DATA  = cms.FileInPath('DarkPhotonSearch/DimuonScoutingAnalyzer/data/102X_dataRun2_HLT_v2/102X_dataRun2_HLT_v2_L3Absolute_AK4CaloHLT.txt'),
     ## JECs for PF ################
     doJECsPF          = cms.bool(True),
     L1corrAK4PF_DATA  = cms.FileInPath('DarkPhotonSearch/DimuonScoutingAnalyzer/data/102X_dataRun2_HLT_v2/102X_dataRun2_HLT_v2_L1FastJet_AK4PFHLT.txt'),
     L2corrAK4PF_DATA  = cms.FileInPath('DarkPhotonSearch/DimuonScoutingAnalyzer/data/102X_dataRun2_HLT_v2/102X_dataRun2_HLT_v2_L2Relative_AK4PFHLT.txt'),
     L3corrAK4PF_DATA  = cms.FileInPath('DarkPhotonSearch/DimuonScoutingAnalyzer/data/102X_dataRun2_HLT_v2/102X_dataRun2_HLT_v2_L3Absolute_AK4PFHLT.txt'),
     triggerResults  = cms.InputTag("TriggerResults", "", "HLT"),
     caloJets        = cms.InputTag("hltScoutingCaloPacker", "", "HLT"),
     caloRho         = cms.InputTag("hltScoutingCaloPacker", "rho", "HLT"),
     pfJets          = cms.InputTag("hltScoutingPFPacker", "", "HLT"),
     pfRho           = cms.InputTag("hltScoutingPFPacker", "rho", "HLT"),
     recoJets        = cms.InputTag("slimmedJets", "", "RECO"),
     muons           = cms.InputTag("hltScoutingMuonPacker", "", "HLT"),
)


process.p = cms.Path(process.demo)
