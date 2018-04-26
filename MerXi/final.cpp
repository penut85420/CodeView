#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

class Sequence {
public:
    int *number;
    int index;
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

    // 翻轉的部分，Current的後面要放到Return的前面
    for (int i = 0; i < action; i++)
        returnNode->w_number(i, current->useNumber(action - i - 1));

    // 沒有翻轉的部分照原位
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
    if (target == head) {
        head = head->getRightNode();
    } else if (head->getLeftNode() == target) {
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

void printAction(Sequence* s, int n) {
    printf("(%d)", s->getAction());

    for (int k = 0; k < n; k++)
        printf(" %d", s->useNumber(k));

    printf("\n");
}

void printSeq(Sequence* s, int n) {
    printf("[%d", s->number[0]);
    for (int k = 1; k < n; k++)
        printf(" %d", s->number[k]);
    printf("] g: %d, h: %d, f: %d, a: %d, i: %d\n",
           s->getgScore(), s->gethScore(),
           s->getfScore(), s->getAction(), s->index);
}

int main() {
    int i, n; // 鬆糕層數
    scanf("%d", &n);
    Sequence *head = new Sequence();

    for (i = 0; i < n; i++) { // 輸入鬆餅
        int in;
        scanf("%d", &in);
        head->w_number(i, in);
    }

    head->w_hScore(gapNumber(head->number, n));
    head->w_gScore(0);
    head->w_fScore();
    head->w_action(0);
    head->index = 1;
    head->setLeftNode(NULL);
    head->setRightNode(NULL);

    while (!isGoal(head->number, n)) {
        head->setLeftNode(NULL);
        head->setRightNode(NULL);

        for (i = 2; i <= n; i++) {
            if (i == head->getAction()) continue;

            Sequence *result = makeSuccessor(head, i, n);
            result->index = i;
//            把所有Node插入Heap中
            if (result->getgScore() == 8)
                printSeq(result, n);
            insertheapSort(head, result);
        } printf("\n");

        // 獲得Min Node為該Round的最佳動作
        Sequence *result = getMin(head);
        removeMin(head, result);
        Sequence *nextResult = getMin(head);
        removeMin(head, nextResult);

        // What the hell is this priority queue QQQQQQQQQ
        while (result->getfScore() == nextResult->getfScore() && result != nextResult) {
            int flag = 1;
            if (result->getgScore() == 8)
                printSeq(result, n), printSeq(nextResult, n);
            if (result->number[0] > nextResult->number[0]) {
                printf("STATE!!\n");
                flag = 0;
            } else if (result->getAction() > nextResult->getAction()) {
                printf("ACTION!!\n");
                flag = 0;
            } else if (result->index > nextResult->index) {
                printf("INDEX!!\n");
                flag = 0;
            }

            if (flag) result = nextResult;
            Sequence *nextnextResult = getMin(head);
            removeMin(head, nextnextResult);
            if (nextResult == nextnextResult) break;
            nextResult = nextnextResult;
//            system("pause");
        }

        printAction(result, n);
        head = result;

        // 把h score設成很大的值才不會繼續當Min Node
        head->w_hScore(9999);
        head->w_fScore();
    }

    return 0;
}
