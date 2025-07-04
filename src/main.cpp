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
    const double lr = 0.8;

    const double eps_start = 0.9;
    const double eps_end = 0.01;
    const double eps_decay = 2500;

    const int n_states  = 100 * 100;
    const int n_actions = 4;

    const int epochs = 1e6;

    Agent agent(gamma, lr, eps_start, eps_end, eps_decay, n_states, n_actions);
    double success_rate = agent.train(epochs);


    InitWindow(L, L, "Q-Learning");
    SetTargetFPS(30);

    Agent_body agent_body(r, r);
    Goal goal(r, r);

    while (!WindowShouldClose()) {
        int ax = (int)agent_body.pos.x / D;
        int ay = (int)agent_body.pos.y / D;

        int gx = (int)goal.pos.x / D;
        int gy = (int)goal.pos.y / D;

        int state = get_state(ax, ay, gx, gy);

        int row, a;
        double max_val = agent.q_table.row(state).maxCoeff(&row, &a);

        Actions_set m = agent_body.translate(a);
        agent_body.move(m);


        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangle(goal.pos.x, goal.pos.y, D, D, GREEN);
        DrawRectangle(agent_body.pos.x, agent_body.pos.y, D, D, RED);

        draw_grid();
        DrawText(TextFormat("%0.1f", success_rate), 10, 10, 40, WHITE);

        EndDrawing();

        if (agent_body.pos.x == goal.pos.x && agent_body.pos.y == goal.pos.y) {
            agent_body.pos.x = r * D;
            agent_body.pos.y = r * D;

            goal.pos.x = r * D;
            goal.pos.y = r * D;

            WaitTime(0.5);
        }

        WaitTime(0.3);
    }    

    return 0;
}
