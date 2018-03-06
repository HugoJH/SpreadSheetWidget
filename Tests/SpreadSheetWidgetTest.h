#ifndef TST_TESTSPREADSHEETWIDGET_H
#define TST_TESTSPREADSHEETWIDGET_H

#include "suite.h"

class SpreadSheetWidgetTest : public TestSuite
{
      Q_OBJECT

   public:
      SpreadSheetWidgetTest();
      using TestSuite::TestSuite;
   private slots:
      void testDynamicRowPopulation();
};

#endif // TST_TESTSPREADSHEETWIDGET_H
