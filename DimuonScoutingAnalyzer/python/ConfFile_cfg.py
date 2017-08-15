import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(-1) )

#process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
 #   fileNames = cms.untracked.vstring(
#        'file:/eos/user/a/amarini/ZeroBiasScouting_Run2017_v2/JetHT/JetHT_1/170624_222405/0000/outputScoutingCalo_9.root',
  #  )
#)


import FWCore.Utilities.FileUtils as FileUtils
mylist = FileUtils.loadListFromFile ('infile4.txt') 
readFiles = cms.untracked.vstring( *mylist)

process.source = cms.Source('PoolSource', fileNames = readFiles)


process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('AnalysisOutput.root'),
 #                                  closeFileFast = cms.untracked.bool(True)
)

## process.demo = cms.EDAnalyzer('DimuonScoutingAnalyzer',
##      triggerResults  = cms.InputTag("TriggerResults", "", "TEST"),
##      muons           = cms.InputTag("hltScoutingMuonPackerCalo", "", "TEST"),
## )

process.demo = cms.EDAnalyzer('HTScoutingAnalyzer',
     triggerResults  = cms.InputTag("TriggerResults", "", "TEST"),
     caloJets        = cms.InputTag("hltScoutingCaloPacker", "", "TEST"),
     pfJets          = cms.InputTag("hltScoutingPFPacker", "", "TEST"),
     recoJets        = cms.InputTag("slimmedJets", "", "RECO"),
     muons           = cms.InputTag("hltScoutingMuonPacker", "", "TEST"),
)


process.p = cms.Path(process.demo)
