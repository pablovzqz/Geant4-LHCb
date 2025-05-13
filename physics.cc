#include "G4DecayPhysics.hh"
#include "G4EmStandardPhysics.hh"
#include "G4HadronPhysicsFTFP_BERT.hh"
#include "physics.hh"  


MyPhysicsList::MyPhysicsList()
{
    RegisterPhysics(new G4EmStandardPhysics());
    RegisterPhysics(new G4DecayPhysics());
    RegisterPhysics(new G4HadronPhysicsFTFP_BERT());  // Para interacción hadrónica y decaimiento de piones
}


MyPhysicsList::~MyPhysicsList()
{}
