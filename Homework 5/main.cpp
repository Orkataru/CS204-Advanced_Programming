#include <iostream>
#include "SUBook.h"
using namespace std;

int main() {
    User u1("name");
    Post& p = u1.createPost("Post 1");
    p.addComment("Comment 1", &u1);
    cout << u1.getNumComments() << " " << p.getComments().size() << " "
        << p.getComments()[0]->getUser().getName() << " " <<
        p.getComments()[0]->getContent() << " " << endl;
    p.addComment("Comment 2", &u1);
    cout << u1.getNumComments() << " " << p.getComments().size() << " "
        << p.getComments()[1]->getUser().getName() << " " <<
        p.getComments()[1]->getContent() << " " << endl;
    return 0;
}
