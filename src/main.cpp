#include <iostream>
#include <vector>
#include <raylib.h>
#include <Eigen/Core>

#include "q_learning.h"

#include "agent_body.h"
#include "goal.h"


void draw_grid() {
    for (int i=0; i<N; i++) {
        DrawLine(i * D, 0, i * D, L, WHITE);
        DrawLine(0, i * D, L, i * D, WHITE);
    }
}


int main() {
    std::srand(time(0));

    const double gamma = 0.95;
    const double eps = 0.2;
    const double lr = 0.8;

    const int n_states  = 100;
    const int n_actions = 4;

    const int epochs = 10000;

    const int gx = 8;
    const int gy = 7;

    Agent agent(gamma, eps, lr, n_states, n_actions);
    agent.train(epochs, gx, gy);


    InitWindow(L, L, "Q-Learning");
    SetTargetFPS(30);

    Agent_body agent_body(r, r);
    Goal goal(gx, gy);

    while (!WindowShouldClose()) {
        int state = get_state((int)agent_body.pos.x / D, (int)agent_body.pos.y / D);

        int row, a;
        double max_val = agent.q_table.row(state).maxCoeff(&row, &a);

        Actions_set m = agent_body.translate(a);
        agent_body.move(m);


        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangle(goal.pos.x, goal.pos.y, D, D, GREEN);
        DrawRectangle(agent_body.pos.x, agent_body.pos.y, D, D, RED);

        draw_grid();

        EndDrawing();

        if (agent_body.pos.x == goal.pos.x && agent_body.pos.y == goal.pos.y) {
            agent_body.pos.x = r * D;
            agent_body.pos.y = r * D;

            WaitTime(0.5);
        }

        WaitTime(0.3);
    }    

    return 0;
}
