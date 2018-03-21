class MedianFilter
{
private:
    static const int filterDepth = 5;
    float elements[filterDepth];
    float filteredElements[filterDepth];
    int filterIndexer;

    static int cmpfunc(const void* first, const void* second);
public:
    MedianFilter() : filterIndexer(0) {};
    void Initialise(float initTemp);
    float Filter(float nextValue);
};
