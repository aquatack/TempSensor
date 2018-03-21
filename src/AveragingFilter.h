class AveragingFilter {
    static const int AVERAGECOUNT = 60;
    float measurements[AVERAGECOUNT];
    int measurementIndex;
public:
    AveragingFilter() : measurementIndex(AVERAGECOUNT) {};
    void Add(float measurement);
    float GetAverage();
    int Length();
    bool Full();
};
