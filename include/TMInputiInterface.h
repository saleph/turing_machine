#ifndef TMINPUTINTERFACE_H
#define TMINPUTINTERFACE_H

#include <string>
using std::string;


struct TMContent {
    string rawAlphabet;
    string rawControlGraph;
};


class TMInputInterface
{
    public:
        virtual ~TMInputInterface() {}
        virtual void setContent(string alphabet, string controlGraph) = 0;
        string getRawAlphabet() { return content.rawAlphabet; }
        string getRawControlGraph() { return content.rawControlGraph; }
    protected:
        TMContent content;
};

#endif // TMINPUTINTERFACE_H
