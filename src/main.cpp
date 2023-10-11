#include <iostream>
#include <string>
#include <cstdlib>
#include <sstream>
#include <vector>
#include "student.h"
#include <cctype>
#include <algorithm>

/* Note:
	1. You will have to comment main() when unit testing your code because catch uses its own main().
	2. You will submit this main.cpp file and any header files you have on Gradescope.
*/


int main(){
    Student* theRoot=insert(nullptr,111191111,"placeHolder");
    /*theRoot=insert(theRoot,22222222,"2");
    theRoot=insert(theRoot,33333333,"3");
    theRoot=insert(theRoot,55555555,"5");
     */

    std::vector<std::string> storage;
    int numberOfLines;
    std::cin>>numberOfLines;
    numberOfLines++;
    while(numberOfLines--)
    {
        std::string temp="";
        std::string line;
        std::getline(std::cin, line);
        if(line=="") continue;

        std::stringstream ss(line);
        while (getline(ss, line, ' ')){
            storage.push_back(line);
        }

        if(storage[0]=="insert"){
            bool printSuccessful=true;
            for(int i=1;i<storage[1].size()-1;i++){
                temp+=storage[1][i];
                if(!isalpha(storage[1][i])){
                    std::cout<<"unsuccessful"<<std::endl;
                    printSuccessful=false;
                }
            }

             if(storage.size()>3){
                int stringSize=storage.size()-2;
                std::string combineString;
                for(int i=1;i<stringSize+1;i++){
                    combineString+=storage[i];
                    combineString+=" ";
                }
                combineString.pop_back();
                storage[1]= combineString;
                storage[2]= storage[storage.size()-1];
             }

            if(storage[2].size()<8){
                std::cout<<"unsuccessful"<<std::endl;
            }
            else if(IDExist(theRoot,stoi(storage[2]))){
                std::cout<<"unsuccessful"<<std::endl;
            }
            else{
                theRoot=insert(theRoot,stoi(storage[2]),temp);
                if(printSuccessful){
                    std::cout<<"successful"<<std::endl;
                }
            }

        }
        else if(line=="remove"){

        }
        else if(storage[0]=="search"){
            for(int i=1;i<storage[1].size()-1;i++){
                temp+=storage[1][i];
            }
            if(isdigit(storage[1][0])) theRoot->searchID(stoi(storage[1]));
            else theRoot->searchName(temp);
        }
        else if(line=="printPreorder"){
            theRoot->printPreorder();
        }
        else if (line=="printInorder"){
            theRoot->printInorder();
        }
        else if (line=="printPostorder"){
            theRoot->printPostorder();
        }
        else if (line=="printLevelCount"){
            theRoot->printLevelCount();
        }
        else if (line=="removeInorder"){
            //
        }
        else std::cout<<"unsuccessful";
        storage.clear();
    }


    //std::cout<<theRoot->searchName("jakson");
    //theRoot->printLevelCount();



    return 0;
}

