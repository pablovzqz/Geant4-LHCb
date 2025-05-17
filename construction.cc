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

    //Creamos la mezcla de gases de las estaciones de muones
    //Creamos los compuestos gaseosos
    //Dioxido de carbono
    G4Material *CO2 = new G4Material("CO2", 1.98*g/cm3, 2);
	CO2->AddElement(nist->FindOrBuildElement("C"), 1);
	CO2->AddElement(nist->FindOrBuildElement("O"), 2);

    //Tetrafluoruro de metano
    G4Material *CF4 = new G4Material("CF4", 3.72*g/cm3, 2);
	CF4->AddElement(nist->FindOrBuildElement("C"), 1);
	CF4->AddElement(nist->FindOrBuildElement("F"), 4);

    //Argon
    G4Element *Ar = nist->FindOrBuildElement("Ar");

    //Creamos la mezcla gaseosa del detector
    G4Material *ms_mixture = new G4Material("Muon station mixture", 1.99 * g/cm3, 3);
	ms_mixture->AddElement(Ar, 40*perCent);
	ms_mixture->AddMaterial(CO2, 55*perCent);
	ms_mixture->AddMaterial(CF4, 5*perCent);


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
    const G4double detThickness = 0.2*m;     // Grosor detector (20 cm)
    const G4double layerSpacing = 0.001*m;      // Espacio entre conjuntos capa+detector

    // Primera capa de hierro (10x10x0.3 m)
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
    new G4PVPlacement(0, G4ThreeVector(0, 0, iron3PosZ), logicIron3, "IronLayer3", logicWorld, false, 0, true);

    // Tercer plano de detectores - colocado justo después de la tercera capa
    G4double det3PosZ = iron3PosZ + ironThickness/2 + detThickness/2;

    // Cuarta capa de hierro
    G4Box* solidIronLayer4 = new G4Box("IronLayer4", 5*m, 5*m, ironThickness/2);
    G4LogicalVolume* logicIron4 = new G4LogicalVolume(solidIronLayer4, ironMat, "IronLayer4");
    logicIron4->SetVisAttributes(ironVis);

    // Posición cuarta capa
    G4double iron4PosZ = det3PosZ + detThickness/2 + layerSpacing + ironThickness/2;
    new G4PVPlacement(0, G4ThreeVector(0, 0, iron4PosZ), logicIron4, "IronLayer4", logicWorld, false, 0, true);

    // Cuarto plano de detectores - colocado justo después de la cuarta capa
    G4double det4PosZ = iron4PosZ + ironThickness/2 + detThickness/2;

    // Detectores (1x1x0.01 m cada uno)
    G4Box* solidDetector = new G4Box("Detector", 0.5*m, 0.5*m, detThickness/2);

    logicDetector1 = new G4LogicalVolume(solidDetector, ms_mixture, "Detector1");
    logicDetector1->SetVisAttributes(detVis);

    logicDetector2 = new G4LogicalVolume(solidDetector, ms_mixture, "Detector2");
    logicDetector2->SetVisAttributes(detVis);

    logicDetector3 = new G4LogicalVolume(solidDetector, ms_mixture, "Detector3");
    logicDetector3->SetVisAttributes(detVis);

    logicDetector4 = new G4LogicalVolume(solidDetector, ms_mixture, "Detector4");
    logicDetector4->SetVisAttributes(detVis);

    // Crear grid de detectores (10x10 detectores cubriendo 10x10 m)
    for(G4int i = 0; i < 10; i++) {
        for(G4int j = 0; j < 10; j++) {
            G4double xPos = -4.5*m + i*m; // Centrado en X (-4.5 a +4.5 m)
            G4double yPos = -4.5*m + j*m; // Centrado en Y (-4.5 a +4.5 m)
            
            // Primer plano de detectores
            new G4PVPlacement(0, G4ThreeVector(xPos, yPos, det1PosZ), 
                            logicDetector1, "Detector1", logicWorld, false, i+j*10, true);
            
            // Segundo plano de detectores
            new G4PVPlacement(0, G4ThreeVector(xPos, yPos, det2PosZ), 
                            logicDetector2, "Detector2", logicWorld, false, i+j*10+100, true);
            
            // Tercer plano de detectores
            new G4PVPlacement(0, G4ThreeVector(xPos, yPos, det3PosZ), 
                            logicDetector3, "Detector3", logicWorld, false, i+j*10+200, true);

            // Cuarto plano de detectores
            new G4PVPlacement(0, G4ThreeVector(xPos, yPos, det4PosZ), 
                            logicDetector4, "Detector4", logicWorld, false, i+j*10+300, true);
        }   
    }

    return physWorld;
}


void MyDetectorConstruction::ConstructSDandField()
{
	MySensitiveDetector *sensDet1 = new MySensitiveDetector("SensitiveDetector1");
    logicDetector1->SetSensitiveDetector(sensDet1);

    MySensitiveDetector *sensDet2 = new MySensitiveDetector("SensitiveDetector2");
    logicDetector2->SetSensitiveDetector(sensDet2);

    MySensitiveDetector *sensDet3 = new MySensitiveDetector("SensitiveDetector3");
    logicDetector3->SetSensitiveDetector(sensDet3);

    MySensitiveDetector *sensDet4 = new MySensitiveDetector("SensitiveDetector4");
    logicDetector4->SetSensitiveDetector(sensDet4);
}
