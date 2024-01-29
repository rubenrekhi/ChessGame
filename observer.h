#ifndef __OBSERVER_H__
#define __OBSERVER_H__
#include <vector>
#include "enumerations.h"
//#include "square.h"
//#include "chessboard.h"

class Square;
class ChessBoard;

class Observer {
    // public methods
    public:
        virtual void notify(std::vector<Square*>& updatedSquares, ChessBoard& board) = 0;
        virtual SubscriptionType getSubType() = 0;
        virtual ~Observer() = default;
};
#endif
