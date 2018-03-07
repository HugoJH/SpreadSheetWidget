#include "SpreadSheetWidget.h"
#include <QKeyEvent>
SpreadSheetWidget::SpreadSheetWidget(QWidget *parent) :
   QTableWidget(parent)
{
}

void SpreadSheetWidget::keyPressEvent(QKeyEvent* event)
{
   if (event->matches(QKeySequence::Copy))
   {
      copyCells();
   }
   else if (event->matches(QKeySequence::Cut))
   {
      cutCells();
   }
   else if (event->matches(QKeySequence::Paste))
   {
      pasteCells();
   }
   else if (event->matches(QKeySequence::Delete))
   {
      deleteCells();
   }
   else
   {
      QTableWidget::keyPressEvent(event);
   }
}

void SpreadSheetWidget::copyCells()
{
   clipboard.clear();
   QItemSelectionModel* selection = selectionModel();
   QModelIndexList indexes = selection->selectedIndexes();
   std::sort(indexes.begin(), indexes.end());

   QModelIndex previous = indexes.first();
   indexes.removeFirst();
   QModelIndex current;
   QStringList temp;

   foreach (current, indexes)
   {
      temp << model()->data(previous).toString();
      if (current.row() != previous.row())
      {
         clipboard.push_back(temp);
         temp.clear();
      }
      previous = current;
   }

   temp << model()->data(previous).toString();
   clipboard.push_back(temp);
}

void SpreadSheetWidget::pasteCells()
{
   QStringList temp;
   int row = currentPasteRow();

   if (row ==-1)
   {
      return;
   }

   int col = currentPasteCol();
   int j = row;

   foreach (temp, clipboard)
   {
      for (int x = 0; x < temp.count(); ++x)
      {
         QTableWidgetItem* newItem = new QTableWidgetItem(temp.at(x));
         setItem(j, x + col, newItem);
      }
      temp.clear();
      ++j;
   }
}

void SpreadSheetWidget::cutCells()
{
   copyCells();
   deleteCells();
}

void SpreadSheetWidget::deleteCells()
{
   QTableWidgetItem* item;
   foreach (item, selectedItems())
   {
      item->setText("");
   }
}

int SpreadSheetWidget::currentPasteRow()
{
   if (selectedRanges().length()>1)
      return -1;
   return selectedRanges().at(0).topRow();
}

int SpreadSheetWidget::currentPasteCol()
{
   if (selectedRanges().length()>1)
      return -1;
   return selectedRanges().at(0).leftColumn();
}
