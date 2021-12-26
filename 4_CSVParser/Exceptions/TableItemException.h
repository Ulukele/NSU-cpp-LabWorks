#include "BaseException.h"

namespace Exceptions {
    class TableItemException : public BaseException {
    public:
        TableItemException(int row, int column) : BaseException(
                "Error while parsing, row: " + std::to_string(row) + ", column: " + std::to_string(column)
                ) {}
    };
}