#include "detector.hh"


MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();

    track->SetTrackStatus(fStopAndKill);

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    G4ThreeVector posPhoton = preStepPoint->GetPosition();

    //G4cout << "Photon position" << posPhoton << G4endl;

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    G4int copyNo = touchable->GetCopyNumber();

    //G4cout << "Copy Number: " << copyNo << G4endl; //serviume pa ver que as trazas non pasaban da primeira capa

    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    //G4cout << "Detector Position: " << posDetector << G4endl;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    
    G4AnalysisManager *man = G4AnalysisManager::Instance();
    if (copyNo < 100) {
    man->FillNtupleIColumn(0, evt);
    man->FillNtupleDColumn(1, posDetector.x());
    man->FillNtupleDColumn(2, posDetector.y());
    man->FillNtupleDColumn(3, posDetector.z());
    man->AddNtupleRow(0); 
    }

    else if (copyNo < 200) {
        man->FillNtupleIColumn(4, evt);
        man->FillNtupleDColumn(5, posDetector.x());
        man->FillNtupleDColumn(6, posDetector.y());
        man->FillNtupleDColumn(7, posDetector.z());
        man->AddNtupleRow(1); 
    }

    else if (copyNo < 300) {
        man->FillNtupleIColumn(8, evt);
        man->FillNtupleDColumn(9, posDetector.x());
        man->FillNtupleDColumn(10, posDetector.y());
        man->FillNtupleDColumn(11, posDetector.z());
        man->AddNtupleRow(2); 
    }

    else if (copyNo < 400) {
        man->FillNtupleIColumn(12, evt);
        man->FillNtupleDColumn(13, posDetector.x());
        man->FillNtupleDColumn(14, posDetector.y());
        man->FillNtupleDColumn(15, posDetector.z());
        man->AddNtupleRow(2); 
    }

    //Código que me imprime un mensaje si alguna de las partículas es un muón o antimuón
    if (track->GetDefinition()->GetParticleName() == "mu+" || 
    track->GetDefinition()->GetParticleName() == "mu-") 
    {
    G4cout << "Muón detectado: " << track->GetPosition() << G4endl;
    }

    return 0;
}
