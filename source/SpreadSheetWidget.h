#ifndef SPREADSHEETWIDGET_H
#define SPREADSHEETWIDGET_H

#include <QTableWidget>

class SpreadSheetWidget : public QTableWidget
{
      Q_OBJECT

   public:
      SpreadSheetWidget(QWidget *parent = 0);

   protected:
      void keyPressEvent(QKeyEvent* event);
   private slots:
      void copyCells();
      void pasteCells();
      void cutCells();
      void deleteCells();
   private:
      int currentPasteRow();
      int currentPasteCol();

      QList<QStringList> clipboard;

};

#endif
