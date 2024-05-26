#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <Windows.h>

const int STATES = 6;
const int ACTIONS = 6;

int R[STATES][ACTIONS] = {
    {-1, -1, 0, -1, -1, -1},
    {-1, -1, 0, -1, -1, -1},
    {0, 0, -1, 0, -1, 100},
    {-1, -1, 0, -1, 0, -1},
    {-1, -1, -1, 0, -1, -1},
    {-1, -1, 0, -1, -1, 100}
};

int Q[STATES][ACTIONS] = {
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0},
    {0, 0, 0, 0, 0, 0}
};

double gamma = 0.8;

int getRandomState() {
    return rand() % STATES;
}

std::vector<int> getAvailableActions(int currentState) {
    std::vector<int> actions;
    for (int i = 0; i < ACTIONS; i++) {
        if (R[currentState][i] >= 0) {
            actions.push_back(i);
        }
    }
    return actions;
}

int getBestAction(int currentState) {
    std::vector<int> actions = getAvailableActions(currentState);
    int bestAction = actions[0];
    for (int action : actions) {
        if (Q[currentState][action] > Q[currentState][bestAction]) {
            bestAction = action;
        }
    }
    std::vector<int> bestActions;
    for (int action : actions) {
        if (Q[currentState][action] == Q[currentState][bestAction]) {
            bestActions.push_back(action);
        }
    }
    return bestActions[rand() % bestActions.size()];
}

int getMaxQ(int nextState) {
    return *std::max_element(Q[nextState], Q[nextState] + ACTIONS);
}

void updateQ(int currentState, int action) {
    int maxQValue = getMaxQ(action);
    Q[currentState][action] = R[currentState][action] + gamma * maxQValue;
}

int main() {
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);
    srand(time(0));
    int numberOfTries;
    std::cout << "Введіть кількість спроб: ";
    std::cin >> numberOfTries;

    for (int i = 0; i < numberOfTries; i++) {
        int currentState = getRandomState();
        std::cout << i + 1 << " спроба - ";

        while (currentState != 5) {
            std::cout << currentState << " стан, ";
            int action = getBestAction(currentState);
            updateQ(currentState, action);
            currentState = action;
        }

        std::cout << currentState << " стан\n";
        std::cout << std::endl;
    }
}

//#include <iostream>
//#include <vector>
//#include <algorithm>
//#include <ctime>
//#include <Windows.h>
//using namespace std;
//
//const int STATES = 6;
//const int ACTIONS = 6;
//
//double R[STATES][ACTIONS] = {
//    {-1, -1, 0, -1, -1, -1},
//    {-1, -1, 0, -1, -1, -1},
//    {0, 0, -1, 0, -1, 100},
//    {-1, -1, 0, -1, 0, -1},
//    {-1, -1, -1, 0, -1, -1},
//    {-1, -1, 0, -1, -1, 100}
//};
//
//double Q[STATES][ACTIONS] = {
//    {0, 0, 0, 0, 0, 0},
//    {0, 0, 0, 0, 0, 0},
//    {0, 0, 0, 0, 0, 0},
//    {0, 0, 0, 0, 0, 0},
//    {0, 0, 0, 0, 0, 0},
//    {0, 0, 0, 0, 0, 0}
//};
//
//double gamma = 0.8;
//
//bool all_equal(vector<double> values_Q)
//{
//    bool allEqual = true;
//    for (const int& value : values_Q) {
//        if (value != values_Q.front()) {
//            allEqual = false;
//            break;
//        }
//    }
//
//    return allEqual;
//}
//
//double maxElementVector(vector<double> values_Q)
//{
//    int maxElement = values_Q.front();
//
//    for (const int& value : values_Q) {
//        if (value > maxElement) {
//            maxElement = value;
//        }
//    }
//
//    return maxElement;
//}
//
//int getRandomState() {
//    return rand() % STATES;
//}
//
//std::vector<int> getAvailableActions(int currentState) {
//    std::vector<int> actions;
//    for (int i = 0; i < ACTIONS; i++) {
//        if (R[currentState][i] >= 0) {
//            actions.push_back(i);
//        }
//    }
//    return actions;
//}
//
//int getBestAction(int currentState) {
//    /*std::vector<int> actions = getAvailableActions(currentState);
//    int bestAction = actions[0];
//    for (int action : actions) {
//        if (Q[currentState][action] > Q[currentState][bestAction]) {
//            bestAction = action;
//        }
//    }
//    std::vector<int> bestActions;
//    for (int action : actions) {
//        if (Q[currentState][action] == Q[currentState][bestAction]) {
//            bestActions.push_back(action);
//        }
//    }
//    return bestActions[rand() % bestActions.size()];*/
//
//    vector<int> actions = getAvailableActions(currentState);
//    vector<pair<double, double>> values_Q;
//
//    for (int i = 0; i < actions.size(); i++)
//    {
//        values_Q.push_back(make_pair(Q[currentState][actions[i]], actions[i]));
//    }
//
//    vector<double> only_values_Q;
//
//    for (int i = 0; i < values_Q.size(); i++)
//    {
//        only_values_Q.push_back(values_Q[i].first);
//    }
//
//    if (all_equal(only_values_Q))
//    {
//        return actions[rand() % actions.size()];
//    }
//
//    else
//    {
//        double max = maxElementVector(only_values_Q);
//        int action = -777;
//
//        for (int i = 0; i < values_Q.size(); i++)
//        {
//            if (max == values_Q[i].first)
//            {
//                action = values_Q[i].second;
//            }
//        }
//
//        return action;
//    }
//}
//
//double getMaxQ(vector<int> states) {
//    vector<int> availableActions = getAvailableActions(states[states.size() - 1]);
//    int max = -777;
//    int index = states[states.size() - 2];
//    for (int i = 0; i < availableActions.size(); i++)
//    {
//        if (max < Q[index][availableActions[i]])
//        {
//            max = Q[index][availableActions[i]];
//        }
//    }
//
//    return max;
//}
//
//void updateQ(vector<int> states) {
//    int prev_prev_room = states[states.size() - 3];
//    int prev_room = states[states.size() - 2];
//    double max = getMaxQ(states);
//
//    Q[prev_prev_room][prev_room] = R[prev_prev_room][prev_room] + 0.8 * max;
//}
//
//int main() {
//    SetConsoleCP(1251);
//    SetConsoleOutputCP(1251);
//    srand(time(0));
//    int numberOfTries;
//    vector<int> states;
//    int prev_Q = Q[5][5];
//    std::cout << "Введіть кількість спроб: ";
//    std::cin >> numberOfTries;
//
//    for (int i = 0; i < numberOfTries; i++) {
//        int currentState = 3;
//        states.push_back(currentState);
//
//        currentState = getBestAction(currentState);
//        states.push_back(currentState);
//
//        while (Q[5][5] == prev_Q) {
//            currentState = getBestAction(currentState);
//            states.push_back(currentState);
//            updateQ(states);
//
//            if (currentState == 5)
//            {
//                states.push_back(currentState);
//                updateQ(states);
//            }
//        }
//
//        cout << i + 1 << " спроба: ";
//        for (int i = 0; i < states.size(); i++)
//        {
//            cout << states[i] << " стан, ";
//        }
//
//        cout << endl;
//
//        cout << "Матриця Q (пам'ять агента):" << endl;
//        for (int j = 0; j < STATES; j++) {
//            for (int k = 0; k < ACTIONS; k++) {
//                cout << Q[j][k] << " ";
//            }
//            cout << endl;
//        }
//        cout << endl;
//
//        states.clear();
//        prev_Q = Q[5][5];
//    }
//
//    /*std::cout << "Матриця Q (пам'ять агента):\n";
//    for (int j = 0; j < STATES; j++) {
//        for (int k = 0; k < ACTIONS; k++) {
//            std::cout << Q[j][k] << " ";
//        }
//        std::cout << std::endl;
//    }
//    std::cout << std::endl;*/
//}