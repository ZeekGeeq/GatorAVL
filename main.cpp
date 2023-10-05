#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <sstream>
#include <iomanip>

using namespace std;


struct StudentNode{
    StudentNode* left;
    StudentNode* right;
    //======useless====
    string NAME;
    //=================
    int ID;
    StudentNode(int key, string Name){

        this->ID = key;
        this->NAME = Name;
        this->left = nullptr;
        this->right = nullptr;
    }
    StudentNode(int key, StudentNode* left, StudentNode* right){
        this->ID = key;
        this->left = left;
        this->right = right;
    }
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
int getMaxNode(StudentNode* Root){
    auto temp = Root;
    while(temp->right != nullptr){
        temp = temp->right;
    }
    return temp->ID;
}
StudentNode* getMinNode(StudentNode* Root){
    auto temp = Root;
    while(temp->left != nullptr){
        temp = temp->left;
    }
    return temp;
}
void InorderTraversal(StudentNode*Root){
    //DFS use a stack data strucutre
    //this means that this can be done with
    //recursion but im a little tired of thinking about recursion
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
            cout<<temp->ID<<", ";
        }
        else{
            cout<<temp->ID<<endl;
        }
        temp = temp->right;
    }

}
//this traversal may be easier to implement recursively
//But i want to seperate it by commas and do so without a vector or array
//and without using 2 functions
void PreorderTraversal(StudentNode* Root){
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
            cout<<temp->ID<<", ";
        }
        else if (temp->ID == max && temp->right == nullptr && temp->left != nullptr){
            cout<<temp->ID<<", "<<temp->left->ID<<endl;
            return;
        }
        else if (temp->ID == max && temp ->left == nullptr && temp ->right == nullptr){
            cout<<temp->ID<<endl;
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

void PostOrderRecurs(StudentNode* Root, int head){
    if(Root == nullptr){
        return;
    }
    PostOrderRecurs(Root->left, head);
    PostOrderRecurs(Root->right, head);
    if(Root->ID == head){
        cout<<Root->ID<<endl;
    }
    else{
        cout<<Root->ID<<", ";
    }
}

void PostOrderTraversal(StudentNode* Root){
    PostOrderRecurs(Root,Root->ID);
}

StudentNode* FindID(StudentNode* Root, int ID){
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
    if(temp == nullptr){
        return nullptr;
    }
    return temp;
}

StudentNode* FindPrev(StudentNode* Root, int key){
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

StudentNode* RemoveID(StudentNode* Root, int key) {
    auto nodeR = FindID(Root, key);
    if(nodeR == nullptr){
        return nullptr;
    }
    bool is_Left_Child;
    auto nodeR_Parent = FindPrev(Root, key);
    if(nodeR_Parent->ID < key){
        is_Left_Child = false;
    }
    else{
        is_Left_Child = true;
    }
    if(nodeR->right == nullptr && nodeR->left == nullptr){
        if(is_Left_Child){
            FindPrev(Root,key)->left= nullptr;
        }
        else{
            FindPrev(Root,key)->right = nullptr;
        }
        delete nodeR;
        return Root;
    }
        //1 nino
    else if(nodeR->right== nullptr && nodeR->left!= nullptr){
        if(is_Left_Child){
            nodeR_Parent->left = nodeR->left;
        }
        else{
            nodeR_Parent->right = nodeR->left;
        }
        delete nodeR;
        return Root;
    }
    else if(nodeR->right != nullptr && nodeR ->left == nullptr){
        if(is_Left_Child){
            nodeR_Parent->left = nodeR->right;
        }
        else{
            nodeR_Parent->right = nodeR->right;
        }
        delete nodeR;
        return Root;
    }
    else{
        //2 children
        auto successor=getMinNode(nodeR->right);
        nodeR->ID = successor->ID;
        nodeR->NAME = successor->NAME;
        nodeR->right = RemoveID(nodeR->right, nodeR->ID);
        return Root;
    }
    //implement other cases later
    return Root;
}

class AVL{
private:
    StudentNode* headRoot;
public:
    AVL(){}
    int num_nodes=0;
    StudentNode* Insert(StudentNode* Root, string name,int key){
        StudentNode* peer;
        if (Root == nullptr){
            peer = new StudentNode(key, name);
            peer ->right= nullptr;
            peer ->left = nullptr;
            num_nodes++;
            return peer;
        }
        if(key == Root->ID){
            return Root;
        }
        else if(key < Root->ID){
            Root->left = Insert(Root->left,name,key);
        }
        else if(key > Root->ID){
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
    StudentNode* removeInorder(StudentNode* Root, int Nth){
        //we will first go over with an inorder traversal and add a counter to stop at the nth index
        if(Root == nullptr||Nth < 0){
            cout<<"unsuccessful"<<endl;
        }
        int counter=0;
        auto temp = Root;
        if(Nth > num_nodes){
            cout<<"unsuccessful"<<endl;
            return nullptr;
        }
        stack<StudentNode*> stackity_stack;
        while(temp != nullptr || stackity_stack.empty() == false){
            while(temp != nullptr){
                stackity_stack.push(temp);
                temp = temp->left;
            }
            if(counter == Nth){
                cout<<"successful"<<endl;
                RemoveID(Root,stackity_stack.top()->ID);
                return Root;
            }
            counter++;
            temp = stackity_stack.top();
            stackity_stack.pop();
            temp = temp->right;
        }
    }


};
//===============================Helper Functions===================================
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
        strings_sep.push_back(removeQuotes(currentPart));
    }
    return strings_sep;
}
//=================================================================================
void ExecuteCommand(string command, AVL &avl, StudentNode* &Root){
    vector<string>commands_names_IDs = splitString(command);
    for(int i =0; i < commands_names_IDs.size();i++){
        cout<<commands_names_IDs[i]<<endl;
    }
}
int main() {
    //start accepting commands
    AVL avl;
    StudentNode* Root = nullptr;
    Root = avl.Insert(Root,"terry",3);
    Root = avl.Insert(Root,"vicky",60);
    Root = avl.Insert(Root, "momma",2);
    Root = avl.Insert(Root,"jordan",70);

    Root = avl.Insert(Root,"killme",-5);
    Root = avl.Insert(Root,"i cant think of names",40);
    Root = avl.Insert(Root,"Hunting",0);
    Root = avl.Insert(Root,"Dirty",21);

    Root = avl.Insert(Root,"Ladybugs",64);
    Root = avl.Insert(Root,"i love",1);
    Root = avl.Insert(Root,"butter",-9);
    Root = avl.Insert(Root,"from plants",-50);

    Root = avl.Insert(Root,"timmy",-100);
    Root = avl.Insert(Root,"timmy",56);
    Root = avl.Insert(Root,"kyle",-100);
    Root = avl.Insert(Root,"stan",-700);

    cout<<avl.num_nodes<<endl;
    InorderTraversal(Root);
    avl.removeInorder(Root,0);

    InorderTraversal(Root);

//    cout<<getBF(Root)<<endl;
//    InorderTraversal(Root);
//    PreorderTraversal(Root);
//    PostOrderTraversal(Root);
//    cout<<FindPrev(Root,-900)->ID<<endl;
//    Root = RemoveID(Root,3);
//    Root = RemoveID(Root,0);
//    InorderTraversal(Root);
    int command_cnt;
    cin>>command_cnt;
    vector<string>instructions;
    string instruction;
    getline(cin,instruction);
    for(int i = 0; i< command_cnt; i++){
        getline(cin,instruction);
        instructions.push_back(instruction);
    }
    ExecuteCommand(instructions[0],avl,Root);
//    AVL gator_avl;
//    StudentNode* Root = nullptr;

    return 0;
}
