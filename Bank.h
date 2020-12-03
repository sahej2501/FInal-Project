#pragma once
#include <string>
#include <iostream>
#include "savings.h"
#include "checking.h"
#include "CD.h"

struct AllAccounts
{
    int key;
    Savings save;
    Checking check;
    CD cd;
};


struct bankAcc
{
    AllAccounts acc;
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
        bool search(bankAcc *&, int);
        bankAcc* removeTraversal(bankAcc *&, int);       //function that removes a given apartment
        bankAcc* minimumKey(bankAcc* curr);
        void displayAllAccounts(bankAcc *) const;

    public:
        BankTree();
        ~BankTree();

        void insertAcc(AllAccounts);
        void searchAcc(int);
        void removeAcc(int);

        void displayAllTenants()
        {
            displayAllTenants(root);
        }
};

BankTree::BankTree()
{
    root = nullptr;
}

BankTree::~BankTree()
{
}

void BankTree::displayAllAccounts(bankAcc *nodePtr) const
{
   if (nodePtr)
   {
      if(nodePtr->acc.key != -1)
      {
         
         displayAllAccounts(nodePtr->left);
         cout<<nodePtr->acc.save.getAccountNumber()<<endl;
         displayAllAccounts(nodePtr->right);
      }
   }
}

//**********************************************************
// insertUnit creates a new node to hold newAcc as its value, *
// and passes it to the insert function.                   *
//**********************************************************

void BankTree::insertAcc(AllAccounts newAcc)
{
   bankAcc *newNode = new bankAcc; // Pointer to a new node.
   // Store num in new node.
   newNode->acc = newAcc;
   newNode->left = nullptr; 
   newNode->right = nullptr;


   // Insert the node.
   insert(root, newNode);
}