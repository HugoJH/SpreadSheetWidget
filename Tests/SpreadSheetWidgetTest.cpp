#include "SpreadSheetWidgetTest.h"

#include <QtTest>
#include <QTableWidgetSelectionRange>

SpreadSheetWidgetTest::SpreadSheetWidgetTest()
{

}

void SpreadSheetWidgetTest::testCopyAndPaste()
{
   SpreadSheetWidget spreadSheet;

   spreadSheet.setFixedWidth(600);
   spreadSheet.setFixedHeight(480);

   spreadSheet.setColumnCount(50);

   spreadSheet.setRowCount(50);

   spreadSheet.setItem(0, 0, new QTableWidgetItem("015"));
   spreadSheet.setItem(9, 2, new QTableWidgetItem("016"));
   spreadSheet.setItem(10, 4, new QTableWidgetItem("017"));

   QTableWidgetSelectionRange rangeBefore(0, 0, 10, 4);
   spreadSheet.setRangeSelected(rangeBefore, true);
   spreadSheet.show();
   QTest::keyClick(&spreadSheet, Qt::Key_C, Qt::ControlModifier);


   spreadSheet.clearSelection();
   spreadSheet.setCurrentCell(11, 0);

   QTest::keyClick(&spreadSheet, Qt::Key_V, Qt::ControlModifier);
   spreadSheet.clearSelection();

   QTableWidgetSelectionRange rangeMid(0, 0, 10, 4);
   spreadSheet.setRangeSelected(rangeMid, true);

   QString selectionStringOrigin = getSelectionString(spreadSheet);

   spreadSheet.clearSelection();

   QTableWidgetSelectionRange rangeAfter(11, 0, 21, 4);
   spreadSheet.setRangeSelected(rangeAfter, true);
   QString selectionStringTarget = getSelectionString(spreadSheet);

   QString expectedOutput = "015\t\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t016\t\t\t\n\t\t\t017\t";
   QCOMPARE(selectionStringOrigin, expectedOutput);
   QCOMPARE(selectionStringTarget, expectedOutput);
}

void SpreadSheetWidgetTest::testCutAndPaste()
{
   SpreadSheetWidget spreadSheet;

   spreadSheet.setFixedWidth(600);
   spreadSheet.setFixedHeight(480);

   spreadSheet.setColumnCount(50);

   spreadSheet.setRowCount(50);

   spreadSheet.setItem(0, 0, new QTableWidgetItem("015"));
   spreadSheet.setItem(9, 2, new QTableWidgetItem("016"));
   spreadSheet.setItem(10, 4, new QTableWidgetItem("017"));

   QTableWidgetSelectionRange rangeBefore(0, 0, 10, 4);
   spreadSheet.setRangeSelected(rangeBefore, true);
   spreadSheet.show();
   QTest::keyClick(&spreadSheet, Qt::Key_X, Qt::ControlModifier);


   spreadSheet.clearSelection();
   spreadSheet.setCurrentCell(11, 0);

   QTest::keyClick(&spreadSheet, Qt::Key_V, Qt::ControlModifier);
   spreadSheet.clearSelection();

   QTableWidgetSelectionRange rangeMid(0, 0, 10, 4);
   spreadSheet.setRangeSelected(rangeMid, true);

   QString selectionStringOrigin = getSelectionString(spreadSheet);

   spreadSheet.clearSelection();

   QTableWidgetSelectionRange rangeAfter(11, 0, 21, 4);
   spreadSheet.setRangeSelected(rangeAfter, true);
   QString selectionStringTarget = getSelectionString(spreadSheet);

   QString expectedOutputTarget = "015\t\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t016\t\t\t\n\t\t\t017\t";
   QString expectedOutputOrigin = "";
   QCOMPARE(selectionStringOrigin, expectedOutputOrigin);
   QCOMPARE(selectionStringTarget, expectedOutputTarget);
}

QString SpreadSheetWidgetTest::getSelectionString(const SpreadSheetWidget& spreadSheet)
{
   QAbstractItemModel* model = spreadSheet.model();
   QItemSelectionModel* selection = spreadSheet.selectionModel();
   QModelIndexList indexes = selection->selectedIndexes();

   QString selected_text;
   // You need a pair of indexes to find the row changes
   QModelIndex previous = indexes.first();
   //indexes.removeFirst();
   foreach(QModelIndex current, indexes)
   {
      QVariant data = model->data(current);
      QString text = data.toString();
      // At this point `text` contains the text in one cell
      selected_text.append(text);
      // If you are at the start of the row the row number of the previous index
      // isn't the same.  Text is followed by a row separator, which is a newline.
      if (current.row() != previous.row())
      {
         selected_text.append('\n');
      }
      // Otherwise it's the same row, so append a column separator, which is a tab.
      else
      {
         selected_text.append('\t');
      }
      previous = current;
   }
   return selected_text;
}

static SpreadSheetWidgetTest SWTest;



