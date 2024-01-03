#include <Views/Components/Composite/ConcreteCompositor.h>

Composite *ConcreteCompositor::getRow(const QVector<Component *> &components,
                                      int spacing, int left, int top, int right,
                                      int bottom) {
  int maxHeight = components[0]->height();
  for (const auto &it : components) {
    if (it->height() > maxHeight) {
      maxHeight = it->height();
    }
  }

  Composite *row =
      getLayout(components, Qt::Horizontal, spacing, left, top, right, bottom);
  row->setFixedHeight(maxHeight);

  return row;
}

Composite *ConcreteCompositor::getBlock(const QVector<Component *> &components,
                                        int spacing, int left, int top,
                                        int right, int bottom) {
  Composite *block =
      getLayout(components, Qt::Vertical, spacing, left, top, right, bottom);

  int height = 0;
  for (const auto &it : components) {
    height += it->height();
  }

  block->setFixedHeight(height + spacing * (components.size() - 1));

  return block;
}

Composite *ConcreteCompositor::getPage(const QVector<Component *> &components,
                                       int spacing, int left, int top,
                                       int right, int bottom) {
  Composite *page =
      getLayout(components, Qt::Vertical, spacing, left, top, right, bottom);

  int height = 0;
  for (const auto &it : components) {
    height += it->height();
  }

  page->setFixedHeight(height + top + bottom +
                       spacing * (components.size() - 1));
  return page;
}

Composite *ConcreteCompositor::getLayout(const QVector<Component *> &components,
                                         Qt::Orientation orientation,
                                         int spacing, int left, int top,
                                         int right, int bottom) {
  Composite *layout = new Composite(orientation);
  layout->setSpacing(spacing);
  layout->setMargins(QMargins(left, top, right, bottom));

  for (const auto &it : components) {
    layout->addWidget(it);
  }
  return layout;
}

AnchorLayout *ConcreteCompositor::anchor(Component *widget, AnchorLines lines,
                                         QMargins margins) {
  AnchorLayout *main = AnchorLayout::get(widget);

  main->top()->anchorTo(lines.top)->setMargin(margins.top());
  main->bottom()->anchorTo(lines.bottom)->setMargin(margins.bottom());
  main->right()->anchorTo(lines.right)->setMargin(margins.right());
  main->left()->anchorTo(lines.left)->setMargin(margins.left());

  return main;
}
