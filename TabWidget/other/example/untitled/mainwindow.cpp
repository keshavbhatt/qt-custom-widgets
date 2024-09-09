#include "mainwindow.h"
#include "fancytabwidget.h"
#include "ui_mainwindow.h"
#include <QIcon>
#include <QLabel>
#include <QLatin1String>
#include <QLayout>
#include <QTabBar>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);

  FancyTabWidget *tabWidget = new FancyTabWidget(
      this, QIcon::fromTheme(QLatin1String("list-add-symbolic.symbolic")));

  QTabBar *tabBar = tabWidget->tabBar();
  tabBar->setTabsClosable(true);
  tabBar->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
  tabBar->setMovable(true);
  connect(tabBar, &QTabBar::tabCloseRequested, this,
          [=](int index) { tabWidget->removeTab(index); });

  connect(tabWidget, &FancyTabWidget::tabAddRequested, [=]() {
    auto index = tabWidget->count() + 1;
    auto nIndex = tabWidget->addTab(
        new QLabel(QString("Hello World from tab %1").arg(index)),
        "Tab " + QString::number(index));
    tabWidget->setCurrentWidget(tabWidget->widget(nIndex));
  });

  tabWidget->addTab(new QLabel("Hello World"), "Tab");

  this->centralWidget()->layout()->addWidget(tabWidget);
}

MainWindow::~MainWindow() { delete ui; }
