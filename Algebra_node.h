#pragma once

#ifndef ALGEBRA_NODE_H
#define ALGEBRA_NODE_H
#include <deque>
#include <QVector>
#include <QStack>
#include <iterator>
#include <QSet>
#include "Token.h"
#include "Enumerate.h"
#include "Shunting_yard.h"


static std::string ch_hor = "-", ch_ver = "|", ch_ddia = "/", ch_rddia = "\\", ch_udia = "\\", ch_ver_hor = "|-", ch_udia_hor = "\\-", ch_ddia_hor = "/-", ch_ver_spa = "| ";

enum LR {
    LEFT, //ëåâûé ïîòîìîê äîáàâèòü
    RIGHT, // ïðàâûé ïîòîìîê äîáàâèòü
    TOP,  // ýëåìåíò â êîðíå
    ONE   // îïåðàòîð ñ îäíèì àðãóìåíòîì
};

class Debug_concept
{
public:
    Debug_concept();
    Debug_concept(int index);
    int index;
    int call_order; // Óðîâåíü âûçîâà â ïðîèçâîäíîé.
    QMap<int, QSet<int>> colored;
    QSet<int> red; // Óçëû â êîòîðûõ íåâåðíî âû÷èñëåíà ïðîèçâîäíàÿ.
    QSet<int> orange; // Óçëû íå÷åòíîãî óðîâíÿ.
    QSet<int> white; // Óçëû ÷åòíîãî óðîâíÿ.
};

class Algebra_Node {
public:
    Token data;
    Algebra_Node* left;
    Algebra_Node* right;
    Algebra_Node();
    ~Algebra_Node();
    Algebra_Node(const Token& data, Algebra_Node* left = nullptr, Algebra_Node* right = nullptr);
    Algebra_Node(const Token& data, Debug_concept& W, Algebra_Node* left = nullptr, Algebra_Node* right = nullptr);
    QString toString();
    void addLeftNode(Algebra_Node* Q);
    void addRightNode(Algebra_Node* Q);

};

class Algebra_Tree {
private:
    Algebra_Node* root;
    Algebra_Node* CloneTree(Algebra_Node* root);
public:
    QVector<Token> polish;
    bool Is_Algebric(); // Â äåðåâå ìîãóò ïðèñóòñâîâàòü àëãåáðàè÷åñêèå âûðàæåíèÿ.
    bool Is_Numeric(); // Â äåðåâå ïðèñóòñòâóþò òîëüêî ÷èñëà.
    Algebra_Tree() { this->root = nullptr; }
    Algebra_Tree(Algebra_Node* node);
    Algebra_Tree& CopyTree();
    Algebra_Tree& AddSubtree(Algebra_Node* node, LR lr);
    Algebra_Tree& SetIndexTree_T();
    void FindValueD_T(QString c, QVector<QVector<QChar>>& paths);
    void FindValueW_T(QString c, QVector<QVector<QChar>>& paths);
    void Print_Tree_T();
    void TreeToPolish_T();
    Algebra_Tree& TreeExprReplaceD_T(QString c, QVariant value);
    Algebra_Tree& TreeExprReplaceW_T(QString c, QVariant value);
    void TreeRExprReplaceOnSubTreeD_T(QString c, Algebra_Node* second);
    void TreeRExprReplaceOnSubTreeW_T(QString c, Algebra_Node* second);
    void TreeRExprReplaceOnSubTreeD_T(QString c, Algebra_Node* second, Debug_concept& W);
    void TreeRExprReplaceOnSubTreeW_T(QString c, Algebra_Node* second, Debug_concept& W);
    double FunctionValue_T(double value, QString symbol);
    QString TreeToInfix_T();
    Algebra_Tree operator+(const Algebra_Tree& other);
    Algebra_Tree operator-(const Algebra_Tree& other);
    Algebra_Tree operator*(const Algebra_Tree& other);
    Algebra_Tree operator/(const Algebra_Tree& other);
    Algebra_Tree operator^(const Algebra_Tree& other);
    typedef Algebra_Tree iterator;
    ~Algebra_Tree();


};


void BypassTreeD(Algebra_Node* root);
void BypassTreeW(Algebra_Node* root);
void Print_Tree_R(Algebra_Node const* node, std::string const prefix, bool root, bool last);
void Print_Tree_Selected_R(Algebra_Node const* node, Algebra_Node* const selectedNode, QString const& prefix, bool root, bool last);
void Print_Tree(Algebra_Node const* node, QString const& prefix, bool root, bool last);
void Print_Tree_R_ColoredSelectNode(Algebra_Node const* node, Algebra_Node* const selectedNode, QString const& prefix, bool root, bool last);
void FindValueW(Algebra_Node* root, QString c, QVector<QVector<char>>& paths);
void FindValueD(Algebra_Node* root, QString c, QVector<QVector<char>>& paths);
Algebra_Node* TreeExprReplaceR(Algebra_Node* root, QString c, QVariant s);
Algebra_Node* TreeExprReplaceW(Algebra_Node* root, QString c, QVariant s);
Algebra_Node* TreeExprReplaceD(Algebra_Node* root, QString c, QVariant s);
bool CompareTrees(Algebra_Node* root1, Algebra_Node* root2);
Algebra_Node* GetOperand(Algebra_Node* root, LR lr);

Algebra_Node* PolishToTree(std::deque<Token> fh);
void TreeToPolish(Algebra_Node* root, QVector<Token>& kh);
void TreeToPolish(Algebra_Node* root, std::deque<Token>& kh);

Algebra_Node* SetNode(QChar c);
Algebra_Node* SetNode(const int m);
Algebra_Node* SetNode(const double m);
Algebra_Node* SetNode(QString s);
Algebra_Node* SetNode(const int m, int& index);
Algebra_Node* SetNode(const double m, int& index);
Algebra_Node* SetNode(QString s, int& index);


Algebra_Tree& SetAlgebricTree(QString s);
Algebra_Node* SetOperatorTree(QString s);
Algebra_Node* SetOperatorTree(QString s, int& index);

Algebra_Node* TreeRExprReplaceOnSubTreeD(Algebra_Node* first, QString c, Algebra_Node* second);
Algebra_Node* TreeRExprReplaceOnSubTreeW(Algebra_Node* first, QString c, Algebra_Node* second);
Algebra_Node* TreeRExprReplaceOnSubTreeD(Algebra_Node* first, QString c, Algebra_Node* second, Debug_concept& W);
Algebra_Node* TreeRExprReplaceOnSubTreeW(Algebra_Node* first, QString c, Algebra_Node* second, Debug_concept& W);

double FunctionValueM(QString expr, QMap<QString, double>& ds);

Algebra_Node* TreeExprReplaceR(Algebra_Node* root, QString c, QVariant s);

Algebra_Node* _CloneTree(Algebra_Node* root);
Algebra_Node* _CloneTree(Algebra_Node* root, Debug_concept& W);

template<typename T>
void _FindValueD(Algebra_Node* root, T c, QVector<QVector<QChar>>& paths);

QString TreeToInfix(Algebra_Node* root);
void RecursiveDestructor(Algebra_Node* root);

#endif

