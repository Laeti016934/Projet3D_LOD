#pragma once

// In C++, a struct is a class where all of the members are public by default.
// Using the class keyword instead would make all of the members private by default.
// Useful for small objects where changing any and all members manually is perfectly fine.
struct Triangle
{
    //Constructors
    Triangle();
    Triangle(const Triangle& t);    //In C++, the & symbol can mean de-referencing like in C, but here it means a reference.
                                    //A reference is a pointer that cannot be NULL (nullptr in C++) and always points to the same thing.
                                    //Since it cannot be nullptr, it can be syntaxically accessed using "." instead of "->".
    Triangle(unsigned int v0, unsigned int v1, unsigned int v2);

    //Destructor
	~Triangle ();

    //Operators. In C++, operators such as +, -=, ++, =, >=, [] etc. can be implemented explicitely.
    unsigned int& operator [] (unsigned int iv);
    unsigned int operator [] (unsigned int iv) const;
    Triangle& operator = (const Triangle &t);

    //Members.
    unsigned int v[3];
};
