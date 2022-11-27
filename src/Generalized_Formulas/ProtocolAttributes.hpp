using namespace std;

template<typename T>
class ProtocolAttributes    {
protected:
    string name_;
    T invariant;
    
    ProtocolAttributes<T>(const string &name) : name_(name)   {}
    ProtocolAttributes<T>() : name_("What") {}

    #define r(x)    r.find(x)-> second
public:
    string name()           {   return  name_;  }
    void setInvariant(T C)  {   invariant = C;  }

    // disallow copying
	ProtocolAttributes & operator=(const ProtocolAttributes &) = delete;
	ProtocolAttributes(const ProtocolAttributes &) = delete;
};