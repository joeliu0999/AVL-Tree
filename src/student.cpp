#include "student.h"

Student* insert(Student* root, int newID, std::string newName)
{
    //impossible edge case
    if(root==nullptr)
        return new Student(newID, newName);
    if(root->ID==111191111){
        return new Student(newID, newName);
    }
    if(newID < root->ID)
        root->left=insert(root->left,newID,newName);
    else
        root->right=insert(root->right,newID,newName);


    //right heavy
    if(maxHeight(root->left)- maxHeight(root->right) ==-2){
        //sub is left heavy
        if(maxHeight(root->right->left) - maxHeight(root->right->right)==1) root=rotateRightLeft(root);
        //right heavy or equal
        else root=rotateLeft(root);
    }
        //left heavy
    else if((maxHeight(root->left) - maxHeight(root->right))>=2){
        //sub is right heavy
        if(maxHeight(root->left->left) - maxHeight(root->left->right)==-1) root=rotateLeftRight(root);
        else root=rotateRight(root);
    }
    if(root!=nullptr)
    {
        root->height = 1 + std::max(root->left != nullptr ? root->left->height : 0,
                root->right != nullptr ? root->right->height : 0);
    }
    return root;
}
std::string preorder(Student* root)
{
    std::string returnStrings="";
    if(root==nullptr){
        return "";
    }
    returnStrings+=(root->name);
    returnStrings+=", ";
    returnStrings+=preorder(root->left);
    returnStrings+=preorder(root->right);
    return returnStrings;
}
std::string  inorder(Student* root)
{
    std::string returnStrings="";
    if(root==nullptr){
        return "";
    }

    returnStrings+=inorder(root->left);
    returnStrings+=(root->name);
    returnStrings+=", ";
    returnStrings+=inorder(root->right);
    return returnStrings;
}
std::string postorder(Student* root)
{
    std::string returnStrings="";
    if(root==nullptr){
        return "";
    }
    returnStrings+=postorder(root->left);
    returnStrings+=postorder(root->right);
    returnStrings+=(root->name);
    returnStrings+=", ";
    return returnStrings;
}
void Student::printPreorder(){
    std::string temp = preorder(this);
    temp.pop_back();
    temp.pop_back();
    std::cout<<temp<<std::endl;
}
void Student::printInorder(){
    std::string temp = inorder(this);
    temp.pop_back();
    temp.pop_back();
    std::cout<<temp<<std::endl;
}
void Student::printPostorder(){
    std::string temp = postorder(this);
    temp.pop_back();
    temp.pop_back();
    std::cout<<temp<<std::endl;
}


Student* rotateLeft(Student *node)
{
    Student* newParent=node->right;
    Student* newGrandchild=node->right->left;
    newParent->left=node;
    node->right=newGrandchild;

    return newParent;
}

Student* rotateRight(Student *node)
{
    Student* newParent=node->left;
    Student* newGrandchild=node->left->right;
    newParent->right=node;
    node->left=newGrandchild;

    return newParent;
}

Student* rotateLeftRight(Student *node)
{
    Student* firstRotation=rotateLeft(node->left);
    node->left=firstRotation;

    return rotateRight(node);

}
Student* rotateRightLeft(Student *node)
{
    Student* firstRotation=rotateRight(node->right);
    node->right=firstRotation;

    return rotateLeft(node);

}
void Student::searchID(int IDToSearch){
    bool printUnsuccessful=true;
    std::queue<Student*> q;
    q.push(this);
    while(!q.empty()){
        if(q.front()->left!=nullptr) q.push(q.front()->left);
        if(q.front()->right!=nullptr) q.push(q.front()->right);
        if(q.front()->ID==IDToSearch){
            std::cout<<q.front()->name<<std::endl;
            printUnsuccessful=false;
        }
        q.pop();
    }
    if(printUnsuccessful==true) std::cout<<"unsuccessful"<<std::endl;
}
void Student::searchName(std::string NameToSearch){
    bool printUnsuccessful=true;
    std::queue<Student*> q;
    q.push(this);
    while(!q.empty()){
        if(q.front()->left!=nullptr) q.push(q.front()->left);
        if(q.front()->right!=nullptr) q.push(q.front()->right);
        if(q.front()->name==NameToSearch){
            std::cout<<q.front()->ID<<std::endl;
            printUnsuccessful=false;
        }
        q.pop();
    }
    if(printUnsuccessful==true) std::cout<<"unsuccessful"<<std::endl;

}
std::string Student::removeID(int IDToRemove){
    std::queue<Student*> q;
    Student* studentToDelete=nullptr;
    q.push(this);
    while(!q.empty()){
        if(q.front()->left!=nullptr) q.push(q.front()->left);
        if(q.front()->right!=nullptr) q.push(q.front()->right);
        if(q.front()->ID==IDToRemove){
            studentToDelete=q.front();
        }
        q.pop();
    }
    if(studentToDelete==nullptr) return "unsuccessful";

    Student* studentParent=findParent(this,studentToDelete);

/*
    if(studentParent==nullptr){
        successor->left=this->left;
        successor->right=this->right;
        //need work
        //this=successor;

    }
    */

    //two children
    if(studentToDelete->right!=nullptr && studentToDelete->left!=nullptr){
        Student* successor=studentToDelete->right;
        while (successor->left!=nullptr){
            successor=successor->left;
        }

        if(studentParent->right->ID==studentToDelete->ID){
            studentToDelete->ID=successor->ID;
        }
        else if(studentParent->left==studentToDelete){
            studentToDelete->ID=successor->ID;
        }
        Student* successorParent=findParent(this,successor);
        delete successor;

    }
    //one child
    else if(studentToDelete->right!=nullptr){
        if(studentParent->right->ID==studentToDelete->ID){studentParent->right=studentToDelete->right;}
        else {studentParent->left=studentToDelete->right;}
        delete studentToDelete;
    }
    else if(studentToDelete->left!=nullptr){
        if(studentParent->right->ID==studentToDelete->ID){studentParent->right=studentToDelete->left;}
        else{studentParent->left=studentToDelete->left;}
        delete studentToDelete;
    }
    //no child
    else{
        delete studentToDelete;
        studentParent->right=nullptr;
        studentParent->left=nullptr;
    }
    return "successful";
}

void Student::printLevelCount(){std::cout<<maxHeight(this)<<std::endl;}

Student* findParent(Student* theRoot, Student* child){
    std::queue<Student*> q;
    q.push(theRoot);
    while(!q.empty()){
        if(q.front()->right!=nullptr) q.push(q.front()->right);
        if(q.front()->left!=nullptr) q.push(q.front()->left);

        if(q.front()->right!=nullptr){
            if(q.front()->right->ID==child->ID) return q.front();
        }
        if(q.front()->left!=nullptr){
            if(q.front()->left->ID==child->ID) return q.front();
        }

        q.pop();
    }
    return nullptr;
}

std::string inorderRemove(Student* root){
    //use string of number to add and then parse
}

/*
std::vector<Student*> inorderVector(Student* root)
{
    std::vector<Student*> vec;
    std::string returnStrings="";
    if(root==nullptr){
        
    }

    returnStrings+=inorder(root->left);
    returnStrings+=(root->name);
    returnStrings+=inorder(root->right);
    return returnStrings;
}
*/

int maxHeight(Student* root){
    if(root==nullptr) return 0;
    return 1+(std::max(maxHeight(root->left),maxHeight(root->right)));
}

bool IDExist(Student* root, int IDToSearch){
    std::queue<Student*> q;
    q.push(root);
    while(!q.empty()){
        if(q.front()->left!=nullptr) q.push(q.front()->left);
        if(q.front()->right!=nullptr) q.push(q.front()->right);
        if(q.front()->ID==IDToSearch){
            return true;
        }
        q.pop();
    }
    return false;
}