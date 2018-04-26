#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;
//part1
bool isGoal(int nodeState[], int totalPancakes) {
    int min = nodeState[0];
    int max = nodeState[0];
    int i;

    for (i = 0; i < totalPancakes; i++) { //找出最小和最大值
        if (nodeState[i] < min) {
            min = nodeState[i];
        }

        if (nodeState[i] > max) {
            max = nodeState[i];
        }
    }

    for (i = 0; i < totalPancakes; i++) { //開始判斷 令陣列中為連續整數
        if (i == 0 && nodeState[i] != min) {
            printf("NO\n");
            return false;
        } else if (i > 0 && i < totalPancakes - 1) {
            if (nodeState[i] < nodeState[i - 1]) {
                printf("NO\n");
                return false;
            }
        } else if (i == totalPancakes - 1) {
            if (nodeState[i] == max) {
                printf("YES\n");
                return true;
            }
        }
    }
};
//part2
int gapNumber(int nodeState[], int totalPancakes) {
    int count = 0;
    int i, j;

    for (i = 0; i < totalPancakes - 1; ++i) {
        j = nodeState[i] - nodeState[i + 1];

        if (j > 1 || j < -1) {
            count++;
        }
    }

    return count;
}
//part3
typedef struct Node {
    short int state[16];
    int g;
    int h;
    int f;
    int action;
    Node *prevNode;
} Node;

Node* makeSuccessor(Node *current, int action, int totalPancakes) {
    Node *returnNode = (Node*) malloc(sizeof(Node));

    // 翻轉的部分，Current的後面要放到Return的前面
    for (int i = 0; i < action; i++)
        returnNode->state[i] = current->state[action - i - 1];

    // 沒有翻轉的部分照原位
    for (int i = action; i < totalPancakes; i++)
        returnNode->state[i] = current->state[i];

    returnNode->g = current->g + 1;

    // 還沒有取得gapNumber()，先預設1
    returnNode->h = 1;

    // f = g + h
    returnNode->f = returnNode->g + returnNode->h;
    returnNode->action = action;
    returnNode->prevNode = current;

    return returnNode;
}

void makeSuccessor_test() {
    int N;
    scanf("%d", &N);

    for (int i = 0; i < N; i++) {
        int n;
        Node *head = (Node*) malloc(sizeof(Node));
        // Input Data
        scanf("%d", &n);
        for (int j = 0; j < n; j++)
            scanf("%d", &head->state[j]);
        scanf("%d", &head->g);
        scanf("%d", &head->action);
        head->h = 1;
        head->prevNode = NULL;
        head->f = head->g + head->h;

        // Action從2開始到total
        for (int j = 2; j <= n; j++) {
            // 跟上一步的Action一樣要跳過
            if (head->action == j) continue;
            Node *result = makeSuccessor(head, j, n);

            // Print State
            printf("[%d", result->state[0]);
            for (int k = 1; k < n; k++)
                printf(" %d", result->state[k]);
            printf("], %d, %d, %d, %d\n", result->g, result->h, result->f, result->action);
        }
    }
    printf("makeSuccessor_test done.\n");
}
//part4 //#include "sequence.h"
class Sequence {
public:
    Sequence() : gScore(0), hScore(0), fScore(0) {
        number = new int[16];
        this->leftNode = NULL;
        this->rightNode = NULL;
    }
    ~Sequence() {
        delete[] number;
    }

    void w_gScore(int gScore) {
        this->gScore = gScore;
    }
    void w_hScore(int hScore) {
        this->hScore = hScore;
    }

    void w_fScore() {
        this->fScore = this->gScore + this->hScore;
    }
    void w_number(int i, int number) {
        this->number[i] = number;
    }
    Sequence* getLeftNode() {
        return this->leftNode;
    }

    Sequence* getRightNode() {
        return this->rightNode;
    }
    void setLeftNode(Sequence* node) {
        this->leftNode = node;
    }

    void setRightNode(Sequence* node) {
        this->rightNode = node;
    }

    int getfScore() {
        return this->fScore;
    }

    int gethScore() {
        return this->hScore;
    }

    int getgScore() {
        return this->gScore;
    }

    int useNumber(int i) {
        return this->number[i];
    }
private:
    int *number;
    int gScore;
    int hScore;
    int fScore;
    Sequence *leftNode;
    Sequence *rightNode;
};

void printTree(Sequence *head) {
    if (head != NULL) {
        printTree(head->getLeftNode());
        cout << "[";

        for (int ii = 0; ii < 16; ii++) {
            cout << head->useNumber(ii);

            if (ii == 15) {
                cout << "]";
            } else {
                cout << " ";
            }
        }

        cout << ", ";
        cout << head->getgScore() << ", " << head->gethScore() << ", " << head->getfScore() << endl;
        printTree(head->getRightNode());
    }
}

void insertheapSort(Sequence *head, Sequence *current) {
    if (head == NULL) {
        head = current;
    } else if (head->getfScore() < current->getfScore()) {
        if (head->getRightNode() == NULL) {
            head->setRightNode(current);
        } else {
            insertheapSort(head->getRightNode(), current);
        }
    } else if (head->getfScore() > current->getfScore()) {
        if (head->getLeftNode() == NULL) {
            head->setLeftNode(current);
        } else {
            insertheapSort(head->getLeftNode(), current);
        }
    } else {
        for (int i = 0; i < 16; i++) {
            if (head->useNumber(i) < current->useNumber(i)) {
                if (head->getRightNode() == NULL) {
                    head->setRightNode(current);
                } else {
                    insertheapSort(head->getRightNode(), current);
                }

                break;
            } else if (head->useNumber(i) > current->useNumber(i)) {
                if (head->getLeftNode() == NULL) {
                    head->setLeftNode(current);
                } else {
                    insertheapSort(head->getLeftNode(), current);
                }

                break;
            } else if (i == 15) {
                if (head->getRightNode() == NULL) {
                    head->setRightNode(current);
                } else {
                    insertheapSort(head->getRightNode(), current);
                }

                break;
            }

        }
    }

}

void removeMin(Sequence *head, Sequence *target) {
    if (head->getLeftNode() == target) {
        if (head->getLeftNode()->getRightNode() == NULL) {
            head->setLeftNode(NULL);
        } else {
            head->setLeftNode(head->getLeftNode()->getRightNode());
        }
    } else {
        removeMin(head->getLeftNode(), target);
    }
}

Sequence* getMin(Sequence *head) {
    if (head->getLeftNode() == NULL) {
        return head;
    }

    getMin(head->getLeftNode());
}

int main() {
    makeSuccessor_test();
    int i, n; //蛋糕層數
    scanf("%d", &n);
    int *cake;//蛋糕
    cake = (int *)malloc(n * sizeof(int));

    for (i = 0; i < n; i++) { //輸入蛋糕
        int in;
        scanf("%d", &in);
        cake[i] = in;
    }

    int gapNum;//h
    gapNum = gapNumber(cake, n);

    free(cake);
    return 0;
}
