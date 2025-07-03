#define R ((double) std::rand() / (RAND_MAX))

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
        return (double) idx;
    }
    
    else {
        return std::rand() % 4;
    }
}

void Agent::learn(double state, double action, double next_state, double reward) {
    double max_val = q_table.row(next_state).maxCoeff();
    q_table(state, action) += lr * (reward + gamma * max_val - q_table(state, action));
}
