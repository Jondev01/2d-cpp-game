#include <vector>
using namespace std;
class Level{
public:
    Level(char* path, int w, int h, int X, int Y); //X, Y  starting in lower left corner. X start from 0, Y start from 1
    char* fileName;
    vector<int> levelMap;
    int width;
    int height;
    int startX;
    int startY;
    int target_time;
    void ReadMap();
};
