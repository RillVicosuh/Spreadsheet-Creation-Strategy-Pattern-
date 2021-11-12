#ifndef _SPREADSHEET_TEST_HPP
#define _SPREADSHEET_TEST_HPP

#include "gtest/gtest.h"
#include "select.hpp"
#include "spreadsheet.cpp"

TEST(SelectNotTest, RegNotTest){
  Spreadsheet sheet;
  sheet.set_column_names({"First","Last","Age","Major"});
  sheet.add_row({"Brian","Becker","21","computer science"});
  sheet.add_row({"Carol","Conners","21","computer science"});
  sheet.add_row({"Joe","Jackson","21","mathematics"});
  sheet.add_row({"Sarah","Summers","21","computer science"});
  std::stringstream s;
  sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"Major","computer science")));
  sheet.print_selection(s);
  EXPECT_EQ(s.str(), "Joe Jackson 21 mathematics \n");
}

TEST(SelectNotTest, EmptyTest){
  Spreadsheet sheet;
  sheet.set_column_names({"First","Last","Age","Major"});
  sheet.add_row({"Brian","Becker","21","computer science"});
  sheet.add_row({"Carol","Conners","21","computer science"});
  sheet.add_row({"Sarah","Summers","21","computer science"});
  std::stringstream s;
  sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"Major","computer science")));
  sheet.print_selection(s);
  EXPECT_EQ(s.str(), "");
}

TEST(SelectNotTest, UnspecifiedValue){
  Spreadsheet sheet;
  sheet.set_column_names({"First","Last","Age","Major"});
  sheet.add_row({"Brian","Becker","21","computer science"});
  sheet.add_row({"Carol","Conners","21","computer science"});
  sheet.add_row({"Joe","Jackson","21","mathematics"});
  sheet.add_row({"Sarah","Summers","21","computer science"});
  std::stringstream s;
  sheet.set_selection(new Select_Not(new Select_Contains(&sheet,"Last","")));
  sheet.print_selection(s);
  EXPECT_EQ(s.str(), "");
}

#endif //_SPREADSHEET_TEST_HPP
