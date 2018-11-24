#include<stdlib.h>
#include<iostream>
#include<iomanip>
#include<stack>
using namespace std;
template<typename T> struct Node {
    T data;
    Node<T> *LChild;
    Node<T> *RChild;
    Node<T> *Parent;
    Node() {}
    Node(T dat, Node<T> *L, Node<T> *R, Node<T> *P) {
        data = dat;
        LChild = L;
        RChild = R;
        Parent = P;
    }
    ~Node() {}
};
template<typename T> class BST {
private:
    Node<T>*root;
public:
    BST() {
        root = NULL;
    }
    ~BST() {
        Destroy_stack();
    }
    Node<T>* getRoot() {
        return root;
    }
    void InsertBST(Node<int>*root, int val);
    void IntBST(int a[], int size);
    void PreTralve(Node<T>*root);
    void PreTralve_stack(Node<T>*root);
    void PreTralve_nostack(Node<T>*root);
    void InTralve(Node<T>*root);
    void InTralve_stack(Node<T>*root);
    void InTralve_nostack(Node<T>*root);
    void PostTralve(Node<T>*root);
    void PostTralve_stack(Node<T>*root);
    void PostTralve_nostack(Node<T>*root);
    Node<T>* Find(Node<T>*root, int val);
    Node<T>*Find_mostLeft(Node<T>*root);
    Node<T>*In_next(Node<T>*root);
    //�ݹ�õ�����
    static int getHeight(Node<T> *root) {
        if (root == NULL) {
            return 0;
        }
        int leftHeight = 0;
        int rightHeight = 0;
        if (root->LChild != NULL) {
            leftHeight += getHeight(root->LChild) + 1;
        }
        if (root->RChild != NULL) {
            rightHeight += getHeight(root->RChild) + 1;
        }
        return leftHeight >= rightHeight ? leftHeight : rightHeight;
    }
    //���õݹ�дDestroy
    void Destroy(Node<T> *root)//����һ�Ŷ�����
    {
        //1.��Ϊ�գ�ֱ�ӷ��أ��޽������
        if (root == NULL)
        {
            return;
        }
        //2.��ֻ��һ����㣬�����ٸýڵ�
        if (root->LChild == NULL && root->RChild == NULL)
        {
            delete root;
            root = NULL;
            return;
        }
        //3.���Ľ�����һ��������������������������������
        Destroy(root->LChild);
        Destroy(root->RChild);
        delete root;
        root = NULL;
    }
    //��ջʵ��Destroy
    void Destroy_stack() {
        stack<Node<T>*> s;
        Node<T> *cur;//��ǰ���
        Node<T> *pre = NULL;//ǰһ�η��ʵĽ��
        s.push(root);
        while (!s.empty())
        {
            cur = s.top();
            if ((cur->LChild == NULL && cur->RChild == NULL) ||
                (pre != NULL && (pre == cur->LChild || pre == cur->RChild)))
            {
                delete cur;  //�����ǰ���û�к��ӽ����ߺ��ӽڵ㶼�ѱ����ʹ�
                s.pop();
                pre = cur;
            }
            else
            {
                if (cur->RChild != NULL)
                    s.push(cur->RChild);
                if (cur->LChild != NULL)
                    s.push(cur->LChild);
            }
        }
        root = NULL;
    }
};
//���Ӷ�ΪO(n*h),��Ϊÿ����һ��Ԫ�ض���Ҫ�Ӹ��ڵ㿪ʼ�ж�
template<typename T>void BST<T>::IntBST(int a[], int size) {
    int i = 0;
    Node<int>*p = BST::root;
    Node<int>*s;
    while (i < size) {//ÿ����Ҫ��ͷ��ʼ�жϸò���δ�
        InsertBST(root, a[i++]);
    }
}
//���Ӷ�ΪO(h),hΪ����
template<typename T> void BST<T>::InsertBST(Node<int>*root, int val) {
    Node<int>*p, *s, *pp = NULL;
    p = root;
    //�ҵ������λ��
    while (p != NULL) {
        pp = p;
        if (val > p->data) {
            p = p->RChild;
        }
        else
            p = p->LChild;
    }
    s = new Node<int>(val, NULL, NULL, NULL);
    s->Parent = pp;//ppΪ����Ŀյص�parent
    if (pp == NULL) {//sΪ��
        root = s;
    }
    else if (pp->data > val) {
        pp->LChild = s;
    }
    else {
        pp->RChild = s;
    }
    BST::root = root;
}
//ʱ�临�Ӷȣ�O(n),ÿ���ڵ㶼����һ��
template<typename T>void BST<T>::PreTralve(Node<T>* root) {
    Node<T>*p = root;
    if (p == NULL) { return; }
    cout << p->data;
    if (p->LChild != NULL) {
        PreTralve(p->LChild);
    }
    if (p->RChild != NULL) {
        PreTralve(p->RChild);
    }
}
template<typename T>void BST<T>::PreTralve_stack(Node<T>* root) {
    if (root == NULL) { return; }
    stack<Node<int>*> s;
    s.push(root);
    while (!s.empty()) {
        Node<int>* p = s.top();
        s.pop();
        if (p == NULL) { continue; }
        cout << setw(4) << p->data;
        if (p->RChild != NULL) { s.push(p->RChild); }
        if (p->LChild != NULL) { s.push(p->LChild); }
    }
}
//ǰ����ջ��δд
template<typename T>void BST<T>::PreTralve_nostack(Node<T>* root) {}
//ʱ�临�Ӷȣ�O(n),ÿ���ڵ㶼����һ��
//����Ľ��������Ľ��
template<typename T>void BST<T>::InTralve(Node<T>*root) {
    Node<T>*p = root;
    if (p == NULL) { return; }
    if (p->LChild != NULL) {
        InTralve(p->LChild);
    }
    cout << p->data;
    if (p->RChild != NULL) {
        InTralve(p->RChild);
    }
}
template<typename T>void BST<T>::InTralve_stack(Node<T>*p) {
    if (root == NULL) { return; }
    stack<Node<int>*> s;
    while (!s.empty() || p != NULL) {
        while (p != NULL) {
            s.push(p);
            p = p->LChild;
        }
        if (p == NULL) {
            p = s.top();
            cout << setw(4) << p->data;
            s.pop();
            p = p->RChild;
        }
    }
}
template<typename T>void BST<T>::InTralve_nostack(Node<T>*root) {
    if (root == NULL) { return; }
    Node<T>*p = Find_mostLeft(root);
    do {
        cout << setw(4) << p->data;
        p = In_next(p);
    } while (p != NULL);
}
//ʱ�临�Ӷȣ�O(n),ÿ���ڵ㶼����һ��
template<typename T>void BST<T>::PostTralve(Node<T>*root) {
    Node<T>*p = root;
    if (p == NULL) { return; }
    if (p->LChild != NULL) {
        PostTralve(p->LChild);
    }
    if (p->RChild != NULL) {
        PostTralve(p->RChild);
    }
    cout << p->data;
}
template<typename T>void BST<T>::PostTralve_stack(Node<T>*root) {
    stack<Node<T>*> s;
    Node<T> *cur;//��ǰ���
    Node<T> *pre = NULL;//ǰһ�η��ʵĽ��
    s.push(root);
    while (!s.empty())
    {
        cur = s.top();
        if ((cur->LChild == NULL && cur->RChild == NULL) ||
            (pre != NULL && (pre == cur->LChild || pre == cur->RChild)))
        {
            cout << cur->data << " ";  //�����ǰ���û�к��ӽ����ߺ��ӽڵ㶼�ѱ����ʹ�
            s.pop();
            pre = cur;
        }
        else
        {
            if (cur->RChild != NULL)
                s.push(cur->RChild);
            if (cur->LChild != NULL)
                s.push(cur->LChild);
        }
    }
}
//������ջ��δд
template<typename T>void BST<T>::PostTralve_nostack(Node<T>*root) {}
//��ѯ�ĸ��Ӷ�ΪO(h)
template<typename T>Node<T>* BST<T>::Find(Node<T>*root, int val) {
    Node<int>*p = root;
    while (p != NULL && val != p->data) {
        if (p->data < val) {
            p = p->RChild;
        }
        else {
            p = p->LChild;

        }
    }
    if (p == NULL) { cout << "����Ϊ�ջ��ֵ������" << endl; }
    return p;
}
template<typename T>Node<T>* BST<T>::Find_mostLeft(Node<T>*root) {
    if (root == NULL) {
        cout << "����Ϊ��" << endl;
        return NULL;
    }
    Node<T>*p = root;
    while (p->LChild != NULL) {
        p = p->LChild;
    }
    //p��ʱ�������µĽڵ�
    return p;
}
template<typename T>Node<T>* BST<T>::In_next(Node<T>*root) {
    if (root == NULL) {
        cout << "�ýڵ�Ϊ��" << endl;
        return NULL;
    }
    if (root->RChild != NULL) {
        return Find_mostLeft(root->RChild);
    }
    Node<T>*p = root->Parent;
    while (p != NULL && root == p->RChild) {
        root = p;
        p = p->Parent;
    }
    return p;
}
