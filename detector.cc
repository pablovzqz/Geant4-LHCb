#include "detector.hh"


MySensitiveDetector::MySensitiveDetector(G4String name) : G4VSensitiveDetector(name)
{}

MySensitiveDetector::~MySensitiveDetector()
{}

G4bool MySensitiveDetector::ProcessHits(G4Step *aStep, G4TouchableHistory *ROhist)
{
    G4Track *track = aStep->GetTrack();

    //track->SetTrackStatus(fStopAndKill);//Esta línea hacía que 
                                //la traza muriese en el detector

    G4StepPoint *preStepPoint = aStep->GetPreStepPoint();
    G4StepPoint *postStepPoint = aStep->GetPostStepPoint();

    //G4ThreeVector posPhoton = preStepPoint->GetPosition();

    //G4cout << "Photon position" << posPhoton << G4endl;

    const G4VTouchable *touchable = aStep->GetPreStepPoint()->GetTouchable();

    G4int copyNo = touchable->GetCopyNumber();

    //G4cout << "Copy Number: " << copyNo << G4endl; //serviume pa ver que as trazas non pasaban da primeira capa

    G4VPhysicalVolume *physVol = touchable->GetVolume();
    G4ThreeVector posDetector = physVol->GetTranslation();

    //G4cout << "Detector Position: " << posDetector << G4endl;

    G4int evt = G4RunManager::GetRunManager()->GetCurrentEvent()->GetEventID();
    
    G4AnalysisManager *man = G4AnalysisManager::Instance();

    G4String particleName = track->GetDefinition()->GetParticleName();

    G4double particleEnergy = track->GetTotalEnergy();

    int detectorIndex = -1;
    if (copyNo < 100) detectorIndex = 0;//Cada capa de detectores cuenta con 100 detectores
    else if (copyNo < 200) detectorIndex = 1;
    else if (copyNo < 300) detectorIndex = 2;
    else if (copyNo < 400) detectorIndex = 3;

    if (detectorIndex != -1) {//Nos aseguramos de que alguno de los detectores esta firing
        man->FillNtupleIColumn(detectorIndex, 0, evt);
        man->FillNtupleDColumn(detectorIndex, 1, posDetector.x());
        man->FillNtupleDColumn(detectorIndex, 2, posDetector.y());
        man->FillNtupleDColumn(detectorIndex, 3, posDetector.z());
        man->FillNtupleSColumn(detectorIndex, 4, particleName);
        man->FillNtupleDColumn(detectorIndex, 5, particleEnergy);
        man->AddNtupleRow(detectorIndex);
    }


    //Código que me imprime un mensaje si alguna de las partículas es un muón o antimuón
    if (track->GetDefinition()->GetParticleName() == "mu+" || 
    track->GetDefinition()->GetParticleName() == "mu-") 
    {
    G4cout << "Muón detectado: " << track->GetPosition() << G4endl;
    }

    return 0;
}
