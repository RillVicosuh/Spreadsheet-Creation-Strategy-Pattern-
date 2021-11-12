#ifndef _SPREADSHEET_TEST_HPP
#define _SPREADSHEET_TEST_HPP

#include "gtest/gtest.h"
#include "select.hpp"
#include "spreadsheet.cpp"


#endif //_SPREADSHEET_TEST_HPP

TEST(SelectContains, test) {
Spreadsheet sheet;
sheet.set_column_names({"First","Last","Age","Major"});
sheet.add_row({"Amanda","Andrews","22","business"});
sheet.add_row({"Brian","Becker","21","computer science"});
sheet.add_row({"Carol","Conners","21","computer science"});
sheet.add_row({"Joe","Jackson","21","mathematics"});
sheet.add_row({"Sarah","Summers","21","computer science"});
sheet.add_row({"Diane","Dole","20","computer engineering"});
sheet.add_row({"David","Dole","22","electrical engineering"});
sheet.add_row({"Dominick","Dole","22","communications"});
sheet.add_row({"George","Genius","9","astrophysics"});
std::stringstream s;
sheet.set_selection(new Select_Contains(&sheet, "First","Amanda"));
sheet.print_selection(s);
EXPECT_EQ("Amanda Andrews 22 business \n", s.str());
}

TEST(SelectOr, test) {
Spreadsheet sheet;
sheet.set_column_names({"First","Last","Age","Major"});
sheet.add_row({"Amanda","Andrews","22","business"});
sheet.add_row({"Brian","Becker","21","computer science"});
sheet.add_row({"Carol","Conners","21","computer science"});
sheet.add_row({"Joe","Jackson","21","mathematics"});
sheet.add_row({"Sarah","Summers","21","computer science"});
sheet.add_row({"Diane","Dole","20","computer engineering"});
sheet.add_row({"David","Dole","22","electrical engineering"});
sheet.add_row({"Dominick","Dole","22","communications"});
sheet.add_row({"George","Genius","9","astrophysics"});
std::stringstream s;
sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "Last", "rews"), new Select_Contains(&sheet, "Major", "art")));
sheet.print_selection(s);
EXPECT_EQ("Amanda Andrews 22 business \n", s.str());
}

TEST(SelectOr, multipleTest) {
Spreadsheet sheet;
sheet.set_column_names({"First","Last","Age","Major"});
sheet.add_row({"Amanda","Andrews","22","business"});
sheet.add_row({"Brian","Becker","21","computer science"});
sheet.add_row({"Carol","Conners","21","computer science"});
sheet.add_row({"Joe","Jackson","21","mathematics"});
sheet.add_row({"Sarah","Summers","21","computer science"});
sheet.add_row({"Diane","Dole","20","computer engineering"});
sheet.add_row({"David","Dole","22","electrical engineering"});
sheet.add_row({"Dominick","Dole","22","communications"});
sheet.add_row({"George","Genius","9","astrophysics"});
std::stringstream s;
sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "Last", "rews"), new Select_Contains(&sheet, "Major", "mathematics")));
sheet.print_selection(s);
EXPECT_EQ("Amanda Andrews 22 business \n" "Joe Jackson 21 mathematics \n", s.str());
}

TEST(SelectOr, CapitalsTest) {
Spreadsheet sheet;
sheet.set_column_names({"First","Last","Age","Major"});
sheet.add_row({"Amanda","Andrews","22","business"});
sheet.add_row({"Joe","Jackson","21","mathematics"});
std::stringstream s;
sheet.set_selection(new Select_Or(new Select_Contains(&sheet, "Last", "REWS"), new Select_Contains(&sheet, "Major", "mathematics")));
sheet.print_selection(s);
EXPECT_EQ("Joe Jackson 21 mathematics \n", s.str());
}
