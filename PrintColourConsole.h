#pragma once

#pragma once
#include <QTextStream>
#include <QCoreApplication>
#include "Algebra_node.h"

void Print_Tree_R_ColoredSelectNode(Algebra_Node const* node, Algebra_Node* const selectedNode, std::string const prefix, bool root, bool last);
void PrintColorText(const QString& text, Qt::GlobalColor color);
void PrintLineWithColorRed(QString expr, QSet<int> f_box);
