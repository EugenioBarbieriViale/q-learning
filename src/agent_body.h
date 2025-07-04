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

        Actions_set translate(int);
        void move(Actions_set);
        void draw();
};

Agent_body::Agent_body(int x, int y) {
    pos.x = x * D;
    pos.y = y * D;
}

Actions_set Agent_body::translate(int action) {
    switch (action) {
        case 0:
            return UP;
        case 1:
            return DOWN;
        case 2:
            return RIGHT;
        case 3: 
            return LEFT;
        default:
            return UP;
    }
}

void Agent_body::move(Actions_set action) {
    switch (action) {
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
