#pragma once
#include <iomanip>
#include <iostream>
using namespace std;

enum RBTColor { RED=0, BLACK };

template <typename T>
class RBTNode {
public:
    RBTColor color;    // 颜色
    T key;            // 关键字(键值)
    RBTNode* left;    // 左孩子
    RBTNode* right;    // 右孩子
    RBTNode* parent; // 父结点

    RBTNode(T value, RBTColor c, RBTNode* p, RBTNode* l, RBTNode* r) :
        key(value), color(c), parent(), left(l), right(r) {}
};

template <typename  T>
struct RBTreeIterator
{
    typedef RBTNode<T> Node;
    typedef RBTreeIterator<T> Self;
    Node* _node;
    RBTreeIterator():_node(NULL){ }
    RBTreeIterator(Node* node)
        :_node(node)
    {}

    RBTreeIterator(Self& v)
        :_node(v._node)
    {}

    //解引用
    T& operator*()
    {
        return _node->key;
    }
    const T& operator*() const
    {
        return _node->key;
    }

    T* operator->()
    {
        return &_node->key;
    }
    const T* operator->()const
    {
        return &_node->key;
    }

    bool operator!=(const Self& it)
    {
        return _node != it._node;
    }

    bool operator==(const Self& it)
    {
        return _node == it._node;
    }

    Self operator++()
    {
        if (_node->right) //存在右节点
        {
            //右子树的最左结点
            _node = _node->right;
            while (_node->left)
            {
                _node = _node->left;
            }
        }
        else //不存在右节点
        {
        
            Node* parent = _node->parent;
            while (parent!=NULL && _node == parent->right)//回溯
            {
                _node = parent;
                parent = parent->parent;
            }
            _node = parent;
        }
        return *this;
    }

    Self operator++(int) {
        Self tmp(*this);
        ++(*this);
        return tmp;
    }

    Self operator--()
    {
        if (_node->left)
        {
            //右子树的最左结点
            _node = _node->left;
            while (_node->right)
            {
                _node = _node->right;
            }
        }
        else
        {
            Node* parent = _node->parent;
            while (parent != NULL && _node == parent->left)
            {
                _node = parent;
                parent = parent->parent;
            }
                _node = parent;
        }
        return *this;
    }

    Self operator--(int) {
        Self tmp(*this);
        --(*this);
        return tmp;
    }
};

template <typename  T>
class RBTreeRIterator
{
public:
    RBTreeRIterator():it(){ }
    RBTreeRIterator(RBTreeIterator<T> &v):it(v){ }
    ~RBTreeRIterator(){}
    typedef RBTreeRIterator<T> Self;

    T& operator*()
    {
        return *it;
    }

    T* operator->()
    {
        return &it;
    }

    bool operator!=(const Self& v)
    {
        return it != v.it;
    }

    bool operator==(const Self& v)
    {
        return it == v.it;
    }

    Self& operator++()
    {
        --(this->it);
        return *this;
    }

    Self& operator++(int) {
        ++(*this);
        return *this;
    }

    Self& operator--()
    {
        ++(this->it);
        return *this;
    }

    Self& operator--(int) {
        --(*this);
        return *this;
    }
private:
    RBTreeIterator<T> it;
};


template <typename T, typename func>
class RBTree {
private:
    RBTNode<T>* mRoot;    // 根结点
    int sz;
public:
    RBTree();
    ~RBTree();

    typedef RBTreeIterator<T> iterator;
    typedef RBTreeRIterator<T> riterator;

    iterator begin()
    {
        return iterator(minimum(mRoot));
    }
    iterator end()
    {
        return iterator(NULL);
    }

    iterator begin() const
    {
        return riterator(minimum(mRoot));
    }
    iterator end() const
    {
        return riterator(NULL);
    }

    const iterator cbegin()
    {
        return iterator(minimum(mRoot));
    }
    const iterator cend() 
    {
        return iterator(NULL);
    }

    riterator rbegin()
    {
        auto it = iterator(maximum(mRoot));
        return riterator(it);
    }
    riterator rend()
    {
        auto it = iterator(maximum(NULL));
        return riterator(it);
    }

    int size() {
        return sz;
    }

    bool empty() {
        return mRoot == NULL;
    }

    // 查找"红黑树"中键值为key的节点
    RBTreeIterator<T> search(T key);

    // 将结点(key为节点键值)插入到红黑树中
    RBTreeIterator<T> insert(T key);

    // 删除结点(key为节点键值)
    void remove(T key);

    // 销毁红黑树
    void destroy();


private:
 

    // (递归实现)查找"红黑树x"中键值为key的节点
    RBTNode<T>* search(RBTNode<T>* x, T key) const;

    // 查找最小结点：返回tree为根结点的红黑树的最小结点。
    RBTNode<T>* minimum(RBTNode<T>* tree);
    // 查找最大结点：返回tree为根结点的红黑树的最大结点。
    RBTNode<T>* maximum(RBTNode<T>* tree);

    // 左旋
    void leftRotate(RBTNode<T>*& root, RBTNode<T>* x);
    // 右旋
    void rightRotate(RBTNode<T>*& root, RBTNode<T>* y);
    // 插入函数
    void insert(RBTNode<T>*& root, RBTNode<T>* node);
    // 插入修正函数
    void insertFixUp(RBTNode<T>*& root, RBTNode<T>* node);
    // 删除函数
    void remove(RBTNode<T>*& root, RBTNode<T>* node);
    // 删除修正函数
    void removeFixUp(RBTNode<T>*& root, RBTNode<T>* node, RBTNode<T>* parent);

    // 销毁红黑树
    void destroy(RBTNode<T>*& tree);


#define rb_parent(r)   ((r)->parent)
#define rb_color(r) ((r)->color)
#define rb_is_red(r)   ((r)->color==RED)
#define rb_is_black(r)  ((r)->color==BLACK)
#define rb_set_black(r)  do { (r)->color = BLACK; } while (0)
#define rb_set_red(r)  do { (r)->color = RED; } while (0)
#define rb_set_parent(r,p)  do { (r)->parent = (p); } while (0)
#define rb_set_color(r,c)  do { (r)->color = (c); } while (0)
};

template <typename T, typename func>
RBTree<T, func>::RBTree() :mRoot(NULL)
{
    mRoot = NULL;
    sz = 0;
}

template <typename T, typename func>
RBTree<T, func>::~RBTree()
{
    sz = 0;
    destroy();
}

template <typename T, typename func>
RBTNode<T>* RBTree<T, func>::search(RBTNode<T>* x, T key) const
{
    if (x == NULL || func()(x->key) == func()(key))
        return x;

    if (func()(key) < func()(x->key))
        return search(x->left, key);
    else
        return search(x->right, key);
}

template <typename T, typename func>
RBTreeIterator<T> RBTree<T, func>::search(T key)
{
    return RBTreeIterator<T>(search(mRoot, key));
}

template <typename T, typename func>
RBTNode<T>* RBTree<T, func>::minimum(RBTNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while (tree->left != NULL)
        tree = tree->left;
    return tree;
}

template <typename T, typename func>
RBTNode<T>* RBTree<T, func>::maximum(RBTNode<T>* tree)
{
    if (tree == NULL)
        return NULL;

    while (tree->right != NULL)
        tree = tree->right;
    return tree;
}

template <typename T, typename func>
void RBTree<T, func>::leftRotate(RBTNode<T>*& root, RBTNode<T>* x)
{
    // 设置x的右孩子为y
    RBTNode<T>* y = x->right;

    // 将 “y的左孩子” 设为 “x的右孩子”；
    // 如果y的左孩子非空，将 “x” 设为 “y的左孩子的父亲”
    x->right = y->left;
    if (y->left != NULL)
        y->left->parent = x;

    // 将 “x的父亲” 设为 “y的父亲”
    y->parent = x->parent;

    if (x->parent == NULL)
    {
        root = y;            // 如果 “x的父亲” 是空节点，则将y设为根节点
    }
    else
    {
        if (x->parent->left == x)
            x->parent->left = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
        else
            x->parent->right = y;    // 如果 x是它父节点的左孩子，则将y设为“x的父节点的左孩子”
    }

    // 将 “x” 设为 “y的左孩子”
    y->left = x;
    // 将 “x的父节点” 设为 “y”
    x->parent = y;
}

template <typename T, typename func>
void RBTree<T, func>::rightRotate(RBTNode<T>*& root, RBTNode<T>* y)
{
    // 设置x是当前节点的左孩子。
    RBTNode<T>* x = y->left;

    // 将 “x的右孩子” 设为 “y的左孩子”；
    // 如果"x的右孩子"不为空的话，将 “y” 设为 “x的右孩子的父亲”
    y->left = x->right;
    if (x->right != NULL)
        x->right->parent = y;

    // 将 “y的父亲” 设为 “x的父亲”
    x->parent = y->parent;

    if (y->parent == NULL)
    {
        root = x;            // 如果 “y的父亲” 是空节点，则将x设为根节点
    }
    else
    {
        if (y == y->parent->right)
            y->parent->right = x;    // 如果 y是它父节点的右孩子，则将x设为“y的父节点的右孩子”
        else
            y->parent->left = x;    // (y是它父节点的左孩子) 将x设为“x的父节点的左孩子”
    }

    // 将 “y” 设为 “x的右孩子”
    x->right = y;

    // 将 “y的父节点” 设为 “x”
    y->parent = x;
}

/*
 * 红黑树插入修正函数
 *
 * 在向红黑树中插入节点之后(失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 插入的结点       
 */
template <typename T, typename func>
void RBTree<T, func>::insertFixUp(RBTNode<T>*& root, RBTNode<T>* node)
{
    RBTNode<T>* parent, * gparent;

    // 若“父节点存在，并且父节点的颜色是红色”
    while ((parent = rb_parent(node)) && rb_is_red(parent))
    {
        gparent = rb_parent(parent);

        //若“父节点”是“祖父节点的左孩子”
        if (parent == gparent->left)
        {
            // Case 1条件：叔叔节点是红色
            {
                RBTNode<T>* uncle = gparent->right;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            // Case 2条件：叔叔是黑色，且当前节点是右孩子
            if (parent->right == node)
            {
                RBTNode<T>* tmp;
                leftRotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是左孩子。
            rb_set_black(parent);
            rb_set_red(gparent);
            rightRotate(root, gparent);
        }
        else//若“z的父节点”是“z的祖父节点的右孩子”
        {
            // Case 1条件：叔叔节点是红色
            {
                RBTNode<T>* uncle = gparent->left;
                if (uncle && rb_is_red(uncle))
                {
                    rb_set_black(uncle);
                    rb_set_black(parent);
                    rb_set_red(gparent);
                    node = gparent;
                    continue;
                }
            }

            // Case 2条件：叔叔是黑色，且当前节点是左孩子
            if (parent->left == node)
            {
                RBTNode<T>* tmp;
                rightRotate(root, parent);
                tmp = parent;
                parent = node;
                node = tmp;
            }

            // Case 3条件：叔叔是黑色，且当前节点是右孩子。
            rb_set_black(parent);
            rb_set_red(gparent);
            leftRotate(root, gparent);
        }
    }

    // 将根节点设为黑色
    rb_set_black(root);
}

template <typename T, typename func>
void RBTree<T, func>::insert(RBTNode<T>*& root, RBTNode<T>* node)
{
    RBTNode<T>* y = NULL;
    RBTNode<T>* x = root;

    // 1. 将红黑树当作一颗二叉查找树，将节点添加到二叉查找树中。
    while (x != NULL)
    {
        y = x;
        if (func()(node->key) < func()(x->key))
            x = x->left;
        else
            x = x->right;
    }

    node->parent = y;
    if (y != NULL)
    {
        if (func()(node->key) < func()(y->key))
            y->left = node;
        else
            y->right = node;
    }
    else
        root = node;

    // 2. 设置节点的颜色为红色
    node->color = RED;

    // 3. 将它重新修正为一颗二叉查找树
    insertFixUp(root, node);
}

template <typename T, typename func>
RBTreeIterator<T> RBTree<T, func>::insert(T key)
{
    RBTNode<T>* z = NULL;

    // 如果新建结点失败，则返回。
    if ((z = new RBTNode<T>(key, BLACK, NULL, NULL, NULL)) == NULL)
        return RBTreeIterator<T>(NULL);

    insert(mRoot, z);
    sz++;
    return RBTreeIterator<T>(z);
}

/*
 * 红黑树删除修正函数
 *
 * 在从红黑树中删除插入节点之后(红黑树失去平衡)，再调用该函数；
 * 目的是将它重新塑造成一颗红黑树。
 *
 * 参数说明：
 *     root 红黑树的根
 *     node 待修正的节点
 */
template <typename T, typename func>
void RBTree<T, func>::removeFixUp(RBTNode<T>*& root, RBTNode<T>* node, RBTNode<T>* parent)
{
    RBTNode<T>* other;

    while ((!node || rb_is_black(node)) && node != root)
    {
        if (parent->left == node)
        {
            other = parent->right;
            if (rb_is_red(other))
            {
                // Case 1: x的兄弟w是红色的
                rb_set_black(other);
                rb_set_red(parent);
                leftRotate(root, parent);
                other = parent->right;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->right || rb_is_black(other->right))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                    rb_set_black(other->left);
                    rb_set_red(other);
                    rightRotate(root, other);
                    other = parent->right;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->right);
                leftRotate(root, parent);
                node = root;
                break;
            }
        }
        else
        {
            other = parent->left;
            if (rb_is_red(other))
            {
                // Case 1: x的兄弟w是红色的
                rb_set_black(other);
                rb_set_red(parent);
                rightRotate(root, parent);
                other = parent->left;
            }
            if ((!other->left || rb_is_black(other->left)) &&
                (!other->right || rb_is_black(other->right)))
            {
                // Case 2: x的兄弟w是黑色，且w的俩个孩子也都是黑色的
                rb_set_red(other);
                node = parent;
                parent = rb_parent(node);
            }
            else
            {
                if (!other->left || rb_is_black(other->left))
                {
                    // Case 3: x的兄弟w是黑色的，并且w的左孩子是红色，右孩子为黑色。
                    rb_set_black(other->right);
                    rb_set_red(other);
                    leftRotate(root, other);
                    other = parent->left;
                }
                // Case 4: x的兄弟w是黑色的；并且w的右孩子是红色的，左孩子任意颜色。
                rb_set_color(other, rb_color(parent));
                rb_set_black(parent);
                rb_set_black(other->left);
                rightRotate(root, parent);
                node = root;
                break;
            }
        }
    }
    if (node)
        rb_set_black(node);
}

template <typename T, typename func>
void RBTree<T, func>::remove(RBTNode<T>*& root, RBTNode<T>* node)
{
    RBTNode<T>* child, * parent;
    RBTColor color;

    // 被删除节点的"左右孩子都不为空"的情况。
    if ((node->left != NULL) && (node->right != NULL))
    {
        // 被删节点的后继节点。(称为"取代节点")
        // 用它来取代"被删节点"的位置，然后再将"被删节点"去掉。
        RBTNode<T>* replace = node;

        // 获取后继节点
        replace = replace->right;
        while (replace->left != NULL)
            replace = replace->left;

        // "node节点"不是根节点(只有根节点不存在父节点)
        if (rb_parent(node))
        {
            if (rb_parent(node)->left == node)
                rb_parent(node)->left = replace;
            else
                rb_parent(node)->right = replace;
        }
        else
            // "node节点"是根节点，更新根节点。
            root = replace;

        // child是"取代节点"的右孩子，也是需要"调整的节点"。
        // "取代节点"肯定不存在左孩子！因为它是一个后继节点。
        child = replace->right;
        parent = rb_parent(replace);
        // 保存"取代节点"的颜色
        color = rb_color(replace);

        // "被删除节点"是"它的后继节点的父节点"
        if (parent == node)
        {
            parent = replace;
        }
        else
        {
            // child不为空
            if (child)
                rb_set_parent(child, parent);
            parent->left = child;

            replace->right = node->right;
            rb_set_parent(node->right, replace);
        }

        replace->parent = node->parent;
        replace->color = node->color;
        replace->left = node->left;
        node->left->parent = replace;

        if (color == BLACK)
            removeFixUp(root, child, parent);

        delete node;
        return;
    }

    if (node->left != NULL)
        child = node->left;
    else
        child = node->right;

    parent = node->parent;
    // 保存"取代节点"的颜色
    color = node->color;

    if (child)
        child->parent = parent;

    // "node节点"不是根节点
    if (parent)
    {
        if (parent->left == node)
            parent->left = child;
        else
            parent->right = child;
    }
    else
        root = child;

    if (color == BLACK)
        removeFixUp(root, child, parent);
    delete node;
}

template <typename T, typename func>
void RBTree<T, func>::remove(T key)
{
    RBTNode<T>* node;

    // 查找key对应的节点(node)，找到的话就删除该节点
    if ((node = search(mRoot, key)) != NULL)
        remove(mRoot, node);
    sz--;
}

template <typename T, typename func>
void RBTree<T, func>::destroy(RBTNode<T>*& tree)
{
    if (tree == NULL)
        return;

    if (tree->left != NULL)
        return destroy(tree->left);
    if (tree->right != NULL)
        return destroy(tree->right);

    delete tree;
    tree = NULL;
}

template <typename T, typename func>
void RBTree<T, func>::destroy()
{
    destroy(mRoot);
}
