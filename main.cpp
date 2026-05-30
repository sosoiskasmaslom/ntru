
#include <iostream>
#include "polynom.h"
#include "algorithm.h"
using namespace std;

int main() {
    int a[] = {-1, 1, -1, 1};
    int b[] = {1, 1};

    own::polynom pa(4, a);
    own::polynom pb(2, b);

    pa.mult(pb).draw(cout);
}

//int main() {
//    int p = 11, N = 5;
//
//    int secr[] = {1, 1, -1, 1, -1};
//    own::polynom key(N, secr);
//
//    own::polynom N_minus_one(N+1, 0);
//    N_minus_one[0] = -1; N_minus_one[-1] = 1;
//
//    key.draw(cout);
//    key.rev(N_minus_one, p).draw(cout);
//
//    return 0;
//}

//int main() {
//    int secr[] = {1, 1, -1, 1, -1};
//    int mesg[] = {1, 1,  1, 1,  1};
//    own::ntru fun(own::polynom(5, secr), 3, 11);
//
//    own::polynom msg(5, mesg);
//    own::polynom enc_msg = fun.encrypt(msg);
//    own::polynom dec_msg = fun.decrypt(enc_msg);
//
//        msg.draw(cout) << " - before changes" << endl;
//    enc_msg.draw(cout) << " - encrypted" << endl;
//    dec_msg.draw(cout) << " - decrypted" << endl;
//
//    return 0;
//}
