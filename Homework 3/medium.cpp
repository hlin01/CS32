//
//  main.cpp
//  Homework 3
//
//  Created by Hender Lin on 5/2/21.
//

class Medium
{
public:
    Medium(string id) {m_id = id;}
    virtual string connect() const = 0;
    string id() const {return m_id;}
    virtual string transmit(string msg) const {return "text: " + msg;}
    virtual ~Medium(){};

private:
    string m_id;
};

class TwitterAccount: public Medium
{
public:
    TwitterAccount(string id): Medium (id){};
    virtual string connect() const {return "Tweet";}
    virtual ~TwitterAccount() {cout << "Destroying the Twitter account " + this->id() + "." << endl;}
};

class Phone: public Medium
{
public:
    Phone(string id, CallType type): Medium (id) {m_type = type;}
    virtual string connect() const {return "Call";}
    string type() const;
    virtual string transmit(string msg) const {return type() + ": " + msg;}
    virtual ~Phone() {cout << "Destroying the phone " + this->id() + "." << endl;}

private:
    CallType m_type;
};

string Phone::type() const
{
    if (m_type == VOICE)
    {
        return "voice";
    }
    else
    {
        return "text";
    }
}

class EmailAccount: public Medium
{
public:
    EmailAccount(string id): Medium (id){};
    virtual string connect() const {return "Email";}
    virtual ~EmailAccount() {cout << "Destroying the email account " + this->id() + "." << endl;}
};

void send(const Medium* m, string msg)
{
    cout << m->connect() << " using id " << m->id()
         << ", sending " << m->transmit(msg) << endl;
}
