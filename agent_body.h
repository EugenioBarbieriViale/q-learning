#define L  600
#define N   10
#define D (L/N)

enum Actions_set {
    UP,
    DOWN,
    RIGHT,
    LEFT,
};

class Agent_body {
    public:
        Vector2 pos;
        Agent_body(int, int);

        void move(std::vector<Actions_set>, int);
        void draw();

    private:
        void step(Actions_set);
};

Agent_body::Agent_body(int x, int y) {
    pos.x = x * D;
    pos.y = y * D;
}

void Agent_body::step(Actions_set a) {
    switch (a) {
        case UP:
            pos.y -= D;
            break;
        case DOWN:
            pos.y += D;
            break;
        case RIGHT:
            pos.x += D;
            break;
        case LEFT:
            pos.x -= D;
            break;
    }
}

void Agent_body::move(std::vector<Actions_set> actions, int time) {
    step(actions[time % actions.size()]);
}
