#define r (std::rand() % 10)
#define R ((double) std::rand() / (RAND_MAX))


int get_state(int ax, int ay, int gx, int gy) {
    return (int) ((ay * 10 + ax) + 100 * (gy * 10 + gx));
}


class Agent {
    private:
        double gamma, lr;
        double eps_start, eps_end, eps_decay;
        int n_states, n_actions;

    public:
        Eigen::MatrixXd q_table;

        Agent(double, double, double, double, double, int, int);

        int get_next_state(int, int&, int&, int, int);
        int select_action(int, double);

        void learn(int, int, int, double, bool);
        double train(int);
};

Agent::Agent(double gamma, double lr, double eps_start, double eps_end, double eps_decay, int n_states, int n_actions) {
    this->gamma = gamma;
    this->lr = lr;

    this->eps_start = eps_start;
    this->eps_end = eps_end;
    this->eps_decay = eps_decay;

    this->n_states = n_states;
    this->n_actions = n_actions;
    
    q_table = Eigen::MatrixXd::Random(n_states, n_actions);
}

int Agent::get_next_state(int action, int &ax, int &ay, int gx, int gy) {
    switch (action) {
        case 0: if (ay > 0) ay--; break;   // UP
        case 1: if (ay < 9) ay++; break;   // DOWN
        case 2: if (ax < 9) ax++; break;   // RIGHT
        case 3: if (ax > 0) ax--; break;   // LEFT
    }
    
    return get_state(ax, ay, gx, gy);
}

int Agent::select_action(int state, double time_step) {
    double sample = R;
    double eps_threshold = eps_end + (eps_start - eps_end) * exp(-1.f * time_step / eps_decay);

    if (sample < eps_threshold) {
        int row, idx;
        double max_val = q_table.row(state).maxCoeff(&row, &idx);
        return idx;
    }
    
    else {
        return std::rand() % 4;
    }
}

void Agent::learn(int state, int action, int next_state, double reward, bool done) {
    double max_val = done ? 0 : q_table.row(next_state).maxCoeff();
    q_table(state, action) = (1 - lr ) * q_table(state, action) + lr * (reward + gamma * max_val);
}

double Agent::train(int epochs) {
    int interval = 500;

    int success = 0;
    double success_rate;

    int total_steps = 0;

    for (int i=0; i<epochs; i++) {
        int ax = r;
        int ay = r;

        int gx = r;
        int gy = r;

        int state = get_state(ax, ay, gx, gy);

        int time_step = 0;
        bool done = false;

        while (!done && time_step < 20) {
            int action = select_action(state, (double)time_step);
            int next_state = get_next_state(action, ax, ay, gx, gy);

            bool terminal_state = (ax == gx && ay == gy);

            double reward = 0;

            if (terminal_state) {
                done = true;
                reward = 1.f;

                success++;

                learn(state, action, next_state, reward, done);
                break;
            }

            else if (next_state == state) {
                reward = -1.f;
            }

            else {
                double dist = sqrt(pow((ax - gx), 2) + pow((ay - gy), 2)) / (10.f * sqrt(2));
                reward = -0.05 * dist;
            }

            learn(state, action, next_state, reward, done);

            state = next_state;
            time_step++;
        }

        success_rate = (double)success / (double)i * 100.f;
        total_steps += time_step;

        if (i % interval == 0) {
            std::cout << "Epoch: " << i << ": Success rate = " << success_rate << "% (" << success << "/" << i << ")";
            std::cout << " -> Avg steps: " << (int)((double)total_steps / (double)interval) << "\n";

            total_steps = 0;
        }
    }

    return ((double)success / (double)epochs * 100.f);
}
