#include <iostream>
#include <stdio.h>
#include <stdlib.h>

using namespace std;

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

int main() {
    makeSuccessor_test();
    return 0;
}