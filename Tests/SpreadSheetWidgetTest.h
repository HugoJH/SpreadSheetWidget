#ifndef TST_TESTSPREADSHEETWIDGET_H
#define TST_TESTSPREADSHEETWIDGET_H

#include "suite.h"
#include "SpreadSheetWidget.h"

class SpreadSheetWidgetTest : public TestSuite
{
      Q_OBJECT

   public:
      SpreadSheetWidgetTest();
      using TestSuite::TestSuite;
   private slots:
      void testCopyAndPaste();
      void testCutAndPaste();
   private:
      QString getSelectionString(const SpreadSheetWidget& spreadSheet);
};

#endif // TST_TESTSPREADSHEETWIDGET_H
