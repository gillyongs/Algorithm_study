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
    void del2(string key) {
        int index = hashFunction(key);
        Node* next;
        Node* cur = &nodeList[index];
        Node* parent = cur; //cur의 부모 노드
        
        while (1) {
            if (key == cur->getKey()) {
                cout << "키 '" << key << "' 삭제\n";

                if(cur->getRight() != NULL && cur->getLeft() != NULL) {
                    //삭제하려는 node의 자식 노드가 2개인 경우
                    Node* Rmin = cur->getRight();
                    Node* temp = cur; // Rmin의 부모 노드 
                    while (Rmin->getLeft() != NULL) {
                        temp = Rmin;
                        Rmin = Rmin->getLeft();
                    }
                    cur->setValue(Rmin->getValue());
                    cur->setKey(Rmin->getKey());
                    //node의 key와 value를 Rmin의 값으로 변경, Rmin은 삭제

                    if (cur->getRight() == Rmin) {
                        cur->setRight(Rmin->getRight());
                    }
                    else {
                        temp->setLeft(Rmin->getRight());
                    }
                    delete Rmin;
                    //Rmin은 부모 노드의 왼쪽에 존재
                    //Rmin의 부모의 left node를 Rmin의 rightNode와 연결
                    //단, 삭제하려는 노드의 바로 오른쪽 노드가 Rmin일 경우엔 Rmin이 오른쪽에 존재
                }

                else if (cur->getLeft() != NULL && cur->getRight() == NULL) {
                    //삭제하려는 node의 leftnode만 존재하는 경우
                    if (parent->getKey() > cur->getKey())
                        parent->setLeft(cur->getLeft());
                    else
                        parent->setRight(cur->getLeft());
                    delete cur;
                    //부모 노드와 left node를 연결, 노드 삭제
                }
                else if (cur->getLeft() == NULL) {
                    //삭제하려는 node의 rightnode만 존재하는 경우
                    if (parent->getKey() > cur->getKey())
                        parent->setLeft(cur->getRight());
                    else
                        parent->setRight(cur->getRight());
                    delete cur;
                }
                else if (cur->getRight() == NULL) {
                    //삭제하려는 node의 leftnode만 존재하는 경우
                    if (parent->getKey() > cur->getKey())
                        parent->setLeft(cur->getLeft());
                    else
                        parent->setRight(cur->getLeft());
                    delete cur;
                }
                else {
                    //삭제하려는 node가 leaf 노드인 경우
                    if (parent->getKey() > cur->getKey())
                        parent->setLeft(NULL);
                    else
                        parent->setRight(NULL);
                    delete cur;
                    //부모 노드의 포인터를 NULL로 변경하고 삭제
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