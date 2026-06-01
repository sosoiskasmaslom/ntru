
#include <iostream>
#include "polynom.h"
#include "algorithm.h"
using namespace std;

//int main() {
//    int a[] = {1, 2, 0, 1, 1};
//    int b[] = {1, 0, 1};
//
//    own::polynom pa(5, a);
//    own::polynom pb(3, b);
//
//    pb.mod(pa).draw(cout);
//}

//int main() {
//
//    int a[] = {6, -6, 6, -6};
//    int b[] = {1, 1};
//
//    own::polynom pa(4, a);
//    own::polynom pb(2, b);
//    own::polynom pc(1, 1);
//
//    (pc -= pa.mult(pb)).mod(11).draw(cout);
//    //(pa += pc).draw(cout);
//}

//int main() {
//    int a[] = {-1, 0, 0, 0, 0, 1};
//    int b[] = {1, 1, -1, 1, -1};
//
//    own::polynom pa(6, a);
//    own::polynom pb(5, b);
//
//    own::polynom *res = pa.division(pb);
//    (*(res)).draw(cout);
//    (*(res+1)).draw(cout);
//    delete[] res;
//}

//int main() {
//    int p = 3, q = 12, N = 5;
//
//    int secr[] = {1, 1, -1, 1, -1};
//    own::polynom key(N, secr);
//
//    own::polynom N_minus_one(N+1, 0);
//    N_minus_one[0] = -1; N_minus_one[-1] = 1;
//
//    //own::polynom F_p = key.rev(N_minus_one, p).mod(q);
//    own::polynom F_q = key.rev(N_minus_one, q).mod(q);
//    F_q.draw(cout);
//
//    //own::polynom h = (F_q).rev(N_minus_one, q).mod(q);
//
//    //key.rev(N_minus_one, p).mod(p).draw(cout);
//    //key.draw(cout);
//
//    //own::polynom *tmp = N_minus_one.division(key);
//    //(*tmp).mod(p).draw(cout);
//    //(*(tmp+1)).mod(p).draw(cout);
//
//    return 0;
//}

int main() {
    own::size_t secr[] = {1, 1, -1, 1, -1};
    own::size_t mesg[] = {1, 1,  0, 0,  1};
    own::ntru fun(own::polynom(5, secr), 3, 11);

    own::polynom msg(5, mesg);
    own::polynom enc_msg = fun.encrypt(msg);
    own::polynom dec_msg = fun.decrypt(enc_msg);

        msg.draw(cout) << " - before changes" << endl;
    enc_msg.draw(cout) << " - encrypted" << endl;
    dec_msg.mod(3).draw(cout) << " - decrypted" << endl;

    return 0;
}
