#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>
#include <set>
#include <stack>
#include <queue>
#include <iterator>
#include <string>

using namespace std;

template<int SIZE> struct Node {
    using State = array<int, SIZE>;

    State st;         // the state of slide puzzle
    Node* parent;     // parent in the search tree
    int level;        // level of the search tree

    // constructors
    Node(State input): st(input), level(1), parent(nullptr){};
    Node(State input, Node* p): st(input), level(p->level+1), parent(p){};

};

template <int SIZE> class SlideGame
{
    using State = array<int, SIZE>;
private:
    State st;          // initial state
    Node<SIZE>* sol;   // the solution
    int LEN;            // LEN = sqrt(SIZE)

public:
    // constructor
    SlideGame(State input): st(input), sol(nullptr){
        LEN = 3;
    };

    // move a block from the "from" position to the "to" position
    State MoveBlock(State s, int from, int to)
    {
        State t = s;
        // swap from and to
        int temp = t[from];
        t[from] = t[to];
        t[to] = temp;

        return t;
    }

    // Search the possible states from the current state s.
    set<State> extend(State s)
    {
        set<State> SS;
        int pos, x, y;

        // find where 0 is
        for (pos=0;pos<SIZE; pos++){
            if (s[pos] == 0){
                x = pos%LEN;
                y = pos/LEN;
                break;
            }
        }

        // move up
        if (y < LEN-1)
            SS.insert(MoveBlock(s, pos+LEN, pos));

        // move down
        if (y>0)
            SS.insert(MoveBlock(s, pos-LEN, pos));

        // move left
        if (x < LEN-1)
            SS.insert(MoveBlock(s, pos+1, pos));

        // move right
        if (x > 0)
            SS.insert(MoveBlock(s, pos-1, pos));

        return SS;
    }

    // check if the state st is the solution, which is
    // 1, 2, ..., N-1, 0
    bool found(State st)
    {
        for (int i=0; i<SIZE-1; i++) {
            if (st[i]!= i+1)
                return false;
        }
        return true;
    }

    // solve the problem using BFS
    int solve()
    {
        queue<Node<SIZE>*>  q;      // queue
        set<State>   explored;      // the states appeared before
        Node<SIZE>* current = new Node<SIZE>(st);  // current solution
        Node<SIZE>* child;                          // expanded solution
        bool done = false;                          // flag for termination

        // early exit check
        if (found(current->st)){
            return 1;
        }
        // start the search
        q.push(current);
        explored.insert(current->st);

        while(q.size()!=0 && !done && current->level<15) {
            current = q.front();
            auto nextStates = extend(current->st);      // find all possible states
            for (auto s : nextStates) {
                if (found(s)) {                         // found a solution
                    sol = new Node<SIZE>(s, current);
                    done = true;
                } else {                                // not a solution
                    auto next = explored.find(s);
                    if (next == explored.cend()) {      // a new node
                        child = new Node<SIZE>(s, current);
                        explored.insert(s);
                        q.push(child);
                    }
                }
            }
            q.pop();
        }

        return done? sol->level:-1;
    }

    // show the status of the board.
    void show_state(State s)
    {
        int i, j;
        for (i=0; i<LEN; i++){
            for(j=0;j<LEN; j++)
                cout << setw(4) << s[i*LEN+j]<< " ";
            cout<< endl;
        }
    }

    // find the difference between two consecutive states
    int diff(State &a, State &b){
        int i;
        for(i=0;i<SIZE;i++){
            if(a[i]!=b[i]){
                return (a[i]==0)?b[i]:a[i];
            }
        }
        return -1;
    }

    // show the solving sequence
    void show_solutions() {
        Node<SIZE>* temp = sol;
        vector<State> tracking;
        int i;

        while (temp != nullptr){ // back tracking
            tracking.push_back(temp->st);
            temp = temp->parent;
        }

        for(i=tracking.size()-1; i>0; i--){
            show_state(tracking[i]);
            cout << "move "<< diff(tracking[i-1], tracking[i]) <<"->\n";
        }
        show_state(tracking[0]);
    }
};

// main function
int main()
{
    int step;
    array<int, 9> init1;
    int T;
    cin >> T;
    while(T--){
        for(int i=0; i<9; i++){
            cin >> init1[i];
        }
        SlideGame<9> problem(init1);
        step = problem.solve();
        if (step>=0 && step<16){
            //problem.show_solutions();
            cout<< "You can solve it within "<< step-1 << " steps." << endl;
        } else
            cout << "You'd better skip this game." << endl;
    }
}
