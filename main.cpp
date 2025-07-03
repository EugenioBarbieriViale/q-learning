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

double get_state(int x, int y) {
    return (double) (x * 10.f + y);
}


int main() {
    std::srand(time(0));

    // InitWindow(L, L, "RL");
    // SetTargetFPS(30);

    // std::vector<Actions_set> moves = {DOWN, RIGHT, UP, LEFT};

    // Agent_body agent_body(3, 3);
    // Goal goal(9, 9);

    // int time = 0; 

    // while (!WindowShouldClose()) {
    //     agent_body.move(moves, time);

    //     BeginDrawing();
    //     ClearBackground(BLACK);


    //     DrawRectangle(agent_body.pos.x, agent_body.pos.y, D, D, RED);
    //     DrawRectangle(goal.pos.x, goal.pos.y, D, D, GREEN);

    //     draw_grid();

    //     EndDrawing();

    //     WaitTime(0.5);
    //     time++;
    // }
    
    Agent_body agent_body(3, 3);
    Goal goal(9, 9);

    const double gamma = 0.99;
    const double eps = 0.2;
    const double lr = 3e-4;

    const int n_states  = 100;
    const int n_actions = 4;

    const int epochs = 10;

    Agent agent(gamma, eps, lr, n_states, n_actions);

    for (int i=0; i<epochs; i++) {
        int x = agent_body.pos.x / D;
        int y = agent_body.pos.y / D;

        double state = get_state(x, y);
        double goal_state = get_state(goal.pos.x / D, goal.pos.y / D);

        int steps = 0;
        while (state != goal_state && steps < 25) {
            double action = agent.select_action(state);
            double next_state = agent.get_next_state(state, action);

            double reward = 0.f;
            if (next_state == goal_state) {
                reward = 1.f;
            }

            // std::cout << state << ", " << next_state << "\n";
            if (next_state <= 0.f) {
                reward = -1.f;
                next_state = 1.f;
            }

            else if (next_state >= 100.f) {
                reward = -1.f;
                next_state = 99.f;
            }
            
            agent.learn(state, action, next_state, reward);

            state = next_state;
            steps++;
        }
    }

    std::cout << agent.q_table << "\n";

    return 0;
}
