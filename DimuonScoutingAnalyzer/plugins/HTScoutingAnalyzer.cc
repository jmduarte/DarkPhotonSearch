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
  double mjjWide; 
  double deltaEtajjWide;
  double deltaPhijjWide;

  TH1F *h1_HT_nominal_monitoring;
  TH1F *h1_HT_monitoring;
  TH1F *h1_HT_nominal;
  TH1F *h1_mjj_nominal_monitoring;
  TH1F *h1_mjj_monitoring;
  TH1F *h1_mjj_nominal;
  TH1F *h1_mjjWide_nominal_monitoring;
  TH1F *h1_mjjWide_monitoring;
  TH1F *h1_mjjWide_nominal;
  TH1F *h1_deltaEtajjWide_nominal_monitoring;
  TH1F *h1_deltaEtajjWide_monitoring;
  TH1F *h1_deltaEtajjWide_nominal;

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

  h1_mjj_nominal_monitoring = histoDir.make<TH1F>("mjj_nominal_monitoring", "mjj_nominal_monitoring", 14000, 0, 14000);
  h1_mjj_nominal            = histoDir.make<TH1F>("mjj_nominal", "mjj_nominal", 14000, 0, 14000);
  h1_mjj_monitoring         = histoDir.make<TH1F>("mjj_monitoring", "mjj_monitoring", 14000, 0, 14000);
  
  h1_mjjWide_nominal_monitoring = histoDir.make<TH1F>("mjjWide_nominal_monitoring", "mjjWide_nominal_monitoring", 14000, 0, 14000);
  h1_mjjWide_nominal            = histoDir.make<TH1F>("mjjWide_nominal", "mjjWide_nominal", 14000, 0, 14000);
  h1_mjjWide_monitoring         = histoDir.make<TH1F>("mjjWide_monitoring", "mjjWide_monitoring", 14000, 0, 14000);
  
  h1_deltaEtajjWide_nominal_monitoring = histoDir.make<TH1F>("deltaEtajjWide_nominal_monitoring", "deltaEtajjWide_nominal_monitoring", 1000, 0, 5);
  h1_deltaEtajjWide_nominal            = histoDir.make<TH1F>("deltaEtajjWide_nominal", "deltaEtajjWide_nominal", 1000, 0, 5);
  h1_deltaEtajjWide_monitoring         = histoDir.make<TH1F>("deltaEtajjWide_monitoring", "deltaEtajjWide_monitoring", 1000, 0, 5);
  
  
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
   mjjWide = 0; 
   deltaEtajjWide = -1;
   deltaPhijjWide = -1;
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

   
   for (ScoutingCaloJetCollection::const_iterator iCj = caloJetHandle->begin(); iCj != caloJetHandle->end(); ++iCj) {
     for (ScoutingCaloJetCollection::const_iterator jCj = iCj+1; jCj != caloJetHandle->end(); ++jCj) {
       if (iCj->pt() > 40. && fabs(iCj->eta()) < 3.0) {	 
	 if (jCj->pt() > 40. && fabs(jCj->eta()) < 3.0) {	   
	   TLorentzVector cj1, cj2 ;
	   cj1.SetPtEtaPhiM(iCj->pt(), iCj->eta(), iCj->phi(), iCj->m());
	   cj2.SetPtEtaPhiM(jCj->pt(), jCj->eta(), jCj->phi(), jCj->m());	   
	   TLorentzVector diJet=cj1+cj2;
	   if (diJet.M()>mjj)   mjj=diJet.M();	   
	 }
       }
     }
   }


   
   TLorentzVector wj1, wj2, wdijet;
   TLorentzVector wj1_tmp, wj2_tmp;
   double wideJetDeltaR_ = 1.1;

   if (caloJetHandle->size() > 2){
     const ScoutingCaloJet & iCj = (*caloJetHandle)[ 0 ];
     const ScoutingCaloJet & jCj = (*caloJetHandle)[ 1 ];
     if (iCj.pt() > 40. && fabs(iCj.eta()) < 3.0) {	 
       if (jCj.pt() > 40. && fabs(jCj.eta()) < 3.0) {
	 TLorentzVector jet1, jet2;
	 jet1.SetPtEtaPhiM(iCj.pt(), iCj.eta(), iCj.phi(), iCj.m());
	 jet2.SetPtEtaPhiM(jCj.pt(), jCj.eta(), jCj.phi(), jCj.m());
	 for (ScoutingCaloJetCollection::const_iterator kCj = caloJetHandle->begin(); kCj != caloJetHandle->end(); ++kCj) {
	   TLorentzVector currentJet;
	   if (kCj->pt() > 40. && fabs(kCj->eta()) < 3.0) {
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
   } // end of two jets.
	 
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
       mjjWide = wdijet.M();
       deltaEtajjWide = fabs(wj1.Eta()-wj2.Eta());
       deltaPhijjWide = fabs(wj1.DeltaPhi(wj2));
     }

   
   if (passNominalTrig && passMonitoringTrig) {
     h1_HT_nominal_monitoring->Fill(HT) ;
     h1_mjj_nominal_monitoring->Fill(mjj) ;
     h1_mjjWide_nominal_monitoring->Fill(mjjWide) ;
     h1_deltaEtajjWide_nominal_monitoring->Fill(deltaEtajjWide) ;
   }
   if (passNominalTrig) {
     h1_HT_nominal->Fill(HT) ;
     h1_mjj_nominal->Fill(mjj) ;
     h1_mjjWide_nominal->Fill(mjjWide) ;
     h1_deltaEtajjWide_nominal->Fill(deltaEtajjWide) ;
   }
   if (passMonitoringTrig) {
     h1_HT_monitoring->Fill(HT) ;
     h1_mjj_monitoring->Fill(mjj) ;
     h1_mjjWide_monitoring->Fill(mjjWide) ;
     h1_deltaEtajjWide_monitoring->Fill(deltaEtajjWide) ;
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
