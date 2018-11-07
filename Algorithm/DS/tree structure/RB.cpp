// BST �������� AVL, RB ,���У�BST Ч��Զ����AVL RB��RB�� ʱ��� AVL �ٸ�������  

/*  �������ƽ���������
		1.ÿ���ڵ㲻�Ǻ�ɫ���Ǻ�ɫ��
		2.���ڵ��Ǻ�ɫ��
		3.ÿ��Ҷ�ӽڵ��Ǻ�ɫ��
		4.����ڵ��Ǻ�ɫ����ô�����������ӽڵ㶼�Ǻ�ɫ�ģ�
		5.��ÿ���ڵ���˵���ӽڵ㵽Ҷ�ӽڵ��·��������ͬ��Ŀ�ĺ�ɫ�ڵ㡣
		6.һ����n���ڵ��RB��,��߶������2log(n+1)
		7.�ڸߣ�ĳ����㵽�� һ��Ҷ��������һ����·���ϵĺ�ɫ��������Ϊ�ý��ĺڸߣ�black-height�������� bh(x)��
		8.����������в������㷨���Ӷȶ��� O(lgn)
		9.��ת�Ĳ���ֻ�������޸�ָ��Ĳ���������㷨���Ӷ��� O(1)��
		10.BST�ı�׼�����ɾ���������ں����Ҳ��O(lgn)�ģ�������������������֤����֮���ǿ�RB��. 
		
		
		
AVL and RB
���Ⱥ�����ǲ�����AVL����ƽ�������ģ���ÿ���ڵ�����������������ĸ߶�����1�Ķ����������
���������Ϊ�ڵ�������ɫ��������÷��ϸ��ƽ������ȡ��ɾ�ڵ�ʱ����ת�����Ľ��ͣ�
�κβ�ƽ�ⶼ����������ת֮�ڽ������AVL���ϸ�ƽ������
RB-Tree����Ҫ���������ɾ��node�ĳ����£�Ч�ʸ��ߡ���Ȼ������AVL�߶�ƽ�⣬���AVL��searchЧ�ʸ���

������Ĳ�ѯ������΢ѷɫ��AVL������Ϊ����avl������΢��ƽ�����һ�㣬
Ҳ����˵������Ĳ�ѯ����ֻ����ͬ���ݵ�avl������һ�αȽϣ�����
������ڲ����ɾ�����걬avl����avl��ÿ�β���ɾ������д�����ƽ��ȼ���,
�������Ϊ��ά�ֺ�����������ĺ�ڱ任����ת�Ŀ����������avl��Ϊ��ά��ƽ��Ŀ���ҪС�ö�

*/ 


struct RBNode {
     int color;//red is 0,black is 1
     void *key;
     void *value;
     struct RBNode *left;
     struct RBNode *right;
     struct RBNode *parent;
};


//**************************************RB���Ĳ���*******************************************************//
//������Ĳ���:���ҵ�Ҫ�½ڵ�����λ�ã����ڵ㸳���ɫ��Ȼ������½ڵ㡣�������������ʵ��޸���
/* Ϊʲô�½�㸳�� 
 ����Υ��2��ֱ�ӽ����ڵ��ڼ��� ��������ڣ�Ӱ��ڸߣ���5������죬ֻ��Ҫ����2 4�������� �������������� 
 */ 
 
 void RB_INSERT(RBNode* T, RBNode *node){//���Ӷȣ�1�ҵ��½�����logn,2�����޸� ��������תO(1)��ʹ�������O(logn)��,so:O(logn) 
 	RBNode *walk = T;
    RBNode *pre = NULL;
    while (walk != NULL){//ȷ�������λ�� 
    	pre = walk;
        if (node->key < walk->key){
        	 walk = walk->left;
		}
           
        else walk = walk->right;// ����Ĭ�ϲ���Ĳ����ظ� 
	} 
        
    node->parent = pre;
    if (pre == NULL)
        root = node;
    else if (node->key <pre->key)
        pre->left = node;
    else pre->right = node;
    RB_INSERT_FIXUP(T, node);
 } 
 
 //������޸�   
 void RB_INSERT_FIXUP(RBNode *T, RBNode *node){
 	while(node->color==0){//����Ľ���� ��ɫ�źϷ� 
    	RBNode *parent = node->parent; 
        if (parent->color!=0)! {
        	break;      //���㲻���ڣ��޳�ͻ 
		}
		//�������ڵĺ��� ��������Ķ��Ӳ�ȫΪ��ɫ 
        RBNode *grandparent = parent->parent;//�޸��ı仯��Ҫ����������游�������ӻ����Һ��� 
        if (parent == grandparent->left){       //������������ǶԳƵģ��˴�����������游�������ӵ����
            BRNode *uncle = grandparent->right;
            if (uncle->color==0){//uncle����ɫ             Ҳ�Ǻ�� 
                parent->color = 1;//Ҫ�ָ������������ ,��Ҫ��parent ��ڣ��ڸ�++������grandparent �ƻ�������5  
                uncle->color = 1;//���Զ�Ӧ uncle ҲҪ�ڸ�++ 
                grandparent->color = 0;//�����������֮ǰ��parent �� uncle һ���Ǻ�ģ�����ֵܵĸ��׼�grandparent �� 
                node = grandparent; //node ָ�� grandparent�����޸������������ level��ֱ�����������Ϊֹ���ӵײ��������ϵ��� 
            } 
			else if (node == parent->right){ //�Ҷ��ӣ�������������ת�����������                                    
                LEFT_ROTATE(T, parent);
                swap(node, parent);
            } 
            else{ //uncle �� �����ܽ� uncle ����ˣ�ֻ�ܽ������������游�ڵ� �������游����죬Ȼ�󽫸�����ڣ������Ϊ�������������������Ͳ�ƽ���� 
                parent->color = 1;//����Һڸ߶�һ 
                grandparent->color = 0;
                RIGHT_ROTATE(T, grandparent);//���游��������Ե�������ƽ�� 
            } 
        } 
        // same as then clause with "right" and "left" exchanged
		else if(parent == grandparent->right){
			BRNode *uncle = grandparent->left;
            if (uncle->color==0){
                parent->color = 1;
                uncle->color = 1;
                grandparent->color = 0; 
                node = grandparent; 
            } 
			else if (node == parent->left){                                   
                RIGHT_ROTATE(T, parent);
                swap(node, parent);
            } 
            else{                 
				parent->color = 1;
                grandparent->color = 0;
                LEFT_ROTATE(T, grandparent);
            } 
		}
    
	}
        
    T-> color = 1; //���ڵ�һ���Ǻ�ɫ 
 
 }
    
 //**************************************RB���Ĳ���*******************************************************//
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
 
