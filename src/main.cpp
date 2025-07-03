#include <iostream>
#include <vector>
#include <raylib.h>
#include <Eigen/Core>

#include "q.h"

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
    const double eps = 0.6;
    const double lr = 0.8;

    const int n_states  = 100;
    const int n_actions = 4;

    const int epochs = 1000;

    Agent agent(gamma, eps, lr, n_states, n_actions);
    agent.train(epochs);


    InitWindow(L, L, "Q-Learning");
    SetTargetFPS(30);

    Agent_body agent_body(r, r);
    Goal goal(5, 5);

    while (!WindowShouldClose()) {
        double state = get_state((int)agent_body.pos.x / D, (int)agent_body.pos.y / D);

        int row, a;
        double max_val = agent.q_table.row(state).maxCoeff(&row, &a);

        Actions_set m = agent_body.translate(a);
        agent_body.move(m);

        if (agent_body.pos.x == goal.pos.x && agent_body.pos.y == goal.pos.y) {
            agent_body.pos.x = r * D;
            agent_body.pos.y = r * D;
        }


        BeginDrawing();
        ClearBackground(BLACK);

        DrawRectangle(agent_body.pos.x, agent_body.pos.y, D, D, RED);
        DrawRectangle(goal.pos.x, goal.pos.y, D, D, GREEN);

        draw_grid();

        EndDrawing();

        WaitTime(0.5);
    }    

    return 0;
}
