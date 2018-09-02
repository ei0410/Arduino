#ifndef analogHat_h
#define analogHat_h

class analogHat {
  private:
    int pattern_x, pattern_y;
    int pattern = 0;
    int radius_x, radius_y;
    int radius = 0;
    int split_num;
    float angle;
    float deg, radian;
  public:
    analogHat(int split);
    int get_pattern(int x, int y);
    int get_radius(int x, int y);
};

#endif
