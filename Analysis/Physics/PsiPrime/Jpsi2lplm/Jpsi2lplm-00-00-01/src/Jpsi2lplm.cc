// -*- C++ -*-
//
//
// Description: J/psi -> Invisible 
//
// Original Author:  SHI Xin <shixin@ihep.ac.cn>
//         Created:  [2016-03-23 Wed 09:12] 
//         Inspired by Zhu Kai and Zhang Chi's code 
//
// Modified to : J/psi -> l+ l- (l=e, mu) by R. Kiuchi
//             : [2017-05-17 Wed 00:33] 


//
// system include files
//


#include "GaudiKernel/Algorithm.h"
#include "GaudiKernel/DeclareFactoryEntries.h"
#include "GaudiKernel/LoadFactoryEntries.h"
#include "GaudiKernel/NTuple.h"
#include "GaudiKernel/Bootstrap.h"

#include "EventModel/EventHeader.h"
#include "EvtRecEvent/EvtRecEvent.h"
#include "EvtRecEvent/EvtRecTrack.h"

#include "CLHEP/Vector/ThreeVector.h"

#include "VertexFit/IVertexDbSvc.h"
#include "VertexFit/Helix.h"
#include "VertexFit/WTrackParameter.h"
#include "VertexFit/VertexFit.h"

#include "ParticleID/ParticleID.h"
#include "McTruth/McParticle.h"


#include <TFile.h>
#include <TH1.h>
#include <TTree.h>

//
// class declaration
//

class Jpsi2lplm : public Algorithm {
  
public:
  Jpsi2lplm(const std::string&, ISvcLocator*);
  ~Jpsi2lplm(); 
  StatusCode initialize();
  StatusCode execute();
  StatusCode finalize();

private:
  // declare r0, z0 cut for charged tracks
  double m_ecms; 
  double m_vr0cut, m_vz0cut;
  // double m_distin_pionlep;
  double m_cha_costheta_cut; 
  double m_total_number_of_charged_max; 
  double m_min_emctime;
  double m_max_emctime;
  double m_gammaCosCut; 
  double m_costheta_barrel_max;
  double m_costheta_endcap_min;
  double m_costheta_endcap_max;
  double m_energy_barrel_min;
  double m_energy_endcap_min;
  double m_photon_iso_angle_min;
  double m_pion_polar_angle_max;
  double m_pion_momentum_max;
  double m_lepton_momentum_min;
  double m_lepton_momentum_max;
  double m_prob_pion_min;
  double m_dipion_mass_min; 
  double m_dipion_mass_max;
  double m_dilepton_mass_min; 
  double m_dilepton_mass_max;
  double m_pipi_costheta_max;
  double m_pipisys_costheta_max; 

  // output file
  std::string m_output_filename;
  bool m_isMonteCarlo; 
  TFile* m_fout; 
  
  // define Histograms
  TH1F* h_evtflw; 
  
  // define Trees
  TTree* m_tree;

  // common info 
  int m_run;
  int m_event;

  // charged tracks
  int m_ncharged;
  int m_npiptrk;
  int m_npimtrk;
  int m_nlptrk;
  int m_nlmtrk;
  double m_trkpip_p; 
  double m_trkpip_px; 
  double m_trkpip_py; 
  double m_trkpip_pz; 
  double m_trkpip_theta; 
  double m_trkpip_phi; 
  double m_trkpip_eraw; 
  
  double m_trkpim_p; 
  double m_trkpim_px; 
  double m_trkpim_py; 
  double m_trkpim_pz; 
  double m_trkpim_theta; 
  double m_trkpim_phi; 
  double m_trkpim_eraw; 

  double m_trklp_p; 
  double m_trklp_px; 
  double m_trklp_py; 
  double m_trklp_pz; 
  double m_trklp_theta; 
  double m_trklp_phi; 
  double m_trklp_eraw; 
  
  double m_trklm_p; 
  double m_trklm_px; 
  double m_trklm_py; 
  double m_trklm_pz; 
  double m_trklm_theta; 
  double m_trklm_phi; 
  double m_trklm_eraw; 

  // neutral tracks
  int m_nshow;
  int m_ngam;
  std::vector<double> *m_raw_gpx; 
  std::vector<double> *m_raw_gpy; 
  std::vector<double> *m_raw_gpz; 
  std::vector<double> *m_raw_ge; 
  
  // vertex 
  double m_vr0;
  double m_vz0;

  // PID info
  double m_prob_pip;
  double m_prob_pim;
  double m_prob_kp;
  double m_prob_km;
  double m_prob_p; 
  double m_prob_pb; 

  // pion info
  double m_pip_px;
  double m_pip_py;
  double m_pip_pz;

  double m_pim_px;
  double m_pim_py;
  double m_pim_pz;

  // lepton info
  double m_lp_px;
  double m_lp_py;
  double m_lp_pz;

  double m_lm_px;
  double m_lm_py;
  double m_lm_pz;

  // fitted pion info
  double m_vtx_pip_px; 
  double m_vtx_pip_py; 
  double m_vtx_pip_pz; 
  double m_vtx_pip_p;
  double m_vtx_pip_e;
  double m_vtx_pip_costheta;
  double m_vtx_pip_phi;

  double m_vtx_pim_px; 
  double m_vtx_pim_py; 
  double m_vtx_pim_pz; 
  double m_vtx_pim_p;
  double m_vtx_pim_e;
  double m_vtx_pim_costheta;
  double m_vtx_pim_phi;

  double m_vtx_mpipi;
  double m_vtx_mrecpipi;
  double m_vtx_cospipi;
  double m_vtx_cos2pisys; 

  // fitted lepton info
  int m_jpsi2elel_flag;
  int m_jpsi2mumu_flag;

  double m_vtx_elp_px; 
  double m_vtx_elp_py; 
  double m_vtx_elp_pz; 
  double m_vtx_elp_p;
  double m_vtx_elp_e;
  double m_vtx_elp_costheta;
  double m_vtx_elp_phi;

  double m_vtx_elm_px; 
  double m_vtx_elm_py; 
  double m_vtx_elm_pz; 
  double m_vtx_elm_p;
  double m_vtx_elm_e;
  double m_vtx_elm_costheta;
  double m_vtx_elm_phi;

  double m_vtx_mup_px; 
  double m_vtx_mup_py; 
  double m_vtx_mup_pz; 
  double m_vtx_mup_p;
  double m_vtx_mup_e;
  double m_vtx_mup_costheta;
  double m_vtx_mup_phi;

  double m_vtx_mum_px; 
  double m_vtx_mum_py; 
  double m_vtx_mum_pz; 
  double m_vtx_mum_p;
  double m_vtx_mum_e;
  double m_vtx_mum_costheta;
  double m_vtx_mum_phi;

  double m_vtx_melel;
  double m_vtx_coselel;
  double m_vtx_cos2elsys; 

  double m_vtx_mmumu;
  double m_vtx_cosmumu;
  double m_vtx_cos2musys; 

    
  // check MDC and EMC match
  long m_pion_mathecd;
  long m_lep_matched;

  // jpsi2invi
  int m_ntrk; 
  int m_npho;

  //  MC truth info
  double m_mc_mom_pip;
  double m_mc_mom_pim;
  double m_mc_mom_mup;
  double m_mc_mom_mum;
  double m_mc_mom_ep;
  double m_mc_mom_em;  
  double m_mc_mom_p;
  double m_mc_mom_pb;
  double m_mc_mom_n;
  double m_mc_mom_nb;
  
  double m_mc_pt_pip;
  double m_mc_pt_pim;
  double m_mc_pt_mup ; 
  double m_mc_pt_mum ; 
  double m_mc_pt_ep ; 
  double m_mc_pt_em ; 
  double m_mc_pt_p ; 
  double m_mc_pt_pb ; 
  double m_mc_pt_n ; 
  double m_mc_pt_nb ;
  
  double m_mc_costhe_mup ; 
  double m_mc_costhe_mum ; 
  double m_mc_costhe_ep ; 
  double m_mc_costhe_em ; 
  double m_mc_costhe_p ; 
  double m_mc_costhe_pb ; 
  double m_mc_costhe_n ; 
  double m_mc_costhe_nb ;
  double m_mc_costhe_pip ; 
  double m_mc_costhe_pim ;
  
  double m_mc_cospipi ; 
  double m_mc_cos2pisys ; 


  // functions
  void book_histogram();
  void book_tree(); 
  void clearVariables();
  bool buildJpsiToLpLm();
  void saveGenInfo(); 
  void saveTrkInfo(EvtRecTrackIterator,
		   EvtRecTrackIterator,
		   EvtRecTrackIterator,
		   EvtRecTrackIterator);
  void savePionInfo(RecMdcKalTrack *,
		    RecMdcKalTrack *);
  void saveLeptonInfo(RecMdcKalTrack *,
		      RecMdcKalTrack *);
  void savePionVtxInfo(HepLorentzVector,
		       HepLorentzVector);  
  void saveLeptonVtxInfo(HepLorentzVector,
			 HepLorentzVector,
			 int);  
  void saveGamInfo(std::vector<int>,
		   SmartDataPtr<EvtRecTrackCol>);
  int selectChargedTracks(SmartDataPtr<EvtRecEvent>,
			  SmartDataPtr<EvtRecTrackCol>,
			  std::vector<int> &,
			  std::vector<int> &,
			  std::vector<int> &,
			  std::vector<int> &); 
  int selectPionPlusPionMinus(SmartDataPtr<EvtRecTrackCol>,
			      std::vector<int>,
			      std::vector<int>);
  int selectLeptonPlusLeptonMinus(SmartDataPtr<EvtRecTrackCol>,
				  std::vector<int>,
				  std::vector<int>);
  void calcTrackPID(EvtRecTrackIterator,
		    double&,
		    double&,
		    double&);
  bool hasGoodPiPiVertex(RecMdcKalTrack *,
			 RecMdcKalTrack *,
			 bool);
  bool hasGoodLpLmVertex(RecMdcKalTrack *,
			 RecMdcKalTrack *,
			 int,
			 bool);
  int selectNeutralTracks(SmartDataPtr<EvtRecEvent>,
			  SmartDataPtr<EvtRecTrackCol>);
  bool passVertexSelection(CLHEP::Hep3Vector,
			   RecMdcKalTrack* ); 
  CLHEP::Hep3Vector getOrigin();
}; 


//
// module declare
//

DECLARE_ALGORITHM_FACTORY( Jpsi2lplm )
DECLARE_FACTORY_ENTRIES( Jpsi2lplm ) {
  DECLARE_ALGORITHM(Jpsi2lplm);
}

LOAD_FACTORY_ENTRIES( Jpsi2lplm )

//
// constants
//

const double PION_MASS = 0.139570;
const double ELECTRON_MASS = 0.000511;
const double MUON_MASS = 0.105658;

const int ELECTRON_PDG_ID = 11;
const int MUON_PDG_ID = 13;
const int PIONPLUS_PDG_ID = 211;

const int JPSI_PDG_ID = 443;
const int PSI2S_PDG_ID = 100443;
const int PROTON_PDG_ID = 2212; 
const int NEUTRON_PDG_ID = 2112; 

const int Electron_Hypothesis_Fit=1;
const int Muon_Hypothesis_Fit=2;

//
// member functions
//
  
Jpsi2lplm::Jpsi2lplm(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator),
  m_tree(0),
  m_raw_gpx(0), 
  m_raw_gpy(0), 
  m_raw_gpz(0), 
  m_raw_ge(0)
{
  declareProperty("OutputFileName", m_output_filename);
  declareProperty("IsMonteCarlo", m_isMonteCarlo);
  declareProperty("Ecms", m_ecms = 3.686);
  declareProperty("Vr0cut", m_vr0cut=1.0);
  declareProperty("Vz0cut", m_vz0cut=10.0);
  declareProperty("ChaCosthetaCut", m_cha_costheta_cut=0.93);
  //declareProperty("ChaCosthetaCut", m_cha_costheta_cut=0.83);
  declareProperty("TotalNumberOfChargedMax", m_total_number_of_charged_max=50);
  declareProperty("MinEstCut", m_min_emctime=0.0);
  declareProperty("MaxEstCut", m_max_emctime=14.0);
  declareProperty("GammaCosCut",  m_gammaCosCut= 0.93); 
  declareProperty("CosthetaBarrelMax", m_costheta_barrel_max=0.8);
  declareProperty("CosthetaEndcapMin", m_costheta_endcap_min=0.86);
  declareProperty("CosthetaEndcapMax", m_costheta_endcap_max=0.92);
  declareProperty("EnergyBarrelMin", m_energy_barrel_min=0.025); 
  declareProperty("EnergyEndcapMin", m_energy_endcap_min=0.050); 
  //declareProperty("EnergyEndcapMin", m_energy_endcap_min=50.0); 
  declareProperty("PhotonIsoAngleMin", m_photon_iso_angle_min=20);
  declareProperty("LeptonMomentumMax", m_lepton_momentum_min=0.6); 
  declareProperty("LeptonMomentumMin", m_lepton_momentum_max=2.5); 
  declareProperty("PionPolarAngleMax", m_pion_polar_angle_max=0.99);
  //declareProperty("PionMomentumMax", m_pion_momentum_max=1.9); 
  declareProperty("PionMomentumMax", m_pion_momentum_max=0.6); 
  declareProperty("ProbPionMin", m_prob_pion_min=0.001);
  declareProperty("DipionMassMin", m_dipion_mass_min=3.0); 
  declareProperty("DipionMassMax", m_dipion_mass_max=3.2); 
  declareProperty("DileptonMassMin", m_dilepton_mass_min=2.5); 
  declareProperty("DileptonMassMax", m_dilepton_mass_max=3.5); 
  declareProperty("PiPiCosthetaMax", m_pipi_costheta_max=0.99);
  declareProperty("PiPiSysCosthetaMax", m_pipisys_costheta_max=0.99);
}


StatusCode Jpsi2lplm::initialize(){
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << ">>>>>>> in initialize()" << endmsg;

  m_fout = new TFile(m_output_filename.c_str(), "RECREATE");
  m_fout->cd(); 

  book_histogram(); 
  book_tree(); 

  log << MSG::INFO << "successfully return from initialize()" <<endmsg;
  return StatusCode::SUCCESS;
}


StatusCode Jpsi2lplm::execute() {
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in execute()" << endreq;
  
  // clear variables
  clearVariables();
  
  h_evtflw->Fill(0); // raw 
  SmartDataPtr<Event::EventHeader>eventHeader(eventSvc(),"/Event/EventHeader");
  if(!eventHeader) return StatusCode::FAILURE;

  m_run = eventHeader->runNumber();
  m_event = eventHeader->eventNumber();
  
  if (buildJpsiToLpLm()) {
    m_tree->Fill(); // only fill tree for the selected events 
  }

  return StatusCode::SUCCESS; 
}

StatusCode Jpsi2lplm::finalize() {
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in finalize()" << endmsg;

  m_fout->cd();
  m_tree->Write();
  h_evtflw->Write();
  m_fout->Close();
  
  return StatusCode::SUCCESS;
}


Jpsi2lplm::~Jpsi2lplm() {
}


void Jpsi2lplm::book_histogram() {

  h_evtflw = new TH1F("hevtflw", "eventflow", 15, 0, 15);
  if (!h_evtflw) return;
  h_evtflw->GetXaxis()->SetBinLabel(1, "raw");
  h_evtflw->GetXaxis()->SetBinLabel(2, "N_{Good}=4");
  h_evtflw->GetXaxis()->SetBinLabel(3, "N_{#gamma}<20");
  h_evtflw->GetXaxis()->SetBinLabel(4, "|cos#theta|<0.99");
  h_evtflw->GetXaxis()->SetBinLabel(5, "pion PID");
  h_evtflw->GetXaxis()->SetBinLabel(6, "cos#theta_{#pi^{+}#pi^{-}}<0.99");
  h_evtflw->GetXaxis()->SetBinLabel(7, "cos#theta_{#pi#pi sys}<0.99");
  h_evtflw->GetXaxis()->SetBinLabel(8, "3<M_{#pi#pi}^{rec}<3.2");
  h_evtflw->GetXaxis()->SetBinLabel(9, "Lepton P<2.0GeV/c");
  h_evtflw->GetXaxis()->SetBinLabel(10, "2.5<M_{ee}<3.5");
  h_evtflw->GetXaxis()->SetBinLabel(11, "2.5<M_{#mu#mu}<3.5");
}


void Jpsi2lplm::book_tree() {

  m_tree=new TTree("tree", "jpsi2lplm");
  if (!m_tree) return; 

  //commom info
  m_tree->Branch("run",&m_run,"run/I");
  m_tree->Branch("event",&m_event,"event/I");
	  
  //charged tracks
  m_tree->Branch("ncharged", &m_ncharged, "ncharged/I");
  m_tree->Branch("npiptrk", &m_npiptrk, "npiptrk/I");
  m_tree->Branch("npimtrk", &m_npimtrk, "npimtrk/I");
  m_tree->Branch("nlptrk", &m_nlptrk, "nlptrk/I");
  m_tree->Branch("nlmtrk", &m_nlmtrk, "nlmtrk/I");

  m_tree->Branch("trkpip_p", &m_trkpip_p, "trkpip_p/D"); 
  m_tree->Branch("trkpip_px", &m_trkpip_px, "trkpip_px/D"); 
  m_tree->Branch("trkpip_py", &m_trkpip_py, "trkpip_py/D"); 
  m_tree->Branch("trkpip_pz", &m_trkpip_pz, "trkpip_pz/D"); 
  m_tree->Branch("trkpip_theta", &m_trkpip_theta, "trkpip_theta/D"); 
  m_tree->Branch("trkpip_phi", &m_trkpip_phi, "trkpip_phi/D"); 
  m_tree->Branch("trkpip_eraw", &m_trkpip_eraw, "trkpip_eraw/D"); 

  m_tree->Branch("trkpim_p", &m_trkpim_p, "trkpim_p/D"); 
  m_tree->Branch("trkpim_px", &m_trkpim_px, "trkpim_px/D"); 
  m_tree->Branch("trkpim_py", &m_trkpim_py, "trkpim_py/D"); 
  m_tree->Branch("trkpim_pz", &m_trkpim_pz, "trkpim_pz/D"); 
  m_tree->Branch("trkpim_theta", &m_trkpim_theta, "trkpim_theta/D"); 
  m_tree->Branch("trkpim_phi", &m_trkpim_phi, "trkpim_phi/D"); 
  m_tree->Branch("trkpim_eraw", &m_trkpim_eraw, "trkpim_eraw/D"); 

  m_tree->Branch("trklp_p", &m_trklp_p, "trklp_p/D"); 
  m_tree->Branch("trklp_px", &m_trklp_px, "trklp_px/D"); 
  m_tree->Branch("trklp_py", &m_trklp_py, "trklp_py/D"); 
  m_tree->Branch("trklp_pz", &m_trklp_pz, "trklp_pz/D"); 
  m_tree->Branch("trklp_theta", &m_trklp_theta, "trklp_theta/D"); 
  m_tree->Branch("trklp_phi", &m_trklp_phi, "trklp_phi/D"); 
  m_tree->Branch("trklp_eraw", &m_trklp_eraw, "trklp_eraw/D"); 

  m_tree->Branch("trklm_p", &m_trklm_p, "trklm_p/D"); 
  m_tree->Branch("trklm_px", &m_trklm_px, "trklm_px/D"); 
  m_tree->Branch("trklm_py", &m_trklm_py, "trklm_py/D"); 
  m_tree->Branch("trklm_pz", &m_trklm_pz, "trklm_pz/D"); 
  m_tree->Branch("trklm_theta", &m_trklm_theta, "trklm_theta/D"); 
  m_tree->Branch("trklm_phi", &m_trklm_phi, "trklm_phi/D"); 
  m_tree->Branch("trklm_eraw", &m_trklm_eraw, "trklm_eraw/D"); 
	  
  //vertex
  m_tree->Branch("vr0", &m_vr0, "vr0/D");
  m_tree->Branch("vz0", &m_vz0, "vz0/D");

	  
  //netual tracks
  m_tree->Branch("nshow", &m_nshow, "nshow/I");
  m_tree->Branch("ngam", &m_ngam, "ngam/I");
  m_tree->Branch("raw_gpx", &m_raw_gpx);
  m_tree->Branch("raw_gpy", &m_raw_gpy);
  m_tree->Branch("raw_gpz", &m_raw_gpz);
  m_tree->Branch("raw_ge", &m_raw_ge);

  // PID info
  m_tree->Branch("prob_pip", &m_prob_pip, "prob_pip/D"); 
  m_tree->Branch("prob_pim", &m_prob_pim, "prob_pim/D"); 
  m_tree->Branch("prob_kp", &m_prob_kp, "prob_kp/D"); 
  m_tree->Branch("prob_km", &m_prob_km, "prob_km/D"); 
  m_tree->Branch("prob_p", &m_prob_p, "prob_p/D"); 
  m_tree->Branch("prob_pb", &m_prob_pb, "prob_pb/D"); 

  // save pion info
  m_tree->Branch("pip_px", &m_pip_px, "pip_px/D");
  m_tree->Branch("pip_py", &m_pip_py, "pip_py/D");
  m_tree->Branch("pip_pz", &m_pip_pz, "pip_pz/D");

  m_tree->Branch("pim_px", &m_pim_px, "pim_px/D");
  m_tree->Branch("pim_py", &m_pim_py, "pim_py/D");
  m_tree->Branch("pim_pz", &m_pim_pz, "pim_pz/D");

  // save lepton info
  m_tree->Branch("lp_px", &m_lp_px, "lp_px/D");
  m_tree->Branch("lp_py", &m_lp_py, "lp_py/D");
  m_tree->Branch("lp_pz", &m_lp_pz, "lp_pz/D");

  m_tree->Branch("lm_px", &m_lm_px, "lm_px/D");
  m_tree->Branch("lm_py", &m_lm_py, "lm_py/D");
  m_tree->Branch("lm_pz", &m_lm_pz, "lm_pz/D");

  // fitted pion info
  m_tree->Branch("vtx_pip_px", &m_vtx_pip_px, "vtx_pip_px/D");
  m_tree->Branch("vtx_pip_py", &m_vtx_pip_py, "vtx_pip_py/D");
  m_tree->Branch("vtx_pip_pz", &m_vtx_pip_pz, "vtx_pip_pz/D");
  m_tree->Branch("vtx_pip_p", &m_vtx_pip_p, "vtx_pip_p/D");
  m_tree->Branch("vtx_pip_e", &m_vtx_pip_e, "vtx_pip_e/D");
  m_tree->Branch("vtx_pip_costheta", &m_vtx_pip_costheta, "vtx_pip_costheta/D");
  m_tree->Branch("vtx_pip_phi", &m_vtx_pip_phi, "vtx_pip_phi/D");
  m_tree->Branch("vtx_pim_px", &m_vtx_pim_px, "vtx_pim_px/D");
  m_tree->Branch("vtx_pim_py", &m_vtx_pim_py, "vtx_pim_py/D");
  m_tree->Branch("vtx_pim_pz", &m_vtx_pim_pz, "vtx_pim_pz/D");
  m_tree->Branch("vtx_pim_p", &m_vtx_pim_p, "vtx_pim_p/D");
  m_tree->Branch("vtx_pim_e", &m_vtx_pim_e, "vtx_pim_e/D");
  m_tree->Branch("vtx_pim_costheta", &m_vtx_pim_costheta, "vtx_pim_costheta/D");
  m_tree->Branch("vtx_pim_phi", &m_vtx_pim_phi, "vtx_pim_phi/D");

  m_tree->Branch("vtx_mpipi", &m_vtx_mpipi, "vtx_mpipi/D");
  m_tree->Branch("vtx_mrecpipi", &m_vtx_mrecpipi, "vtx_mrecpipi/D");
  m_tree->Branch("vtx_cospipi", &m_vtx_cospipi, "vtx_cospipi/D");
  m_tree->Branch("vtx_cos2pisys", &m_vtx_cos2pisys, "vtx_cos2pisys/D");
  

  // fitted lepton info
  m_tree->Branch("jpsi2elel_flag", &m_jpsi2elel_flag, "jpsi2elel_flag/I");
  m_tree->Branch("jpsi2mumu_flag", &m_jpsi2mumu_flag, "jpsi2mumu_flag/I");

  m_tree->Branch("vtx_elp_px", &m_vtx_elp_px, "vtx_elp_px/D");
  m_tree->Branch("vtx_elp_py", &m_vtx_elp_py, "vtx_elp_py/D");
  m_tree->Branch("vtx_elp_pz", &m_vtx_elp_pz, "vtx_elp_pz/D");
  m_tree->Branch("vtx_elp_p", &m_vtx_elp_p, "vtx_elp_p/D");
  m_tree->Branch("vtx_elp_e", &m_vtx_elp_e, "vtx_elp_e/D");
  m_tree->Branch("vtx_elp_costheta", &m_vtx_elp_costheta, "vtx_elp_costheta/D");
  m_tree->Branch("vtx_elp_phi", &m_vtx_elp_phi, "vtx_elp_phi/D");
  m_tree->Branch("vtx_elm_px", &m_vtx_elm_px, "vtx_elm_px/D");
  m_tree->Branch("vtx_elm_py", &m_vtx_elm_py, "vtx_elm_py/D");
  m_tree->Branch("vtx_elm_pz", &m_vtx_elm_pz, "vtx_elm_pz/D");
  m_tree->Branch("vtx_elm_p", &m_vtx_elm_p, "vtx_elm_p/D");
  m_tree->Branch("vtx_elm_e", &m_vtx_elm_e, "vtx_elm_e/D");
  m_tree->Branch("vtx_elm_costheta", &m_vtx_elm_costheta, "vtx_elm_costheta/D");
  m_tree->Branch("vtx_elm_phi", &m_vtx_elm_phi, "vtx_elm_phi/D");

  m_tree->Branch("vtx_mup_px", &m_vtx_mup_px, "vtx_mup_px/D");
  m_tree->Branch("vtx_mup_py", &m_vtx_mup_py, "vtx_mup_py/D");
  m_tree->Branch("vtx_mup_pz", &m_vtx_mup_pz, "vtx_mup_pz/D");
  m_tree->Branch("vtx_mup_p", &m_vtx_mup_p, "vtx_mup_p/D");
  m_tree->Branch("vtx_mup_e", &m_vtx_mup_e, "vtx_mup_e/D");
  m_tree->Branch("vtx_mup_costheta", &m_vtx_mup_costheta, "vtx_mup_costheta/D");
  m_tree->Branch("vtx_mup_phi", &m_vtx_mup_phi, "vtx_mup_phi/D");
  m_tree->Branch("vtx_mum_px", &m_vtx_mum_px, "vtx_mum_px/D");
  m_tree->Branch("vtx_mum_py", &m_vtx_mum_py, "vtx_mum_py/D");
  m_tree->Branch("vtx_mum_pz", &m_vtx_mum_pz, "vtx_mum_pz/D");
  m_tree->Branch("vtx_mum_p", &m_vtx_mum_p, "vtx_mum_p/D");
  m_tree->Branch("vtx_mum_e", &m_vtx_mum_e, "vtx_mum_e/D");
  m_tree->Branch("vtx_mum_costheta", &m_vtx_mum_costheta, "vtx_mum_costheta/D");
  m_tree->Branch("vtx_mum_phi", &m_vtx_mum_phi, "vtx_mum_phi/D");

  m_tree->Branch("vtx_melel", &m_vtx_melel, "vtx_melel/D");
  m_tree->Branch("vtx_coselel", &m_vtx_coselel, "vtx_coselel/D");
  m_tree->Branch("vtx_cos2elsys", &m_vtx_cos2elsys, "vtx_cos2elsys/D");

  m_tree->Branch("vtx_mmumu", &m_vtx_mmumu, "vtx_mmumu/D");
  m_tree->Branch("vtx_cosmumu", &m_vtx_cosmumu, "vtx_cosmumu/D");
  m_tree->Branch("vtx_cos2musys", &m_vtx_cos2musys, "vtx_cos2musys/D");


  // MC truth info
  if (!m_isMonteCarlo) return; 
  m_tree->Branch("mc_mom_pip", &m_mc_mom_pip, "mc_mom_pip/D");
  m_tree->Branch("mc_mom_pim", &m_mc_mom_pim, "mc_mom_pim/D");
  m_tree->Branch("mc_mom_mup", &m_mc_mom_mup, "mc_mom_mup/D");
  m_tree->Branch("mc_mom_mum", &m_mc_mom_mum, "mc_mom_mum/D");
  m_tree->Branch("mc_mom_ep", &m_mc_mom_ep, "mc_mom_ep/D");
  m_tree->Branch("mc_mom_em", &m_mc_mom_em, "mc_mom_em/D");
  m_tree->Branch("mc_mom_p", &m_mc_mom_p, "mc_mom_p/D");
  m_tree->Branch("mc_mom_pb", &m_mc_mom_pb, "mc_mom_pb/D");
  m_tree->Branch("mc_mom_n", &m_mc_mom_n, "mc_mom_n/D");
  m_tree->Branch("mc_mom_nb", &m_mc_mom_nb, "mc_mom_nb/D");
  
  m_tree->Branch("mc_pt_pip", &m_mc_pt_pip, "mc_pt_pip/D");
  m_tree->Branch("mc_pt_pim", &m_mc_pt_pim, "mc_pt_pim/D");
  m_tree->Branch("mc_pt_mup", &m_mc_pt_mup, "mc_pt_mup/D");
  m_tree->Branch("mc_pt_mum", &m_mc_pt_mum, "mc_pt_mum/D");
  m_tree->Branch("mc_pt_ep", &m_mc_pt_ep, "mc_pt_ep/D");
  m_tree->Branch("mc_pt_em", &m_mc_pt_em, "mc_pt_em/D");
  m_tree->Branch("mc_pt_p", &m_mc_pt_p, "mc_pt_p/D");
  m_tree->Branch("mc_pt_pb", &m_mc_pt_pb, "mc_pt_pb/D");
  m_tree->Branch("mc_pt_n", &m_mc_pt_n, "mc_pt_n/D");
  m_tree->Branch("mc_pt_nb", &m_mc_pt_nb, "mc_pt_nb/D");
  
  m_tree->Branch("mc_costhe_pip", &m_mc_costhe_pip, "mc_costhe_pip/D");
  m_tree->Branch("mc_costhe_pim", &m_mc_costhe_pim, "mc_costhe_pim/D");
  m_tree->Branch("mc_costhe_mup", &m_mc_costhe_mup, "mc_costhe_mup/D");
  m_tree->Branch("mc_costhe_mum", &m_mc_costhe_mum, "mc_costhe_mum/D");
  m_tree->Branch("mc_costhe_ep", &m_mc_costhe_ep, "mc_costhe_ep/D");
  m_tree->Branch("mc_costhe_em", &m_mc_costhe_em, "mc_costhe_em/D");
  m_tree->Branch("mc_costhe_p", &m_mc_costhe_p, "mc_costhe_p/D");
  m_tree->Branch("mc_costhe_pb", &m_mc_costhe_pb, "mc_costhe_pb/D");
  m_tree->Branch("mc_costhe_n", &m_mc_costhe_n, "mc_costhe_n/D");
  m_tree->Branch("mc_costhe_nb", &m_mc_costhe_nb, "mc_costhe_nb/D");
    
  m_tree->Branch("mc_cospipi", &m_mc_cospipi, "mc_cospipi/D");
  m_tree->Branch("mc_cos2pisys", &m_mc_cos2pisys, "mc_cos2pisys/D");
  
}

void Jpsi2lplm::clearVariables() {

  m_raw_gpx->clear();
  m_raw_gpy->clear();
  m_raw_gpz->clear();
  m_raw_ge->clear();

  // For electon/muon vertex fitting, it is not guranteed that
  // tree leaf is going to be filled for each event. 
  m_vtx_elp_px=-99; 
  m_vtx_elp_py=-99; 
  m_vtx_elp_pz=-99; 
  m_vtx_elp_p=-99;
  m_vtx_elp_e=-99;
  m_vtx_elp_costheta=-99;
  m_vtx_elp_phi=-99;

  m_vtx_elm_px=-99; 
  m_vtx_elm_py=-99; 
  m_vtx_elm_pz=-99; 
  m_vtx_elm_p=-99;
  m_vtx_elm_e=-99;
  m_vtx_elm_costheta=-99;
  m_vtx_elm_phi=-99;

  m_vtx_mup_px=-99; 
  m_vtx_mup_py=-99; 
  m_vtx_mup_pz=-99; 
  m_vtx_mup_p=-99;
  m_vtx_mup_e=-99;
  m_vtx_mup_costheta=-99;
  m_vtx_mup_phi=-99;

  m_vtx_mum_px=-99; 
  m_vtx_mum_py=-99; 
  m_vtx_mum_pz=-99; 
  m_vtx_mum_p=-99;
  m_vtx_mum_e=-99;
  m_vtx_mum_costheta=-99;
  m_vtx_mum_phi=-99;

  m_vtx_melel=-99;
  m_vtx_coselel=-99;
  m_vtx_cos2elsys=-99; 

  m_vtx_mmumu=-99;
  m_vtx_cosmumu=-99;
  m_vtx_cos2musys=-99; 
}

bool Jpsi2lplm::buildJpsiToLpLm() {

  if (m_isMonteCarlo) saveGenInfo(); 
  
  SmartDataPtr<EvtRecEvent>evtRecEvent(eventSvc(),"/Event/EvtRec/EvtRecEvent");
  if(!evtRecEvent) return false;

  SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(), "/Event/EvtRec/EvtRecTrackCol");
  if(!evtRecTrkCol) return false;

  std::vector<int> iPiPGood, iPiMGood; 
  std::vector<int> iLepPGood, iLepMGood; 
  selectChargedTracks(evtRecEvent, evtRecTrkCol, iPiPGood, iPiMGood, 
		      iLepPGood, iLepMGood);
  //selectChargedTracks(evtRecEvent, evtRecTrkCol, iPGood, iMGood);

  if ( (m_npiptrk != 1) || (m_npimtrk != 1) || (m_nlptrk != 1) || (m_nlmtrk != 1) ) return false;
  h_evtflw->Fill(1); // N_PionP=1, N_PionM=1, N_LeptonP=1, N_LeptonM=1

  if(selectPionPlusPionMinus(evtRecTrkCol, iPiPGood, iPiMGood) != 1) return false; 
  
  if(selectLeptonPlusLeptonMinus(evtRecTrkCol, iLepPGood, iLepMGood) != 1) return false; 

  selectNeutralTracks(evtRecEvent, evtRecTrkCol);
  if (m_ngam >= 20) return false;
  h_evtflw->Fill(2); // N_{#gamma} < 20 
    
  return true; 
}


void Jpsi2lplm::saveGenInfo() {
  SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");
  HepLorentzVector mc_psip,mc_pip,mc_pim,mc_ep,mc_em,mc_mup,mc_mum,mc_p,mc_pb,mc_n,mc_nb,mc_jpsi;

  Event::McParticleCol::iterator iter_mc = mcParticleCol->begin();
  for (; iter_mc != mcParticleCol->end(); iter_mc++){
    if ((*iter_mc)->primaryParticle()) continue;
    if (!(*iter_mc)->decayFromGenerator()) continue;

    if( (*iter_mc)->mother().particleProperty() == PSI2S_PDG_ID) {
      if ( (*iter_mc)->particleProperty() == PIONPLUS_PDG_ID)
	mc_pip = (*iter_mc)->initialFourMomentum();

      if ( (*iter_mc)->particleProperty() == -PIONPLUS_PDG_ID)
	mc_pim = (*iter_mc)->initialFourMomentum();
    }

    if ((*iter_mc)->mother().particleProperty() == JPSI_PDG_ID ) {
      if((*iter_mc)->particleProperty() == -MUON_PDG_ID )
	mc_mup = (*iter_mc)->initialFourMomentum();

      if((*iter_mc)->particleProperty() == MUON_PDG_ID )
	mc_mum = (*iter_mc)->initialFourMomentum();
      
      if((*iter_mc)->particleProperty() == -ELECTRON_PDG_ID )
	mc_ep = (*iter_mc)->initialFourMomentum();

      if((*iter_mc)->particleProperty() == ELECTRON_PDG_ID )
	mc_em = (*iter_mc)->initialFourMomentum();

      if((*iter_mc)->particleProperty() == PROTON_PDG_ID )
	mc_p = (*iter_mc)->initialFourMomentum();

      if((*iter_mc)->particleProperty() == -PROTON_PDG_ID )
	mc_pb = (*iter_mc)->initialFourMomentum();

      if((*iter_mc)->particleProperty() == NEUTRON_PDG_ID )
	mc_n = (*iter_mc)->initialFourMomentum();

      if((*iter_mc)->particleProperty() == -NEUTRON_PDG_ID )
	mc_nb = (*iter_mc)->initialFourMomentum();
    }
  } 

  m_mc_mom_pip = mc_pip.vect().mag();
  m_mc_mom_pim = mc_pim.vect().mag();
  m_mc_mom_mup = mc_mup.vect().mag();
  m_mc_mom_mum = mc_mum.vect().mag();
  m_mc_mom_ep = mc_ep.vect().mag();
  m_mc_mom_em = mc_em.vect().mag();
  m_mc_mom_p = mc_p.vect().mag();
  m_mc_mom_pb = mc_pb.vect().mag();
  m_mc_mom_n = mc_n.vect().mag();
  m_mc_mom_nb = mc_nb.vect().mag();

  m_mc_pt_pip = mc_pip.vect().perp(); 
  m_mc_pt_pim = mc_pim.vect().perp(); 
  m_mc_pt_mup = mc_mup.vect().perp(); 
  m_mc_pt_mum = mc_mum.vect().perp(); 
  m_mc_pt_ep = mc_ep.vect().perp(); 
  m_mc_pt_em = mc_em.vect().perp();
  m_mc_pt_p = mc_p.vect().perp(); 
  m_mc_pt_pb = mc_pb.vect().perp();
  m_mc_pt_n = mc_n.vect().perp(); 
  m_mc_pt_nb = mc_nb.vect().perp();

  m_mc_costhe_mup = mc_mup.vect().cosTheta();
  m_mc_costhe_mum = mc_mum.vect().cosTheta();
  m_mc_costhe_ep = mc_ep.vect().cosTheta();
  m_mc_costhe_em = mc_em.vect().cosTheta();
  m_mc_costhe_p = mc_p.vect().cosTheta();
  m_mc_costhe_pb = mc_pb.vect().cosTheta();
  m_mc_costhe_n = mc_n.vect().cosTheta();
  m_mc_costhe_nb = mc_nb.vect().cosTheta();
  m_mc_costhe_pip = mc_pip.vect().cosTheta();
  m_mc_costhe_pim = mc_pim.vect().cosTheta();
      
  m_mc_cospipi = mc_pip.vect().cosTheta(mc_pim.vect());
  m_mc_cos2pisys = (mc_pip + mc_pim).vect().cosTheta();

}

CLHEP::Hep3Vector Jpsi2lplm::getOrigin() {
  CLHEP::Hep3Vector xorigin(0,0,0);
  IVertexDbSvc*  vtxsvc;
  Gaudi::svcLocator()->service("VertexDbSvc", vtxsvc);
  if(vtxsvc->isVertexValid()){
    double *dbv = vtxsvc->PrimaryVertex(); 
    xorigin.setX(dbv[0]);
    xorigin.setY(dbv[1]);
    xorigin.setZ(dbv[2]);
  }
  return xorigin; 
}


bool Jpsi2lplm::passVertexSelection(CLHEP::Hep3Vector xorigin,
				    RecMdcKalTrack* mdcTrk ) {
  HepVector a = mdcTrk->helix();
  HepSymMatrix Ea = mdcTrk->err();
  HepPoint3D point0(0.,0.,0.);
  VFHelix helixip(point0,a,Ea);
  HepPoint3D IP(xorigin[0],xorigin[1],xorigin[2]);
  helixip.pivot(IP);
  HepVector vecipa = helixip.a();
  
  m_vz0 = vecipa[3];
  m_vr0 = vecipa[0];
  
  if(fabs(m_vz0) >= m_vz0cut) return false;
  if(fabs(m_vr0) >= m_vr0cut) return false;
  
  return true;
}


int Jpsi2lplm::selectChargedTracks(SmartDataPtr<EvtRecEvent> evtRecEvent,
				   SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
				   std::vector<int> & iPiPGood,
				   std::vector<int> & iPiMGood,
				   std::vector<int> & iLepPGood,
				   std::vector<int> & iLepMGood) {

  CLHEP::Hep3Vector xorigin = getOrigin(); 

  std::vector<int> iGood;
  iGood.clear();
  iPiPGood.clear();
  iPiMGood.clear();
  iLepPGood.clear();
  iLepMGood.clear();
  
  // loop through charged tracks 
  for(int i = 0; i < evtRecEvent->totalCharged(); i++){
    // get mdcTrk 
    EvtRecTrackIterator itTrk=evtRecTrkCol->begin() + i;

    // Good Kalman Track 
    if(!(*itTrk)->isMdcKalTrackValid()) continue;

    if(!(*itTrk)->isMdcTrackValid()) continue;
    RecMdcKalTrack* mdcTrk = (*itTrk)->mdcKalTrack();

    // Good Vertex 
    if (!passVertexSelection(xorigin, mdcTrk) ) continue; 

    // Polar angle cut
    if(fabs(cos(mdcTrk->theta())) > m_cha_costheta_cut) continue;

    iGood.push_back((*itTrk)->trackId());
    if(mdcTrk->p() < m_pion_momentum_max){ // with momentum < 0.6 GeV/c is pion candidates
	if(mdcTrk->charge()>0) iPiPGood.push_back((*itTrk)->trackId());
	if(mdcTrk->charge()<0) iPiMGood.push_back((*itTrk)->trackId());
    }
    else{ // otherwise, lepton candidates
      if(mdcTrk->charge()>0) iLepPGood.push_back((*itTrk)->trackId());
      if(mdcTrk->charge()<0) iLepMGood.push_back((*itTrk)->trackId());
    }

  } // end charged tracks

  m_ncharged = iGood.size();
  m_npiptrk = iPiPGood.size();
  m_npimtrk = iPiMGood.size(); 
  m_nlptrk = iLepPGood.size();
  m_nlmtrk = iLepMGood.size(); 

  if (m_npiptrk > 0 && m_npimtrk > 0 && m_nlptrk > 0 && m_nlmtrk > 0) {
    EvtRecTrackIterator itTrk_pip = evtRecTrkCol->begin() + iPiPGood[0];
    EvtRecTrackIterator itTrk_pim = evtRecTrkCol->begin() + iPiMGood[0];
    EvtRecTrackIterator itTrk_lp = evtRecTrkCol->begin() + iLepPGood[0];
    EvtRecTrackIterator itTrk_lm = evtRecTrkCol->begin() + iLepMGood[0];
    saveTrkInfo(itTrk_pip, itTrk_pim, itTrk_lp, itTrk_lm);
  }
  return iGood.size(); 
}

int Jpsi2lplm::selectPionPlusPionMinus(SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
				       std::vector<int> iPGood,
				       std::vector<int> iMGood) {
  int npipi = 0;
  bool evtflw_filled = false;
  
  for(unsigned int i1 = 0; i1 < iPGood.size(); i1++) {
    EvtRecTrackIterator itTrk_p = evtRecTrkCol->begin() + iPGood[i1];
    RecMdcTrack* mdcTrk_p = (*itTrk_p)->mdcTrack();
    if (mdcTrk_p->charge() < 0) continue; // only positive charged tracks

    for(unsigned int i2 = 0; i2 < iMGood.size(); i2++) {
      EvtRecTrackIterator itTrk_m = evtRecTrkCol->begin() + iMGood[i2];
      RecMdcTrack* mdcTrk_m = (*itTrk_m)->mdcTrack();
      if (mdcTrk_m->charge() > 0) continue; // only negative charged tracks

      // polar angle for both pions
      if ( ! ( fabs(cos(mdcTrk_p->theta())) < m_pion_polar_angle_max &&
      	       fabs(cos(mdcTrk_m->theta())) < m_pion_polar_angle_max )) continue;
      if ( !evtflw_filled ) h_evtflw->Fill(3); // |cos#theta| cut 

      // pion momentum
      //if ( ! ( fabs(mdcTrk_p->p()) < m_pion_momentum_max  &&
      //	       fabs(mdcTrk_m->p()) < m_pion_momentum_max )) continue;
      //
      //if ( !evtflw_filled ) h_evtflw->Fill(4); //|p| cut 
      
      // track PID
      double prob_pip, prob_kp, prob_pim, prob_km, prob_p, prob_pb; 
      calcTrackPID(itTrk_p, prob_pip, prob_kp, prob_p);  
      calcTrackPID(itTrk_m, prob_pim, prob_km, prob_pb);
      // printf(">>> %f, %f, %f, %f \n", prob_pip, prob_kp, prob_pim, prob_km);

      m_prob_pip = prob_pip;
      m_prob_kp = prob_kp;
      m_prob_p = prob_p;
      m_prob_pim = prob_pim;
      m_prob_km = prob_km;
      m_prob_pb = prob_pb;
      
      if(! (prob_pip > prob_kp &&
       	    prob_pip > m_prob_pion_min &&
       	    prob_pim > prob_km &&
       	    prob_pim > m_prob_pion_min) ) continue;

      if ( !evtflw_filled ) h_evtflw->Fill(4); //PID
 
      // apply vertex fit
      RecMdcKalTrack *pipTrk = (*(evtRecTrkCol->begin()+iPGood[i1]))->mdcKalTrack();
      RecMdcKalTrack *pimTrk = (*(evtRecTrkCol->begin()+iMGood[i2]))->mdcKalTrack();

      savePionInfo(pipTrk, pimTrk);
      
      if (! hasGoodPiPiVertex(pipTrk, pimTrk, evtflw_filled) ) continue; 
      
      npipi++;
      evtflw_filled = true;
    }
  } 

  return npipi; 
}


int Jpsi2lplm::selectLeptonPlusLeptonMinus(SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
					   std::vector<int> iPGood,
					   std::vector<int> iMGood) {
  int nlplm = 0;
  bool evtflw_filled = false;
  
  for(unsigned int i1 = 0; i1 < iPGood.size(); i1++) {
    EvtRecTrackIterator itTrk_p = evtRecTrkCol->begin() + iPGood[i1];
    RecMdcTrack* mdcTrk_p = (*itTrk_p)->mdcTrack();
    if (mdcTrk_p->charge() < 0) continue; // only positive charged tracks

    for(unsigned int i2 = 0; i2 < iMGood.size(); i2++) {
      EvtRecTrackIterator itTrk_m = evtRecTrkCol->begin() + iMGood[i2];
      RecMdcTrack* mdcTrk_m = (*itTrk_m)->mdcTrack();
      if (mdcTrk_m->charge() > 0) continue; // only negative charged tracks

      // lepton momentum 
      if ( ! ( fabs(mdcTrk_p->p()) < m_lepton_momentum_max  &&
      	       fabs(mdcTrk_m->p()) < m_lepton_momentum_max )) continue;

      if ( !evtflw_filled ) h_evtflw->Fill(8); //|p| cut 
      
      // apply vertex fit
      RecMdcKalTrack *lpTrk = (*(evtRecTrkCol->begin()+iPGood[i1]))->mdcKalTrack();
      RecMdcKalTrack *lmTrk = (*(evtRecTrkCol->begin()+iMGood[i2]))->mdcKalTrack();

      saveLeptonInfo(lpTrk, lmTrk);
      
      int ee_flag=0, mumu_flag=0;
      if ( hasGoodLpLmVertex(lpTrk, lmTrk, Electron_Hypothesis_Fit, evtflw_filled) ) ee_flag=1;
      if ( hasGoodLpLmVertex(lpTrk, lmTrk, Muon_Hypothesis_Fit, evtflw_filled) ) mumu_flag=1; 
      
      m_jpsi2elel_flag = ee_flag;
      m_jpsi2mumu_flag = mumu_flag;
      if(ee_flag==1 || mumu_flag==1) nlplm++;
      evtflw_filled = true;
    }
  } 

  return nlplm; 
}


void Jpsi2lplm::calcTrackPID(EvtRecTrackIterator itTrk_p,
			     double& prob_pip,
			     double& prob_kp,
			     double& prob_p) {
  prob_pip = 999.; 
  prob_kp = 999.; 
  prob_p = 999.; 
  ParticleID * pidp = ParticleID::instance();
  pidp->init();
  pidp->setMethod(pidp->methodProbability());
  pidp->setChiMinCut(4);
  pidp->setRecTrack(*itTrk_p);
  // use PID sub-system
  pidp->usePidSys(pidp->useDedx() | pidp->useTof1() | pidp->useTof2());
  // pidp->usePidSys(pidp->useDedx());
  pidp->identify(pidp->onlyPionKaonProton());
  pidp->calculate();
  if(pidp->IsPidInfoValid()) {
    prob_pip = pidp->probPion();
    prob_kp  = pidp->probKaon();
    prob_p   = pidp->probProton();
  }
}

bool Jpsi2lplm::hasGoodPiPiVertex(RecMdcKalTrack *pipTrk,
				  RecMdcKalTrack *pimTrk,
				  bool evtflw_filled) {

  HepLorentzVector pcms(0.011*m_ecms, 0., 0., m_ecms);

  HepLorentzVector p4_vtx_pip, p4_vtx_pim, p4_vtx_pipi, p4_vtx_recpipi;
  WTrackParameter wvpipTrk, wvpimTrk;
  pipTrk->setPidType(RecMdcKalTrack::pion);
  wvpipTrk = WTrackParameter(PION_MASS, pipTrk->getZHelix(), pipTrk->getZError());

  pimTrk->setPidType(RecMdcKalTrack::pion);
  wvpimTrk = WTrackParameter(PION_MASS, pimTrk->getZHelix(), pimTrk->getZError());
  
  HepPoint3D vx(0., 0., 0.);
  HepSymMatrix Evx(3, 0);

  double bx = 1E+6;
  double by = 1E+6;
  double bz = 1E+6;
  Evx[0][0] = bx*bx;
  Evx[1][1] = by*by;
  Evx[2][2] = bz*bz;
  
  VertexParameter vxpar;
  vxpar.setVx(vx);
  vxpar.setEvx(Evx);
  
  VertexFit* vtxfit = VertexFit::instance();
  vtxfit->init();
  vtxfit->AddTrack(0,  wvpipTrk);
  vtxfit->AddTrack(1,  wvpimTrk);
  vtxfit->AddVertex(0, vxpar,0,1);

  if(!vtxfit->Fit(0)) return false;

  vtxfit->Swim(0);
      
  WTrackParameter wpip = vtxfit->wtrk(0);
  WTrackParameter wpim = vtxfit->wtrk(1);
  p4_vtx_pip = vtxfit->pfit(0) ;
  p4_vtx_pim = vtxfit->pfit(1) ;
  p4_vtx_recpipi = pcms - p4_vtx_pip - p4_vtx_pim;
  p4_vtx_pipi = p4_vtx_pip + p4_vtx_pim;

  double cospipi = cos(p4_vtx_pip.vect().angle(p4_vtx_pim.vect()));
  double cos2pisys = (p4_vtx_pip + p4_vtx_pim).cosTheta();

  if( ! (cospipi < m_pipi_costheta_max) ) return false;
  if( !evtflw_filled ) h_evtflw->Fill(5); // "cos#theta_{#pi^{+}#pi^{-}}<0.99"

  if( ! (fabs(cos2pisys) < m_pipisys_costheta_max ) ) return false;
  if( !evtflw_filled ) h_evtflw->Fill(6); // cos#theta_{#pi#pi sys}<0.99 

  if( ! ( p4_vtx_recpipi.m() >= m_dipion_mass_min &&
	  p4_vtx_recpipi.m() <= m_dipion_mass_max) ) return false;
  if( !evtflw_filled ) h_evtflw->Fill(7); // 3.0<M_{#pi#pi}^{rec}<3.2

  savePionVtxInfo(p4_vtx_pip, p4_vtx_pim); 
  m_vtx_mrecpipi = p4_vtx_recpipi.m();
  m_vtx_mpipi = p4_vtx_pipi.m();
  m_vtx_cospipi = cospipi;
  m_vtx_cos2pisys = cos2pisys; 
  
  return true;
}

bool Jpsi2lplm::hasGoodLpLmVertex(RecMdcKalTrack *lpTrk,
				  RecMdcKalTrack *lmTrk,
				  int particle_flag,
				  bool evtflw_filled) {

  HepLorentzVector pcms(0.011*m_ecms, 0., 0., m_ecms);

  HepLorentzVector p4_vtx_lp, p4_vtx_lm, p4_vtx_lplm;
  WTrackParameter wvlpTrk, wvlmTrk;

  if( particle_flag  == Electron_Hypothesis_Fit ){ 
    lpTrk->setPidType(RecMdcKalTrack::electron);
    wvlpTrk = WTrackParameter(ELECTRON_MASS, lpTrk->getZHelixE(), lpTrk->getZErrorE());
    
    lmTrk->setPidType(RecMdcKalTrack::electron);
    wvlmTrk = WTrackParameter(ELECTRON_MASS, lmTrk->getZHelixE(), lmTrk->getZErrorE());
  }
  if( particle_flag == Muon_Hypothesis_Fit ){
    lpTrk->setPidType(RecMdcKalTrack::muon);
    wvlpTrk = WTrackParameter(MUON_MASS, lpTrk->getZHelixMu(), lpTrk->getZErrorMu());
    
    lmTrk->setPidType(RecMdcKalTrack::muon);
    wvlmTrk = WTrackParameter(MUON_MASS, lmTrk->getZHelixMu(), lmTrk->getZErrorMu());
  }
  
  HepPoint3D vx(0., 0., 0.);
  HepSymMatrix Evx(3, 0);
  
  double bx = 1E+6;
  double by = 1E+6;
  double bz = 1E+6;
  Evx[0][0] = bx*bx;
  Evx[1][1] = by*by;
  Evx[2][2] = bz*bz;
  
  VertexParameter vxpar;
  vxpar.setVx(vx);
  vxpar.setEvx(Evx);
  
  VertexFit* vtxfit = VertexFit::instance();
  vtxfit->init();
  vtxfit->AddTrack(0,  wvlpTrk);
  vtxfit->AddTrack(1,  wvlmTrk);
  vtxfit->AddVertex(0, vxpar,0,1);
  
  if(!vtxfit->Fit(0)) return false;
  
  vtxfit->Swim(0);
  
  WTrackParameter wlp = vtxfit->wtrk(0);
  WTrackParameter wlm = vtxfit->wtrk(1);
  p4_vtx_lp = vtxfit->pfit(0) ;
  p4_vtx_lm = vtxfit->pfit(1) ;
  p4_vtx_lplm = p4_vtx_lp + p4_vtx_lm;

  if( ! ( p4_vtx_lplm.m() >= m_dilepton_mass_min &&
	  p4_vtx_lplm.m() <= m_dilepton_mass_max) ) return false; // 2.5<M_{ll}<3.5
  
  if( particle_flag  == Electron_Hypothesis_Fit ){ 
    if( !evtflw_filled ) h_evtflw->Fill(9); 
  }
  if( particle_flag  == Muon_Hypothesis_Fit ){ 
    if( !evtflw_filled ) h_evtflw->Fill(10); 
  }
  
  saveLeptonVtxInfo(p4_vtx_lp, p4_vtx_lm, particle_flag); 

  return true;
}



int Jpsi2lplm::selectNeutralTracks(SmartDataPtr<EvtRecEvent> evtRecEvent,
				   SmartDataPtr<EvtRecTrackCol> evtRecTrkCol) {

  std::vector<int> iGam;
  iGam.clear();
  std::vector<int> iShow;
  iShow.clear();

  // loop through neutral tracks
  for(int i=evtRecEvent->totalCharged(); i< evtRecEvent->totalTracks(); i++) {
    if (i > m_total_number_of_charged_max) break;

    EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + i ;
    if(!(*itTrk)->isEmcShowerValid()) continue;
    RecEmcShower *emcTrk = (*itTrk)->emcShower();
    iShow.push_back((*itTrk)->trackId());
    
    // TDC window
    if ( !(emcTrk->time() >= m_min_emctime && emcTrk->time() <= m_max_emctime) )
      continue; 

    // Energy threshold
    double abs_costheta(fabs(cos(emcTrk->theta())));
    bool barrel = (abs_costheta < m_costheta_barrel_max); 
    bool endcap = (abs_costheta > m_costheta_endcap_min
		   && abs_costheta < m_costheta_endcap_max);
    double eraw = emcTrk->energy();
    
    if ( !( (barrel && eraw > m_energy_barrel_min)
	    || (endcap && eraw > m_energy_endcap_min)))  continue; 

    // photon isolation: the opening angle between a candidate shower
    // and the closest charged track should be larger than 10 degree 
    CLHEP::Hep3Vector emcpos(emcTrk->x(), emcTrk->y(), emcTrk->z());

    // EMC costheta cut 
    double costhe = cos(emcpos.theta());
    if ( fabs(costhe) >= m_gammaCosCut) continue;
    
    // find the nearest charged track
    double dthe = 200.;
    double dphi = 200.;
    double dang = 200.; 
    for(int j = 0; j < evtRecEvent->totalCharged(); j++) {
      EvtRecTrackIterator jtTrk = evtRecTrkCol->begin() + j;
      if(!(*jtTrk)->isExtTrackValid()) continue;
      RecExtTrack *extTrk = (*jtTrk)->extTrack();
      if(extTrk->emcVolumeNumber() == -1) continue;
      CLHEP::Hep3Vector extpos = extTrk->emcPosition();
      double angd = extpos.angle(emcpos);
      double thed = extpos.theta() - emcpos.theta();
      double phid = extpos.deltaPhi(emcpos);
      thed = fmod(thed+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;
      phid = fmod(phid+CLHEP::twopi+CLHEP::twopi+pi, CLHEP::twopi) - CLHEP::pi;

      if(fabs(thed) < fabs(dthe)) dthe = thed;
      if(fabs(phid) < fabs(dphi)) dphi = phid;
      if(angd < dang) dang = angd;	    
    }

    if(dang>=200) continue;
    dthe = dthe * 180 / (CLHEP::pi);
    dphi = dphi * 180 / (CLHEP::pi);
    dang = dang * 180 / (CLHEP::pi);
    if (dang < m_photon_iso_angle_min ) continue; 

    iGam.push_back((*itTrk)->trackId());
  } // end loop neutral tracks     

  m_ngam = iGam.size();
  m_nshow = iShow.size();

  saveGamInfo(iGam, evtRecTrkCol);   
  
  return iGam.size(); 
}


void Jpsi2lplm::saveTrkInfo(EvtRecTrackIterator itTrk_pip,
			    EvtRecTrackIterator itTrk_pim,
			    EvtRecTrackIterator itTrk_lp,
			    EvtRecTrackIterator itTrk_lm) {

  RecMdcTrack* mdcTrk_pip = (*itTrk_pip)->mdcTrack(); 
  m_trkpip_p = mdcTrk_pip->p();
  m_trkpip_px = mdcTrk_pip->px();
  m_trkpip_py = mdcTrk_pip->py();
  m_trkpip_pz = mdcTrk_pip->pz();
  m_trkpip_theta = mdcTrk_pip->theta();
  m_trkpip_phi = mdcTrk_pip->phi();
  
  if((*itTrk_pip)->isEmcShowerValid()){
    RecEmcShower *emcTrk_pip = (*itTrk_pip)->emcShower();
    m_trkpip_eraw = emcTrk_pip->energy();
  }
  else{ m_trkpip_eraw = -99.0; }

  RecMdcTrack* mdcTrk_pim = (*itTrk_pim)->mdcTrack();
  m_trkpim_p = mdcTrk_pim->p();
  m_trkpim_px = mdcTrk_pim->px();
  m_trkpim_py = mdcTrk_pim->py();
  m_trkpim_pz = mdcTrk_pim->pz();
  m_trkpim_theta = mdcTrk_pim->theta();
  m_trkpim_phi = mdcTrk_pim->phi();
  
  if((*itTrk_pim)->isEmcShowerValid()){
    RecEmcShower *emcTrk_pim = (*itTrk_pim)->emcShower();
    m_trkpim_eraw = emcTrk_pim->energy();
  }
  else{ m_trkpim_eraw = -99.0; }

  RecMdcTrack* mdcTrk_lp = (*itTrk_lp)->mdcTrack(); 
  m_trklp_p = mdcTrk_lp->p();
  m_trklp_px = mdcTrk_lp->px();
  m_trklp_py = mdcTrk_lp->py();
  m_trklp_pz = mdcTrk_lp->pz();
  m_trklp_theta = mdcTrk_lp->theta();
  m_trklp_phi = mdcTrk_lp->phi();
  
  if((*itTrk_lp)->isEmcShowerValid()){
    RecEmcShower *emcTrk_lp = (*itTrk_lp)->emcShower();
    m_trklp_eraw = emcTrk_lp->energy();
  }
  else{ m_trklp_eraw = -99.0; }

  RecMdcTrack* mdcTrk_lm = (*itTrk_lm)->mdcTrack();
  m_trklm_p = mdcTrk_lm->p();
  m_trklm_px = mdcTrk_lm->px();
  m_trklm_py = mdcTrk_lm->py();
  m_trklm_pz = mdcTrk_lm->pz();
  m_trklm_theta = mdcTrk_lm->theta();
  m_trklm_phi = mdcTrk_lm->phi();
  
  if((*itTrk_lm)->isEmcShowerValid()){
    RecEmcShower *emcTrk_lm = (*itTrk_lm)->emcShower();
    m_trklm_eraw = emcTrk_lm->energy();
  }
  else{ m_trklm_eraw = -99.0; }

}

void Jpsi2lplm::saveGamInfo(std::vector<int> iGam,
			    SmartDataPtr<EvtRecTrackCol> evtRecTrkCol){

  for(vector<int>::size_type i=0; i<iGam.size(); i++)  {
    
    EvtRecTrackIterator itTrk = evtRecTrkCol->begin() + iGam[i];
    RecEmcShower* emcTrk = (*itTrk)->emcShower();
    double eraw = emcTrk->energy();
    double phi = emcTrk->phi();
    double theta = emcTrk->theta(); 
    HepLorentzVector p4 = HepLorentzVector(eraw * sin(theta) * cos(phi),
					   eraw * sin(theta) * sin(phi),
					   eraw * cos(theta),
					   eraw );
    m_raw_gpx->push_back(p4.px());
    m_raw_gpy->push_back(p4.py());
    m_raw_gpz->push_back(p4.pz());
    m_raw_ge->push_back(p4.e());
  }
}

void Jpsi2lplm::savePionInfo(RecMdcKalTrack *pipTrk,
			     RecMdcKalTrack *pimTrk){

  m_pip_px = pipTrk->px();
  m_pip_py = pipTrk->py();
  m_pip_pz = pipTrk->pz();

  m_pim_px = pimTrk->px();
  m_pim_py = pimTrk->py();
  m_pim_pz = pimTrk->pz();
  
}

void Jpsi2lplm::saveLeptonInfo(RecMdcKalTrack *lpTrk,
			       RecMdcKalTrack *lmTrk){

  m_lp_px = lpTrk->px();
  m_lp_py = lpTrk->py();
  m_lp_pz = lpTrk->pz();

  m_lm_px = lmTrk->px();
  m_lm_py = lmTrk->py();
  m_lm_pz = lmTrk->pz();

}



void Jpsi2lplm::savePionVtxInfo(HepLorentzVector p4_vtx_pip,
				HepLorentzVector p4_vtx_pim){

  m_vtx_pip_px = p4_vtx_pip.px();
  m_vtx_pip_py = p4_vtx_pip.py();
  m_vtx_pip_pz = p4_vtx_pip.pz();
  m_vtx_pip_p = p4_vtx_pip.rho();
  m_vtx_pip_e = p4_vtx_pip.e();
  m_vtx_pip_costheta = p4_vtx_pip.cosTheta();
  m_vtx_pip_phi = p4_vtx_pip.phi();

  m_vtx_pim_px = p4_vtx_pim.px();
  m_vtx_pim_py = p4_vtx_pim.py();
  m_vtx_pim_pz = p4_vtx_pim.pz();
  m_vtx_pim_p = p4_vtx_pim.rho();
  m_vtx_pim_e = p4_vtx_pim.e();
  m_vtx_pim_costheta = p4_vtx_pim.cosTheta();
  m_vtx_pim_phi = p4_vtx_pim.phi();

}

void Jpsi2lplm::saveLeptonVtxInfo(HepLorentzVector p4_vtx_lp,
				  HepLorentzVector p4_vtx_lm,
				  int particle_flag){

  HepLorentzVector p4_vtx_lplm = p4_vtx_lp + p4_vtx_lm;
  double coslplm = cos(p4_vtx_lp.vect().angle(p4_vtx_lm.vect()));
  double cos2lsys = (p4_vtx_lp + p4_vtx_lm).cosTheta();

  if( particle_flag  == Electron_Hypothesis_Fit ){
    m_vtx_elp_px = p4_vtx_lp.px();
    m_vtx_elp_py = p4_vtx_lp.py();
    m_vtx_elp_pz = p4_vtx_lp.pz();
    m_vtx_elp_p = p4_vtx_lp.rho();
    m_vtx_elp_e = p4_vtx_lp.e();
    m_vtx_elp_costheta = p4_vtx_lp.cosTheta();
    m_vtx_elp_phi = p4_vtx_lp.phi();
    
    m_vtx_elm_px = p4_vtx_lm.px();
    m_vtx_elm_py = p4_vtx_lm.py();
    m_vtx_elm_pz = p4_vtx_lm.pz();
    m_vtx_elm_p = p4_vtx_lm.rho();
    m_vtx_elm_e = p4_vtx_lm.e();
    m_vtx_elm_costheta = p4_vtx_lm.cosTheta();
    m_vtx_elm_phi = p4_vtx_lm.phi();

    m_vtx_melel = p4_vtx_lplm.m();
    m_vtx_coselel = coslplm;
    m_vtx_cos2elsys = cos2lsys;
  }
  if( particle_flag  == Muon_Hypothesis_Fit ){
    m_vtx_mup_px = p4_vtx_lp.px();
    m_vtx_mup_py = p4_vtx_lp.py();
    m_vtx_mup_pz = p4_vtx_lp.pz();
    m_vtx_mup_p = p4_vtx_lp.rho();
    m_vtx_mup_e = p4_vtx_lp.e();
    m_vtx_mup_costheta = p4_vtx_lp.cosTheta();
    m_vtx_mup_phi = p4_vtx_lp.phi();
    
    m_vtx_mum_px = p4_vtx_lm.px();
    m_vtx_mum_py = p4_vtx_lm.py();
    m_vtx_mum_pz = p4_vtx_lm.pz();
    m_vtx_mum_p = p4_vtx_lm.rho();
    m_vtx_mum_e = p4_vtx_lm.e();
    m_vtx_mum_costheta = p4_vtx_lm.cosTheta();
    m_vtx_mum_phi = p4_vtx_lm.phi();

    m_vtx_mmumu = p4_vtx_lplm.m();
    m_vtx_cosmumu = coslplm;
    m_vtx_cos2musys = cos2lsys;
  }
  
}


