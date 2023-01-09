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

};

int main(void)
{
    HashTable hashTable = HashTable(2000);
    hashTable.put("v", 9);
    hashTable.put("z", 7);
    hashTable.put("c", 13);
    hashTable.put("V", 15);
    hashTable.put("Z", 20);
    hashTable.put("C", 22);
    printf("\n");
    hashTable.get("v");
    hashTable.get("z");
    hashTable.get("x");
    printf("\n");
    hashTable.del("k");
    hashTable.del("c");
    hashTable.get("c");
    return 0;
}