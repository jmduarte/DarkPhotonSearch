// -*- C++ -*-
//
// Package:    Analyzer/HTScoutingL1Analyzer
// Class:      HTScoutingL1Analyzer
// 
/**\class HTScoutingL1Analyzer HTScoutingL1Analyzer.cc Analyzer/HTScoutingL1Analyzer/plugins/HTScoutingL1Analyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Swagata Mukherjee
//         Created:  Mon, 26 Jun 2017 09:38:37 GMT
//
//


#include <memory>
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "CondFormats/JetMETObjects/interface/JetCorrectorParameters.h"
#include "CondFormats/JetMETObjects/interface/FactorizedJetCorrector.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "FWCore/Framework/interface/one/EDAnalyzer.h"
#include "FWCore/MessageLogger/interface/MessageLogger.h"
#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Common/interface/TriggerNames.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/Scouting/interface/ScoutingMuon.h"
#include "DataFormats/Scouting/interface/ScoutingPFJet.h"
#include "DataFormats/Scouting/interface/ScoutingCaloJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include <TLorentzVector.h>
#include "TTree.h"
#include "TH1.h"


class HTScoutingL1Analyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit HTScoutingL1Analyzer(const edm::ParameterSet&);
      ~HTScoutingL1Analyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

  // ----------member data ---------------------------
  edm::EDGetTokenT<edm::TriggerResults>            trgResultsLabel_;
  edm::EDGetTokenT<ScoutingCaloJetCollection>      caloJetLabel_;
  edm::EDGetTokenT<double>                         caloRhoLabel_;
  edm::EDGetTokenT<ScoutingPFJetCollection>        pfJetLabel_;
  edm::EDGetTokenT<double>                         pfRhoLabel_;
  edm::EDGetTokenT<double>                         pfLabel_;
  edm::EDGetTokenT<pat::JetCollection>             recoJetLabel_;
  edm::EDGetTokenT<ScoutingMuonCollection>         muonLabel_;
  edm::Service<TFileService> fs;

  TTree *tree;

  uint event=0;
  uint run=0;
  uint lumi=0;

  TBranch *br_event;
  TBranch *br_run;
  TBranch *br_lumi;

  int passNominalHT250Trig;
  int passNominalHT410Trig;
  int passMonitoringTrig;
  int passL1MonitoringTrig;
  double caloRho;
  double caloHT;
  double caloMjj;
  double caloDeltaEtajj;
  double caloMjjWide; 
  double caloDeltaEtajjWide;
  double caloDeltaPhijjWide;
  double pfRho;
  double pfHT;
  double pfMjj;
  double pfDeltaEtajj;
  double pfMjjWide; 
  double pfDeltaEtajjWide;
  double pfDeltaPhijjWide;
  double recoHT;
  double recoMjj;
  double recoDeltaEtajj;
  double recoMjjWide; 
  double recoDeltaEtajjWide;
  double recoDeltaPhijjWide;

  TBranch *br_passNominalHT250Trig;
  TBranch *br_passNominalHT410Trig;
  TBranch *br_passMonitoringTrig;
  TBranch *br_passL1MonitoringTrig;
  TBranch *br_caloRho;
  TBranch *br_caloHT;
  TBranch *br_caloMjj;
  TBranch *br_caloDeltaEtajj;
  TBranch *br_caloMjjWide; 
  TBranch *br_caloDeltaEtajjWide;
  TBranch *br_caloDeltaPhijjWide;
  TBranch *br_pfRho;
  TBranch *br_pfHT;
  TBranch *br_pfMjj;
  TBranch *br_pfDeltaEtajj;
  TBranch *br_pfMjjWide; 
  TBranch *br_pfDeltaEtajjWide;
  TBranch *br_pfDeltaPhijjWide;
  TBranch *br_recoHT;
  TBranch *br_recoMjj;
  TBranch *br_recoDeltaEtajj;
  TBranch *br_recoMjjWide; 
  TBranch *br_recoDeltaEtajjWide;
  TBranch *br_recoDeltaPhijjWide;

  TH1F *h1_caloHT_nominalHT250_monitoring;
  TH1F *h1_caloHT_nominalHT410_monitoring;
  TH1F *h1_caloHT_monitoring;
  TH1F *h1_caloHT_nominalHT250;
  TH1F *h1_caloHT_nominalHT410;
  TH1F *h1_caloMjj_nominalHT250_monitoring;
  TH1F *h1_caloMjj_nominalHT410_monitoring;
  TH1F *h1_caloMjj_monitoring;
  TH1F *h1_caloMjj_nominalHT250;
  TH1F *h1_caloMjj_nominalHT410;
  TH1F *h1_caloDeltaEtajj_nominalHT250_monitoring;
  TH1F *h1_caloDeltaEtajj_nominalHT410_monitoring;
  TH1F *h1_caloDeltaEtajj_monitoring;
  TH1F *h1_caloDeltaEtajj_nominalHT250;
  TH1F *h1_caloDeltaEtajj_nominalHT410;
  TH1F *h1_caloMjjWide_nominalHT250_monitoring;
  TH1F *h1_caloMjjWide_nominalHT410_monitoring;
  TH1F *h1_caloMjjWide_monitoring;
  TH1F *h1_caloMjjWide_nominalHT250;
  TH1F *h1_caloMjjWide_nominalHT410;
  TH1F *h1_caloDeltaEtajjWide_nominalHT250_monitoring;
  TH1F *h1_caloDeltaEtajjWide_nominalHT410_monitoring;
  TH1F *h1_caloDeltaEtajjWide_monitoring;
  TH1F *h1_caloDeltaEtajjWide_nominalHT250;
  TH1F *h1_caloDeltaEtajjWide_nominalHT410;

  TH1F *h1_pfHT_nominalHT250_monitoring;
  TH1F *h1_pfHT_nominalHT410_monitoring;
  TH1F *h1_pfHT_monitoring;
  TH1F *h1_pfHT_nominalHT250;
  TH1F *h1_pfHT_nominalHT410;
  TH1F *h1_pfMjj_nominalHT250_monitoring;
  TH1F *h1_pfMjj_nominalHT410_monitoring;
  TH1F *h1_pfMjj_monitoring;
  TH1F *h1_pfMjj_nominalHT250;
  TH1F *h1_pfMjj_nominalHT410;
  TH1F *h1_pfDeltaEtajj_nominalHT250_monitoring;
  TH1F *h1_pfDeltaEtajj_nominalHT410_monitoring;
  TH1F *h1_pfDeltaEtajj_monitoring;
  TH1F *h1_pfDeltaEtajj_nominalHT250;
  TH1F *h1_pfDeltaEtajj_nominalHT410;
  TH1F *h1_pfMjjWide_nominalHT250_monitoring;
  TH1F *h1_pfMjjWide_nominalHT410_monitoring;
  TH1F *h1_pfMjjWide_monitoring;
  TH1F *h1_pfMjjWide_nominalHT250;
  TH1F *h1_pfMjjWide_nominalHT410;
  TH1F *h1_pfDeltaEtajjWide_nominalHT250_monitoring;
  TH1F *h1_pfDeltaEtajjWide_nominalHT410_monitoring;
  TH1F *h1_pfDeltaEtajjWide_monitoring;
  TH1F *h1_pfDeltaEtajjWide_nominalHT250;
  TH1F *h1_pfDeltaEtajjWide_nominalHT410;

  TH1F *h1_recoHT_nominalHT250_monitoring;
  TH1F *h1_recoHT_nominalHT410_monitoring;
  TH1F *h1_recoHT_monitoring;
  TH1F *h1_recoHT_nominalHT250;
  TH1F *h1_recoHT_nominalHT410;
  TH1F *h1_recoMjj_nominalHT250_monitoring;
  TH1F *h1_recoMjj_nominalHT410_monitoring;
  TH1F *h1_recoMjj_monitoring;
  TH1F *h1_recoMjj_nominalHT250;
  TH1F *h1_recoMjj_nominalHT410;
  TH1F *h1_recoDeltaEtajj_nominalHT250_monitoring;
  TH1F *h1_recoDeltaEtajj_nominalHT410_monitoring;
  TH1F *h1_recoDeltaEtajj_monitoring;
  TH1F *h1_recoDeltaEtajj_nominalHT250;
  TH1F *h1_recoDeltaEtajj_nominalHT410;
  TH1F *h1_recoMjjWide_nominalHT250_monitoring;
  TH1F *h1_recoMjjWide_nominalHT410_monitoring;
  TH1F *h1_recoMjjWide_monitoring;
  TH1F *h1_recoMjjWide_nominalHT250;
  TH1F *h1_recoMjjWide_nominalHT410;
  TH1F *h1_recoDeltaEtajjWide_nominalHT250_monitoring;
  TH1F *h1_recoDeltaEtajjWide_nominalHT410_monitoring;
  TH1F *h1_recoDeltaEtajjWide_monitoring;
  TH1F *h1_recoDeltaEtajjWide_nominalHT250;
  TH1F *h1_recoDeltaEtajjWide_nominalHT410;


  TH1F *h1_caloHT_nominalHT250_l1monitoring;
  TH1F *h1_caloHT_nominalHT410_l1monitoring;
  TH1F *h1_caloHT_l1monitoring;
  TH1F *h1_caloMjj_nominalHT250_l1monitoring;
  TH1F *h1_caloMjj_nominalHT410_l1monitoring;
  TH1F *h1_caloMjj_l1monitoring;
  TH1F *h1_caloDeltaEtajj_nominalHT250_l1monitoring;
  TH1F *h1_caloDeltaEtajj_nominalHT410_l1monitoring;
  TH1F *h1_caloDeltaEtajj_l1monitoring;
  TH1F *h1_caloMjjWide_nominalHT250_l1monitoring;
  TH1F *h1_caloMjjWide_nominalHT410_l1monitoring;
  TH1F *h1_caloMjjWide_l1monitoring;
  TH1F *h1_caloDeltaEtajjWide_nominalHT250_l1monitoring;
  TH1F *h1_caloDeltaEtajjWide_nominalHT410_l1monitoring;
  TH1F *h1_caloDeltaEtajjWide_l1monitoring;

  TH1F *h1_pfHT_nominalHT250_l1monitoring;
  TH1F *h1_pfHT_nominalHT410_l1monitoring;
  TH1F *h1_pfHT_l1monitoring;
  TH1F *h1_pfMjj_nominalHT250_l1monitoring;
  TH1F *h1_pfMjj_nominalHT410_l1monitoring;
  TH1F *h1_pfMjj_l1monitoring;
  TH1F *h1_pfDeltaEtajj_nominalHT250_l1monitoring;
  TH1F *h1_pfDeltaEtajj_nominalHT410_l1monitoring;
  TH1F *h1_pfDeltaEtajj_l1monitoring;
  TH1F *h1_pfMjjWide_nominalHT250_l1monitoring;
  TH1F *h1_pfMjjWide_nominalHT410_l1monitoring;
  TH1F *h1_pfMjjWide_l1monitoring;
  TH1F *h1_pfDeltaEtajjWide_nominalHT250_l1monitoring;
  TH1F *h1_pfDeltaEtajjWide_nominalHT410_l1monitoring;
  TH1F *h1_pfDeltaEtajjWide_l1monitoring;

  TH1F *h1_recoHT_nominalHT250_l1monitoring;
  TH1F *h1_recoHT_nominalHT410_l1monitoring;
  TH1F *h1_recoHT_l1monitoring;
  TH1F *h1_recoMjj_nominalHT250_l1monitoring;
  TH1F *h1_recoMjj_nominalHT410_l1monitoring;
  TH1F *h1_recoMjj_l1monitoring;
  TH1F *h1_recoDeltaEtajj_nominalHT250_l1monitoring;
  TH1F *h1_recoDeltaEtajj_nominalHT410_l1monitoring;
  TH1F *h1_recoDeltaEtajj_l1monitoring;
  TH1F *h1_recoMjjWide_nominalHT250_l1monitoring;
  TH1F *h1_recoMjjWide_nominalHT410_l1monitoring;
  TH1F *h1_recoMjjWide_l1monitoring;
  TH1F *h1_recoDeltaEtajjWide_nominalHT250_l1monitoring;
  TH1F *h1_recoDeltaEtajjWide_nominalHT410_l1monitoring;
  TH1F *h1_recoDeltaEtajjWide_l1monitoring;

  // for JECs
  bool doJECsCalo_, doJECsPF_;
  edm::FileInPath L1corrAK4Calo_DATA_, L2corrAK4Calo_DATA_, L3corrAK4Calo_DATA_,ResCorrAK4Calo_DATA_;
  edm::FileInPath L1corrAK4PF_DATA_, L2corrAK4PF_DATA_, L3corrAK4PF_DATA_,ResCorrAK4PF_DATA_;
  JetCorrectorParameters *L1ParAK4Calo_DATA;
  JetCorrectorParameters *L2ParAK4Calo_DATA;
  JetCorrectorParameters *L3ParAK4Calo_DATA;
  JetCorrectorParameters *L2L3ResAK4Calo_DATA;
  FactorizedJetCorrector *JetCorrectorAK4Calo_DATA;
  JetCorrectorParameters *L1ParAK4PF_DATA;
  JetCorrectorParameters *L2ParAK4PF_DATA;
  JetCorrectorParameters *L3ParAK4PF_DATA;
  JetCorrectorParameters *L2L3ResAK4PF_DATA;
  FactorizedJetCorrector *JetCorrectorAK4PF_DATA;
};


HTScoutingL1Analyzer::HTScoutingL1Analyzer(const edm::ParameterSet& iConfig)

{
  doJECsCalo_                  = iConfig.getParameter<bool>("doJECsCalo");
  L1corrAK4Calo_DATA_          = iConfig.getParameter<edm::FileInPath>("L1corrAK4Calo_DATA");
  L2corrAK4Calo_DATA_          = iConfig.getParameter<edm::FileInPath>("L2corrAK4Calo_DATA");
  L3corrAK4Calo_DATA_          = iConfig.getParameter<edm::FileInPath>("L3corrAK4Calo_DATA");
  doJECsPF_                  = iConfig.getParameter<bool>("doJECsPF");
  L1corrAK4PF_DATA_          = iConfig.getParameter<edm::FileInPath>("L1corrAK4PF_DATA");
  L2corrAK4PF_DATA_          = iConfig.getParameter<edm::FileInPath>("L2corrAK4PF_DATA");
  L3corrAK4PF_DATA_          = iConfig.getParameter<edm::FileInPath>("L3corrAK4PF_DATA");
  caloRhoLabel_            = consumes<double>(iConfig.getParameter<edm::InputTag>("caloRho")),
  pfRhoLabel_            = consumes<double>(iConfig.getParameter<edm::InputTag>("pfRho")),
  trgResultsLabel_         = consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerResults"));
  caloJetLabel_            = consumes<ScoutingCaloJetCollection>(iConfig.getParameter<edm::InputTag>("caloJets"));
  pfJetLabel_              = consumes<ScoutingPFJetCollection>(iConfig.getParameter<edm::InputTag>("pfJets"));
  recoJetLabel_            = consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("recoJets"));
  muonLabel_               = consumes<ScoutingMuonCollection>(iConfig.getParameter<edm::InputTag>("muons"));
  usesResource("TFileService");

  tree = fs->make<TTree>("tree","tree");

  br_event= (TBranch*)tree->Branch("event",&event,"event/i");
  br_run= (TBranch*)tree->Branch("run",&run,"run/i");
  br_lumi= (TBranch*)tree->Branch("lumi",&lumi,"lumi/i");

  br_passNominalHT250Trig = (TBranch*)tree->Branch("passNominalHT250Trig", &passNominalHT250Trig, "passNominalHT250Trig/I");
  br_passNominalHT410Trig = (TBranch*)tree->Branch("passNominalHT410Trig", &passNominalHT410Trig, "passNominalHT410Trig/I");
  br_passMonitoringTrig = (TBranch*)tree->Branch("passMonitoringTrig", &passMonitoringTrig, "passMonitoringTrig/I");
  br_passL1MonitoringTrig = (TBranch*)tree->Branch("passL1MonitoringTrig", &passL1MonitoringTrig, "passL1MonitoringTrig/I");
  br_caloRho = (TBranch*)tree->Branch("caloRho", &caloRho, "caloRho/D");
  br_caloHT = (TBranch*)tree->Branch("caloHT", &caloHT, "caloHT/D");
  br_caloMjj = (TBranch*)tree->Branch("caloMjj", &caloMjj, "caloMjj/D");
  br_caloDeltaEtajj = (TBranch*)tree->Branch("caloDeltaEtajj", &caloDeltaEtajj, "caloDeltaEtajj/D");
  br_caloMjjWide = (TBranch*)tree->Branch("caloMjjWide", &caloMjjWide, "caloMjjWide/D");
  br_caloDeltaEtajjWide = (TBranch*)tree->Branch("caloDeltaEtajjWide", &caloDeltaEtajjWide, "caloDeltaEtajjWide/D");
  br_caloDeltaPhijjWide = (TBranch*)tree->Branch("caloDeltaPhijjWide", &caloDeltaPhijjWide, "caloDeltaPhijjWide/D");
  br_pfRho = (TBranch*)tree->Branch("pfRho", &pfRho, "pfRho/D");
  br_pfHT = (TBranch*)tree->Branch("pfHT", &pfHT, "pfHT/D");
  br_pfMjj = (TBranch*)tree->Branch("pfMjj", &pfMjj, "pfMjj/D");
  br_pfDeltaEtajj = (TBranch*)tree->Branch("pfDeltaEtajj", &pfDeltaEtajj, "pfDeltaEtajj/D");
  br_pfMjjWide = (TBranch*)tree->Branch("pfMjjWide", &pfMjjWide, "pfMjjWide/D");
  br_pfDeltaEtajjWide = (TBranch*)tree->Branch("pfDeltaEtajjWide", &pfDeltaEtajjWide, "pfDeltaEtajjWide/D");
  br_pfDeltaPhijjWide = (TBranch*)tree->Branch("pfDeltaPhijjWide", &pfDeltaPhijjWide, "pfDeltaPhijjWide/D");
  br_recoHT = (TBranch*)tree->Branch("recoHT", &recoHT, "recoHT/D");
  br_recoMjj = (TBranch*)tree->Branch("recoMjj", &recoMjj, "recoMjj/D");
  br_recoDeltaEtajj = (TBranch*)tree->Branch("recoDeltaEtajj", &recoDeltaEtajj, "recoDeltaEtajj/D");
  br_recoMjjWide = (TBranch*)tree->Branch("recoMjjWide", &recoMjjWide, "recoMjjWide/D");
  br_recoDeltaEtajjWide = (TBranch*)tree->Branch("recoDeltaEtajjWide", &recoDeltaEtajjWide, "recoDeltaEtajjWide/D");
  br_recoDeltaPhijjWide = (TBranch*)tree->Branch("recoDeltaPhijjWide", &recoDeltaPhijjWide, "recoDeltaPhijjWide/D");

  
  TFileDirectory histoDir = fs->mkdir("histoDir");

  h1_caloHT_nominalHT250_monitoring = histoDir.make<TH1F>("caloHT_nominalHT250_monitoring", "caloHT_nominalHT250_monitoring", 14000, 0, 14000);
  h1_caloHT_nominalHT250_l1monitoring = histoDir.make<TH1F>("caloHT_nominalHT250_l1monitoring", "caloHT_nominalHT250_l1monitoring", 14000, 0, 14000);
  h1_caloHT_nominalHT250            = histoDir.make<TH1F>("caloHT_nominalHT250", "caloHT_nominalHT250", 14000, 0, 14000);
  h1_caloHT_nominalHT410_monitoring = histoDir.make<TH1F>("caloHT_nominalHT410_monitoring", "caloHT_nominalHT410_monitoring", 14000, 0, 14000);
  h1_caloHT_nominalHT410_l1monitoring = histoDir.make<TH1F>("caloHT_nominalHT410_l1monitoring", "caloHT_nominalHT410_l1monitoring", 14000, 0, 14000);
  h1_caloHT_nominalHT410            = histoDir.make<TH1F>("caloHT_nominalHT410", "caloHT_nominalHT410", 14000, 0, 14000);
  h1_caloHT_monitoring         = histoDir.make<TH1F>("caloHT_monitoring", "caloHT_monitoring", 14000, 0, 14000);
  h1_caloHT_l1monitoring         = histoDir.make<TH1F>("caloHT_l1monitoring", "caloHT_l1monitoring", 14000, 0, 14000);

  h1_caloMjj_nominalHT250_monitoring = histoDir.make<TH1F>("caloMjj_nominalHT250_monitoring", "caloMjj_nominalHT250_monitoring", 14000, 0, 14000);
  h1_caloMjj_nominalHT250_l1monitoring = histoDir.make<TH1F>("caloMjj_nominalHT250_l1monitoring", "caloMjj_nominalHT250_l1monitoring", 14000, 0, 14000);
  h1_caloMjj_nominalHT250            = histoDir.make<TH1F>("caloMjj_nominalHT250", "caloMjj_nominalHT250", 14000, 0, 14000);
  h1_caloMjj_nominalHT410_monitoring = histoDir.make<TH1F>("caloMjj_nominalHT410_monitoring", "caloMjj_nominalHT410_monitoring", 14000, 0, 14000);
  h1_caloMjj_nominalHT410_l1monitoring = histoDir.make<TH1F>("caloMjj_nominalHT410_l1monitoring", "caloMjj_nominalHT410_l1monitoring", 14000, 0, 14000);
  h1_caloMjj_nominalHT410            = histoDir.make<TH1F>("caloMjj_nominalHT410", "caloMjj_nominalHT410", 14000, 0, 14000);
  h1_caloMjj_monitoring         = histoDir.make<TH1F>("caloMjj_monitoring", "caloMjj_monitoring", 14000, 0, 14000);
  h1_caloMjj_l1monitoring         = histoDir.make<TH1F>("caloMjj_l1monitoring", "caloMjj_l1monitoring", 14000, 0, 14000);
  
  h1_caloDeltaEtajj_nominalHT250_monitoring = histoDir.make<TH1F>("caloDeltaEtajj_nominalHT250_monitoring", "caloDeltaEtajj_nominalHT250_monitoring", 1000, 0, 5);
  h1_caloDeltaEtajj_nominalHT250_l1monitoring = histoDir.make<TH1F>("caloDeltaEtajj_nominalHT250_l1monitoring", "caloDeltaEtajj_nominalHT250_l1monitoring", 1000, 0, 5);
  h1_caloDeltaEtajj_nominalHT250            = histoDir.make<TH1F>("caloDeltaEtajj_nominalHT250", "caloDeltaEtajj_nominalHT250", 1000, 0, 5);
  h1_caloDeltaEtajj_nominalHT410_monitoring = histoDir.make<TH1F>("caloDeltaEtajj_nominalHT410_monitoring", "caloDeltaEtajj_nominalHT410_monitoring", 1000, 0, 5);
  h1_caloDeltaEtajj_nominalHT410_l1monitoring = histoDir.make<TH1F>("caloDeltaEtajj_nominalHT410_l1monitoring", "caloDeltaEtajj_nominalHT410_l1monitoring", 1000, 0, 5);
  h1_caloDeltaEtajj_nominalHT410            = histoDir.make<TH1F>("caloDeltaEtajj_nominalHT410", "caloDeltaEtajj_nominalHT410", 1000, 0, 5);
  h1_caloDeltaEtajj_monitoring         = histoDir.make<TH1F>("caloDeltaEtajj_monitoring", "caloDeltaEtajj_monitoring", 1000, 0, 5);
  h1_caloDeltaEtajj_l1monitoring         = histoDir.make<TH1F>("caloDeltaEtajj_l1monitoring", "caloDeltaEtajj_l1monitoring", 1000, 0, 5);
  
  h1_caloMjjWide_nominalHT250_monitoring = histoDir.make<TH1F>("caloMjjWide_nominalHT250_monitoring", "caloMjjWide_nominalHT250_monitoring", 14000, 0, 14000);
  h1_caloMjjWide_nominalHT250_l1monitoring = histoDir.make<TH1F>("caloMjjWide_nominalHT250_l1monitoring", "caloMjjWide_nominalHT250_l1monitoring", 14000, 0, 14000);
  h1_caloMjjWide_nominalHT250            = histoDir.make<TH1F>("caloMjjWide_nominalHT250", "caloMjjWide_nominalHT250", 14000, 0, 14000);
  h1_caloMjjWide_nominalHT410_monitoring = histoDir.make<TH1F>("caloMjjWide_nominalHT410_monitoring", "caloMjjWide_nominalHT410_monitoring", 14000, 0, 14000);
  h1_caloMjjWide_nominalHT410_l1monitoring = histoDir.make<TH1F>("caloMjjWide_nominalHT410_l1monitoring", "caloMjjWide_nominalHT410_l1monitoring", 14000, 0, 14000);
  h1_caloMjjWide_nominalHT410            = histoDir.make<TH1F>("caloMjjWide_nominalHT410", "caloMjjWide_nominalHT410", 14000, 0, 14000);
  h1_caloMjjWide_monitoring         = histoDir.make<TH1F>("caloMjjWide_monitoring", "caloMjjWide_monitoring", 14000, 0, 14000);
  h1_caloMjjWide_l1monitoring         = histoDir.make<TH1F>("caloMjjWide_l1monitoring", "caloMjjWide_l1monitoring", 14000, 0, 14000);
  
  h1_caloDeltaEtajjWide_nominalHT250_monitoring = histoDir.make<TH1F>("caloDeltaEtajjWide_nominalHT250_monitoring", "caloDeltaEtajjWide_nominalHT250_monitoring", 1000, 0, 5);
  h1_caloDeltaEtajjWide_nominalHT250_l1monitoring = histoDir.make<TH1F>("caloDeltaEtajjWide_nominalHT250_l1monitoring", "caloDeltaEtajjWide_nominalHT250_l1monitoring", 1000, 0, 5);
  h1_caloDeltaEtajjWide_nominalHT250            = histoDir.make<TH1F>("caloDeltaEtajjWide_nominalHT250", "caloDeltaEtajjWide_nominalHT250", 1000, 0, 5);
  h1_caloDeltaEtajjWide_nominalHT410_monitoring = histoDir.make<TH1F>("caloDeltaEtajjWide_nominalHT410_monitoring", "caloDeltaEtajjWide_nominalHT410_monitoring", 1000, 0, 5);
  h1_caloDeltaEtajjWide_nominalHT410_l1monitoring = histoDir.make<TH1F>("caloDeltaEtajjWide_nominalHT410_l1monitoring", "caloDeltaEtajjWide_nominalHT410_l1monitoring", 1000, 0, 5);
  h1_caloDeltaEtajjWide_nominalHT410            = histoDir.make<TH1F>("caloDeltaEtajjWide_nominalHT410", "caloDeltaEtajjWide_nominalHT410", 1000, 0, 5);
  h1_caloDeltaEtajjWide_monitoring         = histoDir.make<TH1F>("caloDeltaEtajjWide_monitoring", "caloDeltaEtajjWide_monitoring", 1000, 0, 5);
  h1_caloDeltaEtajjWide_l1monitoring         = histoDir.make<TH1F>("caloDeltaEtajjWide_l1monitoring", "caloDeltaEtajjWide_l1monitoring", 1000, 0, 5);

  h1_pfHT_nominalHT250_monitoring = histoDir.make<TH1F>("pfHT_nominalHT250_monitoring", "pfHT_nominalHT250_monitoring", 14000, 0, 14000);
  h1_pfHT_nominalHT250_l1monitoring = histoDir.make<TH1F>("pfHT_nominalHT250_l1monitoring", "pfHT_nominalHT250_l1monitoring", 14000, 0, 14000);
  h1_pfHT_nominalHT250            = histoDir.make<TH1F>("pfHT_nominalHT250", "pfHT_nominalHT250", 14000, 0, 14000);
  h1_pfHT_nominalHT410_monitoring = histoDir.make<TH1F>("pfHT_nominalHT410_monitoring", "pfHT_nominalHT410_monitoring", 14000, 0, 14000);
  h1_pfHT_nominalHT410_l1monitoring = histoDir.make<TH1F>("pfHT_nominalHT410_l1monitoring", "pfHT_nominalHT410_l1monitoring", 14000, 0, 14000);
  h1_pfHT_nominalHT410            = histoDir.make<TH1F>("pfHT_nominalHT410", "pfHT_nominalHT410", 14000, 0, 14000);
  h1_pfHT_monitoring         = histoDir.make<TH1F>("pfHT_monitoring", "pfHT_monitoring", 14000, 0, 14000);
  h1_pfHT_l1monitoring         = histoDir.make<TH1F>("pfHT_l1monitoring", "pfHT_l1monitoring", 14000, 0, 14000);

  h1_pfMjj_nominalHT250_monitoring = histoDir.make<TH1F>("pfMjj_nominalHT250_monitoring", "pfMjj_nominalHT250_monitoring", 14000, 0, 14000);
  h1_pfMjj_nominalHT250_l1monitoring = histoDir.make<TH1F>("pfMjj_nominalHT250_l1monitoring", "pfMjj_nominalHT250_l1monitoring", 14000, 0, 14000);
  h1_pfMjj_nominalHT250            = histoDir.make<TH1F>("pfMjj_nominalHT250", "pfMjj_nominalHT250", 14000, 0, 14000);
  h1_pfMjj_nominalHT410_monitoring = histoDir.make<TH1F>("pfMjj_nominalHT410_monitoring", "pfMjj_nominalHT410_monitoring", 14000, 0, 14000);
  h1_pfMjj_nominalHT410_l1monitoring = histoDir.make<TH1F>("pfMjj_nominalHT410_l1monitoring", "pfMjj_nominalHT410_l1monitoring", 14000, 0, 14000);
  h1_pfMjj_nominalHT410            = histoDir.make<TH1F>("pfMjj_nominalHT410", "pfMjj_nominalHT410", 14000, 0, 14000);
  h1_pfMjj_monitoring         = histoDir.make<TH1F>("pfMjj_monitoring", "pfMjj_monitoring", 14000, 0, 14000);
  h1_pfMjj_l1monitoring         = histoDir.make<TH1F>("pfMjj_l1monitoring", "pfMjj_l1monitoring", 14000, 0, 14000);

  h1_pfDeltaEtajj_nominalHT250_monitoring = histoDir.make<TH1F>("pfDeltaEtajj_nominalHT250_monitoring", "pfDeltaEtajj_nominalHT250_monitoring", 1000, 0, 5);
  h1_pfDeltaEtajj_nominalHT250_l1monitoring = histoDir.make<TH1F>("pfDeltaEtajj_nominalHT250_l1monitoring", "pfDeltaEtajj_nominalHT250_l1monitoring", 1000, 0, 5);
  h1_pfDeltaEtajj_nominalHT250            = histoDir.make<TH1F>("pfDeltaEtajj_nominalHT250", "pfDeltaEtajj_nominalHT250", 1000, 0, 5);
  h1_pfDeltaEtajj_nominalHT410_monitoring = histoDir.make<TH1F>("pfDeltaEtajj_nominalHT410_monitoring", "pfDeltaEtajj_nominalHT410_monitoring", 1000, 0, 5);
  h1_pfDeltaEtajj_nominalHT410_l1monitoring = histoDir.make<TH1F>("pfDeltaEtajj_nominalHT410_l1monitoring", "pfDeltaEtajj_nominalHT410_l1monitoring", 1000, 0, 5);
  h1_pfDeltaEtajj_nominalHT410            = histoDir.make<TH1F>("pfDeltaEtajj_nominalHT410", "pfDeltaEtajj_nominalHT410", 1000, 0, 5);
  h1_pfDeltaEtajj_monitoring         = histoDir.make<TH1F>("pfDeltaEtajj_monitoring", "pfDeltaEtajj_monitoring", 1000, 0, 5);
  h1_pfDeltaEtajj_l1monitoring         = histoDir.make<TH1F>("pfDeltaEtajj_l1monitoring", "pfDeltaEtajj_l1monitoring", 1000, 0, 5);
  
  h1_pfMjjWide_nominalHT250_monitoring = histoDir.make<TH1F>("pfMjjWide_nominalHT250_monitoring", "pfMjjWide_nominalHT250_monitoring", 14000, 0, 14000);
  h1_pfMjjWide_nominalHT250_l1monitoring = histoDir.make<TH1F>("pfMjjWide_nominalHT250_l1monitoring", "pfMjjWide_nominalHT250_l1monitoring", 14000, 0, 14000);
  h1_pfMjjWide_nominalHT250            = histoDir.make<TH1F>("pfMjjWide_nominalHT250", "pfMjjWide_nominalHT250", 14000, 0, 14000);
  h1_pfMjjWide_nominalHT410_monitoring = histoDir.make<TH1F>("pfMjjWide_nominalHT410_monitoring", "pfMjjWide_nominalHT410_monitoring", 14000, 0, 14000);
  h1_pfMjjWide_nominalHT410_l1monitoring = histoDir.make<TH1F>("pfMjjWide_nominalHT410_l1monitoring", "pfMjjWide_nominalHT410_l1monitoring", 14000, 0, 14000);
  h1_pfMjjWide_nominalHT410            = histoDir.make<TH1F>("pfMjjWide_nominalHT410", "pfMjjWide_nominalHT410", 14000, 0, 14000);
  h1_pfMjjWide_monitoring         = histoDir.make<TH1F>("pfMjjWide_monitoring", "pfMjjWide_monitoring", 14000, 0, 14000);
  h1_pfMjjWide_l1monitoring         = histoDir.make<TH1F>("pfMjjWide_l1monitoring", "pfMjjWide_l1monitoring", 14000, 0, 14000);
  
  h1_pfDeltaEtajjWide_nominalHT250_monitoring = histoDir.make<TH1F>("pfDeltaEtajjWide_nominalHT250_monitoring", "pfDeltaEtajjWide_nominalHT250_monitoring", 1000, 0, 5);
  h1_pfDeltaEtajjWide_nominalHT250_l1monitoring = histoDir.make<TH1F>("pfDeltaEtajjWide_nominalHT250_l1monitoring", "pfDeltaEtajjWide_nominalHT250_l1monitoring", 1000, 0, 5);
  h1_pfDeltaEtajjWide_nominalHT250            = histoDir.make<TH1F>("pfDeltaEtajjWide_nominalHT250", "pfDeltaEtajjWide_nominalHT250", 1000, 0, 5);
  h1_pfDeltaEtajjWide_nominalHT410_monitoring = histoDir.make<TH1F>("pfDeltaEtajjWide_nominalHT410_monitoring", "pfDeltaEtajjWide_nominalHT410_monitoring", 1000, 0, 5);
  h1_pfDeltaEtajjWide_nominalHT410_l1monitoring = histoDir.make<TH1F>("pfDeltaEtajjWide_nominalHT410_l1monitoring", "pfDeltaEtajjWide_nominalHT410_l1monitoring", 1000, 0, 5);
  h1_pfDeltaEtajjWide_nominalHT410            = histoDir.make<TH1F>("pfDeltaEtajjWide_nominalHT410", "pfDeltaEtajjWide_nominalHT410", 1000, 0, 5);
  h1_pfDeltaEtajjWide_monitoring         = histoDir.make<TH1F>("pfDeltaEtajjWide_monitoring", "pfDeltaEtajjWide_monitoring", 1000, 0, 5);
  h1_pfDeltaEtajjWide_l1monitoring         = histoDir.make<TH1F>("pfDeltaEtajjWide_l1monitoring", "pfDeltaEtajjWide_l1monitoring", 1000, 0, 5);

  h1_recoHT_nominalHT250_monitoring = histoDir.make<TH1F>("recoHT_nominalHT250_monitoring", "recoHT_nominalHT250_monitoring", 14000, 0, 14000);
  h1_recoHT_nominalHT250_l1monitoring = histoDir.make<TH1F>("recoHT_nominalHT250_l1monitoring", "recoHT_nominalHT250_l1monitoring", 14000, 0, 14000);
  h1_recoHT_nominalHT250            = histoDir.make<TH1F>("recoHT_nominalHT250", "recoHT_nominalHT250", 14000, 0, 14000);
  h1_recoHT_nominalHT410_monitoring = histoDir.make<TH1F>("recoHT_nominalHT410_monitoring", "recoHT_nominalHT410_monitoring", 14000, 0, 14000);
  h1_recoHT_nominalHT410_l1monitoring = histoDir.make<TH1F>("recoHT_nominalHT410_l1monitoring", "recoHT_nominalHT410_l1monitoring", 14000, 0, 14000);
  h1_recoHT_nominalHT410            = histoDir.make<TH1F>("recoHT_nominalHT410", "recoHT_nominalHT410", 14000, 0, 14000);
  h1_recoHT_monitoring         = histoDir.make<TH1F>("recoHT_monitoring", "recoHT_monitoring", 14000, 0, 14000);
  h1_recoHT_l1monitoring         = histoDir.make<TH1F>("recoHT_l1monitoring", "recoHT_l1monitoring", 14000, 0, 14000);

  h1_recoMjj_nominalHT250_monitoring = histoDir.make<TH1F>("recoMjj_nominalHT250_monitoring", "recoMjj_nominalHT250_monitoring", 14000, 0, 14000);
  h1_recoMjj_nominalHT250_l1monitoring = histoDir.make<TH1F>("recoMjj_nominalHT250_l1monitoring", "recoMjj_nominalHT250_l1monitoring", 14000, 0, 14000);
  h1_recoMjj_nominalHT250            = histoDir.make<TH1F>("recoMjj_nominalHT250", "recoMjj_nominalHT250", 14000, 0, 14000);
  h1_recoMjj_nominalHT410_monitoring = histoDir.make<TH1F>("recoMjj_nominalHT410_monitoring", "recoMjj_nominalHT410_monitoring", 14000, 0, 14000);
  h1_recoMjj_nominalHT410_l1monitoring = histoDir.make<TH1F>("recoMjj_nominalHT410_l1monitoring", "recoMjj_nominalHT410_l1monitoring", 14000, 0, 14000);
  h1_recoMjj_nominalHT410            = histoDir.make<TH1F>("recoMjj_nominalHT410", "recoMjj_nominalHT410", 14000, 0, 14000);
  h1_recoMjj_monitoring         = histoDir.make<TH1F>("recoMjj_monitoring", "recoMjj_monitoring", 14000, 0, 14000);
  h1_recoMjj_l1monitoring         = histoDir.make<TH1F>("recoMjj_l1monitoring", "recoMjj_l1monitoring", 14000, 0, 14000);
  
  h1_recoDeltaEtajj_nominalHT250_monitoring = histoDir.make<TH1F>("recoDeltaEtajj_nominalHT250_monitoring", "recoDeltaEtajj_nominalHT250_monitoring", 1000, 0, 5);
  h1_recoDeltaEtajj_nominalHT250_l1monitoring = histoDir.make<TH1F>("recoDeltaEtajj_nominalHT250_l1monitoring", "recoDeltaEtajj_nominalHT250_l1monitoring", 1000, 0, 5);
  h1_recoDeltaEtajj_nominalHT250            = histoDir.make<TH1F>("recoDeltaEtajj_nominalHT250", "recoDeltaEtajj_nominalHT250", 1000, 0, 5);
  h1_recoDeltaEtajj_nominalHT410_monitoring = histoDir.make<TH1F>("recoDeltaEtajj_nominalHT410_monitoring", "recoDeltaEtajj_nominalHT410_monitoring", 1000, 0, 5);
  h1_recoDeltaEtajj_nominalHT410_l1monitoring = histoDir.make<TH1F>("recoDeltaEtajj_nominalHT410_l1monitoring", "recoDeltaEtajj_nominalHT410_l1monitoring", 1000, 0, 5);
  h1_recoDeltaEtajj_nominalHT410            = histoDir.make<TH1F>("recoDeltaEtajj_nominalHT410", "recoDeltaEtajj_nominalHT410", 1000, 0, 5);
  h1_recoDeltaEtajj_monitoring         = histoDir.make<TH1F>("recoDeltaEtajj_monitoring", "recoDeltaEtajj_monitoring", 1000, 0, 5);
  h1_recoDeltaEtajj_l1monitoring         = histoDir.make<TH1F>("recoDeltaEtajj_l1monitoring", "recoDeltaEtajj_l1monitoring", 1000, 0, 5);
  
  h1_recoMjjWide_nominalHT250_monitoring = histoDir.make<TH1F>("recoMjjWide_nominalHT250_monitoring", "recoMjjWide_nominalHT250_monitoring", 14000, 0, 14000);
  h1_recoMjjWide_nominalHT250_l1monitoring = histoDir.make<TH1F>("recoMjjWide_nominalHT250_l1monitoring", "recoMjjWide_nominalHT250_l1monitoring", 14000, 0, 14000);
  h1_recoMjjWide_nominalHT250            = histoDir.make<TH1F>("recoMjjWide_nominalHT250", "recoMjjWide_nominalHT250", 14000, 0, 14000);
  h1_recoMjjWide_nominalHT410_monitoring = histoDir.make<TH1F>("recoMjjWide_nominalHT410_monitoring", "recoMjjWide_nominalHT410_monitoring", 14000, 0, 14000);
  h1_recoMjjWide_nominalHT410_l1monitoring = histoDir.make<TH1F>("recoMjjWide_nominalHT410_l1monitoring", "recoMjjWide_nominalHT410_l1monitoring", 14000, 0, 14000);
  h1_recoMjjWide_nominalHT410            = histoDir.make<TH1F>("recoMjjWide_nominalHT410", "recoMjjWide_nominalHT410", 14000, 0, 14000);
  h1_recoMjjWide_monitoring         = histoDir.make<TH1F>("recoMjjWide_monitoring", "recoMjjWide_monitoring", 14000, 0, 14000);
  h1_recoMjjWide_l1monitoring         = histoDir.make<TH1F>("recoMjjWide_l1monitoring", "recoMjjWide_l1monitoring", 14000, 0, 14000);
  
  h1_recoDeltaEtajjWide_nominalHT250_monitoring = histoDir.make<TH1F>("recoDeltaEtajjWide_nominalHT250_monitoring", "recoDeltaEtajjWide_nominalHT250_monitoring", 1000, 0, 5);
  h1_recoDeltaEtajjWide_nominalHT250_l1monitoring = histoDir.make<TH1F>("recoDeltaEtajjWide_nominalHT250_l1monitoring", "recoDeltaEtajjWide_nominalHT250_l1monitoring", 1000, 0, 5);
  h1_recoDeltaEtajjWide_nominalHT250            = histoDir.make<TH1F>("recoDeltaEtajjWide_nominalHT250", "recoDeltaEtajjWide_nominalHT250", 1000, 0, 5);
  h1_recoDeltaEtajjWide_nominalHT410_monitoring = histoDir.make<TH1F>("recoDeltaEtajjWide_nominalHT410_monitoring", "recoDeltaEtajjWide_nominalHT410_monitoring", 1000, 0, 5);
  h1_recoDeltaEtajjWide_nominalHT410_l1monitoring = histoDir.make<TH1F>("recoDeltaEtajjWide_nominalHT410_l1monitoring", "recoDeltaEtajjWide_nominalHT410_l1monitoring", 1000, 0, 5);
  h1_recoDeltaEtajjWide_nominalHT410            = histoDir.make<TH1F>("recoDeltaEtajjWide_nominalHT410", "recoDeltaEtajjWide_nominalHT410", 1000, 0, 5);
  h1_recoDeltaEtajjWide_monitoring         = histoDir.make<TH1F>("recoDeltaEtajjWide_monitoring", "recoDeltaEtajjWide_monitoring", 1000, 0, 5);
  h1_recoDeltaEtajjWide_l1monitoring         = histoDir.make<TH1F>("recoDeltaEtajjWide_l1monitoring", "recoDeltaEtajjWide_l1monitoring", 1000, 0, 5);
  

  if (doJECsCalo_) {
    L1ParAK4Calo_DATA = new JetCorrectorParameters(L1corrAK4Calo_DATA_.fullPath());
    L2ParAK4Calo_DATA = new JetCorrectorParameters(L2corrAK4Calo_DATA_.fullPath());
    L3ParAK4Calo_DATA = new JetCorrectorParameters(L3corrAK4Calo_DATA_.fullPath());

    std::vector<JetCorrectorParameters> vParAK4Calo_DATA;
    vParAK4Calo_DATA.push_back(*L1ParAK4Calo_DATA);
    vParAK4Calo_DATA.push_back(*L2ParAK4Calo_DATA);
    vParAK4Calo_DATA.push_back(*L3ParAK4Calo_DATA);

    JetCorrectorAK4Calo_DATA = new FactorizedJetCorrector(vParAK4Calo_DATA);
  }

  if (doJECsPF_) {
    L1ParAK4PF_DATA = new JetCorrectorParameters(L1corrAK4PF_DATA_.fullPath());
    L2ParAK4PF_DATA = new JetCorrectorParameters(L2corrAK4PF_DATA_.fullPath());
    L3ParAK4PF_DATA = new JetCorrectorParameters(L3corrAK4PF_DATA_.fullPath());

    std::vector<JetCorrectorParameters> vParAK4PF_DATA;
    vParAK4PF_DATA.push_back(*L1ParAK4PF_DATA);
    vParAK4PF_DATA.push_back(*L2ParAK4PF_DATA);
    vParAK4PF_DATA.push_back(*L3ParAK4PF_DATA);

    JetCorrectorAK4PF_DATA = new FactorizedJetCorrector(vParAK4PF_DATA);
  }
}



HTScoutingL1Analyzer::~HTScoutingL1Analyzer()
{
}


// ------------ method called for each event  ------------
void
HTScoutingL1Analyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

   event = iEvent.id().event();
   run   = iEvent.id().run();
   lumi  = iEvent.luminosityBlock();

   //std::cout << "\nEVT" << std::endl;
   using namespace edm;
   passNominalHT250Trig=99;
   passNominalHT410Trig=99;
   passMonitoringTrig=99;
   passL1MonitoringTrig=99;
   caloHT=0.0;
   caloMjj=-1;
   caloDeltaEtajj = -1;
   caloMjjWide = -1; 
   caloDeltaEtajjWide = -1;
   caloDeltaPhijjWide = -1;
   
   pfHT=0.0;
   pfMjj=-1;
   pfDeltaEtajj = -1;
   pfMjjWide = -1; 
   pfDeltaEtajjWide = -1;
   pfDeltaPhijjWide = -1;
   
   recoHT=0.0;
   recoMjj=-1;
   recoDeltaEtajj = -1;
   recoMjjWide = -1; 
   recoDeltaEtajjWide = -1;
   recoDeltaPhijjWide = -1;
   edm::Handle<edm::TriggerResults> trgResultsHandle;
   iEvent.getByToken(trgResultsLabel_, trgResultsHandle);
   
   const edm::TriggerNames &trgNames = iEvent.triggerNames(*trgResultsHandle);

   for (size_t i = 0; i < trgNames.size(); ++i) {
     const std::string &name = trgNames.triggerName(i);
   
     if ( (name.find("DST_HT250_CaloScouting_v") != std::string::npos )) {
       passNominalHT250Trig=trgResultsHandle->accept(i);
     }
     if ( (name.find("DST_HT410_PFScouting_v") != std::string::npos )) {
       passNominalHT410Trig=trgResultsHandle->accept(i);
     }
     if ( (name.find("HLT_Mu50_v") != std::string::npos )) {
       passMonitoringTrig=trgResultsHandle->accept(i);
     }
     if ( (name.find("DST_CaloJet40_CaloScouting_PFScouting_v") != std::string::npos )) {
       passL1MonitoringTrig=trgResultsHandle->accept(i);
     }
     
   }
   
   //std::cout << "HT250:" << passNominalHT250Trig << " Mu50:" << passMonitoringTrig << std::endl;
   //std::cout << "HT410:" << passNominalHT410Trig << " Mu50:" << passMonitoringTrig << std::endl;
   
   
   edm::Handle<ScoutingMuonCollection> muonHandle;
   iEvent.getByToken(muonLabel_, muonHandle);
   
   edm::Handle<ScoutingCaloJetCollection> caloJetHandle;
   iEvent.getByToken(caloJetLabel_, caloJetHandle);
   
   edm::Handle<double> caloRhoHandle;
   iEvent.getByToken(caloRhoLabel_, caloRhoHandle);
   caloRho = *caloRhoHandle;

   edm::Handle<ScoutingPFJetCollection> pfJetHandle;
   iEvent.getByToken(pfJetLabel_, pfJetHandle);
   
   edm::Handle<double> pfRhoHandle;
   iEvent.getByToken(pfRhoLabel_, pfRhoHandle);
   pfRho = *pfRhoHandle;

   edm::Handle<pat::JetCollection> recoJetHandle;
   iEvent.getByToken(recoJetLabel_, recoJetHandle);
   
   //JEC Calo factors
   std::vector<double> jecFactorsAK4Calo;
   // Sort AK4 jets by increasing pT
   std::vector<unsigned> sortedAK4CaloJetIdx;
   std::multimap<double, unsigned> sortedAK4CaloJets;

   //std::cout << "Begin ScoutingCaloJetCollection loop\n" << std::endl;
   for (ScoutingCaloJetCollection::const_iterator iCj = caloJetHandle->begin(); iCj != caloJetHandle->end(); ++iCj) {	   
     TLorentzVector cj1;
     double correction = 1.0;
     if (doJECsCalo_) {
       //std::cout << "doJECsCalo" << std::endl;
       JetCorrectorAK4Calo_DATA->setJetEta(iCj->eta());
       JetCorrectorAK4Calo_DATA->setJetPt(iCj->pt());
       JetCorrectorAK4Calo_DATA->setJetA(iCj->jetArea());
       JetCorrectorAK4Calo_DATA->setRho(caloRho);
       correction = JetCorrectorAK4Calo_DATA->getCorrection();
     }
     jecFactorsAK4Calo.push_back(correction);
     cj1.SetPtEtaPhiM(iCj->pt()*correction, iCj->eta(), iCj->phi(), iCj->m());
     sortedAK4CaloJets.insert(std::make_pair(cj1.Pt(), iCj - caloJetHandle->begin()));
     if (cj1.Pt() > 40. && fabs(cj1.Eta()) < 3.0) caloHT += cj1.Pt();
   }
   //std::cout << "End ScoutingCaloJetCollection loop\n" << std::endl;

   // Get Calo jet indices in decreasing pT order
   for (std::multimap<double, unsigned>::const_reverse_iterator it=sortedAK4CaloJets.rbegin(); it!=sortedAK4CaloJets.rend(); ++it) {
     sortedAK4CaloJetIdx.push_back(it->second);
   }
   
   //JEC PF factors
   std::vector<double> jecFactorsAK4PF;
   // Sort AK4 jets by increasing pT
   std::vector<unsigned> sortedAK4PFJetIdx;
   std::multimap<double, unsigned> sortedAK4PFJets;

   //std::cout << "Begin ScoutingPFJetCollection loop\n" << std::endl;
   for (ScoutingPFJetCollection::const_iterator iCj = pfJetHandle->begin(); iCj != pfJetHandle->end(); ++iCj) {	   
     TLorentzVector cj1;
     //cj1.SetPtEtaPhiM(iCj->pt(), iCj->eta(), iCj->phi(), iCj->m());
     double correction = 1.0;
     if (doJECsPF_) {
       //std::cout << "doJECsPF" << std::endl;
       JetCorrectorAK4PF_DATA->setJetEta(iCj->eta());
       JetCorrectorAK4PF_DATA->setJetPt(iCj->pt());
       JetCorrectorAK4PF_DATA->setJetA(iCj->jetArea());
       JetCorrectorAK4PF_DATA->setRho(pfRho);
       correction = JetCorrectorAK4PF_DATA->getCorrection();
     }
     jecFactorsAK4PF.push_back(correction);
     cj1.SetPtEtaPhiM(iCj->pt()*correction, iCj->eta(), iCj->phi(), iCj->m());
     sortedAK4PFJets.insert(std::make_pair(cj1.Pt(), iCj - pfJetHandle->begin()));
     if (iCj->pt() > 40. && fabs(iCj->eta()) < 3.0) pfHT += iCj->pt();
   }
   //std::cout << "End ScoutingPFJetCollection loop\n" << std::endl;

   // Get PF jet indices in decreasing pT order
   for (std::multimap<double, unsigned>::const_reverse_iterator it=sortedAK4PFJets.rbegin(); it!=sortedAK4PFJets.rend(); ++it) {
     sortedAK4PFJetIdx.push_back(it->second);
   }
   
   //std::cout << "Begin pat::JetCollection loop\n" << std::endl;
   for (pat::JetCollection::const_iterator iCj = recoJetHandle->begin(); iCj != recoJetHandle->end(); ++iCj) {	   
     TLorentzVector cj1;
     cj1.SetPtEtaPhiM(iCj->pt(), iCj->eta(), iCj->phi(), iCj->mass());
     if (iCj->pt() > 40. && fabs(iCj->eta()) < 3.0) recoHT += iCj->pt();
   }
   //std::cout << "End pat::JetCollection loop\n" << std::endl;
      
   double wideJetDeltaR_ = 1.1;

   //std::cout << "if caloJetHandle->size() = " <<  caloJetHandle->size() << std::endl;
   if (caloJetHandle->size() > 2){     
     TLorentzVector wj1, wj2, wdijet;
     TLorentzVector wj1_tmp, wj2_tmp;
     const ScoutingCaloJet & iCj = (*caloJetHandle)[ sortedAK4CaloJetIdx[0] ];
     const ScoutingCaloJet & jCj = (*caloJetHandle)[ sortedAK4CaloJetIdx[1] ];
     TLorentzVector jet1, jet2;
     jet1.SetPtEtaPhiM(jecFactorsAK4Calo[ sortedAK4CaloJetIdx[0] ]*(iCj.pt()), iCj.eta(), iCj.phi(), iCj.m());
     jet2.SetPtEtaPhiM(jecFactorsAK4Calo[ sortedAK4CaloJetIdx[1] ]*(jCj.pt()), jCj.eta(), jCj.phi(), jCj.m());
     if (jet1.Pt() > 60. && fabs(jet1.Eta()) < 2.5) {	 
       if (jet2.Pt() > 30. && fabs(jet2.Eta()) < 2.5) {
	 caloMjj = (jet1+jet2).M();
	 caloDeltaEtajj = fabs(jet1.Eta()-jet2.Eta());
	 for(size_t ijet=0; ijet<caloJetHandle->size(); ijet++) {
	   const ScoutingCaloJet & kCj = (*caloJetHandle)[ sortedAK4CaloJetIdx[ijet] ];
	   TLorentzVector currentJet;
	   currentJet.SetPtEtaPhiM(jecFactorsAK4Calo[ sortedAK4CaloJetIdx[ijet] ]*(kCj.pt()), kCj.eta(), kCj.phi(), kCj.m());	     
	   if (currentJet.Pt() > 30. && fabs(currentJet.Eta()) < 2.5) {
	     double DeltaR1 = currentJet.DeltaR(jet1);
	     double DeltaR2 = currentJet.DeltaR(jet2);			   
	     if(DeltaR1 < DeltaR2 && DeltaR1 < wideJetDeltaR_)
	       {
		 wj1_tmp += currentJet;
	       }
	     else if(DeltaR2 < wideJetDeltaR_)
	       {
		 wj2_tmp += currentJet;
	       }			 
	   } // if AK4 jet passes fid and jetid.
	 } //end of ak4 jet loop		     
       } //fid, jet id, pt cut
     } //fid, jet id, pt cut
     
     // Re-order the wide jets in pt
     if( wj1_tmp.Pt() > wj2_tmp.Pt())
       {
	 wj1 = wj1_tmp;
	 wj2 = wj2_tmp;
       }
     else
       {
	 wj1 = wj2_tmp;
	 wj2 = wj1_tmp;
       }
   
     if( wj1.Pt()>0 && wj2.Pt()>0 )
       {
	 // Create dijet system
	 wdijet = wj1 + wj2;
	 caloMjjWide = wdijet.M();
	 caloDeltaEtajjWide = fabs(wj1.Eta()-wj2.Eta());
	 caloDeltaPhijjWide = fabs(wj1.DeltaPhi(wj2));
       }

   } // end of two calo jets.
   //std::cout << "end if caloJetHandle->size() = " <<  caloJetHandle->size() << std::endl;

   //std::cout << "if pfJetHandle->size() = " <<  pfJetHandle->size() << std::endl;
   if (pfJetHandle->size() > 2){     
     TLorentzVector wj1, wj2, wdijet;
     TLorentzVector wj1_tmp, wj2_tmp;
     const ScoutingPFJet & iCj = (*pfJetHandle)[ sortedAK4PFJetIdx[0] ];
     const ScoutingPFJet & jCj = (*pfJetHandle)[ sortedAK4PFJetIdx[1] ];
     if (iCj.pt() > 60. && fabs(iCj.eta()) < 2.5) {	 
       if (jCj.pt() > 30. && fabs(jCj.eta()) < 2.5) {
	 TLorentzVector jet1, jet2;
         jet1.SetPtEtaPhiM(jecFactorsAK4PF[ sortedAK4PFJetIdx[0] ]*(iCj.pt()), iCj.eta(), iCj.phi(), iCj.m());
         jet2.SetPtEtaPhiM(jecFactorsAK4PF[ sortedAK4PFJetIdx[1] ]*(jCj.pt()), jCj.eta(), jCj.phi(), jCj.m());
	 pfMjj = (jet1+jet2).M();
	 pfDeltaEtajj = fabs(jet1.Eta()-jet2.Eta());
	 for(size_t ijet=0; ijet<pfJetHandle->size(); ijet++) {
	   const ScoutingPFJet & kCj = (*pfJetHandle)[ sortedAK4PFJetIdx[ijet] ];
	   TLorentzVector currentJet;
	   currentJet.SetPtEtaPhiM(jecFactorsAK4PF[ sortedAK4PFJetIdx[ijet] ]*(kCj.pt()), kCj.eta(), kCj.phi(), kCj.m());	     
	   if (currentJet.Pt() > 30. && fabs(currentJet.Eta()) < 2.5) {
	     double DeltaR1 = currentJet.DeltaR(jet1);
	     double DeltaR2 = currentJet.DeltaR(jet2);			   
	     if(DeltaR1 < DeltaR2 && DeltaR1 < wideJetDeltaR_)
	       {
		 wj1_tmp += currentJet;
	       }
	     else if(DeltaR2 < wideJetDeltaR_)
	       {
		 wj2_tmp += currentJet;
	       }			 
	   } // if AK4 jet passes fid and jetid.
	 } //end of ak4 jet loop		     
       } //fid, jet id, pt cut
     } //fid, jet id, pt cut
     
     // Re-order the wide jets in pt
     if( wj1_tmp.Pt() > wj2_tmp.Pt())
       {
	 wj1 = wj1_tmp;
	 wj2 = wj2_tmp;
       }
     else
       {
	 wj1 = wj2_tmp;
	 wj2 = wj1_tmp;
       }
   
     if( wj1.Pt()>0 && wj2.Pt()>0 )
       {
	 // Create dijet system
	 wdijet = wj1 + wj2;
	 pfMjjWide = wdijet.M();
	 pfDeltaEtajjWide = fabs(wj1.Eta()-wj2.Eta());
	 pfDeltaPhijjWide = fabs(wj1.DeltaPhi(wj2));
       }

   } // end of two PF jets.
   //std::cout << "end if pfJetHandle->size() = " <<  pfJetHandle->size() << std::endl;
   
   //std::cout << "if recoJetHandle->size() = " <<  recoJetHandle->size() << std::endl;
   if (recoJetHandle->size() > 2){     
     TLorentzVector wj1, wj2, wdijet;
     TLorentzVector wj1_tmp, wj2_tmp;
     const pat::Jet & iCj = (*recoJetHandle)[ 0 ];
     const pat::Jet & jCj = (*recoJetHandle)[ 1 ];
     if (iCj.pt() > 60. && fabs(iCj.eta()) < 2.5) {	 
       if (jCj.pt() > 30. && fabs(jCj.eta()) < 2.5) {
	 TLorentzVector jet1, jet2;
	 jet1.SetPtEtaPhiM(iCj.pt(), iCj.eta(), iCj.phi(), iCj.mass());
	 jet2.SetPtEtaPhiM(jCj.pt(), jCj.eta(), jCj.phi(), jCj.mass());
	 recoMjj = (jet1+jet2).M();
	 recoDeltaEtajj = fabs(jet1.Eta()-jet2.Eta());
	 for (pat::JetCollection::const_iterator kCj = recoJetHandle->begin(); kCj != recoJetHandle->end(); ++kCj) {
	   TLorentzVector currentJet;
	   if (kCj->pt() > 30. && fabs(kCj->eta()) < 2.5) {
	     currentJet.SetPtEtaPhiM(kCj->pt(), kCj->eta(), kCj->phi(), kCj->mass());			   
	     double DeltaR1 = currentJet.DeltaR(jet1);
	     double DeltaR2 = currentJet.DeltaR(jet2);			   
	     if(DeltaR1 < DeltaR2 && DeltaR1 < wideJetDeltaR_)
	       {
		 wj1_tmp += currentJet;
	       }
	     else if(DeltaR2 < wideJetDeltaR_)
	       {
		 wj2_tmp += currentJet;
	       }			 
	   } // if AK4 jet passes fid and jetid.
	 } //end of ak4 jet loop		     
       } //fid, jet id, pt cut
     } //fid, jet id, pt cut
     
     // Re-order the wide jets in pt
     if( wj1_tmp.Pt() > wj2_tmp.Pt())
       {
	 wj1 = wj1_tmp;
	 wj2 = wj2_tmp;
       }
     else
       {
	 wj1 = wj2_tmp;
	 wj2 = wj1_tmp;
       }
   
     if( wj1.Pt()>0 && wj2.Pt()>0 )
       {
	 // Create dijet system
	 wdijet = wj1 + wj2;
	 recoMjjWide = wdijet.M();
	 recoDeltaEtajjWide = fabs(wj1.Eta()-wj2.Eta());
	 recoDeltaPhijjWide = fabs(wj1.DeltaPhi(wj2));
       }

   } // end of two RECO jets.
   //std::cout << "end if recoJetHandle->size() = " <<  recoJetHandle->size() << std::endl;
   
   if (passNominalHT250Trig && passMonitoringTrig) {
     h1_caloHT_nominalHT250_monitoring->Fill(caloHT) ;
     if (caloDeltaEtajj > -1 && caloDeltaEtajj < 1.3) h1_caloMjj_nominalHT250_monitoring->Fill(caloMjj) ;
     h1_caloDeltaEtajj_nominalHT250_monitoring->Fill(caloDeltaEtajj) ;
     if (caloDeltaEtajjWide > -1 && caloDeltaEtajjWide < 1.3) h1_caloMjjWide_nominalHT250_monitoring->Fill(caloMjjWide) ;
     h1_caloDeltaEtajjWide_nominalHT250_monitoring->Fill(caloDeltaEtajjWide) ;
     
     h1_pfHT_nominalHT250_monitoring->Fill(pfHT) ;
     if (pfDeltaEtajj > -1 && pfDeltaEtajj < 1.3) h1_pfMjj_nominalHT250_monitoring->Fill(pfMjj) ;
     h1_pfDeltaEtajj_nominalHT250_monitoring->Fill(pfDeltaEtajj) ;
     if (pfDeltaEtajjWide > -1 && pfDeltaEtajjWide < 1.3) h1_pfMjjWide_nominalHT250_monitoring->Fill(pfMjjWide) ;
     h1_pfDeltaEtajjWide_nominalHT250_monitoring->Fill(pfDeltaEtajjWide) ;
     
     h1_recoHT_nominalHT250_monitoring->Fill(recoHT) ;
     if (recoDeltaEtajj > -1 && recoDeltaEtajj < 1.3) h1_recoMjj_nominalHT250_monitoring->Fill(recoMjj) ;
     h1_recoDeltaEtajj_nominalHT250_monitoring->Fill(recoDeltaEtajj) ;
     if (recoDeltaEtajjWide > -1 && recoDeltaEtajjWide < 1.3) h1_recoMjjWide_nominalHT250_monitoring->Fill(recoMjjWide) ;
     h1_recoDeltaEtajjWide_nominalHT250_monitoring->Fill(recoDeltaEtajjWide) ;
   }
   if (passNominalHT250Trig && passL1MonitoringTrig) {
     h1_caloHT_nominalHT250_l1monitoring->Fill(caloHT) ;
     if (caloDeltaEtajj > -1 && caloDeltaEtajj < 1.3) h1_caloMjj_nominalHT250_l1monitoring->Fill(caloMjj) ;
     h1_caloDeltaEtajj_nominalHT250_l1monitoring->Fill(caloDeltaEtajj) ;
     if (caloDeltaEtajjWide > -1 && caloDeltaEtajjWide < 1.3) h1_caloMjjWide_nominalHT250_l1monitoring->Fill(caloMjjWide) ;
     h1_caloDeltaEtajjWide_nominalHT250_l1monitoring->Fill(caloDeltaEtajjWide) ;
     
     h1_pfHT_nominalHT250_l1monitoring->Fill(pfHT) ;
     if (pfDeltaEtajj > -1 && pfDeltaEtajj < 1.3) h1_pfMjj_nominalHT250_l1monitoring->Fill(pfMjj) ;
     h1_pfDeltaEtajj_nominalHT250_l1monitoring->Fill(pfDeltaEtajj) ;
     if (pfDeltaEtajjWide > -1 && pfDeltaEtajjWide < 1.3) h1_pfMjjWide_nominalHT250_l1monitoring->Fill(pfMjjWide) ;
     h1_pfDeltaEtajjWide_nominalHT250_l1monitoring->Fill(pfDeltaEtajjWide) ;
     
     h1_recoHT_nominalHT250_l1monitoring->Fill(recoHT) ;
     if (recoDeltaEtajj > -1 && recoDeltaEtajj < 1.3) h1_recoMjj_nominalHT250_l1monitoring->Fill(recoMjj) ;
     h1_recoDeltaEtajj_nominalHT250_l1monitoring->Fill(recoDeltaEtajj) ;
     if (recoDeltaEtajjWide > -1 && recoDeltaEtajjWide < 1.3) h1_recoMjjWide_nominalHT250_l1monitoring->Fill(recoMjjWide) ;
     h1_recoDeltaEtajjWide_nominalHT250_l1monitoring->Fill(recoDeltaEtajjWide) ;
   }
   if (passNominalHT410Trig && passMonitoringTrig) {
     h1_caloHT_nominalHT410_monitoring->Fill(caloHT) ;
     if (caloDeltaEtajj > -1 && caloDeltaEtajj < 1.3) h1_caloMjj_nominalHT410_monitoring->Fill(caloMjj) ;
     h1_caloDeltaEtajj_nominalHT410_monitoring->Fill(caloDeltaEtajj) ;
     if (caloDeltaEtajjWide > -1 && caloDeltaEtajjWide < 1.3) h1_caloMjjWide_nominalHT410_monitoring->Fill(caloMjjWide) ;
     h1_caloDeltaEtajjWide_nominalHT410_monitoring->Fill(caloDeltaEtajjWide) ;
     
     h1_pfHT_nominalHT410_monitoring->Fill(pfHT) ;
     if (pfDeltaEtajj > -1 && pfDeltaEtajj < 1.3) h1_pfMjj_nominalHT410_monitoring->Fill(pfMjj) ;
     h1_pfDeltaEtajj_nominalHT410_monitoring->Fill(pfDeltaEtajj) ;
     if (pfDeltaEtajjWide > -1 && pfDeltaEtajjWide < 1.3) h1_pfMjjWide_nominalHT410_monitoring->Fill(pfMjjWide) ;
     h1_pfDeltaEtajjWide_nominalHT410_monitoring->Fill(pfDeltaEtajjWide) ;
     
     h1_recoHT_nominalHT410_monitoring->Fill(recoHT) ;
     if (recoDeltaEtajj > -1 && recoDeltaEtajj < 1.3) h1_recoMjj_nominalHT410_monitoring->Fill(recoMjj) ;
     h1_recoDeltaEtajj_nominalHT410_monitoring->Fill(recoDeltaEtajj) ;
     if (recoDeltaEtajjWide > -1 && recoDeltaEtajjWide < 1.3) h1_recoMjjWide_nominalHT410_monitoring->Fill(recoMjjWide) ;
     h1_recoDeltaEtajjWide_nominalHT410_monitoring->Fill(recoDeltaEtajjWide) ;
   }
   if (passNominalHT410Trig && passL1MonitoringTrig) {
     h1_caloHT_nominalHT410_l1monitoring->Fill(caloHT) ;
     if (caloDeltaEtajj > -1 && caloDeltaEtajj < 1.3) h1_caloMjj_nominalHT410_l1monitoring->Fill(caloMjj) ;
     h1_caloDeltaEtajj_nominalHT410_l1monitoring->Fill(caloDeltaEtajj) ;
     if (caloDeltaEtajjWide > -1 && caloDeltaEtajjWide < 1.3) h1_caloMjjWide_nominalHT410_l1monitoring->Fill(caloMjjWide) ;
     h1_caloDeltaEtajjWide_nominalHT410_l1monitoring->Fill(caloDeltaEtajjWide) ;
     
     h1_pfHT_nominalHT410_l1monitoring->Fill(pfHT) ;
     if (pfDeltaEtajj > -1 && pfDeltaEtajj < 1.3) h1_pfMjj_nominalHT410_l1monitoring->Fill(pfMjj) ;
     h1_pfDeltaEtajj_nominalHT410_l1monitoring->Fill(pfDeltaEtajj) ;
     if (pfDeltaEtajjWide > -1 && pfDeltaEtajjWide < 1.3) h1_pfMjjWide_nominalHT410_l1monitoring->Fill(pfMjjWide) ;
     h1_pfDeltaEtajjWide_nominalHT410_l1monitoring->Fill(pfDeltaEtajjWide) ;
     
     h1_recoHT_nominalHT410_l1monitoring->Fill(recoHT) ;
     if (recoDeltaEtajj > -1 && recoDeltaEtajj < 1.3) h1_recoMjj_nominalHT410_l1monitoring->Fill(recoMjj) ;
     h1_recoDeltaEtajj_nominalHT410_l1monitoring->Fill(recoDeltaEtajj) ;
     if (recoDeltaEtajjWide > -1 && recoDeltaEtajjWide < 1.3) h1_recoMjjWide_nominalHT410_l1monitoring->Fill(recoMjjWide) ;
     h1_recoDeltaEtajjWide_nominalHT410_l1monitoring->Fill(recoDeltaEtajjWide) ;
   }
   if (passNominalHT250Trig) {
     h1_caloHT_nominalHT250->Fill(caloHT) ;
     if (caloDeltaEtajj > -1 && caloDeltaEtajj < 1.3) h1_caloMjj_nominalHT250->Fill(caloMjj) ;
     h1_caloDeltaEtajj_nominalHT250->Fill(caloDeltaEtajj) ;
     if (caloDeltaEtajjWide > -1 && caloDeltaEtajjWide < 1.3) h1_caloMjjWide_nominalHT250->Fill(caloMjjWide) ;
     h1_caloDeltaEtajjWide_nominalHT250->Fill(caloDeltaEtajjWide) ;
     
     h1_pfHT_nominalHT250->Fill(pfHT) ;
     if (pfDeltaEtajj > -1 && pfDeltaEtajj < 1.3) h1_pfMjj_nominalHT250->Fill(pfMjj) ;
     h1_pfDeltaEtajj_nominalHT250->Fill(pfDeltaEtajj) ;
     if (pfDeltaEtajjWide > -1 && pfDeltaEtajjWide < 1.3) h1_pfMjjWide_nominalHT250->Fill(pfMjjWide) ;
     h1_pfDeltaEtajjWide_nominalHT250->Fill(pfDeltaEtajjWide) ;
     
     h1_recoHT_nominalHT250->Fill(recoHT) ;
     if (recoDeltaEtajj > -1 && recoDeltaEtajj < 1.3) h1_recoMjj_nominalHT250->Fill(recoMjj) ;
     h1_recoDeltaEtajj_nominalHT250->Fill(recoDeltaEtajj) ;
     if (recoDeltaEtajjWide > -1 && recoDeltaEtajjWide < 1.3) h1_recoMjjWide_nominalHT250->Fill(recoMjjWide) ;
     h1_recoDeltaEtajjWide_nominalHT250->Fill(recoDeltaEtajjWide) ;
   }
   if (passNominalHT410Trig) {
     h1_caloHT_nominalHT410->Fill(caloHT) ;
     if (caloDeltaEtajj > -1 && caloDeltaEtajj < 1.3) h1_caloMjj_nominalHT410->Fill(caloMjj) ;
     h1_caloDeltaEtajj_nominalHT410->Fill(caloDeltaEtajj) ;
     if (caloDeltaEtajjWide > -1 && caloDeltaEtajjWide < 1.3) h1_caloMjjWide_nominalHT410->Fill(caloMjjWide) ;
     h1_caloDeltaEtajjWide_nominalHT410->Fill(caloDeltaEtajjWide) ;
     
     h1_pfHT_nominalHT410->Fill(pfHT) ;
     if (pfDeltaEtajj > -1 && pfDeltaEtajj < 1.3) h1_pfMjj_nominalHT410->Fill(pfMjj) ;
     h1_pfDeltaEtajj_nominalHT410->Fill(pfDeltaEtajj) ;
     if (pfDeltaEtajjWide > -1 && pfDeltaEtajjWide < 1.3) h1_pfMjjWide_nominalHT410->Fill(pfMjjWide) ;
     h1_pfDeltaEtajjWide_nominalHT410->Fill(pfDeltaEtajjWide) ;
     
     h1_recoHT_nominalHT410->Fill(recoHT) ;
     if (recoDeltaEtajj > -1 && recoDeltaEtajj < 1.3) h1_recoMjj_nominalHT410->Fill(recoMjj) ;
     h1_recoDeltaEtajj_nominalHT410->Fill(recoDeltaEtajj) ;
     if (recoDeltaEtajjWide > -1 && recoDeltaEtajjWide < 1.3) h1_recoMjjWide_nominalHT410->Fill(recoMjjWide) ;
     h1_recoDeltaEtajjWide_nominalHT410->Fill(recoDeltaEtajjWide) ;
   }
   if (passMonitoringTrig) {
     h1_caloHT_monitoring->Fill(caloHT) ;
     if (caloDeltaEtajj > -1 && caloDeltaEtajj < 1.3) h1_caloMjj_monitoring->Fill(caloMjj) ;
     h1_caloDeltaEtajj_monitoring->Fill(caloDeltaEtajj) ;
     if (caloDeltaEtajjWide > -1 && caloDeltaEtajjWide < 1.3) h1_caloMjjWide_monitoring->Fill(caloMjjWide) ;
     h1_caloDeltaEtajjWide_monitoring->Fill(caloDeltaEtajjWide) ;
     
     h1_pfHT_monitoring->Fill(pfHT) ;
     if (pfDeltaEtajj > -1 && pfDeltaEtajj < 1.3) h1_pfMjj_monitoring->Fill(pfMjj) ;
     h1_pfDeltaEtajj_monitoring->Fill(pfDeltaEtajj) ;
     if (pfDeltaEtajjWide > -1 && pfDeltaEtajjWide < 1.3) h1_pfMjjWide_monitoring->Fill(pfMjjWide) ;
     h1_pfDeltaEtajjWide_monitoring->Fill(pfDeltaEtajjWide) ;
     
     h1_recoHT_monitoring->Fill(recoHT) ;
     if (recoDeltaEtajj > -1 && recoDeltaEtajj < 1.3) h1_recoMjj_monitoring->Fill(recoMjj) ;
     h1_recoDeltaEtajj_monitoring->Fill(recoDeltaEtajj) ;
     if (recoDeltaEtajjWide > -1 && recoDeltaEtajjWide < 1.3) h1_recoMjjWide_monitoring->Fill(recoMjjWide) ;
     h1_recoDeltaEtajjWide_monitoring->Fill(recoDeltaEtajjWide) ;
   }
   if (passL1MonitoringTrig) {
     h1_caloHT_l1monitoring->Fill(caloHT) ;
     if (caloDeltaEtajj > -1 && caloDeltaEtajj < 1.3) h1_caloMjj_l1monitoring->Fill(caloMjj) ;
     h1_caloDeltaEtajj_l1monitoring->Fill(caloDeltaEtajj) ;
     if (caloDeltaEtajjWide > -1 && caloDeltaEtajjWide < 1.3) h1_caloMjjWide_l1monitoring->Fill(caloMjjWide) ;
     h1_caloDeltaEtajjWide_l1monitoring->Fill(caloDeltaEtajjWide) ;
     
     h1_pfHT_l1monitoring->Fill(pfHT) ;
     if (pfDeltaEtajj > -1 && pfDeltaEtajj < 1.3) h1_pfMjj_l1monitoring->Fill(pfMjj) ;
     h1_pfDeltaEtajj_l1monitoring->Fill(pfDeltaEtajj) ;
     if (pfDeltaEtajjWide > -1 && pfDeltaEtajjWide < 1.3) h1_pfMjjWide_l1monitoring->Fill(pfMjjWide) ;
     h1_pfDeltaEtajjWide_l1monitoring->Fill(pfDeltaEtajjWide) ;
     
     h1_recoHT_l1monitoring->Fill(recoHT) ;
     if (recoDeltaEtajj > -1 && recoDeltaEtajj < 1.3) h1_recoMjj_l1monitoring->Fill(recoMjj) ;
     h1_recoDeltaEtajj_l1monitoring->Fill(recoDeltaEtajj) ;
     if (recoDeltaEtajjWide > -1 && recoDeltaEtajjWide < 1.3) h1_recoMjjWide_l1monitoring->Fill(recoMjjWide) ;
     h1_recoDeltaEtajjWide_l1monitoring->Fill(recoDeltaEtajjWide) ;
   }

   tree->Fill();
   

#ifdef THIS_IS_AN_EVENT_EXAMPLE
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);
#endif
   
#ifdef THIS_IS_AN_EVENTSETUP_EXAMPLE
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
#endif
}


// ------------ method called once each job just before starting event loop  ------------
void 
HTScoutingL1Analyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HTScoutingL1Analyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HTScoutingL1Analyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HTScoutingL1Analyzer);
