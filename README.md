# Q-Learning from scratch in C++ 
The agent (red square) moves in a 10x10 grid and has learned to reach the goal (green square). Both the agent and the goal have random initial position.

The reinforcment learning algorithm is Q-Learning, in which the quality function given the state and the action is represented by a matrix. The so called Q-table is matrix 10.000x4: all possible positions of the agent (100) times all possible positions of the goal (100), and for each state the possible actions (up, down, right, left, so 4). This function, given the state, returns as ouput the probability of the best action, which is the action expected to receive the maximum reward.

## Screenshot
![q_learning_rnd](https://github.com/user-attachments/assets/e81dfa66-745a-4229-bcd3-81b7aae5a16b)

## Dependencies
- ![eigen](https://eigen.tuxfamily.org/index.php?title=Main_Page) 
- ![raylib](https://www.raylib.com/)
