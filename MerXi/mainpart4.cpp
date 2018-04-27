#include<iostream>
#include<string>
//#include "sequence.h"
using namespace std;
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
    if (head == target && target->getRightNode() != NULL)
        head = head->getRightNode();
    else {
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
}

Sequence* getMin(Sequence *head) {
    if (head->getLeftNode() == NULL)
        return head;

    getMin(head->getLeftNode());
}

int main() {
    Sequence sequence[100];
    Sequence *head = new Sequence;
    head = NULL;
    int now = 0;

    while (1) {
        int number;
        int gScore, hScore;
        string command;
        cin >> command;

        if (!command.compare("INSERT")) {
            for (int i = 0; i < 16; i++) {
                cin >> number;
                sequence[now].w_number(i, number);
            }

            cin >> number;
            sequence[now].w_gScore(number);
            cin >> number;
            sequence[now].w_hScore(number);
            sequence[now].w_fScore();

            if (head == NULL) {
                head = &sequence[now];
            } else {
                insertheapSort(head, &sequence[now]);
            }
        } else if (!command.compare("GETTOP")) {
            Sequence *min = new Sequence;
            min = getMin(head);
            cout << "[";

            for (int ii = 0; ii < 16; ii++) {
                cout << min->useNumber(ii);

                if (ii == 15) {
                    cout << "]";
                } else {
                    cout << " ";
                }
            }

            cout << ", ";
            cout << min->getgScore() << ", " << min->gethScore() << ", " << min->getfScore() << endl;

//            if (min == head && min->getRightNode() != NULL) {
//                head = head->getRightNode();
//            } else {
//                removeMin(head, min);
//            }
            removeMin(head, min);
        } else if (!command.compare("GETALL")) {
            if (head != NULL) {
                printTree(head);
            } else {
                cout << "Empty Tree";
            }

            break;
        } else {
            cout << "Error instrucment!!" << endl;
        }

        now++;
    }

    return 0;
}
