#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "Randomize.hh"


#include <vector>

class MyEventAction : public G4UserEventAction
{
public:
  MyEventAction();
  ~MyEventAction();

  virtual void BeginOfEventAction(const G4Event *);
  virtual void EndOfEventAction(const G4Event *);

  void AddEdep(G4double edep)
  {
    fEdep += edep;
  }

  void AddEVeto(G4double eveto)
  {
    fEVeto += eveto;
  }

  void AddEGamma(G4double egamma, G4int detNumber)
  {
    fEGa[detNumber] += egamma;
  }

  std::vector<G4double> &GetCloverEdep() { return fEGa; };

private:
  G4double fEdep, fEVeto;

  std::vector<G4double> fEGa;
};
#endif
