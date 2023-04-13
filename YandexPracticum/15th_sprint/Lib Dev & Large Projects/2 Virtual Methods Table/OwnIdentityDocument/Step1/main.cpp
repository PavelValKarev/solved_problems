#include <iostream>
#include <string>

#include "identity_document.h"
#include "passport.h"

void PrintID(IdentityDocument* identity_document) {
    identity_document->PrintID();
}

int main() {
   IdentityDocument* identity_document = (IdentityDocument*)(new Passport());
   PrintID(identity_document);
   identity_document->Delete();
   identity_document->PrintUniqueIDCount();
}
