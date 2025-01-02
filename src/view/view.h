#include <WString.h>
#ifndef VIEW_H
#define VIEW_H

class View {
public:
    virtual ~View() = default;
    virtual void setTemp1(const String& temp) = 0;
    virtual void setTemp2(const String& temp) = 0;
    virtual void setPumpMode(const String& temp) = 0;
    // virtual void print() = 0;
};

#endif // VIEW_H