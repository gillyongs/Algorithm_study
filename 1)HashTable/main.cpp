#include <iostream>
#include <string>
using namespace std;

class Node {
private:
    string key;
    int value;
    Node* leftNode;
    Node* rightNode;
    //���� �˻� Ʈ��
public:
    Node() : key("a"), value(0), leftNode(NULL), rightNode(NULL) {}
    //z>a>Z>A, ���ڿ��� �߰��� "a"�� ����Ʈ�� ���,
    //�� ���� ū ���� ���� ������ ���� Ʈ���� ���̸� ����
    Node(string _key, int _value) {
        key = _key;
        value = _value;
        leftNode = NULL;
        rightNode = NULL;
    }
    Node* getLeft() { return leftNode; }
    Node* getRight() { return rightNode; }
    void setLeft(Node* next) { leftNode = next; }
    void setRight(Node* next) { rightNode = next; }
    string getKey() { return key; }
    int getValue() { return value; }
    void setValue(int new_value) { value = new_value; }
    void setKey(string new_key) { key = new_key; }
    void printKV(Node* cur) { cout << "( " << cur->getKey() << ", " << cur->getValue() << " )"; }
};

class HashTable {
private:
    int size;
    Node* nodeList;
    int hashFunction(string s) {
        int len = s.length();
        int hash = 0;
        for (int i = 0; i < len; i++) {
            hash += s[i]*17*(i+1);
        }
        hash = 1;
        return hash % size;
        //digit folding
        //key�� ª�Ƶ� ū ���� ���ü� �ְ� ���� �� ����
    }
public:
    HashTable(int _size) {
        size = _size;
        nodeList = new Node[_size];
    }
    void put(string key, int value) {
        int index = hashFunction(key);
        Node* next;
        Node* cur = &nodeList[index];
        cur->printKV(cur);
        while(1){
        if (key > cur->getKey())
            next = cur->getRight();
        else
            next = cur->getLeft();
        //input key ���� ���� key ������ ũ�� ����������, ������ ��������
        if (next == NULL) {
            break;
        }
        //NULL = leaf ������ �ݺ�
        cur = next;
        cout << " -> ";
        cur->printKV(next);
        }
        //Ž�� ����

        Node* newNode = new Node(key, value);
        cout << " -> ";
        if (key > cur->getKey()) {
            cur->setRight(newNode);
            cur->printKV(cur->getRight());
        }
        else {
            cur->setLeft(newNode);
            cur->printKV(cur->getLeft());
        }
        printf("\n");
        //���� ����
    }
    void get(string key) {
        int index = hashFunction(key);
        Node* next;
        Node* cur = &nodeList[index];
        while (1) {
            if (key == cur->getKey()) {
                if (cur->getValue() == 0)
                    cout << "Ű '" << key << "' ����\n";
                //Ű�� �����ϴµ� value�� 0 = ������ node
                else {
                    cout << "Ű '" << key << "' ���� ";
                    cur->printKV(cur);
                    printf("\n");
                }
                break;
            }
            else if (key > cur->getKey())
                next = cur->getRight();
            else
                next = cur->getLeft();

            if (next == NULL) {
                cout << "Ű '" << key << "' ����\n";
                break;
            }

            cur = next;
        }
    }
    void del (string key) {
        int index = hashFunction(key);
        Node* next;
        Node* cur = &nodeList[index];
        while (1) {
            if (key == cur->getKey()) {
                cur->setValue(0);
                cout << "Ű '" << key << "' ����\n";
                break;
                //value = 0, ������
                //key�� ���� node�� Ʈ���� ���̸� ���ߴµ� ���
            }
            else if (key > cur->getKey())
                next = cur->getRight();
            else
                next = cur->getLeft();

            if (next == NULL) {
                cout << "Ű '" << key << "' ����\n";
                break;
            }

            cur = next;
        }
    }
    void del2(string key) {
        int index = hashFunction(key);
        Node* next;
        Node* cur = &nodeList[index];
        Node* parent = cur; //cur�� �θ� ���
        
        while (1) {
            if (key == cur->getKey()) {
                cout << "Ű '" << key << "' ����\n";

                if(cur->getRight() != NULL && cur->getLeft() != NULL) {
                    //�����Ϸ��� node�� �ڽ� ��尡 2���� ���
                    Node* Rmin = cur->getRight();
                    Node* temp = cur; // Rmin�� �θ� ��� 
                    while (Rmin->getLeft() != NULL) {
                        temp = Rmin;
                        Rmin = Rmin->getLeft();
                    }
                    cur->setValue(Rmin->getValue());
                    cur->setKey(Rmin->getKey());
                    //node�� key�� value�� Rmin�� ������ ����, Rmin�� ����

                    if (cur->getRight() == Rmin) {
                        cur->setRight(Rmin->getRight());
                    }
                    else {
                        temp->setLeft(Rmin->getRight());
                    }
                    delete Rmin;
                    //Rmin�� �θ� ����� ���ʿ� ����
                    //Rmin�� �θ��� left node�� Rmin�� rightNode�� ����
                    //��, �����Ϸ��� ����� �ٷ� ������ ��尡 Rmin�� ��쿣 Rmin�� �����ʿ� ����
                }

                else if (cur->getLeft() != NULL && cur->getRight() == NULL) {
                    //�����Ϸ��� node�� leftnode�� �����ϴ� ���
                    if (parent->getKey() > cur->getKey())
                        parent->setLeft(cur->getLeft());
                    else
                        parent->setRight(cur->getLeft());
                    delete cur;
                    //�θ� ���� left node�� ����, ��� ����
                }
                else if (cur->getLeft() == NULL) {
                    //�����Ϸ��� node�� rightnode�� �����ϴ� ���
                    if (parent->getKey() > cur->getKey())
                        parent->setLeft(cur->getRight());
                    else
                        parent->setRight(cur->getRight());
                    delete cur;
                }
                else if (cur->getRight() == NULL) {
                    //�����Ϸ��� node�� leftnode�� �����ϴ� ���
                    if (parent->getKey() > cur->getKey())
                        parent->setLeft(cur->getLeft());
                    else
                        parent->setRight(cur->getLeft());
                    delete cur;
                }
                else {
                    //�����Ϸ��� node�� leaf ����� ���
                    if (parent->getKey() > cur->getKey())
                        parent->setLeft(NULL);
                    else
                        parent->setRight(NULL);
                    delete cur;
                    //�θ� ����� �����͸� NULL�� �����ϰ� ����
                }
                break;
            }
            else if (key > cur->getKey())
                next = cur->getRight();
            else
                next = cur->getLeft();

            if (next == NULL) {
                cout << "Ű '" << key << "' ����\n";
                break;
            }
            else {
                parent = cur;
                cur = next;
            }
        }
    }

};

int main(void)
{
    HashTable hashTable = HashTable(2000);
    hashTable.put("v", 9);
    hashTable.put("z", 7);
    hashTable.put("c", 13);
    hashTable.put("T", 15);
    hashTable.put("C", 22);
    hashTable.put("Y", 14);
    hashTable.put("Z", 20);
    hashTable.put("U", 20);
    hashTable.put("V", 20);
    hashTable.put("W", 20);
    printf("\n");
    hashTable.get("v");
    hashTable.get("z");
    hashTable.get("x");
    printf("\n");
    hashTable.del2("k");
    hashTable.del2("v");
    hashTable.get("v");
    hashTable.put("v", 17);
    hashTable.del2("T");
    hashTable.put("X", 17);
    hashTable.put("A", 20);
    return 0;
}