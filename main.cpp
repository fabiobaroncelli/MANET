/*
 * main.cc
 * Copyright (C) Fabio Baroncelli 2010 <fabio@>
 */

#include <iostream>
#include "manet.h"
#include "mainwindow.h"
#include <QApplication>

int main(int argc, char **argv)
{
 // Q_INIT_RESOURCE(application);

  QApplication app(argc, argv);
  MainWindow mainWin;
  mainWin.show();
  return app.exec();
}
