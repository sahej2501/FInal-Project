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
        bankAcc* removeTraversal(bankAcc *&, int);       //function that removes a given key
        bankAcc* minimumKey(bankAcc* curr);
        void displayAllAccounts(bankAcc *&) const;
        bool upadte(bankAcc *&, int num, AllAccounts);
        void setCurrentAccout(bankAcc *);

    public:
      BankTree();
      ~BankTree();

      timeHandler t;
      string closeInfo;
      AllAccounts currAccount;

      void insertAcc(AllAccounts);
      bool searchAcc(int);
      void removeAcc(int);
      void upadteAcc(int, AllAccounts);

      void closeAccount(bankAcc *&nodePtr)
      {
         string close;
         close = nodePtr->acc.getAccountNumber() + " " + nodePtr->acc.getName() + " " + 
         nodePtr->acc.getPhone() + " " + nodePtr->acc.getAddress() + " ";
         closeInfo = close;
      }

      void modifi(AllAccounts &);
   

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

//*****************************************
// Allows for modfication such as deposit
//*****************************************

void BankTree::modifi(AllAccounts &temp)
{
   string name, fName, lName;
   //AllAccounts temp;
   //messes up interest
   // temp.setBalance(currAccount.acc.getSavingsBalance(), currAccount.acc.getCheckingBalance(), currAccount.acc.getCDBalance());
   // name = currAccount.acc.getName();
   // fName = name.substr(0, name.find(" "));
   // lName = name.substr(name.find(" ") + 1, name.length());
   // temp.setFirstLastName(fName, lName);
   // temp.setAccountNumber(currAccount.acc.getAccountNumber());
   // temp.setAddress(currAccount.acc.getAddress());
   // temp.setPhone(currAccount.acc.getPhone());
   // temp.setKey(currAccount.acc.getKey());
   //cout<<currAccount.getAccountNumber()<<endl;

   temp.setBalance(currAccount.getSavingsBalance(), currAccount.getCheckingBalance(), currAccount.getCDBalance());
   name = currAccount.getName();
   fName = name.substr(0, name.find(" "));
   lName = name.substr(name.find(" ") + 1, name.length());
   temp.setFirstLastName(fName, lName);
   temp.setAccountNumber(currAccount.getAccountNumber());
   //cout<<temp.getAccountNumber()<<endl;
   temp.setAddress(currAccount.getAddress());
   temp.setPhone(currAccount.getPhone());
   temp.setKey(currAccount.getKey());

}

//************************************************
// Helper function that helps the update function
//************************************************

void BankTree::upadteAcc(int k, AllAccounts c)
{
   upadte(root, k, c);
   // cout<<"Done"<<endl;
}

//************************************************************
// Used to update the node with changes made by user
//***********************************************************

bool BankTree::upadte(bankAcc *&nodePtr, int num, AllAccounts temp)
{
   if (nodePtr == nullptr)
   {
      return false;
   }
   else if (nodePtr->acc.getKey() == num)
   {
      // cout<<"Found"<<endl;
      nodePtr->acc.setBalance(temp.getSavingsBalance(), temp.getCheckingBalance(), temp.getCDBalance());
      return true;
   }
   // recur on left subtree
   if (upadte(nodePtr->left, num, temp))
      return true;
   
   //recur on right subtree
   bool rightFind = upadte(nodePtr->right, num, temp);

   //recur on right allows overall return booleen variable, avoids errors
   return rightFind;
}

// void BankTree::displayAllAccounts(bankAcc *&nodePtr) const
// {
//    if (nodePtr)
//    {
//       if(nodePtr->acc.getKey() != -1)
//       {
         
//          displayAllAccounts(nodePtr->left);
//          cout<<nodePtr->acc.getKey()<<endl;
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
//    close = nodePtr->acc.getAccountNumber() + " " + nodePtr->acc.getName() + " " + 
//    nodePtr->acc.getPhone() + " " + nodePtr->acc.getAddress() + " ";
//    closeInfo = close;
// }

//**********************************************************
// insertbankAcc creates a new node to hold newAcc as its value, *
// and passes it to the insert function.                   *
//**********************************************************

void BankTree::insertAcc(AllAccounts newAcc)
{
   string name, fName, lName;
   bankAcc *newNode = new bankAcc; // Pointer to a new node.
   // Store num in new node.
   //cout<<newAcc.getAccountNumber()<<endl;
   newNode->acc.setBalance(newAcc.getSavingsBalance(), newAcc.getCheckingBalance(), newAcc.getCDBalance());
   name = newAcc.getName();
   fName = name.substr(0, name.find(" "));
   lName = name.substr(name.find(" ") + 1, name.length());
   newNode->acc.setFirstLastName(fName, lName);
   newNode->acc.setAccountNumber(newAcc.getAccountNumber());
   // cout<<newNode->acc.getAccountNumber()<<endl;
   newNode->acc.setAddress(newAcc.getAddress());
   newNode->acc.setPhone(newAcc.getPhone());
   newNode->acc.setKey(newAcc.getKey());

   // newNode->acc = &newAcc;
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
   else if (newNode->acc.getKey() < nodePtr->acc.getKey())
      insert(nodePtr->left, newNode); // Search the left branch
   else if (newNode->acc.getKey() > nodePtr->acc.getKey())
      insert(nodePtr->right, newNode); // Search the right branch
   else
      cout<<"key already has in use"<<endl;
}

//**********************************************************
// searchNode accepts num provided by user, and passes     *
// it to the search function.                              *
//**********************************************************

bool BankTree::searchAcc(int num)
{ 
   bool found;
   if (search(root, num))
   {
      cout<<"Found"<<endl;   //prints out Not Found when search funtion returns false
      found = true;
   }
   else
   {
      cout<<"Not Found"<<endl;
      found = false;
   }
   return found;
}

//**************************************************
// Set the the values from current node so it can be displayed
//*********************************************************

// void BankTree::getCurrentAcc(AllAccounts &curr, bankAcc *&nodePtr)
// {
//    currAccount.setFirstLastName(nodePtr->acc.getName());
//    currAccount.setAccountNumber(nodePtr->acc.getAccountNumber());
//    currAccount.setKey(nodePtr->acc.getKey());
//    currAccount.setAddress(nodePtr->acc.getAddress());

// }

//*************************************************************
// search accepts a bankAcc pointer and an integer value as the 
// key number.     *
// The function returns true when the key number is equal   *
// to the value in the node pointed to by the bankAcc pointer.* 
// This function is called recursively, and it returns false   *
// when the key number cannot be found in the Tree          *
//*************************************************************

bool BankTree::search(bankAcc *&nodePtr, int num)
{
   if (nodePtr == nullptr)
   {
      return false;
   }
   else if (nodePtr->acc.getKey() == num)
   {
      //cout<<nodePtr->acc.getAccountNumber()<<endl;
      setCurrentAccout(nodePtr);
      return true;
   }
   // recur on left subtree
   if (search(nodePtr->left, num))
      return true;
   
   //recur on right subtree
   bool rightFind = search(nodePtr->right, num);

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
   if (num < nodePtr->acc.getKey())
   {
      nodePtr->left = removeTraversal(nodePtr->left, num);
   }
   else if(num > nodePtr->acc.getKey())
   {
      nodePtr->right = removeTraversal(nodePtr->right, num);
   }
   else if(num == nodePtr->acc.getKey())
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
         nodePtr->acc.setKey(temp->acc.getKey()); //sets the min value in right tree for deleting node
         nodePtr->right = removeTraversal(nodePtr->right, temp->acc.getKey());
      }
   }
   return nodePtr; 
}

void BankTree::setCurrentAccout(bankAcc *nodePtr)
{
   string name, fName, lName;
   //AllAccounts temp;
   //messes up interest
   //cout<<nodePtr->acc.getAccountNumber()<<endl;
   currAccount.setBalance(nodePtr->acc.getSavingsBalance(), nodePtr->acc.getCheckingBalance(), nodePtr->acc.getCDBalance());
   name  = nodePtr->acc.getName();
   fName = name.substr(0, name.find(" "));
   lName = name.substr(name.find(" ") + 1, name.length());
   currAccount.setFirstLastName(fName, lName);
   currAccount.setAccountNumber(nodePtr->acc.getAccountNumber());
   currAccount.setAddress(nodePtr->acc.getAddress());
   currAccount.setPhone(nodePtr->acc.getPhone());
   currAccount.setKey(nodePtr->acc.getKey());
   //cout<<currAccount.getAccountNumber()<<endl;
}
#endif