#include "observer.h"
#include "xwindow.h"
#include "enumerations.h"
#include "square.h"
#include "chessboard.h"
#include "chesspiece.h"
#include <string>
#include <vector>

using namespace std;

class GraphicDisplay : public Observer {
   Xwindow xw;

    public:
        GraphicDisplay();
        void notify(vector<Square*>& updatedSquares, ChessBoard& board) override;
        SubscriptionType getSubType() override;

};
