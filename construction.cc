#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Box.hh"
#include "G4PVPlacement.hh"
#include "G4NistManager.hh"
#include "G4SystemOfUnits.hh"
#include "G4PhysicalConstants.hh"
#include "G4VisAttributes.hh"
#include "G4Colour.hh"

#include "construction.hh"

MyDetectorConstruction::MyDetectorConstruction()
{}

MyDetectorConstruction::~MyDetectorConstruction()
{}

G4VPhysicalVolume* MyDetectorConstruction::Construct()
{
    // Materiales
    G4NistManager* nist = G4NistManager::Instance();
    G4Material* worldMat = nist->FindOrBuildMaterial("G4_Galactic");
    G4Material* ironMat = nist->FindOrBuildMaterial("G4_Fe");

    // Atributos visuales
    G4VisAttributes* ironVis = new G4VisAttributes(G4Colour(0.7, 0.7, 0.7)); // Gris para el hierro
    ironVis->SetVisibility(true);
    ironVis->SetForceSolid(true);
    
    G4VisAttributes* detVis = new G4VisAttributes(G4Colour(0., 0., 1.)); // Azul para detectores
    detVis->SetVisibility(true);
    detVis->SetForceSolid(true);

    // Mundo (30x30x30 m)
    G4Box* solidWorld = new G4Box("World", 15*m, 15*m, 15*m);
    G4LogicalVolume* logicWorld = new G4LogicalVolume(solidWorld, worldMat, "World");
    G4VPhysicalVolume* physWorld = new G4PVPlacement(0, G4ThreeVector(), logicWorld, 
                                                   "World", 0, false, 0, true);

    // Parámetros geométricos
    const G4double ironThickness = 0.3*m;       // Grosor capa de hierro
    const G4double detThickness = 0.2*m;     // Grosor detector (1 cm)
    const G4double layerSpacing = 0.001*m;      // Espacio entre conjuntos capa+detector

    // Primera capa de hierro (10x10x1 m)
    G4Box* solidIronLayer1 = new G4Box("IronLayer1", 5*m, 5*m, ironThickness/2);
    G4LogicalVolume* logicIron1 = new G4LogicalVolume(solidIronLayer1, ironMat, "IronLayer1");
    logicIron1->SetVisAttributes(ironVis);
    
    // Posición primera capa
    G4double iron1PosZ = 6*m;
    new G4PVPlacement(0, G4ThreeVector(0, 0, iron1PosZ), logicIron1, "IronLayer1", logicWorld, false, 0, true);

    // Primer plano de detectores - colocado justo después de la primera capa
    G4double det1PosZ = iron1PosZ + ironThickness/2 + detThickness/2;
    
    // Segunda capa de hierro
    G4Box* solidIronLayer2 = new G4Box("IronLayer2", 5*m, 5*m, ironThickness/2);
    G4LogicalVolume* logicIron2 = new G4LogicalVolume(solidIronLayer2, ironMat, "IronLayer2");
    logicIron2->SetVisAttributes(ironVis);
    
    // Posición segunda capa
    G4double iron2PosZ = det1PosZ + detThickness/2 + layerSpacing + ironThickness/2;
    new G4PVPlacement(0, G4ThreeVector(0, 0, iron2PosZ), logicIron2, "IronLayer2", logicWorld, false, 0, true);

    // Segundo plano de detectores - colocado justo después de la segunda capa
    G4double det2PosZ = iron2PosZ + ironThickness/2 + detThickness/2;

    // Tercera capa de hierro
    G4Box* solidIronLayer3 = new G4Box("IronLayer3", 5*m, 5*m, ironThickness/2);
    G4LogicalVolume* logicIron3 = new G4LogicalVolume(solidIronLayer3, ironMat, "IronLayer3");
    logicIron3->SetVisAttributes(ironVis);

    // Posición tercera capa
    G4double iron3PosZ = det2PosZ + detThickness/2 + layerSpacing + ironThickness/2;
    new G4PVPlacement(0, G4ThreeVector(0, 0, iron3PosZ), logicIron2, "IronLayer2", logicWorld, false, 0, true);

    // Tercer plano de detectores - colocado justo después de la terceraa capa
    G4double det3PosZ = iron3PosZ + ironThickness/2 + detThickness/2;

    // Cuartaa capa de hierro
    G4Box* solidIronLayer4 = new G4Box("IronLayer4", 5*m, 5*m, ironThickness/2);
    G4LogicalVolume* logicIron4 = new G4LogicalVolume(solidIronLayer4, ironMat, "IronLayer3");
    logicIron4->SetVisAttributes(ironVis);

    // Posición cuarta capa
    G4double iron4PosZ = det3PosZ + detThickness/2 + layerSpacing + ironThickness/2;
    new G4PVPlacement(0, G4ThreeVector(0, 0, iron4PosZ), logicIron3, "IronLayer2", logicWorld, false, 0, true);

    // Tercer plano de detectores - colocado justo después de la terceraa capa
    G4double det4PosZ = iron4PosZ + ironThickness/2 + detThickness/2;

    // Detectores (1x1x0.01 m cada uno)
    G4Box* solidDetector = new G4Box("Detector", 0.5*m, 0.5*m, detThickness/2);
    G4LogicalVolume* logicDetector = new G4LogicalVolume(solidDetector, worldMat, "Detector");
    logicDetector->SetVisAttributes(detVis);

    // Crear grid de detectores (10x10 detectores cubriendo 10x10 m)
    for(G4int i = 0; i < 10; i++) {
        for(G4int j = 0; j < 10; j++) {
            G4double xPos = -4.5*m + i*m; // Centrado en X (-4.5 a +4.5 m)
            G4double yPos = -4.5*m + j*m; // Centrado en Y (-4.5 a +4.5 m)
            
            // Primer plano de detectores
            new G4PVPlacement(0, G4ThreeVector(xPos, yPos, det1PosZ), 
                            logicDetector, "Detector1", logicWorld, false, i+j*10, true);
            
            // Segundo plano de detectores
            new G4PVPlacement(0, G4ThreeVector(xPos, yPos, det2PosZ), 
                            logicDetector, "Detector2", logicWorld, false, i+j*10+100, true);
            
            // Tercer plano de detectores
            new G4PVPlacement(0, G4ThreeVector(xPos, yPos, det3PosZ), 
                            logicDetector, "Detector3", logicWorld, false, i+j*10+100, true);

            // Cuarto plano de detectores
            new G4PVPlacement(0, G4ThreeVector(xPos, yPos, det4PosZ), 
                            logicDetector, "Detector4", logicWorld, false, i+j*10+100, true);
        }   
    }

    return physWorld;
}
