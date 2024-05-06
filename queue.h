#pragma once
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

template<typename D>

struct Node {
  D data;
  Node* nextPtr;
};

template<typename D>
class Queue {
private:
  Node<D>* headPtr;
  Node<D>* tailPtr;

public:
  Queue();
  ~Queue();
  void enQueue(D d);
  D deQueue();
  D peek();
  bool isEmpty();
  void printQueue();
};


template<typename D>
Queue<D>::Queue() {
  headPtr = nullptr;
  tailPtr = nullptr;
}



template<typename D>
bool Queue<D>::isEmpty() {
  return (headPtr == nullptr);
}



template<typename D>
void Queue<D>::enQueue(D d) {
  //code this
  // create node
  Node<D>* newNode = new Node<D>;
  newNode->data = d;
  newNode->nextPtr = nullptr;
  //add to empty list?
  if (isEmpty()) {
  headPtr = newNode;
  tailPtr = newNode;
  }
  //add to end of list
  else {
    tailPtr->nextPtr = newNode;
    tailPtr = newNode;

  }
}


template<typename D>
D Queue<D>::deQueue() {
  //code this
  D tempData;
  if (!isEmpty()){
    tempData = headPtr->data;
    Node<D>* tempNode = headPtr;
    headPtr = headPtr->nextPtr;
    delete tempNode;
    tempNode = nullptr;
    return tempData;
    }
  else
    throw runtime_error("Queue is empty");

}



template<typename D>
D Queue<D>::peek() {
  //code this
  D tempData;
  if (!isEmpty()) {
    tempData = headPtr->data;
  }
  return tempData;
}

template<typename D>
Queue<D>::~Queue() {
    while (!isEmpty()){
      deQueue();
    }
}


template<typename D>
void Queue<D>::printQueue() {
  //coded for your
  Node<D>* tempNode = headPtr;
  while (tempNode != nullptr) {
    cout << tempNode->data->getMake() << "  " << tempNode->data->getModel()<< endl;
    tempNode = tempNode->nextPtr;
  }
  cout << "Ending queue print\n";
};