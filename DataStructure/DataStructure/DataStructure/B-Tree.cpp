/*
 * File processing, 2020
 * btree.cpp
 * implementation of B-tree
 */

#include <stdio.h>
#include <stdlib.h>
#include <iostream>

 /**
  * BTNode represents a single node in B-tree.
  */
typedef class BTNode {
public:
	int           n, * K;
	class BTNode** P;
} BTNode;

/**
 * getBTNode retruns a new BTNode.
 * @param m: number of branch points in B-tree
 * @return a new BTNode
 */
BTNode* getBTNode(int m) {
	//BTNode* node = (BTNode*)malloc(sizeof(BTNode));
	//node->K = (int*)malloc(sizeof(int) * (m - 1));
	//node->P = (BTNode**)malloc(sizeof(BTNode*) * m);
	BTNode* node = new BTNode;
	node->n = 0;

	node->K = new int[m - 1]; // m-1���� ������
	node->P = new BTNode*[m]; // m���� ��� ����

	return node;
}

typedef BTNode* BTree;

/**
 * insertBT inserts newKey into T.
 * @param T: a B-tree
 * @param m: number of branch points in B-tree
 * @param newKey: a key to insert
 */
void insertBT(BTree* T, int m, int newKey) {
	/* write your code here */
}

/**
 * deleteBT deletes oldKey from T.
 * @param T: a B-tree
 * @param m: number of branch points in B-tree
 * @param oldKey: a key to delete
 */
void deleteBT(BTree* T, int m, int oldKey) {
	/* write your code here */
}

/**
 * inorderBT implements inorder traversal in T.
 * @param T: a B-tree
 */
void inorderBT(BTree T) {
	/* write your code here */
}

int main() {
	/* do not modify the code below */

	int insertTestCases[] = { 40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 66, 10, 22, 30, 44, 55, 50, 60, 100, 28, 18, 9, 5, 17, 6, 3, 1, 4, 2, 7, 8, 73, 12, 13, 14, 16, 15, 25, 24, 28, 45, 49, 42, 43, 41, 47, 48, 46, 63, 68, 61, 62, 64, 69, 67, 65, 54, 59, 58, 51, 53, 57, 52, 56, 83, 81, 82, 84, 75, 89 };
	int deleteTestCases[] = { 66, 10, 22, 30, 44, 55, 50, 60, 100, 28, 18, 9, 5, 17, 6, 3, 1, 4, 2, 7, 8, 73, 12, 13, 14, 16, 15, 25, 24, 28, 40, 11, 77, 33, 20, 90, 99, 70, 88, 80, 45, 49, 42, 43, 41, 47, 48, 46, 63, 68, 53, 57, 52, 56, 83, 81, 82, 84, 75, 89, 61, 62, 64, 69, 67, 65, 54, 59, 58, 51 };

	BTree T = NULL;

	for (int tC : insertTestCases) { insertBT(&T, 3, tC); inorderBT(T); printf("\n"); }
	for (int tC : deleteTestCases) { deleteBT(&T, 3, tC); inorderBT(T); printf("\n"); }

	T = NULL;

	for (int tC : insertTestCases) { insertBT(&T, 4, tC); inorderBT(T); printf("\n"); }
	for (int tC : deleteTestCases) { deleteBT(&T, 4, tC); inorderBT(T); printf("\n"); }
}