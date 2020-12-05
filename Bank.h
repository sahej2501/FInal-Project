#ifndef BANK_H
#define BANK_H
#include <string>
#include <iostream>
#include "AccountNode.h"
#include "savings.h"
#include "checking.h"
#include "timeHandler.h"
#include "CD.h"



struct bankAcc
{
    AllAccounts *acc;
    bankAcc *left;
    bankAcc *right;
};

class BankTree
{
    private:
        bankAcc *root;  //root
        
        //functions methods for public method manipulation 
        void insert(bankAcc *&, bankAcc *&);
        void deleteNode(AllAccounts, bankAcc *&);
        bool search(bankAcc *&, int, bankAcc &);
        bankAcc* removeTraversal(bankAcc *&, int);       //function that removes a given key
        bankAcc* minimumKey(bankAcc* curr);
        void displayAllAccounts(bankAcc *&) const;

    public:
      BankTree();
      ~BankTree();

      timeHandler t;
      string closeInfo;
      bankAcc currAccount;

      void insertAcc(AllAccounts);
      void searchAcc(int);
      void removeAcc(int);

      void closeAccount(bankAcc *&nodePtr)
      {
         string close;
         close = nodePtr->acc->getAccountNumber() + " " + nodePtr->acc->getName() + " " + 
         nodePtr->acc->getPhone() + " " + nodePtr->acc->getAddress() + " ";
         closeInfo = close;
      }
   

      void setCurrNode(AllAccounts &, bankAcc *&);

      //   void displayAllTenants()
      //   {
      //       displayAllTenants(root);
      //   }
};

BankTree::BankTree()
{
    root = nullptr;
}

BankTree::~BankTree()
{
}

// void BankTree::displayAllAccounts(bankAcc *&nodePtr) const
// {
//    if (nodePtr)
//    {
//       if(nodePtr->acc->getKey() != -1)
//       {
         
//          displayAllAccounts(nodePtr->left);
//          cout<<nodePtr->acc->getKey()<<endl;
//          displayAllAccounts(nodePtr->right);
//       }
//    }
// }

//*********************************************
// returns string of all closing information to
// be saved later
//*********************************************

// void closeAccount(bankAcc *&nodePtr)
// {
//    string close;
//    close = nodePtr->acc->getAccountNumber() + " " + nodePtr->acc->getName() + " " + 
//    nodePtr->acc->getPhone() + " " + nodePtr->acc->getAddress() + " ";
//    closeInfo = close;
// }

//**********************************************************
// insertbankAcc creates a new node to hold newAcc as its value, *
// and passes it to the insert function.                   *
//**********************************************************

void BankTree::insertAcc(AllAccounts newAcc)
{
   bankAcc *newNode = new bankAcc; // Pointer to a new node.
   // Store num in new node.
   newNode->acc = &newAcc;
   newNode->left = nullptr;
   newNode->right = nullptr;
   
   // Insert the node.
   insert(root, newNode);
}

//*************************************************************
// insert accepts a Acc pointer and a pointer to a node. *
// The function inserts the node into the tree pointed to by  *
// the Acc pointer. This function is called recursively. *
//*************************************************************

void BankTree::insert(bankAcc *&nodePtr, bankAcc *&newNode)
{
   if (nodePtr == nullptr)
      nodePtr = newNode; // Insert the node.
   else if (newNode->acc->getKey() < nodePtr->acc->getKey())
      insert(nodePtr->left, newNode); // Search the left branch
   else if (newNode->acc->getKey() > nodePtr->acc->getKey())
      insert(nodePtr->right, newNode); // Search the right branch
   else
      cout<<"key already has in use"<<endl;
}

//**********************************************************
// searchNode accepts num provided by user, and passes     *
// it to the search function.                              *
//**********************************************************

void BankTree::searchAcc(int num)
{ 
   if (search(root, num, currAccount))
   {
      cout<<"Found"<<endl;   //prints out Not Found when search funtion returns false
   }
   else
   {
      cout<<"Not Found"<<endl;
   }
}

//**************************************************
// Set the the values from current node so it can be displayed
//*********************************************************

// void BankTree::getCurrentAcc(AllAccounts &curr, bankAcc *&nodePtr)
// {
//    currAccount.setFirstLastName(nodePtr->acc->getName());
//    currAccount.setAccountNumber(nodePtr->acc->getAccountNumber());
//    currAccount.setKey(nodePtr->acc->getKey());
//    currAccount.setAddress(nodePtr->acc->getAddress());

// }

//*************************************************************
// search accepts a bankAcc pointer and an integer value as the 
// key number.     *
// The function returns true when the key number is equal   *
// to the value in the node pointed to by the bankAcc pointer.* 
// This function is called recursively, and it returns false   *
// when the key number cannot be found in the Tree          *
//*************************************************************

bool BankTree::search(bankAcc *&nodePtr, int num, bankAcc &currAccount)
{
   if (nodePtr == nullptr)
   {
      return false;
   }
   else if (nodePtr->acc->getKey() == num)
   {
      cout<<"Found"<<endl;
      currAccount = *nodePtr;
      return true;
   }
   // recur on left subtree
   if (search(nodePtr->left, num, currAccount))
      return true;
   
   //recur on right subtree
   bool rightFind = search(nodePtr->right, num, currAccount);

   //recur on right allows overall return booleen variable, avoids errors
   return rightFind;
}

//******************************************************
// The remove function accepts the key number and
// then removes it from the tree 
//*******************************************************

void BankTree::removeAcc(int key)
{
   removeTraversal(root, key);
}

//****************************************
// Finds the minimum value in the right 
// subtree for case 3 in removal traversal
//****************************************

bankAcc* BankTree::minimumKey(bankAcc* curr)
{
   while (curr->left != nullptr) 
   {
		curr = curr->left;
	}
	return curr;
}

//********************************************************
// Removes the node with the given key number and
// returns a type bankAcc
//*********************************************************

bankAcc* BankTree::removeTraversal(bankAcc *&nodePtr, int num)
{
   //base case 
   if (nodePtr == nullptr)
   {
      return nodePtr;
   }

   //recursivly searchs for the given key num
   if (num < nodePtr->acc->getKey())
   {
      nodePtr->left = removeTraversal(nodePtr->left, num);
   }
   else if(num > nodePtr->acc->getKey())
   {
      nodePtr->right = removeTraversal(nodePtr->right, num);
   }
   else if(num == nodePtr->acc->getKey())
   {
      closeAccount(nodePtr);
      //case 1: deleting node does not have any children
      if(nodePtr->left == nullptr && nodePtr->right == nullptr)
      {
         delete nodePtr;
         nodePtr = nullptr;
      }

      //case 2: if it has only one child
      else if(nodePtr->left == nullptr)   //if there is only right child
      {
         bankAcc *temp = nodePtr;
         nodePtr = nodePtr->right;
         delete temp;
      }
      else if(nodePtr->right == nullptr)  //if there is only left child
      {
         bankAcc *temp = nodePtr;
         nodePtr = nodePtr->left;
         delete temp;
      }
      
      //Case 3: if there are 2 children
      else
      {
         bankAcc *temp = minimumKey(nodePtr->right);
         nodePtr->acc->setKey(temp->acc->getKey()); //sets the min value in right tree for deleting node
         nodePtr->right = removeTraversal(nodePtr->right, temp->acc->getKey());
      }
   }
   return nodePtr; 
}
#endif