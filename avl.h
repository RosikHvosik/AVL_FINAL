#include <string>
#include <iostream>
#include <algorithm>
#include <fstream>
#include <queue>
#include "key.h"
#include "list.h"
#include "Parsing.h"

struct TreeNode {
	FIO key;
	int bal;
    TreeNode* left;
    TreeNode* right;
	List lines;

		 TreeNode(const FIO& fio, int count, int bal, TreeNode* left, TreeNode* right, int line) : key(fio), bal(0), left(nullptr), right(nullptr){
			lines.appendToBegin(line);
		 }
};

class AVL_tree{
	public:
	TreeNode* root;
	AVL_tree() : root(nullptr){}

	~AVL_tree(){
		clear(root);
		std::cout<<"\nДерево уничтожено";
	}
	

	void clear(TreeNode* node) {
    if (node) {
      clear(node->left);
      clear(node->right);
      delete node;
    }
  }
    void readFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (!inFile) {
        std::cerr << "Ошибка открытия файла: " << filename << std::endl;
        return;
    }

    std::string line;
    int lineNumber = 0;
    bool heightIncreased = false;

    while (std::getline(inFile, line)) {
        lineNumber++;
        try {
            auto [surname, name, patronymic] = parseFullName(line);
            FIO fio(surname, name, patronymic);
            insert(fio, root, heightIncreased, lineNumber);
        } catch (const std::exception& e) {
            std::cerr << "Ошибка в строке " << lineNumber << ": " << e.what() << std::endl;
        }
    }

    inFile.close();
}



	void insert(FIO fio, TreeNode*& p, bool& h, int line) {
    TreeNode* p1;
    TreeNode* p2;

    if (p == nullptr) {
        p = new TreeNode(fio, 1, 0, nullptr, nullptr, line);
        h = true;
    } else if (p->key > fio) {
        insert(fio, p->left, h, line);

        if (h) {
            if (p->bal == 1) {
                p->bal = 0;
                h = false;
            } else if (p->bal == 0) {
                p->bal = -1;
            } else {
                p1 = p->left;

                if (p1->bal == -1) {
                    // Right rotation
                    std::cout << "Right rotation\n";
                    p->left = p1->right;
                    p1->right = p;
                    p->bal = 0;
                    p = p1;
                } else {
                    // Left-right rotation
                    std::cout << "Left-right rotation\n";
                    p2 = p1->right;
                    p1->right = p2->left;
                    p2->left = p1;
                    p->left = p2->right;
                    p2->right = p;

                    if (p2->bal == -1) {
                        p->bal = 1;
                    } else {
                        p->bal = 0;
                    }

                    if (p2->bal == 1) {
                        p1->bal = -1;
                    } else {
                        p1->bal = 0;
                    }
                    p = p2;
                }
                p->bal = 0;
                h = false;
            }
        }
    } else if (p->key < fio) {
        insert(fio, p->right, h, line);

        if (h) {
            if (p->bal == -1) {
                p->bal = 0;
                h = false;
            } else if (p->bal == 0) {
                p->bal = 1;
            } else {
                p1 = p->right;

                if (p1->bal == 1) {
                    // Left rotation
                    std::cout << "Left rotation\n";
                    p->right = p1->left;
                    p1->left = p;
                    p->bal = 0;
                    p = p1;
                } else {
                    // Right-left rotation
                    std::cout << "Right-left rotation\n";
                    p2 = p1->left;
                    p1->left = p2->right;
                    p2->right = p1;
                    p->right = p2->left;
                    p2->left = p;

                    if (p2->bal == 1) {
                        p->bal = -1;
                    } else {
                        p->bal = 0;
                    }

                    if (p2->bal == -1) {
                        p1->bal = 1;
                    } else {
                        p1->bal = 0;
                    }
                    p = p2;
                }
                p->bal = 0;
                h = false;
            }
        }
    } else {

        p->lines.appendToBegin(line);
        std::cout << "Добавлена строка " << line << " в узел с ключом: " << p->key.surname << std::endl;
        h = false;
    }
}
	void balanceL(TreeNode*& p, bool& h) {
    TreeNode* p1;
    TreeNode* p2;

    if (p->bal == -1) {
        p->bal = 0;
    } else if (p->bal == 0) {
        p->bal = 1;
        h = false;
    } else { 
        p1 = p->right;

        if (p1->bal >= 0) { 
            p->right = p1->left;
            p1->left = p;
            
            if (p1->bal == 0) {
                p->bal = 1;
                p1->bal = -1;
                h = false;
            } else {
                p->bal = 0;
                p1->bal = 0;
            }
            p = p1;
        } else { 
            p2 = p1->left;



            p1->left = p2->right;
            p2->right = p1;
            p->right = p2->left;
            p2->left = p;
            

            if (p2->bal == 1) {
                p->bal = -1;
            } else {
                p->bal = 0;
            }

            if (p2->bal == -1) {
                p1->bal = 1;
            } else {
                p1->bal = 0;
            }

            p = p2;
            p2->bal = 0;
        }
    }
}




void balanceR(TreeNode*& p, bool& h) {
    TreeNode* p1;
    TreeNode* p2;

    if (p->bal == 1) {
        p->bal = 0;
    } else if (p->bal == 0) {
        p->bal = -1;
        h = false;
    } else { 
        p1 = p->left;



        if (p1->bal <= 0) { 
            p->left = p1->right;
            p1->right = p;
            if (p1->bal == 0) {
                p->bal = -1;
                p1->bal = 1;
                h = false;
            } else {
                p->bal = 0;
                p1->bal = 0;
            }
            p = p1;
        } else { 
            p2 = p1->right;



            p1->right = p2->left;
            p2->left = p1;
            p->left = p2->right;
            p2->right = p;


            if (p2->bal == -1) {
                p->bal = 1;
            } else {
                p->bal = 0;
            }

            if (p2->bal == 1) {
                p1->bal = -1;
            } else {
                p1->bal = 0;
            }

            p = p2;
            p2->bal = 0;
        }
    }
}



void delete_node(FIO x, TreeNode*& p, bool& h, unsigned int rowIndex) {
    TreeNode* q;

    if (p == nullptr){
        return;
    } 
    else if(p->key > x){

        delete_node(x, p->left,h, rowIndex);

        if(h){
            balanceL(p,h);
        }
    }

    else if (p->key < x){
        delete_node(x, p->right, h, rowIndex);

        if (h) {
            balanceR(p,h);
        }
    }
    else if (std::find((p->lines).search(rowIndex).begin(), (p->lines).search(rowIndex).end(), rowIndex) != (p->lines).search(rowIndex).end()){
        q = p;

        if(q->right == nullptr){
            p = q->right;
            h = true;
        }

        else if (q->left == nullptr){
            p = q->right;
            h = true;
        }

        else{
            virtDel(q->left, h, q, rowIndex);

            if(h){
                balanceL(p,h);
            }
        }
    }
}

void virtDel(TreeNode*& r, bool& h, TreeNode*& q, unsigned int rowIndex){
    if (r->right != nullptr){
        virtDel(r->right, h, q, rowIndex);

        if(h){
            balanceR(r, h);
        }
    }

    else{
        if ((q->lines.size()) > 1){
            q->lines.deleteValue(rowIndex);
        }

        else{
            q->key = r->key;
            q->lines = r->lines;
            q = r;
            r = r->left;
            h = true;
        }
    }
}
	void inOrder(TreeNode* node) const {
    if (node) {
        inOrder(node->right);

        std::cout << node->key.surname << " " 
                  << node->key.name << " "
                  << node->key.patronymic << " встречается в строках: ";

        if (node->lines.begin != nullptr) {
            Node* temp = node->lines.begin;
            do {
                std::cout << temp->data << " ";
                temp = temp->next;
            } while (temp != node->lines.begin);
        } else {
            std::cout << "нет строк";
        }

        std::cout << std::endl;

        inOrder(node->left);
    }
}


	void inOrder(TreeNode* node, std::ofstream& outFile) const {
    if (node) {
        inOrder(node->right, outFile);

        outFile << node->key.surname << " "
                << node->key.name << " "
                << node->key.patronymic << " встречается в строках: ";


        if (node->lines.begin != nullptr) {
            Node* temp = node->lines.begin;
            do {
                outFile << temp->data << " ";
                temp = temp->next;
            } while (temp != node->lines.begin);
        } else {
            outFile << "нет строк";
        }

        outFile << std::endl;

        inOrder(node->left, outFile);
    }
}



	void printToFile(const std::string& filename) const {
    std::ofstream outFile(filename);  
    if (!outFile) {
        std::cerr << "Ошибка при открытии файла для записи!" << std::endl;
        return;
    }

    inOrder(root, outFile);
    outFile.close();  
    }

void printTree(TreeNode* node, int depth = 0) const {
    if (node != nullptr) {

        printTree(node->right, depth + 1);


        std::cout << std::string(depth * 4, ' ')
                  << node->key.surname << " "
                  << node->key.name << " "
                  << node->key.patronymic << " строки: ";


        if (node->lines.begin != nullptr) {
            Node* temp = node->lines.begin;
            do {
                std::cout << temp->data << " ";
                temp = temp->next;
            } while (temp != node->lines.begin);
        } else {
            std::cout << "нет строк";
        }

        std::cout << std::endl;


        printTree(node->left, depth + 1);
    }
}








	TreeNode* search(const FIO& fio, TreeNode* p) const {
    if (p == nullptr) {
        std::cout<<"Элемент не найден"<<endl;;
        return nullptr;
    }
    
    if (fio == p->key) {
        std::cout<<"Элемент найден"<<endl;;
        return p;
    }
    else if (fio < p->key) {
        return search(fio, p->left);
    }
    else {
        return search(fio, p->right);
    }
	}
	TreeNode* findroot(){
		return this->root;
	}
}; 