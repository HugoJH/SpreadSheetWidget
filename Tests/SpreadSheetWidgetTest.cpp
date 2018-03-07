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

   QTest::keySequence(&spreadSheet, QKeySequence::Copy);


   spreadSheet.clearSelection();
   spreadSheet.setCurrentCell(11, 0);

   QTest::keySequence(&spreadSheet, QKeySequence::Paste);
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

   QTest::keySequence(&spreadSheet, QKeySequence::Cut);


   spreadSheet.clearSelection();
   spreadSheet.setCurrentCell(11, 0);

   QTest::keySequence(&spreadSheet, QKeySequence::Paste);
   spreadSheet.clearSelection();

   QTableWidgetSelectionRange rangeMid(0, 0, 10, 4);
   spreadSheet.setRangeSelected(rangeMid, true);

   QString selectionStringOrigin = getSelectionString(spreadSheet);

   spreadSheet.clearSelection();

   QTableWidgetSelectionRange rangeAfter(11, 0, 21, 4);
   spreadSheet.setRangeSelected(rangeAfter, true);

   QString selectionStringTarget = getSelectionString(spreadSheet);
   QString expectedOutputTarget = "015\t\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t016\t\t\t\n\t\t\t017\t";
   QString expectedOutputOrigin = "\t\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t";

   QCOMPARE(selectionStringOrigin, expectedOutputOrigin);
   QCOMPARE(selectionStringTarget, expectedOutputTarget);
}

void SpreadSheetWidgetTest::testDelete()
{
   SpreadSheetWidget spreadSheet;

   spreadSheet.setFixedWidth(600);
   spreadSheet.setFixedHeight(480);

   spreadSheet.setColumnCount(50);

   spreadSheet.setRowCount(50);

   spreadSheet.setItem(0, 0, new QTableWidgetItem("015"));
   spreadSheet.setItem(9, 2, new QTableWidgetItem("016"));
   spreadSheet.setItem(10, 4, new QTableWidgetItem("017"));

   QTableWidgetSelectionRange range(0, 0, 10, 4);
   spreadSheet.setRangeSelected(range, true);

   QTest::keySequence(&spreadSheet, QKeySequence::Delete);

   QString selectionString = getSelectionString(spreadSheet);
   QString expectedOutput = "\t\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t\n\t\t\t\t";

   QCOMPARE(selectionString, expectedOutput);
}

QString SpreadSheetWidgetTest::getSelectionString(const SpreadSheetWidget& spreadSheet)
{
   QAbstractItemModel* model = spreadSheet.model();
   QItemSelectionModel* selection = spreadSheet.selectionModel();
   QModelIndexList indexes = selection->selectedIndexes();

   QString selected_text;
   QModelIndex previous = indexes.first();

   foreach(QModelIndex current, indexes)
   {
      QVariant data = model->data(current);
      QString text = data.toString();
      selected_text.append(text);

      if (current.row() != previous.row())
      {
         selected_text.append('\n');
      }
      else
      {
         selected_text.append('\t');
      }
      previous = current;
   }
   return selected_text;
}

static SpreadSheetWidgetTest SWTest;



