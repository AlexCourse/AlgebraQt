#include "Algebra_node.h"
#include <QString>
#include <QQueue>
#include <QSet>
#include <algorithm>
#define DEBUG 1

using namespace std;

Algebra_Node::Algebra_Node(const Token& data, Algebra_Node* left, Algebra_Node* right)
    : data(data), left(left), right(right) {}

Algebra_Node::Algebra_Node(const Token& data, Debug_concept& W, Algebra_Node* left, Algebra_Node* right)
    : data(SetToken(data.GetValue())), left(left), right(right) {}

Algebra_Node::Algebra_Node()
{
    Token T = _SetToken("0");
    this->data = Token(T);
    this->left = nullptr;
    this->right = nullptr;
}

Algebra_Node::~Algebra_Node() {
    data.~Token();
    delete left;
    delete right;
}


QString Algebra_Node::toString() {
    return data.value.toString();
}

void Algebra_Node::addLeftNode(Algebra_Node* Q) {
    this->left = Q;
}

void Algebra_Node::addRightNode(Algebra_Node* Q) {
    this->right = Q;
}

Debug_concept::Debug_concept() : index(0), call_order(0) {}

Debug_concept::Debug_concept(int index) : index(index), call_order(0) {}

void Print_Tree_R(Algebra_Node const* node, string const prefix = " ", bool root = true, bool last = true) {
    cout << prefix << (root ? "" : (last ? ch_udia_hor : ch_ver_hor));
    cout << (node ? ToString(node->data.value) : "") << endl;
    if (!node || (!node->left && !node->right))
        return;
    vector<Algebra_Node*> v{ node->left, node->right };
    for (size_t i = 0; i < v.size(); ++i)
        Print_Tree_R(v[i], prefix + (root ? "" : (last ? "  " : ch_ver_spa)), false, i + 1 >= v.size());
}

Algebra_Node* PolishToTree(deque<Token> fh) {
    QVector<Algebra_Node*> fs;
    for (Token p : fh) {
        Algebra_Node* T = new Algebra_Node(p);
        fs.push_back(T);
    }
    std::reverse(fs.begin(), fs.end());
    QStack<Algebra_Node*> st;
    Algebra_Node* T = nullptr;
    while (!fs.empty()) {
        T = fs.back();
        fs.pop_back();
        if (f_arg(T->data)) {
            st.push(T);
        }
        else if (f_opr_two(T->data)) {
            Algebra_Node* p = st.top();
            st.pop();
            Algebra_Node* q = st.top();
            st.pop();
            T->addRightNode(p);
            T->addLeftNode(q);
            st.push(T);
        }
        else if (f_opr_one(T->data)) {
            Algebra_Node* q = st.top();
            st.pop();
            T = new Algebra_Node(T->data);
            T->addLeftNode(q);
            st.push(T);
        }
    }
    return T;
}

template <typename T>
void _ReverseVector(QVector<T>& fh)
{
    int start = 0;
    int end = fh.size() - 1;

    while (start < end) {
        std::swap(fh[start], fh[end]);
        start++;
        end--;
    }
}

template <typename T>
QVector<T> ReverseVector(QVector<T>& fh) {
    QVector<T> kh;
    typename QVector<T>::reverse_iterator iter;

    for (iter = fh.rbegin(); iter != fh.rend(); ++iter) {
        T elem = *iter;
        kh.push_back(elem);
    }

    return kh;
}

template <typename T>
deque<T> ReverseVector(deque<T>& fh) {
    deque<T> kh;
    typename deque<T>::reverse_iterator iter;

    for (iter = fh.rbegin(); iter != fh.rend(); ++iter) {
        T elem = *iter;
        kh.push_back(elem);
    }
    return kh;
}
// ========================================================================================================================

void BypassTreeD(Algebra_Node* root) {
    if (root == nullptr)
        return;

    QStack<Algebra_Node*> st;
    st.push(root);

    while (!st.empty()) {
        Algebra_Node* currentNode = st.top();
        st.pop();

        cout << currentNode->data << " ";

        if (currentNode->right)
            st.push(currentNode->right);
        if (currentNode->left)
            st.push(currentNode->left);
    }
}

void BypassTreeW(Algebra_Node* root) {
    if (root == nullptr) {
        return;
    }

    QQueue<Algebra_Node*> fs;
    fs.push_back(root);

    while (!fs.empty()) {
        Algebra_Node* currentNode = fs.front();
        fs.pop_front();

        cout << currentNode->data << " ";

        if (currentNode->left != nullptr) {
            fs.push_back(currentNode->left);
        }

        if (currentNode->right != nullptr) {
            fs.push_back(currentNode->right);
        }
    }
}

void Print_stack(QStack<QChar> st)
{
    QStack<QChar> sq = st;
    while (sq.empty()) {
        qDebug() << sq.top() << " ";
        sq.pop();
    }
}

void FindValueD(Algebra_Node* root, QString c, QVector<QVector<QChar>>& paths) { //
    // Ïåðâàÿ ïåðåìåííàÿ - êîðåíü äåðåâà. ñ - èñêîìîå çíà÷åíèå, paths - âñå íàéäåííûå ïóòè â äåðåâå äëÿ ýòîãî çíà÷åíèÿ.
    if (root == nullptr) {
        return;
    }

    QStack<Algebra_Node*> st;
    QStack<QVector<QChar>> k_st;
    QVector<QChar> track;
    st.push(root);
    track.push_back('0');
    Algebra_Node* currentNode = st.top();
    st.pop();

    while (true) {

        if (CE(currentNode->data.value, c))
        {
            bool B = false;
            if (track.empty())
            {
                track.push_back('0');
                B = true;
            }
            paths.push_back(track);
            if (B)  track.pop_back();
        }
        if (currentNode->left != nullptr) {
            st.push(currentNode->left);
            track.push_back('L');
            QVector<QChar> es;
            es = track; // Вызываем конструктор копирования. !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!1
            k_st.push(es);
            track.pop_back();
        }
        if (currentNode->right != nullptr) {
            st.push(currentNode->right);
            track.push_back('R');
            QVector<QChar> es;
            es = track; // Вызываем конструктор копирования. !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!
            k_st.push(es);
            track.pop_back();
        }
        while (0);
        if (!st.empty())
        {
            currentNode = st.top();
            st.pop();
            track = k_st.top();
            k_st.pop();
        }
        else break;
    }
}


void FindValueW(Algebra_Node* root, QString c, QVector<QVector<QChar>>& paths) { //
    // Ïåðâàÿ ïåðåìåííàÿ - êîðåíü äåðåâà. ñ - èñêîìîå çíà÷åíèå, paths - âñå íàéäåííûå ïóòè â äåðåâå äëÿ ýòîãî çíà÷åíèÿ.
    if (root == nullptr) {
        return;
    }

    QQueue<Algebra_Node*> fs;
    QQueue<QVector<QChar>> k_queue;
    QVector<QChar> track;
    fs.push_back(root);
    track.push_back('0');

    Algebra_Node* currentNode = fs.front();
    fs.pop_front();

    while (true) {

        if (CE(currentNode->data.value, c))
        {
            bool B = false;
            if (track.empty())
            {
                track.push_back('0');
                B = true;
            }
            paths.push_back(track);
            if (B)  track.pop_front();
        }

        if (currentNode->left != nullptr) {
            fs.push_back(currentNode->left);
            track.push_back('L');
            QVector<QChar> es;
            es = track; // Вызываем конструктор копирования.
            k_queue.push_back(es);
            track.pop_front();
        }

        if (currentNode->right != nullptr) {
            fs.push_back(currentNode->right);
            track.push_back('R');
            QVector<QChar> es;
            es = track; // Вызываем конструктор копирования.
            k_queue.push_back(es);
            track.pop_front();
        }
        if (!fs.empty())
        {
            currentNode = fs.front();
            fs.pop_front();
            track = k_queue.front();
            k_queue.pop_front();
        }
        else break;
    }
}

void Algebra_Tree::FindValueD_T(QString c, QVector<QVector<QChar>>& paths)
{
    Algebra_Node* node = this->root;
    FindValueD(node, c, paths);
}

void Algebra_Tree::FindValueW_T(QString c, QVector<QVector<QChar>>& paths)
{
    Algebra_Node* node = this->root;
    FindValueD(node, c, paths);
}


// ===========================================================================================================================
Algebra_Node* TreeExprReplaceR(Algebra_Node* root, QString c, QVariant value) {
    // Âîçâðàùàåò êîïèþ äåðåâà ñ çàìåíåííûìè çíà÷åíèÿìè.
    // root - êîðåíü äåðåâà.
    // c - çíà÷åíèå êîòîðîå çàìåíÿåì.
    // value - çíà÷åíèå , êîòîðûì çàìåíÿåì.
    if (root == nullptr) {
        return nullptr;
    }

    Algebra_Node* newNode = new Algebra_Node();

    if (CE(root->data.value, c)) {
        Token token = SetToken(value);
        newNode = new Algebra_Node(token);
        while (0); // For breakpoint.
    }
    else {
        newNode = new Algebra_Node(root->data);
    }

    newNode->left = TreeExprReplaceR(root->left, c, value);
    newNode->right = TreeExprReplaceR(root->right, c, value);

    return newNode;
}

// =================================================================================================================================


Algebra_Node* TreeExprReplaceD(Algebra_Node* root, QString c, QVariant s) {
    // Âîçâðàùàåò êîïèþ äåðåâà ñ çàìåíåííûìè çíà÷åíèÿìè.
    // root - êîðåíü äåðåâà.
    // c - çíà÷åíèå êîòîðîå çàìåíÿåì.
    // value - çíà÷åíèå , êîòîðûì çàìåíÿåì.
    if (root == nullptr) {
        return nullptr;
    }

    QStack<Algebra_Node*> nodeStack;
    nodeStack.push(root);

    while (!nodeStack.empty()) {
        Algebra_Node* currentNode = nodeStack.top();
        nodeStack.pop();

        if (CE(currentNode->data.value, c)) {
            Token T = SetToken(s);
            currentNode = new Algebra_Node(T);
        }

        if (currentNode->right != nullptr) {
            nodeStack.push(currentNode->right);
        }

        if (currentNode->left != nullptr) {
            nodeStack.push(currentNode->left);
        }
    }

    return root;
}

Algebra_Node* TreeExprReplaceW(Algebra_Node* root, QString c, QVariant value) {
    if (root == nullptr) {
        return nullptr;
    }

    QQueue<Algebra_Node*> nodeQueue;
    nodeQueue.push_back(root);

    while (!nodeQueue.empty()) {
        Algebra_Node* currentNode = nodeQueue.front();
        nodeQueue.pop_front();

        if (CE(currentNode->data.value, c)) {
            Token T = SetToken(value);
            currentNode->data = T;
        }

        if (currentNode->left != nullptr) {
            nodeQueue.push_back(currentNode->left);
        }

        if (currentNode->right != nullptr) {
            nodeQueue.push_back(currentNode->right);
        }
    }

    return root;
}

// ============================================================================================================================================================
Algebra_Tree& Algebra_Tree::TreeExprReplaceD_T(QString c, QVariant value)
{
    const int MODE = 1;
    Algebra_Node* first_root = this->root;
    Algebra_Node* second_root;
    if (MODE == 0) second_root = TreeExprReplaceD(first_root, c, value); // Çàìåíà íåðàáî÷åé ôóíêöèè
    if (MODE == 1) second_root = TreeExprReplaceR(first_root, c, value);
    Algebra_Tree t = Algebra_Tree(second_root);
    return t;
}

Algebra_Tree& Algebra_Tree::TreeExprReplaceW_T(QString c, QVariant value)
{
    const int MODE = 1;
    Algebra_Node* first_root = this->root;
    Algebra_Node* second_root;
    if (MODE == 0) second_root = TreeExprReplaceW(first_root, c, value); // Çàìåíà íåðàáî÷åé ôóíêöèè
    if (MODE == 1) second_root = TreeExprReplaceR(first_root, c, value);
    Algebra_Tree t = Algebra_Tree(second_root);
    return t;
}

// =============================================================================================================================================================

Algebra_Node* _CloneTree(Algebra_Node* root) {
    if (root == nullptr) {
        return nullptr;
    }

    Algebra_Node* newNode = new Algebra_Node(root->data);
    newNode->left = _CloneTree(root->left);
    newNode->right = _CloneTree(root->right);

    return newNode;
}

Algebra_Node* _CloneTree(Algebra_Node* root, Debug_concept& W) {
    if (root == nullptr) {
        return nullptr;
    }

    Algebra_Node* newNode = new Algebra_Node(root->data, W);
    W.index++;
    newNode->left = _CloneTree(root->left, W);
    newNode->right = _CloneTree(root->right, W);

    return newNode;
}

Algebra_Tree& Algebra_Tree::CopyTree() {
    Algebra_Node* node = this->root;
    Algebra_Tree* clonedTree = new Algebra_Tree();
    clonedTree->root = _CloneTree(node);
    return *clonedTree;
}


Algebra_Node* TreeRExprReplaceOnSubTreeD(Algebra_Node* first, QString c, Algebra_Node* second, Debug_concept& W)
{ // Çàìåíà íàéäåííîãî ýëåìåíòà íà ïîääåðåâî.
  // first - êîðåíü äåðåâà ,â êîòîðîì èùåòñÿ ýëåìåíò.
  // ñ - íàéäåííûé ýëåìåíò.
    // second - ïîääåðåâî íà êîòîðîå çàìåíÿåì.
    if (first == nullptr)
        return nullptr;

    QStack<Algebra_Node*> st;
    QStack<QChar> lr_st;
    QStack<Algebra_Node*> parents;
    st.push(first);
    lr_st.push('0');
    parents.push(second);

    while (!st.empty()) {
        Algebra_Node* currentNode = st.top();
        Algebra_Node* parent = parents.top();
        char p = lr_st.top().toLatin1();
        st.pop();
        lr_st.pop();
        parents.pop();

        if (CE(currentNode->data.value, c))
        {
            Algebra_Node& Q = *parent;
            Algebra_Node* C = _CloneTree(second, W);
            if (DEBUG)
            {
                QVector<Token> kh, ks;
                TreeToPolish(C, ks);
                TreeToPolish(second, kh);
                QVector<int> fs, es;
                fs = CountIndex(ks);
                es = CountIndex(kh);
                while (0); // Äëÿ òî÷êè îñòàíîâà.
            }
            if (!(parent == second)) // Åñëè ÿâëÿåòñÿ êîðíåì.
            {
                switch (p)
                {
                    case 'L': { Q.addLeftNode(C); break; }
                    case 'R': { Q.addRightNode(C); break; }
                }
                while (0);
            }
            else first = C; // Ñòàíîâèòñÿ â êîðåíü.
        }

        if (currentNode->left != nullptr)
        {
            lr_st.push('L');
            parents.push(currentNode);
            st.push(currentNode->left);
        }
        if (currentNode->right != nullptr)
        {
            lr_st.push('R');
            parents.push(currentNode);
            st.push(currentNode->right);
        }
    }
    if (DEBUG)
    {
        first = first;
        while (0); // Äëÿ òî÷êè îñòàíîâà.
    }
    return first;
}

Algebra_Node* TreeRExprReplaceOnSubTreeW(Algebra_Node* first, QString c, Algebra_Node* second, Debug_concept& W)
{ // Çàìåíà íàéäåííîãî ýëåìåíòà íà ïîääåðåâî.
  // first - êîðåíü äåðåâà ,â êîòîðîì èùåòñÿ ýëåìåíò.
  // ñ - íàéäåííûé ýëåìåíò.
    // second - ïîääåðåâî íà êîòîðîå çàìåíÿåì.
    if (first == nullptr) {
        return nullptr;
    }

    int n = 0; // ×èñëî çàìåí ïîääåðåâîì.
    QQueue<Algebra_Node*> fs;
    QQueue<QChar> lr_fs;
    QQueue<Algebra_Node*> parents;
    fs.push_back(first);
    lr_fs.push_back('0');
    parents.push_back(first);

    while (!fs.empty()) {
        Algebra_Node* currentNode = fs.front();
        Algebra_Node* parent = parents.front();
        char p = lr_fs.back().toLatin1();
        fs.pop_front();
        lr_fs.pop_front();
        parents.pop_front();

        if (CE(currentNode->data.value, c))
        {
            Algebra_Node& Q = *parent;
            Algebra_Node* C = _CloneTree(second, W);
            if (DEBUG)
            {
                QVector<Token> kh, ks;
                TreeToPolish(C, ks);
                TreeToPolish(second, kh);
                QVector<int> fs, es;
                fs = CountIndex(ks);
                es = CountIndex(kh);
                while (0); // Äëÿ òî÷êè îñòàíîâà.
            }

            if (!(parent == second))
            {
                switch (p)
                {
                   case 'L': { Q.addLeftNode(C); break; }
                   case 'R': { Q.addRightNode(C); break; }
                }
            }
            else first = C;
        }


        if (currentNode->left != nullptr)
        {
            lr_fs.push_back('L');
            parents.push_back(currentNode);
            fs.push_back(currentNode->left);
        }

        if (currentNode->right != nullptr)
        {
            lr_fs.push_back('R');
            parents.push_back(currentNode);
            fs.push_back(currentNode->right);
        }
    }
    return first;
}

Algebra_Node* TreeRExprReplaceOnSubTreeD(Algebra_Node* first, QString c, Algebra_Node* second)
{
    Debug_concept W = Debug_concept();
    Algebra_Node* root = TreeRExprReplaceOnSubTreeD(first, c, second, W);
    return root;
}

Algebra_Node* TreeRExprReplaceOnSubTreeW(Algebra_Node* first, QString c, Algebra_Node* second)
{
    Debug_concept W = Debug_concept();
    Algebra_Node* root = TreeRExprReplaceOnSubTreeW(first, c, second, W);
    return root;
}

void Algebra_Tree::TreeRExprReplaceOnSubTreeD_T(const QString c, Algebra_Node* second)
{
    Debug_concept W = Debug_concept();
    this->TreeRExprReplaceOnSubTreeD_T(c, second, W);
}
void Algebra_Tree::TreeRExprReplaceOnSubTreeW_T(const QString c, Algebra_Node* second)
{
    Debug_concept W = Debug_concept();
    this->TreeRExprReplaceOnSubTreeW_T(c, second, W);
}

bool CompareTrees(Algebra_Node* root1, Algebra_Node* root2) {
    // Ôóíêöèÿ ðåêóðñèâíîãî ñðàâíåíèÿ äâóõ äåðåâüåâ íà ðàâåíñòâî.
    // Åñëè îáà äåðåâà ïóñòû, òî îíè ðàâíû
    if (root1 == nullptr && root2 == nullptr) {
        return true;
    }
    // Åñëè òîëüêî îäíî èç äåðåâüåâ ïóñòî, òî îíè íå ðàâíû
    if (root1 == nullptr || root2 == nullptr) {
        return false;
    }
    // Ñðàâíèâàåì çíà÷åíèÿ óçëîâ è ðåêóðñèâíî ñðàâíèâàåì èõ ïîääåðåâüÿ
    return (root1->data.value == root2->data.value) && CompareTrees(root1->left, root2->left) && CompareTrees(root1->right, root2->right);
}

Algebra_Node* GetOperand(Algebra_Node* root, LR lr)
{
    if (lr == LR::LEFT) return root->left;
    if (lr == LR::RIGHT) return root->right;
}

Algebra_Tree::Algebra_Tree(Algebra_Node* node)
{
    this->root = node;
}

Algebra_Tree Algebra_Tree::operator+(const Algebra_Tree& other)
{
    Algebra_Node* top_node = SetNode('+');
    Algebra_Node* first_root = this->root;
    Algebra_Node* second_root = other.root;
    Algebra_Node* A = _CloneTree(first_root);
    Algebra_Node* B = _CloneTree(second_root);
    top_node->addLeftNode(A);
    top_node->addRightNode(B);
    return Algebra_Tree(top_node);
}

Algebra_Tree Algebra_Tree::operator-(const Algebra_Tree& other)
{
    Algebra_Node* top_node = SetNode('-');
    Algebra_Node* first_root = this->root;
    Algebra_Node* second_root = other.root;
    Algebra_Node* A = _CloneTree(first_root);
    Algebra_Node* B = _CloneTree(second_root);
    top_node->addLeftNode(A);
    top_node->addRightNode(B);
    return  Algebra_Tree(top_node);
}

Algebra_Tree Algebra_Tree::operator*(const Algebra_Tree& other)
{
    Algebra_Node* top_node = SetNode('*');
    Algebra_Node* first_root = this->root;
    Algebra_Node* second_root = other.root;
    Algebra_Node* A = _CloneTree(first_root);
    Algebra_Node* B = _CloneTree(second_root);
    top_node->addLeftNode(A);
    top_node->addRightNode(B);
    return  Algebra_Tree(top_node);
}

Algebra_Tree Algebra_Tree::operator/(const Algebra_Tree& other)
{
    Algebra_Node* top_node = SetNode('/');
    Algebra_Node* first_root = this->root;
    Algebra_Node* second_root = other.root;
    Algebra_Node* A = _CloneTree(first_root);
    Algebra_Node* B = _CloneTree(second_root);
    top_node->addLeftNode(A);
    top_node->addRightNode(B);
    return  Algebra_Tree(top_node);
}

Algebra_Tree Algebra_Tree::operator^(const Algebra_Tree& other)
{
    Algebra_Node* top_node = SetNode('^');
    Algebra_Node* first_root = this->root;
    Algebra_Node* second_root = other.root;
    Algebra_Node* A = _CloneTree(first_root);
    Algebra_Node* B = _CloneTree(second_root);
    top_node->addLeftNode(A);
    top_node->addRightNode(B);
    return  Algebra_Tree(top_node);
}



Algebra_Tree& Algebra_Tree::AddSubtree(Algebra_Node* node, LR lr)
{ // Äîáàâëåíèå ïîääåðåâà ê âûáðàííîìó óçëó:
  // Ïàðàìåòðû - node âûáðàííûé óçåë. lr - êàêîãî íàïðàâëåíèÿ ïîòîìîê çàìåíÿåòñÿ ïîääåðåâîì.
  // Äîáàâëÿåìîå ïîääåðåâî ñîäåðæèòñÿ â òåêóùåì êëàññå.
    Algebra_Tree& second_tree = CopyTree();
    Algebra_Node* second = this->root;
    this->root = node;
    if (lr == LR::LEFT)
    {
        node->left = second;
    }
    if (lr == LR::RIGHT)
    {
        node->right = second;
    }
    return *this;
}


void Algebra_Tree::Print_Tree_T()
{
    Algebra_Node* node = this->root;
    Print_Tree_R(node);
}


void TreeToPolish(Algebra_Node* root, QVector<Token>& kh)
{ // Íà âõîä ïîäàåòñÿ êîðåíü äåðåâà , âîçâðàùàåòñÿ çíà÷åíèå âî âòîðîì ïàðàìåòðå â ôîðìàòå Îáðàòíîé Ïîëüñêîé Íîòàöèè.
    kh.clear();
    if (root == nullptr)
        return;

    QStack<Algebra_Node*> st;
    st.push(root);

    while (!st.empty()) {
        Algebra_Node* currentNode = st.top();
        st.pop();

        kh.push_back(currentNode->data);

        if (currentNode->left)
            st.push(currentNode->left);
        if (currentNode->right)
            st.push(currentNode->right);
    }
    kh = ReverseVector(kh);
    while (0); // Äëÿ òî÷êè îñòàíîâà.
}

void TreeToPolish(Algebra_Node* root, deque<Token>& kh)
{ // Íà âõîä ïîäàåòñÿ êîðåíü äåðåâà , âîçâðàùàåòñÿ çíà÷åíèå âî âòîðîì ïàðàìåòðå â ôîðìàòå Îáðàòíîé Ïîëüñêîé Íîòàöèè.
    kh.clear();
    if (root == nullptr)
        return;

    QStack<Algebra_Node*> st;
    st.push(root);

    while (!st.empty()) {
        Algebra_Node* currentNode = st.top();
        st.pop();

        kh.push_back(currentNode->data);

        if (currentNode->left)
            st.push(currentNode->left);
        if (currentNode->right)
            st.push(currentNode->right);
    }
    kh = ReverseVector(kh);
    while (0); // Äëÿ òî÷êè îñòàíîâà.

}

void Algebra_Tree::TreeToPolish_T()
{
    Algebra_Node* node = this->root;
    QVector<Token> kh = this->polish;
    TreeToPolish(root, kh);
    this->polish = kh;
}



bool Algebra_Tree::Is_Numeric() // Ðåàëèçîâàòü ñ èñïîëüçîâàíèåì èòåðàòîðà ïî äåðåâó.
{
    return true;
}

bool Algebra_Tree::Is_Algebric() // Ðåàëèçîâàòü ñ èñïîëüçîâàíèåì èòåðàòîðà ïî äåðåâó.
{
    return true;
}

Algebra_Node* SetNode(QChar c)
{
    Token token = SetToken(c);
    Algebra_Node* node = new Algebra_Node(token);
    return node;
}

Algebra_Node* SetNode(const int m)
{
    Token token = SetToken(m);
    Algebra_Node* node = new Algebra_Node(token);
    return node;
}

Algebra_Node* SetNode(const double m)
{
    Token token = SetToken(m);
    Algebra_Node* node = new Algebra_Node(token);
    return node;
}

Algebra_Node* SetNode(QString s)
{
    Token token = SetToken(s);
    Algebra_Node* node = new Algebra_Node(token);
    return node;
}

Algebra_Node* SetNode(const int m, int& index)
{
    Token token = SetToken(m);
    Algebra_Node* node = new Algebra_Node(token);
    return node;
}

Algebra_Node* SetNode(const double m, int& index)
{
    Token token = SetToken(m);
    Algebra_Node* node = new Algebra_Node(token);
    return node;
}

Algebra_Node* SetNode(QString s, int& index)
{
    Token token = SetToken(s);
    Algebra_Node* node = new Algebra_Node(token);
    return node;
}



Algebra_Tree& SetAlgebricTree(QString s)
{ // Ôóíêöèÿ íà âõîä ïîëó÷àåì âûðàæåíèå â èíôèêñíîé çàïèñè, à íà âûõîäå äåðåâî àëãåáðàè÷åñêîãî âûðàæåíèÿ.
    deque<Token> fh, eh;
    fh = exprToTokens(s);
    Tokenize_u_minus(fh);
    fh = ReplaceElementInPolish(fh, M_PI, "Pi");
    eh = shuntingYard(fh);
    Algebra_Node* root = PolishToTree(eh);
    Algebra_Tree* tree = new Algebra_Tree(root);
    Algebra_Tree& T = *tree;
    return T;
}

Algebra_Node* SetOperatorTree(QString s, int& index)
{
    deque<Token> fh, eh;
    fh = exprToTokens(s, index, "ORDERING");
    Tokenize_u_minus(fh);
    eh = shuntingYard(fh);
    Algebra_Node* root = PolishToTree(eh);
    return root;
}

Algebra_Node* SetOperatorTree(QString s)
{
    int index = 0;
    Algebra_Node* root = SetOperatorTree(s, index);
    return root;
}


void Algebra_Tree::TreeRExprReplaceOnSubTreeW_T(QString c, Algebra_Node* second, Debug_concept& W)
{
    Algebra_Node* root = this->root;
    TreeRExprReplaceOnSubTreeW(root, c, second, W);
}

void Algebra_Tree::TreeRExprReplaceOnSubTreeD_T(QString c, Algebra_Node* second, Debug_concept& W)
{
    Algebra_Node* root = this->root;
    TreeRExprReplaceOnSubTreeD(root, c, second, W);
}

double FunctionValue(Algebra_Node* root, double value, QString symbol)
{ // Ïîäñòàíîâêà â âûðàæåíèå ôóíêöèè îò õ çàäàííîé äåðåâîì ÷èñëîííîãî çíà÷åíèÿ àðãóìåíòà x.
    const bool LOCAL_DEBUG = false;
    if (LOCAL_DEBUG)
    {
        for (int i = 0; i < 1; i++) cout << endl;
        cout << "FunctionValue() : DEBUG : BEFORE" << endl;
        Print_Tree_R(root);
        for (int i = 0; i < 43; i++) cout << "=";
        for (int i = 0; i < 2; i++) cout << endl;
    }
    Algebra_Node* second_root = TreeExprReplaceR(root, symbol, value);
    if (LOCAL_DEBUG)
    {
        cout << "FunctionValue() : DEBUG : AFTER" << endl;
        Print_Tree_R(second_root);
    }
    deque<Token> kh;
    TreeToPolish(second_root, kh);
    if (LOCAL_DEBUG)
    {
        cout << endl;
        for (Token token : kh) cout << token << " ";
    }
    double r = PolishCalculation(kh);
    return r;
}

double Algebra_Tree::FunctionValue_T(double value, QString symbol)
{
    Algebra_Node* root = this->root;
    double r = FunctionValue(root, value, symbol);
    return r;
}


double FunctionValueM(QString expr, QMap<QString, double>& ds)
{
    Algebra_Node* root = SetOperatorTree(expr);

    QMap<QString, double>::iterator iter;
    for (iter = ds.begin(); iter != ds.end(); ++iter)
    {
        QString p = iter.key();
        root = TreeExprReplaceR(root, p, iter.value());
    }
    Algebra_Tree* T = new Algebra_Tree(root);
    Algebra_Tree& tree = *T;
    if (DEBUG)
    {
        qDebug() << "FunctionValueM() : AFTER";
        tree.Print_Tree_T();
    }
    if (tree.Is_Numeric())
    {
        QVector<Token> kh, ks;
        TreeToPolish(root, kh);
        double r = PolishCalculation(kh);
        delete T;  // Удаляем выделенную память после использования.
        return r;
    }
    else
    {
        qCritical() << "error";
        delete T;  // Удаляем выделенную память после использования.
        return 0;
    }
}

QString TreeToInfix(Algebra_Node* root)
{ // Ïåðåâîä âûðàæåíèÿ çàäàííîãî äåðåâîì â èíôèêñíóþ çàïèñü ýòîãî âûðàæåíèÿ.
    deque<Token> fh, eh;
    TreeToPolish(root, fh);
    QString s = PostfixToInfix(fh);
    return s;
}

QString Algebra_Tree::TreeToInfix_T()
{
    Algebra_Node* root = this->root;
    QString s = TreeToInfix(root);
    return s;
}

Algebra_Node* SetIndexTree(Algebra_Node* root)
{
    if (root == nullptr) {
        return nullptr;
    }

    Algebra_Node* newNode = new Algebra_Node();
    int m = root->data.index;
    Token token = SetToken(m);
    newNode = new Algebra_Node(token);
    while (0); // For breakpoint.

    newNode->left = SetIndexTree(root->left);
    newNode->right = SetIndexTree(root->right);

    return newNode;
}

Algebra_Tree& Algebra_Tree::SetIndexTree_T()
{
    Algebra_Node* root = this->root;
    Algebra_Node* second_root = SetIndexTree(root);
    // Algebra_Tree C = Algebra_Tree(second_root);
    Algebra_Tree* K = new Algebra_Tree(second_root);
    Algebra_Tree& C = *K;
    return C;
}

void deleteBinaryTree(Algebra_Node* node) {
    if (node == nullptr) {
        return;
    }
    // Ðåêóðñèâíî óäàëÿåì ëåâîå è ïðàâîå ïîääåðåâî
    if (node->left != nullptr) deleteBinaryTree(node->left);
    if (node->right != nullptr) deleteBinaryTree(node->right);
    // Óäàëÿåì òåêóùèé óçåë
    node->left = nullptr;
    node->right = nullptr;
    delete node;
}

void RecursiveDestructor(Algebra_Node* root)
{
    deleteBinaryTree(root);
}

Algebra_Tree::~Algebra_Tree()
{
    Algebra_Node* root = this->root;
    RecursiveDestructor(root);
    root = nullptr;
}
