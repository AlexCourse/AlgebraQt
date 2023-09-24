#include "PrintColourConsole.h"
#include <QList>
#include <QSet>
#include <QString>
#include <QDebug>

#include "PrintColourConsole.h"

void PrintColorText(const QString& text, Qt::GlobalColor color)
{
    // Создаем объект QTextStream для вывода текста на консоль
    QTextStream out(stdout);

    // Форматируем текст, чтобы он имел заданный цвет
    QString formattedText = QString("\033[1;%1m%2\033[0m").arg(color).arg(text);

    // Выводим текст на консоль
    std::cout << qPrintable(formattedText) << std::endl;
}

void Print_Tree_R_ColoredSelectNode(Algebra_Node const* node, Algebra_Node* const selectedNode, std::string const prefix, bool root, bool last) {

    std::cout << prefix << (root ? "" : (last ? ch_udia_hor : ch_ver_hor));
    std::string s = "" , t;
    t = ToString(node->data.value);
    if (node) s = t;
    else s = "";
    QString f = QString::fromStdString(s);
    if ( node == selectedNode) PrintColorText(f , Qt::blue);
    else PrintColorText(f , Qt::white);
    if (!node || (!node->left && !node->right))
         return;
    std::vector<Algebra_Node*> v{ node->left, node->right };
    for (size_t i = 0; i < v.size(); ++i)
    Print_Tree_R_ColoredSelectNode(v[i], selectedNode, prefix + (root ? "" : (last ? "  " : ch_ver_spa)), false, i + 1 >= v.size());
}


void PrintLineWithColorRed(QString expr, QSet<int> f_box)
{
    int n = expr.size();
    for (int i = 0; i < n; i++)
    {
        if (f_box.contains(i)) PrintColorText(expr , Qt::red);
        else PrintColorText(expr , Qt::white);
    }
    std::cout << std::endl;
}

