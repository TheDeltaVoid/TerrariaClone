#include "entities.h"

#include <string>

class Player : public PhysicsEntity{
    private:
    public:
    Player();

    void update() override;
    void debugRender() override;
};
