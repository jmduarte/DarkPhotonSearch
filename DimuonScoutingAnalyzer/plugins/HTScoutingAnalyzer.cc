// -*- C++ -*-
//
// Package:    Analyzer/HTScoutingAnalyzer
// Class:      HTScoutingAnalyzer
// 
/**\class HTScoutingAnalyzer HTScoutingAnalyzer.cc Analyzer/HTScoutingAnalyzer/plugins/HTScoutingAnalyzer.cc

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
#include "DataFormats/PatCandidates/interface/Muon.h"
#include "DataFormats/PatCandidates/interface/TriggerObjectStandAlone.h"
#include "DataFormats/PatCandidates/interface/PackedTriggerPrescales.h"
#include <TLorentzVector.h>
#include "TH1.h"

class HTScoutingAnalyzer : public edm::one::EDAnalyzer<edm::one::SharedResources>  {
   public:
      explicit HTScoutingAnalyzer(const edm::ParameterSet&);
      ~HTScoutingAnalyzer();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);


   private:
      virtual void beginJob() override;
      virtual void analyze(const edm::Event&, const edm::EventSetup&) override;
      virtual void endJob() override;

  // ----------member data ---------------------------
  edm::EDGetTokenT<edm::TriggerResults>            trgResultsLabel_;
  edm::EDGetTokenT<ScoutingCaloJetCollection>      caloJetLabel_;
  edm::EDGetTokenT<ScoutingPFJetCollection>        pfJetLabel_;
  edm::EDGetTokenT<ScoutingMuonCollection>         muonLabel_;
  edm::Service<TFileService> fs;

  int passNominalTrig;
  int passMonitoringTrig;
  double HT;
  double mjj;

  TH1F *h1_HT_nominal_monitoring;
  TH1F *h1_HT_monitoring;
  TH1F *h1_HT_nominal;
  TH1F *h1_mjj_nominal_monitoring;
  TH1F *h1_mjj_monitoring;
  TH1F *h1_mjj_nominal;

};


HTScoutingAnalyzer::HTScoutingAnalyzer(const edm::ParameterSet& iConfig)

{
  trgResultsLabel_         = consumes<edm::TriggerResults>(iConfig.getParameter<edm::InputTag>("triggerResults"));
  caloJetLabel_            = consumes<ScoutingCaloJetCollection>(iConfig.getParameter<edm::InputTag>("caloJets"));
  pfJetLabel_              = consumes<ScoutingPFJetCollection>(iConfig.getParameter<edm::InputTag>("pfJets"));
  muonLabel_               = consumes<ScoutingMuonCollection>(iConfig.getParameter<edm::InputTag>("muons"));
  usesResource("TFileService");

  TFileDirectory histoDir = fs->mkdir("histoDir");

  h1_HT_nominal_monitoring = histoDir.make<TH1F>("HT_nominal_monitoring", "HT_nominal_monitoring", 14000, 0, 14000);
  h1_HT_nominal            = histoDir.make<TH1F>("HT_nominal", "HT_nominal", 14000, 0, 14000);
  h1_HT_monitoring         = histoDir.make<TH1F>("HT_monitoring", "HT_monitoring", 14000, 0, 14000);
  
}


HTScoutingAnalyzer::~HTScoutingAnalyzer()
{
}


// ------------ method called for each event  ------------
void
HTScoutingAnalyzer::analyze(const edm::Event& iEvent, const edm::EventSetup& iSetup)
{

  //std::cout << "\nEVT" << std::endl;
   using namespace edm;
   passNominalTrig=99;
   passMonitoringTrig=99;
   HT=0.0;
   mjj=0.0;
   edm::Handle<edm::TriggerResults> trgResultsHandle;
   iEvent.getByToken(trgResultsLabel_, trgResultsHandle);
   
   const edm::TriggerNames &trgNames = iEvent.triggerNames(*trgResultsHandle);

   for (size_t i = 0; i < trgNames.size(); ++i) {
     const std::string &name = trgNames.triggerName(i);
   
     if ( (name.find("DST_HT250_CaloScouting") != std::string::npos )) {
       passNominalTrig=trgResultsHandle->accept(i);
     }
     if ( (name.find("HLT_Mu50") != std::string::npos )) {
       passMonitoringTrig=trgResultsHandle->accept(i);
     }
     
   }
   
   //std::cout << passNominalTrig << " " << passMonitoringTrig << std::endl;
   
   
   edm::Handle<ScoutingMuonCollection> muonHandle;
   iEvent.getByToken(muonLabel_, muonHandle);
   
   edm::Handle<ScoutingCaloJetCollection> caloJetHandle;
   iEvent.getByToken(caloJetLabel_, caloJetHandle);
   
   edm::Handle<ScoutingPFJetCollection> pfJetHandle;
   iEvent.getByToken(pfJetLabel_, pfJetHandle);
   
   
   for (ScoutingCaloJetCollection::const_iterator iCj = caloJetHandle->begin(); iCj != caloJetHandle->end(); ++iCj) {	   
     TLorentzVector cj1;
     cj1.SetPtEtaPhiM(iCj->pt(), iCj->eta(), iCj->phi(), iCj->m());
     if (iCj->pt() > 40. && fabs(iCj->eta()) < 3.0) HT += iCj->pt();
   }

   if (passNominalTrig && passMonitoringTrig) h1_HT_nominal_monitoring->Fill(HT) ;
   if (passNominalTrig) h1_HT_nominal->Fill(HT) ;
   if (passMonitoringTrig) h1_HT_monitoring->Fill(HT) ;


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
HTScoutingAnalyzer::beginJob()
{
}

// ------------ method called once each job just after ending the event loop  ------------
void 
HTScoutingAnalyzer::endJob() 
{
}

// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
HTScoutingAnalyzer::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(HTScoutingAnalyzer);
