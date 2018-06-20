// -*- C++ -*-
//
// Package:    Analyzer/HTScoutingJetMatchAnalyzer
// Class:      HTScoutingJetMatchAnalyzer
// 
/**\class HTScoutingJetMatchAnalyzer HTScoutingJetMatchAnalyzer.cc Analyzer/HTScoutingJetMatchAnalyzer/plugins/HTScoutingJetMatchAnalyzer.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Jiajing Mao
//         Created:  Wed, 20 Jun 2018
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
#include "FWCore/Common/interface/TriggerResultsByName.h"
#include "DataFormats/Common/interface/TriggerResults.h"
#include "DataFormats/HLTReco/interface/TriggerEvent.h"
#include "DataFormats/HLTReco/interface/TriggerTypeDefs.h"
#include "DataFormats/HLTReco/interface/TriggerObject.h"
#include "DataFormats/VertexReco/interface/Vertex.h"
#include "DataFormats/VertexReco/interface/VertexFwd.h"
#include "DataFormats/Scouting/interface/ScoutingMuon.h"
#include "DataFormats/Scouting/interface/ScoutingPFJet.h"
#include "DataFormats/Scouting/interface/ScoutingCaloJet.h"
#include "DataFormats/PatCandidates/interface/Jet.h"
#include "DataFormats/PatCandidates/interface/MET.h"
#include "DataFormats/PatCandidates/interface/Muon.h"
//#include "DataFormats/PatCandidates/interface/TriggerPrimitive.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include <TLorentzVector.h>
#include "TH1.h"
#include "HLTrigger/HLTcore/interface/HLTConfigProvider.h"

#include "Math/VectorUtil.h"

#include <cassert>

using namespace reco;
using namespace edm;


class HTScoutingJetMatchAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
        typedef math::XYZTLorentzVectorF LorentzVector;

   public:
      explicit HTScoutingJetMatchAnalyzer(const edm::ParameterSet&);
      ~HTScoutingJetMatchAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

  // ----------member data ---------------------------
  edm::EDGetTokenT<edm::TriggerResults>            trgResultsLabel_;
  edm::EDGetTokenT<pat::TriggerObjectStandAloneCollection> trgObjStandAloneLabel_;
  edm::EDGetTokenT<ScoutingCaloJetCollection>      caloJetLabel_;
  edm::EDGetTokenT<double>                         caloRhoLabel_;
  edm::EDGetTokenT<ScoutingPFJetCollection>        pfJetLabel_;
  edm::EDGetTokenT<pat::JetCollection>             recoJetLabel_;
  edm::EDGetTokenT<ScoutingMuonCollection>         muonLabel_;
  edm::Service<TFileService> fs;
  //edm::OwnVector<pat::TriggerPrimitive> patTriggerPrimitivesOwned_myTrigObjects_;

  std::string   processName_;
  std::string triggerName_;

  double tagPt_;
  double tagEta_;
  double probePt_;
  double probeEta_;

  HLTConfigProvider hltConfig_;

  int passNominalHT250Trig;
  int passNominalHT410Trig;
  int passMonitoringTrig;
  double caloRho;
  double caloHT;
  double caloMjj;
  double caloDeltaEtajj;
  double caloMjjWide; 
  double caloDeltaEtajjWide;
  double caloDeltaPhijjWide;
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
  double trgmatchMjj;
  double trgmatchDeltaEtajj;

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

  // trg match hists
  TH1F *h1_trgmatchMjj_nominalHT250_monitoring;
  TH1F *h1_trgmatchMjj_nominalHT410_monitoring;
  TH1F *h1_trgmatchMjj_monitoring;
  TH1F *h1_trgmatchMjj_nominalHT250;
  TH1F *h1_trgmatchMjj_nominalHT410;

  // for JECs
  bool doJECs_;
  edm::FileInPath L1corrAK4_DATA_, L2corrAK4_DATA_, L3corrAK4_DATA_,ResCorrAK4_DATA_;
  JetCorrectorParameters *L1ParAK4_DATA;
  JetCorrectorParameters *L2ParAK4_DATA;
  JetCorrectorParameters *L3ParAK4_DATA;
  JetCorrectorParameters *L2L3ResAK4_DATA;
  FactorizedJetCorrector *JetCorrectorAK4_DATA;
};

HTScoutingJetMatchAnalyzer::HTScoutingJetMatchAnalyzer(const edm::ParameterSet& iConfig)

{
  processName_             = iConfig.getUntrackedParameter<std::string>("processName","HLT");
  triggerName_         = iConfig.getUntrackedParameter<std::string>("triggerName","DST_CaloJet40_CaloBTagScouting_v14");
  doJECs_                  = iConfig.getParameter<bool>("doJECs");
  L1corrAK4_DATA_          = iConfig.getParameter<edm::FileInPath>("L1corrAK4_DATA");
  L2corrAK4_DATA_          = iConfig.getParameter<edm::FileInPath>("L2corrAK4_DATA");
  L3corrAK4_DATA_          = iConfig.getParameter<edm::FileInPath>("L3corrAK4_DATA");
  caloRhoLabel_            = consumes<double>(iConfig.getParameter<edm::InputTag>("caloRho")),
  trgResultsLabel_         = consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerResults"));
  trgObjStandAloneLabel_ = consumes<pat::TriggerObjectStandAloneCollection> (iConfig.getUntrackedParameter<edm::InputTag>("triggerObjectsStandAlone", edm::InputTag("selectedPatTrigger")));
  caloJetLabel_            = consumes<ScoutingCaloJetCollection>(iConfig.getParameter<edm::InputTag>("caloJets"));
  pfJetLabel_              = consumes<ScoutingPFJetCollection>(iConfig.getParameter<edm::InputTag>("pfJets"));
  recoJetLabel_            = consumes<pat::JetCollection>(iConfig.getParameter<edm::InputTag>("recoJets"));
  muonLabel_               = consumes<ScoutingMuonCollection>(iConfig.getParameter<edm::InputTag>("muons"));
  usesResource("TFileService");

  tagPt_ = iConfig.getUntrackedParameter<double>("tagPt",60.);
  tagEta_ = iConfig.getUntrackedParameter<double>("tagEta",2.4);
  probePt_ = iConfig.getUntrackedParameter<double>("probePt",50.);
  probeEta_ = iConfig.getUntrackedParameter<double>("probeEta",2.4);


  TFileDirectory histoDir = fs->mkdir("histoDir");

  h1_caloHT_nominalHT250_monitoring = histoDir.make<TH1F>("caloHT_nominalHT250_monitoring", "caloHT_nominalHT250_monitoring", 14000, 0, 14000);
  h1_caloHT_nominalHT250            = histoDir.make<TH1F>("caloHT_nominalHT250", "caloHT_nominalHT250", 14000, 0, 14000);
  h1_caloHT_nominalHT410_monitoring = histoDir.make<TH1F>("caloHT_nominalHT410_monitoring", "caloHT_nominalHT410_monitoring", 14000, 0, 14000);
  h1_caloHT_nominalHT410            = histoDir.make<TH1F>("caloHT_nominalHT410", "caloHT_nominalHT410", 14000, 0, 14000);
  h1_caloHT_monitoring         = histoDir.make<TH1F>("caloHT_monitoring", "caloHT_monitoring", 14000, 0, 14000);

  h1_caloMjj_nominalHT250_monitoring = histoDir.make<TH1F>("caloMjj_nominalHT250_monitoring", "caloMjj_nominalHT250_monitoring", 14000, 0, 14000);
  h1_caloMjj_nominalHT250            = histoDir.make<TH1F>("caloMjj_nominalHT250", "caloMjj_nominalHT250", 14000, 0, 14000);
  h1_caloMjj_nominalHT410_monitoring = histoDir.make<TH1F>("caloMjj_nominalHT410_monitoring", "caloMjj_nominalHT410_monitoring", 14000, 0, 14000);
  h1_caloMjj_nominalHT410            = histoDir.make<TH1F>("caloMjj_nominalHT410", "caloMjj_nominalHT410", 14000, 0, 14000);
  h1_caloMjj_monitoring         = histoDir.make<TH1F>("caloMjj_monitoring", "caloMjj_monitoring", 14000, 0, 14000);
  
  h1_caloDeltaEtajj_nominalHT250_monitoring = histoDir.make<TH1F>("caloDeltaEtajj_nominalHT250_monitoring", "caloDeltaEtajj_nominalHT250_monitoring", 1000, 0, 5);
  h1_caloDeltaEtajj_nominalHT250            = histoDir.make<TH1F>("caloDeltaEtajj_nominalHT250", "caloDeltaEtajj_nominalHT250", 1000, 0, 5);
  h1_caloDeltaEtajj_nominalHT410_monitoring = histoDir.make<TH1F>("caloDeltaEtajj_nominalHT410_monitoring", "caloDeltaEtajj_nominalHT410_monitoring", 1000, 0, 5);
  h1_caloDeltaEtajj_nominalHT410            = histoDir.make<TH1F>("caloDeltaEtajj_nominalHT410", "caloDeltaEtajj_nominalHT410", 1000, 0, 5);
  h1_caloDeltaEtajj_monitoring         = histoDir.make<TH1F>("caloDeltaEtajj_monitoring", "caloDeltaEtajj_monitoring", 1000, 0, 5);
  
  h1_caloMjjWide_nominalHT250_monitoring = histoDir.make<TH1F>("caloMjjWide_nominalHT250_monitoring", "caloMjjWide_nominalHT250_monitoring", 14000, 0, 14000);
  h1_caloMjjWide_nominalHT250            = histoDir.make<TH1F>("caloMjjWide_nominalHT250", "caloMjjWide_nominalHT250", 14000, 0, 14000);
  h1_caloMjjWide_nominalHT410_monitoring = histoDir.make<TH1F>("caloMjjWide_nominalHT410_monitoring", "caloMjjWide_nominalHT410_monitoring", 14000, 0, 14000);
  h1_caloMjjWide_nominalHT410            = histoDir.make<TH1F>("caloMjjWide_nominalHT410", "caloMjjWide_nominalHT410", 14000, 0, 14000);
  h1_caloMjjWide_monitoring         = histoDir.make<TH1F>("caloMjjWide_monitoring", "caloMjjWide_monitoring", 14000, 0, 14000);
  
  h1_caloDeltaEtajjWide_nominalHT250_monitoring = histoDir.make<TH1F>("caloDeltaEtajjWide_nominalHT250_monitoring", "caloDeltaEtajjWide_nominalHT250_monitoring", 1000, 0, 5);
  h1_caloDeltaEtajjWide_nominalHT250            = histoDir.make<TH1F>("caloDeltaEtajjWide_nominalHT250", "caloDeltaEtajjWide_nominalHT250", 1000, 0, 5);
  h1_caloDeltaEtajjWide_nominalHT410_monitoring = histoDir.make<TH1F>("caloDeltaEtajjWide_nominalHT410_monitoring", "caloDeltaEtajjWide_nominalHT410_monitoring", 1000, 0, 5);
  h1_caloDeltaEtajjWide_nominalHT410            = histoDir.make<TH1F>("caloDeltaEtajjWide_nominalHT410", "caloDeltaEtajjWide_nominalHT410", 1000, 0, 5);
  h1_caloDeltaEtajjWide_monitoring         = histoDir.make<TH1F>("caloDeltaEtajjWide_monitoring", "caloDeltaEtajjWide_monitoring", 1000, 0, 5);

  h1_pfHT_nominalHT250_monitoring = histoDir.make<TH1F>("pfHT_nominalHT250_monitoring", "pfHT_nominalHT250_monitoring", 14000, 0, 14000);
  h1_pfHT_nominalHT250            = histoDir.make<TH1F>("pfHT_nominalHT250", "pfHT_nominalHT250", 14000, 0, 14000);
  h1_pfHT_nominalHT410_monitoring = histoDir.make<TH1F>("pfHT_nominalHT410_monitoring", "pfHT_nominalHT410_monitoring", 14000, 0, 14000);
  h1_pfHT_nominalHT410            = histoDir.make<TH1F>("pfHT_nominalHT410", "pfHT_nominalHT410", 14000, 0, 14000);
  h1_pfHT_monitoring         = histoDir.make<TH1F>("pfHT_monitoring", "pfHT_monitoring", 14000, 0, 14000);

  h1_pfMjj_nominalHT250_monitoring = histoDir.make<TH1F>("pfMjj_nominalHT250_monitoring", "pfMjj_nominalHT250_monitoring", 14000, 0, 14000);
  h1_pfMjj_nominalHT250            = histoDir.make<TH1F>("pfMjj_nominalHT250", "pfMjj_nominalHT250", 14000, 0, 14000);
  h1_pfMjj_nominalHT410_monitoring = histoDir.make<TH1F>("pfMjj_nominalHT410_monitoring", "pfMjj_nominalHT410_monitoring", 14000, 0, 14000);
  h1_pfMjj_nominalHT410            = histoDir.make<TH1F>("pfMjj_nominalHT410", "pfMjj_nominalHT410", 14000, 0, 14000);
  h1_pfMjj_monitoring         = histoDir.make<TH1F>("pfMjj_monitoring", "pfMjj_monitoring", 14000, 0, 14000);

  h1_pfDeltaEtajj_nominalHT250_monitoring = histoDir.make<TH1F>("pfDeltaEtajj_nominalHT250_monitoring", "pfDeltaEtajj_nominalHT250_monitoring", 1000, 0, 5);
  h1_pfDeltaEtajj_nominalHT250            = histoDir.make<TH1F>("pfDeltaEtajj_nominalHT250", "pfDeltaEtajj_nominalHT250", 1000, 0, 5);
  h1_pfDeltaEtajj_nominalHT410_monitoring = histoDir.make<TH1F>("pfDeltaEtajj_nominalHT410_monitoring", "pfDeltaEtajj_nominalHT410_monitoring", 1000, 0, 5);
  h1_pfDeltaEtajj_nominalHT410            = histoDir.make<TH1F>("pfDeltaEtajj_nominalHT410", "pfDeltaEtajj_nominalHT410", 1000, 0, 5);
  h1_pfDeltaEtajj_monitoring         = histoDir.make<TH1F>("pfDeltaEtajj_monitoring", "pfDeltaEtajj_monitoring", 1000, 0, 5);
  
  h1_pfMjjWide_nominalHT250_monitoring = histoDir.make<TH1F>("pfMjjWide_nominalHT250_monitoring", "pfMjjWide_nominalHT250_monitoring", 14000, 0, 14000);
  h1_pfMjjWide_nominalHT250            = histoDir.make<TH1F>("pfMjjWide_nominalHT250", "pfMjjWide_nominalHT250", 14000, 0, 14000);
  h1_pfMjjWide_nominalHT410_monitoring = histoDir.make<TH1F>("pfMjjWide_nominalHT410_monitoring", "pfMjjWide_nominalHT410_monitoring", 14000, 0, 14000);
  h1_pfMjjWide_nominalHT410            = histoDir.make<TH1F>("pfMjjWide_nominalHT410", "pfMjjWide_nominalHT410", 14000, 0, 14000);
  h1_pfMjjWide_monitoring         = histoDir.make<TH1F>("pfMjjWide_monitoring", "pfMjjWide_monitoring", 14000, 0, 14000);
  
  h1_pfDeltaEtajjWide_nominalHT250_monitoring = histoDir.make<TH1F>("pfDeltaEtajjWide_nominalHT250_monitoring", "pfDeltaEtajjWide_nominalHT250_monitoring", 1000, 0, 5);
  h1_pfDeltaEtajjWide_nominalHT250            = histoDir.make<TH1F>("pfDeltaEtajjWide_nominalHT250", "pfDeltaEtajjWide_nominalHT250", 1000, 0, 5);
  h1_pfDeltaEtajjWide_nominalHT410_monitoring = histoDir.make<TH1F>("pfDeltaEtajjWide_nominalHT410_monitoring", "pfDeltaEtajjWide_nominalHT410_monitoring", 1000, 0, 5);
  h1_pfDeltaEtajjWide_nominalHT410            = histoDir.make<TH1F>("pfDeltaEtajjWide_nominalHT410", "pfDeltaEtajjWide_nominalHT410", 1000, 0, 5);
  h1_pfDeltaEtajjWide_monitoring         = histoDir.make<TH1F>("pfDeltaEtajjWide_monitoring", "pfDeltaEtajjWide_monitoring", 1000, 0, 5);

  h1_recoHT_nominalHT250_monitoring = histoDir.make<TH1F>("recoHT_nominalHT250_monitoring", "recoHT_nominalHT250_monitoring", 14000, 0, 14000);
  h1_recoHT_nominalHT250            = histoDir.make<TH1F>("recoHT_nominalHT250", "recoHT_nominalHT250", 14000, 0, 14000);
  h1_recoHT_nominalHT410_monitoring = histoDir.make<TH1F>("recoHT_nominalHT410_monitoring", "recoHT_nominalHT410_monitoring", 14000, 0, 14000);
  h1_recoHT_nominalHT410            = histoDir.make<TH1F>("recoHT_nominalHT410", "recoHT_nominalHT410", 14000, 0, 14000);
  h1_recoHT_monitoring         = histoDir.make<TH1F>("recoHT_monitoring", "recoHT_monitoring", 14000, 0, 14000);

  h1_recoMjj_nominalHT250_monitoring = histoDir.make<TH1F>("recoMjj_nominalHT250_monitoring", "recoMjj_nominalHT250_monitoring", 14000, 0, 14000);
  h1_recoMjj_nominalHT250            = histoDir.make<TH1F>("recoMjj_nominalHT250", "recoMjj_nominalHT250", 14000, 0, 14000);
  h1_recoMjj_nominalHT410_monitoring = histoDir.make<TH1F>("recoMjj_nominalHT410_monitoring", "recoMjj_nominalHT410_monitoring", 14000, 0, 14000);
  h1_recoMjj_nominalHT410            = histoDir.make<TH1F>("recoMjj_nominalHT410", "recoMjj_nominalHT410", 14000, 0, 14000);
  h1_recoMjj_monitoring         = histoDir.make<TH1F>("recoMjj_monitoring", "recoMjj_monitoring", 14000, 0, 14000);
  
  h1_recoDeltaEtajj_nominalHT250_monitoring = histoDir.make<TH1F>("recoDeltaEtajj_nominalHT250_monitoring", "recoDeltaEtajj_nominalHT250_monitoring", 1000, 0, 5);
  h1_recoDeltaEtajj_nominalHT250            = histoDir.make<TH1F>("recoDeltaEtajj_nominalHT250", "recoDeltaEtajj_nominalHT250", 1000, 0, 5);
  h1_recoDeltaEtajj_nominalHT410_monitoring = histoDir.make<TH1F>("recoDeltaEtajj_nominalHT410_monitoring", "recoDeltaEtajj_nominalHT410_monitoring", 1000, 0, 5);
  h1_recoDeltaEtajj_nominalHT410            = histoDir.make<TH1F>("recoDeltaEtajj_nominalHT410", "recoDeltaEtajj_nominalHT410", 1000, 0, 5);
  h1_recoDeltaEtajj_monitoring         = histoDir.make<TH1F>("recoDeltaEtajj_monitoring", "recoDeltaEtajj_monitoring", 1000, 0, 5);
  
  h1_recoMjjWide_nominalHT250_monitoring = histoDir.make<TH1F>("recoMjjWide_nominalHT250_monitoring", "recoMjjWide_nominalHT250_monitoring", 14000, 0, 14000);
  h1_recoMjjWide_nominalHT250            = histoDir.make<TH1F>("recoMjjWide_nominalHT250", "recoMjjWide_nominalHT250", 14000, 0, 14000);
  h1_recoMjjWide_nominalHT410_monitoring = histoDir.make<TH1F>("recoMjjWide_nominalHT410_monitoring", "recoMjjWide_nominalHT410_monitoring", 14000, 0, 14000);
  h1_recoMjjWide_nominalHT410            = histoDir.make<TH1F>("recoMjjWide_nominalHT410", "recoMjjWide_nominalHT410", 14000, 0, 14000);
  h1_recoMjjWide_monitoring         = histoDir.make<TH1F>("recoMjjWide_monitoring", "recoMjjWide_monitoring", 14000, 0, 14000);
  
  h1_recoDeltaEtajjWide_nominalHT250_monitoring = histoDir.make<TH1F>("recoDeltaEtajjWide_nominalHT250_monitoring", "recoDeltaEtajjWide_nominalHT250_monitoring", 1000, 0, 5);
  h1_recoDeltaEtajjWide_nominalHT250            = histoDir.make<TH1F>("recoDeltaEtajjWide_nominalHT250", "recoDeltaEtajjWide_nominalHT250", 1000, 0, 5);
  h1_recoDeltaEtajjWide_nominalHT410_monitoring = histoDir.make<TH1F>("recoDeltaEtajjWide_nominalHT410_monitoring", "recoDeltaEtajjWide_nominalHT410_monitoring", 1000, 0, 5);
  h1_recoDeltaEtajjWide_nominalHT410            = histoDir.make<TH1F>("recoDeltaEtajjWide_nominalHT410", "recoDeltaEtajjWide_nominalHT410", 1000, 0, 5);
  h1_recoDeltaEtajjWide_monitoring         = histoDir.make<TH1F>("recoDeltaEtajjWide_monitoring", "recoDeltaEtajjWide_monitoring", 1000, 0, 5);
  
  h1_trgmatchMjj_nominalHT250_monitoring = histoDir.make<TH1F>("trgmatchMjj_nominalHT250_monitoring", "trgmatchMjj_nominalHT250_monitoring", 14000, 0, 14000);
  h1_trgmatchMjj_nominalHT250            = histoDir.make<TH1F>("trgmatchMjj_nominalHT250", "trgmatchMjj_nominalHT250", 14000, 0, 14000);
  h1_trgmatchMjj_nominalHT410_monitoring = histoDir.make<TH1F>("trgmatchMjj_nominalHT410_monitoring", "trgmatchMjj_nominalHT410_monitoring", 14000, 0, 14000);
  h1_trgmatchMjj_nominalHT410            = histoDir.make<TH1F>("trgmatchMjj_nominalHT410", "trgmatchMjj_nominalHT410", 14000, 0, 14000);
  h1_trgmatchMjj_monitoring         = histoDir.make<TH1F>("trgmatchMjj_monitoring", "trgmatchMjj_monitoring", 14000, 0, 14000);

  if (doJECs_) {
    L1ParAK4_DATA = new JetCorrectorParameters(L1corrAK4_DATA_.fullPath());
    L2ParAK4_DATA = new JetCorrectorParameters(L2corrAK4_DATA_.fullPath());
    L3ParAK4_DATA = new JetCorrectorParameters(L3corrAK4_DATA_.fullPath());

    std::vector<JetCorrectorParameters> vParAK4_DATA;
    vParAK4_DATA.push_back(*L1ParAK4_DATA);
    vParAK4_DATA.push_back(*L2ParAK4_DATA);
    vParAK4_DATA.push_back(*L3ParAK4_DATA);

    JetCorrectorAK4_DATA = new FactorizedJetCorrector(vParAK4_DATA);
  }
}



//____________________________________________________________________________
HTScoutingJetMatchAnalyzer::~HTScoutingJetMatchAnalyzer()
{
}

//
// member functions
//
//____________________________________________________________________________
/*
void
HTScoutingJetMatchAnalyzer::beginRun(const edm::Run& iRun, const edm::EventSetup& iSetup)
{
        using namespace std;
        using namespace edm;

        bool changed(true);
        if (hltConfig_.init(iRun,iSetup,processName_,changed)) {
                if (changed) {
                        const unsigned int n(hltConfig_.size());
                        // check if trigger names in (new) config
                        unsigned int triggerIndex(hltConfig_.triggerIndex(triggerName_));
                        if (triggerIndex>=n) {
                                cout << "HTScoutingJetMatchAnalyzer::analyze:"
                                        << " TriggerName " << triggerName_ 
                                        << " not available in config!" << endl;
                        }
                }// if changed
        } else {
                cout << "HTScoutingJetMatchAnalyzer::analyze:"
                        << " config extraction failure with process name "
                        << processName_ << endl;
        }

}
*/

// ------------ method called for each event  ------------
void
HTScoutingJetMatchAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  //std::cout << "\nEVT" << std::endl;
   using namespace edm;
   using namespace std;
   using namespace reco;
   using namespace trigger;

   passNominalHT250Trig=99;
   passNominalHT410Trig=99;
   passMonitoringTrig=99;
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
   trgmatchMjj=-1;
   trgmatchDeltaEtajj=-1;
   edm::Handle<edm::TriggerResults> trgResultsHandle;
   // get event products
   iEvent.getByToken(trgResultsLabel_, trgResultsHandle);
   if (!trgResultsHandle.isValid()) {
           cout << "HTScoutingJetMatchAnalyzer::analyze: Error in getting TriggerResults product from Event!" << endl;
           return;
   }

   edm::Handle<pat::TriggerObjectStandAloneCollection> trgOSA;
   iEvent.getByToken(trgObjStandAloneLabel_,trgOSA);
   if (!trgOSA.isValid()) {
           cout << "Error in getting TriggerObjectStandAlone product from Event!" << endl;
           return;
   }

   // sanity check
   assert(trgResultsHandle->size()==hltConfig_.size());


   // trigger names
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
     
   }
   
   //std::cout << "HT250:" << passNominalHT250Trig << " Mu50:" << passMonitoringTrig << std::endl;
   //std::cout << "HT410:" << passNominalHT410Trig << " Mu50:" << passMonitoringTrig << std::endl;
   

   // retrieve necessary containers 
   edm::Handle<ScoutingMuonCollection> muonHandle;
   iEvent.getByToken(muonLabel_, muonHandle);
   
   edm::Handle<ScoutingCaloJetCollection> caloJetHandle;
   iEvent.getByToken(caloJetLabel_, caloJetHandle);
   
   edm::Handle<double> caloRhoHandle;
   iEvent.getByToken(caloRhoLabel_, caloRhoHandle);
   caloRho = *caloRhoHandle;

   edm::Handle<ScoutingPFJetCollection> pfJetHandle;
   iEvent.getByToken(pfJetLabel_, pfJetHandle);

   edm::Handle<pat::JetCollection> recoJetHandle;
   iEvent.getByToken(recoJetLabel_, recoJetHandle);

    const unsigned int ntrigs(hltConfig_.size());
    const unsigned int triggerIndex(hltConfig_.triggerIndex(triggerName_));
    assert(triggerIndex==iEvent.triggerNames(*trgResultsHandle).triggerIndex(triggerName_));

    // abort on invalid trigger name
    if (triggerIndex>=ntrigs) {
            cout << "HTScoutingJetMatchAnalyzer::analyzeTrigger: path "
                    << triggerName_ << " - not found!" << endl;
            return;
    }

    // accept DST_CaloJet40_CaloBTagScouting_v14
    bool accept = trgResultsHandle->accept(triggerIndex);

   // trigger objects
   std::vector<LorentzVector> trigJets;
   for (size_t i = 0; i < trgNames.size(); ++i) {
        const std::string &name = trgNames.triggerName(i);
        for (pat::TriggerObjectStandAlone obj : *trgOSA) {
                obj.unpackPathNames(name);
                if ( !obj.id(85) ) continue; // jet type id (mu 83 jet 85)
                if ( !obj.hasPathName( name, true, true ) ) continue; // checks if object is associated to last filter (true) and L3 filter (true)
                trigJets.push_back(LorentzVector(obj.p4()));
                cout << "  - pt: " << obj.pt() << ", eta: " << obj.eta() << ", phi: " << obj.phi() << endl;
        } // loop on trigger objects
   } // loop over trigger names

  if (accept && trigJets.size() == 0) {
         cout << "HTScoutingJetMatchAnalyzer::analyzeTrigger: ERROR!! no valid trigger leptons!" << endl;
  }

 //---------------------------------- 
 // reco jets --- trg match
 //---------------------------------- 

  const float dr_trigmatch = 0.4;

  for (pat::JetCollection::const_iterator jet_tag = recoJetHandle->begin(); jet_tag != recoJetHandle->end(); ++jet_tag) {	   
          cout << " - tag cand: pt: " << jet_tag->pt() << ", eta: " << jet_tag->eta()
                  << ", phi: " << jet_tag->phi() << endl;

          // check if jet passes tag cuts
          if (jet_tag->pt() < tagPt_) continue;
          if (fabs(jet_tag->eta()) > tagEta_) continue;

          // check if jet matches trigger
          bool trigmatch_tag = false;
          for (unsigned int itrig=0; itrig < trigJets.size(); ++itrig) {
                  if (ROOT::Math::VectorUtil::DeltaR(jet_tag->p4(),trigJets.at(itrig)) < dr_trigmatch) trigmatch_tag = true;
          }
          if (!trigmatch_tag) continue;

          // good tag jet: look for any probe jets in the event
          for (pat::JetCollection::const_iterator jet_probe = recoJetHandle->begin(); jet_probe != recoJetHandle->end(); ++jet_probe) {	   
                  // make sure probe isn't the same as the tag
                  if (ROOT::Math::VectorUtil::DeltaR(jet_tag->p4(),jet_probe->p4()) < 0.01) continue;

                  // check probe cuts
                  if (jet_probe->pt() < probePt_) continue;
                  if (fabs(jet_probe->eta()) > probeEta_) continue;

                  cout << " - probe cand: pt: " << jet_probe->pt() << ", eta: " << jet_probe->eta()
                          << ", phi: " << jet_probe->phi() << endl;

                  // dijet mass
                  LorentzVector dijet = LorentzVector(jet_tag->p4() + jet_probe->p4());
	          trgmatchMjj = dijet.M();
	          trgmatchDeltaEtajj = fabs((jet_tag->p4()).Eta()-(jet_probe->p4()).Eta());

                  // check if probe jet matches trigger
                  bool trigmatch_probe = false;
                  for (unsigned int itrig=0; itrig < trigJets.size(); ++itrig) {
                          if (ROOT::Math::VectorUtil::DeltaR(jet_probe->p4(),trigJets.at(itrig)) < dr_trigmatch) trigmatch_probe = true;
                  }

          } // loop over probe

  } // loop over tag


  //  _____________________________________
  //  Iteraor of caloJet, pfJet and recoJet
  //  _____________________________________


   //JEC factors
   std::vector<double> jecFactorsAK4;
   // Sort AK4 jets by increasing pT
   std::vector<unsigned> sortedAK4JetIdx;
   std::multimap<double, unsigned> sortedAK4Jets;

   for (ScoutingCaloJetCollection::const_iterator iCj = caloJetHandle->begin(); iCj != caloJetHandle->end(); ++iCj) {	   
     TLorentzVector cj1;
     double correction = 1.0;
     if (doJECs_) {
       JetCorrectorAK4_DATA->setJetEta(iCj->eta());
       JetCorrectorAK4_DATA->setJetPt(iCj->pt());
       JetCorrectorAK4_DATA->setJetA(iCj->jetArea());
       JetCorrectorAK4_DATA->setRho(caloRho);
       correction = JetCorrectorAK4_DATA->getCorrection();
     }
     jecFactorsAK4.push_back(correction);
     cj1.SetPtEtaPhiM(iCj->pt()*correction, iCj->eta(), iCj->phi(), iCj->m());
     sortedAK4Jets.insert(std::make_pair(cj1.Pt(), iCj - caloJetHandle->begin()));
     if (cj1.Pt() > 40. && fabs(cj1.Eta()) < 3.0) caloHT += cj1.Pt();
   }
   // Get jet indices in decreasing pT order
   for (std::multimap<double, unsigned>::const_reverse_iterator it=sortedAK4Jets.rbegin(); it!=sortedAK4Jets.rend(); ++it) {
     sortedAK4JetIdx.push_back(it->second);
   }
   

   for (ScoutingPFJetCollection::const_iterator iCj = pfJetHandle->begin(); iCj != pfJetHandle->end(); ++iCj) {	   
     TLorentzVector cj1;
     cj1.SetPtEtaPhiM(iCj->pt(), iCj->eta(), iCj->phi(), iCj->m());
     if (iCj->pt() > 40. && fabs(iCj->eta()) < 3.0) pfHT += iCj->pt();
   }

   for (pat::JetCollection::const_iterator iCj = recoJetHandle->begin(); iCj != recoJetHandle->end(); ++iCj) {	   
     TLorentzVector cj1;
     cj1.SetPtEtaPhiM(iCj->pt(), iCj->eta(), iCj->phi(), iCj->mass());
     if (iCj->pt() > 40. && fabs(iCj->eta()) < 3.0) recoHT += iCj->pt();
   }
      
  //  _____________________________________
  //  wide jet
  //  _____________________________________

   double wideJetDeltaR_ = 1.1;

   if (caloJetHandle->size() > 2){     
     TLorentzVector wj1, wj2, wdijet;
     TLorentzVector wj1_tmp, wj2_tmp;
     const ScoutingCaloJet & iCj = (*caloJetHandle)[ sortedAK4JetIdx[0] ];
     const ScoutingCaloJet & jCj = (*caloJetHandle)[ sortedAK4JetIdx[1] ];
     TLorentzVector jet1, jet2;
     jet1.SetPtEtaPhiM(jecFactorsAK4[ sortedAK4JetIdx[0] ]*(iCj.pt()), iCj.eta(), iCj.phi(), iCj.m());
     jet2.SetPtEtaPhiM(jecFactorsAK4[ sortedAK4JetIdx[1] ]*(jCj.pt()), jCj.eta(), jCj.phi(), jCj.m());
     if (jet1.Pt() > 60. && fabs(jet1.Eta()) < 2.5) {	 
       if (jet2.Pt() > 30. && fabs(jet2.Eta()) < 2.5) {
	 caloMjj = (jet1+jet2).M();
	 caloDeltaEtajj = fabs(jet1.Eta()-jet2.Eta());
	 for(size_t ijet=0; ijet<caloJetHandle->size(); ijet++) {
	   const ScoutingCaloJet & kCj = (*caloJetHandle)[ sortedAK4JetIdx[ijet] ];
	   TLorentzVector currentJet;
	   currentJet.SetPtEtaPhiM(jecFactorsAK4[ sortedAK4JetIdx[ijet] ]*(kCj.pt()), kCj.eta(), kCj.phi(), kCj.m());	     
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

   if (pfJetHandle->size() > 2){     
     TLorentzVector wj1, wj2, wdijet;
     TLorentzVector wj1_tmp, wj2_tmp;
     const ScoutingPFJet & iCj = (*pfJetHandle)[ 0 ];
     const ScoutingPFJet & jCj = (*pfJetHandle)[ 1 ];
     if (iCj.pt() > 60. && fabs(iCj.eta()) < 2.5) {	 
       if (jCj.pt() > 30. && fabs(jCj.eta()) < 2.5) {
	 TLorentzVector jet1, jet2;
	 jet1.SetPtEtaPhiM(iCj.pt(), iCj.eta(), iCj.phi(), iCj.m());
	 jet2.SetPtEtaPhiM(jCj.pt(), jCj.eta(), jCj.phi(), jCj.m());
	 pfMjj = (jet1+jet2).M();
	 pfDeltaEtajj = fabs(jet1.Eta()-jet2.Eta());
	 for (ScoutingPFJetCollection::const_iterator kCj = pfJetHandle->begin(); kCj != pfJetHandle->end(); ++kCj) {
	   TLorentzVector currentJet;
	   if (kCj->pt() > 30. && fabs(kCj->eta()) < 2.5) {
	     currentJet.SetPtEtaPhiM(kCj->pt(), kCj->eta(), kCj->phi(), kCj->m());			   
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

  //  _____________________________________
  //  Fill histograms
  //  _____________________________________
   
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

   // plots for matched reco jets
   
   if (passNominalHT250Trig && accept) {
     if (trgmatchDeltaEtajj > -1 && trgmatchDeltaEtajj < 1.3) h1_trgmatchMjj_nominalHT250_monitoring->Fill(trgmatchMjj) ;
   }
   if (passNominalHT250Trig) {
     if (trgmatchDeltaEtajj > -1 && trgmatchDeltaEtajj < 1.3) h1_trgmatchMjj_nominalHT250->Fill(trgmatchMjj) ;
   }
   if (passNominalHT410Trig && accept) {
     if (trgmatchDeltaEtajj > -1 && trgmatchDeltaEtajj < 1.3) h1_trgmatchMjj_nominalHT410_monitoring->Fill(trgmatchMjj) ;
   }
   if (passNominalHT410Trig) {
     if (trgmatchDeltaEtajj > -1 && trgmatchDeltaEtajj < 1.3) h1_trgmatchMjj_nominalHT410->Fill(trgmatchMjj) ;
   }
   if (accept) {
     if (trgmatchDeltaEtajj > -1 && trgmatchDeltaEtajj < 1.3) h1_trgmatchMjj_monitoring->Fill(trgmatchMjj) ;
   }

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
HTScoutingJetMatchAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HTScoutingJetMatchAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HTScoutingJetMatchAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HTScoutingJetMatchAnalyzer);
