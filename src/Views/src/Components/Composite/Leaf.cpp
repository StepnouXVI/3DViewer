#include <Views/Components/Composite/Leaf.h>

Leaf::Leaf(QWidget *parent) : Component(parent) {}

bool Leaf::isComposite() const { return false; }

void Leaf::addWidget(QWidget *) {}
