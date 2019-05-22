// -*- C++ -*-
//
//
// Description: J/psi -> Anything (Inclusive decay) 
//
// Original Author:  SHI Xin <shixin@ihep.ac.cn>
//         Created:  [2016-09-12 Mon 12:22] 
//


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

class Jpsi2incl : public Algorithm {
  
public:
  Jpsi2incl(const std::string&, ISvcLocator*);
  ~Jpsi2incl(); 
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
  double m_pion_polar_angle_max;
  double m_pion_momentum_max;
  double m_prob_pion_min;
  double m_dipion_mass_min; 
  double m_dipion_mass_max;
  double m_pipi_costheta_max;
  double m_pipisys_costheta_max; 

  // output file
  std::string m_output_filename;
  bool m_isMonteCarlo; 
  bool m_isZCcondition;
  TFile* m_fout; 
  
  // define Histograms
  TH1F* h_cutflw; 
  
  // define Trees
  TTree* m_tree;

  // common info 
  int m_run;
  int m_event;

  // charged tracks
  int m_ncharged;
  int m_nptrk;
  int m_nmtrk;

  std::vector<double> *m_trkp_p; 
  std::vector<double> *m_trkp_px; 
  std::vector<double> *m_trkp_py; 
  std::vector<double> *m_trkp_pz; 
  std::vector<double> *m_trkp_theta; 
  std::vector<double> *m_trkp_phi; 
  double m_trkp_eraw; 
  
  std::vector<double> *m_trkm_p; 
  std::vector<double> *m_trkm_px; 
  std::vector<double> *m_trkm_py; 
  std::vector<double> *m_trkm_pz; 
  std::vector<double> *m_trkm_theta; 
  std::vector<double> *m_trkm_phi; 
  double m_trkm_eraw; 

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
  int m_npipi; 
  std::vector<double> *m_pip_p;
  std::vector<double> *m_pip_px;
  std::vector<double> *m_pip_py;
  std::vector<double> *m_pip_pz;
  std::vector<double> *m_pip_theta;

  std::vector<double> *m_pim_p;
  std::vector<double> *m_pim_px;
  std::vector<double> *m_pim_py;
  std::vector<double> *m_pim_pz;
  std::vector<double> *m_pim_theta;

  // pion PID info
  std::vector<double> *m_pip_prob_pip;
  std::vector<double> *m_pip_prob_kp;
  std::vector<double> *m_pip_prob_p;

  std::vector<double> *m_pim_prob_pim;
  std::vector<double> *m_pim_prob_km;
  std::vector<double> *m_pim_prob_pb;
  
  // fitted info
  std::vector<double> *m_vtx_pip_px; 
  std::vector<double> *m_vtx_pip_py; 
  std::vector<double> *m_vtx_pip_pz; 
  std::vector<double> *m_vtx_pip_e;
  std::vector<double> *m_vtx_pim_px; 
  std::vector<double> *m_vtx_pim_py; 
  std::vector<double> *m_vtx_pim_pz; 
  std::vector<double> *m_vtx_pim_e;

  std::vector<double> *m_vtx_mpipi;
  std::vector<double> *m_vtx_mrecpipi;
  std::vector<double> *m_vtx_cospipi;
  std::vector<double> *m_vtx_cos2pisys; 
    
  // check MDC and EMC match
  long m_pion_matched;
  long m_lep_matched;

  // jpsi2incl
  int m_ntrk; 
  int m_npho;

  //  MC truth info
  int m_indexmc;
  int m_pdgid[100];
  int m_trkidx[100];
  int m_motheridx[100];
  int m_motherpid[100];

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
  bool buildJpsiToInclusive();
  void saveGenInfo(); 
  void saveTrkInfo(EvtRecTrackIterator,
		   EvtRecTrackIterator);
  void savePionInfo(RecMdcKalTrack *,
		    RecMdcKalTrack *);
  void saveVtxInfo(HepLorentzVector,
		   HepLorentzVector,
		   HepLorentzVector,
		   HepLorentzVector,
		   double,
		   double);  
  void savePidInfo(double, double, double, double, double, double);

  int selectChargedTracks(SmartDataPtr<EvtRecEvent>,
			  SmartDataPtr<EvtRecTrackCol>,
			  std::vector<int> &,
			  std::vector<int> &); 
  int selectPionPlusPionMinus(SmartDataPtr<EvtRecTrackCol>,
			      std::vector<int>,
			      std::vector<int>);
  void calcTrackPID(EvtRecTrackIterator,
		    double&,
		    double&,
		    double&);
  bool hasGoodPiPiVertex(RecMdcKalTrack *,
			 RecMdcKalTrack *,
			 HepLorentzVector &, 
			 HepLorentzVector &, 
			 HepLorentzVector &, 
			 HepLorentzVector &,
			 double &,
			 double &, 
			 bool&,
			 bool&,
			 bool&);
  bool passVertexSelection(CLHEP::Hep3Vector,
			   RecMdcKalTrack* ); 
  CLHEP::Hep3Vector getOrigin();
}; 


//
// module declare
//

DECLARE_ALGORITHM_FACTORY( Jpsi2incl )
DECLARE_FACTORY_ENTRIES( Jpsi2incl ) {
  DECLARE_ALGORITHM(Jpsi2incl);
}

LOAD_FACTORY_ENTRIES( Jpsi2incl )

//
// constants
//

const double PION_MASS = 0.139570;

const int ELECTRON_PDG_ID = 11;
const int MUON_PDG_ID = 13;
const int PIONPLUS_PDG_ID = 211;

const int JPSI_PDG_ID = 443;
const int PSI2S_PDG_ID = 100443;
const int PROTON_PDG_ID = 2212; 
const int NEUTRON_PDG_ID = 2112; 

enum {
  CUT_RAW,  
  CUT_NPM, 
  CUT_COSTHETA, 
  CUT_PION, 
  CUT_PID, 
  CUT_COSTHETA_PIPI, 
  CUT_COSTHETA_PIPISYS, 
  CUT_MPIPI,
  CUT_TOTAL
}; 

//
// member functions
//
  
Jpsi2incl::Jpsi2incl(const std::string& name, ISvcLocator* pSvcLocator) :
  Algorithm(name, pSvcLocator),
  m_tree(0),
  m_trkp_p(0),
  m_trkp_px(0),
  m_trkp_py(0),
  m_trkp_pz(0),
  m_trkp_theta(0),
  m_trkp_phi(0),
  m_trkm_p(0),
  m_trkm_px(0),
  m_trkm_py(0),
  m_trkm_pz(0),
  m_trkm_theta(0),
  m_trkm_phi(0),
  m_pip_p(0),
  m_pip_px(0),
  m_pip_py(0),
  m_pip_pz(0),
  m_pip_theta(0),
  m_pim_p(0),
  m_pim_px(0),
  m_pim_py(0),
  m_pim_pz(0),
  m_pim_theta(0),
  m_pip_prob_pip(0),
  m_pip_prob_kp(0),
  m_pip_prob_p(0),
  m_pim_prob_pim(0),
  m_pim_prob_km(0),
  m_pim_prob_pb(0),
  m_vtx_pip_px(0), 
  m_vtx_pip_py(0), 
  m_vtx_pip_pz(0), 
  m_vtx_pip_e(0), 
  m_vtx_pim_px(0), 
  m_vtx_pim_py(0), 
  m_vtx_pim_pz(0), 
  m_vtx_pim_e(0),
  m_vtx_mpipi(0), 
  m_vtx_mrecpipi(0),
  m_vtx_cospipi(0), 
  m_vtx_cos2pisys(0) 
{
  declareProperty("OutputFileName", m_output_filename);
  declareProperty("IsMonteCarlo", m_isMonteCarlo);
  declareProperty("ZChi_AnaCondition", m_isZCcondition=false);
  //declareProperty("ZChi_AnaCondition", m_isZCcondition=true);
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
  declareProperty("PionPolarAngleMax", m_pion_polar_angle_max=0.99);
  declareProperty("PionMomentumMax", m_pion_momentum_max=1.9); 
  declareProperty("ProbPionMin", m_prob_pion_min=0.001);
  declareProperty("DipionMassMin", m_dipion_mass_min=3.0); 
  declareProperty("DipionMassMax", m_dipion_mass_max=3.2); 
  declareProperty("PiPiCosthetaMax", m_pipi_costheta_max=0.99);
  declareProperty("PiPiSysCosthetaMax", m_pipisys_costheta_max=0.99);
}


StatusCode Jpsi2incl::initialize(){
  MsgStream log(msgSvc(), name());

  m_fout = new TFile(m_output_filename.c_str(), "RECREATE");
  m_fout->cd(); 

  book_histogram(); 
  book_tree(); 

  log << MSG::INFO << "successfully return from initialize()" <<endmsg;
  return StatusCode::SUCCESS;
}


StatusCode Jpsi2incl::execute() {
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in execute()" << endreq;

  clearVariables(); 
  
  h_cutflw->Fill(CUT_RAW); // raw 
  SmartDataPtr<Event::EventHeader>eventHeader(eventSvc(),"/Event/EventHeader");
  if(!eventHeader) return StatusCode::FAILURE;

  m_run = eventHeader->runNumber();
  m_event = eventHeader->eventNumber();
  
  if (buildJpsiToInclusive()) {
    m_tree->Fill(); // only fill tree for the selected events 
  }

  return StatusCode::SUCCESS; 
}

StatusCode Jpsi2incl::finalize() {
  MsgStream log(msgSvc(), name());
  log << MSG::INFO << "in finalize()" << endmsg;

  m_fout->cd();
  m_tree->Write();
  h_cutflw->Write();
  m_fout->Close();
  
  return StatusCode::SUCCESS;
}


Jpsi2incl::~Jpsi2incl() {
}


void Jpsi2incl::book_histogram() {

  h_cutflw = new TH1F("hcutflw", "cutflow", CUT_TOTAL, 0, CUT_TOTAL);
  if (!h_cutflw) return;
  h_cutflw->GetXaxis()->SetBinLabel(CUT_RAW+1, "raw");
  h_cutflw->GetXaxis()->SetBinLabel(CUT_NPM+1, "N^{+}>=1 N^{-}>=1");
  h_cutflw->GetXaxis()->SetBinLabel(CUT_COSTHETA+1, "|cos#theta|<0.99");
  h_cutflw->GetXaxis()->SetBinLabel(CUT_PION+1, "|p|<1.9");
  h_cutflw->GetXaxis()->SetBinLabel(CUT_PID+1, "PID"); 
  h_cutflw->GetXaxis()->SetBinLabel(CUT_COSTHETA_PIPI+1, "cos#theta_{#pi^{+}#pi^{-}}<0.99");
  h_cutflw->GetXaxis()->SetBinLabel(CUT_COSTHETA_PIPISYS+1, "cos#theta_{#pi#pi sys}<0.99");
  h_cutflw->GetXaxis()->SetBinLabel(CUT_MPIPI+1, "3<M_{#pi#pi}^{rec}<3.2");
}


void Jpsi2incl::book_tree() {

  m_tree=new TTree("tree", "jpsi2incl");
  if (!m_tree) return; 

  //commom info
  m_tree->Branch("run",&m_run,"run/I");
  m_tree->Branch("event",&m_event,"event/I");
	  
  //charged tracks
  m_tree->Branch("ncharged", &m_ncharged, "ncharged/I");
  m_tree->Branch("nptrk", &m_nptrk, "nptrk/I");
  m_tree->Branch("nmtrk", &m_nmtrk, "nmtrk/I");

  m_tree->Branch("trkp_p", &m_trkp_p); 
  m_tree->Branch("trkp_px", &m_trkp_px); 
  m_tree->Branch("trkp_py", &m_trkp_py); 
  m_tree->Branch("trkp_pz", &m_trkp_pz); 
  m_tree->Branch("trkp_theta", &m_trkp_theta); 
  m_tree->Branch("trkp_phi", &m_trkp_phi); 
  m_tree->Branch("trkp_eraw", &m_trkp_eraw, "trkp_eraw/D"); 

  m_tree->Branch("trkm_p", &m_trkm_p); 
  m_tree->Branch("trkm_px", &m_trkm_px); 
  m_tree->Branch("trkm_py", &m_trkm_py); 
  m_tree->Branch("trkm_pz", &m_trkm_pz); 
  m_tree->Branch("trkm_theta", &m_trkm_theta); 
  m_tree->Branch("trkm_phi", &m_trkm_phi); 
  m_tree->Branch("trkm_eraw", &m_trkm_eraw, "trkm_eraw/D"); 
	  
  //vertex
  m_tree->Branch("vr0", &m_vr0, "vr0/D");
  m_tree->Branch("vz0", &m_vz0, "vz0/D");

  // PID info
  m_tree->Branch("prob_pip", &m_prob_pip, "prob_pip/D"); 
  m_tree->Branch("prob_pim", &m_prob_pim, "prob_pim/D"); 
  m_tree->Branch("prob_kp", &m_prob_kp, "prob_kp/D"); 
  m_tree->Branch("prob_km", &m_prob_km, "prob_km/D"); 
  m_tree->Branch("prob_p", &m_prob_p, "prob_p/D"); 
  m_tree->Branch("prob_pb", &m_prob_pb, "prob_pb/D"); 

  // save pion info
  m_tree->Branch("npipi", &m_npipi, "npipi/I");
  m_tree->Branch("pip_p", &m_pip_p);
  m_tree->Branch("pip_px", &m_pip_px);
  m_tree->Branch("pip_py", &m_pip_py);
  m_tree->Branch("pip_pz", &m_pip_pz);
  m_tree->Branch("pip_theta", &m_pip_theta);

  m_tree->Branch("pim_p", &m_pim_p);
  m_tree->Branch("pim_px", &m_pim_px);
  m_tree->Branch("pim_py", &m_pim_py);
  m_tree->Branch("pim_pz", &m_pim_pz);
  m_tree->Branch("pim_theta", &m_pim_theta);

  // save pion pid info
  m_tree->Branch("pip_prob_pip", &m_pip_prob_pip);
  m_tree->Branch("pip_prob_kp", &m_pip_prob_kp);
  m_tree->Branch("pip_prob_p", &m_pip_prob_p);

  m_tree->Branch("pim_prob_pim", &m_pim_prob_pim);
  m_tree->Branch("pim_prob_km", &m_pim_prob_km);
  m_tree->Branch("pim_prob_pb", &m_pim_prob_pb);

  // fitted info
  m_tree->Branch("vtx_pip_px", &m_vtx_pip_px);
  m_tree->Branch("vtx_pip_py", &m_vtx_pip_py);
  m_tree->Branch("vtx_pip_pz", &m_vtx_pip_pz);
  m_tree->Branch("vtx_pip_e", &m_vtx_pip_e);
  m_tree->Branch("vtx_pim_px", &m_vtx_pim_px);
  m_tree->Branch("vtx_pim_py", &m_vtx_pim_py);
  m_tree->Branch("vtx_pim_pz", &m_vtx_pim_pz);
  m_tree->Branch("vtx_pim_e", &m_vtx_pim_e);

  m_tree->Branch("vtx_mpipi", &m_vtx_mpipi);
  m_tree->Branch("vtx_mrecpipi", &m_vtx_mrecpipi);
  m_tree->Branch("vtx_cospipi", &m_vtx_cospipi);
  m_tree->Branch("vtx_cos2pisys", &m_vtx_cos2pisys);
  
  // MC truth info
  if (!m_isMonteCarlo) return; 
  m_tree->Branch("indexmc", &m_indexmc, "indexmc/I");
  m_tree->Branch("pdgid", m_pdgid, "m_pdgid[100]/I");
  m_tree->Branch("trkidx", m_trkidx, "m_trkidx[100]/I");
  m_tree->Branch("motherpid", m_motherpid, "m_motherpid[100]/I");
  m_tree->Branch("motheridx", m_motheridx, "m_motheridx[100]/I");

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

void Jpsi2incl::clearVariables() {
  m_run = 0;
  m_event = 0;

  // MC Topology
  m_indexmc = 0;
  for(int i=0;i<100;i++)
    {
      m_pdgid[i] = 0;
      m_trkidx[i] = 0;
      m_motheridx[i] = 0;
      m_motherpid[i] = 0;
    }

  m_trkp_p->clear();
  m_trkp_px->clear();
  m_trkp_py->clear();
  m_trkp_pz->clear();
  m_trkp_theta->clear();
  m_trkp_phi->clear();

  m_trkm_p->clear();
  m_trkm_px->clear();
  m_trkm_py->clear();
  m_trkm_pz->clear();
  m_trkm_theta->clear();
  m_trkm_phi->clear();

  m_pip_p->clear();
  m_pip_px->clear();
  m_pip_py->clear();
  m_pip_pz->clear();
  m_pip_theta->clear();

  m_pim_p->clear();
  m_pim_px->clear();
  m_pim_py->clear();
  m_pim_pz->clear();
  m_pim_theta->clear();

  m_pip_prob_pip->clear();
  m_pip_prob_kp->clear();
  m_pip_prob_p->clear();

  m_pim_prob_pim->clear();
  m_pim_prob_km->clear();
  m_pim_prob_pb->clear();

  m_vtx_pip_px->clear();
  m_vtx_pip_py->clear();
  m_vtx_pip_pz->clear();
  m_vtx_pip_e->clear();
  m_vtx_pim_px->clear();
  m_vtx_pim_py->clear();
  m_vtx_pim_pz->clear();
  m_vtx_pim_e->clear();
  
  m_vtx_mpipi->clear(); 
  m_vtx_mrecpipi->clear();
  m_vtx_cospipi->clear(); 
  m_vtx_cos2pisys->clear(); 
}


bool Jpsi2incl::buildJpsiToInclusive() {

  if (m_isMonteCarlo) saveGenInfo(); 
  
  SmartDataPtr<EvtRecEvent>evtRecEvent(eventSvc(),"/Event/EvtRec/EvtRecEvent");
  if(!evtRecEvent) return false;

  SmartDataPtr<EvtRecTrackCol> evtRecTrkCol(eventSvc(), "/Event/EvtRec/EvtRecTrackCol");
  if(!evtRecTrkCol) return false;

  std::vector<int> iPGood, iMGood; 
  selectChargedTracks(evtRecEvent, evtRecTrkCol, iPGood, iMGood);

  if (m_nptrk < 1 || m_nmtrk < 1) return false;
  h_cutflw->Fill(CUT_NPM); // N^{+} >= 1 and N^{-} >= 1  

  m_npipi = selectPionPlusPionMinus(evtRecTrkCol, iPGood, iMGood);  
  if(m_npipi==0)return false;

  return true; 
}


void Jpsi2incl::saveGenInfo() {
  SmartDataPtr<Event::McParticleCol> mcParticleCol(eventSvc(), "/Event/MC/McParticleCol");
  HepLorentzVector mc_psip,mc_pip,mc_pim,mc_ep,mc_em,mc_mup,mc_mum,mc_p,mc_pb,mc_n,mc_nb,mc_jpsi;

  // MC Topology 
  {
    int m_numParticle = 0;
    bool Decay = false;
    int rootIndex = -1;
    Event::McParticleCol::iterator iter_mc_topo = mcParticleCol->begin();
    for (; iter_mc_topo != mcParticleCol->end(); iter_mc_topo++) {
      if ((*iter_mc_topo)->primaryParticle() && Decay) { rootIndex++; continue; }
      if ((*iter_mc_topo)->primaryParticle()) continue;
      if (!(*iter_mc_topo)->decayFromGenerator()) continue;
      if ((*iter_mc_topo)->particleProperty() == PSI2S_PDG_ID) {
        Decay = true;
        rootIndex = (*iter_mc_topo)->trackIndex();
      }
      if (!Decay) continue;
      int mpdgid = ((*iter_mc_topo)->mother()).particleProperty();
      int mcidx = (((*iter_mc_topo)->mother()).particleProperty() == PSI2S_PDG_ID) ? 0 : ((*iter_mc_topo)->mother()).trackIndex() - rootIndex;
      //int mcidx = ((*iter_mc_topo)->mother()).trackIndex() - rootIndex;
      int pdgid = (*iter_mc_topo)->particleProperty();
      int trkidx = (*iter_mc_topo)->trackIndex() - rootIndex;
      m_pdgid[m_numParticle] = pdgid;
      m_trkidx[m_numParticle] = trkidx;
      m_motheridx[m_numParticle] = mcidx;
      m_motherpid[m_numParticle] = mpdgid;
      m_numParticle++;
    }
    m_indexmc = m_numParticle;
  }


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

CLHEP::Hep3Vector Jpsi2incl::getOrigin() {
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


bool Jpsi2incl::passVertexSelection(CLHEP::Hep3Vector xorigin,
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


int Jpsi2incl::selectChargedTracks(SmartDataPtr<EvtRecEvent> evtRecEvent,
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
    //saveTrkInfo(itTrk_p, itTrk_m);
  }
  return iGood.size(); 
}

int Jpsi2incl::selectPionPlusPionMinus(SmartDataPtr<EvtRecTrackCol> evtRecTrkCol,
				       std::vector<int> iPGood,
				       std::vector<int> iMGood) {
  int npipi = 0;
  bool cutflw_costheta_filled = false;
  bool cutflw_pion_filled = false;
  bool cutflw_pid_filled = false;
  bool cutflw_costheta_pipi_filled = false;
  bool cutflw_costheta_pipisys_filled = false;
  bool cutflw_mpipi_filled = false;
  
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
      if ( !cutflw_costheta_filled ) h_cutflw->Fill(CUT_COSTHETA); 
      cutflw_costheta_filled = true;
      
      // pion momentum
      if ( ! ( fabs(mdcTrk_p->p()) < m_pion_momentum_max  &&
      	       fabs(mdcTrk_m->p()) < m_pion_momentum_max )) continue;

      if ( !cutflw_pion_filled ) h_cutflw->Fill(CUT_PION); 
      cutflw_pion_filled = true;
      
      // track PID
      double prob_pip, prob_kp, prob_pim, prob_km, prob_p, prob_pb; 
      calcTrackPID(itTrk_p, prob_pip, prob_kp, prob_p);  
      calcTrackPID(itTrk_m, prob_pim, prob_km, prob_pb);

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

      if ( !cutflw_pid_filled ) h_cutflw->Fill(CUT_PID); 
      cutflw_pid_filled = true;
   
      // apply vertex fit
      RecMdcKalTrack *pipTrk = (*(evtRecTrkCol->begin()+iPGood[i1]))->mdcKalTrack();
      RecMdcKalTrack *pimTrk = (*(evtRecTrkCol->begin()+iMGood[i2]))->mdcKalTrack();

      HepLorentzVector p4_vtx_pip, p4_vtx_pim, p4_vtx_pipi, p4_vtx_recpipi;
      double cospipi, cos2pisys; 
      if (! hasGoodPiPiVertex(pipTrk, pimTrk,
			      p4_vtx_pip, p4_vtx_pim, p4_vtx_pipi, p4_vtx_recpipi,
			      cospipi, cos2pisys, cutflw_costheta_pipi_filled,
			      cutflw_costheta_pipisys_filled, cutflw_mpipi_filled) ) continue;

      saveVtxInfo(p4_vtx_pip, p4_vtx_pim, p4_vtx_pipi, p4_vtx_recpipi, cospipi, cos2pisys); 
      savePionInfo(pipTrk, pimTrk);
      
      savePidInfo(prob_pip, prob_kp, prob_p,  prob_pim, prob_km, prob_pb);

      //  Save track info (RecMdcTrack) 
      saveTrkInfo(itTrk_p, itTrk_m);

      npipi++;
    }
  } 

  return npipi; 
}


void Jpsi2incl::calcTrackPID(EvtRecTrackIterator itTrk_p,
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

bool Jpsi2incl::hasGoodPiPiVertex(RecMdcKalTrack *pipTrk,
				  RecMdcKalTrack *pimTrk,
				  HepLorentzVector &p4_vtx_pip, 
				  HepLorentzVector &p4_vtx_pim, 
				  HepLorentzVector &p4_vtx_pipi, 
				  HepLorentzVector &p4_vtx_recpipi,
				  double &cospipi,
				  double &cos2pisys, 
				  bool &cutflw_costheta_pipi_filled, 
				  bool &cutflw_costheta_pipisys_filled, 
				  bool &cutflw_mpipi_filled) {

  HepLorentzVector pcms;
  if (!m_isZCcondition){
    pcms = HepLorentzVector(0.011*m_ecms, 0., 0., m_ecms);
  }
  else{ pcms = HepLorentzVector(0.011*m_ecms, -0.001, 0.005, m_ecms); }
  //HepLorentzVector pcms(0.011*m_ecms, 0., 0., m_ecms);

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

  cospipi = cos(p4_vtx_pip.vect().angle(p4_vtx_pim.vect()));
  cos2pisys = (p4_vtx_pip + p4_vtx_pim).cosTheta();

  //if( ! (cospipi < m_pipi_costheta_max) ) return false;
  if( !cutflw_costheta_pipi_filled ) h_cutflw->Fill(CUT_COSTHETA_PIPI); 
  cutflw_costheta_pipi_filled = true; 

  //if( ! (fabs(cos2pisys) < m_pipisys_costheta_max ) ) return false;
  if( !cutflw_costheta_pipisys_filled ) h_cutflw->Fill(CUT_COSTHETA_PIPISYS); 
  cutflw_costheta_pipisys_filled = true; 

  if( ! ( p4_vtx_recpipi.m() >= m_dipion_mass_min &&
	  p4_vtx_recpipi.m() <= m_dipion_mass_max) ) return false;
  if( !cutflw_mpipi_filled ) h_cutflw->Fill(CUT_MPIPI); // 3<M_{#pi#pi}^{rec}<3.2
  cutflw_mpipi_filled = true; 
  
  return true;
}


void Jpsi2incl::saveTrkInfo(EvtRecTrackIterator itTrk_p,
			    EvtRecTrackIterator itTrk_m) {

  RecMdcTrack* mdcTrk_p = (*itTrk_p)->mdcTrack(); 
  m_trkp_p->push_back(mdcTrk_p->p());
  m_trkp_px->push_back(mdcTrk_p->px());
  m_trkp_py->push_back(mdcTrk_p->py());
  m_trkp_pz->push_back(mdcTrk_p->pz());
  m_trkp_theta->push_back(mdcTrk_p->theta());
  m_trkp_phi->push_back(mdcTrk_p->phi());
  
  if((*itTrk_p)->isEmcShowerValid()){
    RecEmcShower *emcTrk_p = (*itTrk_p)->emcShower();
    m_trkp_eraw = emcTrk_p->energy();
  }

  RecMdcTrack* mdcTrk_m = (*itTrk_m)->mdcTrack();
  m_trkm_p->push_back(mdcTrk_m->p());
  m_trkm_px->push_back(mdcTrk_m->px());
  m_trkm_py->push_back(mdcTrk_m->py());
  m_trkm_pz->push_back(mdcTrk_m->pz());
  m_trkm_theta->push_back(mdcTrk_m->theta());
  m_trkm_phi->push_back(mdcTrk_m->phi());
  
  if((*itTrk_m)->isEmcShowerValid()){
    RecEmcShower *emcTrk_m = (*itTrk_m)->emcShower();
    m_trkm_eraw = emcTrk_m->energy();
  }
}


void Jpsi2incl::savePionInfo(RecMdcKalTrack *pipTrk,
			     RecMdcKalTrack *pimTrk){

  m_pip_p->push_back(pipTrk->p());
  m_pip_px->push_back(pipTrk->px());
  m_pip_py->push_back(pipTrk->py());
  m_pip_pz->push_back(pipTrk->pz());
  m_pip_theta->push_back(pipTrk->theta());

  m_pim_p->push_back(pimTrk->p());
  m_pim_px->push_back(pimTrk->px());
  m_pim_py->push_back(pimTrk->py());
  m_pim_pz->push_back(pimTrk->pz());
  m_pim_theta->push_back(pimTrk->theta());
  
}

void Jpsi2incl::saveVtxInfo(HepLorentzVector p4_vtx_pip,
			    HepLorentzVector p4_vtx_pim,
			    HepLorentzVector p4_vtx_pipi,
			    HepLorentzVector p4_vtx_recpipi,
			    double cospipi,
			    double cos2pisys){

  m_vtx_pip_px->push_back(p4_vtx_pip.px());
  m_vtx_pip_py->push_back(p4_vtx_pip.py());
  m_vtx_pip_pz->push_back(p4_vtx_pip.pz());
  m_vtx_pip_e->push_back(p4_vtx_pip.e());

  m_vtx_pim_px->push_back(p4_vtx_pim.px());
  m_vtx_pim_py->push_back(p4_vtx_pim.py());
  m_vtx_pim_pz->push_back(p4_vtx_pim.pz());
  m_vtx_pim_e->push_back(p4_vtx_pim.e());

  m_vtx_mrecpipi->push_back(p4_vtx_recpipi.m());
  m_vtx_mpipi->push_back(p4_vtx_pipi.m());
  m_vtx_cospipi->push_back(cospipi);
  m_vtx_cos2pisys->push_back(cos2pisys); 

}

void Jpsi2incl::savePidInfo(double prob_pip,
			    double prob_kp,
			    double prob_p,
			    double prob_pim,
			    double prob_km,
			    double prob_pb){


  m_pip_prob_pip->push_back(prob_pip);
  m_pip_prob_kp->push_back(prob_kp);
  m_pip_prob_p->push_back(prob_p);

  m_pim_prob_pim->push_back(prob_pim);
  m_pim_prob_km->push_back(prob_km);
  m_pim_prob_pb->push_back(prob_pb);

}
