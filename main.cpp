
#include <iostream>
#include "polynom.h"
#include "algorithm.h"
using namespace std;

int main() {
    int secr[] = {1, 1, -1, 1, -1};
    int mesg[] = {1, 1,  1, 1,  1};
    own::ntru fun(own::polynom(5, secr), 3, 11);

    own::polynom msg(5, mesg);
    own::polynom enc_msg = fun.encrypt(msg);
    own::polynom dec_msg = fun.decrypt(enc_msg);

        msg.draw(cout) << " - before changes" << endl;
    enc_msg.draw(cout) << " - encrypted" << endl;
    dec_msg.draw(cout) << " - decrypted" << endl;

    return 0;
}
