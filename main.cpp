#include <iostream>
#include <vector>
#include <raylib.h>
#include <Eigen/Dense>
 
using Eigen::MatrixXd;

#define L 600
#define N 10
#define D (L/N)

enum Direction {
    UP,
    DOWN,
    RIGHT,
    LEFT,
};

class Agent {
    public:
        Vector2 pos;
        Agent(int, int);

        void move(std::vector<Direction>, int);
        void draw();

    private:
        void step(Direction);
};

Agent::Agent(int x, int y) {
    pos.x = x;
    pos.y = y;
}

void Agent::step(Direction d) {
    switch (d) {
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

void Agent::move(std::vector<Direction> moves, int time) {
    step(moves[time % moves.size()]);
}

void Agent::draw() {
    DrawRectangle(pos.x, pos.y, D, D, RED);
}

class Goal {
    public:
        Vector2 pos;
        Goal(int, int);

        void draw();
};

Goal::Goal(int x, int y) {
    pos.x = x;
    pos.y = y;
}

void Goal::draw() {
    DrawRectangle(pos.x, pos.y, D, D, GREEN);
}

void draw_grid() {
    for (int i=0; i<N; i++) {
        DrawLine(i * D, 0, i * D, L, WHITE);
        DrawLine(0, i * D, L, i * D, WHITE);
    }
}


int main() {
    InitWindow(L, L, "RL");
    SetTargetFPS(30);

    std::vector<Direction> moves = {DOWN, RIGHT, UP, LEFT};

    Agent a(0, 0);
    Goal g(L-D, L-D);

    int time = 0; 

    while (!WindowShouldClose()) {
        a.move(moves, time);

        BeginDrawing();
        ClearBackground(BLACK);

        a.draw();
        g.draw();

        draw_grid();

        EndDrawing();

        WaitTime(0.5);
        time++;
    }

    return 0;
}
