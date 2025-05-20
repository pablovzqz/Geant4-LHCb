#include "run.hh"

MyRunAction::MyRunAction()
{
    
}

MyRunAction::~MyRunAction()
{}

void MyRunAction::BeginOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->SetVerboseLevel(2);//Para asegurarnos de que se está creando el archivo ROOT

    man->OpenFile("output.root");

    man->CreateNtuple("Hits1", "Hitsdata1");
    man->CreateNtupleIColumn("fEvent");//columna de ints
    man->CreateNtupleDColumn("fX");//columna de doubles
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->CreateNtupleSColumn("particle");//columna de strings
    man->CreateNtupleDColumn("Energy");
    man->FinishNtuple();

    man->CreateNtuple("Hits2", "Hitsdata2");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->CreateNtupleSColumn("particle");
    man->CreateNtupleDColumn("Energy");
    man->FinishNtuple();

    man->CreateNtuple("Hits3", "Hitsdata3");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->CreateNtupleSColumn("particle");
    man->CreateNtupleDColumn("Energy");
    man->FinishNtuple();

    man->CreateNtuple("Hits4", "Hitsdata4");
    man->CreateNtupleIColumn("fEvent");
    man->CreateNtupleDColumn("fX");
    man->CreateNtupleDColumn("fY");
    man->CreateNtupleDColumn("fZ");
    man->CreateNtupleSColumn("particle");
    man->CreateNtupleDColumn("Energy");
    man->FinishNtuple();
}

void MyRunAction::EndOfRunAction(const G4Run*)
{
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    man->Write();
    man->CloseFile();
}

