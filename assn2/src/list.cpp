#include "list.hpp"

bool operator<(const Student &s, const List &list) {
    for (int i = 0; i < list.dept_cnt; i++)
        if (s[i] == list[i].data)
            return true;
    return false
}
