// -*- C++ -*-
// 
//
// Description: J/psi -> Invisible
//
// Original Author:  SHI Xin <shixin@ihep.ac.cn>
//         Created:  [2016-03-23 Wed 09:12] 
//         Inspired by Zhu Kai and Zhang Chi's code 
//
// Modified to : J/psi -> p nbar pi- and c.c.  by R. Kiuchi
//             : [2017-03-02 Thu 15:00] 

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

class Jpsi2pnpi : public Algorithm {
  
public:
  Jpsi2pnpi(const std::string&, ISvcLocator*);
  ~Jpsi2pnpi(); 
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
  double m_prob_pion_min;
  double m_prob_proton_min;
  double m_neutron_mass_min; 
  double m_neutron_mass_max;
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
  int m_nptrk;
  int m_nmtrk;
  double m_trkp_p; 
  double m_trkp_px; 
  double m_trkp_py; 
  double m_trkp_pz; 
  double m_trkp_theta; 
  double m_trkp_phi; 
  double m_trkp_eraw; 
  
  double m_trkm_p; 
  double m_trkm_px; 
  double m_trkm_py; 
  double m_trkm_pz; 
  double m_trkm_theta; 
  double m_trkm_phi; 
  double m_trkm_eraw; 

  // neutral tracks
  int m_nshow;
  int m_ngam;
  std::vector<double> *m_raw_gpx; 
  std::vector<double> *m_raw_gpy; 
  std::vector<double> *m_raw_gpz; 
  std::vector<double> *m_raw_ge; 
  std::vector<double> *m_gn_dang;
  std::vector<int> *m_raw_cstat;
  std::vector<int> *m_raw_nhit;
  std::vector<double> *m_raw_secmom;
  
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

  int m_pnpi_flag;

  // Kalman track info
  double m_kal_trkp_p;
  double m_kal_trkp_px;
  double m_kal_trkp_py;
  double m_kal_trkp_pz;

  double m_kal_trkm_p;
  double m_kal_trkm_px;
  double m_kal_trkm_py;
  double m_kal_trkm_pz;

  // fitted info
  double m_vtx_proton_px; 
  double m_vtx_proton_py; 
  double m_vtx_proton_pz;
  double m_vtx_proton_p; 
  double m_vtx_proton_e;
  double m_vtx_proton_costheta;
  double m_vtx_proton_phi;

  double m_vtx_neutron_px; 
  double m_vtx_neutron_py; 
  double m_vtx_neutron_pz;
  double m_vtx_neutron_p; 
  double m_vtx_neutron_e;
  double m_vtx_neutron_m;
  double m_vtx_neutron_costheta;
  double m_vtx_neutron_phi;

  double m_vtx_pion_px; 
  double m_vtx_pion_py; 
  double m_vtx_pion_pz; 
  double m_vtx_pion_p;
  double m_vtx_pion_e;
  double m_vtx_pion_costheta;
  double m_vtx_pion_phi;

  double m_vtx_proton_pion_p;
  double m_vtx_proton_pion_e;
  double m_vtx_proton_pion_m;
    
  // check MDC and EMC match
  long m_pion_matched;
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
  bool buildJpsiToPNPi();
  void saveGenInfo(); 
  void saveTrkInfo(EvtRecTrackIterator,
		   EvtRecTrackIterator);
  void saveKalmanTrackInfo(RecMdcKalTrack *,
			   RecMdcKalTrack *);
  void saveVtxInfo(HepLorentzVector,
		   HepLorentzVector,
		   HepLorentzVector); 
  void saveGamInfo(std::vector<int>,
		   SmartDataPtr<EvtRecTrackCol>);
  int selectChargedTracks(SmartDataPtr<EvtRecEvent>,
			  SmartDataPtr<EvtRecTrackCol>,
			  std::vector<int> &,
			  std::vector<int> &); 
  int selectProtonPion(SmartDataPtr<EvtRecTrackCol>,
		       std::vector<int>,
		       std::vector<int>);
  void calcTrackPID(EvtRecTrackIterator,
		    double&,
		    double&,
		    double&);
  bool hasGoodProtonPiVertex(RecMdcKalTrack *,
			     RecMdcKalTrack *,
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

DECLARE_ALGORITHM_FACTORY( Jpsi2pnpi )
DECLARE_FACTORY_ENTRIES( Jpsi2pnpi ) {
  DECLARE_ALGORITHM(Jpsi2pnpi);
}

LOAD_FACTORY_ENTRIES( Jpsi2pnpi )

//
// constants
//

const double PION_MASS = 0.139570;
const double PROTON_MASS = 0.938272;

const int ProtonPionMinusFlag = 1;
const int AntiProtonPionPlusFlag = 2;

const int ELECTRON_PDG_ID = 11;
const int MUON_PDG_ID = 13;
const int PIONPLUS_PDG_ID = 211;

const int JPSI_PDG_ID = 443;
const int PSI2S_PDG_ID = 100443;
const int PROTON_PDG_ID = 2212; 
const int NEUTRON_PDG_ID = 2112; 

//
// member functions
//
  
Jpsi2pnpi::Jpsi2pnpi(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator),
  m_tree(0),
  m_raw_gpx(0), 
  m_raw_gpy(0), 
  m_raw_gpz(0), 
  m_raw_ge(0),
  m_gn_dang(0),
  m_raw_cstat(0),
  m_raw_nhit(0),
  m_raw_secmom(0)
{
  declareProperty("OutputFileName", m_output_filename);
  declareProperty("IsMonteCarlo", m_isMonteCarlo);
  declareProperty("Ecms", m_ecms = 3.097);
  declareProperty("Vr0cut", m_vr0cut=1.0);
  declareProperty("Vz0cut", m_vz0cut=10.0);
  declareProperty("ChaCosthetaCut", m_cha_costheta_cut=0.93);
  declareProperty("TotalNumberOfChargedMax", m_total_number_of_charged_max=50);
  declareProperty("MinEstCut", m_min_emctime=0.0);
  declareProperty("MaxEstCut", m_max_emctime=14.0);
  declareProperty("GammaCosCut",  m_gammaCosCut= 0.93); 
  declareProperty("CosthetaBarrelMax", m_costheta_barrel_max=0.8);
  declareProperty("CosthetaEndcapMin", m_costheta_endcap_min=0.86);
  declareProperty("CosthetaEndcapMax", m_costheta_endcap_max=0.92);
  declareProperty("EnergyBarrelMin", m_energy_barrel_min=0.025); 
  declareProperty("EnergyEndcapMin", m_energy_endcap_min=0.050); 
  declareProperty("PhotonIsoAngleMin", m_photon_iso_angle_min=10);
  declareProperty("PionPolarAngleMax", m_pion_polar_angle_max=0.99);
  declareProperty("PionMomentumMax", m_pion_momentum_max=1.9); 
  declareProperty("ProbPionMin", m_prob_proton_min=0.001);
  declareProperty("ProbPionMin", m_prob_pion_min=0.001);
  declareProperty("RecProtonPionMassMin", m_neutron_mass_min=0.75); 
  declareProperty("RecProtonPionMassMax", m_neutron_mass_max=1.13);
}


StatusCode Jpsi2pnpi::initialize(){
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << ">>>>>>> in initialize()" << endmsg;

  m_fout = new TFile(m_output_filename.c_str(), "RECREATE");
  m_fout->cd(); 

  book_histogram(); 
  book_tree(); 

  log << MSG::INFO << "successfully return from initialize()" <<endmsg;
  return StatusCode::SUCCESS;
}


StatusCode Jpsi2pnpi::execute() {
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in execute()" << endreq;
  
  // clear variables 
  clearVariables();

  h_evtflw->Fill(0); // raw 
  SmartDataPtr<Event::EventHeader>eventHeader(eventSvc(),"/Event/EventHeader");
  if(!eventHeader) return StatusCode::FAILURE;

  m_run = eventHeader->runNumber();
  m_event = eventHeader->eventNumber();
  

  if (buildJpsiToPNPi()) {
    m_tree->Fill(); // only fill tree for the selected events 
  }

  return StatusCode::SUCCESS; 
}

StatusCode Jpsi2pnpi::finalize() {
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in finalize()" << endmsg;

  m_fout->cd();
  m_tree->Write();
  h_evtflw->Write();
  m_fout->Close();
  
  return StatusCode::SUCCESS;
}


Jpsi2pnpi::~Jpsi2pnpi() {
}


void Jpsi2pnpi::book_histogram() {

  h_evtflw = new TH1F("hevtflw", "eventflow", 10, 0, 10);
  if (!h_evtflw) return;
  h_evtflw->GetXaxis()->SetBinLabel(1, "raw");
  h_evtflw->GetXaxis()->SetBinLabel(2, "N_{Good}=2");

  h_evtflw->GetXaxis()->SetBinLabel(3, "PID"); 

  h_evtflw->GetXaxis()->SetBinLabel(4, "0.75<M_{#p#pi}^{rec}<1.13");
}


void Jpsi2pnpi::book_tree() {

  m_tree=new TTree("tree", "jpsi2pnpi");
  if (!m_tree) return; 

  //commom info
  m_tree->Branch("run",&m_run,"run/I");
  m_tree->Branch("event",&m_event,"event/I");
	  
  //charged tracks
  m_tree->Branch("ncharged", &m_ncharged, "ncharged/I");
  m_tree->Branch("nptrk", &m_nptrk, "nptrk/I");
  m_tree->Branch("nmtrk", &m_nmtrk, "nmtrk/I");
  m_tree->Branch("trkp_p", &m_trkp_p, "trkp_p/D"); 
  m_tree->Branch("trkp_px", &m_trkp_px, "trkp_px/D"); 
  m_tree->Branch("trkp_py", &m_trkp_py, "trkp_py/D"); 
  m_tree->Branch("trkp_pz", &m_trkp_pz, "trkp_pz/D"); 
  m_tree->Branch("trkp_theta", &m_trkp_theta, "trkp_theta/D"); 
  m_tree->Branch("trkp_phi", &m_trkp_phi, "trkp_phi/D"); 
  m_tree->Branch("trkp_eraw", &m_trkp_eraw, "trkp_eraw/D"); 

  m_tree->Branch("trkm_p", &m_trkm_p, "trkm_p/D"); 
  m_tree->Branch("trkm_px", &m_trkm_px, "trkm_px/D"); 
  m_tree->Branch("trkm_py", &m_trkm_py, "trkm_py/D"); 
  m_tree->Branch("trkm_pz", &m_trkm_pz, "trkm_pz/D"); 
  m_tree->Branch("trkm_theta", &m_trkm_theta, "trkm_theta/D"); 
  m_tree->Branch("trkm_phi", &m_trkm_phi, "trkm_phi/D"); 
  m_tree->Branch("trkm_eraw", &m_trkm_eraw, "trkm_eraw/D"); 
	  
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
  
  m_tree->Branch("gn_dang", &m_gn_dang);
  m_tree->Branch("raw_cstat",&m_raw_cstat);
  m_tree->Branch("raw_nhit",&m_raw_nhit);
  m_tree->Branch("raw_secmom",&m_raw_secmom);


  // PID info
  m_tree->Branch("prob_pip", &m_prob_pip, "prob_pip/D"); 
  m_tree->Branch("prob_pim", &m_prob_pim, "prob_pim/D"); 
  m_tree->Branch("prob_kp", &m_prob_kp, "prob_kp/D"); 
  m_tree->Branch("prob_km", &m_prob_km, "prob_km/D"); 
  m_tree->Branch("prob_p", &m_prob_p, "prob_p/D"); 
  m_tree->Branch("prob_pb", &m_prob_pb, "prob_pb/D"); 

  m_tree->Branch("pnpi_flag", &m_pnpi_flag, "pnpi_flag/I"); 

  // save Kalman fitting track info
  m_tree->Branch("kal_trkp_p", &m_kal_trkp_p, "kal_trkp_p/D");
  m_tree->Branch("kal_trkp_px", &m_kal_trkp_px, "kal_trkp_px/D");
  m_tree->Branch("kal_trkp_py", &m_kal_trkp_py, "kal_trkp_py/D");
  m_tree->Branch("kal_trkp_pz", &m_kal_trkp_pz, "kal_trkp_pz/D");

  m_tree->Branch("kal_trkm_p", &m_kal_trkm_p, "kal_trkm_p/D");
  m_tree->Branch("kal_trkm_px", &m_kal_trkm_px, "kal_trkm_px/D");
  m_tree->Branch("kal_trkm_py", &m_kal_trkm_py, "kal_trkm_py/D");
  m_tree->Branch("kal_trkm_pz", &m_kal_trkm_pz, "kal_trkm_pz/D");

  // fitted info
  m_tree->Branch("vtx_proton_px", &m_vtx_proton_px, "vtx_proton_px/D");
  m_tree->Branch("vtx_proton_py", &m_vtx_proton_py, "vtx_proton_py/D");
  m_tree->Branch("vtx_proton_pz", &m_vtx_proton_pz, "vtx_proton_pz/D");
  m_tree->Branch("vtx_proton_p", &m_vtx_proton_p, "vtx_proton_p/D");
  m_tree->Branch("vtx_proton_e", &m_vtx_proton_e, "vtx_proton_e/D");
  m_tree->Branch("vtx_proton_costheta", &m_vtx_proton_costheta, "vtx_proton_costheta/D");
  m_tree->Branch("vtx_proton_phi", &m_vtx_proton_phi, "vtx_proton_phi/D");

  m_tree->Branch("vtx_neutron_px", &m_vtx_neutron_px, "vtx_neutron_px/D");
  m_tree->Branch("vtx_neutron_py", &m_vtx_neutron_py, "vtx_neutron_py/D");
  m_tree->Branch("vtx_neutron_pz", &m_vtx_neutron_pz, "vtx_neutron_pz/D");
  m_tree->Branch("vtx_neutron_p", &m_vtx_neutron_p, "vtx_neutron_p/D");
  m_tree->Branch("vtx_neutron_e", &m_vtx_neutron_e, "vtx_neutron_e/D");
  m_tree->Branch("vtx_neutron_m", &m_vtx_neutron_m, "vtx_neutron_m/D");
  m_tree->Branch("vtx_neutron_costheta", &m_vtx_neutron_costheta, "vtx_neutron_costheta/D");
  m_tree->Branch("vtx_neutron_phi", &m_vtx_neutron_phi, "vtx_neutron_phi/D");

  m_tree->Branch("vtx_pion_px", &m_vtx_pion_px, "vtx_pion_px/D");
  m_tree->Branch("vtx_pion_py", &m_vtx_pion_py, "vtx_pion_py/D");
  m_tree->Branch("vtx_pion_pz", &m_vtx_pion_pz, "vtx_pion_pz/D");
  m_tree->Branch("vtx_pion_p", &m_vtx_pion_p, "vtx_pion_p/D");
  m_tree->Branch("vtx_pion_e", &m_vtx_pion_e, "vtx_pion_e/D");
  m_tree->Branch("vtx_pion_costheta", &m_vtx_pion_costheta, "vtx_pion_costheta/D");
  m_tree->Branch("vtx_pion_phi", &m_vtx_pion_phi, "vtx_pion_phi/D");
  
  m_tree->Branch("vtx_proton_pion_p", &m_vtx_proton_pion_p, "vtx_proton_pion_p/D");
  m_tree->Branch("vtx_proton_pion_e", &m_vtx_proton_pion_e, "vtx_proton_pion_e/D");
  m_tree->Branch("vtx_proton_pion_m", &m_vtx_proton_pion_m, "vtx_proton_pion_m/D");
  
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

void Jpsi2pnpi::clearVariables() {

  m_raw_gpx->clear();
  m_raw_gpy->clear();
  m_raw_gpz->clear();
  m_raw_ge->clear();
  m_gn_dang->clear();
  m_raw_cstat->clear();
  m_raw_nhit->clear();
  m_raw_secmom->clear();

  m_run = 0;
  m_event = 0;
}

bool Jpsi2pnpi::buildJpsiToPNPi() {

  if (m_isMonteCarlo) saveGenInfo(); 
  
  SmartDataPtr<EvtRecEvent>evtRecEvent(eventSvc(),"/Event/EvtRec/EvtRecEvent");
  if(!evtRecEvent) return false;

  SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(), "/Event/EvtRec/EvtRecTrackCol");
  if(!evtRecTrkCol) return false;

  std::vector<int> iPGood, iMGood; 
  selectChargedTracks(evtRecEvent, evtRecTrkCol, iPGood, iMGood);

  if (m_ncharged != 2) return false;
  h_evtflw->Fill(1); // N_{Good} = 2 

  if( selectProtonPion(evtRecTrkCol, iPGood, iMGood)!=1 ) return false;

  selectNeutralTracks(evtRecEvent, evtRecTrkCol);
  if (m_ngam >= 30) return false;
  //h_evtflw->Fill(2); // N_{#gamma} < 30 

  return true; 
}


void Jpsi2pnpi::saveGenInfo() {
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

CLHEP::Hep3Vector Jpsi2pnpi::getOrigin() {
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


bool Jpsi2pnpi::passVertexSelection(CLHEP::Hep3Vector xorigin,
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


int Jpsi2pnpi::selectChargedTracks(SmartDataPtr<EvtRecEvent> evtRecEvent,
				   SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
				   std::vector<int> & iPGood,
				   std::vector<int> & iMGood) {

  CLHEP::Hep3Vector xorigin = getOrigin(); 

  std::vector<int> iGood;
  iGood.clear();
  iPGood.clear();
  iMGood.clear();
  
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
    if(mdcTrk->charge()>0) iPGood.push_back((*itTrk)->trackId());
    if(mdcTrk->charge()<0) iMGood.push_back((*itTrk)->trackId());

  } // end charged tracks

  m_ncharged = iGood.size();
  m_nptrk = iPGood.size();
  m_nmtrk = iMGood.size(); 

  if (m_nptrk > 0 && m_nmtrk > 0) {
    EvtRecTrackIterator itTrk_p = evtRecTrkCol->begin() + iPGood[0];
    EvtRecTrackIterator itTrk_m = evtRecTrkCol->begin() + iMGood[0];
    saveTrkInfo(itTrk_p, itTrk_m);
  }
  return iGood.size(); 
}


int Jpsi2pnpi::selectProtonPion(SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
				std::vector<int> iPGood,
				std::vector<int> iMGood) {
  int nppi = 0;
  bool evtflw_filled = false;
  
  for(unsigned int i1 = 0; i1 < iPGood.size(); i1++) {
    EvtRecTrackIterator itTrk_p = evtRecTrkCol->begin() + iPGood[i1];
    RecMdcTrack* mdcTrk_p = (*itTrk_p)->mdcTrack();
    if (mdcTrk_p->charge() < 0) continue; // only positive charged tracks

    for(unsigned int i2 = 0; i2 < iMGood.size(); i2++) {
      EvtRecTrackIterator itTrk_m = evtRecTrkCol->begin() + iMGood[i2];
      RecMdcTrack* mdcTrk_m = (*itTrk_m)->mdcTrack();
      if (mdcTrk_m->charge() > 0) continue; // only negative charged tracks

      //// polar angle for both pions
      //if ( ! ( fabs(cos(mdcTrk_p->theta())) < m_pion_polar_angle_max &&
      //	       fabs(cos(mdcTrk_m->theta())) < m_pion_polar_angle_max )) continue;
      //if ( !evtflw_filled ) h_evtflw->Fill(3); // |cos#theta| cut 

      //// pion momentum
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
 
      int pid_flag=0;
      int pid_flag1=0;
      int pid_flag2=0;
      if( (prob_p > prob_kp && prob_p > prob_pip && prob_p > m_prob_proton_min) &&
	  (prob_pim > prob_pb && prob_pim > prob_km && prob_pim > m_prob_pion_min) ){ pid_flag1=1; }

      if( (prob_pb > prob_km && prob_pb > prob_pim && prob_pb > m_prob_proton_min) &&
	  (prob_pip > prob_p && prob_pip > prob_kp && prob_pip > m_prob_pion_min) ){ pid_flag2=1; }

      
      if( (pid_flag1==0 && pid_flag2==0) || (pid_flag1==1 && pid_flag2==1) ) continue;
      if( pid_flag1==1 && pid_flag2==0){ pid_flag = ProtonPionMinusFlag; }
      if( pid_flag1==0 && pid_flag2==1){ pid_flag = AntiProtonPionPlusFlag; }

      m_pnpi_flag = pid_flag;
      if ( !evtflw_filled ) h_evtflw->Fill(2); //PID

      // apply vertex fit
      RecMdcKalTrack *pTrk = (*(evtRecTrkCol->begin()+iPGood[i1]))->mdcKalTrack();
      RecMdcKalTrack *mTrk = (*(evtRecTrkCol->begin()+iMGood[i2]))->mdcKalTrack();

      saveKalmanTrackInfo(pTrk, mTrk);

      if( pid_flag == ProtonPionMinusFlag )
	{
	  if( ! hasGoodProtonPiVertex(pTrk, mTrk, evtflw_filled) ) continue;
	}
      if( pid_flag == AntiProtonPionPlusFlag )
	{
	  if( ! hasGoodProtonPiVertex(mTrk, pTrk, evtflw_filled) ) continue;
	}      
      
      evtflw_filled = true;
      nppi++;
    }
  } 

  return nppi; 
}


void Jpsi2pnpi::calcTrackPID(EvtRecTrackIterator itTrk_p,
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
  pidp->identify(pidp->onlyPionKaonProton());
  pidp->calculate();
  if(pidp->IsPidInfoValid()) {
    prob_pip = pidp->probPion();
    prob_kp  = pidp->probKaon();
    prob_p   = pidp->probProton();
  }
}


bool Jpsi2pnpi::hasGoodProtonPiVertex(RecMdcKalTrack *pTrk,
				      RecMdcKalTrack *piTrk,
				      bool evtflw_filled) {

  HepLorentzVector pcms(0.011*m_ecms, 0., 0., m_ecms);

  HepLorentzVector p4_vtx_proton, p4_vtx_pion;
  HepLorentzVector p4_vtx_rec_proton_pion, p4_vtx_proton_pion;
  WTrackParameter wvpTrk, wvpiTrk;

  pTrk->setPidType(RecMdcKalTrack::proton);
  wvpTrk = WTrackParameter(PROTON_MASS, pTrk->getZHelixP(), pTrk->getZErrorP());
  
  piTrk->setPidType(RecMdcKalTrack::pion);
  wvpiTrk = WTrackParameter(PION_MASS, piTrk->getZHelix(), piTrk->getZError());
    
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
  vtxfit->AddTrack(0,  wvpTrk);
  vtxfit->AddTrack(1,  wvpiTrk);
  vtxfit->AddVertex(0, vxpar,0,1);

  if(!vtxfit->Fit(0)) return false;

  vtxfit->Swim(0);
      
  WTrackParameter wp  = vtxfit->wtrk(0);
  WTrackParameter wpi = vtxfit->wtrk(1);
  p4_vtx_proton = vtxfit->pfit(0) ;
  p4_vtx_pion = vtxfit->pfit(1) ;
  p4_vtx_rec_proton_pion = pcms - p4_vtx_proton - p4_vtx_pion;
  p4_vtx_proton_pion = p4_vtx_proton + p4_vtx_pion;

  // 0.75 < M_{#proton#pion}^{rec} == neutron < 1.13
  if( ! ( p4_vtx_rec_proton_pion.m() >= m_neutron_mass_min &&
          p4_vtx_rec_proton_pion.m() <= m_neutron_mass_max ) ) return false; 

  if( !evtflw_filled ) h_evtflw->Fill(3); // 0.75<M_{#proton#pi}^{rec}<1.13

  saveVtxInfo(p4_vtx_proton, p4_vtx_pion, p4_vtx_rec_proton_pion); 
  
  return true;
}


int Jpsi2pnpi::selectNeutralTracks(SmartDataPtr<EvtRecEvent> evtRecEvent,
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


void Jpsi2pnpi::saveTrkInfo(EvtRecTrackIterator itTrk_p,
			    EvtRecTrackIterator itTrk_m) {

  RecMdcTrack* mdcTrk_p = (*itTrk_p)->mdcTrack(); 
  m_trkp_p = mdcTrk_p->p();
  m_trkp_px = mdcTrk_p->px();
  m_trkp_py = mdcTrk_p->py();
  m_trkp_pz = mdcTrk_p->pz();
  m_trkp_theta = mdcTrk_p->theta();
  m_trkp_phi = mdcTrk_p->phi();
  
  if((*itTrk_p)->isEmcShowerValid()){
    RecEmcShower *emcTrk_p = (*itTrk_p)->emcShower();
    m_trkp_eraw = emcTrk_p->energy();
  }

  RecMdcTrack* mdcTrk_m = (*itTrk_m)->mdcTrack();
  m_trkm_p = mdcTrk_m->p();
  m_trkm_px = mdcTrk_m->px();
  m_trkm_py = mdcTrk_m->py();
  m_trkm_pz = mdcTrk_m->pz();
  m_trkm_theta = mdcTrk_m->theta();
  m_trkm_phi = mdcTrk_m->phi();
  
  if((*itTrk_m)->isEmcShowerValid()){
    RecEmcShower *emcTrk_m = (*itTrk_m)->emcShower();
    m_trkm_eraw = emcTrk_m->energy();
  }

}

void Jpsi2pnpi::saveGamInfo(std::vector<int> iGam,
			    SmartDataPtr<EvtRecTrackCol> evtRecTrkCol){

  HepLorentzVector p4_neutron = HepLorentzVector(m_vtx_neutron_px,
						 m_vtx_neutron_py,
						 m_vtx_neutron_pz,
						 m_vtx_neutron_e );

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

    double angle = p4.vect().angle(p4_neutron.vect());
    double dangle = angle*180.0/(CLHEP::pi);
    // if( dangle < 30 ) continue;
    m_gn_dang->push_back(dangle);

    int cstat = emcTrk->status();
    int nhit = emcTrk->numHits();
    double secmom = emcTrk->secondMoment();
    m_raw_cstat->push_back(cstat);
    m_raw_nhit->push_back(nhit);
    m_raw_secmom->push_back(secmom);

    // For test
    //std::cout << "cstat = " << cstat << std::endl;
    //std::cout << "nhit = " << nhit << std::endl;
    //std::cout << "second moment = " << secmom << std::endl;

    m_raw_gpx->push_back(p4.px());
    m_raw_gpy->push_back(p4.py());
    m_raw_gpz->push_back(p4.pz());
    m_raw_ge->push_back(p4.e());
  }
}

void Jpsi2pnpi::saveKalmanTrackInfo(RecMdcKalTrack *pTrk,
				    RecMdcKalTrack *mTrk){

  m_kal_trkp_p = pTrk->p();
  m_kal_trkp_px = pTrk->px();
  m_kal_trkp_py = pTrk->py();
  m_kal_trkp_pz = pTrk->pz();

  m_kal_trkm_p = mTrk->p();
  m_kal_trkm_px = mTrk->px();
  m_kal_trkm_py = mTrk->py();
  m_kal_trkm_pz = mTrk->pz();
}

void Jpsi2pnpi::saveVtxInfo(HepLorentzVector p4_vtx_proton,
			    HepLorentzVector p4_vtx_pion,
			    HepLorentzVector p4_vtx_rec_proton_pion){

  HepLorentzVector p4_vtx_proton_pion = p4_vtx_proton + p4_vtx_pion;

  m_vtx_proton_px = p4_vtx_proton.px();
  m_vtx_proton_py = p4_vtx_proton.py();
  m_vtx_proton_pz = p4_vtx_proton.pz();
  m_vtx_proton_p = p4_vtx_proton.rho();
  m_vtx_proton_e = p4_vtx_proton.e();      
  m_vtx_proton_costheta = p4_vtx_proton.cosTheta();
  m_vtx_proton_phi = p4_vtx_proton.phi();
  
  m_vtx_pion_px = p4_vtx_pion.px();
  m_vtx_pion_py = p4_vtx_pion.py();
  m_vtx_pion_pz = p4_vtx_pion.pz();
  m_vtx_pion_p = p4_vtx_pion.rho();
  m_vtx_pion_e = p4_vtx_pion.e();
  m_vtx_pion_costheta = p4_vtx_pion.cosTheta();
  m_vtx_pion_phi = p4_vtx_pion.phi();
  
  m_vtx_neutron_px = p4_vtx_rec_proton_pion.px();
  m_vtx_neutron_py = p4_vtx_rec_proton_pion.py();
  m_vtx_neutron_pz = p4_vtx_rec_proton_pion.pz();
  m_vtx_neutron_p = p4_vtx_rec_proton_pion.rho();
  m_vtx_neutron_e = p4_vtx_rec_proton_pion.e();
  m_vtx_neutron_costheta = p4_vtx_rec_proton_pion.cosTheta();
  m_vtx_neutron_phi = p4_vtx_rec_proton_pion.phi();
  
  m_vtx_neutron_m = p4_vtx_rec_proton_pion.m();
  
  m_vtx_proton_pion_p = p4_vtx_proton_pion.rho();
  m_vtx_proton_pion_e = p4_vtx_proton_pion.e();
  m_vtx_proton_pion_m = p4_vtx_proton_pion.m();
}


