#define r (std::rand() % 10)
#define R ((double) std::rand() / (RAND_MAX))


double get_state(int x, int y) {
    return (double) (x * 10.f + y);
}


class Agent {
    private:
        double gamma, eps, lr;
        int n_states, n_actions;

    public:
        Eigen::MatrixXd q_table;

        Agent(double, double, double, int, int);

        double get_next_state(double, double);
        double select_action(double);

        void learn(double, double, double, double);
        void train(int);
};

Agent::Agent(double gamma, double eps, double lr, int n_states, int n_actions) {
    this->gamma = gamma;
    this->eps = eps;
    this->lr = lr;

    this->n_states = n_states;
    this->n_actions = n_actions;
    
    q_table = Eigen::MatrixXd::Zero(n_states, n_actions);
}

double Agent::get_next_state(double state, double action) {
    double next_state = state;

    switch ((int)action) {
        case 0: // UP
            next_state -= 10;
            break;
        case 1: // DOWN
            next_state += 10;
            break;
        case 2: // RIGHT
            next_state += 1;
            break;
        case 3: // LEFT
            next_state -= 1;
            break;
    }
    
    return next_state;
}

double Agent::select_action(double state) {
    double sample = R;

    if (sample < eps) {
        int row, idx;
        double max_val = q_table.row(state).maxCoeff(&row, &idx);
        return (double)idx;
    }
    
    else {
        return (double)(std::rand() % 4);
    }
}

void Agent::learn(double state, double action, double next_state, double reward) {
    double max_val = q_table.row(next_state).maxCoeff();
    q_table((int)state, (int)action) += lr * (reward + gamma * max_val - q_table((int)state, (int)action));
}

void Agent::train(int epochs) {
    for (int i=0; i<epochs; i++) {
        int ax = r;
        int ay = r;

        int gx = 5;
        int gy = 5;

        double state = get_state(ax, ay);
        double goal_state = get_state(gx, gy);

        int steps = 0;
        while (state != goal_state && steps < 10) {
            double action = select_action(state);
            double next_state = get_next_state(state, action);

            double reward = 0.f;
            if (next_state == goal_state) {
                std::cout << i << ": YESS------------------------\n";
                reward = 1.f;
            }

            if (next_state <= 0.f) {
                reward = -1.f;
                next_state = 1.f;
            }

            else if (next_state >= 100.f) {
                reward = -1.f;
                next_state = 99.f;
            }
            
            learn(state, action, next_state, reward);

            state = next_state;
            steps++;
        }
    }

    std::cout << q_table << "\n";
}
