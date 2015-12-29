#ifndef TMINPUTINTERFACE_H
#define TMINPUTINTERFACE_H


class TMInputInterface
{
    public:
        virtual TMInputInterface() {};
        virtual ~TMInputInterface() {};
        virtual std::unordered_set<char> getAlphabet();
        virtual void setAlphabet(std::unordered_set<char>);
        virtual std::vector<char> getTape();
        virtual void setTape(std::vector<char> val);
        virtual unsigned int getHeadPosition();
        virtual void setHeadPosition(int);
    protected:
    private:
        std::unordered_set<char> alphabet;
        std::vector<char> tape;
        unsigned int headPosition;
};

#endif // TMINPUTINTERFACE_H
