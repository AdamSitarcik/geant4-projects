#ifndef EVENT_HH
#define EVENT_HH

#include "G4UserEventAction.hh"
#include "G4Event.hh"
#include "G4AnalysisManager.hh"
#include "Randomize.hh"

#include "run.hh"

class MyEventAction : public G4UserEventAction
{
public:
  MyEventAction(MyRunAction*);
  ~MyEventAction();

  virtual void BeginOfEventAction(const G4Event*);
  virtual void EndOfEventAction(const G4Event*);

  void AddEdep(G4double edep) {
    fEdep += edep;
  }

  void AddEVeto(G4double eveto) {
    fEVeto += eveto;
  }

private:
  G4double fEdep, fEVeto;
};
#endif
