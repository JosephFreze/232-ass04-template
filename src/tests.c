#ifndef UNITY_H
#define UNITY_H
#include "unity.h"
#endif
#include <stdlib.h>

// ============================================================
// Forward declarations — implemented in code.c
// ============================================================

typedef struct Node {
    int value;
    struct Node *nextPtr;
} Node;

void  initNode    (Node *nodePtr, int value);
Node* createNode  (int value);
void  destroyNode (Node **nodePtrPtr);
void  destroyList (Node **headPtrPtr);
int   addFirst    (Node **headPtrPtr, Node *newNodePtr);
int   addLast     (Node **headPtrPtr, Node *newNodePtr);
Node* detachFirst (Node **headPtrPtr);
Node* detachLast  (Node **headPtrPtr);
Node* detachValue (Node **headPtrPtr, int value);
int   deleteFirst (Node **headPtrPtr);
int   deleteLast  (Node **headPtrPtr);
int   deleteValue (Node **headPtrPtr, int value);
void  destroyList (Node **headPtrPtr);
int   printList   (Node *headPtr);
int   listLength  (Node *headPtr);


// ============================================================
//  UNIT TESTS
//
//  Rules:
//  - Use TEST_ASSERT_TRUE_MESSAGE for every assertion.
//  - Do NOT use TEST_ASSERT_EQUAL — it reveals expected values.
//  - Heap tests: use createNode / destroyList.
//  - Stack tests: declare Node variables on the stack.
//  - Do NOT modify function names or signatures.
// ============================================================


// ============================================================
// test_initNode_sets_value
//
// Declare a Node on the stack.
// Call initNode with a known value.
// Verify that the value field contains that value.
// ============================================================

void test_initNode_sets_value(void)
{
    Node a;

    initNode(&a, 4);

    TEST_ASSERT_EQUAL(4, a.value);
}


// ============================================================
// test_initNode_sets_next_null
//
// Declare a Node on the stack.
// Call initNode.
// Verify that nextPtr is NULL after the call.
// ============================================================

void test_initNode_sets_next_null(void)
{
    Node a;

    initNode(&a, 4);

    TEST_ASSERT_EQUAL(NULL, a.nextPtr);

}


// ============================================================
// test_initNode_null_guard
//
// Call initNode with NULL as the nodePtr.
// Verify the program does not crash.
// ============================================================

void test_initNode_null_guard(void)
{

    initNode(NULL, 332524);

    TEST_ASSERT_TRUE_MESSAGE(1, "Didn't fail");
}


// ============================================================
// test_createNode_not_null
//
// Call createNode with a known value.
// Verify the returned pointer is NOT NULL.
// Remember to free memory after the test using destroyNode.
// ============================================================

void test_createNode_not_null(void)
{
    Node *b = createNode(45);
    TEST_ASSERT_EQUAL(45, b->value);
}


// ============================================================
// test_createNode_value
//
// Call createNode with a known value.
// Verify that the value field of the returned node
// contains the correct value.
// Remember to free memory after the test using destroyNode.
// ============================================================

void test_createNode_value(void)
{
    Node *b = createNode(45);
    TEST_ASSERT_EQUAL(45, b->value);
    destroyNode(&b);
}


// ============================================================
// test_createNode_next_null
//
// Call createNode.
// Verify that nextPtr of the returned node is NULL.
// Remember to free memory after the test using destroyNode.
// ============================================================

void test_createNode_next_null(void)
{
    Node *b = createNode(45);
    TEST_ASSERT_EQUAL(NULL, b->nextPtr);
    destroyNode(&b);
}


// ============================================================
// test_destroyNode_sets_null
//
// Call createNode to allocate a node.
// Call destroyNode.
// Verify that the pointer is NULL after the call.
// ============================================================

void test_destroyNode_sets_null(void)
{
    Node *b = createNode(45);
    destroyNode(&b); 

    TEST_ASSERT_EQUAL(NULL, b);
}


// ============================================================
// test_addFirst_empty_list
//
// Start with headPtr == NULL.
// Create a node and call addFirst.
// Verify that headPtr now points to the new node.
// Clean up with destroyList.
// ============================================================

void test_addFirst_empty_list(void)
{
    Node *headPtr = NULL;
    Node *c = createNode(5);

    addFirst(&headPtr, c);

    TEST_ASSERT_EQUAL(c, headPtr);

    destroyList(&headPtr);
}


// ============================================================
// test_addFirst_non_empty
//
// Add two nodes using addFirst.
// Verify that headPtr points to the SECOND node added
// (the most recently added node is at the front).
// Verify the first node is reachable via nextPtr.
// Clean up with destroyList.
// ============================================================

void test_addFirst_non_empty(void)
{
    Node *headPtr = NULL;
    Node *d = createNode(2);
    Node *e = createNode(3);
    
    addFirst(&headPtr, d);
    addFirst(&headPtr, e);

    TEST_ASSERT_EQUAL(e, headPtr);
    TEST_ASSERT_EQUAL(d, headPtr->nextPtr);

    destroyList(&headPtr);
}


// ============================================================
// test_addFirst_null_headptr
//
// Call addFirst with NULL as headPtrPtr.
// Verify the function returns -1.
// ============================================================

void test_addFirst_null_headptr(void)
{
    Node *f = createNode(3);
    int result = addFirst(NULL, f);

    TEST_ASSERT_EQUAL(-1, result);
}


// ============================================================
// test_addLast_empty_list
//
// Start with headPtr == NULL.
// Create a node and call addLast.
// Verify that headPtr points to the new node.
// Clean up with destroyList.
// ============================================================

void test_addLast_empty_list(void)
{
    Node *headPtr = NULL;
    Node *a = createNode(5);

    addLast(&headPtr, a);

    TEST_ASSERT_EQUAL(a, headPtr);

    destroyList(&headPtr);
}


// ============================================================
// test_addLast_non_empty
//
// Add two nodes using addLast.
// Verify that headPtr points to the FIRST node added.
// Verify the second node is reachable via nextPtr.
// Verify the second node's nextPtr is NULL.
// Clean up with destroyList.
// ============================================================

void test_addLast_non_empty(void)
{
    Node *headPtr = NULL;
    Node *a = createNode(2);
    Node *b = createNode(3);

    addLast(&headPtr, a);
    addLast(&headPtr, b);

    TEST_ASSERT_EQUAL(a, headPtr);
    TEST_ASSERT_EQUAL(b, headPtr->nextPtr);
    TEST_ASSERT_EQUAL(NULL, b->nextPtr);

    destroyList(&headPtr);
}


// ============================================================
// test_addLast_null_guard
//
// Call addLast with NULL as headPtrPtr.
// Verify the function returns -1.
// ============================================================

void test_addLast_null_guard(void)
{
    Node *a = createNode(5);

    int result = addLast(NULL, a);

    TEST_ASSERT_EQUAL(-1, result);

    destroyNode(&a);
}


// ============================================================
// test_detachFirst_returns_node
//
// Build a stack chain: a -> b -> NULL
// Call detachFirst.
// Verify the returned pointer equals &a.
// ============================================================

void test_detachFirst_returns_node(void)
{
    Node a = {1, NULL};
    Node b = {2, NULL};

    a.nextPtr = &b;
    Node *headPtr = &a;

    Node *result = detachFirst(&headPtr);

    TEST_ASSERT_EQUAL(&a, result);
}


// ============================================================
// test_detachFirst_updates_head
//
// Build a stack chain: a -> b -> NULL
// Call detachFirst.
// Verify that headPtr now points to b.
// ============================================================

void test_detachFirst_updates_head(void)
{
    Node a = {1, NULL};
    Node b = {2, NULL};

    a.nextPtr = &b;
    Node *headPtr = &a;

    detachFirst(&headPtr);

    TEST_ASSERT_EQUAL(&b, headPtr);
}

// ============================================================
// test_detachFirst_empty_list
//
// Call detachFirst on an empty list (headPtr == NULL).
// Verify the function returns NULL without crashing.
// ============================================================

void test_detachFirst_empty_list(void)
{
    Node *headPtr = NULL;

    Node *result = detachFirst(&headPtr);

    TEST_ASSERT_EQUAL(NULL, result);
}


// ============================================================
// test_detachValue_found
//
// Build a stack chain: a(1) -> b(2) -> c(3) -> NULL
// Call detachValue for value 2 (middle node).
// Verify the returned pointer equals &b.
// Verify a->nextPtr now points to c.
// Verify b->nextPtr is NULL after detach.
// ============================================================

void test_detachValue_found(void)
{
    Node a = {1, NULL};
    Node b = {2, NULL};
    Node c = {3, NULL};

    a.nextPtr = &b;
    b.nextPtr = &c;

    Node *headPtr = &a;

    Node *result = detachValue(&headPtr, 2);

    TEST_ASSERT_EQUAL(&b, result);
    TEST_ASSERT_EQUAL(&c, a.nextPtr);
    TEST_ASSERT_EQUAL(NULL, b.nextPtr);
}


// ============================================================
// test_detachValue_head
//
// Build a stack chain: a(1) -> b(2) -> NULL
// Call detachValue for value 1 (head node).
// Verify the returned pointer equals &a.
// Verify headPtr now points to b.
// ============================================================

void test_detachValue_head(void)
{
    Node a = {1, NULL};
    Node b = {2, NULL};

    a.nextPtr = &b;

    Node *headPtr = &a;

    Node *result = detachValue(&headPtr, 1);

    TEST_ASSERT_EQUAL(&a, result);
    TEST_ASSERT_EQUAL(&b, headPtr);
}


// ============================================================
// test_detachValue_not_found
//
// Build a stack chain: a(1) -> b(2) -> NULL
// Call detachValue for a value that does not exist (e.g. 99).
// Verify the function returns NULL.
// ============================================================

void test_detachValue_not_found(void)
{
    Node a = {1, NULL};
    Node b = {2, NULL};

    a.nextPtr = &b;

    Node *headPtr = &a;

    Node *result = detachValue(&headPtr, 99);

    TEST_ASSERT_EQUAL(NULL, result);
}


// ============================================================
// test_deleteFirst_removes_node
//
// Create two heap nodes and build a list.
// Call deleteFirst.
// Verify the function returns 0.
// Verify headPtr now points to the second node.
// Clean up with destroyList.
// ============================================================

void test_deleteFirst_removes_node(void)
{
    Node *a = createNode(1);
    Node *b = createNode(2);

    a->nextPtr = b;
    Node *headPtr = a;

    int result = deleteFirst(&headPtr);

    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(b, headPtr);

    destroyList(&headPtr);
}


// ============================================================
// test_deleteFirst_empty_list
//
// Call deleteFirst on an empty list.
// Verify the function returns -1 without crashing.
// ============================================================

void test_deleteFirst_empty_list(void)
{
    Node *headPtr = NULL;

    int result = deleteFirst(&headPtr);

    TEST_ASSERT_EQUAL(-1, result);
}


// ============================================================
// test_deleteValue_found
//
// Create three heap nodes: 10 -> 20 -> 30
// Call deleteValue for 20.
// Verify the function returns 0.
// Verify listLength is now 2.
// Verify 20 is no longer in the list.
// Clean up with destroyList.
// ============================================================

void test_deleteValue_found(void)
{
    Node *a = createNode(10);
    Node *b = createNode(20);
    Node *c = createNode(30);

    a->nextPtr = b;
    b->nextPtr = c;

    Node *headPtr = a;

    int result = deleteValue(&headPtr, 20);

    TEST_ASSERT_EQUAL(0, result);
    TEST_ASSERT_EQUAL(2, listLength(headPtr));
    TEST_ASSERT_EQUAL(c, a->nextPtr);

    destroyList(&headPtr);
}


// ============================================================
// test_deleteValue_not_found
//
// Create two heap nodes: 10 -> 20
// Call deleteValue for 99.
// Verify the function returns -1.
// Verify the list is unchanged (length still 2).
// Clean up with destroyList.
// ============================================================

void test_deleteValue_not_found(void)
{
    Node *a = createNode(10);
    Node *b = createNode(20);

    a->nextPtr = b;
    Node *headPtr = a;

    int result = deleteValue(&headPtr, 99);

    TEST_ASSERT_EQUAL(-1, result);
    TEST_ASSERT_EQUAL(2, listLength(headPtr));

    destroyList(&headPtr);
}


// ============================================================
// test_destroyList_empties_list
//
// Create three heap nodes and build a list.
// Call destroyList.
// Verify headPtr is NULL after the call.
// ============================================================

void test_destroyList_empties_list(void)
{
    Node *a = createNode(10);
    Node *b = createNode(20);
    Node *c = createNode(30);

    a->nextPtr = b;
    b->nextPtr = c;

    Node *headPtr = a;

    destroyList(&headPtr);

    TEST_ASSERT_EQUAL(NULL, headPtr);
}


// ============================================================
// test_listLength_empty
//
// Call listLength with NULL.
// Verify the function returns 0.
// ============================================================

void test_listLength_empty(void)
{
    int result = listLength(NULL);

    TEST_ASSERT_EQUAL(0, result);
}


// ============================================================
// test_listLength_three
//
// Create three heap nodes and build a list.
// Call listLength.
// Verify the function returns 3.
// Clean up with destroyList.
// ============================================================

void test_listLength_three(void)
{
    Node *a = createNode(10);
    Node *b = createNode(20);
    Node *c = createNode(30);

    a->nextPtr = b;
    b->nextPtr = c;

    Node *headPtr = a;

    int result = listLength(headPtr);

    TEST_ASSERT_EQUAL(3, result);

    destroyList(&headPtr);
}

// ============================================================
// test_printList_empty
//
// Call printList with NULL.
// Verify the function returns -1 without crashing.
// ============================================================

void test_printList_empty(void)
{
    int result = printList(NULL);

    TEST_ASSERT_EQUAL(-1, result);
}