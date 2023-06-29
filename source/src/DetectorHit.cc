#include "DetectorHit.hh"



G4ThreadLocal G4Allocator<DetectorHit>* DetectorHitAllocator = nullptr;



DetectorHit::DetectorHit(G4int tube_id) : G4VHit(), tube_id(tube_id) {

}

DetectorHit::~DetectorHit() {

}



G4bool DetectorHit::operator==(const DetectorHit& hit) const {
    return tube_id == hit.tube_id;
}



void DetectorHit::Draw() {

}

void DetectorHit::Print() {

}