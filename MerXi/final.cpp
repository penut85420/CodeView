#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Sequence {
public:
    int *number;
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
    void w_action(int a) {
        this->action = a;
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

    int getAction() {
        return action;
    }
private:
    int gScore;
    int hScore;
    int fScore;
    int action;
    Sequence *leftNode;
    Sequence *rightNode;
};

bool isGoal(int nodeState[], int totalPancakes) {
    int min = nodeState[0];
    int max = nodeState[0];
    int i;

    for (i = 0; i < totalPancakes; i++) { //��X�̤p�M�̤j��
        if (nodeState[i] < min) {
            min = nodeState[i];
        }

        if (nodeState[i] > max) {
            max = nodeState[i];
        }
    }

    for (i = 0; i < totalPancakes; i++) { //�}�l�P�_ �O�}�C�����s����
        if (i == 0 && nodeState[i] != min) {
            // printf("NO\n");
            return false;
        } else if (i > 0 && i < totalPancakes - 1) {
            if (nodeState[i] < nodeState[i - 1]) {
                // printf("NO\n");
                return false;
            }
        } else if (i == totalPancakes - 1) {
            if (nodeState[i] == max) {
                // printf("YES\n");
                return true;
            }
        }
    }
};

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

Sequence* makeSuccessor(Sequence *current, int action, int totalPancakes) {
    Sequence *returnNode = new Sequence();

    // ½�઺�����ACurrent���᭱�n���Return���e��
    for (int i = 0; i < action; i++)
        returnNode->w_number(i, current->useNumber(action - i - 1));

    // �S��½�઺�����ӭ��
    for (int i = action; i < totalPancakes; i++)
        returnNode->w_number(i, current->useNumber(i));

    returnNode->w_gScore(current->getgScore() + 1);
    returnNode->w_hScore(gapNumber(returnNode->number, totalPancakes));

    // f = g + h
    returnNode->w_fScore();
    returnNode->w_action(action);
}

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
    int i, n; // �P�|�h��
    scanf("%d", &n);
    Sequence *head = new Sequence();

    for (i = 0; i < n; i++) { // ��J�P��
        int in;
        scanf("%d", &in);
        head->w_number(i, in);
    }

    head->w_hScore(gapNumber(head->number, n));
    head->w_gScore(0);
    head->w_fScore();
    head->w_action(0);

    while (!isGoal(head->number, n)) {
        head->setLeftNode(NULL);
        head->setRightNode(NULL);
        for (i = 2; i <= n; i++) {
            if (i == head->getAction()) continue;
            Sequence *result = makeSuccessor(head, i, n);
            // ��Ҧ�Node���JHeap��
            insertheapSort(head, result);
        }
        // ��oMin Node����Round���̨ΰʧ@
        Sequence *result = getMin(head);
        printf("(%d)", result->getAction());
        for (int k = 0; k < n; k++)
            printf(" %d", result->useNumber(k));
        printf("\n");
        head = result;
        // ��h score�]���ܤj���Ȥ~���|�~���Min Node
        head->w_hScore(9999);
        head->w_fScore();
    }

    return 0;
}
