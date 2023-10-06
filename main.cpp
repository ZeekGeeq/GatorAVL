#include <iostream>
#include<string>
#include <stack>
#include <vector>
#include<regex>
#include <bits/stdc++.h>
#include <sstream>
#include <iomanip>

using namespace std;
struct StudentNode{
    StudentNode* left;
    StudentNode* right;
    //======useless====
    string NAME;
    string exact_key;
    //=================
    int ID;
    StudentNode(string key, string Name){
        this->exact_key = key;
        this->ID = stoi(key);
        this->NAME = Name;
        this->left = nullptr;
        this->right = nullptr;
    }
    StudentNode(string key, StudentNode* left, StudentNode* right){
        this->exact_key = key;
        this->ID = stoi(key);
        this->left = left;
        this->right = right;
    }
};
class AVL{
    int num_nodes;
    StudentNode* head_root;
public:
    AVL(){
        num_nodes = 0;
        //The node counter's only purpose is for
        //the Inorder delete
        head_root= nullptr;}
    StudentNode* getRoot(){
        return head_root;
    }
    int getNodeCount(){
        return num_nodes;
    }
    StudentNode* set_root(StudentNode* new_root){
        head_root = new_root;
    }
    StudentNode* rotateLeft(StudentNode* padre){
        StudentNode *nino = padre->right;
        StudentNode *ninito = nino->left;
        nino->left = padre;
        padre->right = ninito;
        return nino;
    };
    StudentNode* rotateRight(StudentNode* padre){
        StudentNode *nino = padre->left;
        StudentNode *ninito = nino->right;
        nino->right = padre;
        padre->left = ninito;
        return nino;
    };

    int getHeight(StudentNode* Root){
        if(Root == nullptr){
            return 0;
        }
        else{
            return max(getHeight(Root->left), getHeight(Root->right))+1;
        }
    };
    int getBF(StudentNode* Node){
        //will return balance factor of any root
        //sign does not matter
        return (getHeight(Node->left)- getHeight(Node->right));
    }
    StudentNode* getMinNode(StudentNode* Root){
        auto temp = Root;
        while(temp->left != nullptr){
            temp = temp->left;
        }
        return temp;
    }

    StudentNode* rotateRightLeft(StudentNode* hippo){
        //R
        hippo->right = rotateRight(hippo->right);
        //L
        return rotateLeft(hippo);
    };
    StudentNode* rotateLeftRight(StudentNode* rhino){
        //L
        rhino->left = rotateLeft(rhino->left);
        //R
        return rotateRight(rhino);
    };

    StudentNode* Insert(StudentNode* Root, string name,string key){
        int key_int = stoi(key);
        StudentNode* peer;

        if (Root == nullptr){
            peer = new StudentNode(key, name);
            peer ->right= nullptr;
            peer ->left = nullptr;
            this->num_nodes++;
            return peer;
        }
        if(key_int == Root->ID){
            return Root;
        }
        else if(key_int < Root->ID){
            Root->left = Insert(Root->left,name,key);
        }
        else if(key_int > Root->ID){
            Root->right = Insert(Root->right,name,key);
        }
        //return Root;
        //Tried implementing secondary balancing function, its hard.. :('
        int balFact = getBF(Root);

        if(balFact == 0 || balFact ==1){return Root;}
        if(balFact == -2){//suggests rightside imbalance
            int bFR= getBF(Root->right);
            if(bFR == -1){
                return rotateLeft(Root);
            }
            else{
                return rotateRightLeft(Root);
            }
        }
        if(balFact == 2){//suggests leftside imbalance
            int bFL = getBF(Root->left);
            if(bFL == 1){
                return rotateRight(Root);
            }
            else{
                return rotateLeftRight(Root);
            }
        }
        return Root;
    }
    int getMaxNode(StudentNode* Root){
        auto temp = Root;
        while(temp->right != nullptr){
            temp = temp->right;
        }
        return temp->ID;
    }

    void PreorderTraversal(){
        auto Root = getRoot();
        if(Root == nullptr){
            return;
        }
        int max = getMaxNode(Root);

        stack<StudentNode*> nodes;
        StudentNode* temp;
        nodes.push(Root);
        while(!nodes.empty()){
            temp = nodes.top();
            if (temp->ID != max){
                cout<<temp->NAME<<", ";
            }
            else if (temp->ID == max && temp->right == nullptr && temp->left != nullptr){
                cout<<temp->NAME<<", "<<temp->left->NAME<<endl;
                return;
            }
            else if (temp->ID == max && temp ->left == nullptr && temp ->right == nullptr){
                cout<<temp->NAME<<endl;
                return;
            }
            nodes.pop();
            if(temp->right!= nullptr){
                nodes.push(temp->right);
            }
            if(temp->left!= nullptr){
                nodes.push(temp->left);
            }
        }
    }

    void InorderTraversal(){
        //DFS use a stack data strucutre
        //this means that this can be done with
        //recursion but im a little tired of thinking about recursion
        auto Root = getRoot();
        auto temp = Root;
        int max_value = getMaxNode(Root);
        stack<StudentNode*> stackity_stack;
        while(temp != nullptr || stackity_stack.empty() == false){
            while(temp != nullptr){
                stackity_stack.push(temp);
                temp = temp->left;
            }
            temp = stackity_stack.top();
            stackity_stack.pop();
            if(temp->ID != max_value){
                cout<<temp->NAME<<", ";
            }
            else{
                cout<<temp->NAME<<endl;
            }
            temp = temp->right;
        }

    }

    void PostOrderRecurs(StudentNode* Root, int head){
        if(Root == nullptr){
            return;
        }
        PostOrderRecurs(Root->left, head);
        PostOrderRecurs(Root->right, head);
        if(Root->ID == head){
            cout<<Root->NAME<<endl;
        }
        else{
            cout<<Root->NAME<<", ";
        }
    }
    void PostOrderTraversal(){
        auto Root = getRoot();
        PostOrderRecurs(Root,Root->ID);
    }

    StudentNode* FindID(StudentNode* Root, string exact_ID){
        regex place("[0-9]+");
        if(!regex_match(exact_ID,place)){
            return nullptr;
        }

        int ID = stoi(exact_ID);
        auto temp = Root;
        while(temp->ID != ID){
            if (ID < temp->ID){
                temp = temp->left;
            }
            else if(ID > temp->ID){
                temp = temp->right;
            }
            if(temp == nullptr){
                return nullptr;
            }
        }
        return temp;
    }

    StudentNode* FindPrev(StudentNode* Root, string exact_key){
        int key = stoi(exact_key);
        auto temp0 = Root;
        bool zeh_bool = true;
        if (temp0->ID == key){
            return temp0;
            //single node tree
        }
        while(zeh_bool){
            if(temp0->right != nullptr){
                if (temp0->right->ID==key){
                    zeh_bool = false;
                }
            }
            if(temp0->left!= nullptr){
                if(temp0->left->ID == key){
                    zeh_bool = false;
                }
            }
            if(zeh_bool){
                if(key < temp0->ID){
                    temp0 = temp0->left;
                }
                else{
                    temp0 = temp0->right;
                }
            }
        }
        return temp0;
    };
    vector<StudentNode*> FindNAME(StudentNode* Root, string name) {
        //used inorder traversal to iterate through list with some modifications
        vector<StudentNode*> nodes_nameFound;
        auto temp = Root;
        stack<StudentNode*> stackity_stack;
        stackity_stack.push(Root);
        while(!stackity_stack.empty()){
            temp = stackity_stack.top();
            if(name.compare(temp->NAME)==0){
                nodes_nameFound.push_back(temp);
            }
            stackity_stack.pop();
            if(temp->right!= nullptr){
                stackity_stack.push(temp->right);
            }
            if(temp->left!= nullptr){
                stackity_stack.push(temp->left);
            }
        }
        return nodes_nameFound;
    }
    StudentNode* removeID(StudentNode* root, string exact_key)
    {
        if (root == nullptr){
            return nullptr;
        }
        int ID = stoi(exact_key);
        if (ID > root->ID)
            root->right = removeID(root->right, exact_key);
        else if (ID < root->ID)
            root->left = removeID(root->left, exact_key);
        else {
            if (root->left == nullptr && root->right == nullptr){
                delete root;
                num_nodes--;
                root = nullptr;
                return root;
            }
            else if(root->right == nullptr){
                StudentNode* temp = root;
                root = root->left;
                num_nodes--;
                delete temp;
                return root;
            }
            else if(root->left == nullptr){
                StudentNode* temp = root;
                root = root->right;
                num_nodes--;
                delete temp;
                return root;
            }
            else{
                StudentNode* temp = getMinNode(root->right);
                root->ID = temp->ID;
                root->NAME = temp->NAME;
                root->exact_key = temp->exact_key;
                root->right = removeID(root->right, root->exact_key);
                return root;
            }
        }
        return root;
    }
    StudentNode* removeInorder(StudentNode* Root, int Nth){
        //we will first go over with an inorder traversal and add a counter to stop at the nth index
        if(Root == nullptr||Nth < 0){
            cout<<"unsuccessful"<<endl;
        }
        if((0>=Nth || Nth >= getNodeCount())){
            cout<<"unsuccessful"<<endl;
            return Root;
        }
        int counter=0;
        auto temp = Root;
        stack<StudentNode*> stackity_stack;
        while(temp != nullptr || stackity_stack.empty() == false){
            while(temp != nullptr){
                stackity_stack.push(temp);
                temp = temp->left;
            }
            if(counter == Nth){
                cout<<"successful"<<endl;
                removeID(Root,stackity_stack.top()->exact_key);
                return Root;
            }
            counter++;
            temp = stackity_stack.top();
            stackity_stack.pop();
            temp = temp->right;
        }
    }

};

void unsuccess(){
    cout<<"unsuccessful"<<endl;
}
void success(){
    cout<<"successful"<<endl;
}




bool validate_name(string name){
    regex place("[a-zA-Z\\s\"]+");
    return regex_match(name,place);
}
bool validate_number(string num){
    regex place("[0-9]+");
    return (regex_match(num, place)&&num.length()==8);
}
bool Validate_input(vector<string> input){
    if(input.size()==0){return false;}
    if(input[0].compare("insert")==0){
        if(input.size() != 3 || !validate_name(input[1]) || !validate_number(input[2])){
            return false;
        }
        else{
            return true;
        }
    }
    else if(input[0].compare("remove")==0){
        if(input.size() != 2 || !validate_number(input[1])){
            return false;
        }
        else{
            return true;
        }
    }
    else if(input[0].compare("search")==0){}
    else if(input[0].compare("printInorder")==0){
        if(input.size()!=1){return false;}
        else{return true;}
    }
    else if(input[0].compare("printPreorder")==0){
        if(input.size()!=1){return false;}
        else{return true;}
    }
    else if(input[0].compare("printPostorder")==0){
        if(input.size()!=1){return false;}
        else{return true;}
    }
    else if(input[0].compare("printLevelCount")==0){}
    return false;

}
string removeQuotes(string& input) {
    if (input.size() >= 2 && input.front() == '"' && input.back() == '"') {
        return input.substr(1, input.size() - 2);
    } else {
        return input;
    }
}
vector<string> splitString(string& input) {
    vector<std::string> strings_sep;
    string currentPart;
    istringstream iss(input);
    //bless the sstream library
    while (iss >> quoted(currentPart)) {
        strings_sep.push_back(currentPart);
    }
    return strings_sep;
}
//=================================================================================
void ExecuteCommand(string command, AVL &avl) {
    auto Root = avl.getRoot();
    vector<string> commands_names_IDs = splitString(command);
    if(!Validate_input(commands_names_IDs)){
        unsuccess();
        return;
    }
    if(commands_names_IDs[0].compare("insert")==0){
        if(count(command.begin(),command.end(),'\"')!=2){
            unsuccess();
            return;
        }
        if(avl.getRoot() == nullptr){
            StudentNode* Node = avl.Insert(avl.getRoot(),commands_names_IDs[1],commands_names_IDs[2]);
            avl.set_root(Node);
            success();
            return;
        }
        else if(avl.FindID(avl.getRoot(),commands_names_IDs[2])== nullptr){
            StudentNode* Node = avl.Insert(avl.getRoot(),commands_names_IDs[1],commands_names_IDs[2]);
            avl.set_root(Node);
            success();
            return;
        }
        else{
            unsuccess();
            return;
        }
    }
    else if(commands_names_IDs[0].compare("remove")==0){
        if(avl.FindID(avl.getRoot(),commands_names_IDs[1])== nullptr){
            unsuccess();
            return;
        }
        StudentNode* Node = avl.removeID(avl.getRoot(),commands_names_IDs[1]);
        avl.set_root(Node);
        success();
        return;
    }
    else if(commands_names_IDs[0].compare("printPreorder")==0){
        avl.PreorderTraversal();
        return;
    }
    else if(commands_names_IDs[0].compare("printInorder")==0){
        avl.InorderTraversal();
        return;
    }
    else if(commands_names_IDs[0].compare("printPostorder")==0){
        avl.PostOrderTraversal();
        return;
    }
}





int main() {
    AVL avl;

    int command_cnt;
    cin>>command_cnt;
    vector<string>instructions;
    string instruction;
    getline(cin,instruction);
    for(int i = 0; i< command_cnt; i++){
        getline(cin,instruction);
        instructions.push_back(instruction);
    }
    for(int c = 0;c<command_cnt;c++){
        ExecuteCommand(instructions[c],avl);
    }
    return 0;
}
