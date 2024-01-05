#pragma once

#include <Views/Components/Composite/Composite.h>
#include <Views/lib/AnchorLayout/AnchorLayout.h>

#include <QVector>

class ConcreteCompositor {
 public:
  struct AnchorLines {
    AnchorLine *left;
    AnchorLine *top;
    AnchorLine *right;
    AnchorLine *bottom;
  };

  static Composite *getRow(const QVector<Component *> &components,
                           int spacing = spacing_, int left = 0, int top = 0,
                           int right = 0, int bottom = 0);
  static Composite *getBlock(const QVector<Component *> &components,
                             int spacing = spacing_, int left = 0, int top = 0,
                             int right = 0, int bottom = 0);
  static Composite *getPage(const QVector<Component *> &components,
                            int spacing = spacing_ * 2, int left = spacing_,
                            int top = spacing_, int right = spacing_,
                            int bottom = spacing_);
  static Composite *getLayout(const QVector<Component *> &components,
                              Qt::Orientation orientation, int spacing = 0,
                              int left = 0, int top = 0, int right = 0,
                              int bottom = 0);

  static AnchorLayout *anchor(Component *widget, AnchorLines lines,
                              QMargins margins = {0, 0, 0, 0});

 private:
  static const int spacing_ = 15;
};
