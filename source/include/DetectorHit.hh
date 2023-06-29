#pragma once

#include <G4Allocator.hh>
#include <G4THitsCollection.hh>
#include <G4VHit.hh>



class DetectorHit : public G4VHit {
public:
    DetectorHit(G4int tube_id);
    DetectorHit(const DetectorHit& hit) = default;
    ~DetectorHit();

    DetectorHit& operator=(const DetectorHit& hit) = default;
    G4bool operator==(const DetectorHit& hit) const;

    inline void* operator new(size_t count);
    inline void operator delete(void* hit);

    void Draw();
    void Print();

    inline G4int GetTubeID() const { return tube_id; }

private:
    G4int tube_id;
};



typedef G4THitsCollection<DetectorHit> DetectorHitsCollection;
extern G4ThreadLocal G4Allocator<DetectorHit>* DetectorHitAllocator;



inline void* DetectorHit::operator new(size_t count) {
    (void) count;
    
    if(!DetectorHitAllocator)
        DetectorHitAllocator = new G4Allocator<DetectorHit>;
    return (void*) DetectorHitAllocator->MallocSingle();
}

inline void DetectorHit::operator delete(void* hit) {
    DetectorHitAllocator->FreeSingle((DetectorHit*) hit);
}