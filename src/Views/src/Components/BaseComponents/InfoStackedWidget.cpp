#include <Views/Components/BaseComponents/InfoStackedWidget.h>

InfoStackedWidget::InfoStackedWidget(const QVector<QString> &titles,
                                     QWidget *parent)
    : titles_(titles), stackedWidget_(new StackedWidget(this)) {
  setParent(parent);
  setFixedWidth(320);
  stackedWidget_->setObjectName("info_stacked_widget");

  connect(stackedWidget_, &StackedWidget::pageChanged,
          [this](int) { emit pageChanged(activePage_); });
}

InfoStackedWidget::InfoStackedWidget(EntityInfo *entityInfo, QWidget *parent)
    : InfoStackedWidget(entityInfo->getTitles(), parent) {
  if (entityInfo->getData().size() == 0) {
    setDefaultPage();
  } else {
    for (const auto &it : entityInfo->getData()) {
      addPage(it);
    }
  }

  connect(entityInfo, &EntityInfo::dataAdded, this,
          &InfoStackedWidget::addPage);
}

void InfoStackedWidget::setSpeed(int speed) { stackedWidget_->setSpeed(speed); }

void InfoStackedWidget::setButtons(Button *prev, Button *next) {
  stackedWidget_->setButtons(prev, next);
}

void InfoStackedWidget::setDefaultPage() {
  addPage({QVector<QString>(titles_.size(), "none")});
  isDefaultPage_ = true;
}

StackedWidget *InfoStackedWidget::getStackedWidget() { return stackedWidget_; }

void InfoStackedWidget::addPage(const QVector<QString> &data) {
  if (isDefaultPage_ == true) {
    isDefaultPage_ = false;
    removePage(0);
  }
  int dataSize = data.size();

  if (dataSize != titles_.size()) {
    throw std::runtime_error(
        "Data size is not equal to InfoStackedWidget size.");
  }

  QVector<Component *> rows(dataSize);

  for (int i = 0; i < dataSize; ++i) {
    rows[i] = ConcreteCompositor::getRow(
        {getTitleLabel(titles_[i]), getDataLabel(data[i])});
    rows[i]->setObjectName("info_stacked_widget_items");
  }

  Composite *page =
      ConcreteCompositor::getPage(rows, 0, spacing, 0, spacing, 0);
  stackedWidget_->addWidget(page);
  setFixedHeight(page->height());

  stackedWidget_->slideToIndex(count() - 1);
}

Component *InfoStackedWidget::getTitleLabel(const QString &title) {
  return Builder::getLabel(title, Qt::AlignLeft | Qt::AlignVCenter);
}

void InfoStackedWidget::resizeEvent(QResizeEvent *) {
  stackedWidget_->resize(size());
}

Component *InfoStackedWidget::getDataLabel(const QString &data) {
  return Builder::getLabel(data, Qt::AlignRight | Qt::AlignVCenter);
}

int InfoStackedWidget::count() { return stackedWidget_->count(); }

void InfoStackedWidget::removePage(const int &index) {
  stackedWidget_->removePage(index);
}

void InfoStackedWidget::setEnabled(bool enabled) {
  stackedWidget_->setEnabled(enabled);
}
