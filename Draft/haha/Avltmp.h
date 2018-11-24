#include<stdlib.h>
#include<iostream>
#include<iomanip>
#include<stack>
#include<math.h>
template <typename T>
struct AVLTreeNode {
    T key;
    int height;
    AVLTreeNode* lchild;
    AVLTreeNode* rchild;
    AVLTreeNode() {}
    AVLTreeNode(int h, T k, AVLTreeNode*l, AVLTreeNode*r) :key(k), height(h), lchild(l), rchild(r) {}
    ~AVLTreeNode() {
    }
};
template<typename T> class AVL {
private:
    AVLTreeNode<T>* root;
public:
    //���ú������������������Ӷ�ΪO(n)
    void Destroy_stack() {
        stack<AVLTreeNode<T>*> s;
        AVLTreeNode<T> *cur;//��ǰ���
        AVLTreeNode<T> *pre = NULL;//ǰһ�η��ʵĽ��
        s.push(root);
        while (!s.empty())
        {
            cur = s.top();
            if ((cur->lchild == NULL && cur->rchild == NULL) ||
                (pre != NULL && (pre == cur->lchild || pre == cur->rchild)))
            {
                delete cur;  //�����ǰ���û�к��ӽ����ߺ��ӽڵ㶼�ѱ����ʹ�
                s.pop();
                pre = cur;
            }
            else
            {
                if (cur->rchild != NULL)
                    s.push(cur->rchild);
                if (cur->lchild != NULL)
                    s.push(cur->lchild);
            }
        }
        root = NULL;
    }
    static void get() { return; }
    void setroot(AVLTreeNode<T> *p) { root = p; }
    AVLTreeNode<T>* getroot() { return root; }
    AVL() {
        root = NULL;
    }
    int max(int a, int b) {
        if (a > b) {
            return a;
        }
        else
            return b;
    }
    int tree_height(AVLTreeNode<T> *p) {
        if (p == NULL) {
            return 0;
        }
        else
            return p->height;
    }
    //�����ʱ�����ĳ�ڵ�����Ҷ����������2��������Ҫ�������е���һ����ת
    //����ĸ��Ӷ���ΪO(log n)��
    AVLTreeNode<T>* AVL_Insert(AVLTreeNode<T> *root, T v) {
        if (root == NULL) {
            root = new AVLTreeNode<T>(0, v, NULL, NULL);
        }
        else if (v < root->key) {
            root->lchild = AVL_Insert(root->lchild, v);
            if (tree_height(root->lchild) - tree_height(root->rchild) == 2) {
                if (v < root->lchild->key) {
                    root = left_left_rotation(root);
                }
                else
                {
                    root = left_right_rotation(root);
                }
            }
        }
        else if (v > root->key) {
            root->rchild = AVL_Insert(root->rchild, v);
            if (tree_height(root->rchild) - tree_height(root->lchild) == 2) {
                if (v < root->rchild->key) {
                    root = right_left_rotation(root);
                }
                else {
                    root = right_right_rotation(root);
                }
            }
        }
        else {
            cout << "Insert Failed!";
            return 0;
        }
        root->height = max(tree_height(root->lchild), tree_height(root->rchild)) + 1;
        return root;
    }
    //����n�εĲ�����������Ӷ�ΪO(n*log n)��
    void AVL_creat(int *p, int size, AVLTreeNode<T> *root) {
        for (int i = 0; i < size; i++) {
            root = AVL_Insert(root, p[i]);
        }
        AVL::root = root;
    }
    //��������ת�����ǳ������Ĳ��������Ǽ����Ĳ���
    AVLTreeNode<T>* left_left_rotation(AVLTreeNode<T> *p) {
        AVLTreeNode<T> *k = p->lchild;
        p->lchild = k->rchild;
        k->rchild = p;
        p->height = max(tree_height(p->lchild), tree_height(p->rchild)) + 1;
        k->height = max(tree_height(k->lchild), p->height) + 1;
        return k;
    }
    AVLTreeNode<T>* right_right_rotation(AVLTreeNode<T> *p) {

        AVLTreeNode<T> *k = p->rchild;
        p->rchild = k->lchild;
        k->lchild = p;
        p->height = max(tree_height(p->lchild), tree_height(p->rchild)) + 1;
        k->height = max(tree_height(k->rchild), p->height) + 1;
        return k;
    }
    AVLTreeNode<T>* left_right_rotation(AVLTreeNode<T> *p) {
        p->lchild = right_right_rotation(p->lchild);
        return left_left_rotation(p);
    }
    AVLTreeNode<T>* right_left_rotation(AVLTreeNode<T> *p) {
        p->rchild = left_left_rotation(p->rchild);
        return right_right_rotation(p);
    }
    //�˴����������õݹ��ǰ�к�����������ӶȾ�ΪO(n)
    void PreTralve_stack(AVLTreeNode<T>* root) {
        if (root == NULL) { return; }
        stack<AVLTreeNode<int>*> s;
        s.push(root);
        while (!s.empty()) {
            AVLTreeNode<int>* p = s.top();
            s.pop();
            if (p == NULL) { continue; }
            cout << p->key << "  ";
            if (p->rchild != NULL) { s.push(p->rchild); }
            if (p->lchild != NULL) { s.push(p->lchild); }
        }
    }
    void InTralve_stack(AVLTreeNode<T>* p) {
        if (root == NULL) { return; }
        stack<AVLTreeNode<int>*> s;
        while (!s.empty() || p != NULL) {
            while (p != NULL) {
                s.push(p);
                p = p->lchild;
            }
            if (p == NULL) {
                p = s.top();
                cout << p->key << "  ";
                s.pop();
                p = p->rchild;
            }
        }
    }
    void PostTralve_stack(AVLTreeNode<T>*root) {
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
    //������ҵ������µĽڵ㣬֮ǰ���Ե�ʱ���õ���
    AVLTreeNode<T>* Find_mostLeft(AVLTreeNode<T>*root) {
        if (root == NULL) {
            cout << "����Ϊ��" << endl;
            return NULL;
        }
        AVLTreeNode<T> *p = root;
        while (p->lchild != NULL) {
            p = p->lchild;
        }
        //p��ʱ�������µĽڵ�
        return p;
    }
    //���ҵĸ��Ӷ�ΪO(h)
    AVLTreeNode<T>* Find(AVLTreeNode<T>*root, int val) {
        AVLTreeNode<int>*p = root;
        while (p != NULL && val != p->key) {
            if (p->key < val) {
                p = p->rchild;
            }
            else {
                p = p->lchild;

            }
        }
        if (p == NULL) { cout << "����Ϊ�ջ��ֵ������" << endl; }
        return p;
    }
};
