#ifndef RUN_HH
#define RUN_HH

#include "G4UserRunAction.hh"

#include "G4AnalysisManager.hh"
#include "G4Run.hh"


class MyRunAction : public G4UserRunAction
{
public:
  MyRunAction();
  ~MyRunAction();

  virtual void BeginRunAction(const G4Run*);
  virtual void EndRunAction(const G4Run*);
};

#endif
