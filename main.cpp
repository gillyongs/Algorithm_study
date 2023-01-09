#include <iostream>
#include <string>
using namespace std;

class Node {
private:
    string key;
    int value;
    Node* leftNode;
    Node* rightNode;
    //이진 검색 트리
public:
    Node() : key("a"), value(0), leftNode(NULL), rightNode(NULL) {}
    //z>a>Z>A, 문자열의 중간값 "a"를 디폴트로 사용,
    //이 보다 큰 값과 작은 값으로 나눠 트리의 높이를 낮춤
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
        //key가 짧아도 큰 값이 나올수 있게 값을 더 곱함
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
        //input key 값이 현재 key 값보다 크면 오른쪽으로, 작으면 왼쪽으로
        if (next == NULL) {
            break;
        }
        //NULL = leaf 노드까지 반복
        cur = next;
        cout << " -> ";
        cur->printKV(next);
        }
        //탐색 과정

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
        //삽입 과정
    }
    void get(string key) {
        int index = hashFunction(key);
        Node* next;
        Node* cur = &nodeList[index];
        while (1) {
            if (key == cur->getKey()) {
                if (cur->getValue() == 0)
                    cout << "키 '" << key << "' 없음\n";
                //키가 존재하는데 value가 0 = 삭제된 node
                else {
                    cout << "키 '" << key << "' 있음 ";
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
                cout << "키 '" << key << "' 없음\n";
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
                cout << "키 '" << key << "' 삭제\n";
                break;
                //value = 0, 삭제됨
                //key만 남은 node는 트리의 높이를 낮추는데 사용
            }
            else if (key > cur->getKey())
                next = cur->getRight();
            else
                next = cur->getLeft();

            if (next == NULL) {
                cout << "키 '" << key << "' 없음\n";
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