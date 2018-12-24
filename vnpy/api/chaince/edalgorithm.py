# -*- coding: utf-8 -*-
from jwt.algorithms import Algorithm
from . import ed25519
import base64


def base64url_decode(input):
    rem = len(input) % 4
    if rem > 0:
        input += b'=' * (4 - rem)
    return base64.urlsafe_b64decode(input)


class EDAlgorithm(Algorithm):

    def prepare_key(self, key):
        if isinstance(key, unicode):
            key = key.encode('utf-8')

        if isinstance(key, bytes):
            if len(key) == 43:
                key = base64url_decode(key)
        else:
            raise TypeError("Expecting an Ed25519 compatible key.")

        # mimic nacl's SigningKey
        class Ed25519Key(bytes):
            @property
            def verify_key(self):
                return ed25519.publickey(self)

        return Ed25519Key(key)

    def sign(self, msg, key):
        pk = ed25519.publickey(key)
        return ed25519.signature(msg, key, pk)

    def verify(self, msg, key, sig):
        try:
            ed25519.checkvalid(sig, msg, key)
        except:
            return False
        return True

