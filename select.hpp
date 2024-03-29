#ifndef __SELECT_HPP__
#define __SELECT_HPP__

#include <cstring>
#include <iostream>
#include <string>
#include "spreadsheet.hpp"
using namespace std;
class Select
{
public:
    virtual ~Select() = default;

    // Return true if the specified row should be selected.
    virtual bool select(const Spreadsheet* sheet, int row) const = 0;
};

// A common type of criterion for selection is to perform a comparison based on
// the contents of one column.  This class contains contains the logic needed
// for dealing with columns. Note that this class is also an abstract base
// class, derived from Select.  It introduces a new select function (taking just
// a string) and implements the original interface in terms of this.  Derived
// classes need only implement the new select function.  You may choose to
// derive from Select or Select_Column at your convenience.
class Select_Column: public Select
{
protected:
    int column;
public:
    Select_Column(const Spreadsheet* sheet, const std::string& name)
    {
        column = sheet->get_column_by_name(name);
    }

    virtual bool select(const Spreadsheet* sheet, int row) const
    {
        return select(sheet->cell_data(row, column));
    }

    // Derived classes can instead implement this simpler interface.
    virtual bool select(const std::string& s) const = 0;
};

class Select_Contains: public Select_Column {
  private:
    string item;
  public:
    Select_Contains(const Spreadsheet* sheet, const string& temp, const string& temp2) : Select_Column(sheet, temp) {
        item = temp2;
    }

    virtual bool select(const string& s) const {
        if(s.find(item) != string::npos){
            return true;
        }
        else{
            return false;
        }
    }
};

class Select_And: public Select{
  private:
    Select* select1;
    Select* select2;
  public:
    Select_And(Select* select1_, Select* select2_){
      select1 = select1_;
      select2 = select2_;
    }
    virtual bool select(const Spreadsheet* sheet, int row) const{
      bool x = select1->select(sheet, row);
      bool y = select2->select(sheet, row);
      return (x&&y);
    }
    ~Select_And(){
      delete select1;
      delete select2;
      select1 = nullptr;
      select2 = nullptr;
    }
};
#endif //__SELECT_HPP__
