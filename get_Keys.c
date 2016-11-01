#include <stdlib.h>
#include "Parameters.h"
#include "paillier.h"

int get_pub_Keys(paillier_public_key *pub, FILE *public_key){
       
    paillier_public_init(pub);    
    paillier_public_in_str(pub, public_key);
   
    return 0;
}

int get_priv_Keys(paillier_private_key *priv, FILE *private_key){
       
    paillier_private_init(priv);    
    paillier_private_in_str(priv, private_key);
   
    return 0;
}