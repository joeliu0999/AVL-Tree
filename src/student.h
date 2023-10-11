#pragma

#include <iostream>
#include <string>
#include <queue>
#include <vector>

class Student{
public:
    int ID;
    std::string name;
    int height;

    Student *left;
    Student *right;
    Student(int x, std::string y): ID(x),name(y),height(1),left(nullptr),right(nullptr){}
    //print preorder
    void printPreorder();
    //print inorder
    void printInorder();
    //print postorder
    void printPostorder();
    //print name is found the corresponding ID, else print unsuccessful
    void searchID(int IDToSearch);
    //print ID if corresponding name is found, else print unsuccessful
    void searchName(std::string NameToSearch);
    //return unsuccessful if the node to delete does not exist
    std::string removeID(int IDtoDelete);
    //print level count
    void printLevelCount();


};
Student* insert(Student* root, int newID, std::string newName);
std::string preorder(Student* root);
std::string inorder(Student* root);
std::string postorder(Student* root);
Student* rotateLeft(Student *node);
Student* rotateRight(Student *node);
Student* rotateRightLeft(Student *node);
Student* rotateLeftRight(Student *node);
//return the parent of the child else return nullptr
Student* findParent(Student* theRoot, Student* child);
std::vector<Student*> inorderVector(Student* root);
int maxHeight(Student* root);
bool IDExist(Student* root, int IDToSearch);
