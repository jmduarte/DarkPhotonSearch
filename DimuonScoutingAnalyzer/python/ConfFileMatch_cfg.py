import FWCore.ParameterSet.Config as cms

process = cms.Process("Demo")

process.load("FWCore.MessageService.MessageLogger_cfi")
process.MessageLogger.cerr.FwkReport.reportEvery = 1000

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(10000) )

process.source = cms.Source("PoolSource",
                            fileNames = cms.untracked.vstring('root://cmsxrootd.fnal.gov//store/data/Run2018A/SingleMuon/MINIAOD/PromptReco-v1/000/315/252/00000/A4345B88-404B-E811-894C-FA163EECC2C3.root',)
                            )

process.TFileService = cms.Service("TFileService",
                                   fileName = cms.string('AnalysisOutputMatch.root'),
 #                                  closeFileFast = cms.untracked.bool(True)
)

process.demo = cms.EDAnalyzer('HTScoutingJetMatchAnalyzer',
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
     triggerObjectsStandAlone = cms.InputTag("slimmedPatTrigger","RECO")
)


process.p = cms.Path(process.demo)
